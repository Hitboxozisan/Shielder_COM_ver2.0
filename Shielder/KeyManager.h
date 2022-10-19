#pragma once
class KeyManager final
{
public:
    static KeyManager& GetInstance();// �A�h���X��Ԃ�

    void Update();

    bool CheckPressed(int keyCode) const;     // �L�[��������Ă��邩
    bool CheckJustPressed(int keyCode) const; // �L�[�������ꂽ�u�Ԃ�
    bool CheckRelease(int keyCode) const;     // �L�[�������ꂽ��

    int  GetKeyReleaseCount() const; // �A���L�[���͂��Ȃ��J�E���g��Ԃ�
private:
    // �O���ł̎��s���֎~����
    KeyManager();                        // �R���X�g���N�^
    KeyManager(const KeyManager&);     // �R�s�[�R���X�g���N�^
    void operator=(const KeyManager&); // ������Z�q
    ~KeyManager();                       // �f�X�g���N�^

    char currentState[256];          // ���݂̃L�[�������
    char prevState[256];             // �O�t���[���̃L�[�������
    int  allKeyReleaseCount;           // �A���L�[���͂��Ȃ��J�E���g
};

