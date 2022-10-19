#pragma once

#include <string>

using namespace std;

class ModelManager final
{
public:

	enum ModelKind
	{
		FIELD = 0,
		PLAYER,
		ENEMY,
		SHIELD,
		BULLET,

		MODEL_AMOUNT
	};

	ModelManager();
	~ModelManager();

	static ModelManager& GetInstance();

	const int& GetModelHandle(ModelKind modelKind)const;

private:

	void LoadAllModel();
	void DeleteAllModel();

	static const string MODEL_FOLDER_PATH;
	static const string FIELD_PATH;
	static const string PLAYER_PATH;
	static const string ENEMY_PATH;
	static const string SHIELD_PATH;
	static const string BULLET_PATH;

	int modelHandle[MODEL_AMOUNT];
};

