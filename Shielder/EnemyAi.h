#pragma once

class Character;

class EnemyAi
{
public:
	EnemyAi();
	~EnemyAi();

	static EnemyAi& GetInstance();

	void Initialize(Character** inCharacter);

	bool RangeWithPlayerNear();			//�v���C���[�Ƃ̋������߂���
	VECTOR DeterminingLandingPoint();	//�v���C���[�̈ʒu��Ԃ�

private:
	static const float NEAR_DISTANCE;		//�߂��Ɣ��f���鋗��

	Character** character;
};

