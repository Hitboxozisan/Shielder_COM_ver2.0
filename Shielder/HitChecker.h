#pragma once

class Character;
class Player;
class Enemy;
class Shield;
class Bullet;

class HitChecker final
{
public:
	HitChecker(int inCharacaterAmount);
	~HitChecker();

	void Check(Character **character, Shield *shield, std::list<Bullet*>* bullett);

private:

	void ShieldAndCharacter(Character** character, Shield *shield);
	void CharacterAndCharacter(Character** character);
	void ShieldAndBullet(Character** character, Shield* shield, std::list<Bullet*>* bullet);
	void CharacterAndBullet(Character** character, std::list<Bullet*>* bullet);

	int characterAmount;
	int hitStopTime;
};

