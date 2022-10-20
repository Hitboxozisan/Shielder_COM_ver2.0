#include "Pch.h"

#include "Character.h"

#include "Camera.h"

#include "KeyManager.h"

const VECTOR Camera::CAMERA_INITIAL_POSITION = VGet(2000.0f, 80.0f, -1000.0f);
const float Camera::CAMERA_LOOK_AT_HEIGHT = 300.0f;
const float Camera::CAMERA_LOOK_AT_DISTANCE = 10.0f;
const float Camera::CAMERA_FOV = 60.0f;
const float Camera::CAMERA_NEAR = 1000.0f;
const float Camera::CAMERA_FAR = 1000.0f;
const float Camera::CAMERA_OUTSIDE_RANGE = 500.0f;

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Initialize()
{
	vAngle = 0.0f;
	hAngle = 0.0f;
	float fov = CAMERA_FOV * DX_PI / 180.0f;
	//FOVを設定
	SetupCamera_Perspective(fov);

	//カメラの描画範囲を指定（NEARが手前、FARが奥のはずだが逆になってる？）
	SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);
}

void Camera::SetPosition(Character** character)
{
	VECTOR tempPosition1;
	VECTOR tempPosition2;

	// 注視点はキャラクターモデルの座標から CAMERA_LOOK_AT_HEIGHT 分だけ高い位置
	targetPosition = CAMERA_INITIAL_POSITION;
	targetPosition.y += CAMERA_LOOK_AT_HEIGHT;

	// カメラの位置はカメラの水平角度と垂直角度から算出

	// 最初に垂直角度を反映した位置を算出
	sinParam = sin(vAngle / 180.0f * DX_PI_F);
	cosParam = cos(vAngle / 180.0f * DX_PI_F);
	tempPosition1.x = 0.0f;
	tempPosition1.y = sinParam * CAMERA_LOOK_AT_DISTANCE;
	tempPosition1.z = -cosParam * CAMERA_LOOK_AT_DISTANCE;

	// 次に水平角度を反映した位置を算出
	sinParam = sin(hAngle / 180.0f * DX_PI_F);
	cosParam = cos(hAngle / 180.0f * DX_PI_F);
	tempPosition2.x = cosParam * tempPosition1.x - sinParam * tempPosition1.z;
	tempPosition2.y = tempPosition1.y;
	tempPosition2.z = sinParam * tempPosition1.x + cosParam * tempPosition1.z;

	// 算出した座標に注視点の位置を加算したものがカメラの位置
	position = VAdd(tempPosition2, targetPosition);
	/*position.x = (character[1]->GetPosition().x - character[0]->GetPosition().x ) / 2;*/
	
	// カメラの設定に反映する
	SetCameraPositionAndTarget_UpVecY(position, targetPosition);
	//DXライブラリのカメラとEffekseerのカメラを同期する
	Effekseer_Sync3DSetting();
	

	//setcamerapositionandangle()		//使うとよい
}

void Camera::Update(Character** character)
{
	twoPositionDistance = VSub(character[1]->GetPosition(), character[0]->GetPosition());
	//if(twoPositionDistance > )

	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_I))
	{
		position.z += 1;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_L))
	{
		position.x += 1;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_J))
	{
		position.x -= 1;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_K))
	{
		position.z -= 1;
	}
	
	

	//SetCameraPositionAndAngle(position, 0, 0, 0);
}

void Camera::Finalize()
{
	//プレイヤーとエネミーの距離が一定距離離れたら
	/*if (twoPositionDistance.x >= CAMERA_OUTSIDE_RANGE)
	{
		printfDx("outside");
	}*/


}
