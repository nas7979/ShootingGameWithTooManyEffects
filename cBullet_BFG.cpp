#include "DXUT.h"
#include "cBullet_BFG.h"
#include "cEnemyBase.h"


cBullet_BFG::cBullet_BFG(cObject* Owner)
	:cBulletBase(Owner)
{
}


cBullet_BFG::~cBullet_BFG()
{
}

void cBullet_BFG::Init()
{
	AddComponent<cRenderer>();
	AddComponent<cCollider>();
	m_LaserImage[0] = IMAGE->Find("Laser1");
	m_LaserImage[1] = IMAGE->Find("Laser2");
	m_LaserImage[2] = IMAGE->Find("Laser3");
	m_Speed = 4;
	m_Damage = 300;

	m_pObject->SetAlarmSize(1);
	m_pObject->SetAlarmFunc([&](int Index)->void
	{
		OBJECT->Find(&m_Enemys, Tag::Enemy);
		cParticle_Base* a;
		cCollider* Coll;
		float Dist;
		float Dir;
		float Size;
		char Name[10];
		for (auto& iter : m_Enemys)
		{
			Dist = D3DXVec2Length(&(m_pObject->GetPosition() - iter->GetPosition()));
			if (Dist <= m_Range)
			{
				Coll = iter->GetComponent<cCollider>();
				iter->GetComponent<cEnemyBase>()->AddHp(-m_LaserDamage);
				for (int i = 0; i < Coll->GetColliderCount(); i++)
				{
					Size = Coll->GetCollider(i)->Size * 0.75;
					Dir = DegAngle(m_pObject->GetPosition(), Coll->GetCollider(i)->WorldPos + Vec2(Random(-Size, Size), Random(-Size, Size)));
					a = PARTICLE->AddParticle(m_LaserImage[rand() % 3], m_pObject->GetPosition() + RotateVec(Vec2(Dist * 0.5, 0), Dir), Dir, false, D3DCOLOR_XRGB(Random(100, 150), 255, Random(0, 150)));
					PARTICLE->SetScale(a, Vec2(Dist / 512, 0.25), Vec2(0, 0), 1);
					PARTICLE->SetAlpha(a, 510, -255, 1.3);
					sprintf(Name, "Spark%d", (rand() % 4) + 1);
					a = PARTICLE->AddParticle(IMAGE->Find(Name), Coll->GetCollider(i)->WorldPos + Vec2(Random(-Size, Size), Random(-Size, Size)), Random(0, 359), true, D3DCOLOR_XRGB(Random(100, 150), 255, Random(0, 150)));
					PARTICLE->SetScale(a, Vec2(0.15, 0.15) * Random(0.5f, 1.f), Vec2(0, 0), 1);
					PARTICLE->SetAlpha(a, Random(2, 4) * 255, -255, 1);
					if (iter->GetComponent<cEnemyBase>()->GetHp() <= 0)
					{
						iter->GetComponent<cEnemyBase>()->SetKilledby(Killedby::BFG);
					}
				}
			}
		}
		sprintf(Name, "Spark%d", (rand() % 4) + 1);
		a = PARTICLE->AddParticle(IMAGE->Find(Name), m_pObject->GetPosition() + Vec2(Random(-20, 20), Random(-20, 20)), Random(0, 359), true, D3DCOLOR_XRGB(Random(100, 150), 255, Random(0, 150)));
		PARTICLE->SetScale(a, Vec2(0.15, 0.15) * Random(0.5f, 1.f), Vec2(0, 0), 1);
		PARTICLE->SetAlpha(a, Random(2, 4) * 255, -255, 1);
		m_pObject->Alarm(0, 1);
	});
	m_pObject->Alarm(0, 1);
}

void cBullet_BFG::Update()
{
	m_pObject->Translate(Vec2(cos(m_Direction), sin(m_Direction)) * m_Speed * SYSTEM->GetTimeScale());
	if (IsOutMap())
	{
		Explode();
		m_pObject->Destroy();
	}
	if (m_RotateAssigntoDirection)
	{
		m_pObject->SetRotation(D3DXToDegree(m_Direction));
	}
}

void cBullet_BFG::Render()
{
}

void cBullet_BFG::Release()
{
}

void cBullet_BFG::Explode()
{
	cParticle_Anim* a = PARTICLE->AddParticle<cParticle_Anim>(nullptr, m_pObject->GetPosition(), 0, true);
	a->SetAnimation(IMAGE->FindAnimation("BFGHit"), 10);
	SOUND->Play("Wep_BFG_Hit")->SetVolume(TOVOLUME(90));

	float Dist;
	for (auto& iter : m_Enemys)
	{
		Dist = D3DXVec2Length(&(m_pObject->GetPosition() - iter->GetPosition()));
		if (Dist <= 250)
		{
			iter->GetComponent<cEnemyBase>()->AddHp(-200);
			if (iter->GetComponent<cEnemyBase>()->GetHp() <= 0)
			{
				iter->GetComponent<cEnemyBase>()->SetKilledby(Killedby::BFG);
			}
		}
	}
}
