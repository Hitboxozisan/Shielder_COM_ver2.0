#include "Pch.h"
#include "Collision.h"

namespace My3dLib
{
	//-----------------------------------------------------------------------------
	// @brief 球体コンストラクタ
	//-----------------------------------------------------------------------------
	Sphere::Sphere()
		: localCenter()
		, worldCenter()
		, radius(0.0f)
	{
	}

	//-----------------------------------------------------------------------------
	// @brief 球体コンストラクタ
	//-----------------------------------------------------------------------------
	Sphere::Sphere(const VECTOR& center, float radius)
		: localCenter(center)
		, worldCenter(center)
		, radius(radius)
	{
	}

	//-----------------------------------------------------------------------------
	// @brief 球体のワールド座標を移動する
	//-----------------------------------------------------------------------------
	void Sphere::Move(const VECTOR& pos)
	{
		worldCenter = localCenter + pos;
	}

	//-----------------------------------------------------------------------------
	// @brief 当たり判定 球・球
	// @param[in] sphere1 球
	// @param[in] sphere2 球
	// @return bool 球同士がぶつかっている場合はtrue を返す
	//-----------------------------------------------------------------------------
	bool CollisionPair(const Sphere& sphere1, const Sphere& sphere2)
	{
		return HitCheck_Sphere_Sphere(sphere1.worldCenter, sphere1.radius,
			sphere2.worldCenter, sphere2.radius);
	}

	bool CollisionCapsuleAndSphere(const Sphere& sphere, const Capsule& capsule)
	{
		return HitCheck_Sphere_Capsule(sphere.worldCenter, sphere.radius,
			capsule.worldPosition1, capsule.worldPosition2, capsule.radius);
	}


	Capsule::Capsule()
		: worldPosition1()
		, localPosition1()
		, worldPosition2()
		, localPosition2()
		, radius()
	{

	}

	Capsule::Capsule(const VECTOR& pos1, const VECTOR& pos2, float radius)
		: worldPosition1(pos1)
		, localPosition1(pos1)
		, worldPosition2(pos2)
		, localPosition2(pos2)
		, radius(radius)
	{

	}

	void Capsule::Set(const VECTOR& pos1, const VECTOR& pos2)
	{
		worldPosition1 = localPosition1 + pos1;
		worldPosition2 = localPosition2 + pos2;
	}

}
