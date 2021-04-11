#include "DXUT.h"
#include "cTimeLine_Zako7.h"
#include "cBullet_Friction.h"
#include "cEnemyBase.h"


cTimeLine_Zako7::cTimeLine_Zako7(cObject* Owner)
	:cTimeLine(Owner)
{
}


cTimeLine_Zako7::~cTimeLine_Zako7()
{
}

void cTimeLine_Zako7::Init()
{
	m_pObject->GetComponent<cEnemyBase>()->SetScore(1500);
	m_pObject->GetComponent<cEnemyBase>()->SetHp(100);
	m_Direction = D3DXToRadian(270);
}

void cTimeLine_Zako7::Update()
{
	float TimeScale = SYSTEM->GetTimeScale();
	Vec2 Vec;
	D3DXVec2Normalize(&Vec, &(OBJECT->GetPlayer()->GetPosition() - m_pObject->GetPosition()));
	m_Direction += 0.06 * D3DXVec2Dot(&RotateVec(Vec2(0, 1), D3DXToDegree(m_Direction)), &Vec) * TimeScale;

	m_pObject->Translate(Vec2(cos(m_Direction), sin(m_Direction)) * 7 * TimeScale);
	m_pObject->SetRotation(D3DXToDegree(m_Direction));
}

void cTimeLine_Zako7::Render()
{
}

void cTimeLine_Zako7::Release()
{
}
