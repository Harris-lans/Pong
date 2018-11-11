#include "COGBounce.h"

COGBounce::COGBounce(GameObject* pGameObject)
	:Component(pGameObject)
{

}

ComponentType COGBounce::GetType() const
{
	return ComponentType::Bounce;
}

void COGBounce::OnCollision(COGPhysics* pPhysicsComponent, COGPhysics* pOtherPhysicsComponent, exVector2 pNormalVector)
{
	exVector2 currentDirection = pPhysicsComponent->GetFacingDirection();
	float pDotProduct = exVector2::DotProduct(currentDirection, pNormalVector);
	exVector2 newFacingDirection = { (2 * pDotProduct * pNormalVector.x) , (2 * pDotProduct * pNormalVector.y) };
	newFacingDirection.x = currentDirection.x - newFacingDirection.x;
	newFacingDirection.y = currentDirection.y - newFacingDirection.y;
	newFacingDirection.Normalize();

	// Setting the new Facing Direction
	pPhysicsComponent->SetFacingDirection(newFacingDirection);
}
