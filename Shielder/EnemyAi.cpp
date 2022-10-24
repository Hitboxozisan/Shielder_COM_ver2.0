#include "Pch.h"
#include "EnemyAi.h"
#include "Character.h"

const float EnemyAi::NEAR_DISTANCE = 300;

EnemyAi::EnemyAi()
{
}

EnemyAi::~EnemyAi()
{
}

EnemyAi& EnemyAi::GetInstance()
{
	static EnemyAi enemyAi;
	return enemyAi;
}

void EnemyAi::Initialize(Character** inCharacter)
{
	character = inCharacter;
}

/// <summary>
/// プレイヤーとの距離が近いか
/// </summary>
/// <returns></returns>
bool EnemyAi::RangeWithPlayerNear()
{
	//プレイヤーとエネミーの距離
	VECTOR sub;
	sub = character[0]->GetPosition() - character[1]->GetPosition();
	
	//プレイヤーとの距離が近ければ
	if (VSize(sub) <= NEAR_DISTANCE)
	{
		return true;
	}

	return false;
}

VECTOR EnemyAi::DeterminingLandingPoint()
{
	return character[0]->GetPosition();
}
