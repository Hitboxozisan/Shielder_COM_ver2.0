#include "Pch.h"

#include "PlayerLaserEffect.h"

PlayerLaserEffect::PlayerLaserEffect()
{
}

PlayerLaserEffect::~PlayerLaserEffect()
{
}

void PlayerLaserEffect::Initialize()
{
	effectHandle = LoadEffekseerEffect("Data/Effect/playerLaser.efkefc", 25.0f);
	SetSpeedPlayingEffekseer3DEffect(effectHandle, 0.1);
	if (effectHandle == -1)
	{
		printfDx("�ǂݍ��݂Ɏ��s_LaserEffect");
	}
}

void PlayerLaserEffect::Finalize()
{
	//�G�t�F�N�g���폜����
	DeleteEffekseerEffect(effectHandle);
}

void PlayerLaserEffect::Activate(VECTOR inPosition)
{
	exist = true;
	frame = 0;
	position = inPosition;
	//position = VGet(320.0f, 300.0f, 100.0f);
	position.y = 50.0f;
	position.z = 0.0f;
	playingEffectHandle = -1;

	SpecificEnemyPosition(inPosition);
}

void PlayerLaserEffect::Deactivate()
{
	exist = false;
}

void PlayerLaserEffect::Update(VECTOR inPostion)
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
		SetSpeedPlayingEffekseer3DEffect(playingEffectHandle, 0.2);			//�G�t�F�N�g�̍Đ����x��ݒ肷��
		//SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0, 90, 0);
		
	}
	//��莞�Ԍo�ߌ�Đ����x��߂�
	if (frame == 300)
	{
		SetSpeedPlayingEffekseer3DEffect(playingEffectHandle, 1.0);
		SetScalePlayingEffekseer3DEffect(playingEffectHandle, 3.0f, 3.0f, 3.0f);
	}

	//�G�t�F�N�g���Đ����I�������
	if (frame >= 1000)
	{
		Deactivate();
	}

	SetPosPlayingEffekseer3DEffect(playingEffectHandle, position.x, position.y, position.z);
}

void PlayerLaserEffect::Draw()
{
	if (exist == false)
	{
		return;
	}

	UpdateEffekseer3D();
	DrawEffekseer3D();
}

//�G�l�~�[�̈ʒu�����
//���[�U�[�𔭎˂���ʒu���p�x
void PlayerLaserEffect::SpecificEnemyPosition(VECTOR inPosition)
{
	return;
}
