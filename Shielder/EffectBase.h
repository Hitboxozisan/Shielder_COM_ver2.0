#pragma once
class EffectBase
{
public:
	EffectBase();
	virtual ~EffectBase();

	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Activate(VECTOR inPosition) = 0;
	virtual void Deactivate() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	bool GetExist() const;			//存在しているかどうか
protected:
	int effectHandle;
	int playingEffectHandle;
	VECTOR position;
	float frame;
	bool exist;			//存在しているか
	int existFrame;		//存在できる残りフレーム
	
private:
	EffectBase(const EffectBase&);
	void operator=(const EffectBase&);
};

