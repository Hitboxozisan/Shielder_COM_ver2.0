#include "Pch.h"
#include "SoundManager.h"

using std::string;

const string SoundManager::SOUND_FOLDER_PATH = "Data/Sound/";
const string SoundManager::BGM_PATH = "Bgm";
const string SoundManager::SE_PATH = "Se";
const string SoundManager::BGM_FILENAME_EXTENSION = ".mp3";
const string SoundManager::SE_FILENAME_EXTENSION = ".mp3";

const int SoundManager::SE_VOLUME = 255 * 40 / 100;
const int SoundManager::BGM_VOLUME = 255 * 40 / 100;

SoundManager::SoundManager()
	:bgmData()
	, seData()
	, sePlayFlag()
{
	LoadAllSound();
	VolumeChange();
}

SoundManager::~SoundManager()
{
    DeleteAllSound();
}

SoundManager& SoundManager::GetInstance()
{
	static SoundManager soundManager;
	return soundManager;
}

void SoundManager::Update()
{
    // 登録された効果音を再生
    for (int i = 0; i < SE_AMOUNT; ++i)
    {
        // 登録されていない
        if (sePlayFlag[i] == false)
        {
            continue;
        }

        // 同じ音声が既に再生中なら音量を0にして停止
        if (CheckSoundMem(seData[i]) != 0)   // 戻り値がint
        {
            ChangeVolumeSoundMem(0, seData[i]);
            StopSoundMem(seData[i]);
            ChangeVolumeSoundMem(SE_VOLUME, seData[i]);
        }
        PlaySoundMem(seData[i], DX_PLAYTYPE_BACK, TRUE); // 再生
        sePlayFlag[i] = false;
    }
}

void SoundManager::PlayBgm(Bgm bgm, bool loop)
{
    if (loop == true)
    {
        PlaySoundMem(bgmData[bgm], DX_PLAYTYPE_LOOP, TRUE);
    }
    else
    {
        PlaySoundMem(bgmData[bgm], DX_PLAYTYPE_BACK, TRUE);
    }
}

void SoundManager::StopBgm()
{
    for (int i = 0; i < BGM_AMOUNT; ++i)
    {
        StopSoundMem(bgmData[i]);
    }
}

void SoundManager::SetSePlayFlag(Se se)
{
    sePlayFlag[se] = true;
}

void SoundManager::LoadAllSound()
{
    // BGMデータ読み込み
    string path = SOUND_FOLDER_PATH + BGM_PATH; // フォルダパス + ファイル名
    string fullPath = path;
    for (int i = 0; i < BGM_AMOUNT; ++i)
    {
        fullPath = path + std::to_string(i) + BGM_FILENAME_EXTENSION; // + 連番数字 + .拡張子
        bgmData[i] = LoadSoundMem(fullPath.c_str());

        if (bgmData[i] < 0)
        {
            printfDx("音声読み込みに失敗_SoundManager_bgm[%d]\n", i);
        }
    }


    path = SOUND_FOLDER_PATH + SE_PATH; // フォルダパス + ファイル名
    fullPath = path;
    for (int i = 0; i < SE_AMOUNT; ++i)
    {
        fullPath = path + std::to_string(i) + SE_FILENAME_EXTENSION; // + 連番数字 + .拡張子
        seData[i] = LoadSoundMem(fullPath.c_str());

        if (seData[i] < 0)
        {
            printfDx("音声読み込みに失敗_SoundManager_se[%d]\n", i);
        }
    }
}

void SoundManager::DeleteAllSound()
{
    // BGM
    for (int i = 0; i < BGM_AMOUNT; ++i)
    {
        DeleteSoundMem(BGM_VOLUME, bgmData[i]);
        bgmData[i] = NULL;
    }

    // SE
    for (int i = 0; i < SE_AMOUNT; ++i)
    {
        DeleteSoundMem(SE_VOLUME, seData[i]);
        seData[i] = NULL;
    }
}

void SoundManager::VolumeChange()
{
    // BGM
    for (int i = 0; i < BGM_AMOUNT; ++i)
    {
        ChangeVolumeSoundMem(BGM_VOLUME, bgmData[i]);
    }

    // SE
    for (int i = 0; i < SE_AMOUNT; ++i)
    {
        ChangeVolumeSoundMem(SE_VOLUME, seData[i]);
    }
}
