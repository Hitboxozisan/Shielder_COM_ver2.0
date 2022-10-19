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
		printfDx("読み込みに失敗_GuardEffect");
	}
}

void GuardEffect::Activate(VECTOR inPosition)
{
	position = inPosition;
	SetPosPlayingEffekseer3DEffect(effectHandle, position.x, position.y, position.z);
}

void GuardEffect::Deactivate()
{
	//エフェクトを削除する
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
