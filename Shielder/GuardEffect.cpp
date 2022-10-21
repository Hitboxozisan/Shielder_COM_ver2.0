#include "Pch.h"
#include "GuardEffect.h"

GuardEffect::GuardEffect()
{
}

GuardEffect::~GuardEffect()
{
}

void GuardEffect::Initialize()
{
	effectHandle = LoadEffekseerEffect("Data/Effect/Blow.efkefc", 20.0f);
	if (effectHandle == -1)
	{
		printfDx("�ǂݍ��݂Ɏ��s_GuardEffect");
	}
	
}

void GuardEffect::Finalize()
{
	//�G�t�F�N�g���폜����
	DeleteEffekseerEffect(effectHandle);
}

void GuardEffect::Activate(VECTOR inPosition)
{
	exist = true;
	frame = 0;
	position = inPosition;
	//position = VGet(320.0f, 300.0f, 100.0f);
	position.y = 0.0f;
	position.z = 0.0f;
	playingEffectHandle = -1;
}

void GuardEffect::Deactivate()
{
	exist = false;
}

void GuardEffect::Update()
{
	if (exist == false)
	{
		return;
	}

	frame++;
	if (static_cast<int>(frame) % 60 == 0)
	{
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);
	}
	//�G�t�F�N�g���Đ����I�������
	if (frame >= 240)
	{
		Deactivate();
	}

	SetPosPlayingEffekseer3DEffect(playingEffectHandle, position.x, position.y, position.z);
}


void GuardEffect::Draw()
{
	if (exist == false)
	{
		return;
	}

	UpdateEffekseer3D();
	DrawEffekseer3D();
}
	