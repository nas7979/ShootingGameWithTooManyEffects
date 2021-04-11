#pragma once
class cComponent
{
public:
	cComponent(cObject* Owner);
	virtual ~cComponent();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

protected:
	cObject* m_pObject;

public:
	template <typename T>
	T* AddComponent()
	{
		return m_pObject->AddComponent<T>();
	}

	template <typename T>
	T* GetComponent()
	{
		return m_pObject->GetComponent<T>();
	}
};

