#pragma once
class ScreenFade
{
public:
	static ScreenFade& GetInstance();

	void Update();
	void Draw();

	void FadeIn();
	void FadeOut();
	void Reset();
	bool IsFinish();

private:
	ScreenFade();
	ScreenFade(const ScreenFade&);
	void operator=(const ScreenFade&);
	~ScreenFade();

	int remainingFrame;
	int alpha;

	void (ScreenFade::* pUpdate)();
	void (ScreenFade::* pDraw)();

	void UpdateFadeIn();
	void DrawFadeIn();
	void UpdateFadeOut();
	void DrawFadeOut();
};

