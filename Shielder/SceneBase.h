#pragma once

class SceneManager;

class SceneBase
{
public:
	SceneBase(SceneManager* const sceneManager);
	virtual ~SceneBase();

	virtual void Initialize() = 0;	//����������
	virtual void Finalize() = 0;	//�I������
	virtual void Activate() = 0;	//����������
	virtual void Deactivate() = 0;	//�񊈐�������
	virtual void Update() = 0;		//�X�V����
	virtual void Draw() = 0;		//�`�揈��

protected:
	SceneManager* const parent;

private:
	SceneBase();						//�f�t�H���g�R���X�g���N�^
	SceneBase(const SceneBase&);		//�R�s�[�R���X�g���N�^
	void operator=(const SceneBase&);	//�R�s�[������Z�q
};

