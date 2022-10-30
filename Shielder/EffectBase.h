#pragma once
class EffectBase
{
public:
	EffectBase();
	virtual ~EffectBase();

	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Activate(VECTOR inPosition) = 0;		//ˆø”‚ğ‚Ç‚¤‚É‚©‚µ‚½‚¢
	virtual void Deactivate() = 0;
	virtual void Update(VECTOR inPostion, VECTOR inEnemyPosition) = 0;
	virtual void Draw() = 0;

	bool GetExist() const;			//‘¶İ‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©
protected:
	int effectHandle;
	int playingEffectHandle;
	VECTOR position;
	float frame;
	bool exist;			//‘¶İ‚µ‚Ä‚¢‚é‚©
	int existFrame;		//‘¶İ‚Å‚«‚éc‚èƒtƒŒ[ƒ€
	
private:
	EffectBase(const EffectBase&);
	void operator=(const EffectBase&);
};

