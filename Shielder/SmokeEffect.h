#pragma once

#include "BillboardBase.h"

class SmokeEffect final : public BillboardBase
{
public:
	SmokeEffect();
	~SmokeEffect();

	void Activate(const VECTOR& inPosition, float inSize);
	void Draw(const VECTOR& inPosition);

	void UpdateEach();
private:
	static const int DEFAULT_EXIST_FRAME;			//���݂ł��鏉���t���[����
	static const float INCREASE_SIZE;				//1�t���[���ő�������T�C�Y

	float size;			//�摜�̑傫��

	float opacity;			//�s�����x
};

