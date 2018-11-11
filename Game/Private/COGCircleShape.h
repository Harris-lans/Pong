#pragma once
#include "COGShape.h"

class COGCircleShape : public COGShape
{
public:
	COGCircleShape(exEngineInterface* pEngine, GameObject* pGameObject, float fRadius, exColor& pColor);

	virtual ComponentType GetType() const;
	virtual void Render() override;

	float& GetRadius();

private:
	float mRadius;
};