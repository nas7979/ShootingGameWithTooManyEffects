#include "DXUT.h"
#include "cZako.h"
#include "cBulletBase.h"
#include "cItem.h"
#include "cBullet_BFG.h"

cZako::cZako(cObject* Owner)
	:cEnemyBase(Owner)
{
}


cZako::~cZako()
{
}

void cZako::Init()
{
	AddComponent<cPath>();
	AddComponent<cCollider>()->AddCollList(Tag::PlayerBullet);
	GetComponent<cCollider>()->AddCollList(Tag::Player);
	AddComponent<cRenderer>()->SetImage(IMAGE->Find(m_pObject->GetName()));

	GetComponent<cCollider>()->SetCollFunc([&](cObject* Other)->void
	{
		switch (Other->GetTag())
		{
		case Tag::PlayerBullet:
			{
			if (Other->GetDestroyed()) break;
			float Size = GetComponent<cCollider>()->GetCollider(0)->Size;
			m_Hp -= Other->GetComponent<cBulletBase>()->GetDamage();
			Other->Destroy();
			GetComponent<cRenderer>()->SetColor(D3DCOLOR_XRGB(255, 0, 0));
			m_pObject->Alarm(0, 3);

			if (Other->GetName() == "Wep_Default_Bullet" || Other->GetName() == "Wep_Chain_Bullet")
			{
				char Name[25];
				sprintf(Name, "Smoke%d", (rand() % 3) + 1);
				Vec2 Offset = Vec2(Random(-Size, Size), Random(-Size, Size)) * 0.5;
				cParticle_Base* a = PARTICLE->AddParticle(IMAGE->Find(Name), Offset + Other->GetPosition(), Random(0, 359), true, D3DCOLOR_XRGB(30, 30, 30));
				PARTICLE->SetScale(a, Vec2(0.3, 0.3) * Random(0.75f, 1.25f), Vec2(-0.002, -0.002), 1);
				PARTICLE->SetAlpha(a, 255, -5, 1.1);
				for (int i = 0; i < 10; i++)
				{
					a = PARTICLE->AddParticle(IMAGE->Find("Burst"), Offset + Other->GetPosition() + Vec2(Random(-15.f, 15.f), Random(-15.f, 15.f)), Random(0, 359), true, D3DCOLOR_XRGB(255, Random(30, 130), 30));
					PARTICLE->SetScale(a, Vec2(0.15, 0.15) * Random(0.5f, 1.5f), Vec2(-0.002, -0.002), 1.2);
					PARTICLE->SetAlpha(a, Random(100, 255), 0, 1);
				}
				sprintf(Name, "Wep_Default_Hit%d", (rand() % 9) + 1);
				LPDIRECTSOUNDBUFFER Snd = SOUND->Play(Name);
				Snd->SetVolume(TOVOLUME(75));
				Snd->SetFrequency(30000);
			}
			else if (Other->GetName() == "Wep_Plasma_Bullet")
			{
				cParticle_Base* a = PARTICLE->AddParticle(IMAGE->Find("Burst"), Vec2(Random(-Size, Size), Random(-Size, Size)) * 0.5 + Other->GetPosition(), Random(0, 359), true, D3DCOLOR_XRGB(0, 125, 255));
				PARTICLE->SetScale(a, Vec2(0.6, 0.6) * Random(0.75f, 1.25f), Vec2(-0.075, -0.075), 1.2);
				char Name[25];
				for (int i = 0; i < 4; i++)
				{
					sprintf(Name, "Spark%d", (rand() % 4) + 1);
					a = PARTICLE->AddParticle(IMAGE->Find(Name), m_pObject->GetPosition() + Vec2(Random(-Size, Size), Random(-Size, Size)), Random(0, 359), true, D3DCOLOR_XRGB(0, Random(50, 150), 255));
					PARTICLE->SetScale(a, Vec2(0.15, 0.15) * Random(0.5f, 1.f), Vec2(0, 0), 1);
					PARTICLE->SetAlpha(a, Random(3, 6) * 255, -255, 1);
				}
				sprintf(Name, "Wep_Plasma_Hit%d", (rand() % 3) + 1);
				LPDIRECTSOUNDBUFFER Snd = SOUND->Play(Name);
				Snd->SetVolume(TOVOLUME(81));
				if (m_Hp <= 0)
				{
					m_Killedby = Killedby::Plasma;
				}
			}
			else if (Other->GetName() == "Wep_Rocket_Bullet")
			{
				cParticle_Anim* a = PARTICLE->AddParticle<cParticle_Anim>(nullptr, m_pObject->GetPosition() + Vec2(Random(-Size, Size), Random(-Size, Size)), Random(0, 359), true);
				a->SetAnimation(IMAGE->FindAnimation("Explosion_Small"), 1);
				a->SetFrame(Random(0, 5));
				PARTICLE->SetScale(a, Vec2(1, 1) * Random(0.75f, 1.5f), Vec2(0, 0), 1);
				if (m_Hp <= 0)
				{
					m_Killedby = Killedby::Rocket;
				}
				LPDIRECTSOUNDBUFFER Snd = SOUND->Play("Wep_Rocket_Hit");
				Snd->SetFrequency(Random(40000, 50000));
				Snd->SetVolume(TOVOLUME(98));
			}
			else if (Other->GetName() == "Melee_Bullet")
			{
				Vec2 Offset = Vec2(Random(-Size, Size), Random(-Size, Size)) * 0.5;
				cParticle_Base* a = PARTICLE->AddParticle(IMAGE->Find("Smoke1"), Offset + Other->GetPosition(), Random(0, 359), true, D3DCOLOR_XRGB(30, 30, 30));
				PARTICLE->SetScale(a, Vec2(0.3, 0.3) * Random(0.75f, 1.25f), Vec2(-0.002, -0.002), 1);
				PARTICLE->SetAlpha(a, 255, -5, 1.1);
				for (int i = 0; i < 10; i++)
				{
					a = PARTICLE->AddParticle(IMAGE->Find("Burst"), Offset + Other->GetPosition() + Vec2(Random(-15.f, 15.f), Random(-15.f, 15.f)), Random(0, 359), true, D3DCOLOR_XRGB(255, Random(30, 130), 30));
					PARTICLE->SetScale(a, Vec2(0.15, 0.15) * Random(0.5f, 1.5f), Vec2(-0.002, -0.002), 1.2);
					PARTICLE->SetAlpha(a, Random(100, 255), 0, 1);
				}
				if (m_Hp <= 0)
				{
					m_Killedby = Killedby::Melee;
				}
			}
			else if (Other->GetName() == "Wep_BFG_Bullet")
			{
				Other->GetComponent<cBullet_BFG>()->Explode();
				if (m_Hp <= 0)
				{
					m_Killedby = Killedby::BFG;
				}
			}
			break;
			}
		}
	});

	m_Score = 0;

	m_pObject->SetAlarmSize(1);
	m_pObject->SetAlarmFunc([&](int Index)->void
	{
		switch (Index)
		{
		case 0:
		{
			GetComponent<cRenderer>()->SetColor(D3DCOLOR_XRGB(255, 255, 255));
			break;
		}
		}
	});
}

void cZako::Update()
{
	if (m_Hp <= 0)
	{
		float Size;
		cCollider* Coll = GetComponent<cCollider>();
		char Name[20];
		m_pObject->Destroy();
		sprintf(Name, "Explosion_Small%d", (rand() % 4) + 1);
		SOUND->Play(Name)->SetVolume(TOVOLUME(87));
		CAMERA->Shake(20, 8);
		SYSTEM->AddScore(m_Score);
		for (int i = 0; i < Coll->GetColliderCount(); i++)
		{
			Size = Coll->GetCollider(i)->Size;
			for (int j = 0; j < 4; j++)
			{
				cParticle_Anim* a = PARTICLE->AddParticle<cParticle_Anim>(nullptr, Coll->GetCollider(i)->WorldPos + Vec2(Random(-Size, Size), Random(-Size, Size)), Random(0, 359), true);
				a->SetAnimation(IMAGE->FindAnimation("Explosion_Small"), 1);
				a->SetFrame(Random(0, 10));
				PARTICLE->SetScale(a, Vec2(1, 1) * Random(0.75f, 1.5f), Vec2(0, 0), 1);
			}
		}

		cParticle_Emitter* b;
		switch (m_Killedby)
		{
		case Killedby::Sniper:
		{
			SYSTEM->SetTimeScale(0.2, 20);
			CAMERA->Shake(30, 15);
			for (int i = 0; i < Coll->GetColliderCount(); i++)
			{
				Size = Coll->GetCollider(i)->Size;
				for (int j = 0; j < 5; j++)
				{
					sprintf(Name, "Debris%d", (rand() % 6) + 1);
					b = PARTICLE->AddParticle<cParticle_Emitter>(IMAGE->Find(Name), Coll->GetCollider(i)->WorldPos + Vec2(Random(-Size, Size), Random(-Size, Size)), 0, false);
					PARTICLE->SetScale(b, Vec2(0.5, 0.5) * Random(0.75f, 1.25f), Vec2(-0.001, -0.001), 1.03);
					PARTICLE->SetSpeed(b, Random(2.f, 3.f), 0.99, Random(0, 359));
					PARTICLE->SetRotation(b, Random(0, 356), Random(-0.3f, 0.3f), 0.99);
					b->SetEmitterFunc(3, [&](cParticle_Emitter* Part)->void
					{
						char Name[10];
						sprintf(Name, "Smoke%d", (rand() % 3) + 1);
						cParticle_Base* a = PARTICLE->AddParticle(IMAGE->Find(Name), Part->m_Pos, Random(0, 359), false, D3DCOLOR_XRGB(70, 40, 40));
						PARTICLE->SetScale(a, Vec2(0.3, 0.3) * Part->m_Scale.x, Vec2(-0.001, -0.001), 1);
						PARTICLE->SetAlpha(a, 200, -2, 1.1);
						sprintf(Name, "Spark%d", (rand() % 4) + 1);
						a = PARTICLE->AddParticle(IMAGE->Find(Name), Part->m_Pos + Vec2(Random(-5.f, 5.f), Random(-5.f, 5.f)), Random(0, 359), true, D3DCOLOR_XRGB(255, Random(0, 50), Random(0, 50)));
						PARTICLE->SetScale(a, Vec2(0.1, 0.1) * Part->m_Scale.x, Vec2(0, 0), 1);
						PARTICLE->SetAlpha(a, Random(3, 6) * 255, -255, 1);
					});
				}
			}
			cParticle_Base* c = PARTICLE->AddParticle(IMAGE->Find("Circle1"), m_pObject->GetPosition(), 0, true, D3DCOLOR_XRGB(255, 0, 0));
			PARTICLE->SetScale(c, Vec2(0.05, 0.05), Vec2(0.075, 0.075), 1);
			PARTICLE->SetAlpha(c, 255, -30, 1);
			break;
		}
		case Killedby::Other:
		{
			for (int i = 0; i < Coll->GetColliderCount(); i++)
			{
				Size = Coll->GetCollider(i)->Size;
				for (int j = 0; j < 5; j++)
				{
					sprintf(Name, "Debris%d", (rand() % 6) + 1);
					b = PARTICLE->AddParticle<cParticle_Emitter>(IMAGE->Find(Name), Coll->GetCollider(i)->WorldPos + Vec2(Random(-Size, Size), Random(-Size, Size)), 0, false);
					PARTICLE->SetScale(b, Vec2(0.5, 0.5) * Random(0.75f, 1.25f), Vec2(-0.001, -0.001), 1.03);
					PARTICLE->SetSpeed(b, Random(2.f, 3.f), 0.99, Random(0, 359));
					PARTICLE->SetRotation(b, Random(0, 356), Random(-0.3f, 0.3f), 0.99);
					b->SetEmitterFunc(3, [&](cParticle_Emitter* Part)->void
					{
						char Name[10];
						sprintf(Name, "Smoke%d", (rand() % 3) + 1);
						cParticle_Base* a = PARTICLE->AddParticle(IMAGE->Find(Name), Part->m_Pos, Random(0, 359), false, D3DCOLOR_XRGB(40, 40, 40));
						PARTICLE->SetScale(a, Vec2(0.3, 0.3) * Part->m_Scale.x, Vec2(-0.001, -0.001), 1);
						PARTICLE->SetAlpha(a, 200, -2, 1.1);
					});
				}
			}
			break;
		}

		case Killedby::Plasma:
		{
			for (int i = 0; i < Coll->GetColliderCount(); i++)
			{
				Size = Coll->GetCollider(i)->Size;
				for (int j = 0; j < 5; j++)
				{
					sprintf(Name, "Debris%d", (rand() % 6) + 1);
					b = PARTICLE->AddParticle<cParticle_Emitter>(IMAGE->Find(Name), Coll->GetCollider(i)->WorldPos + Vec2(Random(-Size, Size), Random(-Size, Size)), 0, false);
					PARTICLE->SetScale(b, Vec2(0.5, 0.5) * Random(0.75f, 1.25f), Vec2(-0.001, -0.001), 1.03);
					PARTICLE->SetSpeed(b, Random(2.f, 3.f), 0.99, Random(0, 359));
					PARTICLE->SetRotation(b, Random(0, 356), Random(-0.3f, 0.3f), 0.99);
					b->SetEmitterFunc(3, [&](cParticle_Emitter* Part)->void
					{
						char Name[10];
						sprintf(Name, "Smoke%d", (rand() % 3) + 1);
						cParticle_Base* a = PARTICLE->AddParticle(IMAGE->Find(Name), Part->m_Pos, Random(0, 359), false, D3DCOLOR_XRGB(40, 40, 70));
						PARTICLE->SetScale(a, Vec2(0.3, 0.3) * Part->m_Scale.x, Vec2(-0.001, -0.001), 1);
						PARTICLE->SetAlpha(a, 200, -2, 1.1);
						sprintf(Name, "Spark%d", (rand() % 4) + 1);
						a = PARTICLE->AddParticle(IMAGE->Find(Name), Part->m_Pos + Vec2(Random(-5.f, 5.f), Random(-5.f, 5.f)), Random(0, 359), true, D3DCOLOR_XRGB(0, Random(50, 150), 255));
						PARTICLE->SetScale(a, Vec2(0.1, 0.1) * Part->m_Scale.x, Vec2(0, 0), 1);
						PARTICLE->SetAlpha(a, Random(3, 6) * 255, -255, 1);
					});
				}
			}
			cParticle_Base* c = PARTICLE->AddParticle(IMAGE->Find("Circle1"), m_pObject->GetPosition(), 0, true, D3DCOLOR_XRGB(0, 125, 255));
			PARTICLE->SetScale(c, Vec2(0.05, 0.05), Vec2(0.075, 0.075), 1);
			PARTICLE->SetAlpha(c, 255, -30, 1);
			break;
		}

		case Killedby::Rocket:
		{
			for (int i = 0; i < Coll->GetColliderCount(); i++)
			{
				Size = Coll->GetCollider(i)->Size;
				for (int j = 0; j < 5; j++)
				{
					sprintf(Name, "Debris%d", (rand() % 6) + 1);
					b = PARTICLE->AddParticle<cParticle_Emitter>(IMAGE->Find(Name), Coll->GetCollider(i)->WorldPos + Vec2(Random(-Size, Size), Random(-Size, Size)), 0, false);
					PARTICLE->SetScale(b, Vec2(0.5, 0.5) * Random(0.75f, 1.25f), Vec2(-0.001, -0.001), 1.03);
					PARTICLE->SetSpeed(b, Random(2.f, 3.f), 0.99, Random(0, 359));
					PARTICLE->SetRotation(b, Random(0, 356), Random(-0.3f, 0.3f), 0.99);
					b->SetEmitterFunc(3, [&](cParticle_Emitter* Part)->void
					{
						char Name[10];
						sprintf(Name, "Smoke%d", (rand() % 3) + 1);
						cParticle_Base* a = PARTICLE->AddParticle(IMAGE->Find(Name), Part->m_Pos, Random(0, 359), false, D3DCOLOR_XRGB(40, 40, 40));
						PARTICLE->SetScale(a, Vec2(0.3, 0.3) * Part->m_Scale.x, Vec2(-0.001, -0.001), 1);
						PARTICLE->SetAlpha(a, 200, -2, 1.1);
						sprintf(Name, "Flame%d", (rand() % 4) + 1);
						a = PARTICLE->AddParticle(IMAGE->Find(Name), Part->m_Pos + Vec2(Random(-15.f, 15.f), Random(-15.f, 15.f)) * Part->m_Scale.x, Random(0, 359), false, D3DCOLOR_XRGB(255, Random(25, 125), 0));
						PARTICLE->SetScale(a, Vec2(0.11, 0.11) * Part->m_Scale.x, Vec2(-0.002, -0.002), 1.1);
						PARTICLE->SetAlpha(a, 200, -1, 1);
					});
				}
			}
			break;
		}

		case Killedby::Melee:
		{
			SYSTEM->SetTimeScale(0.1, 30);
			CAMERA->Shake(45, 25);
			for (int i = 0; i < Coll->GetColliderCount(); i++)
			{
				Size = Coll->GetCollider(i)->Size;
				for (int j = 0; j < 5; j++)
				{
					sprintf(Name, "Debris%d", (rand() % 6) + 1);
					b = PARTICLE->AddParticle<cParticle_Emitter>(IMAGE->Find(Name), Coll->GetCollider(i)->WorldPos + Vec2(Random(-Size, Size), Random(-Size, Size)), 0, false);
					PARTICLE->SetScale(b, Vec2(0.5, 0.5) * Random(0.75f, 1.25f), Vec2(-0.001, -0.001), 1.03);
					PARTICLE->SetSpeed(b, Random(2.f, 3.f), 0.99, Random(0, 359));
					PARTICLE->SetRotation(b, Random(0, 356), Random(-0.3f, 0.3f), 0.99);
					b->SetEmitterFunc(3, [&](cParticle_Emitter* Part)->void
					{
						char Name[10];
						sprintf(Name, "Smoke%d", (rand() % 3) + 1);
						cParticle_Base* a = PARTICLE->AddParticle(IMAGE->Find(Name), Part->m_Pos, Random(0, 359), false, D3DCOLOR_XRGB(30, 10, 10));
						PARTICLE->SetScale(a, Vec2(0.3, 0.3) * Part->m_Scale.x, Vec2(-0.001, -0.001), 1);
						PARTICLE->SetAlpha(a, 200, -2, 1.1);
					});
				}
			}
			cObject* a;
			for (int i = 0; i < 5; i++)
			{
				a = OBJECT->AddObject("Item_Plasma", m_pObject->GetPosition(), Tag::Item, 4);
				a->AddComponent<cItem>();
				a = OBJECT->AddObject("Item_Chain", m_pObject->GetPosition(), Tag::Item, 4);
				a->AddComponent<cItem>();
			}
			a = OBJECT->AddObject("Item_Rocket", m_pObject->GetPosition(), Tag::Item, 4);
			a->AddComponent<cItem>();
			a = OBJECT->AddObject("Item_Rocket", m_pObject->GetPosition(), Tag::Item, 4);
			a->AddComponent<cItem>();
			a = OBJECT->AddObject("Item_Sniper", m_pObject->GetPosition(), Tag::Item, 4);
			a->AddComponent<cItem>();
			break;
		}

		case Killedby::BFG:
		{
			for (int i = 0; i < Coll->GetColliderCount(); i++)
			{
				Size = Coll->GetCollider(i)->Size;
				for (int j = 0; j < 5; j++)
				{
					sprintf(Name, "Debris%d", (rand() % 6) + 1);
					b = PARTICLE->AddParticle<cParticle_Emitter>(IMAGE->Find(Name), Coll->GetCollider(i)->WorldPos + Vec2(Random(-Size, Size), Random(-Size, Size)), 0, false);
					PARTICLE->SetScale(b, Vec2(0.5, 0.5) * Random(0.75f, 1.25f), Vec2(-0.001, -0.001), 1.03);
					PARTICLE->SetSpeed(b, Random(2.f, 3.f), 0.99, Random(0, 359));
					PARTICLE->SetRotation(b, Random(0, 356), Random(-0.3f, 0.3f), 0.99);
					b->SetEmitterFunc(3, [&](cParticle_Emitter* Part)->void
					{
						char Name[10];
						sprintf(Name, "Smoke%d", (rand() % 3) + 1);
						cParticle_Base* a = PARTICLE->AddParticle(IMAGE->Find(Name), Part->m_Pos, Random(0, 359), false, D3DCOLOR_XRGB(40, 70, 40));
						PARTICLE->SetScale(a, Vec2(0.3, 0.3) * Part->m_Scale.x, Vec2(-0.001, -0.001), 1);
						PARTICLE->SetAlpha(a, 200, -2, 1.1);
						sprintf(Name, "Spark%d", (rand() % 4) + 1);
						a = PARTICLE->AddParticle(IMAGE->Find(Name), Part->m_Pos + Vec2(Random(-5.f, 5.f), Random(-5.f, 5.f)), Random(0, 359), true, D3DCOLOR_XRGB(Random(100, 150), 255, Random(0, 150)));
						PARTICLE->SetScale(a, Vec2(0.1, 0.1) * Part->m_Scale.x, Vec2(0, 0), 1);
						PARTICLE->SetAlpha(a, Random(3, 6) * 255, -255, 1);
					});
				}
			}
			cParticle_Base* c = PARTICLE->AddParticle(IMAGE->Find("Circle1"), m_pObject->GetPosition(), 0, true, D3DCOLOR_XRGB(120, 255, 110));
			PARTICLE->SetScale(c, Vec2(0.05, 0.05), Vec2(0.075, 0.075), 1);
			PARTICLE->SetAlpha(c, 255, -30, 1);
			break;
		}
		}
	}
}

void cZako::Render()
{
}

void cZako::Release()
{
}
