#include "DXUT.h"
#include "cBullet.h"


cBullet::cBullet(cObject * Owner)
	:cBulletBase(Owner)
{
}

cBullet::~cBullet()
{
}

void cBullet::Init()
{
	AddComponent<cRenderer>();
	AddComponent<cCollider>();
}

void cBullet::Update()
{
	m_pObject->Translate(Vec2(cos(m_Direction), sin(m_Direction)) * m_Speed * SYSTEM->GetTimeScale());
	if (IsOutMap())
	{
		m_pObject->Destroy();
	}
	if (m_RotateAssigntoDirection)
	{
		m_pObject->SetRotation(D3DXToDegree(m_Direction));
	}
}

void cBullet::Render()
{
}

void cBullet::Release()
{
}
