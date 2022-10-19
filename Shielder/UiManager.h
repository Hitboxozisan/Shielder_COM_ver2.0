#pragma once

#include "GameMain.h"
#include <string>

class UiManager
{
public:
	UiManager();
	~UiManager();

	void Initialize();
	void Finalize();
	

	void Draw(GameMain::State state, float characterHp, float playerTrunk, float enemyTrunk);
private:
	UiManager(const UiManager&);
	void operator=(const UiManager&);

	void StartBattleDraw();
	void PlayerHpDraw(float characterHp);
	void TrunkGaugeDraw(float playerTrunk, float enemyTrunk);
	void DrawTitle();
	
	static const std::string GRAPHIC_FOLDER_PATH;
	static const std::string UI_GRAPHIC_PATH;
	static const std::string FILENAME_EXTENSION;

	enum Image
	{
		PLAYER_HP,
		PLAYER_TRUNK,
		ENEMY_TRUNK,
		IMAGE_AMOUNT
	};

	int imageHandle[IMAGE_AMOUNT];
	int frame;
};

