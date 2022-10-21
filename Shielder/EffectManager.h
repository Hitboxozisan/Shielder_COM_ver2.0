#pragma once

#include "EffectBase.h"
#include <string>

class EffectManager final
{
public:
	enum Effects
	{
		SPARK,				//スパーク

		EFFECT_AMOUNT		//エフェクトの総数
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

	EffectBase* effects[EFFECT_AMOUNT];
};

