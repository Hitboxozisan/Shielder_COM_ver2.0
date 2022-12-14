#pragma once

using namespace My3dLib;

namespace ShieldState
{
	//状態
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
	void Initialize();
	void Finalize();
	void Update(const VECTOR& inPosition, const VECTOR& inDirection, const VECTOR& inPrevDirection);
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
	float defenseCount;			//盾を出してからの経過時間

	ShieldState::State state;
	VECTOR position;
	VECTOR direction;
	VECTOR prevDirection;
	VECTOR DistanceToPlyaer;

	Sphere collisionSphere;
};

