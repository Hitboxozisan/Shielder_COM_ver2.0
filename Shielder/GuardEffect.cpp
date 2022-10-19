#include "Pch.h"
#include "EffekseerForDXLib.h"
#include "GuardEffect.h"

GuardEffect::GuardEffect()
	:effectHandle()
	,position()
	,playEffectHandle()
{
}

GuardEffect::~GuardEffect()
{
}

void GuardEffect::Initialize()
{
	effectHandle = LoadEffekseerEffect("Data/Effect/Laser01.efkefc", 1.0f);
	if (effectHandle == -1)
	{
		printfDx("�ǂݍ��݂Ɏ��s_GuardEffect");
	}
}

void GuardEffect::Activate(VECTOR inPosition)
{
	position = inPosition;
	SetPosPlayingEffekseer3DEffect(effectHandle, position.x, position.y, position.z);
}

void GuardEffect::Deactivate()
{
	//�G�t�F�N�g���폜����
	DeleteEffekseerEffect(effectHandle);
}

void GuardEffect::Update()
{
	playEffectHandle = PlayEffekseer3DEffect(effectHandle);
	//UpdateEffekseer3D();
}


void GuardEffect::Draw()
{
	DrawEffekseer3D();
}
