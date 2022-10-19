#include "Pch.h"
#include "UiManager.h"

using std::string;

const std::string UiManager::GRAPHIC_FOLDER_PATH = "Data/Image/";
const std::string UiManager::UI_GRAPHIC_PATH = "ui";
const std::string UiManager::FILENAME_EXTENSION = ".png";

UiManager::UiManager()
	:imageHandle()
	,frame(0)
{
}

UiManager::~UiManager()
{
	if (imageHandle[0] != NULL)
	{
		Finalize();
	}
}

void UiManager::Initialize()
{
	string path = GRAPHIC_FOLDER_PATH + UI_GRAPHIC_PATH;
	string fullPath = path;

	for (int i = 0; i < IMAGE_AMOUNT; ++i)
	{
		fullPath = path + std::to_string(i) + FILENAME_EXTENSION;
		imageHandle[i] = LoadGraph(fullPath.c_str());

		if (imageHandle[i] < 0)
		{
			printfDx("画像読み込みに失敗_ui[%d]", i);
		}
	}


}

void UiManager::Finalize()
{
	for (int i = 0; i < IMAGE_AMOUNT; ++i)
	{
		DeleteGraph(imageHandle[i]);
		imageHandle[i] = NULL;
	}
}

void UiManager::Draw(GameMain::State state, float characterHp, float playerTrunk, float enemyTrunk)
{
	++frame;
	switch (state)
	{
	case GameMain::START:
		StartBattleDraw();
		break;
	case GameMain::GAME:
		PlayerHpDraw(characterHp);
		TrunkGaugeDraw(playerTrunk, enemyTrunk);
		break;
	case GameMain::GAME_OVER:
		break;
	case GameMain::RESULT:
		break;
	default:
		break;
	}
	
}

void UiManager::StartBattleDraw()
{
	if (frame <= 100)
	{
		//最大体力をいったん100とする
		float playerMaxHp = 100.0f;
		//最大体幹量をいったん100とする
		float playerMaxTrunk = 100.0f;
		float enemyMaxTrunk = 100.0f;

		//体力ゲージ表示
		DrawBox(20, 445, 40 + 100 * frame / playerMaxHp, 450, GetColor(0, 255, 0), TRUE);
		//体力ゲージ枠
		DrawRotaGraph(80, 445, 0.2, 0.0, imageHandle[PLAYER_HP], TRUE);

		//体幹ゲージ表示
		DrawBox(195, 440, 195 + 240 * (frame / playerMaxTrunk), 455, GetColor(0, 255, 0), TRUE);			//プレイヤーの体幹ゲージ
		DrawBox(35, 95, 35 + 570 * (frame / enemyMaxTrunk), 105, GetColor(0, 255, 0), TRUE);					//エネミーの体幹ゲージ
		//ゲージの枠を表示
		DrawRotaGraph(315, 450, 0.4, 0.0, imageHandle[PLAYER_TRUNK], TRUE);		//プレイヤーゲージ枠
		DrawRotaGraph(320, 100, 0.3, 0.0, imageHandle[ENEMY_TRUNK], TRUE);		//エネミーゲージ枠
	}
}

void UiManager::PlayerHpDraw(float characterHp)
{
	//最大体力をいったん100とする
	float playerMaxHp = 100.0f;
	//DrawGraphF(50, 300, imageHandle[PLAYER_HP], TRUE);

	//体力ゲージ表示
	DrawBox(20, 445, 40 + 100 * characterHp/playerMaxHp, 450, GetColor(0, 255, 0), TRUE);
	//体力ゲージ枠
	DrawRotaGraph(80, 445, 0.2, 0.0, imageHandle[PLAYER_HP], TRUE);
}

void UiManager::TrunkGaugeDraw(float playerTrunk, float enemyTrunk)
{
	//最大体幹量をいったん100とする
	float playerMaxTrunk = 100.0f;
	float enemyMaxTrunk = 100.0f;

	//DrawGraphF(200, 400, imageHandle[PLAYER_TRUNK], TRUE);
	//DrawGraphF(200, 200, imageHandle[ENEMY_TRUNK], TRUE);

	//体幹ゲージ表示
	DrawBox(195, 440, 195 + 240 * (playerTrunk/playerMaxTrunk), 455, GetColor(0, 255, 0), TRUE);			//プレイヤーの体幹ゲージ
	DrawBox(35, 95, 35 + 570 * (enemyTrunk/enemyMaxTrunk), 105, GetColor(0, 255, 0), TRUE);					//エネミーの体幹ゲージ
	//ゲージの枠を表示
	DrawRotaGraph(315, 450, 0.4, 0.0, imageHandle[PLAYER_TRUNK], TRUE);		//プレイヤーゲージ枠
	DrawRotaGraph(320, 100, 0.3, 0.0, imageHandle[ENEMY_TRUNK], TRUE);		//エネミーゲージ枠

}

void UiManager::DrawTitle()
{
}


