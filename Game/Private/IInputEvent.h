#pragma once
#include "Engine\Public\SDL.h"
#include "COGTransform.h"
#include "COGPhysics.h"

class IInputEvent
{
public:
	virtual void OnButtonPressed() = 0;
};