#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{
	for (Component* pComponent : mComponents)
	{
		pComponent->Destroy();

		delete pComponent;
	}
}

void GameObject::Initialize()
{
	for (Component* pComponent : mComponents)
	{
		pComponent->Initialize();
	}
}

void GameObject::AddComponent(Component* pComponent)
{
	mComponents.push_back(pComponent);
}

void GameObject::RemoveComponent(Component* pComponent)
{
	for (int i = 0; i < mComponents.size(); i++)
	{
		if (mComponents[i] == pComponent)
		{
			delete pComponent;
			mComponents.erase(mComponents.begin() + i);
			return;
		}
	}
}

int GameObject::NumberOfComponents() const
{
	return mComponents.size();
}

// Components
Component::Component(GameObject* pGameObject)
{
	mGameObject = pGameObject;
}

void Component::Initialize()
{

}

void Component::Destroy()
{

}