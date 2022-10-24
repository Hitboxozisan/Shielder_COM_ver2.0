#pragma once

#include "SceneBase.h"

#include <string>

class Result final : public SceneBase 
{
public:
	Result(SceneManager* const sceneManager);
	~Result();

	void Initialize();	//初期化処理
	void Finalize();	//終了処理
	void Activate();	//活性化処理
	void Deactivate();	//非活性化処理
	void Update();		//更新処理
	void Draw();		//描画処理


private:
	Result();
	Result(const Result&);
	void operator=(const Result&);

	static const std::string IMAGE_FOLDER_PATH;
	static const std::string RESULT_PATH;
	static const std::string FILENAME_EXTENSION;

	int font;
	int number[9];
	int alpha;
	int alphaAdd;
	int imageHandle;
	int lifeBonus;
	int destroyBonus;
	int totalScore;
	int pushEnterImageHandle;

	int frame;
};

