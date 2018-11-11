#pragma once
#include "GameObject.h"
#include "COGTransform.h"

class COGShape : public Component
{
public:

	static std::vector<COGShape*> mShapeComponents;

protected:
	COGShape(exEngineInterface* pEngine, GameObject* pGameObject, exColor& pColor);
	~COGShape();

public:

	virtual void Initialize() override;
	virtual void Render() = 0;

protected:
	exColor mColor;
	exEngineInterface* mEngine;
	COGTransform* mTransform;
};