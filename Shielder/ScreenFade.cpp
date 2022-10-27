#include "Pch.h"

#include "GameDefine.h"
#include "ScreenFade.h"

ScreenFade::ScreenFade()
    :alpha()
    ,pUpdate(nullptr)
    ,pDraw(nullptr)
{
}

ScreenFade::~ScreenFade()
{
}


ScreenFade& ScreenFade::GetInstance()
{
    static ScreenFade screenFade;
    return screenFade;
}

void ScreenFade::Update()
{
    //ˆ—‚ª‚È‚¯‚ê‚Îˆ—‚µ‚È‚¢
    if (pUpdate == nullptr)
    {
        return;
    }
    (this->*pUpdate)();
}

void ScreenFade::Draw()
{
    //ˆ—‚ª‚È‚¯‚ê‚Îˆ—‚µ‚È‚¢
    if (pDraw == nullptr)
    {
        return;
    }

    (this->*pDraw)();
}

void ScreenFade::FadeIn()
{
    
}

void ScreenFade::FadeOut()
{
}

void ScreenFade::Reset()
{
}

bool ScreenFade::IsFinish()
{
    if (pUpdate == nullptr)
    {
        return true;
    }
    return false;
}

void ScreenFade::UpdateFadeIn()
{
    
}

void ScreenFade::DrawFadeIn()
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(255, 255, 255), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
}

void ScreenFade::UpdateFadeOut()
{
  
}

void ScreenFade::DrawFadeOut()
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(255, 255, 255), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
}
