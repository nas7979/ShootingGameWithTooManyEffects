#pragma once

template <typename T>
class cSingleton
{
public:
	cSingleton() {};
	virtual ~cSingleton() {};

private:
	static T* p;

public:
	static void CreateInstance()
	{
		p = new T;
	}
	static T* GetInstance()
	{
		return p;
	}
	static void ReleaseInstance()
	{
		SAFE_DELETE(p);
	}
};
template <typename T>
T* cSingleton<T>::p = nullptr;