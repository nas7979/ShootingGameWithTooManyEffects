#include "DXUT.h"
#include "cItem.h"


cItem::cItem(cObject* Owner)
	:cComponent(Owner)
{
}


cItem::~cItem()
{
}

void cItem::Init()
{
	AddComponent<cRenderer>()->SetImage(IMAGE->Find("Ammo"));
	AddComponent<cCollider>()->SetColliderCount(1);
	GetComponent<cCollider>()->AddCollider(Vec2(0, 0), 25);
	if (m_pObject->GetName() == "Item_Plasma")
	{
		GetComponent<cRenderer>()->SetColor(D3DCOLOR_XRGB(0, 100, 255));
	}
	else if(m_pObject->GetName() == "Item_Chain")
	{
		GetComponent<cRenderer>()->SetColor(D3DCOLOR_XRGB(255, 255, 150));
	}
	else if (m_pObject->GetName() == "Item_Rocket")
	{
		GetComponent<cRenderer>()->SetColor(D3DCOLOR_XRGB(100, 100, 100));
	}
	else if (m_pObject->GetName() == "Item_Sniper")
	{
		GetComponent<cRenderer>()->SetColor(D3DCOLOR_XRGB(255, 0, 0));
	}
	m_Speed = 0.1;
	m_Spread = Vec2(Random(-7.f, 7.f), Random(-7.f, 7.f));
}

void cItem::Update()
{
	float TimeScale = SYSTEM->GetTimeScale();
	m_Speed += 0.1 * TimeScale;
	m_Spread *= pow(0.95, 1 / (1 / TimeScale));

	Vec2 Vec;
	D3DXVec2Normalize(&Vec, &(OBJECT->GetPlayer()->GetPosition() - m_pObject->GetPosition()));
	m_pObject->Translate(m_Spread + Vec * m_Speed);
}

void cItem::Render()
{
}

void cItem::Release()
{
}
