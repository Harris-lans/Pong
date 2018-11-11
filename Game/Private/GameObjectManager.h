#pragma once
#include "GameObject.h"
#include "Singleton.h"
#include <vector>

class GameObjectManager : public Singleton<GameObjectManager>
{
private:
	std::vector<GameObject*> mGameObjects;
public:
	GameObjectManager();
	~GameObjectManager();

	GameObject* CreateGameObject();
	void DeleteGameObject(GameObject* pGameObject);
	void ClearAllGameObjects();

	void Update(float fDeltaTime);
	void Render();
};

GameObjectManager* Singleton<GameObjectManager>::existingInstance = nullptr;