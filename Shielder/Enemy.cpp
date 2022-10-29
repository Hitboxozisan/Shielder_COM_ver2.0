#include "Pch.h"
#include <chrono>
#include <thread>
#include <random>
#include "Enemy.h"

#include "EnemyAi.h"
#include "Bullet.h"
#include "BulletCreater.h"

#include "ModelManager.h"
#include "DeltaTime.h"

#ifdef DEBUG

#include"KeyManager.h"

#endif // DEBUG


const float Enemy::COLLIDE_RADIUS = 50.0f;
const float Enemy::NORMAL_SPEED = 3.0f;
const float Enemy::DEFENSE_SPEED = 2.0f;
const float Enemy::KICK_SPEED = 20.0f;							
const float Enemy::JUMP_DIRECTION_Y = -30.0f;
const float Enemy::JUMP_HEIGHT = 600.0f;
const float Enemy::STOP_VELOCITY = 0.5f;
const float Enemy::FRICTION_FORCE = 0.05f;
const float Enemy::GRAVITY = 0.25f;
const float Enemy::TRUNK_POINT = 100.0f;
const float Enemy::INCREASE_TRUNK_POINT = 5.0f;
const float Enemy::ASSAULT_MAGNIFICATION = 1.0f;
const float Enemy::BULLET_MAGNIFICATION = 0.8;	
const float Enemy::SLOW_BULLET_MAGNIFICATION = 0.3;
const float Enemy::JUMPKICK_MAGNIFICATION = 0.5f;
const float Enemy::SHOT_INTERVAL = 0.5f;

Enemy::Enemy(BulletCreater* const inBulletCreater)
	:Character(inBulletCreater)
	,frame(0.0f)
	,trunkMagnification()
	,assaultCount(0)
	,movedDistance(0.0f)
	,stopTime(0.0f)
	,stopMove()
	,currentRightPosition()
	,shotInterval()
	,shotCount(0)
	,physical(FINE)
	,state(NONE)
	,attackType()
	,prevType()
{

}

Enemy::~Enemy()
{

}

void Enemy::Initialize(EffectManager* const inEffectManager)
{
	vec = LEFT;
	speed = NORMAL_SPEED;
	trunkPoint = 0;
	position = VGet(2400.0f, 1.0f, 100.0f);
	nextPosition = position;
	direction = ZERO_VECTOR;
	nextDirction = direction;


	//direction = VGet(1.0f, 0.0f, 0.0f);

	state = NORMAL;
	prevType = attackType;
	attackType = JUDGE;

	pUpdate = &Enemy::UpdateAttack;

	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY));
	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータの読み込み_Enemy\n");
	}

	MV1SetScale(modelHandle, VGet(0.5f, 0.5f, 0.5f));

	//当たり判定球を設定
	collisionSphere.localCenter = VGet(0.0f, 0.0f, 0.0f);
	collisionSphere.radius = COLLIDE_RADIUS;
	collisionSphere.worldCenter = position;
}

void Enemy::Update()
{
#ifdef DEBUG
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_RSHIFT))
	{
		trunkPoint = 99.0f;
	}

#endif // DEBUG

	if (this->pUpdate != nullptr)
	{
		switch (physical)
		{
		case FINE:
			(this->*pUpdate)();
			break;
		case CAUTION:
			(this->*pUpdate)();
			break;
		case DENGER:
			(this->*pUpdate)();
			break;
		}
	}

	collisionSphere.localCenter.y = 30.0f;

	//体幹ゲージが0になったら死亡する
	if (trunkPoint >= 100.0f)
	{
		WaitTimer(0);
		//エフェクト再生

		state = DEAD;
	}
	
}

void Enemy::Draw()
{
	MV1DrawModel(modelHandle);

	//UI
	DrawFormatString(300, 130, GetColor(255, 255, 255), "E : %f", this->GetTrunk(), TRUE);		//体幹ゲージ表示
	DrawFormatString(300, 170, GetColor(255, 255, 255), "MD : %f", movedDistance, TRUE);
	DrawFormatString(300, 190, GetColor(255, 255, 255), "Interval : %f", GetInterval(), TRUE);
	DrawFormatString(300, 210, GetColor(255, 255, 255), "AT : %d", attackType);
	DrawFormatString(300, 230, GetColor(255, 255, 255), "ShotCount : %d", shotCount);
	DrawFormatString(300, 250, GetColor(255, 255, 255), "PrevType : %d", prevType);


	//当たり判定デバック描画
	DrawSphere3D(collisionSphere.worldCenter, collisionSphere.radius,
		8, GetColor(0, 255, 0), 0, FALSE);
	
}

void Enemy::OnHitOtherCharacter(const VECTOR& forceDirection, bool just)
{
	stopTime = 0.0f;
	//移動を止める
	stopMove = true;
}

void Enemy::OnHitShield(const VECTOR& adjust, bool just)
{
	bool isjust;			//ジャストガードされたか
	isjust = just;
	//前回のvelocityをリセットする
	velocity = ZERO_VECTOR;
	stopTime = 0.0f;
	stopMove = true;

	VECTOR force = adjust;
	force.y = 0.0f;			//変な方向に動かないようにする
	force.z = 0.0f;			//変な方向に動かないようにする

	force = VScale(force, -3.0f);

	//後退させる
	velocity = VAdd(velocity, force);
	
	//ジャストガードじゃなければ減少量を半減させる
	if (isjust)
	{
		trunkPoint += INCREASE_TRUNK_POINT * trunkMagnification;
	}
	else
	{
		trunkPoint += INCREASE_TRUNK_POINT * trunkMagnification * 0.5;
	}
	state = SLIDE;
	pUpdate = &Enemy::UpdateSlide;
	
	//bullet = nullptr;
}

/// <summary>
/// 盾と弾が接触した
/// </summary>
/// <param name="adjust"></param>
void Enemy::OnHitShieldWithBullet(const VECTOR& adjust, bool just)
{
	bool isjust;
	isjust = just;

	//ジャストガードじゃなければ減少量を半減させる
	if (isjust)
	{
		trunkPoint += INCREASE_TRUNK_POINT * trunkMagnification;
	}
	else
	{
		trunkPoint += INCREASE_TRUNK_POINT * trunkMagnification * 0.5;
	}
}

const bool Enemy::IsAlive() const
{
	//存在しないなら死んでいる状態にする
	if (state == NONE ||
		state == DEAD)
	{
		return false;
	}

	return true;
}

//const bool Enemy::IsCollidableState() const
//{
//	return false;
//}

void Enemy::Move()
{
	if (!VSquareSize(inputDirection) == 0.0f)
	{
		nextDirction = VNorm(inputDirection);
	}
	else
	{
		nextDirction = inputDirection;
	}

	nextPosition = VAdd(position, VScale(nextDirction, speed));
}

void Enemy::MoveFinish()
{
	prevPosition = position;
	position = nextPosition;
	direction = nextDirction;

	//位置を設定
	MV1SetPosition(modelHandle, position);

	//移動キーを押していない場合は向きを固定する
	if (!VSquareSize(inputDirection) == 0.0f)
	{
		MV1SetRotationYUseDir(modelHandle, direction, 0.0f);
	}

}

/// <summary>
/// 突進攻撃
/// </summary>
void Enemy::Assault()
{
	
	VECTOR force = VGet(1.0f, 0.0f, 0.0f);			//移動量を設定
	force.y = 0.0f;			//変な方向に動かないようにする
	force.z = 0.0f;			//変な方向に動かないようにする

	//エネミーの現在地が右端寄りなら
	if (currentRightPosition)
	{
		force = VScale(force, 0.5f);		//左側に力を与える
	}
	else
	{
		force = VScale(force, -0.5f);		//右側に力を与える
	}
	
	//突進させる
	if (movedDistance <= 300.0f && movedDistance >= -300.0f)
	{
		stopTime = 0.0f;
		velocity = VAdd(velocity, force);
		nextPosition = VAdd(nextPosition, velocity);
	}
	
	//停止時間を超えたら突進再開
	if (stopTime >= 0.5f)
	{
		++assaultCount;
		movedDistance = 0.0f;
		force = VGet(1.0f, 0.0f, 0.0f);
	}

	//3回突進したら次の行動に移る
	if (assaultCount >= 4.0f)
	{
		attackType = JUDGE;
	}

	stopTime += DeltaTime::GetInstace().GetDeltaTime();
	movedDistance += velocity.x;			//進んだ距離を加算
}


/// <summary>
/// 弾発射処理
/// </summary>
void Enemy::Bullet()
{
	shotInterval += DeltaTime::GetInstace().GetDeltaTime();

	if (shotInterval >= SHOT_INTERVAL)
	{
		CreateBullet();			//弾を生成
		ShootBullet();			//弾を発射
		shotInterval = 0.0f;	//インターバルをリセット
		shotCount++;			//発射回数を増加
	}
	if (shotCount == 4)
	{
		attackType = JUDGE;		//判断処理に移る
	}
	
}

/// <summary>
/// 弾速の遅い弾を発射
/// </summary>
void Enemy::SlowBullet()
{
	shotInterval += DeltaTime::GetInstace().GetDeltaTime();
	
	//近ければ接近してくる
	if (EnemyAi::GetInstance().RangeWithPlayerNear())
	{
		attackType = ASSAULT;
	}
	else if (shotInterval >= SHOT_INTERVAL)
	{
		CreateBullet();			//弾を生成
		ShootBullet();			//弾を発射
		shotInterval = 0.0f;	//インターバルをリセット
		shotCount++;			//発射回数増加
		prevType = attackType;
		attackType = JUDGE;		//判断処理に移る
	}
}

/// <summary>
/// ジャンプ後プレイヤーに向かって突進
/// </summary>
void Enemy::Jump()
{
	jumpPower.y += GRAVITY;
	//一定高さまでジャンプしたら
	if (nextPosition.y >= JUMP_HEIGHT)
	{
		jumpPower = ZERO_VECTOR;
		frame++;
		//規定フレーム経過したら
		if (frame >= 60.0f)
		{
			attackType = KICK;			//次の状態に移行する
		}
	}
	//一定の高さになるまでフレームを加算しない
	else
	{
		frame = 0;
	}
	
	nextPosition = VAdd(nextPosition, jumpPower);			//移動
}

/// <summary>
/// プレイヤーに向かって突進
/// </summary>
void Enemy::Kick()
{
	VECTOR playerPosition;				//プレイヤーの位置

	playerPosition = EnemyAi::GetInstance().DeterminingLandingPoint();		//プレイヤーの位置を特定
	jumpPower = VNorm(playerPosition - nextPosition) * KICK_SPEED;			//プレイヤーの位置へのベクトルを設定
	

	if (nextPosition.y <= 0.0f)
	{
		nextPosition.y = 0.0f;
		attackType = JUDGE;				//地面と接触したら次の状態に移行する
	}

	nextPosition = VAdd(nextPosition, jumpPower);			//移動
}

/// <summary>
/// 初期位置に戻る
/// </summary>
void Enemy::Back()
{
	float rightPos = SCREEN_RIGHTMOST - 1.0f;
	float leftPos = SCREEN_LEFTMOST + 1.0f;

	returnForce.y -= GRAVITY;

	//画面端まで移動
	if (nextPosition.x >= SCREEN_LEFTMOST && nextPosition.x <= SCREEN_RIGHTMOST)
	{
	}
	else
	{
		//飛んできた位置が右寄りかどうかで補正位置を選択
		if (!currentRightPosition)
		{
			nextPosition.x = rightPos;
		}
		else
		{
			nextPosition.x = leftPos;
		}
		returnForce.x = 0.0f;								//横移動を停止させる
	}

	nextPosition = VAdd(nextPosition, returnForce);			//画面端まで移動
	//collisionSphere.Move(position);

	//地面に着地したら落下を止める
	if (nextPosition.y < 0.0f)
	{
		SetNextAttack();
	}
}

/// <summary>
/// 接触後の反動
/// </summary>
void Enemy::Slide()
{
	//滑らせる
	if (velocity.x <= 0.0f)
	{
		velocity.x += FRICTION_FORCE;
	}
	else
	{
		velocity.x -= FRICTION_FORCE;
	}

	//止まったら画面端状態に戻る
	if (VSquareSize(velocity) <= STOP_VELOCITY)
	{
		velocity = ZERO_VECTOR;
		state = NORMAL;
		attackType = JUDGE;
		pUpdate = &Enemy::UpdateAttack;
	}

	//画面端なら必要以上進まないようにする
	if (SCREEN_LEFTMOST + 10 <= nextPosition.x && SCREEN_RIGHTMOST - 10 >= nextPosition.x)
	{
		nextPosition = VAdd(nextPosition, velocity);
	}
}

/// <summary>
/// 弾を生成
/// </summary>
void Enemy::CreateBullet()
{
	if (bulletCreater->IsCreatableCheck() == true)
	{
		bullet = bulletCreater->Create(position, direction);		//弾を生成
	}
}

/// <summary>
/// 弾を発射
/// </summary>
void Enemy::ShootBullet()
{
	//弾を保持していないなら処理しない
	if (bullet == nullptr)
	{
		return;
	}

	bullet->Shoot(static_cast<int>(attackType));
	//attackType = JUDGE;	

	//規定回数攻撃したら次の行動に移る
	//bullet = nullptr;
}

/// <summary>
/// 次の行動を決定する
/// </summary>
void Enemy::SetNextAttack()
{
	//乱数用変数
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<int> next(0, ATTACK_AMOUST - 2);
	int nextAttack;
	AttackType at;

	velocity = ZERO_VECTOR;
	assaultCount = 0;			//突進回数をリセット
	returnForce = ZERO_VECTOR;
	position.y = 0.0f;
	nextPosition.y = 0.0f;


	//次の状態を指定（テスト用）
	/*attackType = BULLET;
	return;*/

	//前回の行動がSLOW_BULLETかつ規定数撃っていない場合
	if (prevType == SLOW_BULLET && shotCount <= 3.0f)
	{
		attackType = SLOW_BULLET;
	}
	else
	{
		shotCount = 0;				//発射回数をリセット
		
		nextAttack = next(eng);							//次の行動を指定
		at = static_cast<AttackType>(nextAttack);		//列挙型に変換する
		if (prevType == at || prevType == SLOW_BULLET)
		{
			nextAttack = next(eng);
			at = static_cast<AttackType>(nextAttack);
		}
		
		attackType = at;		//次の状態に移行する
		
	}
}

/// <summary>
/// エネミーの現在位置を判断
/// </summary>
void Enemy::CurrentPositionJudge()
{
	returnForce = VGet(15.0f, 0.0f, 0.0f);
	returnForce.y = JUMP_DIRECTION_Y;
	jumpPower = ZERO_VECTOR;
	jumpPower.y = -JUMP_DIRECTION_Y;
	//jumpPower = VScale(jumpPower, 0.7f);

	//エネミーの現在地が右端寄りなら
	if (SCREEN_RIGHTMOST - position.x <= SCREEN_CENTER)
	{
		currentRightPosition = true;		//右端にいる状態に
		returnForce = VScale(returnForce, -0.7f);
		nextDirction = VGet(1.0f, 0.0f, 0.0f);
		//画面端に戻る
		attackType = BACK;

		//左端に近くなったら
		if (position.x - SCREEN_LEFTMOST <= 150.0f)
		{
			
		}
	}
	//エネミーの現在地が左寄りなら
	else
	{
		currentRightPosition = false;		//左端にいる状態に
		returnForce = VScale(returnForce, 0.7f);
		returnForce.y *= -1.0f;				//ジャンプするよう補正する
		nextDirction = VGet(-1.0f, 0.0f, 0.0f);
		//画面端に戻る
		attackType = BACK;

		//右端が近くなったら
		if (SCREEN_RIGHTMOST - position.x <= 150.0f)
		{
			
		}
	}
}


void Enemy::UpdateFine()
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)();			//各状態の更新処理
	}
}

void Enemy::UpdateCaution()
{

}

void Enemy::UpdateDenger()
{

}

void Enemy::UpdateNormal()
{
	stopTime += DeltaTime::GetInstace().GetDeltaTime();
	if (stopTime > 1.5f)
	{
		stopMove = false;
	}
	InputAction();
	Move();

}

void Enemy::UpdateAttack()
{
	if (attackType == ASSAULT ||
		attackType == BULLET ||
		attackType == SLOW_BULLET ||
		attackType == JUMP)
	{
		prevType = attackType;
	}

	//各行動パターンに応じた行動処理
	switch (attackType)
	{
	case ASSAULT:
		trunkMagnification = ASSAULT_MAGNIFICATION;
		Assault();
		break;
	case BULLET:
		trunkMagnification = BULLET_MAGNIFICATION;
		Bullet();
		break;
	case SLOW_BULLET:
		trunkMagnification = SLOW_BULLET_MAGNIFICATION;
		SlowBullet();
		break;
	case JUMP:
		trunkMagnification = JUMPKICK_MAGNIFICATION;
		Jump();
		break;
	case KICK:
		trunkMagnification = JUMPKICK_MAGNIFICATION;
		Kick();
		break;
	case JUDGE:
		CurrentPositionJudge();
		break;
	case BACK:
		Back();
		break;
	}
	
}

void Enemy::UpdateSlide()
{
	Slide();
}

void Enemy::UpdateDamage()
{

}

void Enemy::InputAction()
{
	inputDirection = ZERO_VECTOR;
	inputDirection += vec * speed;
	
	if ( position.x >= SCREEN_RIGHTMOST)
	{
		vec = LEFT;
	}
	else if(position.x <= SCREEN_LEFTMOST)
	{
		vec = RIGHT;
	}

	collisionSphere.Move(position);
}
