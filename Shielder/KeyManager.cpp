#include "KeyManager.h"
#include "Pch.h"

#include <chrono>

//=========================
// �R���X�g���N�^
//=========================
KeyManager::KeyManager()
    : currentState()
    , prevState()
    , allKeyReleaseCount()
{
    // �����Ȃ�
}
//=========================
// �R�s�[�R���X�g���N�^
//=========================
KeyManager::KeyManager(const KeyManager&)
{
    // �g�p���Ȃ�
}
//=========================
// ������Z�q
//=========================
void KeyManager::operator=(const KeyManager&)
{
    // �g�p���Ȃ�
}

//=========================
// �f�X�g���N�^
//=========================
KeyManager::~KeyManager()
{
    // �����Ȃ�
}

//=========================
// �A�h���X�����ƎQ�ƕԂ�
//=========================
KeyManager& KeyManager::GetInstance()
{
    static KeyManager keyManager;
    return keyManager;
}

//=========================
// �X�V����
//=========================
void KeyManager::Update()
{
    for (int i = 0; i < 256; ++i)
    {
        prevState[i] = currentState[i]; // prev���X�V
    }

    GetHitKeyStateAll(currentState);  // current���X�V

    // �����L�[��������Ă�����J�E���g���Z�b�g
    for (int i = 0; i < 256; ++i)
    {
        if (currentState[i])
        {
            allKeyReleaseCount = 0;
            return;
        }
    }

    ++allKeyReleaseCount;
}

//=========================
// �L�[��������Ă��邩
//=========================
bool KeyManager::CheckPressed(int keyCode) const
{
    if (currentState[keyCode] == 0)
    {
        return false;   // ���t���[���ŉ�����Ă��Ȃ�
    }
    return true;    // ���t���[���ŉ�����Ă���
}

//=========================
// �L�[�����߂ĉ����ꂽ�u�Ԃ�
//=========================
bool KeyManager::CheckJustPressed(int keyCode) const
{
    if (prevState[keyCode] == 1)
    {
        return false;   // �O�t���[���ŉ�����Ă���
    }
    if (currentState[keyCode] == 0)
    {
        return false;   // ���t���[���ŉ�����Ă��Ȃ�
    }

    return true;    // ���t���[���ŏ��߂ĉ����ꂽ
}

//=========================
// �L�[�������ꂽ��
//=========================
bool KeyManager::CheckRelease(int keyCode) const
{
    if (prevState[keyCode] == 0)
    {
        return false;   // �O�t���[���ŉ�����Ă��Ȃ�
    }
    if (currentState[keyCode] == 1)
    {
        return false;   // ���t���[���ŉ�����Ă���
    }

    return true;    // ���t���[���ŃL�[�͗����ꂽ
}

//=========================
// �O��̃L�[���͂���̃J�E���g
//=========================
int KeyManager::GetKeyReleaseCount() const
{
    return allKeyReleaseCount;
}
