#include "DXUT.h"
#include "cTimeLine_Zako4.h"
#include "cBullet_Friction.h"
#include "cEnemyBase.h"


cTimeLine_Zako4::cTimeLine_Zako4(cObject* Owner)
	:cTimeLine(Owner)
{
}


cTimeLine_Zako4::~cTimeLine_Zako4()
{
}

void cTimeLine_Zako4::Init()
{
	m_BulletImage = IMAGE->Find("Bullet2");
	m_pObject->GetComponent<cEnemyBase>()->SetScore(2000);
	m_pObject->GetComponent<cEnemyBase>()->SetHp(150);
}

void cTimeLine_Zako4::Update()
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
		case 40:
		case 60:
		case 80:
		{
			cObject* a;
			for (int i = -1; i <= 1; i += 2)
			{
				for (int j = -1; j <= 1; j += 2)
				{
					a = OBJECT->AddObject("EnemyBullet", m_pObject->GetPosition() + RotateVec(Vec2(0,i * 20), m_pObject->GetRotation()), Tag::EnemyBullet, 0);
					a->AddComponent<cBullet_Friction>()->SetDirection(m_pObject->GetRotation() + j * 15 - 180);
					a->GetComponent<cBullet_Friction>()->SetSpeed(10);
					a->GetComponent<cBullet_Friction>()->SetFriction(0.95, 5);
					a->GetComponent<cRenderer>()->SetImage(m_BulletImage);
					a->GetComponent<cRenderer>()->SetColor(D3DCOLOR_XRGB(0, 255, 255));
					a->GetComponent<cCollider>()->SetColliderCount(1);
					a->GetComponent<cCollider>()->AddCollider(Vec2(0, 0), 8);
				}
			}
			break;
		}
		case 160:
		{
			m_Cur = 0;
			m_Last = 0;
			break;
		}
		}
	}
	m_Last = (int)m_Cur;
	m_Cur += SYSTEM->GetTimeScale();
}

void cTimeLine_Zako4::Render()
{
}

void cTimeLine_Zako4::Release()
{
}
