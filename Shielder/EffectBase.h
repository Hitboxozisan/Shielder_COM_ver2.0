#pragma once
class EffectBase
{
public:
	EffectBase();
	virtual ~EffectBase();

	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Activate(VECTOR inPosition) = 0;		//�������ǂ��ɂ�������
	virtual void Deactivate() = 0;
	virtual void Update(VECTOR inPostion, VECTOR inEnemyPosition) = 0;
	virtual void Draw() = 0;

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

