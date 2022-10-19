#pragma once

class SceneBase;

class SceneManager final
{
public:
	//�V�[����Ԓ�`
	enum Scene
	{
		TITLE = 0,	//�^�C�g�����
		GAME_MAIN,	//�Q�[�����
		RESULT,		//���U���g���
		END			//�I������@���@�V�[���̌�
	};

	SceneManager();
	~SceneManager();

	void Initialize();
	void Finalize();
	void Update();
	void Draw();

	void SetNextScene(Scene next);
	Scene GetCurrentScene() { return currentScene; }
	Scene GetNextScene() { return nextScene; }
private:
	SceneManager(const SceneManager&);		//�R�s�[�R���X�g���N�^
	void operator=(const SceneManager&);	//�R�s�[������Z�q

	SceneBase* eachScenes[Scene::END];		//�e�V�[���̃C���X�^���X
	SceneBase* currentPointer;				//���݂̃V�[���̃|�C���^
	Scene	   currentScene;				//���݂̃V�[��
	Scene	   nextScene;					//���̃V�[��

	void ChangeScene();						//�V�[����ύX����
};

