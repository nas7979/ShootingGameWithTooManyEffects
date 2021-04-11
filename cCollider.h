#pragma once
struct Collider
{
	Vec2 LocalPos, WorldPos;
	float Size;
	Collider(Vec2 pos, float size)
	{
		LocalPos = pos;
		Size = size;
	}
};
class cCollider : public cComponent
{
	friend class cObjectManager;
public:
	cCollider(cObject* Owner);
	~cCollider();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

private:
	Collider** m_Colliders;
	int m_ColliderCount;
	vector<Tag> m_CollList;
	function<void(cObject* Other)> m_CollFunc;

public:
	void SetColliderCount(int Count);
	int GetColliderCount() { return m_ColliderCount; }
	void AddCollider(Vec2 Pos, float Size);
	void AddCollList(Tag Tag) { m_CollList.push_back(Tag); }
	void SetCollFunc(function<void(cObject* Other)> Func) { m_CollFunc = Func; }
	Collider* GetCollider(int Index) { return m_Colliders[Index]; }
};

