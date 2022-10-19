#pragma once
class ObjectBase
{
public:
	ObjectBase();
	virtual ~ObjectBase();

	const VECTOR& GetPosition() const { return position; }
	const VECTOR& GetDirection() const { return direction; }
	float GetCollideRadius() const { return collideRadius; }
protected:
	int modelHandle;
	VECTOR position;
	VECTOR direction;

	float collideRadius;
private:

};

