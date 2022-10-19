#include "Pch.h"
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
{
}

Result::~Result()
{
}

void Result::Initialize()
{
	string path = IMAGE_FOLDER_PATH;
	string fullpath = path + RESULT_PATH + FILENAME_EXTENSION;

	alpha = 255;
	alphaAdd = -1;

	imageHandle = LoadGraph(fullpath.c_str());
	if (imageHandle < 0)
	{
		printfDx("読み込みに失敗_imageHandle");
	}

	fullpath = path + "Push_Enter" + FILENAME_EXTENSION;
	pushEnterImageHandle = LoadGraph(fullpath.c_str());
}

void Result::Finalize()
{
}

void Result::Activate()
{
}

void Result::Deactivate()
{
}

void Result::Update()
{
	//スペースキーでタイトルに
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_RETURN))
	{
		parent->SetNextScene(SceneManager::TITLE);
		return;
	}
}

void Result::Draw()
{
	SetDrawBright(255, 255, 255);
	DrawExtendGraph(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, imageHandle, TRUE);

	alpha += alphaAdd;						//徐々に透明にする
	if (alpha == 0 || alpha == 255)
	{
		alphaAdd = -alphaAdd;
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawExtendGraph(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, pushEnterImageHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}
