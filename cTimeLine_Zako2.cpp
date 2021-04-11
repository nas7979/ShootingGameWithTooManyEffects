#include "DXUT.h"
#include "cTimeLine_Zako2.h"
#include "cBullet.h"
#include "cEnemyBase.h"


cTimeLine_Zako2::cTimeLine_Zako2(cObject* Owner)
	:cTimeLine(Owner)
{
}


cTimeLine_Zako2::~cTimeLine_Zako2()
{
}

void cTimeLine_Zako2::Init()
{
	m_BulletImage = IMAGE->Find("Bullet2");
	m_pObject->GetComponent<cEnemyBase>()->SetScore(1000);
	m_pObject->GetComponent<cEnemyBase>()->SetHp(75);
}

void cTimeLine_Zako2::Update()
{
	m_pObject->SetRotation(GetComponent<cPath>()->GetDirection());
	if (m_Cur != m_Last)
	{
		switch ((int)m_Cur)
		{
		case 60:
		{
			cObject* a;
			a = OBJECT->AddObject("EnemyBullet", m_pObject->GetPosition(), Tag::EnemyBullet, 0);
			a->AddComponent<cBullet>()->SetDirection(DegAngle(m_pObject->GetPosition(), OBJECT->GetPlayer()->GetPosition()));
			a->GetComponent<cBullet>()->SetSpeed(4);
			a->GetComponent<cRenderer>()->SetImage(m_BulletImage);
			a->GetComponent<cRenderer>()->SetColor(D3DCOLOR_XRGB(255, 255, 0));
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

	Vec2 Pos = m_pObject->GetPosition();
	float Size = 128;
	if (Pos.x - Size > 1000 || Pos.x + Size < 0 || Pos.y - Size > WINSIZEY || Pos.y + Size < 0)
	{
		m_pObject->Destroy();
	}
}

void cTimeLine_Zako2::Render()
{
}

void cTimeLine_Zako2::Release()
{
}
