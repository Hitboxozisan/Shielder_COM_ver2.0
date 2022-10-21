#pragma once

#include "SceneBase.h"
#include <list>

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

	std::list<Bullet*> activeBullet;
	std::list<Bullet*> deactiveBullet;


	void UpdateStart();
	void UpdateGame();
	void UpdateGameOver();
	void UpdateResult();
	void (GameMain::* pUpdate)();

	int frame;							//åoâﬂÉtÉåÅ[ÉÄ
};