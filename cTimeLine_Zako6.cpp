#include "DXUT.h"
#include "cTimeLine_Zako6.h"
#include "cBullet_Friction.h"
#include "cEnemyBase.h"


cTimeLine_Zako6::cTimeLine_Zako6(cObject* Owner)
	:cTimeLine(Owner)
{
}


cTimeLine_Zako6::~cTimeLine_Zako6()
{
}

void cTimeLine_Zako6::Init()
{
	m_BulletImage = IMAGE->Find("Bullet2");
	m_pObject->GetComponent<cEnemyBase>()->SetScore(2000);
	m_pObject->GetComponent<cEnemyBase>()->SetHp(150);
}

void cTimeLine_Zako6::Update()
{
	m_pObject->SetRotation(GetComponent<cPath>()->GetDirection());
	if (m_pObject->GetComponent<cPath>()->GetSpeed() == 0)
	{
		m_pObject->GetComponent<cPath>()->ClearPath();
		m_pObject->GetComponent<cPath>()->AddPath(Vec2(Random(50, 950), Random(50, 670)), Vec2(Random(50, 950), Random(50, 670)));
		m_pObject->GetComponent<cPath>()->SetSpeed(2);
	}
	if (m_Cur != m_Last)
	{
		switch ((int)m_Cur)
		{
		case 30:
		{
			cObject* a;
			a = OBJECT->AddObject("EnemyBullet", m_pObject->GetPosition(), Tag::EnemyBullet, 0);
			a->AddComponent<cBullet_Friction>()->SetDirection(DegAngle(m_pObject->GetPosition(), OBJECT->GetPlayer()->GetPosition()));
			a->GetComponent<cBullet_Friction>()->SetSpeed(0.1);
			a->GetComponent<cBullet_Friction>()->SetFriction(1.1, 8);
			a->GetComponent<cRenderer>()->SetImage(m_BulletImage);
			a->GetComponent<cRenderer>()->SetColor(D3DCOLOR_XRGB(255, 0, 255));
			a->GetComponent<cCollider>()->SetColliderCount(1);
			a->GetComponent<cCollider>()->AddCollider(Vec2(0, 0), 8);
			m_Cur = 0;
			m_Last = 0;
			break;
		}
		}
	}
	m_Last = (int)m_Cur;
	m_Cur += SYSTEM->GetTimeScale();
}

void cTimeLine_Zako6::Render()
{
}

void cTimeLine_Zako6::Release()
{
}
