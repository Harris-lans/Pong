#include "IInputEvent.h"
#include "COGTransform.h"
#include "COGPhysics.h"

class COGMoveUp : public Component, public IInputEvent
{
private:
	COGTransform* mTransform;
	COGPhysics* mPhysics;

public:
	COGMoveUp(GameObject* pGameObject);
	~COGMoveUp();

	virtual void Initialize() override;
	virtual ComponentType GetType() const override;
	virtual void OnButtonPressed() override;
};
