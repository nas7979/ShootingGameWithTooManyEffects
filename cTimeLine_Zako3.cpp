#include "DXUT.h"
#include "cTimeLine_Zako3.h"
#include "cBullet_Friction.h"
#include "cEnemyBase.h"


cTimeLine_Zako3::cTimeLine_Zako3(cObject* Owner)
	:cTimeLine(Owner)
{
}


cTimeLine_Zako3::~cTimeLine_Zako3()
{
}

void cTimeLine_Zako3::Init()
{
	m_BulletImage = IMAGE->Find("Bullet2");
	m_pObject->GetComponent<cEnemyBase>()->SetScore(2000);
	m_pObject->GetComponent<cEnemyBase>()->SetHp(150);
}

void cTimeLine_Zako3::Update()
{
	m_pObject->SetRotation(GetComponent<cPath>()->GetDirection());
	if (m_Cur != m_Last)
	{
		switch ((int)m_Cur)
		{
		case 90:
		{
			cObject* a;
			for (int i = 0; i < 18; i++)
			{
				a = OBJECT->AddObject("EnemyBullet", m_pObject->GetPosition(), Tag::EnemyBullet, 0);
				a->AddComponent<cBullet_Friction>()->SetDirection(i * 20);
				a->GetComponent<cBullet_Friction>()->SetSpeed(10);
				a->GetComponent<cBullet_Friction>()->SetFriction(0.95, 3);
				a->GetComponent<cRenderer>()->SetImage(m_BulletImage);
				a->GetComponent<cRenderer>()->SetColor(D3DCOLOR_XRGB(0, 255, 0));
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

void cTimeLine_Zako3::Render()
{
}

void cTimeLine_Zako3::Release()
{
}
