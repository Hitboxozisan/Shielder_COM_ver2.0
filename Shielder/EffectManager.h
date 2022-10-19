#pragma once
class EffectManager final
{
public:
	EffectManager();
	~EffectManager();

	void Initialize();
	void Finalize();
	void Activate();
	void Deactivate();
	void Update();
	void Draw();

	void CreateGuardEffect(const VECTOR& inPosition);

private:
	EffectManager(const EffectManager&);
	void operator=(const EffectManager&);

	EffectBase** effects;
};

