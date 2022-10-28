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
		DAMAGE,				//�_���[�W
		PLAYER_DEAD,		//���S
		RECOVERY,

		EFFECT_AMOUNT,		//�G�t�F�N�g�̑���
	};

	EffectManager();
	~EffectManager();

	void Initialize();
	void Finalize();
	void Activate(VECTOR inPosition);
	void Deactivate();
	void Update(VECTOR inPostion);
	void Draw(const VECTOR& inPosition);

	void CreateSparkEffect(const VECTOR& inPosition);		//�ΉԂ𐶐�����
	void CreateSmokeEffect(const VECTOR& inPosition);		//���𐶐�����
	void CreateDamageEffect(const VECTOR& inPosition);		//�_���[�W�G�t�F�N�g�𐶐�����
	void CreatePlayerDiedEffect(const VECTOR& inPosition);	//�v���C���[���S�G�t�F�N�g�𐶐�����
	void CreateRecoveryEffect(const VECTOR& inPosition);	//�v���C���[�񕜃G�t�F�N�g�𐶐�����

private:
	EffectManager(const EffectManager&);
	void operator=(const EffectManager&);

	static const std::string SPARK_EFFECT_PATH;
	static const std::string DAMAGE_EFFECT_PATH;
	static const std::string RIGOR_EFFECT_GRAPHIC_PATH;

	static const int SMOKE_EFFECT_AMOUNT;

	//�x�[�X�N���X�C���X�^���X�̑���
	//enum �� �����炩���ꂷ��K�v����
	static const int BILLBOARD_AMOUNT;

	EffectBase* effects[EFFECT_AMOUNT];
	BillboardBase** graphicEffects;

	int smokeGraphicHandle;
};

