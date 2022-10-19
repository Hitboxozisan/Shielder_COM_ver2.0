#include "DeltaTime.h"

DeltaTime::DeltaTime()
{
}

DeltaTime::~DeltaTime()
{
}

DeltaTime& DeltaTime::GetInstace()
{
    static DeltaTime deltaTime;
    return deltaTime;
}
