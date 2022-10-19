#pragma once

class SceneBase;

class SceneManager final
{
public:
	//シーン状態定義
	enum Scene
	{
		TITLE = 0,	//タイトル画面
		GAME_MAIN,	//ゲーム画面
		RESULT,		//リザルト画面
		END			//終了する　兼　シーンの個数
	};

	SceneManager();
	~SceneManager();

	void Initialize();
	void Finalize();
	void Update();
	void Draw();

	void SetNextScene(Scene next);
	Scene GetCurrentScene() { return currentScene; }
	Scene GetNextScene() { return nextScene; }
private:
	SceneManager(const SceneManager&);		//コピーコンストラクタ
	void operator=(const SceneManager&);	//コピー代入演算子

	SceneBase* eachScenes[Scene::END];		//各シーンのインスタンス
	SceneBase* currentPointer;				//現在のシーンのポインタ
	Scene	   currentScene;				//現在のシーン
	Scene	   nextScene;					//次のシーン

	void ChangeScene();						//シーンを変更する
};

