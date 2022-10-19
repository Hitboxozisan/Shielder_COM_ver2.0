#include "Pch.h"


#include "ModelManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "DeltaTime.h"


// ラインを描く範囲
#define LINE_AREA_SIZE			10000.0f
// ラインの数
#define LINE_NUM			50


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(IS_WINDOW_MODE);
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16);

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//Effekseerを初期化する
	//引数は画面に表示する最大パーティクル数
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DXライブラリのデバイスロストした時のコールバックを設定する。
	// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
	// ただし、DirectX11を使用する場合は実行する必要はない。
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Zバッファを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetUseZBuffer3D(TRUE);

	// Zバッファへの書き込みを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetWriteZBuffer3D(TRUE);

	ModelManager::GetInstance();

	SceneManager* sceneManager = new SceneManager();
	sceneManager->Initialize();

	int nowCount, prevCount;
	nowCount = prevCount = GetNowCount();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//deltaTimeの計測
		float deltaTime;
		nowCount = GetNowCount();
		deltaTime = (nowCount - prevCount) / 1000.0f;
		DeltaTime::GetInstace().SetDeltaTime(deltaTime);
		KeyManager::GetInstance().Update();		//入力処理

		sceneManager->Update();					//各シーンに応じた更新処理
		
		//画面更新処理
		ClearDrawScreen();
		//UpdateEffekseer3D();

		sceneManager->Draw();					//各シーンに応じた描画処理

#ifdef DEBUG
		
#endif // DEBUG

		ScreenFlip();
		prevCount = nowCount;
	}

	//Effekseerを終了する
	Effkseer_End();

	// ＤＸライブラリ使用の終了処理
	DxLib_End();

	// ソフトの終了
	return 0;
}