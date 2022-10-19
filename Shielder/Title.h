#pragma once

#include "SceneBase.h"

#include <string>

class Title final : public SceneBase
{
public:
	Title(SceneManager* const sceneManager);
	~Title();

	void Initialize();	//‰Šú‰»ˆ—
	void Finalize();	//I—¹ˆ—
	void Activate();	//Šˆ«‰»ˆ—
	void Deactivate();	//”ñŠˆ«‰»ˆ—
	void Update();		//XVˆ—
	void Draw();		//•`‰æˆ—

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

