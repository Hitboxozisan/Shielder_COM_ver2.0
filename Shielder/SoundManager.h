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
	//�萔
	static const std::string SOUND_FOLDER_PATH;  // Sound�t�H���_�܂ł̃p�X
	static const std::string BGM_PATH;           // BGM�t�@�C����(�A�ԏ���)
	static const std::string SE_PATH;            // SE�t�@�C����(�A�ԏ���)
	static const std::string BGM_FILENAME_EXTENSION; // BGM�g���q
	static const std::string SE_FILENAME_EXTENSION;  // SE�g���q

	static const int BGM_VOLUME;                 // BGM�̉���
	static const int SE_VOLUME;                  // SE�̉���


	int  bgmData[BGM_AMOUNT];  // BGM�ǂݍ��ݗp
	int  seData[SE_AMOUNT];    // SE�ǂݍ��ݗp
	bool sePlayFlag[SE_AMOUNT];// ���̃t���[���ōĐ����邩
};

