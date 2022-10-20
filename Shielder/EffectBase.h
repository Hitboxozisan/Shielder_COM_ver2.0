#pragma once
class EffectBase
{
public:
	EffectBase();
	virtual ~EffectBase();

	void Initialize();
	void Finalize();
	virtual void Activate(VECTOR inPosition) = 0;
	void Deactivate();
	void Update();
	void Draw();

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

