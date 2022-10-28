#include "Pch.h"
#include "EffectBase.h"

EffectBase::EffectBase()
	:effectHandle()
	,playingEffectHandle()
	,position()
	,frame()
	,exist(false)
	,existFrame()
{
}

EffectBase::~EffectBase()
{
}

void EffectBase::Initialize()
{
}

void EffectBase::Finalize()
{
}

void EffectBase::Activate(VECTOR inPosition)
{
}

void EffectBase::Deactivate()
{
}

void EffectBase::Update(VECTOR inPostion)
{
}

void EffectBase::Draw()
{
}

bool EffectBase::GetExist() const
{
	return exist;
}
