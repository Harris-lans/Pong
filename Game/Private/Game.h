//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.h
// definition of MyGame, an implementation of exGameInterface
//

#include "Game/Public/GameInterface.h"
#include "Engine/Public/EngineTypes.h"
#include "GameObjectManager.h"
#include "COGScoredEvent.h"
#include "Player.h"
#include "Ball.h"
#include <vector>
#include <string>

//-----------------------------------------------------------------
//-----------------------------------------------------------------

class MyGame : public exGameInterface
{
public:

								MyGame();
	virtual						~MyGame();

	virtual void				Initialize( exEngineInterface* pEngine );

	virtual const char*			GetWindowName() const;
	virtual void				GetClearColor( exColor& color ) const;

	virtual void				OnEvent( SDL_Event* pEvent );
	virtual void				OnEventsConsumed();

	virtual void				Run( float fDeltaT );


private:
	GameObject*					CreateBoundaries(exVector2 pPosition, float fWidth, float fHeight, exColor& pColor);

	Player*						mPlayer1;
	Player*						mPlayer2;
	Ball*						mBall;
	GameObject*					mPlayer1Wall;
	GameObject*					mPlayer2Wall;
	exVector2					mPlayer1ScorePosition;
	exVector2					mPlayer2ScorePosition;

	exEngineInterface*			mEngine;

	GameObjectManager*			mGameObjectManager;
	bool						mGameOver;
	std::string					mGameOverText;
	exVector2					mGameOverTextPosition;

	exColor						mScoreFontColor;

	int							mFontID;

	exVector2					mTextPosition;

};
