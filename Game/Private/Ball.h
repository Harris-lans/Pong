#pragma once
#include "GameObjectManager.h"
#include "COGPhysics.h"

class Ball
{
public:
	const float BALL_RADIUS = 20.0f;
	const float BALL_VELOCITY = 400.0f;
	const exVector2 DEFAULT_START_LOCATION = { kViewportWidth / 2, kViewportHeight / 2 };

private:
	exEngineInterface * mEngine;
	GameObject* mGameObject;
	GameObjectManager* mGameObjectManager;
	COGTransform* mTransformComponent;
	COGPhysics* mPhysicsComponent;

public:
	Ball(exEngineInterface* pEngine, exVector2 pPosition);
	~Ball();
	void ResetBall();

private:
	GameObject* CreateBall(exVector2& pPosition);
};