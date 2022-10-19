#pragma once

#include "Character.h"

class Shield;

class Player final : public Character
{
public:
	enum State
	{
		NONE,		//���݂��Ȃ�
		NORMAL,		//�ʏ�
		DEFENSE,	//�h��
		SLIDE,		//�h�䎞�ɐڐG
		DAMAGE,		//��e
		RIGOR,		//�d��
		DEAD		//���S
	};
	
	Player(BulletCreater* const);
	~Player();

	void Initialize();
	void Update();
	void Draw();

	void ReleaseInvincible();

	void BreakShield();										//���̑ϋv�l�����E�ɒB����

	void OnHitOtherCharacter(const VECTOR& forceDirection);
	void OnHitShield(const VECTOR& adjust);					//���ƃL�����N�^�[����������
	void OnHitShieldWithBullet(const VECTOR& adjust);

	const State GetState() const { return state; }
	const bool IsDefense()const { return isDefense; }
	//const bool IsCollidableState() const;
	const float GetTrunk() const { return trunkPoint; }
	const bool IsAlive() const;

	//�f�o�b�O�p
	const float GetInvincibleTime() const { return invincibleTime; }

private:
	//Player();
	Player(const Player&);			//�R�s�[�R���X�g���N�^
	void operator=(const Player&);	//�R�s�[������Z�q

	static const float HIT_POINT;							//�̗�
	static const float DECREMENT_HIT_POINT;					//�̗͂̌�����
	static const float COLLIDE_RADIUS;						//�����蔻�苅���a
	static const float NORMAL_SPEED;
	static const float DEFENSE_SPEED;
	static const float HIT_OTHER_CHARACTER_DIRECTION_Y;		//�G�L�����Ɠ�����������Y�����̌���
	static const float JUST_DEFENSE_TIME;					//�W���X�g�K�[�h�Ɣ��f���鎞��
	static const float NORMAL_DEFENSE_TIME;					//�m�[�}���K�[�h�Ɣ��f���鎞��
	static const float STOP_VELOCITY;						//�~�܂����Ɣ��f���鑬�x
	static const float GRAVITY;								//�d��
	static const float FRICTION_FORCE;						//���C��
	static const float TRUNK_POINT;							//�̊��Q�[�W
	static const float INCREASE_TRUNK_POINT;				//�̊��Q�[�W������
	static const float RIGOR_TIME;							//�d������
	static const float INVINCIBLE_TIME;						//���G����
	static const float DEFENCE_INTERVAL;					//���ɖh��ł���܂ł̎���

	State state;

	float defenceInterval;			//����W�J���Ă���̌o�ߎ���
	float justDefenceTime;			//�W���X�g�K�[�h�Ɣ��f���鎞��
	float normalDefenceTime;		//�m�[�}���K�[�h�Ɣ��f���鎞��
	

	bool isDefense;

	void (Player::* pUpdate)();		//Update�֐��|�C���^



	//�e��Ԃ̍X�V����
	void UpdateNormal();
	void UpdateDefence();
	void UpdateSlide();
	void UpdateDamage();
	void UpdateRigor();

	void Move();
	void MoveFinish();
	void Jump();
	void Defense();
	void Slide();		//�W���X�g�K�[�h�ȊO�ŐڐG
	void Damage();
	void InputAction();
	void CreateShield();
};
