#pragma once

#include "SceneBase.h"

#include <string>

class Character;

/// <summary>
/// Result�N���X���ݕs�g�p
/// GameMain�ɂĕʓrResult�쐬
/// </summary>
class Result final : public SceneBase
{
public:
	Result(SceneManager* const sceneManager);
	~Result();

	void Initialize();	//����������
	void Finalize();	//�I������
	void Activate();	//����������
	void Deactivate();	//�񊈐�������
	void Update();		//�X�V����
	void Draw();		//�`�揈��


private:
	Result();
	Result(const Result&);
	void operator=(const Result&);

	static const std::string IMAGE_FOLDER_PATH;
	static const std::string RESULT_PATH;
	static const std::string FILENAME_EXTENSION;

	int font;
	int number[9];
	int alpha;
	int alphaAdd;
	int imageHandle;					//Result��ʉ摜
	int playerLife;						//�v���C���[�̎c��̗�
	int destroy;						//�|������
	int lifeBonus;
	int destroyBonus;
	int totalScore;
	int pushEnterImageHandle;

	int frame;

	Character** character;

	//void SetCharacter(Character** character);
};

