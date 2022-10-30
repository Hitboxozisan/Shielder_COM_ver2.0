#include "Pch.h"
#include "Field.h"

#include "ModelManager.h"

Field::Field()
{
}

Field::~Field()
{
}

void Field::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::FIELD));
	MV1SetScale(modelHandle, VGet(1.5f, 1.0f, 2.0f));														//モデルのサイズ変更

	position = VGet(2000.0f, -40.0f, 100.0f);
	MV1SetPosition(modelHandle, position);
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));
}

void Field::Draw()
{
	MV1DrawModel(modelHandle);

}
