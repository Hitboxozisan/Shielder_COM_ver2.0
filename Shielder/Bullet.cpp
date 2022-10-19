#include "Pch.h"

#include "Bullet.h"

#include "ModelManager.h"

const float Bullet::NORMAL_SPEED = 15.0f;
const float Bullet::SLOW_SPEED = 2.5f;
const float Bullet::SCALE_BY_DIRECTION_FOR_CORRECTION = 5.0f;
const float Bullet::COLLIDE_RADIUS = 50.0f;

Bullet::Bullet()
	:state(NONE)
	,velocity()
	,speed(0.0f)
{
}

Bullet::~Bullet()
{
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

void Bullet::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::BULLET));

	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗_Bullet\n");
	}
}

void Bullet::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

void Bullet::Activate(const VECTOR& inPosition, const VECTOR& inDirection)
{
	position = inPosition;
	direction = inDirection;
	velocity = ZERO_VECTOR;

	collisionSphere.localCenter = VGet(0.0f, 0.0f, 0.0f);
	collisionSphere.radius = COLLIDE_RADIUS;
	collisionSphere.worldCenter = position;

	state = NORMAL;

	SetToFrontOfEnemy(inPosition, inDirection);		//エネミーの前方に位置調整

	MV1SetScale(modelHandle, VGet(0.5f, 0.5f, 0.2f));	//モデル拡大縮小
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, 1.5f, 0.0f));
}

void Bullet::Deactivate()
{
	state = NONE;
}

bool Bullet::Update()
{
	//存在しないなら処理しない
	if (state == NONE)
	{
		return false;
	}

	//エネミー攻撃が通常球なら
	if (state == NORMAL)
	{
		speed = NORMAL_SPEED;
	}
	else
	{
		speed = SLOW_SPEED;
	}

	//テスト用direction
	//direction = VGet(0.5f, 0.0f, 0.0f);

	//飛んでいるときの処理
	if (state == NORMAL ||
		state == SLOW)
	{
		Move();
		return true;
	}

	return true;
}

void Bullet::Draw()
{
	//存在しないなら描画しない
	if (state == NONE)
	{
		return;
	}

	MV1SetPosition(modelHandle, position);		//3Dモデルのポジション設定
	

	MV1DrawModel(modelHandle);	//3Dモデルの描画

	//当たり判定デバック描画
	DrawSphere3D(collisionSphere.worldCenter, collisionSphere.radius,
		8, GetColor(0, 255, 0), 0, FALSE);
}

void Bullet::Shoot(int attackType)
{
	//エネミー攻撃が通常弾なら
	if (attackType == 1)		
	{
		state = NORMAL;
	}
	else if(attackType == 2)
	{
		state = SLOW;
	}
	
}

void Bullet::SetToFrontOfEnemy(const VECTOR& inPosition, const VECTOR& inDirection)
{
	position = inPosition;
	direction = inDirection;

	//エネミーの前方に位置調整
	VECTOR distanceToPlayer = VScale(direction, SCALE_BY_DIRECTION_FOR_CORRECTION);

	position = VAdd(position, distanceToPlayer);
}

Bullet::State Bullet::GetState() const
{
	return state;
}

bool Bullet::IsCollidableState() const
{
	if (state == NORMAL ||
		state == SLOW)
	{
		return true;
	}

	return false;
}

void Bullet::OnOutField()
{
	state = NONE;
}

void Bullet::OnHitBreak()
{
	state = NONE;
}

void Bullet::Move()
{
	//画面外に出たら消滅させる
	if (position.x <= SCREEN_LEFTMOST || position.x >= SCREEN_RIGHTMOST)
	{
		OnOutField();
	}
	position = VAdd(position, VScale(direction, speed));	//向いている方向に移動
	collisionSphere.Move(position);				//当たり判定球移動
}
