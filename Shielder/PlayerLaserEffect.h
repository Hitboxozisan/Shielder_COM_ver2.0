#pragma once

#include "EffectBase.h"

class PlayerLaserEffect : public EffectBase
{
public:
	PlayerLaserEffect();
	~PlayerLaserEffect();

	void Initialize();
	void Finalize();
	void Activate(VECTOR inPosition);
	void Deactivate();
	void Update(VECTOR inPostion);
	void Draw();
private:
	PlayerLaserEffect(const PlayerLaserEffect&);
	void operator=(const PlayerLaserEffect&);

};

