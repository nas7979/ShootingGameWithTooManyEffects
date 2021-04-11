#pragma once
enum Tag
{
	Player,
	Enemy,
	PlayerBullet,
	EnemyBullet,
	Item,
	None,
	End
};
class cComponent;
class cObject
{
	friend class cObjectManager;
public:
	cObject();
	virtual ~cObject();

protected:

	void Release();

	Vec2 m_Pos = Vec2(0, 0);
	float m_Rot = 0;
	Vec2 m_Scale = Vec2(1, 1);
	string m_Name;
	Tag m_Tag;
	int m_Depth;
	bool m_Destroyed = false;
	vector<cComponent*> m_Components;
	float* m_Alarm = nullptr;
	int m_AlarmSize = 0;
	function<void(int Index)> m_AlarmFunc;

public:
	template <typename T>
	T* AddComponent()
	{
		T* a = new T(this);
		m_Components.push_back(a);
		a->Init();
		return a;
	}

	template <typename T>
	T* GetComponent()
	{
		for (auto& iter : m_Components)
		{
			if (typeid(*iter) == typeid(T))
			{
				return static_cast<T*>(iter);
			}
		}
		for (auto& iter : m_Components)
		{
			if (dynamic_cast<T*>(iter))
			{
				return static_cast<T*>(iter);
			}
		}
		return nullptr;
	}

	Vec2 GetPosition() { return m_Pos; }
	void SetPosition(Vec2 Pos) { m_Pos = Pos; }
	void Translate(Vec2 Pos) { m_Pos += Pos; }
	Vec2 GetScale() { return m_Scale; }
	void SetScale(Vec2 Scale) { m_Scale = Scale; }
	float GetRotation() { return m_Rot; }
	void Rotate(float Rot) { m_Rot += Rot; }
	void SetRotation(float Rot) { m_Rot = Rot; }
	string GetName() { return m_Name; }
	void SetName(string Name) { m_Name = Name; }
	Tag GetTag() { return m_Tag; }
	void SetTag(Tag Tag) { m_Tag = Tag; }
	int GetDepth() { return m_Depth; }
	void SetDepth(int Depth) { m_Depth = Depth; }
	void Destroy() { m_Destroyed = true; }
	bool GetDestroyed() { return m_Destroyed; }
	void SetAlarmSize(int Size);
	void Alarm(int Index, float Duration) { m_Alarm[Index] = Duration; }
	float GetAlarmDuration(int Index) { return m_Alarm[Index]; }
	void SetAlarmFunc(function<void(int Index)> Func) { m_AlarmFunc = Func; }
};

