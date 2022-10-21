#pragma once

#include "Mover.h"

using namespace My3dLib;

class Shield;
class Bullet;
class BulletCreater;
class EffectManager;

//状態
//namespace CharacterState
//{
//	enum State
//	{
//		NONE,		//存在しない
//		NORMAL,		//通常
//		ATTACK,		//攻撃
//		DEFENSE,	//防御
//		SLIDE,		//防御時に接触
//		DAMAGE,		//被弾
//		DEAD		//死亡
//	};
//}

class Character : public Mover
{
public:

	Character(BulletCreater* const);
	virtual ~Character();

	virtual void Initialize(EffectManager* const inEffectManager) = 0;
	void Finalize();

	virtual void Update() = 0;
	virtual void Draw() = 0;
	void MoveFinish();				//移動予定地に実際に移動する

	//当たり判定関係関数
	virtual void OnHitOtherCharacter(const VECTOR& forceDirection) = 0;		//他のキャラクターと当たった
	virtual void OnHitShield(const VECTOR& adjust) = 0;						//盾とキャラクターが当たった
	virtual void OnHitShieldWithBullet(const VECTOR& adjust) = 0;			//盾と弾が接触した

	//ゲッター
	const float& GetHitPoint() const { return hitPoint; }							//現在のhitPointを返す
	const VECTOR& GetNextPosition() const  { return nextPosition; }					//移動予定位置を返す
	const VECTOR GetCollisionShere() const { return collisionSphere.worldCenter; }	//当たり判定球を返す
	const float GetCollisionRadius() const { return collisionSphere.radius; }		//当たり判定球の半径を返す
	const bool IsCollidableState() const;											//何かと接触できる状態か
	const float GetInvicibleTime() const { return invincibleTime; }					//無敵時間の経過時間を返す
	virtual const bool IsAlive() const = 0;

	Shield* GetShieldPointer() const { return shield; }
	Bullet* GetBulletPointer() const { return bullet; }

	//デバッグ用
	const VECTOR& GetVelocity() const { return velocity; }		// 現在の速度、加速度、向きを返す
	const float& GetTrunkPoint() const { return trunkPoint; }	// 現在の体幹ゲージを返す

protected:
	VECTOR inputDirection;

	int   id;				// キャラの識別番号
	float hitPoint;			// キャラの体力
	float trunkPoint;		// 体幹ゲージの量
	float speed;			// 移動速度
	VECTOR velocity;		// 現在の速度、加速度、向き
	VECTOR nextPosition;	// 移動予定のポジション
	VECTOR nextDirction;	// 移動後の予定の向き
	VECTOR prevPosition;	// 前フレームのポジション
	VECTOR prevDirection;	// 前フレームの向き
	bool   noDrawFrame;		// 描画しないフレームか
	float invincibleTime;	// 無敵時間

	//CharacterState::State state;	

	Shield* shield;			//盾のインスタンス

	Bullet* bullet;			//弾のインスタンス
	BulletCreater* const bulletCreater;		//弾生成クラスのポインタ

	Sphere collisionSphere;	//当たり判定球
private:
	//定数
	/*static const float COLLIDE_RADIUS;
	static const float NORMAL_SPEED;
	static const float DEFENSE_SPEED;*/
	
	

	virtual void InputAction() = 0;
};

