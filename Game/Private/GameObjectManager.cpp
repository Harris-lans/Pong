#include "GameObjectManager.h"
#include "COGBounce.h"
#include "COGInputReader.h"
#include "COGMoveDown.h"
#include "COGMoveUp.h"

GameObjectManager::GameObjectManager()
{
	// Nothing to do here for now
}

GameObjectManager::~GameObjectManager()
{
	// Nothing to do here for now
}

void GameObjectManager::DeleteGameObject(GameObject* pGameObject)
{
	for (int i = 0; i < mGameObjects.size(); i++)
	{
		if (mGameObjects[i] == pGameObject)
		{
			delete pGameObject;
			mGameObjects.erase(mGameObjects.begin() + i);
			return;
		}
	}
}

GameObject* GameObjectManager::CreateGameObject()
{
	GameObject* newGameObject = new GameObject();
	mGameObjects.push_back(newGameObject);
	return newGameObject;
}

void GameObjectManager::ClearAllGameObjects()
{
	for (GameObject* pGameObject : mGameObjects)
	{
		DeleteGameObject(pGameObject);
	}
}

void GameObjectManager::Update(float fDeltaTime)
{
	// Updating the physics component and the input reader components

	for (COGPhysics* pPhysicsComponent : COGPhysics::mPhysicsComponents)
	{
		pPhysicsComponent->Update(fDeltaTime);
	}

	for (COGInputReader* pInputReaderComponent : COGInputReader::mInputReaderComponents)
	{
		pInputReaderComponent->Update();
	}
}

void GameObjectManager::Render()
{
	// Rendering all the shapes
	for (COGShape* pShapeComponent : COGShape::mShapeComponents)
	{
		pShapeComponent->Render();
	}
}