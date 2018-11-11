#include "COGCircleShape.h"
#include "COGTransform.h"

COGCircleShape::COGCircleShape(exEngineInterface* pEngine, GameObject* pGameObject, float fRadius, exColor& pColor)
	:COGShape(pEngine, pGameObject, pColor)
{
	mRadius = fRadius;
}

ComponentType COGCircleShape::GetType() const
{
	return ComponentType::CircleShape;
}

void COGCircleShape::Render()
{
	// Cecking if the game object has a transform
	if (mTransform != nullptr)
	{
		exVector2 position = mTransform->GetPosition();
		
		// Drawing the circle
		mEngine->DrawCircle(position, mRadius, mColor, 2);
	}
}

float& COGCircleShape::GetRadius()
{
	return mRadius;
}