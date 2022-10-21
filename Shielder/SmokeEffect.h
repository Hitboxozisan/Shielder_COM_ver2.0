#pragma once

#include "BillboardBase.h"

class SmokeEffect final : public BillboardBase
{
public:
	SmokeEffect();
	~SmokeEffect();

	void Activate(const VECTOR& creatorPosition, float creatorSize);
	void Draw();

	void UpdateEach();
private:

};

