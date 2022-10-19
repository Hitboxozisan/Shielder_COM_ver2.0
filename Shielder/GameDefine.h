#pragma once

extern const bool IS_WINDOW_MODE;		//�E�B���h�E���[�h��

extern const int  SCREEN_WIDTH;			//�E�B���h�E�̕�
extern const int  SCREEN_HEIGHT;		//�E�B���h�E�̍���

extern const int SCREEN_LEFTMOST;		//��ʍ��[���W
extern const int SCREEN_RIGHTMOST;		//��ʉE�[���W

extern const int SCREEN_CENTER;			//��ʒ��S���W

extern const VECTOR ZERO_VECTOR;		//�[���x�N�g��

extern const VECTOR RIGHT;
extern const VECTOR LEFT;


template <typename T>
inline void SafeDelete(T*& p)   // �|�C���^�̎Q�Ɠn��
{
    // NULL�`�F�b�N�͕s�v
    delete (p);
    (p) = nullptr;

}