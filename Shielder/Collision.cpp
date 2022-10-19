#include "Pch.h"
#include "Collision.h"

namespace My3dLib
{
	//-----------------------------------------------------------------------------
	// @brief ���̃R���X�g���N�^
	//-----------------------------------------------------------------------------
	Sphere::Sphere()
		: localCenter()
		, worldCenter()
		, radius(0.0f)
	{
	}

	//-----------------------------------------------------------------------------
	// @brief ���̃R���X�g���N�^
	//-----------------------------------------------------------------------------
	Sphere::Sphere(const VECTOR& center, float radius)
		: localCenter(center)
		, worldCenter(center)
		, radius(radius)
	{
	}

	//-----------------------------------------------------------------------------
	// @brief ���̂̃��[���h���W���ړ�����
	//-----------------------------------------------------------------------------
	void Sphere::Move(const VECTOR& pos)
	{
		worldCenter = localCenter + pos;
	}

	//-----------------------------------------------------------------------------
	// @brief �����蔻�� ���E��
	// @param[in] sphere1 ��
	// @param[in] sphere2 ��
	// @return bool �����m���Ԃ����Ă���ꍇ��true ��Ԃ�
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
