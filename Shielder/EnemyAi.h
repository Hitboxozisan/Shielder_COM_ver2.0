#pragma once

class Character;

class EnemyAi
{
public:
	EnemyAi();
	~EnemyAi();

	static EnemyAi& GetInstance();

	void Initialize(Character** inCharacter);

	bool RangeWithPlayerNear();			//プレイヤーとの距離が近いか
	VECTOR DeterminingLandingPoint();	//プレイヤーの位置を返す

private:
	static const float NEAR_DISTANCE;		//近いと判断する距離

	Character** character;
};

