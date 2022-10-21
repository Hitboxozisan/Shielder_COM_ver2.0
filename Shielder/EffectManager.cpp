#include "Pch.h"

//#include "EffectBase.h"
#include "EffectManager.h"
#include "GuardEffect.h"
#include "SmokeEffect.h"

const int EffectManager::SMOKE_EFFECT_AMOUNT = 32;

//ベースクラスインスタンスの総量
const int EffectManager::BILLBOARD_AMOUNT = SMOKE_EFFECT_AMOUNT;

const std::string EffectManager::SPARK_EFFECT_PATH = "Data/Effect/Blow.efkefc";
const std::string EffectManager::RIGOR_EFFECT_GRAPHIC_PATH = "Data/Effect/smoke.png";


EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
}

void EffectManager::Initialize()
{
	//画像読み込み
	smokeGraphicHandle = LoadGraph(RIGOR_EFFECT_GRAPHIC_PATH.c_str());

	effects[0] = new GuardEffect();
	effects[0]->Initialize();

	graphicEffects = new BillboardBase * [BILLBOARD_AMOUNT];

	int itr = 0;
	int length = 0;

	length += SMOKE_EFFECT_AMOUNT;
	for ( itr = 0 ; itr < length; ++itr)
	{
		graphicEffects[itr] = new SmokeEffect();
		graphicEffects[itr]->Initialize(&smokeGraphicHandle);
	}
}

void EffectManager::Finalize()
{
	for (int i = 0; i < EFFECT_AMOUNT; ++i)
	{
		effects[i]->Finalize();
		SafeDelete(effects[i]);
	}

	for (int i = 0; i < BILLBOARD_AMOUNT; ++i)
	{
		graphicEffects[i]->Finalize();
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

	for (int i = 0; i < BILLBOARD_AMOUNT; ++i)
	{
		graphicEffects[i]->Deactivate();
	}
}

void EffectManager::Update()
{
	for (int i = 0; i < EFFECT_AMOUNT; ++i)
	{
		effects[i]->Update();
	}

	for (int i = 0; i < BILLBOARD_AMOUNT; ++i)
	{
		graphicEffects[i]->Update();
	}
}

void EffectManager::Draw()
{
	int itr = 0;
	int length = 0;

	for (int i = 0; i < EFFECT_AMOUNT; ++i)
	{
		effects[i]->Draw();
	}

	itr = BILLBOARD_AMOUNT;
	for (; itr < length; ++itr)
	{
		graphicEffects[itr]->Draw();
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
