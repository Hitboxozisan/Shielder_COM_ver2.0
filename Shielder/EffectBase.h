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

