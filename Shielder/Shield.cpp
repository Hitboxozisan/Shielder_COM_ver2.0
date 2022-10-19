#include "Pch.h"
#include "Player.h"
#include "Enemy.h"
#include "Shield.h"

#include "ModelManager.h"
#include "DeltaTime.h"

using namespace ShieldState;

const float Shield::SCALE_BY_DIRECTION_FOR_CORRECTION = 80.0f;
const float Shield::COLLISION_SHIELD_RADIUS = 20.0f;
const float Shield::COLLISION_SHIELD_HEIGHT = 120.0f;

Shield& Shield::GetInstance()
{
	static Shield shield;
	return shield;
}


Shield::Shield()
	: state(NONE)
	,modelHandle()
	,position()
	,direction()
	,DistanceToPlyaer()
{
}

Shield::~Shield()
{
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

void Shield::Create()
{

}

void Shield::Activate(const VECTOR& inPosition, const VECTOR& inDirection, const VECTOR& inPrevDirection)
{
	state = DEPLOYMENT;
	position = inPosition;				//���̈ʒu��ݒ�
	direction = inDirection;			
	prevDirection = inPrevDirection;
	
	//�v���C���[�̑O���ɐݒu
	if (VSquareSize(direction) != 0.0f)
	{
		DistanceToPlyaer = VScale(direction, SCALE_BY_DIRECTION_FOR_CORRECTION);
	}
	else 
	{
		//DistanceToPlyaer = VScale(prevDirection, SCALE_BY_DIRECTION_FOR_CORRECTION);
	}

	position = VAdd(position, DistanceToPlyaer);
}

void Shield::Deactivate()
{
	state = NONE;
}

void Shield::Initialize(const VECTOR& inPrevDirection)
{
	defenseCount = 0.0f;

	//���f���ǂݍ���
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::SHIELD));
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�̓ǂݍ��݂Ɏ��s_Shield\n");
	}

	MV1SetScale(modelHandle, VGet(0.5f, 0.5f, 0.5f));

	
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.radius = COLLISION_SHIELD_RADIUS;
	collisionSphere.worldCenter = position;
	collisionSphere.worldCenter.y = COLLISION_SHIELD_HEIGHT;
}


void Shield::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}


void Shield::Update()
{
	if (state == NONE)
	{
		return;
	}
	
	defenseCount += DeltaTime::GetInstace().GetDeltaTime();

	////�v���C���[�̑O���ɐݒu
	//VECTOR DistanceToPlyaer = VScale(direction, SCALE_BY_DIRECTION_FOR_CORRECTION);
	//position = VAdd(position, DistanceToPlyaer);

	MV1SetPosition(modelHandle, position);
	
	if (VSquareSize(direction) != 0.0f)
	{
		MV1SetRotationYUseDir(modelHandle, direction, 0.0f);
	}
	collisionSphere.Move(position);

	//�G�Ƃ̓����蔻��
	
}

void Shield::Draw()
{
	if (state == NONE)
	{
		return;
	}

	//���f���̕`��
	MV1DrawModel(modelHandle);

	//�����蔻��f�o�b�N�`��
	DrawSphere3D(collisionSphere.worldCenter, collisionSphere.radius,
		8, GetColor(0, 255, 0), 0, FALSE);
}

void Shield::OnHitOtherCharacter()
{
	//�ڐG���Ă��銎�ڐG���Ԃ����Ȃ�
	/*HitCheck_Sphere_Sphere(collisionSphere.worldCenter, collisionSphere.radius, 
		enemy->GetCollisionShere(), enemy->GetCollisionRadius());
	{
		printfDx("Hit");
	}*/
}
