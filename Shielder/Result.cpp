#include "Pch.h"
#include <chrono>
#include <thread>
#include <random>
#include "Result.h"

#include "GameDefine.h"
#include "SceneManager.h"
#include "KeyManager.h"

using namespace std;

const string Result::IMAGE_FOLDER_PATH = "Data/Image/";
const string Result::RESULT_PATH = "Result";
const string Result::FILENAME_EXTENSION = ".png";

Result::Result(SceneManager* const sceneManager)
	:SceneBase(sceneManager)
	,imageHandle()
	,lifeBonus()
	,destroyBonus()
	,totalScore()
	,frame()
{
}

Result::~Result()
{
}

void Result::Initialize()
{
	string path = IMAGE_FOLDER_PATH;
	string fullpath = path + RESULT_PATH + FILENAME_EXTENSION;

	//�t�H���g�ǂݍ���
	font = CreateFontToHandle("Molot", 50, 1, DX_FONTTYPE_ANTIALIASING);

	//�����ǂݍ���
	LoadDivGraph("Data/Font/number.png", 10, 190, 27, 19, 27, number);

	alpha = 255;
	alphaAdd = -1;

	imageHandle = LoadGraph(fullpath.c_str());
	if (imageHandle < 0)
	{
		printfDx("�ǂݍ��݂Ɏ��s_imageHandle");
	}

	fullpath = path + "Push_Enter" + FILENAME_EXTENSION;
	pushEnterImageHandle = LoadGraph(fullpath.c_str());
}

void Result::Finalize()
{
}

void Result::Activate()
{
	frame = 0;
}

void Result::Deactivate()
{
}

void Result::Update()
{
	//�����p�ϐ�
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<int> next(0, 999999999 - 1);

	frame++;

	
	{
		lifeBonus = next(eng);
	}

	//�X�y�[�X�L�[�Ń^�C�g����
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_RETURN))
	{
		parent->SetNextScene(SceneManager::TITLE);
		return;
	}
}

void Result::Draw()
{
	//SetDrawBright(255, 255, 255);
	DrawExtendGraph(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, imageHandle, TRUE);

	alpha += alphaAdd;						//���X�ɓ����ɂ���
	if (alpha == 0 || alpha == 255)
	{
		alphaAdd = -alphaAdd;
	}

	//�e�X�g�`��
	//DrawFormatStringToHandle(200, 200, , GetColor(255, 255, 255), font);
	DrawGraph(300, 200, number[0], TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawExtendGraph(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, pushEnterImageHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}
