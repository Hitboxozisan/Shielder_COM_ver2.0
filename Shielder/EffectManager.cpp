#include "Pch.h"

#include "EffectBase.h"
#include "EffectManager.h"
#include "GuardEffect.h"


const std::string SPARK_EFFECT_PATH = "Data/Effect/Blow.efkefc";

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
}

void EffectManager::Initialize()
{
	/*GuardEffect* sparkEffect = new GuardEffect;
	sparkEffect->Initialize();*/

	effects = new EffectBase*[EFFECT_AMOUNT]();

	effects[0] = new GuardEffect();
	effects[0]->Initialize();
}

void EffectManager::Finalize()
{
	for (int i = 0; i < EFFECT_AMOUNT; ++i)
	{
		effects[i]->Finalize();
	}
}

void EffectManager::Activate(VECTOR inPosition)
{
	for (int i = 0; i < EFFECT_AMOUNT; ++i)
	{
		effects[i]->Activate(inPosition);
	}
}

void EffectManager::Deactivate()
{
	for (int i = 0; i < EFFECT_AMOUNT; ++i)
	{
		effects[i]->Deactivate();
	}
}

void EffectManager::Update()
{
	for (int i = 0; i < EFFECT_AMOUNT; ++i)
	{
		effects[i]->Update();
	}
}

void EffectManager::Draw()
{
	for (int i = 0; i < EFFECT_AMOUNT; ++i)
	{
		effects[i]->Draw();
	}
}

void EffectManager::CreateSparkEffect(const VECTOR& inPosition)
{
	if (effects[SPARK]->GetExist() == false)
	{
		effects[SPARK]->Activate(inPosition);
		return;
	}
}
