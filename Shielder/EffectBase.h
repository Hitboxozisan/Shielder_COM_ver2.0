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

	bool GetExist() const;			//���݂��Ă��邩�ǂ���
protected:
	int effectHandle;
	int playingEffectHandle;
	VECTOR position;
	float frame;
	bool exist;			//���݂��Ă��邩
	int existFrame;		//���݂ł���c��t���[��
	
private:
	EffectBase(const EffectBase&);
	void operator=(const EffectBase&);
};

