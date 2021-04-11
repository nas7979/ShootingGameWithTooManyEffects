#include "DXUT.h"
#include "cPath.h"


cPath::cPath(cObject* Owner)
	:cComponent(Owner)
{
}


cPath::~cPath()
{
}

void cPath::Init()
{
	m_Speed = 0;
	m_Direction = 0;
	m_Friction = 1;
	m_NextPoint = 0;
}

void cPath::Update()
{
	if (m_Points.size() != 0)
	{
		float TimeScale = SYSTEM->GetTimeScale();
		Vec2 Next = m_Points[m_NextPoint];
		m_Speed *= pow(m_Friction, 1 / (1 / TimeScale));
		m_pObject->Translate(Vec2(cos(m_Direction), sin(m_Direction)) * m_Speed * TimeScale);
		if (D3DXVec2Length(&(m_pObject->GetPosition() - Next)) <= m_Speed + 0.1)
		{
			m_NextPoint++;
			m_pObject->SetPosition(Next);
			if (m_NextPoint == m_Points.size())
			{
				m_Speed = 0;
				m_NextPoint--;
			}
			else
			{
				m_Direction = RadAngle(m_pObject->GetPosition(), m_Points[m_NextPoint]);
			}
		}
	}
}

void cPath::Render()
{
}

void cPath::Release()
{
}

void cPath::AddPath(Vec2 Goal, Vec2 Cont)
{
	if (Cont == Vec2(-1, -1))
	{
		m_Points.push_back(Goal);
		if (m_Points.size() == 1)
		{
			m_NextPoint = 0;
			m_Direction = RadAngle(m_pObject->GetPosition(), m_Points[0]);
		}
	}
	else
	{
		Vec2 v1, v2, v3;
		Vec2 Cur = m_pObject->GetPosition();
		for (int i = 1; i <= 20; i++)
		{
			D3DXVec2Lerp(&v1, &Cur, &Cont, 0.05 * i);
			D3DXVec2Lerp(&v2, &Cont, &Goal, 0.05 * i);
			D3DXVec2Lerp(&v3, &v1, &v2, 0.05 * i);
			m_Points.push_back(v3);
		}
		if (m_Points.size() == 20)
		{
			m_NextPoint = 0;
			m_Direction = RadAngle(m_pObject->GetPosition(), m_Points[0]);
		}
	}
}
