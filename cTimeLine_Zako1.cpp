#include "DXUT.h"
#include "cTimeLine_Zako1.h"
#include "cBullet_Friction.h"
#include "cEnemyBase.h"


cTimeLine_Zako1::cTimeLine_Zako1(cObject* Owner)
	:cTimeLine(Owner)
{
}


cTimeLine_Zako1::~cTimeLine_Zako1()
{
}

void cTimeLine_Zako1::Init()
{
	m_BulletImage = IMAGE->Find("Bullet2");
	m_pObject->GetComponent<cEnemyBase>()->SetScore(1000);
	m_pObject->GetComponent<cEnemyBase>()->SetHp(75);
}

void cTimeLine_Zako1::Update()
{
	m_pObject->SetRotation(GetComponent<cPath>()->GetDirection());
	if (m_Cur != m_Last)
	{
		switch ((int)m_Cur)
		{
		case 90:
		{
			cObject* a;
			for (int i = -1; i <= 1; i++)
			{
				a = OBJECT->AddObject("EnemyBullet", m_pObject->GetPosition(), Tag::EnemyBullet, 0);
				a->AddComponent<cBullet_Friction>()->SetDirection(m_pObject->GetRotation() + i * 20);
				a->GetComponent<cBullet_Friction>()->SetSpeed(10);
				a->GetComponent<cBullet_Friction>()->SetFriction(0.98, 5);
				a->GetComponent<cRenderer>()->SetImage(m_BulletImage);
				a->GetComponent<cRenderer>()->SetColor(D3DCOLOR_XRGB(255, 0, 0));
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

	Vec2 Pos = m_pObject->GetPosition();
	float Size = 128;
	if (Pos.x - Size > 1000 || Pos.x + Size < 0 || Pos.y - Size > WINSIZEY || Pos.y + Size < 0)
	{
		m_pObject->Destroy();
	}
}

void cTimeLine_Zako1::Render()
{
}

void cTimeLine_Zako1::Release()
{
}
