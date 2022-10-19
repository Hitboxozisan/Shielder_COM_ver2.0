#pragma once

#include "SceneBase.h"

#include <string>

class Result final : public SceneBase 
{
public:
	Result(SceneManager* const sceneManager);
	~Result();

	void Initialize();	//‰Šú‰»ˆ—
	void Finalize();	//I—¹ˆ—
	void Activate();	//Šˆ«‰»ˆ—
	void Deactivate();	//”ñŠˆ«‰»ˆ—
	void Update();		//XVˆ—
	void Draw();		//•`‰æˆ—


private:
	Result();
	Result(const Result&);
	void operator=(const Result&);

	static const std::string IMAGE_FOLDER_PATH;
	static const std::string RESULT_PATH;
	static const std::string FILENAME_EXTENSION;

	int alpha;
	int alphaAdd;
	int imageHandle;
	int pushEnterImageHandle;
};

