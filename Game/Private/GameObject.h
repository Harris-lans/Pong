#pragma once
#include "Engine\Public\EngineInterface.h"
#include <vector>

// All the different types of components
enum class ComponentType : int
{
	Transform = 0,
	Physics,
	BoxShape,
	CircleShape,
	ScoredEvent,
	Bounce,
	InputReader,
	KeyPress,
	MoveUp,
	MoveDown
};


// Declaring the component class
class Component;

class GameObject
{
public:

	GameObject();

	~GameObject();

	void Initialize();
	
	void AddComponent(Component* pComponent);
	
	void RemoveComponent(Component* pComponent);

	int NumberOfComponents() const;

	template<class T>
	T* FindComponent(ComponentType eType)
	{
		for (Component* pComponent : mComponents)
		{
			if (pComponent->GetType() == eType)
			{
				return (T*)pComponent;
			}
		}

		return nullptr;
	}

private:
	std::vector<Component*> mComponents;

};

// Components
class Component
{
protected:
	Component(GameObject* gameObject);

public:

	virtual ComponentType GetType() const = 0;

	virtual void Initialize();
	virtual void Destroy();

protected:

	template<class T>
	void AddToComponentVector(std::vector<T*>& componentVector)
	{
		componentVector.push_back((T*)this);
	}

	template<class T>
	void RemoveFromComponentVector(std::vector<T*>& componentVector)
	{
		for (int i = 0; i < componentVector.size(); i++)
		{
			if (componentVector[i] == this)
			{
				componentVector.erase(componentVector.begin() + i);
				return;
			}
		}
	}

protected:

	GameObject * mGameObject;

};