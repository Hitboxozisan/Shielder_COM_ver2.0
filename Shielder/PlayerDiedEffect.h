#pragma once

#include"EffectBase.h"

class PlayerDiedEffect : public EffectBase
{
public:
	PlayerDiedEffect();
	~PlayerDiedEffect();

	void Initialize();
	void Finalize();
	void Activate(VECTOR inPosition);
	void Deactivate();
	void Update();
	void Draw();
private:
	PlayerDiedEffect(const PlayerDiedEffect&);
	void operator = (const PlayerDiedEffect&);
};

