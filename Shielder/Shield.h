#pragma once

using namespace My3dLib;

namespace ShieldState
{
	//èÛë‘
	enum State
	{
		NONE,
		DEPLOYMENT
	};
}

class Shield final
{
public:
	static Shield& GetInstance();
	
	Shield();
	~Shield();
	void Create();
	void Activate(const VECTOR& inPosition, const VECTOR& inDirection, const VECTOR& inPrevDirection);
	void Deactivate();
	void Initialize(const VECTOR& inDirection);
	void Finalize();
	void Update();
	void Draw();

	void DecrementTrunk();
	void OnHitOtherCharacter();

	ShieldState::State GetState() const { return state; }
	const VECTOR GetPosition() const { return position; }
	const float GetDefenseCount() const { return defenseCount; }
	const float GetCollisionRadius() const { return collisionSphere.radius; }
	

private:
	static const float SCALE_BY_DIRECTION_FOR_CORRECTION;
	static const float COLLISION_SHIELD_RADIUS;
	static const float COLLISION_SHIELD_HEIGHT;
	


	int modelHandle;
	float defenseCount;			//èÇÇèoÇµÇƒÇ©ÇÁÇÃåoâﬂéûä‘

	ShieldState::State state;
	VECTOR position;
	VECTOR direction;
	VECTOR prevDirection;
	VECTOR DistanceToPlyaer;

	Sphere collisionSphere;
};

