#include "Player.h"
#include "COGBounce.h"
#include "COGInputReader.h"
#include "COGMoveDown.h"
#include "COGMoveUp.h"

Player::Player(exEngineInterface* pEngine, int pMoveUpKeycode, int pMoveDownKeyCode, exVector2 pPosition)
{
	mEngine = pEngine;
	mGameObjectManager = GameObjectManager::GetInstance();
	mGameObject = CreatePaddle(pMoveUpKeycode, pMoveDownKeyCode, pPosition);
	mScore = 0;
}

Player::~Player()
{
	// Nothing to do here for now
}

int& Player::GetScore()
{
	return mScore;
}

void Player::IncreaseScore()
{
	++mScore;
}

GameObject* Player::CreatePaddle(int pMoveUpKeycode, int pMoveDownKeyCode, exVector2& pPosition)
{
	GameObject* pPaddle = mGameObjectManager->CreateGameObject();
	std::vector<Component*> pPaddleComponents;

	// Making Components for the paddle
	//=================================

	// Making Physics Component
	COGPhysics* pPhysicsComponent = new COGPhysics(mEngine, pPaddle, false, PADDLE_VELOCITY);

	// Making InputReader Component
	COGInputReader* pInputReader = new COGInputReader(pPaddle);
	IInputEvent* pMoveUp = new COGMoveUp(pPaddle);
	IInputEvent* pMoveDown = new COGMoveDown(pPaddle);
	// Mapping Inputs
	pInputReader->AddInputEvents(pMoveUpKeycode, pMoveUp);
	pInputReader->AddInputEvents(pMoveDownKeyCode, pMoveDown);

	// Making Transform and Shape Components
	exColor pPaddleColor;
	pPaddleColor.SetColor(200, 200, 200, 255);

	pPaddleComponents.push_back(new COGTransform(pPaddle, pPosition));
	pPaddleComponents.push_back(new COGBoxShape(mEngine, pPaddle, PADDLE_WIDTH, PADDLE_HEIGHT, pPaddleColor));
	pPaddleComponents.push_back(pPhysicsComponent);
	pPaddleComponents.push_back(pInputReader);

	// Adding the Components to the GameObject
	for (Component* pComponent : pPaddleComponents)
	{
		pPaddle->AddComponent(pComponent);
	}

	// Initializing all the components
	pPaddle->Initialize();

	return pPaddle;
}