#include "DXUT.h"
#include "cObjectManager.h"


cObjectManager::cObjectManager()
{
	Init();
}


cObjectManager::~cObjectManager()
{
	Release();
}

void cObjectManager::Init()
{
	m_Objects = new list<cObject*>[Tag::End];
}

void cObjectManager::Update()
{
	float TimeScale = SYSTEM->GetTimeScale();
	for (int i = 0; i < Tag::End; i++)
	{
		for (auto& iter = m_Objects[i].begin(); iter != m_Objects[i].end();)
		{
			if ((*iter)->m_Destroyed == false)
			{
				for (int i = 0; i < (*iter)->m_AlarmSize; i++)
				{
					(*iter)->m_Alarm[i] -= (1 * TimeScale);
					if ((*iter)->m_Alarm[i] > -100 && (*iter)->m_Alarm[i] <= 0)
					{
						(*iter)->m_Alarm[i] = -100;
						(*iter)->m_AlarmFunc(i);
					}
				}

				for (auto& Comp : (*iter)->m_Components)
				{
					Comp->Update();
				}
				if ((*iter)->GetComponent<cCollider>() != nullptr)
				{
					CollisionCheck(*iter);
				}
				iter++;
			}
			else
			{
				(*iter)->Release();
				iter = m_Objects[i].erase(iter);
			}
		}
	}
}

void cObjectManager::Render()
{
	m_RenderObjects.sort([&](cObject* Next, cObject* Prev)->bool {return Next->GetDepth() > Prev->GetDepth(); });
	for (auto& iter = m_RenderObjects.begin(); iter != m_RenderObjects.end();)
	{
		if ((*iter)->m_Components.size() == 0)
		{
			SAFE_DELETE(*iter);
			iter = m_RenderObjects.erase(iter);
			continue;
		}
		for (auto& Comp : (*iter)->m_Components)
		{
			Comp->Render();
		}
		iter++;
	}
}

void cObjectManager::Release()
{
	for (int i = 0; i < Tag::End; i++)
	{
		for (auto& iter : m_Objects[i])
		{
			iter->Release();
			SAFE_DELETE(iter);
		}
	}
	SAFE_DELETE_ARRAY(m_Objects);
}

void cObjectManager::CollisionCheck(cObject * Object)
{
	cCollider* SelfColl = Object->GetComponent<cCollider>();
	cCollider* OtherColl;
	for (auto& Tag : SelfColl->m_CollList)
	{
		for (auto& iter : m_Objects[Tag])
		{
			OtherColl = iter->GetComponent<cCollider>();
			if (OtherColl == nullptr) continue;

			for (int i = 0; i < SelfColl->m_ColliderCount; i++)
			{
				for (int j = 0; j < OtherColl->m_ColliderCount; j++)
				{
					if (D3DXVec2Length(&(SelfColl->m_Colliders[i]->WorldPos - OtherColl->m_Colliders[j]->WorldPos)) <= SelfColl->m_Colliders[i]->Size + OtherColl->m_Colliders[j]->Size)
					{
						SelfColl->m_CollFunc(iter);
					}
				}
			}
		}
	}
}

cObject * cObjectManager::AddObject(string Name, Vec2 Pos, Tag Tag, int Depth)
{
	cObject* a = new cObject;
	a->m_Name = Name;
	a->m_Pos = Pos;
	a->m_Tag = Tag;
	a->m_Depth = Depth;
	m_Objects[Tag].push_back(a);
	m_RenderObjects.push_back(a);
	return a;
}

void cObjectManager::Find(list<cObject*>* List, string Name, Tag Tag)
{
	for (auto& iter : m_Objects[Tag])
	{
		if (iter->GetName() == Name)
		{
			(*List).push_back(iter);
		}
	}
}

void cObjectManager::Find(list<cObject*>* List, Tag Tag)
{
	(*List) = m_Objects[Tag];
}

void cObjectManager::ClearAll()
{
	for (int i = 0; i < Tag::End; i++)
	{
		for (auto& iter : m_Objects[i])
		{
			iter->Release();
			SAFE_DELETE(iter);
		}
		m_Objects[i].clear();
	}
	m_RenderObjects.clear();
}
