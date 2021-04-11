#include "DXUT.h"
#include "cBullet_Homing.h"
#include "cEnemyBase.h"


cBullet_Homing::cBullet_Homing(cObject* Owner)
	:cBulletBase(Owner)
{
}


cBullet_Homing::~cBullet_Homing()
{
}

void cBullet_Homing::Init()
{
	AddComponent<cRenderer>();
	AddComponent<cCollider>();

	m_Target = nullptr;
	m_RotateSpeed = 1;
	m_RotateSpeedVel = 0;
}

void cBullet_Homing::Update()
{
	float TimeScale = SYSTEM->GetTimeScale();

	char Name[10];
	sprintf(Name, "Smoke%d", (rand() % 3) + 1);
	cParticle_Base* a = PARTICLE->AddParticle(IMAGE->Find(Name), m_pObject->GetPosition(), Random(0, 359), false, D3DCOLOR_XRGB(40, 40, 40));
	PARTICLE->SetScale(a, Vec2(0.1, 0.1), Vec2(-0.0005, -0.0005), 1);
	PARTICLE->SetAlpha(a, 255, -1, 1.1);
	sprintf(Name, "Flame%d", (rand() % 4) + 1);
	a = PARTICLE->AddParticle(IMAGE->Find(Name), m_pObject->GetPosition(), Random(0, 359), false, D3DCOLOR_XRGB(255, Random(25, 125), 0));
	PARTICLE->SetScale(a, Vec2(0.05, 0.05), Vec2(-0.002, -0.002), 1.1);
	PARTICLE->SetAlpha(a, 200, -1, 1);

	m_RotateSpeed += m_RotateSpeedVel;
	if (m_Target)
	{
		if (m_Target->GetDestroyed())
		{
			m_Target = nullptr;
		}
		else
		{
			Vec2 Vec;
			D3DXVec2Normalize(&Vec, &(m_Target->GetPosition() - m_pObject->GetPosition()));
			m_Direction += m_RotateSpeed * D3DXVec2Dot(&RotateVec(Vec2(0, 1), D3DXToDegree(m_Direction)), &Vec) * TimeScale;
		}
	}
	m_pObject->Translate(Vec2(cos(m_Direction), sin(m_Direction)) * m_Speed * TimeScale);
	if (IsOutMap() && m_Target == nullptr)
	{
		m_pObject->Destroy();
	}
	if (m_RotateAssigntoDirection)
	{
		m_pObject->SetRotation(D3DXToDegree(m_Direction));
	}
}

void cBullet_Homing::Render()
{
}

void cBullet_Homing::Release()
{
}
