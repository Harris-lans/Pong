#include "COGMoveDown.h"

COGMoveDown::COGMoveDown(GameObject* pGameObject)
	:Component(pGameObject)
{
	
}

COGMoveDown::~COGMoveDown()
{

}

void COGMoveDown::Initialize()
{
	mTransform = mGameObject->FindComponent<COGTransform>(ComponentType::Transform);
	mPhysics = mGameObject->FindComponent<COGPhysics>(ComponentType::Physics);
	mShape = mGameObject->FindComponent<COGBoxShape>(ComponentType::BoxShape);
}

ComponentType COGMoveDown::GetType() const
{
	return ComponentType::MoveDown;
}

void COGMoveDown::OnButtonPressed()
{
	exVector2& pPosition = mTransform->GetPosition();
	// Having an offset for the floor
	if (pPosition.y <= kViewportHeight - 40 - mShape->GetHeight())
	{
		// Moving the object down
		pPosition.y += mPhysics->GetVelocity();
	}
}
