#pragma once

#include "Mover.h"

class EnemyBase : public Mover
{
public:

	void Initialize();
	void Finalize();
	void Activate();
	void Deactivate();
	void Update();
	void Draw();

	void OnHitShield();
	void OnHitCharacter();

protected:
	
private:

};

