#include "Pch.h"

#include "GuardEffect.h"

#include "ModelManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "DeltaTime.h"


// ���C����`���͈�
#define LINE_AREA_SIZE			15000.0f
// ���C���̐�
#define LINE_NUM			50


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(IS_WINDOW_MODE);
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16);

	SetUseLighting(TRUE);

	SetDrawScreen(DX_SCREEN_BACK);

	SetUseDirect3DVersion(DX_DIRECT3D_11);

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//Effekseer������������
	//�����͉�ʂɕ\������ő�p�[�e�B�N����
	if (Effekseer_Init(2200) == -1)
	{
		DxLib_End();
		return -1;
	}

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
	// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
	// �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Effekseer��2D�`��̐ݒ������B
	//Effekseer_Set2DSetting(SCREEN_WIDTH, SCREEN_HEIGHT);

	// Z�o�b�t�@��L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetUseZBuffer3D(TRUE);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetWriteZBuffer3D(TRUE);

	ModelManager::GetInstance();

	SceneManager* sceneManager = new SceneManager();
	sceneManager->Initialize();

	int nowCount, prevCount;
	nowCount = prevCount = GetNowCount();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//deltaTime�̌v��
		float deltaTime;
		nowCount = GetNowCount();
		deltaTime = (nowCount - prevCount) / 1000.0f;
		DeltaTime::GetInstace().SetDeltaTime(deltaTime);
		KeyManager::GetInstance().Update();		//���͏���

		sceneManager->Update();					//�e�V�[���ɉ������X�V����
		
		//��ʍX�V����
		ClearDrawScreen();
	

		sceneManager->Draw();					//�e�V�[���ɉ������`�揈��

#ifdef DEBUG
		
#endif // DEBUG

		// �ʒu�֌W��������悤�ɒn�ʂɃ��C����`�悷��
		{
			int i;
			VECTOR Pos1;
			VECTOR Pos2;

			SetUseZBufferFlag(TRUE);

			Pos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
			Pos2 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, LINE_AREA_SIZE / 2.0f);
			for (i = 0; i <= LINE_NUM; i++)
			{
				DrawLine3D(Pos1, Pos2, GetColor(255, 255, 255));
				Pos1.x += LINE_AREA_SIZE / LINE_NUM;
				Pos2.x += LINE_AREA_SIZE / LINE_NUM;
			}

			Pos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
			Pos2 = VGet(LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
			for (i = 0; i < LINE_NUM; i++)
			{
				DrawLine3D(Pos1, Pos2, GetColor(255, 255, 255));
				Pos1.z += LINE_AREA_SIZE / LINE_NUM;
				Pos2.z += LINE_AREA_SIZE / LINE_NUM;
			}

			SetUseZBufferFlag(FALSE);
		}

		ScreenFlip();
		prevCount = nowCount;
	}

	//Effekseer���I������
	Effkseer_End();

	// �c�w���C�u�����g�p�̏I������
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}