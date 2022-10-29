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

	position = VGet(2000.0f, -100.0f, 100.0f);
	MV1SetPosition(modelHandle, position);
}

void Field::Draw()
{
	//MV1DrawModel(modelHandle);

}
