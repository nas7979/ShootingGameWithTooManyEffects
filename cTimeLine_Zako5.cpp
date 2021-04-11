#include "DXUT.h"
#include "cTimeLine_Zako5.h"
#include "cBullet_Friction.h"
#include "cEnemyBase.h"


cTimeLine_Zako5::cTimeLine_Zako5(cObject* Owner)
	:cTimeLine(Owner)
{
}


cTimeLine_Zako5::~cTimeLine_Zako5()
{
}

void cTimeLine_Zako5::Init()
{
	m_BulletImage = IMAGE->Find("Bullet2");
	m_pObject->GetComponent<cEnemyBase>()->SetScore(2000);
	m_pObject->GetComponent<cEnemyBase>()->SetHp(150);
}

void cTimeLine_Zako5::Update()
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
		case 50:
		{
			cObject* a;
			for (int i = 0; i < 4; i++)
			{
				a = OBJECT->AddObject("EnemyBullet", m_pObject->GetPosition(), Tag::EnemyBullet, 0);
				a->AddComponent<cBullet_Friction>()->SetDirection(m_pObject->GetRotation() + i * 90);
				a->GetComponent<cBullet_Friction>()->SetSpeed(8);
				a->GetComponent<cBullet_Friction>()->SetFriction(0.96, 3);
				a->GetComponent<cRenderer>()->SetImage(m_BulletImage);
				a->GetComponent<cRenderer>()->SetColor(D3DCOLOR_XRGB(0, 0, 255));
				a->GetComponent<cCollider>()->SetColliderCount(1);
				a->GetComponent<cCollider>()->AddCollider(Vec2(0, 0), 8);
			}
			m_Cur = 0;
			m_Last = 0;
			break;
		}
		}
	}
	m_Last = (int)m_Cur;
	m_Cur += SYSTEM->GetTimeScale();
}

void cTimeLine_Zako5::Render()
{
}

void cTimeLine_Zako5::Release()
{
}
