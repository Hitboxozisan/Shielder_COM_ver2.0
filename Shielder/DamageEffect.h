#pragma once

#include "EffectBase.h"

class DamageEffect : public EffectBase
{
public:
	DamageEffect();
	~DamageEffect();

	void Initialize();
	void Finalize();
	void Activate(VECTOR inPosition);
	void Deactivate();
	void Update(VECTOR inPostion);
	void Draw();

private:
	DamageEffect(const DamageEffect&);
	void operator=(const DamageEffect&);

};

