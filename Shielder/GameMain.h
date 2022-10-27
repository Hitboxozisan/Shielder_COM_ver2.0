#pragma once

#include "SceneBase.h"
#include <list>
#include <string>

class Camera;
class Player;
class Enemy;
class Character;
class HitChecker;
class Bullet;
class BulletCreater;
class Background;
class EffectManager;
class GuardEffect;
class UiManager;
class Result;

class GameMain final : public SceneBase
{
public:
	GameMain(SceneManager* const sceneManager);
	~GameMain();

	void Initialize();
	void Finalize();
	void Activate();
	void Deactivate();
	void Update();
	void Draw();

	enum State
	{
		START,
		GAME,
		GAME_OVER,
		RESULT
	};

private:
	GameMain();
	GameMain(const GameMain&);
	void operator=(const GameMain&);

	//ファイルパス
	static const std::string IMAGE_FOLDER_PATH;
	static const std::string RESULT_PATH;
	static const std::string  FILENAME_EXTENSION;

	static const int PLAYER_AMOUNT;
	static const int ENEMY_AMOUNT;
	static const int CHARACTER_AMOUNT;
	static const float MAX_BULLET_AMOUNT;

	State state;

	Camera* camera;
	Character** character;
	Background* background;
	HitChecker* hitchecker;
	BulletCreater* bulletCreater;
	GuardEffect* guardEffect;
	EffectManager* effectManager;
	UiManager* uiManager;
	//Result* result;

	std::list<Bullet*> activeBullet;
	std::list<Bullet*> deactiveBullet;


	void UpdateStart();
	void UpdateGame();
	void UpdateGameOver();
	void UpdateResult();
	void (GameMain::* pUpdate)();

	int fontHandle;						//フォント用ハンドル
	int resultImageHandle;				//リザルト画面画像
	int lifeScore;
	int destroyScore;
	int totalScore;
	int frame;							//経過フレーム

	int alpha;							//ALPHA値（テスト）
};