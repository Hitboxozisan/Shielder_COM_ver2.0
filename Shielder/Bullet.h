#pragma once

#include "Mover.h"

class Bullet final : public Mover
{
public:
	enum State
	{
		NONE,			//���݂��Ȃ�
		NORMAL,			//���ł���i�ʏ�j
		SLOW			//���ł���i�������j
	};

	Bullet();
	~Bullet();

	void Initialize();
	void Finalize();
	void Activate(const VECTOR& inPosition, const VECTOR& inDirection);
	void Deactivate();
	bool Update();
	void Draw();

	void Shoot(int attackType);

	void SetToFrontOfEnemy(const VECTOR& inPosition, const VECTOR& inDirection);

	State GetState() const;
	bool IsCollidableState() const;

	const float GetCollisionRadius() const { return collisionSphere.radius; }

	void OnOutField();			//�t�B�[���h�O�ɏo��
	void OnHitBreak();			//�����ɓ������ĉ���

private:
	//�萔
	static const float NORMAL_SPEED;					  //�ʏ틅�ړ����x
	static const float SLOW_SPEED;						  //�x���e�ړ����x
	static const float SCALE_BY_DIRECTION_FOR_CORRECTION; // �ʒu�␳�p�Ɍ����x�N�g���Ɋ|����{��
	static const float COLLIDE_RADIUS;			   		  //�����蔻�苅���a

	State state;		//���݂̏��
	VECTOR velocity;	//���݂̑��x�A�����x�A���������A�}�C�i�X�ɂ��Ȃ�
	float speed;		//���݂̑��x

	My3dLib::Sphere collisionSphere;			//�����蔻��p��

	void Move();		//�ړ�����
};

