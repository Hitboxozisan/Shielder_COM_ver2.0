#include "Pch.h"
#include "Title.h"

#include "GameDefine.h"
#include "SceneManager.h"
#include "KeyManager.h"

using namespace std;

const string Title::MOVIE_FOLDER_PATH = "Data/Movie/";
const string Title::DEMO_PATH = "Demo";
//const string Title::FILENAME_EXTENSION = ".mp4";
const string Title::IMAGE_FOLDER_PATH = "Data/Image/";
const string Title::TITLE_PATH = "Title";
const string Title::KEY_PATH = "Push_Space";
const string Title::FILENAME_EXTENSION = ".png";

Title::Title(SceneManager* const sceneManager)
	:SceneBase(sceneManager)
	,movieGraphHandle()
	,frame()
{
}

Title::~Title()
{
}

void Title::Initialize()
{
	string path = MOVIE_FOLDER_PATH;
	string fullpath = path + DEMO_PATH + FILENAME_EXTENSION;
	/*movieGraphHandle = LoadGraph(fullpath.c_str());
	if (movieGraphHandle < 0)
	{
		printfDx("動画読み込みに失敗_demo");
	}*/

	alpha = 255;
	alphaAdd = -1;

	path = IMAGE_FOLDER_PATH;
	fullpath = path + TITLE_PATH + FILENAME_EXTENSION;
	titleImageHandle = LoadGraph(fullpath.c_str());
	if (titleImageHandle < 0)
	{
		printfDx("error");
	}
	
	path = IMAGE_FOLDER_PATH;
	fullpath = path + KEY_PATH + FILENAME_EXTENSION;
	keyImageHandle = LoadGraph(fullpath.c_str());
	if (keyImageHandle < 0)
	{
		printfDx("error");
	}
}

void Title::Finalize()
{

}

void Title::Activate()
{
}

void Title::Deactivate()
{
	PauseMovieToGraph(movieGraphHandle);
}

void Title::Update()
{
	//スペースキーでゲーム開始
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_SPACE))
	{
		PauseMovieToGraph(movieGraphHandle);
		parent->SetNextScene(SceneManager::GAME_MAIN);
		return;
	}
}

void Title::Draw()
{
	DrawExtendGraph(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, titleImageHandle, TRUE);

	alpha += alphaAdd;						//徐々に透明にする
	if (alpha == 0 || alpha == 255)
	{
		alphaAdd = -alphaAdd;
	}
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawExtendGraph(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, keyImageHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}
