#include "Pch.h"
#include "PlayerDiedEffect.h"

PlayerDiedEffect::PlayerDiedEffect()
{
}

PlayerDiedEffect::~PlayerDiedEffect()
{
}

void PlayerDiedEffect::Initialize()
{
	//�G�t�F�N�g�̓ǂݍ���
	effectHandle = LoadEffekseerEffect("Data/Effect/playerDied.efkefc", 15.0f);
	if (effectHandle == -1)
	{
		printfDx("�ǂݍ��݂Ɏ��s_playerDiedEffect");
	}
}

void PlayerDiedEffect::Finalize()
{
	//�G�t�F�N�g���폜����
	DeleteEffekseerEffect(effectHandle);
}

void PlayerDiedEffect::Activate(VECTOR inPosition)
{
	exist = true;
	frame = 0;
	position = inPosition;
	//position = VGet(320.0f, 300.0f, 100.0f);
	position.y = 50.0f;
	position.z = 0.0f;
	playingEffectHandle = -1;
}

void PlayerDiedEffect::Deactivate()
{
	exist = false;
}

void PlayerDiedEffect::Update()
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



	//�G�t�F�N�g���Đ����I�������
	if (frame >= 60)
	{
		Deactivate();
	}

	SetPosPlayingEffekseer3DEffect(playingEffectHandle, position.x, position.y, position.z);
}

void PlayerDiedEffect::Draw()
{
	if (exist == false)
	{
		return;
	}

	UpdateEffekseer3D();
	DrawEffekseer3D();
}
