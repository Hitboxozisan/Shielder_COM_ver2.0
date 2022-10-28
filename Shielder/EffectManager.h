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
		DAMAGE,				//ダメージ
		PLAYER_DEAD,		//死亡
		RECOVERY,

		EFFECT_AMOUNT,		//エフェクトの総数
	};

	EffectManager();
	~EffectManager();

	void Initialize();
	void Finalize();
	void Activate(VECTOR inPosition);
	void Deactivate();
	void Update(VECTOR inPostion);
	void Draw(const VECTOR& inPosition);

	void CreateSparkEffect(const VECTOR& inPosition);		//火花を生成する
	void CreateSmokeEffect(const VECTOR& inPosition);		//煙を生成する
	void CreateDamageEffect(const VECTOR& inPosition);		//ダメージエフェクトを生成する
	void CreatePlayerDiedEffect(const VECTOR& inPosition);	//プレイヤー死亡エフェクトを生成する
	void CreateRecoveryEffect(const VECTOR& inPosition);	//プレイヤー回復エフェクトを生成する

private:
	EffectManager(const EffectManager&);
	void operator=(const EffectManager&);

	static const std::string SPARK_EFFECT_PATH;
	static const std::string DAMAGE_EFFECT_PATH;
	static const std::string RIGOR_EFFECT_GRAPHIC_PATH;

	static const int SMOKE_EFFECT_AMOUNT;

	//ベースクラスインスタンスの総量
	//enum と こちらか統一する必要あり
	static const int BILLBOARD_AMOUNT;

	EffectBase* effects[EFFECT_AMOUNT];
	BillboardBase** graphicEffects;

	int smokeGraphicHandle;
};

