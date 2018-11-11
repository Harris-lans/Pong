#pragma once
#include "COGPhysics.h"
#include "COGBounce.h"
#include "Mathf.h"

std::vector<COGPhysics*> COGPhysics::mPhysicsComponents;

COGPhysics::COGPhysics(exEngineInterface* pEngine, GameObject* pGameObject, bool bGenerateCollisionEvents, float fVelocity)
	:Component(pGameObject)
{
	mEngine = pEngine;
	mDebugColor.SetColor(0, 255, 0, 255);

	mGenerateCollisionEvents = bGenerateCollisionEvents;
	mVelocity = fVelocity;
	// Storing the object in the static variable
	AddToComponentVector(mPhysicsComponents);
}

COGPhysics::~COGPhysics()
{
	// Clearing the static vector of physics components
	for (COGPhysics* pPhysicsComponent : mPhysicsComponents)
	{
		pPhysicsComponent->RemoveFromComponentVector(mPhysicsComponents);
	}

	// Clearing all the events
	for (int i = 0; i < mCollisionEventListeners.size(); i++)
	{
		if (dynamic_cast<Component*>(mCollisionEventListeners[i]) == nullptr)
		{
			delete mCollisionEventListeners[i];
		}

		mCollisionEventListeners.erase(mCollisionEventListeners.begin() + i);
	}
}

ComponentType COGPhysics::GetType() const
{
	return ComponentType::Physics;
}

void COGPhysics::Initialize()
{
	// Storing reference to transform and shape of the game object
	mTransform = mGameObject->FindComponent<COGTransform>(ComponentType::Transform);
	mBoxShape = mGameObject->FindComponent<COGBoxShape>(ComponentType::BoxShape);
	mCircleShape = mGameObject->FindComponent<COGCircleShape>(ComponentType::CircleShape);
}

void COGPhysics::AddPhysicsEvents(IPhysicsCollisionEvent* pPhysicsEvent)
{
	mGameObject->AddComponent(dynamic_cast<Component*>(pPhysicsEvent));
	mCollisionEventListeners.push_back(pPhysicsEvent);
}

void COGPhysics::RemovePhysicsEvents(IPhysicsCollisionEvent* pEvent)
{
	for (int i = 0; i < mCollisionEventListeners.size(); i++)
	{
		if (mCollisionEventListeners[i] == pEvent)
		{
			if (dynamic_cast<Component*>(pEvent) == nullptr)
			{
				delete pEvent;
			}
			
			mCollisionEventListeners.erase(mCollisionEventListeners.begin() + i);
			return;
		}
	}
}

exVector2 COGPhysics::IsColliding(COGPhysics* pOther)
{
	// Checking if the collsion is between a circle and a box
	if ((mCircleShape != nullptr && pOther->mBoxShape != nullptr) || (mBoxShape != nullptr && pOther->mCircleShape != nullptr))
	{
		// Checking if the circle is colliding with the rectangle
		//========================================================

		exVector2 nearestPositionOnRectangle = { 0 , 0 };
		exVector2 point1Box;
		exVector2 point2Box;
		exVector2 centerCircle;
		float radiusOfCircle;
		
		if (mCircleShape != nullptr && pOther->mBoxShape != nullptr)
		{
			point1Box = { (pOther->mTransform->GetPosition().x) , (pOther->mTransform->GetPosition().y) };
			point2Box = { (pOther->mTransform->GetPosition().x + pOther->mBoxShape->GetWidth()) , (pOther->mTransform->GetPosition().y + pOther->mBoxShape->GetHeight()) };
			centerCircle = { (mTransform->GetPosition().x) , (mTransform->GetPosition().y) };
			radiusOfCircle = mCircleShape->GetRadius();
		}

		else
		{
			point1Box = { (mTransform->GetPosition().x) , (mTransform->GetPosition().y) };
			point2Box = { (mTransform->GetPosition().x + mBoxShape->GetWidth()) , (mTransform->GetPosition().y + mBoxShape->GetHeight()) };
			centerCircle = { (pOther->mTransform->GetPosition().x) , (pOther->mTransform->GetPosition().y) };
			radiusOfCircle = pOther->mCircleShape->GetRadius();
		}

		// Finding the nearest point on the rectangle's border to the circle
		nearestPositionOnRectangle.x = Mathf::Max(point1Box.x , (Mathf::Min(point2Box.x , centerCircle.x)));
		nearestPositionOnRectangle.y = Mathf::Max(point1Box.y , (Mathf::Min(point2Box.y, centerCircle.y)));

		// Calculating the distance between the nearest point and the center of the circle
		exVector2 distanceVector = { (centerCircle.x - nearestPositionOnRectangle.x) , (centerCircle.y - nearestPositionOnRectangle.y) };
		float distanceFloat = distanceVector.Magnitude();


		// Collision Check
		if (distanceFloat <= radiusOfCircle)
		{	
			// Finding the normal of the surface of the box; 
			distanceVector.Normalize();

			// Moving the Circle out of the box if they are overlapping
			float depthPenetration = abs(radiusOfCircle - distanceFloat);
			exVector2& position = mTransform->GetPosition();
			position.x += distanceVector.x * depthPenetration;
			position.y += distanceVector.y * depthPenetration;

			return distanceVector;
		}
	}

	return {NULL , NULL};
}

exVector2& COGPhysics::GetFacingDirection()
{
	return mFacingDirection;
}

float& COGPhysics::GetVelocity()
{
	return mVelocity;
}

void COGPhysics::SetFacingDirection(exVector2& pFacingDirection)
{
	mFacingDirection = pFacingDirection;
}

void COGPhysics::SetVelocity(float fVelocity)
{
	mVelocity = fVelocity;
}

void COGPhysics::Update(float fDeltaTime)
{
	// Adding Velocity to the object
	exVector2& myPosition = mTransform->GetPosition();
	myPosition.x += mFacingDirection.x * mVelocity * fDeltaTime;
	myPosition.y += mFacingDirection.y * mVelocity * fDeltaTime;

	// Check collisions
	if (mGenerateCollisionEvents)
	{
		for (COGPhysics* pPhysicsOther : COGPhysics::mPhysicsComponents)
		{
			// Do not collide with self
			if (pPhysicsOther == this)
			{
				continue;
			}

			const exVector2 pNormal = IsColliding(pPhysicsOther);

			// If the normal is null there is no collision
			if (pNormal.x == NULL && pNormal.y == NULL)
			{
				continue;
			}
			else
			{
				// Trigger all Events that should happen on a collision
				for (IPhysicsCollisionEvent* pCollisionEventListener : mCollisionEventListeners)
				{
					pCollisionEventListener->OnCollision(this, pPhysicsOther, pNormal);
				}
			}
		}
	}
}