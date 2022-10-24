#pragma once

#include<string>

class SoundManager final
{
public:
	enum Bgm
	{

	};

	enum Se
	{

	};

	static SoundManager& GetInstance();

	void Update();

	void PlayBgm(Bgm bgm, bool loop = true);
	void StopBgm();
	void SetSePlayFlag(Se se);

private:
	SoundManager();
	SoundManager(const SoundManager&);
	void operator=(const SoundManager&);
	~SoundManager();

	void LoadAllSound();
	void DeleteAllSound();

	void VolumeChange();

	static const std::string SOUND_FOLDER_PATH;
};

