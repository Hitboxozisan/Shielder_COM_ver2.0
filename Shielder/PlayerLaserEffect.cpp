#include "Pch.h"

#include "PlayerLaserEffect.h"

using namespace My3dLib;

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

}

void PlayerLaserEffect::Deactivate()
{
	exist = false;
}

void PlayerLaserEffect::Update(VECTOR inPostion, VECTOR inEnemyPosition)
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
		SpecificEnemyPosition(inPostion, inEnemyPosition);									//���ˊp�x��ݒ�
		//SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0, 90, 0);
		
	}
	//��莞�Ԍo�ߌ�Đ����x��߂�
	if (frame == 300)
	{
		SetSpeedPlayingEffekseer3DEffect(playingEffectHandle, 1.0);
		SetScalePlayingEffekseer3DEffect(playingEffectHandle, 3.0f, 3.0f, 3.0f);
	}

	//�G�t�F�N�g���Đ����I�������
	if (frame >= 800)
	{
		//�G�t�F�N�g���~����
		StopEffekseer3DEffect(playingEffectHandle);
		//Deactivate();
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
void PlayerLaserEffect::SpecificEnemyPosition(VECTOR inPosition, VECTOR inEnemyPosition)
{
	inPosition.z = 0.0f;
	inEnemyPosition.z = 0.0f;

	//��̃x�N�g���̐�Βl
	float absoluteValue1 = VSquareSize(inPosition);
	float absoluteValue2 = VSquareSize(inEnemyPosition);
	
	//���ς̌v�Z
	float innerProduct = VDot(inPosition, inEnemyPosition);

	absoluteValue1 = absoluteValue1 / 10000;
	absoluteValue2 = absoluteValue2 / 10000;
	float absoluteValue = absoluteValue1 * absoluteValue2;

	innerProduct = innerProduct / 10000;

	//�ł��o���p�x���v�Z
	float rad = static_cast<float>((innerProduct / absoluteValue));
	rad *= 10000;

	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0.0f, 0.0f, 0.0f);
	return;
}
