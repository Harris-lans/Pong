#include "COGScoredEvent.h"

COGScoredEvent::COGScoredEvent(GameObject* pGameObject, Player* pPlayer, Ball* pBall)
	:Component(pGameObject)
{
	mPlayer = pPlayer;
	mBall = pBall;
}

ComponentType COGScoredEvent::GetType() const
{
	return ComponentType::ScoredEvent;
}

void COGScoredEvent::OnCollision(COGPhysics* pPhysicsComponent, COGPhysics* pOtherPhysicsComponent, exVector2 pNormalVector)
{
	mPlayer->IncreaseScore();
	mBall->ResetBall();
}
