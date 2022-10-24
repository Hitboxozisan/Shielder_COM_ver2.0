#include "Pch.h"

#include "SmokeEffect.h"

const int SmokeEffect::DEFAULT_EXIST_FRAME = 60;
const float SmokeEffect::INCREASE_SIZE = 0.8f;


/// <summary>
/// �R���X�g���N�^
/// </summary>
SmokeEffect::SmokeEffect()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SmokeEffect::~SmokeEffect()
{
}

/// <summary>
/// ����������
/// </summary>
/// <param name="creatorPosition"></param>
/// <param name="creatorSize"></param>
void SmokeEffect::Activate(const VECTOR& inPosition, float inSize)
{
	position = inPosition;
	position.y = 0.0f;			//�n�ʂ��牌���o��

	size = inSize;

	exist = true;
	existFrame = DEFAULT_EXIST_FRAME;

	opacity = 0.6f;
}

/// <summary>
/// �`�揈��
/// </summary>
void SmokeEffect::Draw(const VECTOR& inPosition)
{
	//���݂��Ȃ��Ȃ珈�����Ȃ�
	if (exist == false)
	{
		return;
	}

	//�v���C���[�̐^������o��悤�ɂ���
	//position = inPosition;
	//position.y = 10.0f;

	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 255 - ((DEFAULT_EXIST_FRAME - existFrame) * 4));	//�u�����h���[�h

	DrawBillboard3D(position, 0.5f, 0.5f, size * 3.0f, 0.0f, *graphicPointer, TRUE);		//�摜�̕`��

	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 255);	//�u�����h���[�h����
}

/// <summary>
/// �X�V����
/// </summary>
void SmokeEffect::UpdateEach()
{
	//���X�ɑ傫������
	size += INCREASE_SIZE;
}
