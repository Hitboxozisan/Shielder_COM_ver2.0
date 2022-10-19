#pragma once

namespace My3dLib
{
	// @brief ���̓����蔻��.
	struct Sphere
	{
		Sphere();
		Sphere(const VECTOR& center, float radius);
		void Move(const VECTOR& pos);

		VECTOR localCenter; // ���̂̃��[�J�����S���W
		VECTOR worldCenter; // ���̂̃��[���h���S���W
		float  radius;      // ���̂̔��a
	};

	struct Capsule
	{
		Capsule();
		Capsule(const VECTOR& pos1, const VECTOR& pos2, float radius);
		void Set(const VECTOR& pos1, const VECTOR& pos2);


		VECTOR worldPosition1;	 // ���̂̃��[���h���S���W
		VECTOR localPosition1;	 // ���̂̃��[�J�����S���W
		VECTOR worldPosition2;	 // ���̂̃��[���h���S���W
		VECTOR localPosition2;	 // ���̂̃��[�J�����S���W
		float  radius;      // ���̂̔��a
	};

	// �����蔻��̊֐��g�ݍ��킹
	bool CollisionPair(const Sphere& sphere1, const Sphere& sphere2);
	bool CollisionCapsuleAndSphere(const Sphere& sphere, const Capsule& capsule);


}