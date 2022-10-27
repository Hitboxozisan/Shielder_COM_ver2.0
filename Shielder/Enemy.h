#pragma once

#include "Character.h"

class Enemy final : public Character
{
public:
	//�c��̗�
	enum EnemyState
	{
		FINE,
		CAUTION,
		DENGER
	};

	//�s�����
	enum State
	{
		NONE,		//���݂��Ȃ�
		NORMAL,		//�ʏ�
		ATTACK,		//�U��
		SLIDE,		//���˕Ԃ�
		DAMAGE,		//��e
		DEAD		//���S
	};

	enum AttackType
	{
		ASSAULT = 0,	//�ːi�U��
		BULLET,			//�ʏ�e����
		SLOW_BULLET,	//�x���e����
		JUMP,			//�W�����v
		KICK,			//�L�b�N
		JUDGE,			//�ǂ��ɂ��邩���f
		BACK,			//��ʒ[�ɖ߂�

		ATTACK_AMOUST	//�s���p�^�[����
	};

	Enemy(BulletCreater* const);
	~Enemy();
	void Initialize(EffectManager* const inEffectManager);
	void Update();

	void Draw();
	void OnHitOtherCharacter(const VECTOR& forceDirection, bool just);		//���̃L�����N�^�[�Ɠ�������
	void OnHitShield(const VECTOR& adjust, bool just);						//���ƃL�����N�^�[����������
	void OnHitShieldWithBullet(const VECTOR& adjust, bool just);

	//const bool IsCollidableState() const;
	const float GetTrunk() const { return trunkPoint; }
	const bool IsAlive() const;

	//�f�o�b�O
	const float GetInterval() const { return shotInterval; }

private:
	static const float COLLIDE_RADIUS;
	static const float NORMAL_SPEED;
	static const float DEFENSE_SPEED;
	static const float KICK_SPEED;							//�L�b�N���X�s�[�h
	static const float JUMP_DIRECTION_Y;					//�W�����v���ɏ�����ɉ������
	static const float JUMP_HEIGHT;							//JUMPKICK���̍ő卂�x
	static const float STOP_VELOCITY;
	static const float FRICTION_FORCE;
	static const float GRAVITY;								//�d��
	static const float TRUNK_POINT;							//�̊��Q�[�W
	static const float INCREASE_TRUNK_POINT;				//�̊��Q�[�W������
	static const float ASSAULT_MAGNIFICATION;				//ASSAULT���̌����{��
	static const float BULLET_MAGNIFICATION;				//BULLET���̌����{��
	static const float SLOW_BULLET_MAGNIFICATION;			//SLOW_BULLET���̌����{��
	static const float JUMPKICK_MAGNIFICATION;				//JUMPKICK���̌����{��
	static const float SHOT_INTERVAL;

	float frame;
	float trunkMagnification;		//�h���ꂽ�Ƃ��̑̊��Q�[�W�̌���{��
	int assaultCount;
	float movedDistance;			//�ړ����n�߂Ă���̈ړ���
	float stopTime;					//��~���Ă���̌o�ߎ���
	bool stopMove;					//��~���Ă��邩
	bool currentRightPosition;		//�E���ɂ��邩
	float shotInterval;				//���ˊԊu
	int   shotCount;				//���ˉ�

	void (Enemy::*pUpdate)();				//Update�֐��|�C���^

	VECTOR vec;
	VECTOR returnForce;
	VECTOR jumpPower;
	EnemyState physical;
	State state;
	AttackType attackType;					//�G�̍s���p�^�[��
	AttackType prevType;					//�O��̍s���p�^�[��
	
	//�e��Ԃɉ������X�V����
	void UpdateFine();
	void UpdateCaution();
	void UpdateDenger();
	void UpdateNormal();
	void UpdateAttack();
	void UpdateSlide();
	void UpdateDamage();

	void Move();
	void MoveFinish();
	void Assault();				//�ːi�U��
	void Bullet();				//�e����
	void SlowBullet();
	void Jump();				//�W�����v��v���C���[�Ɍ������ēːi
	void Kick();
	void Back();				//��ʒ[�ɖ߂�
	void Slide();

	void CreateBullet();				//�e�𐶐�����
	void ShootBullet();					//�e�𔭎˂���
	void SetNextAttack();				//���̍s�������肷��
	void CurrentPositionJudge();		//�G�l�~�[����ʂ̉E���ǂ��瑤�ɂ��邩

	void InputAction();
};

