#pragma once

#include "SceneBase.h"

#include <string>

class Character;

/// <summary>
/// Resultクラス現在不使用
/// GameMainにて別途Result作成
/// </summary>
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
	int imageHandle;					//Result画面画像
	int playerLife;						//プレイヤーの残り体力
	int destroy;						//倒したか
	int lifeBonus;
	int destroyBonus;
	int totalScore;
	int pushEnterImageHandle;

	int frame;

	Character** character;

	//void SetCharacter(Character** character);
};

