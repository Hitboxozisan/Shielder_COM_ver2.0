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

	//ゲーム開始時にカメラを所定の位置まで移動させる
	void StartCamera(Character** character);

	//プレイヤーにズームする
	void PlayerZoom(Character** character);

	//ズームアウト
	void ZoomOut();
	//カメラを元の位置に戻す
	void RestoreCamera();

	//現在位置を取得
	const VECTOR& GetCameraPosition() const { return position; }

private:

	static const VECTOR CAMERA_INITIAL_POSITION;	//カメラ初期位置
	static const float  CAMERA_CHANGE_SPEED;		//カメラの位置を変更するスピード
	static const float  CAMERA_ZOOM_RANGE;			//ズームした時のカメラとの距離
	static const float  CAMERA_LOOK_AT_HEIGHT;
	static const float  CAMERA_LOOK_AT_DISTANCE;
	static const float  CAMERA_FOV;					//視野角
	static const float  CAMERA_NEAR;				//カメラの描画範囲（手前）
	static const float  CAMERA_FAR;					//カメラの描画範囲（奥）
	static const float  CAMERA_OUTSIDE_RANGE;		//カメラが離れる距離

	VECTOR mainCameraPosition;		//ゲーム画面のカメラの最終位置
	VECTOR position;
	VECTOR velocity;				//速度、加速度、向き
	VECTOR targetPosition;
	VECTOR twoPositionDistance;		//プレイヤーとエネミーの距離
	float changeSpeed;				//カメラの位置を変更するスピード
	float rangeOfCameraAndObject;	//カメラとオブジェクトの距離


	//カメラの向き
	float hAngle;
	float vAngle;

	float sinParam;
	float cosParam;
};

