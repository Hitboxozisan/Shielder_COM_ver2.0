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
		printfDx("読み込みに失敗_LaserEffect");
	}
}

void PlayerLaserEffect::Finalize()
{
	//エフェクトを削除する
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

void PlayerLaserEffect::Update(VECTOR inPostion)
{
	//存在しないなら処理しない
	if (exist == false)
	{
		return;
	}

	frame++;

	if (frame <= 1)
	{
		
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);			//エフェクトを再生する
	}

	//エフェクトを再生し終わったら
	if (frame >= 60)
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
