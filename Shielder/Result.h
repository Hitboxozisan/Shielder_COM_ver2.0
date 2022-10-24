#pragma once

#include "SceneBase.h"

#include <string>

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
	int imageHandle;
	int lifeBonus;
	int destroyBonus;
	int totalScore;
	int pushEnterImageHandle;

	int frame;
};

