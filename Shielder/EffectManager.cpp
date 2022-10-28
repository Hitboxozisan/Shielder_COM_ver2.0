#include "Pch.h"

//#include "EffectBase.h"
#include "EffectManager.h"
#include "GuardEffect.h"
#include "DamageEffect.h"
#include "PlayerDiedEffect.h"
#include "SmokeEffect.h"
#include "RecoveryEffect.h"

const int EffectManager::SMOKE_EFFECT_AMOUNT = 32;

//ベースクラスインスタンスの総量
const int EffectManager::BILLBOARD_AMOUNT = SMOKE_EFFECT_AMOUNT;

const std::string EffectManager::SPARK_EFFECT_PATH = "Data/Effect/Blow.efkefc";
const std::string EffectManager::DAMAGE_EFFECT_PATH = "Data/Effect/damage.efkefc";
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

	//各エフェクト初期化
	effects[0] = new GuardEffect();
	effects[0]->Initialize();

	effects[1] = new DamageEffect();
	effects[1]->Initialize();

	effects[2] = new PlayerDiedEffect();
	effects[2]->Initialize();

	effects[3] = new RecoveryEffect();
	effects[3]->Initialize();

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

void EffectManager::Update(VECTOR inPostion)
{
	for (int i = 0; i < EFFECT_AMOUNT; ++i)
	{
		effects[i]->Update(inPostion);
	}

	for (int i = 0; i < BILLBOARD_AMOUNT; ++i)
	{
		graphicEffects[i]->Update();
	}
}

void EffectManager::Draw(const VECTOR& inPosition)
{
	int itr = 0;
	int length = 0;

	for (int i = 0; i < EFFECT_AMOUNT; ++i)
	{
		effects[i]->Draw();
	}

	length = BILLBOARD_AMOUNT;
	for (; itr < length; ++itr)
	{
		graphicEffects[itr]->Draw(inPosition);
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

/// <summary>
/// 煙を生成する
/// </summary>
/// <param name="inPosition"></param>
void EffectManager::CreateSmokeEffect(const VECTOR& inPosition)
{
	int itr = 0;
	int length = itr + SMOKE_EFFECT_AMOUNT;

	for (; itr < SMOKE_EFFECT_AMOUNT; ++itr)
	{
		if (graphicEffects[itr]->GetExist())
		{
			++itr;
		}
		else
		{
			graphicEffects[itr]->Activate(inPosition, 100.0f);
			return;
		}
	}
}

void EffectManager::CreateDamageEffect(const VECTOR& inPosition)
{
	if (effects[DAMAGE]->GetExist() == false)
	{
		effects[DAMAGE]->Activate(inPosition);
		return;
	}
}

void EffectManager::CreatePlayerDiedEffect(const VECTOR& inPosition)
{
	if (effects[PLAYER_DEAD]->GetExist() == false)
	{
		effects[PLAYER_DEAD]->Activate(inPosition);
		return;
	}
}

void EffectManager::CreateRecoveryEffect(const VECTOR& inPosition)
{
	if (effects[RECOVERY]->GetExist() == false)
	{
		effects[RECOVERY]->Activate(inPosition);
		return;
	}
}
