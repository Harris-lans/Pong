#pragma once
#include "COGShape.h"

class COGBoxShape : public COGShape
{
public:
	COGBoxShape(exEngineInterface* pEngine, GameObject* pGameObject, float fWidth, float fHeight, exColor& pColor);

	virtual ComponentType GetType() const;

	virtual void Render() override;

	float& GetWidth();
	float& GetHeight();

private:
	float mWidth;
	float mHeight;
};