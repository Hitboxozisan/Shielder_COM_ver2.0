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
		printfDx("読み込みに失敗_RecoveryEffect");
	}
}

void RecoveryEffect::Finalize()
{
	//エフェクトを削除する
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

	position = inPosition;				//エフェクト再生位置をプレイヤーの位置に
	position.y = 50.0f;					//再生位置を補正

	//エフェクトを再生し終わったら
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
