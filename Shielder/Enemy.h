#pragma once

#include "Character.h"

class Enemy final : public Character
{
public:
	//残り体力
	enum EnemyState
	{
		FINE,
		CAUTION,
		DENGER
	};

	//行動状態
	enum State
	{
		NONE,		//存在しない
		NORMAL,		//通常
		ATTACK,		//攻撃
		SLIDE,		//跳ね返る
		DAMAGE,		//被弾
		DEAD		//死亡
	};

	enum AttackType
	{
		ASSAULT = 0,	//突進攻撃
		BULLET,			//通常弾発射
		SLOW_BULLET,	//遅延弾発射
		JUMP,			//ジャンプ
		KICK,			//キック
		JUDGE,			//どこにいるか判断
		BACK,			//画面端に戻る

		ATTACK_AMOUST	//行動パターン数
	};

	Enemy(BulletCreater* const);
	~Enemy();
	void Initialize(EffectManager* const inEffectManager);
	void Update();

	void Draw();
	void OnHitOtherCharacter(const VECTOR& forceDirection, bool just);		//他のキャラクターと当たった
	void OnHitShield(const VECTOR& adjust, bool just);						//盾とキャラクターが当たった
	void OnHitShieldWithBullet(const VECTOR& adjust, bool just);

	//const bool IsCollidableState() const;
	const float GetTrunk() const { return trunkPoint; }
	const bool IsAlive() const;

	//デバッグ
	const float GetInterval() const { return shotInterval; }

private:
	static const float COLLIDE_RADIUS;
	static const float NORMAL_SPEED;
	static const float DEFENSE_SPEED;
	static const float KICK_SPEED;							//キック時スピード
	static const float JUMP_DIRECTION_Y;					//ジャンプ時に上方向に加える力
	static const float JUMP_HEIGHT;							//JUMPKICK時の最大高度
	static const float STOP_VELOCITY;
	static const float FRICTION_FORCE;
	static const float GRAVITY;								//重力
	static const float TRUNK_POINT;							//体幹ゲージ
	static const float INCREASE_TRUNK_POINT;				//体幹ゲージ減少量
	static const float ASSAULT_MAGNIFICATION;				//ASSAULT時の減少倍率
	static const float BULLET_MAGNIFICATION;				//BULLET時の減少倍率
	static const float SLOW_BULLET_MAGNIFICATION;			//SLOW_BULLET時の減少倍率
	static const float JUMPKICK_MAGNIFICATION;				//JUMPKICK時の減少倍率
	static const float SHOT_INTERVAL;

	float frame;
	float trunkMagnification;		//防がれたときの体幹ゲージの減る倍率
	int assaultCount;
	float movedDistance;			//移動を始めてからの移動量
	float stopTime;					//停止してからの経過時間
	bool stopMove;					//停止しているか
	bool currentRightPosition;		//右側にいるか
	float shotInterval;				//発射間隔
	int   shotCount;				//発射回数

	void (Enemy::*pUpdate)();				//Update関数ポインタ

	VECTOR vec;
	VECTOR returnForce;
	VECTOR jumpPower;
	EnemyState physical;
	State state;
	AttackType attackType;					//敵の行動パターン
	AttackType prevType;					//前回の行動パターン
	
	//各状態に応じた更新処理
	void UpdateFine();
	void UpdateCaution();
	void UpdateDenger();
	void UpdateNormal();
	void UpdateAttack();
	void UpdateSlide();
	void UpdateDamage();

	void Move();
	void MoveFinish();
	void Assault();				//突進攻撃
	void Bullet();				//弾発射
	void SlowBullet();
	void Jump();				//ジャンプ後プレイヤーに向かって突進
	void Kick();
	void Back();				//画面端に戻る
	void Slide();

	void CreateBullet();				//弾を生成する
	void ShootBullet();					//弾を発射する
	void SetNextAttack();				//次の行動を決定する
	void CurrentPositionJudge();		//エネミーが画面の右左どちら側にいるか

	void InputAction();
};

