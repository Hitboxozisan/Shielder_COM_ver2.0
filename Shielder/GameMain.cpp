#include "Pch.h"
#include <chrono>
#include <thread>
#include <random>

#include "GameMain.h"

#include "KeyManager.h"
#include "SceneManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Character.h"
#include "Camera.h"
#include "HitChecker.h"
#include "ModelManager.h"
#include "Shield.h"
#include "Bullet.h"
#include "BulletCreater.h"
#include "EnemyAi.h"
#include "Background.h"
#include "Field.h"
#include "UiManager.h"
#include "EffectManager.h"
#include "SoundManager.h"
#include "GuardEffect.h"
#include "Result.h"


const string GameMain::IMAGE_FOLDER_PATH = "Data/Image/";
const string GameMain::RESULT_PATH = "Result";
const string GameMain::FILENAME_EXTENSION = ".png";

const int	GameMain::PLAYER_AMOUNT = 1;
const int	GameMain::ENEMY_AMOUNT = 1;
const int	GameMain::CHARACTER_AMOUNT = PLAYER_AMOUNT + ENEMY_AMOUNT;
const float GameMain::MAX_BULLET_AMOUNT = 8;

GameMain::GameMain(SceneManager* const sceneManager)
	:SceneBase(sceneManager)
	,state(START)
	,pUpdate(nullptr)
	,frame()
	,alpha()
	,pushEnterAlpha()
	,alphaAdd(1)
{
}

GameMain::~GameMain()
{
	if (character != nullptr)
	{
		Finalize();
	}
}

void GameMain::Initialize()
{
	string path = IMAGE_FOLDER_PATH;
	string fullpath = path + RESULT_PATH + FILENAME_EXTENSION;

	//�摜�ǂݍ��݁i�����͂��ƂŕʃN���X�ŏ���������ׂ����j
	resultImageHandle = LoadGraph(fullpath.c_str());
	pushEnterHandle = LoadGraph("Data/Image/Push_Enter.png");			//��ŏ�L�Ɠ���
	if (resultImageHandle < 0)
	{
		printfDx("�ǂݍ��݂Ɏ��s_imageHandle");
	}
	//�V�����t�H���g�f�[�^���쐬
	fontHandle = CreateFontToHandle("Molot", 100, 1, DX_FONTTYPE_ANTIALIASING);

	//�G�t�F�N�g�Ǘ��N���X
	effectManager = new EffectManager();
	effectManager->Initialize();

	//�e�����N���X
	bulletCreater = new BulletCreater(&activeBullet, &deactiveBullet);

	//�L�����N�^�[�N���X
	character = new Character * [CHARACTER_AMOUNT]();

	//�v���C���[
	for (int i = 0; i < PLAYER_AMOUNT; i++)
	{
		character[i] = new Player(bulletCreater);
		character[i]->Initialize(effectManager);
	}

	//�G�l�~�[
	for (int i = PLAYER_AMOUNT; i < CHARACTER_AMOUNT; ++i)
	{
		character[i] = new Enemy(bulletCreater);
		character[i]->Initialize(effectManager);
	}

	//�G�̒e
	for (int i = 0; i < MAX_BULLET_AMOUNT; ++i)
	{
		deactiveBullet.push_back( new Bullet() );
		deactiveBullet.back()->Initialize();
	}
	
	//�J�����N���X
	camera = new Camera();
	camera->Initialize();
	camera->SetPosition(character);

	//�w�i�N���X
	background = new Background;
	background->Initialize();

	field = new Field;
	field->Initialize();
	
	//UI�Ǘ��N���X
	uiManager = new UiManager;
	uiManager->Initialize();

	//�����蔻��N���X
	hitchecker = new HitChecker(CHARACTER_AMOUNT);

	EnemyAi::GetInstance().Initialize(character);
}

void GameMain::Finalize()
{
	for (int i = 0; i < CHARACTER_AMOUNT; ++i)
	{
		character[i]->Finalize();
		SafeDelete(character[i]);
	}
}

void GameMain::Activate()
{
	for (int i = 0; i < CHARACTER_AMOUNT; ++i)
	{
		character[i]->Initialize(effectManager);
	}

	state = START;
	pUpdate = &GameMain::UpdateStart;

#ifdef DEBUG
	state = START;
	pUpdate = &GameMain::UpdateStart;
#endif
}

void GameMain::Deactivate()
{
	for (int i = 0; i < CHARACTER_AMOUNT; ++i)
	{
		
	}

	state = START;
}

void GameMain::Update()
{
	//ESC�������ꂽ��^�C�g����
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_ESCAPE))
	{
		parent->SetNextScene(SceneManager::TITLE);
	}

	//�����������
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)();	//��Ԃ��Ƃ̍X�V����
	}

	
	//guardEffect->Update();
	//background->Update();

	++frame;
}

void GameMain::Draw()
{
	background->Draw();		//�w�i�`��
	field->Draw();			//�t�B�[���h�`��

	uiManager->Draw(state, character[0]->GetHitPoint(), character[0]->GetTrunkPoint(), character[1]->GetTrunkPoint());


	for (auto itr = activeBullet.begin(); itr != activeBullet.end(); ++itr)
	{
		(*itr)->Draw();
	}

	for (int i = 0; i < CHARACTER_AMOUNT; ++i)
	{
		character[i]->Draw();
	}

	//��ʂ��t�F�[�h�A�E�g
	if (state == GAME_OVER || state == RESULT)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	//���U���g��ʂ̕\��
	if (state == RESULT)
	{
		//���U���g�摜�`��
		DrawExtendGraph(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, resultImageHandle, TRUE);
		pushEnterAlpha += alphaAdd;						//���X�ɓ����ɂ���
		if (pushEnterAlpha == 0 || pushEnterAlpha == 255)
		{
			alphaAdd = -alphaAdd;
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, pushEnterAlpha);
		DrawExtendGraph(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, pushEnterHandle, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, pushEnterAlpha);
		DrawFormatStringToHandle(1100, 400, GetColor(255, 255, 255), fontHandle, "%d", lifeScore);
		DrawFormatStringToHandle(1100, 560, GetColor(255, 255, 255), fontHandle, "%d", trunkScore);
		DrawFormatStringToHandle(1100, 870, GetColor(255, 255, 255), fontHandle,  "%d", totalScore);
	}

	effectManager->Draw(character[0]->GetPosition());
	
	//UI�f�o�b�O
	DrawFormatString(50, 70, GetColor(255, 255, 255), "P::position.x : %f", character[0]->GetPosition().x);
	DrawFormatString(50, 90, GetColor(255, 255, 255), "E::position.x : %f", character[1]->GetPosition().x);
	DrawFormatString(50, 110, GetColor(255, 255, 255), "Velocity.x : %f", character[0]->GetVelocity().x);
	DrawFormatString(50, 130, GetColor(255, 255, 255), "Velocity.y : %f", character[0]->GetVelocity().y);
	DrawFormatString(50, 150, GetColor(255, 255, 255), "Velocity.z : %f", character[0]->GetVelocity().z);
	DrawFormatString(50, 170, GetColor(255, 255, 255), "ST : %f", character[0]->GetTrunkPoint());
	DrawFormatString(50, 190, GetColor(255, 255, 255), "HP : %f", character[0]->GetHitPoint());

	//�J�����̌��ݒn��\��
	DrawFormatString(300, 70, GetColor(255, 255, 255), "Camera.X : %f\nCamera.Y : %f\nCamera.Z : %f", camera->GetCameraPosition().x, camera->GetCameraPosition().y, camera->GetCameraPosition().z);

}

void GameMain::UpdateStart()
{
	if (frame > 100)
	{
		SoundManager::GetInstance().PlayBgm( SoundManager::MAIN, false);
		//camera->StartCamera(character);
		frame = 0;
		state = GAME;
		pUpdate = &GameMain::UpdateGame;
	}
}

void GameMain::UpdateGame()
{
	for (int i = 0; i < CHARACTER_AMOUNT; ++i)
	{
		character[i]->Update();
	}

	//�A�N�e�B�u�Ȓe�̍X�V����
	for (auto itr = activeBullet.begin(); itr != activeBullet.end();)
	{
		//�����Ă������A�N�e�B�u���X�g
		if ((*itr)->Update() == false)
		{
			(*itr)->Deactivate();
			deactiveBullet.push_back(*itr);
			itr = activeBullet.erase(itr);
		}
		else
		{
			++itr;
		}
	}

	//�v���C���[������ł����
	if (character[0]->IsAlive() == false ||
		character[1]->IsAlive() == false)
	{
		frame = 0.0f;
		alpha = 0;
		state = GAME_OVER;
		pUpdate = &GameMain::UpdateGameOver;
	}

	effectManager->Update(character[0]->GetPosition(), character[1]->GetPosition());
	hitchecker->Check(character, character[0]->GetShieldPointer(), &activeBullet);
	camera->Update(character);
}

void GameMain::UpdateGameOver()
{
	//�G�l�~�[�����񂾏ꍇ�͉��o���o��
	//if (character[1]->IsAlive() == false)
	//{
	//	//camera->PlayerZoom(character);
	//	effectManager->CreatePlayerLaser(character[0]->GetPosition());
	//	if (frame >= 850)
	//	{
	//		alpha++;
	//	}
	//}

	if (frame <= 300 || character[1]->IsAlive() == false)
	{
		//���X�ɈÂ����Ă���
		alpha++;
	}

	//alpah�l�𑝉���������
	if(alpha >= 200)
	{
		state = RESULT;
		frame = 0;
		pUpdate = &GameMain::UpdateResult;
		//parent->SetNextScene(SceneManager::RESULT);
		//return;
	}
	
	effectManager->Update(character[0]->GetPosition(), character[1]->GetPosition());
}

void GameMain::UpdateResult()
{
	//�����p�ϐ�
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<int> next(0, 999999999 - 1);

	//���t���[���o�߂���܂�
	//�e�X�R�A�������_���Ȑ��l��\��������
	//�t���[���Ŕ��f�ł͂Ȃ��J�E���g�Ŕ��f�̂ق����ǂ�����
	if (frame <= 240)
	{
		lifeScore = next(eng);
		trunkScore = next(eng);
		totalScore = next(eng);
	}
	else if (frame <= 300)
	{
		//SoundManager::GetInstance().SetSePlayFlag(SoundManager::DECIDE_SCORE);
		lifeScore = character[0]->GetHitPoint() * 15000;
		trunkScore = next(eng);
		totalScore = next(eng);
	}
	else if (frame <= 360)
	{
		SoundManager::GetInstance().SetSePlayFlag(SoundManager::DECIDE_SCORE);
		trunkScore = character[1]->GetTrunkPoint() * 20000;
		totalScore = next(eng);
	}
	else
	{
		//SoundManager::GetInstance().SetSePlayFlag(SoundManager::DECIDE_SCORE);
		totalScore = lifeScore + trunkScore;
	}


	//�X�y�[�X�L�[�������͈�莞�Ԍo�߂Ń^�C�g����ʂɈڍs����
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_RETURN) ||
		frame >= 1200)
	{
		Deactivate();
		parent->SetNextScene(SceneManager::TITLE);
	}
}
