#include "COGMoveUp.h"

COGMoveUp::COGMoveUp(GameObject* pGameObject)
	:Component(pGameObject)
{
	
}

COGMoveUp::~COGMoveUp()
{

}

void COGMoveUp::Initialize()
{
	mTransform = mGameObject->FindComponent<COGTransform>(ComponentType::Transform);
	mPhysics = mGameObject->FindComponent<COGPhysics>(ComponentType::Physics);
}

ComponentType COGMoveUp::GetType() const
{
	return ComponentType::MoveUp;
}

void COGMoveUp::OnButtonPressed()
{
	exVector2& pPosition = mTransform->GetPosition();
	// Having an offset for the ceiling
	if (pPosition.y >= 40)
	{
		// Moving the object up
		pPosition.y -= mPhysics->GetVelocity();
	}
}
