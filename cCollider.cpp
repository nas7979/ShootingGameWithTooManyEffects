#include "DXUT.h"
#include "cCollider.h"


cCollider::cCollider(cObject* Owner)
	:cComponent(Owner)
{
}


cCollider::~cCollider()
{
}

void cCollider::Init()
{
	m_ColliderCount = 0;
	m_Colliders = nullptr;
}

void cCollider::Update()
{
	for (int i = 0; i < m_ColliderCount; i++)
	{
		m_Colliders[i]->WorldPos = m_pObject->GetPosition() + RotateVec(m_Colliders[i]->LocalPos, m_pObject->GetRotation());
	}
}

void cCollider::Render()
{
	//for (int i = 0; i < m_ColliderCount; i++)
	//{
	//	IMAGE->CenterRender(IMAGE->Find("Coll_Circle"), m_Colliders[i]->WorldPos, 0, Vec2(0.02, 0.02) * m_Colliders[i]->Size);
	//}
}

void cCollider::Release()
{
	for (int i = 0; i < m_ColliderCount; i++)
	{
		SAFE_DELETE(m_Colliders[i]);
	}
	SAFE_DELETE_ARRAY(m_Colliders);
}

void cCollider::SetColliderCount(int Count)
{
	m_ColliderCount = Count;
	m_Colliders = new Collider*[Count];
	for (int i = 0; i < m_ColliderCount; i++)
	{
		m_Colliders[i] = nullptr;
	}
}

void cCollider::AddCollider(Vec2 Pos, float Size)
{
	for (int i = 0; i < m_ColliderCount; i++)
	{
		if (m_Colliders[i] == nullptr)
		{
			m_Colliders[i] = new Collider(Pos, Size);
			m_Colliders[i]->WorldPos = m_pObject->GetPosition() + RotateVec(m_Colliders[i]->LocalPos, m_pObject->GetRotation());
			return;
		}
	}
}
