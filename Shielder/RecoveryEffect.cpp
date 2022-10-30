#include "Pch.h"

#include "RecoveryEffect.h"

RecoveryEffect::RecoveryEffect()
{
}

RecoveryEffect::~RecoveryEffect()
{
}

void RecoveryEffect::Initialize()
{
	effectHandle = LoadEffekseerEffect("Data/Effect/recovery.efkefc", 15.0);
	if (effectHandle == -1)
	{
		printfDx("�ǂݍ��݂Ɏ��s_RecoveryEffect");
	}
}

void RecoveryEffect::Finalize()
{
	//�G�t�F�N�g���폜����
	DeleteEffekseerEffect(effectHandle);
}

void RecoveryEffect::Activate(VECTOR inPosition)
{
	exist = true;
	frame = 0;
	position = inPosition;
	//position = VGet(320.0f, 300.0f, 100.0f);
	position.y = 50.0f;
	position.z = 0.0f;
	playingEffectHandle = -1;
}

void RecoveryEffect::Deactivate()
{
	exist = false;
}

void RecoveryEffect::Update(VECTOR inPosition, VECTOR inEnemyPosition)
{
	//���݂��Ȃ��Ȃ珈�����Ȃ�
	if (exist == false)
	{
		return;
	}

	frame++;

	if (frame <= 1)
	{
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);			//�G�t�F�N�g���Đ�����
	}

	position = inPosition;				//�G�t�F�N�g�Đ��ʒu���v���C���[�̈ʒu��
	position.y = 50.0f;					//�Đ��ʒu��␳

	//�G�t�F�N�g���Đ����I�������
	if (frame >= 60)
	{
		Deactivate();
	}

	SetPosPlayingEffekseer3DEffect(playingEffectHandle, position.x, position.y, position.z);
}

void RecoveryEffect::Draw()
{
	if (exist == false)
	{
		return;
	}

	UpdateEffekseer3D();
	DrawEffekseer3D();
}
