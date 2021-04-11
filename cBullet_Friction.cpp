#include "DXUT.h"
#include "cBullet_Friction.h"


cBullet_Friction::cBullet_Friction(cObject* Owner)
	:cBulletBase(Owner)
{
}


cBullet_Friction::~cBullet_Friction()
{
}

void cBullet_Friction::Init()
{
	AddComponent<cRenderer>();
	AddComponent<cCollider>();
}

void cBullet_Friction::Update()
{
	float TimeScale = SYSTEM->GetTimeScale();
	m_Speed *= pow(m_Friction, 1 / (1 / TimeScale));
	if (m_Friction > 1)
	{
		if (m_Speed >= m_EndSpeed)
		{
			m_Speed = m_EndSpeed;
			m_Friction = 1;
		}
	}
	else
	{
		if (m_Speed <= m_EndSpeed)
		{
			m_Speed = m_EndSpeed;
			m_Friction = 1;
		}
	}
	m_pObject->Translate(Vec2(cos(m_Direction), sin(m_Direction)) * m_Speed * TimeScale);
	if (IsOutMap())
	{
		m_pObject->Destroy();
	}
	if (m_RotateAssigntoDirection)
	{
		m_pObject->SetRotation(D3DXToDegree(m_Direction));
	}
}

void cBullet_Friction::Render()
{
}

void cBullet_Friction::Release()
{
}
