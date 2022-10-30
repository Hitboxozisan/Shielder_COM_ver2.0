#pragma once

#include<string>

class SoundManager final
{
public:
	enum Bgm
	{
		MAIN,

		BGM_AMOUNT
	};

	enum Se
	{
		CHARACTER_HIT,
		BULLET_HIT,
		SHIELD_HIT,
		PLAYER_STARTLAZER,
		PLAYER_LAZER,
		PLAYER_DIE,
		DECIDE_SCORE,
		SE_AMOUNT
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
	//定数
	static const std::string SOUND_FOLDER_PATH;  // Soundフォルダまでのパス
	static const std::string BGM_PATH;           // BGMファイル名(連番除く)
	static const std::string SE_PATH;            // SEファイル名(連番除く)
	static const std::string BGM_FILENAME_EXTENSION; // BGM拡張子
	static const std::string SE_FILENAME_EXTENSION;  // SE拡張子

	static const int BGM_VOLUME;                 // BGMの音量
	static const int SE_VOLUME;                  // SEの音量


	int  bgmData[BGM_AMOUNT];  // BGM読み込み用
	int  seData[SE_AMOUNT];    // SE読み込み用
	bool sePlayFlag[SE_AMOUNT];// このフレームで再生するか
};

