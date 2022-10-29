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

	void SpecificEnemyPosition(VECTOR inPosition);			//エネミーの位置を特定（レーザー発射位置を特定）

private:
	PlayerLaserEffect(const PlayerLaserEffect&);
	void operator=(const PlayerLaserEffect&);
	

	VECTOR direction;											//向き


};

