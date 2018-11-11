#pragma once
#include "GameObject.h"
#include "Engine\Public\EngineInterface.h"

class COGTransform : public Component
{
public:

	COGTransform(GameObject* gameObject, exVector2 pPosition);

	virtual ComponentType GetType() const;

	exVector2& GetPosition();
	void SetPosition(exVector2& newPosition);

private:

	exVector2 mPosition;

};