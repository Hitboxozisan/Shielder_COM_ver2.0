#pragma once

#include "EffectBase.h"

class GuardEffect : public EffectBase
{
public:
	GuardEffect();
	~GuardEffect();
	
	void Initialize();
	void Finalize();
	void Activate(VECTOR inPosition);
	void Deactivate();
	void Update();
	void Draw();


private:
	//GuardEffect();
	GuardEffect(const GuardEffect&);
	void operator=(const GuardEffect&);
	//~GuardEffect();
};

