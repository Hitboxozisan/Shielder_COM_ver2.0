#pragma once

#include "Mover.h"

using namespace My3dLib;

class Shield;
class Bullet;
class BulletCreater;
class EffectManager;

//���
//namespace CharacterState
//{
//	enum State
//	{
//		NONE,		//���݂��Ȃ�
//		NORMAL,		//�ʏ�
//		ATTACK,		//�U��
//		DEFENSE,	//�h��
//		SLIDE,		//�h�䎞�ɐڐG
//		DAMAGE,		//��e
//		DEAD		//���S
//	};
//}

class Character : public Mover
{
public:

	Character(BulletCreater* const);
	virtual ~Character();

	virtual void Initialize(EffectManager* const inEffectManager) = 0;
	void Finalize();

	virtual void Update() = 0;
	virtual void Draw() = 0;
	void MoveFinish();				//�ړ��\��n�Ɏ��ۂɈړ�����

	//�����蔻��֌W�֐�
	virtual void OnHitOtherCharacter(const VECTOR& forceDirection) = 0;		//���̃L�����N�^�[�Ɠ�������
	virtual void OnHitShield(const VECTOR& adjust) = 0;						//���ƃL�����N�^�[����������
	virtual void OnHitShieldWithBullet(const VECTOR& adjust) = 0;			//���ƒe���ڐG����

	//�Q�b�^�[
	const float& GetHitPoint() const { return hitPoint; }							//���݂�hitPoint��Ԃ�
	const VECTOR& GetNextPosition() const  { return nextPosition; }					//�ړ��\��ʒu��Ԃ�
	const VECTOR GetCollisionShere() const { return collisionSphere.worldCenter; }	//�����蔻�苅��Ԃ�
	const float GetCollisionRadius() const { return collisionSphere.radius; }		//�����蔻�苅�̔��a��Ԃ�
	const bool IsCollidableState() const;											//�����ƐڐG�ł����Ԃ�
	const float GetInvicibleTime() const { return invincibleTime; }					//���G���Ԃ̌o�ߎ��Ԃ�Ԃ�
	virtual const bool IsAlive() const = 0;

	Shield* GetShieldPointer() const { return shield; }
	Bullet* GetBulletPointer() const { return bullet; }

	//�f�o�b�O�p
	const VECTOR& GetVelocity() const { return velocity; }		// ���݂̑��x�A�����x�A������Ԃ�
	const float& GetTrunkPoint() const { return trunkPoint; }	// ���݂̑̊��Q�[�W��Ԃ�

protected:
	VECTOR inputDirection;

	int   id;				// �L�����̎��ʔԍ�
	float hitPoint;			// �L�����̗̑�
	float trunkPoint;		// �̊��Q�[�W�̗�
	float speed;			// �ړ����x
	VECTOR velocity;		// ���݂̑��x�A�����x�A����
	VECTOR nextPosition;	// �ړ��\��̃|�W�V����
	VECTOR nextDirction;	// �ړ���̗\��̌���
	VECTOR prevPosition;	// �O�t���[���̃|�W�V����
	VECTOR prevDirection;	// �O�t���[���̌���
	bool   noDrawFrame;		// �`�悵�Ȃ��t���[����
	float invincibleTime;	// ���G����

	//CharacterState::State state;	

	Shield* shield;			//���̃C���X�^���X

	Bullet* bullet;			//�e�̃C���X�^���X
	BulletCreater* const bulletCreater;		//�e�����N���X�̃|�C���^

	Sphere collisionSphere;	//�����蔻�苅
private:
	//�萔
	/*static const float COLLIDE_RADIUS;
	static const float NORMAL_SPEED;
	static const float DEFENSE_SPEED;*/
	
	

	virtual void InputAction() = 0;
};

