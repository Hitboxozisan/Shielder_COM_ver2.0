#pragma once

namespace My3dLib
{
	// @brief 球体当たり判定.
	struct Sphere
	{
		Sphere();
		Sphere(const VECTOR& center, float radius);
		void Move(const VECTOR& pos);

		VECTOR localCenter; // 球体のローカル中心座標
		VECTOR worldCenter; // 球体のワールド中心座標
		float  radius;      // 球体の半径
	};

	struct Capsule
	{
		Capsule();
		Capsule(const VECTOR& pos1, const VECTOR& pos2, float radius);
		void Set(const VECTOR& pos1, const VECTOR& pos2);


		VECTOR worldPosition1;	 // 球体のワールド中心座標
		VECTOR localPosition1;	 // 球体のローカル中心座標
		VECTOR worldPosition2;	 // 球体のワールド中心座標
		VECTOR localPosition2;	 // 球体のローカル中心座標
		float  radius;      // 球体の半径
	};

	// 当たり判定の関数組み合わせ
	bool CollisionPair(const Sphere& sphere1, const Sphere& sphere2);
	bool CollisionCapsuleAndSphere(const Sphere& sphere, const Capsule& capsule);


}