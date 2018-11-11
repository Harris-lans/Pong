 #include "COGInputReader.h"
 #include "GameObject.h"
#include "Engine\Public\SDL.h"
#include "Output.h"

std::vector<COGInputReader*> COGInputReader::mInputReaderComponents;

COGInputReader::COGInputReader(GameObject* pGameObject)
	:Component(pGameObject)
{
	mInputReaderComponents.push_back(this);
}

COGInputReader::~COGInputReader()
{
	// Clearing the static vector of input reader components
	for (COGInputReader* pInputReaderComponent : mInputReaderComponents)
	{
		pInputReaderComponent->RemoveFromComponentVector(mInputReaderComponents);
	}

	// Clearing all the events
	for (int i = 0; i < mKeyboardEvents.size(); i++)
	{
		// Checking if the event is also a component
		if (dynamic_cast<Component*>(mKeyboardEvents[i]) == nullptr)
		{
			// Deleting the event if it is not
			// The Component class takes care of deleting all the components
			delete mKeyboardEvents[i];
		}
		mKeyboardEvents.erase(mKeyboardEvents.begin() + i);
		mKeyboardBindings.erase(mKeyboardBindings.begin() + i);
	}
}

void COGInputReader::AddInputEvents(int iKeyBinding, IInputEvent* pInputEvent)
{
	mKeyboardBindings.push_back(iKeyBinding);
	mKeyboardEvents.push_back(pInputEvent);

	// Adding the events to the component list if the event is also a component
	Component* pComponent = dynamic_cast<Component*>(pInputEvent);
	if (pComponent != nullptr)
	{
		mGameObject->AddComponent(pComponent);
	}
}

void COGInputReader::RemoveInputEvents(IInputEvent* pInputEvent)
{
	for (int i = 0; i < mKeyboardEvents.size(); i++)
	{
		if (mKeyboardEvents[i] == pInputEvent)
		{
			// Checking if the event is also a component
			if (dynamic_cast<Component*>(pInputEvent) == nullptr)
			{
				// Deleting the event if it is not
				// The Component class takes care of deleting all the components
				delete pInputEvent;
			}
			mKeyboardEvents.erase(mKeyboardEvents.begin() + i);
			mKeyboardBindings.erase(mKeyboardBindings.begin() + i);
			return;
		}
	}
}

void COGInputReader::Update()
{
	// Getting the current keyboard state
	int keys = 0;
	const Uint8* pState = SDL_GetKeyboardState(&keys);

	// Checking if any keypresses have been registered
	for (int i = 0; i < mKeyboardEvents.size(); i++)
	{
		// Checking if the respective keybindings are active and triggering the respective events
		if (pState[mKeyboardBindings[i]])
		{
			mKeyboardEvents[i]->OnButtonPressed();
		}
	}
}

ComponentType COGInputReader::GetType() const
{
	return ComponentType::InputReader;
}