#pragma once

#include "SceneBase.h"

#include <string>

class Title final : public SceneBase
{
public:
	Title(SceneManager* const sceneManager);
	~Title();

	void Initialize();	//����������
	void Finalize();	//�I������
	void Activate();	//����������
	void Deactivate();	//�񊈐�������
	void Update();		//�X�V����
	void Draw();		//�`�揈��

private:
	Title();
	Title(const Title&);
	void operator=(const Title&);

	static const std::string MOVIE_FOLDER_PATH;
	static const std::string DEMO_PATH;
	//static const std::string FILENAME_EXTENSION;
	static const std::string IMAGE_FOLDER_PATH;
	static const std::string TITLE_PATH;
	static const std::string KEY_PATH;
	static const std::string FILENAME_EXTENSION;

	int movieGraphHandle;
	int titleImageHandle;
	int keyImageHandle;

	int alpha;
	int alphaAdd;
	int frame;
};

