#include "Pch.h"

#include "Bullet.h"
#include "BulletCreater.h"

BulletCreater::BulletCreater(std::list<Bullet*>* const activeList, std::list<Bullet*>* const deactiveList)
	:activeBullet(activeList)
	,deActiveBullet(deactiveList)
{
}

BulletCreater::~BulletCreater()
{
}

Bullet* BulletCreater::Create(const VECTOR& inPosition, const VECTOR& inDirection)
{
	activeBullet->push_back(deActiveBullet->front());
	deActiveBullet->pop_front();
	activeBullet->back()->Activate(inPosition, inDirection);

	return activeBullet->back();
}

bool BulletCreater::IsCreatableCheck()
{
	//‹ó‚«‚ª‚ ‚é
	if (deActiveBullet->empty() == false)
	{
		return true;
	}

	return false;
}
