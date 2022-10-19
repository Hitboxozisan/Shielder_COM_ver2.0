#pragma once

class Character;

class Camera final
{
public:
	Camera();
	~Camera();

	void Initialize();
	void SetPosition(Character** character);
	void Update(Character** character);
	void Finalize();

	//現在位置を取得
	const VECTOR& GetCameraPosition() const { return position; }

private:

	static const VECTOR CAMERA_INITIAL_POSITION;	//カメラ初期位置
	static const float  CAMERA_LOOK_AT_HEIGHT;
	static const float  CAMERA_LOOK_AT_DISTANCE;
	static const float  CAMERA_FOV;					//視野角
	static const float  CAMERA_NEAR;				//カメラの描画範囲（手前）
	static const float  CAMERA_FAR;					//カメラの描画範囲（奥）
	static const float  CAMERA_OUTSIDE_RANGE;		//カメラが離れる距離

	VECTOR position;
	VECTOR targetPosition;
	VECTOR twoPositionDistance;		//プレイヤーとエネミーの距離

	//カメラの向き
	float hAngle;
	float vAngle;

	float sinParam;
	float cosParam;
};

