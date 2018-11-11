#include "COGShape.h"

std::vector<COGShape*> COGShape::mShapeComponents;

COGShape::COGShape(exEngineInterface* pEngine, GameObject* pGameObject, exColor& pColor)
	:Component(pGameObject)
{
	mEngine = pEngine;
	mColor = pColor;
}

COGShape::~COGShape()
{
	// Clearing the static vector of physics components
	for (COGShape* pShapeComponent : mShapeComponents)
	{
		pShapeComponent->RemoveFromComponentVector(mShapeComponents);
	}
}

void COGShape::Initialize()
{
	// Getting the transform of the gameobject
	mTransform = mGameObject->FindComponent<COGTransform>(ComponentType::Transform);
	
	// Adding the shape component to the static vector
	AddToComponentVector(mShapeComponents);
}
