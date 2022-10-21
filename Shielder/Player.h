#pragma once

#include "Character.h"

class Shield;
class EffectManager;

class Player final : public Character
{
public:
	enum State
	{
		NONE,		//存在しない
		NORMAL,		//通常
		DEFENSE,	//防御
		SLIDE,		//防御時に接触
		DAMAGE,		//被弾
		RIGOR,		//硬直
		DEAD		//死亡
	};
	
	Player(BulletCreater* const);
	~Player();

	void Initialize(EffectManager* const inEffectManager);
	void Update();

	void Draw();

	void ReleaseInvincible();							//無敵解除

	//当たり判定関係関数
	void OnHitOtherCharacter(const VECTOR& forceDirection);
	void OnHitShield(const VECTOR& adjust);				//盾とキャラクターが当たった
	void OnHitShieldWithBullet(const VECTOR& adjust);

	//ゲッター
	const State GetState() const { return state; }
	const float GetTrunk() const { return trunkPoint; }
	const bool IsAlive() const;
	const bool IsJust() const { return isJust; };

	//デバッグ用
	const float GetInvincibleTime() const { return invincibleTime; }

private:
	//Player();
	Player(const Player&);			//コピーコンストラクタ
	void operator=(const Player&);	//コピー代入演算子

	static const float HIT_POINT;							//体力
	static const float DECREMENT_HIT_POINT;					//体力の減少量
	static const float COLLIDE_RADIUS;						//当たり判定球半径
	static const float NORMAL_SPEED;						//NORMAL時の移動速度
	static const float DEFENSE_SPEED;						//DEFENSE時の移動速度
	static const float HIT_OTHER_CHARACTER_DIRECTION_Y;		//敵キャラと当たった時のY方向の向き
	static const float JUST_DEFENSE_TIME;					//ジャストガードと判断する時間
	static const float NORMAL_DEFENSE_TIME;					//ノーマルガードと判断する時間
	static const float STOP_VELOCITY;						//止まったと判断する速度
	static const float GRAVITY;								//重力
	static const float FRICTION_FORCE;						//摩擦力
	static const float TRUNK_POINT;							//体幹ゲージ
	static const float INCREASE_TRUNK_POINT;				//体幹ゲージ減少量
	static const float INVINCIBLE_TIME;						//無敵時間
	static const float DEFENCE_INTERVAL;					//次に防御できるまでの時間

	State state;
	EffectManager* effectManager;

	float defenceInterval;			//盾を展開してからの経過時間
	float justDefenceTime;			//ジャストガードと判断する時間
	float normalDefenceTime;		//ノーマルガードと判断する時間
	
	bool isJust;					//ジャストガードか

	void (Player::* pUpdate)();		//Update関数ポインタ



	//各状態の更新処理
	void UpdateNormal();
	void UpdateDefence();
	void UpdateSlide();
	void UpdateDamage();
	void UpdateRigor();


	void Move();
	void MoveFinish();
	void Jump();
	void Defense();
	void Slide();		//ジャストガード以外で接触
	void Damage();		//被弾
	void Rigor();		//硬直
	void InputAction();
	void CreateShield();
};

