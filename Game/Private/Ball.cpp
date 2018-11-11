#include "Ball.h"
#include "COGBounce.h"
#include "COGInputReader.h"
#include "COGMoveDown.h"
#include "COGMoveUp.h"
#include <time.h>

Ball::Ball(exEngineInterface* pEngine, exVector2 pPosition)
{
	// Seeding rand
	srand(time(NULL));

	mEngine = pEngine;
	mGameObjectManager = GameObjectManager::GetInstance();
	mGameObject = CreateBall(pPosition);
	mTransformComponent = mGameObject->FindComponent<COGTransform>(ComponentType::Transform);
	mPhysicsComponent = mGameObject->FindComponent<COGPhysics>(ComponentType::Physics);
	ResetBall();
}

Ball::~Ball()
{

}

GameObject* Ball::CreateBall(exVector2& pPosition)
{
	GameObject* pGameObject = mGameObjectManager->CreateGameObject();

	exColor pColor;
	pColor.SetColor(255, 255, 255, 255);

	// Creating Components for the ball
	pGameObject->AddComponent(new COGTransform(pGameObject, DEFAULT_START_LOCATION));
	pGameObject->AddComponent(new COGCircleShape(mEngine, pGameObject, BALL_RADIUS, pColor));
	COGPhysics* pPhysicsComponent = new COGPhysics(mEngine, pGameObject, true, BALL_VELOCITY);
	pGameObject->AddComponent(pPhysicsComponent);
	// Adding Bounce Event
	pPhysicsComponent->AddPhysicsEvents(new COGBounce(pGameObject));

	pGameObject->Initialize();
	return pGameObject;
}

void Ball::ResetBall()
{
	exVector2& pPosition = mTransformComponent->GetPosition();
	pPosition = DEFAULT_START_LOCATION;

	exVector2 pNewFacingDirection = { 0 , 0 };
	pNewFacingDirection.x = ( (rand() % 3 - 1) * (rand() % kViewportWidth + 1) - pPosition.x);
	pNewFacingDirection.y = ( (rand() % 3 - 1) * (rand() % kViewportHeight + 1) - pPosition.y);
	pNewFacingDirection.Normalize();
	mPhysicsComponent->SetFacingDirection(pNewFacingDirection);
}