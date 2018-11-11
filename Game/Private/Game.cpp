//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.cpp
// implementation of MyGame, an implementation of exGameInterface
//

#include "Game/Private/Game.h"

#include "Engine/Public/EngineInterface.h"
#include "Engine/Public/SDL.h"


//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* gWindowName = "Pong 2.0";
const float DEFAULT_BORDER_THICKNESS = 30.0f;
const int MAX_SCORE = 10;
const exVector2 DEFAULT_BALL_START = { (kViewportWidth / 2), (kViewportHeight / 2) };

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::MyGame()
	: mEngine( nullptr )
	, mFontID( -1 )
	,mGameOver(false)
	,mGameOverText("")
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::~MyGame()
{
	mGameObjectManager->ClearAllGameObjects();
	mGameObjectManager->DeleteInstance();
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Initialize( exEngineInterface* pEngine )
{
	mEngine = pEngine;
	mGameObjectManager = GameObjectManager::GetInstance();
	mPlayer1 = new Player(mEngine, SDL_SCANCODE_W, SDL_SCANCODE_S, { DEFAULT_BORDER_THICKNESS + 10 , 100 });
	mPlayer2 = new Player(mEngine, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, { kViewportWidth - (DEFAULT_BORDER_THICKNESS + 10 + PADDLE_WIDTH) , 100 });
	mBall = new Ball(mEngine, DEFAULT_BALL_START);

	exColor pColorOfBoundaries;
	pColorOfBoundaries.SetColor(128, 128, 128, 255);

	CreateBoundaries({ 0 , 0 }, kViewportWidth, DEFAULT_BORDER_THICKNESS, pColorOfBoundaries);
	CreateBoundaries({ 0 , (kViewportHeight - DEFAULT_BORDER_THICKNESS) }, kViewportWidth, DEFAULT_BORDER_THICKNESS, pColorOfBoundaries);

	mPlayer1Wall = CreateBoundaries({ 0 , 0 }, DEFAULT_BORDER_THICKNESS , kViewportHeight, pColorOfBoundaries);
	mPlayer2Wall = CreateBoundaries({ (kViewportWidth - DEFAULT_BORDER_THICKNESS) , 0 }, DEFAULT_BORDER_THICKNESS, kViewportHeight, pColorOfBoundaries);

	
	// Adding the Scored events for Player 1
	COGPhysics* pPhysicsComponent = mPlayer2Wall->FindComponent<COGPhysics>(ComponentType::Physics);
	IPhysicsCollisionEvent* scoredEvent = (IPhysicsCollisionEvent*) new COGScoredEvent(mPlayer2Wall, mPlayer1, mBall);
	pPhysicsComponent->AddPhysicsEvents(scoredEvent);

	// Adding the Scored events for Player 2
	pPhysicsComponent = mPlayer1Wall->FindComponent<COGPhysics>(ComponentType::Physics);
	scoredEvent = (IPhysicsCollisionEvent*) new COGScoredEvent(mPlayer1Wall, mPlayer2, mBall);
	pPhysicsComponent->AddPhysicsEvents(scoredEvent);

	// Initializing Font Data
	mFontID = mEngine->LoadFont("randomFont.ttf", 20);
	mScoreFontColor.SetColor(255, 255, 255, 255);
	mPlayer1ScorePosition.x = kViewportWidth / 4;
	mPlayer1ScorePosition.y = 5;
	mPlayer2ScorePosition.x = kViewportWidth * 3 / 4;
	mPlayer2ScorePosition.y = 5;
	
	mGameOverTextPosition = { (kViewportWidth / 2) , (kViewportHeight / 2) };
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* MyGame::GetWindowName() const
{
	return gWindowName;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::GetClearColor( exColor& color ) const
{
	color.mColor[0] = 0;
	color.mColor[1] = 0;
	color.mColor[2] = 0;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEvent( SDL_Event* pEvent )
{

}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEventsConsumed()
{

}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Run( float fDeltaT )
{
	if (!mGameOver)
	{
		mGameObjectManager->Update(fDeltaT);
		mGameObjectManager->Render();

		std::string p1ScoreStr("Player One-" + std::to_string(mPlayer1->GetScore()));
		std::string p2ScoreStr("Player Two-" + std::to_string(mPlayer2->GetScore()));

		const char* p1ScoreChar = p1ScoreStr.c_str();
		const char* p2ScoreChar = p2ScoreStr.c_str();

		mEngine->DrawText(mFontID, mPlayer1ScorePosition, p1ScoreChar, mScoreFontColor, 0);
		mEngine->DrawText(mFontID, mPlayer2ScorePosition, p2ScoreChar, mScoreFontColor, 0);

		if (mPlayer1->GetScore() >= MAX_SCORE)
		{
			mGameOverText = "Player 1 won the game.";
			mGameOver = true;
		}
		else if (mPlayer2->GetScore() >= MAX_SCORE)
		{
			mGameOverText = "Player 2 won the game.";
			mGameOver = true;
		}
	}
	else
	{
		const char* gameOverText = mGameOverText.c_str();
		mEngine->DrawText(mFontID, mGameOverTextPosition, gameOverText, mScoreFontColor, 0);
	}
}

GameObject* MyGame::CreateBoundaries(exVector2 pPosition, float fWidth, float fHeight, exColor& pColor)
{
	GameObject* pBoundary = mGameObjectManager->CreateGameObject();

	// Creating Components for the boundaries
	pBoundary->AddComponent(new COGTransform(pBoundary, pPosition));
	pBoundary->AddComponent(new COGBoxShape(mEngine, pBoundary, fWidth, fHeight, pColor));
	pBoundary->AddComponent(new COGPhysics(mEngine, pBoundary, true, 0.0f));

	pBoundary->Initialize();
	return pBoundary;
}

