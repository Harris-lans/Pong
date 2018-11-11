#pragma once
#include "IInputEvent.h"
#include "GameObject.h"

class COGInputReader : public Component
{
public:
	static std::vector<COGInputReader*> mInputReaderComponents;
public:
	COGInputReader(GameObject* pGameObject);
	~COGInputReader();

	void AddInputEvents(int iKeyBinding, IInputEvent* pInputEvent);
	void RemoveInputEvents(IInputEvent* pInputEvent);

	ComponentType GetType() const;

	virtual void Update();

private:
	std::vector<int> mKeyboardBindings;
	std::vector<IInputEvent*> mKeyboardEvents;
};