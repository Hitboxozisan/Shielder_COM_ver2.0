#include "Pch.h"
#include <chrono>
#include <thread>
#include <random>
#include "Enemy.h"

#include "Bullet.h"
#include "BulletCreater.h"

#include "ModelManager.h"
#include "DeltaTime.h"

const float Enemy::COLLIDE_RADIUS = 50.0f;
const float Enemy::NORMAL_SPEED = 3.0f;
const float Enemy::DEFENSE_SPEED = 2.0f;
const float Enemy::KICK_SPEED = 7.0f;							
const float Enemy::JUMP_DIRECTION_Y = -30.0f;
const float Enemy::STOP_VELOCITY = 0.5f;
const float Enemy::FRICTION_FORCE = 0.05f;
const float Enemy::GRAVITY = 0.25f;
const float Enemy::TRUNK_POINT = 100.0f;
const float Enemy::INCREASE_TRUNK_POINT = 5.0f;
const float Enemy::ASSAULT_MAGNIFICATION = 1.0f;
const float Enemy::BULLET_MAGNIFICATION = 1.2;	
const float Enemy::SLOW_BULLET_MAGNIFICATION = 0.3;
const float Enemy::JUMPKICK_MAGNIFICATION = 0.5f;
const float Enemy::SHOT_INTERVAL = 1.0f;

Enemy::Enemy(BulletCreater* const inBulletCreater)
	:Character(inBulletCreater)
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

void Enemy::Initialize()
{
	vec = LEFT;
	speed = NORMAL_SPEED;
	trunkPoint = TRUNK_POINT;
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
	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�̓ǂݍ���_Enemy\n");
	}

	MV1SetScale(modelHandle, VGet(0.5f, 0.5f, 0.5f));

	//�����蔻�苅��ݒ�
	collisionSphere.localCenter = VGet(0.0f, 0.0f, 0.0f);
	collisionSphere.radius = COLLIDE_RADIUS;
	collisionSphere.worldCenter = position;
}

void Enemy::Update()
{
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

	//�̊��Q�[�W��0�ɂȂ����玀�S����
	if (trunkPoint <= 0.0f)
	{
		WaitTimer(0);
		//�G�t�F�N�g�Đ�

		state = DEAD;
	}
	
}

void Enemy::Draw()
{
	MV1DrawModel(modelHandle);

	//UI
	DrawFormatString(300, 130, GetColor(255, 255, 255), "E : %f", this->GetTrunk(), TRUE);		//�̊��Q�[�W�\��
	DrawFormatString(300, 170, GetColor(255, 255, 255), "MD : %f", movedDistance, TRUE);
	DrawFormatString(300, 190, GetColor(255, 255, 255), "Interval : %f", GetInterval(), TRUE);
	DrawFormatString(300, 210, GetColor(255, 255, 255), "AT : %d", attackType);
	DrawFormatString(300, 230, GetColor(255, 255, 255), "ShotCount : %d", shotCount);

	//�����蔻��f�o�b�N�`��
	DrawSphere3D(collisionSphere.worldCenter, collisionSphere.radius,
		8, GetColor(0, 255, 0), 0, FALSE);
	
}

void Enemy::OnHitOtherCharacter(const VECTOR& forceDirection)
{
	stopTime = 0.0f;
	//�ړ����~�߂�
	stopMove = true;
}

void Enemy::OnHitShield(const VECTOR& adjust)
{
	//�O���velocity�����Z�b�g����
	velocity = ZERO_VECTOR;
	stopTime = 0.0f;
	stopMove = true;

	VECTOR force = adjust;
	force.y = 0.0f;			//�ςȕ����ɓ����Ȃ��悤�ɂ���
	force.z = 0.0f;			//�ςȕ����ɓ����Ȃ��悤�ɂ���

	force = VScale(force, -3.0f);

	//��ނ�����
	velocity = VAdd(velocity, force);
	
	trunkPoint -= INCREASE_TRUNK_POINT * trunkMagnification;		//�̊��Q�[�W����
	state = SLIDE;
	pUpdate = &Enemy::UpdateSlide;
	
	//bullet = nullptr;
}

/// <summary>
/// ���ƒe���ڐG����
/// </summary>
/// <param name="adjust"></param>
void Enemy::OnHitShieldWithBullet(const VECTOR& adjust)
{
	trunkPoint -= INCREASE_TRUNK_POINT * trunkMagnification;		//�̊��Q�[�W����
}

const bool Enemy::IsAlive() const
{
	//���݂��Ȃ��Ȃ玀��ł����Ԃɂ���
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

	//�ʒu��ݒ�
	MV1SetPosition(modelHandle, position);

	//�ړ��L�[�������Ă��Ȃ��ꍇ�͌������Œ肷��
	if (!VSquareSize(inputDirection) == 0.0f)
	{
		MV1SetRotationYUseDir(modelHandle, direction, 0.0f);
	}

}

/// <summary>
/// �ːi�U��
/// </summary>
void Enemy::Assault()
{
	
	VECTOR force = VGet(1.0f, 0.0f, 0.0f);			//�ړ��ʂ�ݒ�
	force.y = 0.0f;			//�ςȕ����ɓ����Ȃ��悤�ɂ���
	force.z = 0.0f;			//�ςȕ����ɓ����Ȃ��悤�ɂ���

	//�G�l�~�[�̌��ݒn���E�[���Ȃ�
	if (currentRightPosition)
	{
		force = VScale(force, 0.5f);		//�����ɗ͂�^����
	}
	else
	{
		force = VScale(force, -0.5f);		//�E���ɗ͂�^����
	}
	
	//�ːi������
	if (movedDistance <= 300.0f && movedDistance >= -300.0f)
	{
		stopTime = 0.0f;
		velocity = VAdd(velocity, force);
		nextPosition = VAdd(nextPosition, velocity);
	}
	
	//��~���Ԃ𒴂�����ːi�ĊJ
	if (stopTime >= 0.5f)
	{
		++assaultCount;
		movedDistance = 0.0f;
		force = VGet(1.0f, 0.0f, 0.0f);
	}

	//3��ːi�����玟�̍s���Ɉڂ�
	if (assaultCount >= 3.0f)
	{
		attackType = JUDGE;
	}

	stopTime += DeltaTime::GetInstace().GetDeltaTime();
	movedDistance += velocity.x;			//�i�񂾋��������Z
}


/// <summary>
/// �e���ˏ���
/// </summary>
void Enemy::Bullet()
{
	shotInterval += DeltaTime::GetInstace().GetDeltaTime();
	if (shotInterval >= SHOT_INTERVAL)
	{
		CreateBullet();			//�e�𐶐�
		ShootBullet();			//�e�𔭎�
		shotInterval = 0.0f;	//�C���^�[�o�������Z�b�g
		shotCount++;			//���ˉ񐔂𑝉�
	}
	if (shotCount == 4)
	{
		attackType = JUDGE;		//���f�����Ɉڂ�
	}
	
}

/// <summary>
/// �e���̒x���e�𔭎�
/// </summary>
void Enemy::SlowBullet()
{
	shotInterval += DeltaTime::GetInstace().GetDeltaTime();
	if (shotInterval >= SHOT_INTERVAL)
	{
		CreateBullet();			//�e�𐶐�
		ShootBullet();			//�e�𔭎�
		shotInterval = 0.0f;	//�C���^�[�o�������Z�b�g
		shotCount++;			//���ˉ񐔑���
		prevType = attackType;
		attackType = JUDGE;		//���f�����Ɉڂ�
	}
}

/// <summary>
/// �W�����v��v���C���[�Ɍ������ēːi
/// </summary>
void Enemy::JumpKick()
{
	bool isKick;

	//��荂���܂ŃW�����v������
	if (nextPosition.y <= 200.0f)
	{
		//���Α��܂ŃL�b�N����


	}
	if (nextPosition.y <= 0.0f)
	{
		attackType = JUDGE;
	}
}

/// <summary>
/// �����ʒu�ɖ߂�
/// </summary>
void Enemy::Back()
{
	
	float rightPos = SCREEN_RIGHTMOST - 1.0f;
	float leftPos = SCREEN_LEFTMOST + 1.0f;

	returnForce.y -= GRAVITY;

	//��ʒ[�܂ňړ�
	if (nextPosition.x >= SCREEN_LEFTMOST && nextPosition.x <= SCREEN_RIGHTMOST)
	{
	}
	else
	{
		//���ł����ʒu���E��肩�ǂ����ŕ␳�ʒu��I��
		if (!currentRightPosition)
		{
			nextPosition.x = rightPos;
		}
		else
		{
			nextPosition.x = leftPos;
		}
		returnForce.x = 0.0f;								//���ړ����~������
	}

	nextPosition = VAdd(nextPosition, returnForce);			//��ʒ[�܂ňړ�
	//collisionSphere.Move(position);

	//�n�ʂɒ��n�����痎�����~�߂�
	if (nextPosition.y < 0.0f)
	{
		SetNextAttack();
	}
}

/// <summary>
/// �ڐG��̔���
/// </summary>
void Enemy::Slide()
{
	//���点��
	if (velocity.x <= 0.0f)
	{
		velocity.x += FRICTION_FORCE;
	}
	else
	{
		velocity.x -= FRICTION_FORCE;
	}

	//�~�܂������ʒ[��Ԃɖ߂�
	if (VSquareSize(velocity) <= STOP_VELOCITY)
	{
		velocity = ZERO_VECTOR;
		state = NORMAL;
		attackType = JUDGE;
		pUpdate = &Enemy::UpdateAttack;
	}

	nextPosition = VAdd(nextPosition, velocity);
}

/// <summary>
/// �e�𐶐�
/// </summary>
void Enemy::CreateBullet()
{
	if (bulletCreater->IsCreatableCheck() == true)
	{
		bullet = bulletCreater->Create(position, direction);		//�e�𐶐�
	}
}

/// <summary>
/// �e�𔭎�
/// </summary>
void Enemy::ShootBullet()
{
	//�e��ێ����Ă��Ȃ��Ȃ珈�����Ȃ�
	if (bullet == nullptr)
	{
		return;
	}

	bullet->Shoot(static_cast<int>(attackType));
	//attackType = JUDGE;	

	//�K��񐔍U�������玟�̍s���Ɉڂ�
	//bullet = nullptr;
}

/// <summary>
/// ���̍s�������肷��
/// </summary>
void Enemy::SetNextAttack()
{
	//�����p�ϐ�
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<int> next(0, ATTACK_AMOUST - 1);

	velocity = ZERO_VECTOR;
	assaultCount = 0;			//�ːi�񐔂����Z�b�g
	returnForce = ZERO_VECTOR;
	position.y = 0.0f;
	nextPosition.y = 0.0f;

	if (prevType == SLOW_BULLET && shotCount <= 2.0f)
	{
		attackType = SLOW_BULLET;
	}
	else
	{
		shotCount = 0;				//���ˉ񐔂����Z�b�g
		int nextAttack = next(eng);	//���̍s�����w��
		AttackType at = static_cast<AttackType>(nextAttack);	//�񋓌^�ɕϊ�����
		if (prevType == at)
		{
			nextAttack = next(eng);
			at = static_cast<AttackType>(nextAttack);
		}

		//���̍s�����W�����v�R�肾�����ꍇ������ɗ͂������Ă���
		if (at == JUMPKICK)
		{
			returnForce.y = JUMP_DIRECTION_Y;
		}

		attackType = at;		//���̏�ԂɈڍs����
	}
}

/// <summary>
/// �G�l�~�[�̌��݈ʒu�𔻒f
/// </summary>
void Enemy::CurrentPositionJudge()
{
	float sub;
	returnForce = VGet(13.0f, 0.0f, 0.0f);
	returnForce.y = JUMP_DIRECTION_Y;

	//�G�l�~�[�̌��ݒn���E�[���Ȃ�
	if (SCREEN_RIGHTMOST - position.x <= SCREEN_CENTER)
	{
		currentRightPosition = true;		//�E�[�ɂ����Ԃ�
		returnForce = VScale(returnForce, -0.7f);
		nextDirction = VGet(1.0f, 0.0f, 0.0f);
		//��ʒ[�ɖ߂�
		attackType = BACK;

		//���[�ɋ߂��Ȃ�����
		if (position.x - SCREEN_LEFTMOST <= 150.0f)
		{
			
		}
	}
	//�G�l�~�[�̌��ݒn�������Ȃ�
	else
	{
		currentRightPosition = false;		//���[�ɂ����Ԃ�
		returnForce = VScale(returnForce, 0.7f);
		returnForce.y *= -1.0f;				//�W�����v����悤�␳����
		nextDirction = VGet(-1.0f, 0.0f, 0.0f);
		//��ʒ[�ɖ߂�
		attackType = BACK;
		

		//�E�[���߂��Ȃ�����
		if (SCREEN_RIGHTMOST - position.x <= 150.0f)
		{
			
		}
	}
}


void Enemy::UpdateFine()
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)();			//�e��Ԃ̍X�V����
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
	//�e�s���p�^�[���ɉ������s������
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
	case JUMPKICK:
		trunkMagnification = JUMPKICK_MAGNIFICATION;
		JumpKick();
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