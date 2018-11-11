#pragma once
#include "GameObjectManager.h"

const float PADDLE_HEIGHT = 150.0f;
const float PADDLE_WIDTH = 25.0f;
const float PADDLE_VELOCITY = 4.0f;

class Player
{
private:
	GameObject* mGameObject;
	GameObjectManager* mGameObjectManager;
	exEngineInterface* mEngine;
	int mScore;

private:
	GameObject* CreatePaddle(int pMoveUpKeycode, int pMoveDownKeyCode, exVector2& pPosition);

public:
	Player(exEngineInterface* pEngine, int pMoveUpKeycode, int pMoveDownKeyCode, exVector2 pPosition);
	~Player();

	int& GetScore();
	void IncreaseScore();
};