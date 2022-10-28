#include "Pch.h"
#include "UiManager.h"

using std::string;

const std::string UiManager::GRAPHIC_FOLDER_PATH = "Data/Image/";
const std::string UiManager::UI_GRAPHIC_PATH = "ui";
const std::string UiManager::FILENAME_EXTENSION = ".png";

UiManager::UiManager()
	:imageHandle()
	,frame(0)
{
}

UiManager::~UiManager()
{
	if (imageHandle[0] != NULL)
	{
		Finalize();
	}
}

void UiManager::Initialize()
{
	string path = GRAPHIC_FOLDER_PATH + UI_GRAPHIC_PATH;
	string fullPath = path;

	for (int i = 0; i < IMAGE_AMOUNT; ++i)
	{
		fullPath = path + std::to_string(i) + FILENAME_EXTENSION;
		imageHandle[i] = LoadGraph(fullPath.c_str());

		if (imageHandle[i] < 0)
		{
			printfDx("�摜�ǂݍ��݂Ɏ��s_ui[%d]", i);
		}
	}


}

void UiManager::Finalize()
{
	for (int i = 0; i < IMAGE_AMOUNT; ++i)
	{
		DeleteGraph(imageHandle[i]);
		imageHandle[i] = NULL;
	}
}

void UiManager::Draw(GameMain::State state, float characterHp, float playerTrunk, float enemyTrunk)
{
	++frame;
	switch (state)
	{
	case GameMain::START:
		StartBattleDraw();
		break;
	case GameMain::GAME:
		PlayerHpDraw(characterHp);
		TrunkGaugeDraw(playerTrunk, enemyTrunk);
		break;
	case GameMain::GAME_OVER:

		break;
	case GameMain::RESULT:

		break;
	default:
		break;
	}
	
}

void UiManager::StartBattleDraw()
{
	if (frame <= 100)
	{
		//�ő�̗͂���������100�Ƃ���
		float playerMaxHp = 100.0f;
		//�ő�̊��ʂ���������100�Ƃ���
		float playerMaxTrunk = 100.0f;
		float enemyMaxTrunk = 100.0f;

		//�̗̓Q�[�W�\��
		DrawBox(300, 445, 300 + 1000 * frame / playerMaxHp, 450, GetColor(0, 255, 0), TRUE);
		//�̗̓Q�[�W�g
		DrawRotaGraph(300, 1000, 0.8, 0.0, imageHandle[PLAYER_HP], TRUE);

		//�̊��Q�[�W�\��
		DrawBox(195, 440, 195 + 240 * (frame / playerMaxTrunk), 455, GetColor(0, 255, 0), TRUE);			//�v���C���[�̑̊��Q�[�W
		//DrawBox(35, 95, 35 + 570 * (frame / enemyMaxTrunk), 105, GetColor(0, 255, 0), TRUE);					//�G�l�~�[�̈�{�̊��Q�[�W
		DrawBox(980, 90, 980 + 750 * (frame / enemyMaxTrunk), 110, GetColor(246, 200, 0), TRUE);					//�G�l�~�[�̉E���̊��Q�[�W
		DrawBox(980, 90, 980 + 750 * (-frame / enemyMaxTrunk), 110, GetColor(246, 200, 0), TRUE);					//�G�l�~�[�̍����̊��Q�[�W
		//�Q�[�W�̘g��\��
		DrawRotaGraph(950, 1000, 0.8, 0.0, imageHandle[PLAYER_TRUNK], TRUE);		//�v���C���[�Q�[�W�g
		DrawRotaGraph(980, 100, 0.8, 0.0, imageHandle[ENEMY_TRUNK], TRUE);		//�G�l�~�[�Q�[�W�g
	}

}

void UiManager::PlayerHpDraw(float characterHp)
{
	//�ő�̗͂���������100�Ƃ���
	float playerMaxHp = 100.0f;
	//DrawGraphF(50, 300, imageHandle[PLAYER_HP], TRUE);

	//�̗̓Q�[�W�\��
	DrawBox(55, 1000, 55 + 490 * (characterHp/playerMaxHp), 1025, GetColor(0, 255, 0), TRUE);
	//�̗̓Q�[�W�g
	DrawRotaGraph(300, 1000, 0.8, 0.0, imageHandle[PLAYER_HP], TRUE);
}

void UiManager::TrunkGaugeDraw(float playerTrunk, float enemyTrunk)
{
	//�ő�̊��ʂ���������100�Ƃ���
	float playerMaxTrunk = 100.0f;
	float enemyMaxTrunk = 100.0f;

	//�F����
	int subGreen = enemyTrunk;

	//DrawGraphF(200, 400, imageHandle[PLAYER_TRUNK], TRUE);
	//DrawGraphF(200, 200, imageHandle[ENEMY_TRUNK], TRUE);

	//�̊��Q�[�W�\��
	DrawBox(710, 990, 710 + 300 * (playerTrunk/playerMaxTrunk), 1015, GetColor(0, 255, 0), TRUE);			//�v���C���[�̑̊��Q�[�W
	DrawBox(980, 90, 980 + 750 * (enemyTrunk/enemyMaxTrunk), 110, GetColor(246, 200 - subGreen, 0), TRUE);				//�G�l�~�[�̉E���̊��Q�[�W
	DrawBox(980, 90, 980 + 750 * (-enemyTrunk / enemyMaxTrunk), 110, GetColor(246, 200 - subGreen, 0), TRUE);			//�G�l�~�[�̍����̊��Q�[�W


	//�Q�[�W�̘g��\��
	DrawRotaGraph(950, 1000, 0.8, 0.0, imageHandle[PLAYER_TRUNK], TRUE);	//�v���C���[�̊��Q�[�W�g
	DrawRotaGraph(980, 100, 0.8, 0.0, imageHandle[ENEMY_TRUNK], TRUE);		//�G�l�~�[�̊��Q�[�W�g

}

void UiManager::DrawTitle()
{
}


