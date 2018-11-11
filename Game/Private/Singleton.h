#pragma once

template <class T>
class Singleton
{
protected:
	static T* existingInstance;
	// Making the constructor protected
	Singleton() {}

public:
	// Deleting the copy assignment operator so that they are not duplicated
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	static T* GetInstance()
	{
		if (existingInstance == nullptr)
		{
			existingInstance = new T();
		}
		return existingInstance;
	}

	static void DeleteInstance()
	{
		delete existingInstance;
		existingInstance = nullptr;
	}
};