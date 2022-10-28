#include "Pch.h"

#include "Bullet.h"

#include "ModelManager.h"

const float Bullet::NORMAL_SPEED = 13.0f;
const float Bullet::SLOW_SPEED = 5.0f;
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
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s_Bullet\n");
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

	SetToFrontOfEnemy(inPosition, inDirection);		//�G�l�~�[�̑O���Ɉʒu����

	MV1SetScale(modelHandle, VGet(0.5f, 0.5f, 0.2f));	//���f���g��k��
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, 1.5f, 0.0f));
}

void Bullet::Deactivate()
{
	state = NONE;
}

bool Bullet::Update()
{
	//���݂��Ȃ��Ȃ珈�����Ȃ�
	if (state == NONE)
	{
		return false;
	}

	//�G�l�~�[�U�����ʏ틅�Ȃ�
	if (state == NORMAL)
	{
		speed = NORMAL_SPEED;
	}
	else
	{
		speed = SLOW_SPEED;
	}

	//�e�X�g�pdirection
	//direction = VGet(0.5f, 0.0f, 0.0f);

	//���ł���Ƃ��̏���
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
	//���݂��Ȃ��Ȃ�`�悵�Ȃ�
	if (state == NONE)
	{
		return;
	}

	MV1SetPosition(modelHandle, position);		//3D���f���̃|�W�V�����ݒ�
	

	MV1DrawModel(modelHandle);	//3D���f���̕`��

	//�����蔻��f�o�b�N�`��
	DrawSphere3D(collisionSphere.worldCenter, collisionSphere.radius,
		8, GetColor(0, 255, 0), 0, FALSE);
}

void Bullet::Shoot(int attackType)
{
	//�G�l�~�[�U�����ʏ�e�Ȃ�
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

	//�G�l�~�[�̑O���Ɉʒu����
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
	Deactivate();
}

void Bullet::OnHitBreak()
{
	state = NONE;
}

void Bullet::Move()
{
	//��ʊO�ɏo������ł�����
	if (position.x <= SCREEN_LEFTMOST || position.x >= SCREEN_RIGHTMOST)
	{
		OnOutField();
	}
	position = VAdd(position, VScale(direction, speed));	//�����Ă�������Ɉړ�
	collisionSphere.Move(position);				//�����蔻�苅�ړ�
}
