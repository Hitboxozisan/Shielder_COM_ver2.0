#pragma once

#include "EffectBase.h"
#include "BillboardBase.h"
#include <string>

class EffectManager final
{
public:
	enum Effects
	{
		SPARK,				//スパーク

		EFFECT_AMOUNT,		//エフェクトの総数
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

	//ベースクラスインスタンスの総量
	//enum と こちらか統一する必要あり
	static const int BILLBOARD_AMOUNT;

	EffectBase* effects[EFFECT_AMOUNT];
	BillboardBase** graphicEffects;

	int smokeGraphicHandle;
};

