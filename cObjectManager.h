#pragma once
#include "cObject.h"
#include "cComponent.h"
class cObjectManager : public cSingleton<cObjectManager>
{
public:
	cObjectManager();
	~cObjectManager();

	void Init();
	void Update();
	void Render();
	void Release();

private:
	list<cObject*>* m_Objects;
	list<cObject*> m_RenderObjects;

	void CollisionCheck(cObject* Object);

public:
	cObject* AddObject(string Name, Vec2 Pos, Tag Tag, int Depth);

	void Find(list<cObject*>* List, string Name, Tag Tag);
	void Find(list<cObject*>* List, Tag Tag);
	cObject* GetPlayer() { return m_Objects[Tag::Player].front(); }
	void ClearAll();

};

#define OBJECT cObjectManager::GetInstance()