#include "COGBoxShape.h"
#include "COGTransform.h"
#include "Output.h"

COGBoxShape::COGBoxShape(exEngineInterface* pEngine, GameObject* pGameObject, float fWidth, float fHeight, exColor& pColor)
	:COGShape(pEngine, pGameObject, pColor)
{
	// Initializing the dimensions of the shape
	mWidth = fWidth;
	mHeight = fHeight;
}

ComponentType COGBoxShape::GetType() const
{
	return ComponentType::BoxShape;
}

void COGBoxShape::Render()
{
	// Checking if there is a transform object in the game object
	if (mTransform != nullptr)
	{
		exVector2 vertex1 = mTransform->GetPosition();
		exVector2 vertex2 = { (vertex1.x + mWidth) , (vertex1.y + mHeight) };

		// Drawing the box
		mEngine->DrawBox(vertex1, vertex2, mColor, 2);
	}
}

float& COGBoxShape::GetWidth()
{
	return mWidth;
}

float& COGBoxShape::GetHeight()
{
	return mHeight;
}