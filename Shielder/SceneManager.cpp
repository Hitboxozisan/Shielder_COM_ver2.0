
#include "SceneManager.h"

#include "GameMain.h"
#include "Title.h"
#include "Result.h"

SceneManager::SceneManager()
	:eachScenes()
	,currentPointer(nullptr)
	,currentScene()
	,nextScene()
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::Initialize()
{
	eachScenes[TITLE] = new Title(this);
	eachScenes[GAME_MAIN] = new GameMain( this );
	eachScenes[RESULT] = new Result(this);

	//

	for (int i = 0; i < SceneManager::END; ++i)
	{
		eachScenes[i]->Initialize();
	}

	//�{����TITLE
	currentScene = nextScene = TITLE;
#ifdef DEBUG
	currentScene = nextScene = GAME_MAIN;
#endif

	currentPointer = eachScenes[currentScene];
	currentPointer->Activate();
}

void SceneManager::Finalize()
{
	for (int i = 0; i < SceneManager::END; ++i)
	{
		eachScenes[i]->Finalize();
		delete eachScenes[i];
		eachScenes[i] = nullptr;
	}
}

void SceneManager::Update()
{
	if (currentScene != nextScene)
	{
		ChangeScene();		//���̃V�[��
	}

	if (currentPointer != nullptr)
	{
		currentPointer->Update();	//���݂̃V�[���̍X�V����
	}
}

void SceneManager::Draw()
{
	if (currentPointer != nullptr)
	{
		currentPointer->Draw();		//���݂̃V�[���̕`�揈��
	}
}

void SceneManager::SetNextScene(Scene next)
{
	nextScene = next;
}

void SceneManager::ChangeScene()
{
	if (nextScene == END)
	{
		return;
	}

	currentPointer->Deactivate();
	currentPointer = eachScenes[nextScene];
	currentScene = nextScene;
	currentPointer->Activate();
}
