#pragma once

#include "EffectBase.h"
#include "BillboardBase.h"
#include <string>

class EffectManager final
{
public:
	enum Effects
	{
		SPARK,				//�X�p�[�N

		EFFECT_AMOUNT,		//�G�t�F�N�g�̑���
	};

	EffectManager();
	~EffectManager();

	void Initialize();
	void Finalize();
	void Activate(VECTOR inPosition);
	void Deactivate();
	void Update();
	void Draw();

	void CreateSparkEffect(const VECTOR& inPosition);

private:
	EffectManager(const EffectManager&);
	void operator=(const EffectManager&);

	static const std::string SPARK_EFFECT_PATH;
	static const std::string RIGOR_EFFECT_GRAPHIC_PATH;

	static const int SMOKE_EFFECT_AMOUNT;

	//�x�[�X�N���X�C���X�^���X�̑���
	//enum �� �����炩���ꂷ��K�v����
	static const int BILLBOARD_AMOUNT;

	EffectBase* effects[EFFECT_AMOUNT];
	BillboardBase** graphicEffects;

	int smokeGraphicHandle;
};

