#pragma once

#include "EffectBase.h"

class GuardEffect : public EffectBase
{
public:
	GuardEffect();
	~GuardEffect();
	
	void Initialize();
	void Activate(VECTOR inPosition);
	void Deactivate();
	void Update();
	void Draw();
private:
	//GuardEffect();
	GuardEffect(const GuardEffect&);
	void operator=(const GuardEffect&);
	//~GuardEffect();

	int effectHandle;		//エフェクトハンドル
	VECTOR position;		

	int playEffectHandle;
};

