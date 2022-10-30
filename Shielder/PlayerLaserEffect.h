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
	void Update(VECTOR inPostion, VECTOR inEnemyPosition);
	void Draw();

	void SpecificEnemyPosition(VECTOR inPosition, VECTOR inEnemyPosition);			//�G�l�~�[�̈ʒu�����i���[�U�[���ˈʒu�����j

private:
	PlayerLaserEffect(const PlayerLaserEffect&);
	void operator=(const PlayerLaserEffect&);
	

	VECTOR direction;										//����
};

