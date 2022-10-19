#include "Pch.h"
#include "ModelManager.h"

const string ModelManager::MODEL_FOLDER_PATH = "Data/Model/";
const string ModelManager::FIELD_PATH = "Map/TestMap.mv1";
const string ModelManager::PLAYER_PATH = "Player/TestPlayer.mv1";
const string ModelManager::ENEMY_PATH = "Enemy/TestEnemy.mv1";
const string ModelManager::SHIELD_PATH = "Shield/Shield.mv1";
const string ModelManager::BULLET_PATH = "Bullet/Bullet.mv1";

ModelManager::ModelManager()
	:modelHandle()
{
	LoadAllModel();
}

ModelManager::~ModelManager()
{
	DeleteAllModel();
}

ModelManager& ModelManager::GetInstance()
{
	static ModelManager ModelManager;
	return ModelManager;
}

void ModelManager::LoadAllModel()
{
	string fullPath = MODEL_FOLDER_PATH + FIELD_PATH;
	modelHandle[FIELD] = MV1LoadModel(fullPath.c_str());

	fullPath = MODEL_FOLDER_PATH + PLAYER_PATH;
	modelHandle[PLAYER] = MV1LoadModel(fullPath.c_str());

	fullPath = MODEL_FOLDER_PATH + ENEMY_PATH;
	modelHandle[ENEMY] = MV1LoadModel(fullPath.c_str());

	fullPath = MODEL_FOLDER_PATH + SHIELD_PATH;
	modelHandle[SHIELD] = MV1LoadModel(fullPath.c_str());

	fullPath = MODEL_FOLDER_PATH + BULLET_PATH;
	modelHandle[BULLET] = MV1LoadModel(fullPath.c_str());

	for (int i = 0; i < MODEL_AMOUNT; ++i)
	{
		if (modelHandle[i] < 0)
		{
			printfDx("モデルデータの読み込み失敗_[%d]\n", i);
		}
	}
}

void ModelManager::DeleteAllModel()
{
	for (int i = 0; i < MODEL_AMOUNT; ++i)
	{
		if (modelHandle[i] != NULL)
		{
			MV1DeleteModel(modelHandle[i]);
			modelHandle[i] = NULL;
		}
	}
}

const int& ModelManager::GetModelHandle(ModelKind modelKind) const
{
	if (modelKind == MODEL_AMOUNT)
	{
		printfDx("不正な値を参照しています_ModelManager");
		return modelHandle[0];
	}

	return modelHandle[modelKind];
}