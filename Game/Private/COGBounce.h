#pragma once
#include "COGPhysics.h"
#include "COGTransform.h"

class COGBounce : public Component, public IPhysicsCollisionEvent
{
public:

	COGBounce(GameObject* pGameObject);

	virtual ComponentType GetType() const;
	virtual void OnCollision(COGPhysics* pPhysicsComponent, COGPhysics* pOtherPhysicsComponent, exVector2 pNormalVector) override;

};

