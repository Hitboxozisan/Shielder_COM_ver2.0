#pragma once

#include "EffectBase.h"

class RecoveryEffect : public EffectBase
{
public:
	RecoveryEffect();
	~RecoveryEffect();

	void Initialize();
	void Finalize();
	void Activate(VECTOR inPosition);
	void Deactivate();
	void Update(VECTOR inPosition);
	void Draw();
private:
	RecoveryEffect(const RecoveryEffect&);
	void operator=(const RecoveryEffect&);
};

