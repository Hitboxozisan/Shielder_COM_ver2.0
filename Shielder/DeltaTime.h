#pragma once
class DeltaTime
{
public:
	DeltaTime();
	~DeltaTime();
	static DeltaTime& GetInstace();

	void  SetDeltaTime(float delta) { deltaTime = delta; };
	inline float GetDeltaTime() { return deltaTime; };
private:
	float deltaTime;
};

