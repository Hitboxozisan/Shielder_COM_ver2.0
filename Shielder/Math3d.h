#pragma once

namespace My3dLib
{
	// @brief ベクトル同士の加算
	VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs);

	// @brief ベクトル同士の減算
	VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs);

	// @brief ベクトルのスカラー倍
	VECTOR operator*(float s, const VECTOR& rhs);

	// @brief ベクトルのスカラー倍
	VECTOR operator*(const VECTOR& lhs, float s);

	// @brief += VECTORの演算子
	VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs);

	// @brief *= VECTORのスカラー倍の複合代入演算子
	VECTOR operator*=(VECTOR& lhs, float rhs);

	// @brief ２つのベクトルの角度はほぼ同じか
	bool IsNearAngle(const VECTOR& v1, const VECTOR& v2);

	// @brief nowVecからdirVecの最短の回転方向を調べる（Y軸回転を想定)
	float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec);

	// @brief nowVecから aimVecに向かってdegreeVerociyの速度でY回転する.
	VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVerocity);

	float GetRandf(float min, float max);

}
