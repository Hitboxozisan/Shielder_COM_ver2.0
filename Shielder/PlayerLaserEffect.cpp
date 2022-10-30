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

void PlayerLaserEffect::Update(VECTOR inPostion, VECTOR inEnemyPosition)
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
		SetSpeedPlayingEffekseer3DEffect(playingEffectHandle, 0.2);			//エフェクトの再生速度を設定する
		SpecificEnemyPosition(inPostion, inEnemyPosition);									//発射角度を設定
		//SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0, 90, 0);
		
	}
	//一定時間経過後再生速度を戻す
	if (frame == 300)
	{
		SetSpeedPlayingEffekseer3DEffect(playingEffectHandle, 1.0);
		SetScalePlayingEffekseer3DEffect(playingEffectHandle, 3.0f, 3.0f, 3.0f);
	}

	//エフェクトを再生し終わったら
	if (frame >= 800)
	{
		//エフェクトを停止する
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

//エネミーの位置を特定
//レーザーを発射する位置を角度
void PlayerLaserEffect::SpecificEnemyPosition(VECTOR inPosition, VECTOR inEnemyPosition)
{
	inPosition.z = 0.0f;
	inEnemyPosition.z = 0.0f;

	//二つのベクトルの絶対値
	float absoluteValue1 = VSquareSize(inPosition);
	float absoluteValue2 = VSquareSize(inEnemyPosition);
	
	//内積の計算
	float innerProduct = VDot(inPosition, inEnemyPosition);

	absoluteValue1 = absoluteValue1 / 10000;
	absoluteValue2 = absoluteValue2 / 10000;
	float absoluteValue = absoluteValue1 * absoluteValue2;

	innerProduct = innerProduct / 10000;

	//打ち出す角度を計算
	float rad = static_cast<float>((innerProduct / absoluteValue));
	rad *= 10000;

	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0.0f, 0.0f, 0.0f);
	return;
}
