#include "Pch.h"
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
#include "Background.h"
#include "UiManager.h"
#include "EffectManager.h"
#include "GuardEffect.h"

const int	GameMain::PLAYER_AMOUNT = 1;
const int	GameMain::ENEMY_AMOUNT = 1;
const int	GameMain::CHARACTER_AMOUNT = PLAYER_AMOUNT + ENEMY_AMOUNT;
const float GameMain::MAX_BULLET_AMOUNT = 3;

GameMain::GameMain(SceneManager* const sceneManager)
	:SceneBase(sceneManager)
	,state(START)
	,pUpdate(nullptr)
	,frame()
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
	//�J�����N���X
	camera = new Camera();
	camera->Initialize();
	camera->SetPosition(character);

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
		deactiveBullet.push_back(new Bullet());
		deactiveBullet.back()->Initialize();
	}
	
	//�w�i�N���X
	background = new Background;
	background->Initialize();

	
	//UI�Ǘ��N���X
	uiManager = new UiManager;
	uiManager->Initialize();

	//�����蔻��N���X
	hitchecker = new HitChecker(CHARACTER_AMOUNT);
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

	//guardEffect->Activate(character[0]->GetPosition());

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

	++frame;
}

void GameMain::Draw()
{
	background->Draw();		//�w�i�`��
	uiManager->Draw(state, character[0]->GetHitPoint(), character[0]->GetTrunkPoint(), character[1]->GetTrunkPoint());

	
	for (auto itr = activeBullet.begin(); itr != activeBullet.end(); ++itr)
	{
		(*itr)->Draw();
	}

	for (int i = 0; i < CHARACTER_AMOUNT; ++i)
	{
		character[i]->Draw();
	}

	effectManager->Draw();

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
		state = GAME_OVER;
		pUpdate = &GameMain::UpdateGameOver;
	}

	effectManager->Update();
	hitchecker->Check(character, character[0]->GetShieldPointer(), character[1]->GetBulletPointer());
	camera->Update(character);
}

void GameMain::UpdateGameOver()
{
	
	if (frame <= 255)
	{
		SetDrawBright(255 - frame, 255 - frame, 255 - frame);
	}
	else
	{

		parent->SetNextScene(SceneManager::RESULT);
		return;

		//���U���g��ʕ`��
		//DrawGraph(0, 0, resultImageHandle, TRUE);
	}


}

void GameMain::UpdateResult()
{
}
