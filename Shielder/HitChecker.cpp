#include "Pch.h"
#include "HitChecker.h"

#include "GameDefine.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "Shield.h"
#include "Bullet.h"
#include "SoundManager.h"

HitChecker::HitChecker(int inCharacaterAmount)
	:characterAmount(inCharacaterAmount)
	,hitStopTime(0.0f)
{
}

HitChecker::~HitChecker()
{
}

void HitChecker::Check(Character** character, Shield *shield, std::list<Bullet*>* bullet)
{
	CharacterAndCharacter(character);
	ShieldAndCharacter(character, shield);
	ShieldAndBullet(character, shield, bullet);
	CharacterAndBullet(character, bullet);

	character[0]->MoveFinish();
	character[1]->MoveFinish();
}

/// <summary>
/// 盾とエネミーの当たり判定
/// </summary>
/// <param name="character"></param>
/// <param name="shield"></param>
void HitChecker::ShieldAndCharacter(Character** character, Shield *shield)
{
	//防御していなければ処理しない
	if (shield->GetState() != ShieldState::NONE)
	{
		VECTOR shieldPos = character[0]->GetPosition();
		shieldPos.y = 0.0f;

		VECTOR characterOtherPos = character[1]->GetPosition();
		characterOtherPos.y = 0.0f;

		VECTOR sub = VSub(shieldPos, characterOtherPos);
		//sub.y = 0.0f;

		float length = VSize(sub);
		
		//盾と敵が接触したら
		if (HitCheck_Sphere_Sphere(shield->GetPosition(), shield->GetCollisionRadius(),
			character[1]->GetPosition(), character[1]->GetCollisionRadius()) &&
			character[0]->IsCollidableState())
		{
			SoundManager::GetInstance().SetSePlayFlag(SoundManager::SHIELD_HIT);
			//printfDx("HitShield");
			sub = VScale(sub, 1.0f);				//吹き飛ばす方向は逆方向
			VECTOR forceDirection = VNorm(sub);
			character[0]->OnHitShield(forceDirection, character[0]->IsJust());
			character[1]->OnHitShield(forceDirection, character[0]->IsJust());
			WaitTimer(hitStopTime);					//ヒットストップ
		}
	}
}

/// <summary>
/// プレイヤーとエネミーの当たり判定
/// </summary>
/// <param name="character"></param>
void HitChecker::CharacterAndCharacter(Character** character)
{
	VECTOR characterPos = character[0]->GetPosition();
	characterPos.y = 0.0f;

	VECTOR characterOtherPos = character[1]->GetPosition();
	characterOtherPos.y = 0.0f;

	VECTOR sub = VSub(characterPos, characterOtherPos);
	//sub.y = 0.0f;

	float length = VSize(sub);

	if (HitCheck_Sphere_Sphere(character[0]->GetPosition(), character[0]->GetCollisionRadius(),
		character[1]->GetPosition(), character[1]->GetCollisionRadius()) &&
		character[0]->IsCollidableState())
	{
		SoundManager::GetInstance().SetSePlayFlag(SoundManager::CHARACTER_HIT);
		sub = VScale(sub, 1.0f);		//吹き飛ばす方向は逆方向
		VECTOR forceDirection = VNorm(sub);
		character[0]->OnHitOtherCharacter(forceDirection, character[0]->IsJust());
		character[1]->OnHitOtherCharacter(forceDirection, character[0]->IsJust());
		WaitTimer(hitStopTime);			//ヒットストップ
	}
}

/// <summary>
/// 盾と弾の当たり判定
/// </summary>
/// <param name="character"></param>
/// <param name="bullet"></param>
void HitChecker::ShieldAndBullet(Character** character, Shield* shield, std::list<Bullet*>* bullet)
{
	for (auto itr = bullet->begin(); itr != bullet->end(); ++itr)
	{
		//防御しているかつ弾が存在しているなら処理する
		if (shield->GetState() != ShieldState::NONE && bullet != nullptr)
		{
			VECTOR shieldPos = character[0]->GetPosition();
			shieldPos.y = 0.0f;

			VECTOR bulletPos = (*itr)->GetPosition();
			bulletPos.y = 0.0f;

			VECTOR sub = VSub(shieldPos, bulletPos);
			//sub.y = 0.0f;

			float length = VSize(sub);

			if (HitCheck_Sphere_Sphere(shield->GetPosition(), shield->GetCollisionRadius(),
				(*itr)->GetPosition(), (*itr)->GetCollisionRadius()) &&
				character[0]->IsCollidableState() && (*itr)->IsCollidableState())
			{
				SoundManager::GetInstance().SetSePlayFlag(SoundManager::SHIELD_HIT);
				sub = VScale(sub, 1.0f);		//吹き飛ばす方向は逆方向
				VECTOR forceDirection = VNorm(sub);
				character[0]->OnHitShield(forceDirection, character[0]->IsJust());
				character[1]->OnHitShieldWithBullet(forceDirection, character[0]->IsJust());
				(*itr)->OnHitBreak();
				WaitTimer(hitStopTime);				//ヒットストップ
			}
		}
	}
}

/// <summary>
/// プレイヤーと弾の当たり判定
/// </summary>
/// <param name="character"></param>
/// <param name="bullet"></param>
void HitChecker::CharacterAndBullet(Character** character, std::list<Bullet*>* bullet)
{
	for (auto itr = bullet->begin(); itr != bullet->end(); ++itr)
	{
		if (bullet != nullptr)
		{
			VECTOR characterPos = character[0]->GetPosition();
			characterPos.y = 0.0f;

			VECTOR characterOtherPos = character[1]->GetPosition();
			characterOtherPos.y = 0.0f;

			VECTOR sub = VSub(characterPos, characterOtherPos);
			//sub.y = 0.0f;

			float length = VSize(sub);

			if (HitCheck_Sphere_Sphere(character[0]->GetPosition(), character[0]->GetCollisionRadius(),
				(*itr)->GetPosition(), (*itr)->GetCollisionRadius()) &&
				character[0]->IsCollidableState() && (*itr)->IsCollidableState())
			{
				SoundManager::GetInstance().SetSePlayFlag(SoundManager::BULLET_HIT);
				sub = VScale(sub, 1.0f);		//吹き飛ばす方向は逆方向
				VECTOR forceDirection = VNorm(sub);
				character[0]->OnHitOtherCharacter(forceDirection, character[0]->IsJust());
				(*itr)->OnHitBreak();
				WaitTimer(hitStopTime);			//ヒットストップ
			}
		}
	}
}
