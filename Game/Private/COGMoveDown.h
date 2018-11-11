#include "IInputEvent.h"
#include "COGTransform.h"
#include "COGPhysics.h"

class COGMoveDown : public Component, public IInputEvent
{
private:
	COGTransform* mTransform;
	COGBoxShape* mShape;
	COGPhysics* mPhysics;

public:
	COGMoveDown(GameObject* pGameObject);
	~COGMoveDown();

	virtual void Initialize() override;
	virtual ComponentType GetType() const override;
	virtual void OnButtonPressed() override;
};
