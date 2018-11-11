#pragma once
#include "Player.h"
#include "Ball.h"
#include "COGPhysics.h"

class COGScoredEvent : public Component, public IPhysicsCollisionEvent
{
public:
	COGScoredEvent(GameObject* pGameObject, Player* pPlayer, Ball* pBall);

	virtual ComponentType GetType() const;
	virtual void OnCollision(COGPhysics* pPhysicsComponent, COGPhysics* pOtherPhysicsComponent, exVector2 pNormalVector) override;

private:
	Player* mPlayer;
	Ball* mBall;
};