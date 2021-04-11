#pragma once
#include "cBulletBase.h"
class cBullet_BFG : public cBulletBase
{
public:
	cBullet_BFG(cObject* Owner);
	~cBullet_BFG();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

private:
	float m_Charge;
	float m_Range;
	float m_LaserDamage;
	list<cObject*> m_Enemys;
	Texture* m_LaserImage[3];

public:
	void SetCharge(float Charge) { m_Charge = Charge; m_Range = m_Charge * 20; m_LaserDamage = m_Charge * 0.04; }
	void Explode();
};

