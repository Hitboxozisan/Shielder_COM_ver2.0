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
/// �v���C���[�Ƃ̋������߂���
/// </summary>
/// <returns></returns>
bool EnemyAi::RangeWithPlayerNear()
{
	//�v���C���[�ƃG�l�~�[�̋���
	VECTOR sub;
	sub = character[0]->GetPosition() - character[1]->GetPosition();
	
	//�v���C���[�Ƃ̋������߂����
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
