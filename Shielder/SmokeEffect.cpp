#include "Pch.h"

#include "SmokeEffect.h"

const int SmokeEffect::DEFAULT_EXIST_FRAME = 60;
const float SmokeEffect::INCREASE_SIZE = 0.8f;


/// <summary>
/// コンストラクタ
/// </summary>
SmokeEffect::SmokeEffect()
{
}

/// <summary>
/// デストラクタ
/// </summary>
SmokeEffect::~SmokeEffect()
{
}

/// <summary>
/// 活性化処理
/// </summary>
/// <param name="creatorPosition"></param>
/// <param name="creatorSize"></param>
void SmokeEffect::Activate(const VECTOR& inPosition, float inSize)
{
	position = inPosition;
	position.y = 0.0f;			//地面から煙を出す

	size = inSize;

	exist = true;
	existFrame = DEFAULT_EXIST_FRAME;

	opacity = 0.6f;
}

/// <summary>
/// 描画処理
/// </summary>
void SmokeEffect::Draw(const VECTOR& inPosition)
{
	//存在しないなら処理しない
	if (exist == false)
	{
		return;
	}

	//プレイヤーの真下から出るようにする
	//position = inPosition;
	//position.y = 10.0f;

	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 255 - ((DEFAULT_EXIST_FRAME - existFrame) * 4));	//ブレンドモード

	DrawBillboard3D(position, 0.5f, 0.5f, size * 3.0f, 0.0f, *graphicPointer, TRUE);		//画像の描画

	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 255);	//ブレンドモード解除
}

/// <summary>
/// 更新処理
/// </summary>
void SmokeEffect::UpdateEach()
{
	//徐々に大きくする
	size += INCREASE_SIZE;
}
