#include "DXUT.h"
#include "cPlayerMenu.h"
#include "cBullet.h"
#include "cBullet_Friction.h"
#include "cBullet_Homing.h"
#include "cBullet_BFG.h"
#include "cEnemyBase.h"


cPlayerMenu::cPlayerMenu(cObject* Owner)
	:cComponent(Owner)
{
}


cPlayerMenu::~cPlayerMenu()
{
}

void cPlayerMenu::Init()
{
	AddComponent<cCollider>()->SetColliderCount(1);
	GetComponent<cCollider>()->AddCollider(Vec2(0, 0), 10);
	GetComponent<cCollider>()->AddCollList(Tag::EnemyBullet);
	GetComponent<cCollider>()->AddCollList(Tag::Enemy);
	GetComponent<cCollider>()->AddCollList(Tag::Item);

	m_pObject->SetAlarmSize(10);
	m_pObject->SetAlarmFunc([&](int Index)->void
	{
		switch (Index)
		{
		case 0:
		{
			char Name[10];
			sprintf(Name, "Flame%d", (rand() % 4) + 1);
			cParticle_Base* a = PARTICLE->AddParticle(IMAGE->Find(Name), m_pObject->GetPosition() + Vec2(18, 25), rand() % 360, false, D3DCOLOR_XRGB(0, 255, 255));
			PARTICLE->SetSpeed(a, Random(1.f, 3.f), Random(0.97f, 0.985f), 90);
			PARTICLE->SetScale(a, Vec2(0.03, 0.03) * Random(0.75f, 1.25f), -Vec2(0.0025, 0.0025), 1.05);
			a = PARTICLE->AddParticle(IMAGE->Find(Name), m_pObject->GetPosition() + Vec2(-18, 25), rand() % 360, false, D3DCOLOR_XRGB(0, 255, 255));
			PARTICLE->SetSpeed(a, Random(1.f, 3.f), Random(0.97f, 0.985f), 90);
			PARTICLE->SetScale(a, Vec2(0.03, 0.03) * Random(0.75f, 1.25f), -Vec2(0.0025, 0.0025), 1.05);
			break;
		}
		case 1:
		{
			m_AttackAble = true;
			break;
		}
		case 2:
		{
			m_InDash = false;
			m_pObject->SetScale(Vec2(0.25, 0.25));
			break;
		}
		case 3:
		{
			m_Hp--;
			m_Hit = false;
			m_Dead = true;
			m_Invincible = true;
			SYSTEM->SetTimeScale(1, -1);
			list<cObject*> Temp;
			OBJECT->Find(&Temp, Tag::EnemyBullet);
			for (auto& iter : Temp)
			{
				iter->Destroy();
			}
			GetComponent<cRenderer>()->SetColor(D3DCOLOR_ARGB(0, 0, 0, 0));

			char Name[20];
			sprintf(Name, "Explosion_Small%d", (rand() % 4) + 1);
			SOUND->Play(Name)->SetVolume(TOVOLUME(90));
			CAMERA->Shake(60, 20);
			for (int i = 0; i < 6; i++)
			{
				cParticle_Anim* a = PARTICLE->AddParticle<cParticle_Anim>(nullptr, m_pObject->GetPosition() + Vec2(Random(-30, 30), Random(-30, 30)), Random(0, 359), true);
				a->SetAnimation(IMAGE->FindAnimation("Explosion_Small"), 1);
				a->SetFrame(Random(0, 10));
				PARTICLE->SetScale(a, Vec2(1, 1) * Random(0.75f, 1.5f), Vec2(0, 0), 1);
			}

			cParticle_Emitter* b;
			for (int i = 0; i < 9; i++)
			{
				sprintf(Name, "Debris%d", (rand() % 6) + 1);
				b = PARTICLE->AddParticle<cParticle_Emitter>(IMAGE->Find(Name), m_pObject->GetPosition() + Vec2(Random(-20, 20), Random(-20, 20)), 0, false);
				PARTICLE->SetScale(b, Vec2(0.7, 0.7) * Random(0.75f, 1.25f), Vec2(-0.001, -0.001), 1.03);
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
			if (m_Hp != 0)
			{
				m_pObject->Alarm(5, 50);
			}
			else
			{
				m_pObject->Alarm(7, 120);
			}
			break;
		}
		case 4:
		{
			m_DashAble = true;
			break;
		}
		case 5:
		{
			cParticle_Base* a = PARTICLE->AddParticle(IMAGE->Find(SYSTEM->GetDoot() == false ? "Cruiser3" : "Doot"), Vec2(500, 360), 0, true);
			PARTICLE->SetScale(a, Vec2(3, 3), Vec2(-0.5, -0.5), 0.9);
			PARTICLE->SetAlpha(a, 0, 20, 1);
			m_pObject->Alarm(6, 10);
			break;
		}
		case 6:
		{
			if (m_Dead)
			{
				m_pObject->SetPosition(Vec2(500, 360));
				GetComponent<cRenderer>()->SetColor(D3DCOLOR_ARGB(100, 255, 255, 255));
				m_Dead = false;
				m_pObject->Alarm(6, 60);
			}
			else
			{
				GetComponent<cRenderer>()->SetColor(D3DCOLOR_ARGB(255, 255, 255, 255));
				m_Invincible = false;
			}
			break;
		}
		case 7:
		{
			break;
		}
		case 8:
		{
			m_MeleeAble = true;
			break;
		}
		case 9:
		{
			if (m_BFGCharging != 0)
			{
				float Rot = m_Direction;
				cParticle_Emitter* a = PARTICLE->AddParticle<cParticle_Emitter>(IMAGE->Find("Circle1"), m_pObject->GetPosition() + Vec2(0, 10) + RotateVec(Vec2(35, 0), Rot), 0, true, D3DCOLOR_XRGB(120, 255, 110));
				PARTICLE->SetScale(a, Vec2(0.03, 0.03) * m_BFGCharging, Vec2(-0.0005, -0.0005) * m_BFGCharging, 1.1);
				PARTICLE->SetAlpha(a, 1, +10, 1.1);
				a->SetEmitterFunc(0, [&](cParticle_Emitter* Part)->void
				{
					Part->m_Pos = OBJECT->GetPlayer()->GetPosition() + Vec2(0, 10) + RotateVec(Vec2(35, 0), m_Direction);
				});
				m_pObject->Alarm(9, 5 + m_BFGCharging * 2);
			}
			break;
		}
		}
	});

	m_Hp = 5;
	m_Speed = 5;
	m_pObject->SetScale(Vec2(0.25, 0.25));
	m_AttackAble = true;
	m_InDash = false;
	m_Hit = false;
	m_Dead = false;
	m_DashAble = true;
	m_MeleeAble = true;
	m_Invincible = false;
	m_DashDirection = Vec2(0, 0);
	m_PlasmaAmmo = 500000;
	m_ChainAmmo = 750000;
	m_SniperAmmo = 50000;
	m_RocketAmmo = 80000;
	m_BFGCharging = 0;
	m_Direction = 270;

	m_pObject->Alarm(0, -100);

	GetComponent<cCollider>()->SetCollFunc([&](cObject* Other)->void
	{
		if (m_Dead) return;

		switch (Other->GetTag())
		{
		case Tag::EnemyBullet:
		{
			Other->Destroy();
			cParticle_Base* a = PARTICLE->AddParticle(IMAGE->Find("Circle5"), Other->GetPosition(), 0, false, Other->GetComponent<cRenderer>()->GetColor());
			PARTICLE->SetScale(a, Vec2(0.01, 0.01), Vec2(0.015, 0.015), 0.95);
			PARTICLE->SetAlpha(a, 255, -20, 1);
		}

		case Tag::Enemy:
		{
			if (m_Hit) return;
			if (m_InDash) return;
			if (m_Invincible) return;

			SOUND->Play("PlayerHit")->SetVolume(TOVOLUME(85));
			SYSTEM->SetTimeScale(0.1, -1);
			m_pObject->Alarm(3, 1);
			m_Hit = true;
			if (m_BFGCharging != 0)
			{
				m_BFGCharging = 0;
				m_BFGChargingSound->Stop();
			}
			break;
		}

		case Tag::Item:
		{
			Other->Destroy();
			SOUND->Play("Ammo")->SetVolume(TOVOLUME(85));
			break;
		}
		}
	});
}

void cPlayerMenu::Update()
{
	bool Moved = false;
	float TimeScale = SYSTEM->GetTimeScale();
	Vec2 PrevPos = m_pObject->GetPosition();

	if(m_InDash)
	{
		if (m_DashDirection.y == 0)
		{
			m_pObject->SetScale(Vec2(min(3, max(1, D3DXVec2Length(&m_DashDirection) * 0.1)), 1 - min(0.75, D3DXVec2Length(&m_DashDirection) * 0.02)) * 0.25);
		}
		else if (m_DashDirection.x == 0)
		{
			m_pObject->SetScale(Vec2(1 - min(0.75, D3DXVec2Length(&m_DashDirection) * 0.02), min(3, max(1, D3DXVec2Length(&m_DashDirection) * 0.1))) * 0.25);
		}
		else
		{
			m_pObject->SetScale(Vec2(1 - min(0.75, D3DXVec2Length(&m_DashDirection) * 0.02), 1 - min(0.75, D3DXVec2Length(&m_DashDirection) * 0.02)) * 0.25);
		}
		m_pObject->Translate(m_DashDirection * TimeScale);
		m_DashDirection *= pow(0.8, 1 / (1 / TimeScale));

		if ((m_pObject->GetPosition() + Vec2(0, -m_Speed) * TimeScale).y < 20)
		{
			m_pObject->SetPosition(Vec2(m_pObject->GetPosition().x, 20));
		}
		if ((m_pObject->GetPosition() + Vec2(0, -m_Speed) * TimeScale).y > 700)
		{
			m_pObject->SetPosition(Vec2(m_pObject->GetPosition().x, 700));
		}
		if ((m_pObject->GetPosition() + Vec2(0, -m_Speed) * TimeScale).x < 20)
		{
			m_pObject->SetPosition(Vec2(20, m_pObject->GetPosition().y));
		}
		if ((m_pObject->GetPosition() + Vec2(0, -m_Speed) * TimeScale).x > 980)
		{
			m_pObject->SetPosition(Vec2(980, m_pObject->GetPosition().y));
		}
	}

	if (m_pObject->GetAlarmDuration(0) <= -100)
	{
		m_pObject->Alarm(0, 1);
	}

	if (m_BFGCharging != 0)
	{
		float Rot = m_Direction;
		m_BFGCharging += 0.14285714285714285714285714285715;
		CAMERA->Shake(10, m_BFGCharging * 0.25);
		char Name[10];
		sprintf(Name, "Spark%d", (rand() % 4) + 1);
		cParticle_Base* a = PARTICLE->AddParticle(IMAGE->Find(Name), m_pObject->GetPosition() + Vec2(0, 10) + RotateVec(Vec2(35, 0), Rot) + Vec2(Random(-1.3f, 1.3f), Random(-1.3f, 1.3f)) * m_BFGCharging,
			Random(0, 359), true, D3DCOLOR_XRGB(Random(100, 150), 255, Random(0, 150)));
		PARTICLE->SetScale(a, Vec2(0.0075, 0.0075) * Random(0.5f, 1.f) * m_BFGCharging, Vec2(0, 0), 1);
		PARTICLE->SetAlpha(a, Random(2, 4) * 255, -255, 1);
		if (m_BFGCharging >= 20)
		{
			m_AttackAble = false;
			float Rot = m_Direction;
			if (m_BFGChargingSound != nullptr)
			{
				m_BFGChargingSound->Stop();
			}
			SOUND->Play("Wep_BFG_Fire")->SetVolume(TOVOLUME(90));
			CAMERA->Shake(60, 10 + m_BFGCharging * 0.75);
			SYSTEM->SetTimeScale(min(1, 7 / m_BFGCharging), 45);

			cObject* a = OBJECT->AddObject("Wep_BFG_Bullet", m_pObject->GetPosition() + Vec2(0, 10) + RotateVec(Vec2(35, 0), Rot), Tag::PlayerBullet, 4);
			a->AddComponent<cBullet_BFG>()->SetDirection(Rot);
			a->GetComponent<cBullet_BFG>()->SetCharge(m_BFGCharging + 30);
			a->AddComponent<cAnimation>()->AddAnimation("IDLE", "Bullet_BFG", 10, true);
			a->GetComponent<cAnimation>()->SetAnimation("IDLE");
			a->GetComponent<cCollider>()->SetColliderCount(1);
			a->GetComponent<cCollider>()->AddCollider(Vec2(0, 0), 23);

			cParticle_Base* b = PARTICLE->AddParticle(IMAGE->Find("Circle1"), m_pObject->GetPosition() + Vec2(0, 10) + RotateVec(Vec2(35, 0), Rot), 0, true, D3DCOLOR_XRGB(120, 255, 110));
			PARTICLE->SetScale(b, Vec2(0.1, 0.1), Vec2(0.02, 0.02) * m_BFGCharging, 0.9);
			PARTICLE->SetAlpha(b, 255, -10, 1);
			b = PARTICLE->AddParticle(IMAGE->Find("Bullet3"), m_pObject->GetPosition() + Vec2(0, 10) + RotateVec(Vec2(35, 0), Rot), 0, false, D3DCOLOR_XRGB(120, 255, 110));
			PARTICLE->SetScale(b, Vec2(0.25, 0.25), Vec2(0.05, 0.05) * m_BFGCharging, 0.9);
			PARTICLE->SetAlpha(b, 150, -10, 1);

			m_PlasmaAmmo -= 30 + (int)m_BFGCharging;
			m_BFGCharging = 0;
			m_pObject->Alarm(1, 30);
		}
	}

	if (GetComponent<cPath>()->GetSpeed() == 0)
	{
		if (m_InDash == false && m_DashAble)
		{
			if (m_pObject->GetPosition().y < 500)
			{
				Dash(Vec2(0, 1));
			}
		}
	}
	else
	{
		if (m_pObject->GetPosition().y <= -50)
		{
			SCENE->ChangeScene("INGAME");
		}
	}
}

void cPlayerMenu::Render()
{
	if (!m_Dead)
	{
		Vec2 Scale = Vec2(1, 1) * (1 - D3DXVec2Length(&m_DashDirection) * 0.02);
		D3DCOLOR Color = m_pObject->GetComponent<cRenderer>()->GetColor();
		switch (m_Weapon)
		{
		case Weapon::Wep_Default:
		{
			IMAGE->CenterRender(IMAGE->Find("Turret_Medium1"), m_pObject->GetPosition() + Vec2(0, 10), D3DXToRadian(m_Direction) + D3DXToRadian(90), Scale, Color);
			break;
		}
		case Weapon::Wep_Plasma:
		{
			IMAGE->CenterRender(IMAGE->Find("Turret_Medium2"), m_pObject->GetPosition() + Vec2(0, 10), D3DXToRadian(m_Direction) + D3DXToRadian(90), Scale * 1.3, Color);
			break;
		}
		case Weapon::Wep_Chain:
		{
			IMAGE->CenterRender(IMAGE->Find("Turret_Large2"), m_pObject->GetPosition() + Vec2(0, 10), D3DXToRadian(m_Direction) + D3DXToRadian(90), Scale * 1.2, Color);
			break;
		}
		case Weapon::Wep_Rocket:
		{
			IMAGE->CenterRender(IMAGE->Find("Turret_Small2"), m_pObject->GetPosition() + Vec2(0, 10), D3DXToRadian(m_Direction) + D3DXToRadian(90), Scale * 1.5, Color);
			break;
		}
		case Weapon::Wep_Sniper:
		{
			IMAGE->CenterRender(IMAGE->Find("Turret_Small3"), m_pObject->GetPosition() + Vec2(0, 10), D3DXToRadian(m_Direction) + D3DXToRadian(90), Scale * 1.5, Color);
			break;
		}
		case Weapon::Wep_BFG:
		{
			IMAGE->CenterRender(IMAGE->Find("Turret_Large1"), m_pObject->GetPosition() + Vec2(0, 10), D3DXToRadian(m_Direction) + D3DXToRadian(90), Scale * 1.2, Color);
			break;
		}
		}
	}
}

void cPlayerMenu::Release()
{
}

void cPlayerMenu::FireBFG(float Dir, float Charge)
{
	if (m_AttackAble)
	{
		m_AttackAble = false;
		m_BFGCharging = 0.14285714285714285714285714285715;
		m_BFGChargingSound = SOUND->Play("Wep_BFG_Charge");
		m_BFGChargingSound->SetVolume(TOVOLUME(90));
		m_pObject->Alarm(9, 1);
	}
}

void cPlayerMenu::Attack(float Dir)
{
	m_Direction = Dir;
	if (m_AttackAble && m_Weapon != Wep_BFG)
	{
		float Rot = Dir;
		cObject* a;
		switch (m_Weapon)
		{
		case Wep_Default:
		{
			m_AttackAble = false;
			for (int i = -1; i <= 1; i++)
			{
				a = OBJECT->AddObject("Wep_Default_Bullet", m_pObject->GetPosition() + Vec2(0, 10) + RotateVec(Vec2(15, 0), Rot), Tag::PlayerBullet, 4);
				a->SetScale(Vec2(1.5, 1.5));
				a->AddComponent<cBullet>()->SetDamage(8);
				a->GetComponent<cBullet>()->SetDirection(Rot + i * 6);
				a->GetComponent<cBullet>()->SetSpeed(20);
				a->GetComponent<cRenderer>()->SetImage(IMAGE->Find("Bullet1"));
				a->GetComponent<cRenderer>()->SetColor(D3DCOLOR_XRGB(250, 240, 200));
				a->GetComponent<cCollider>()->SetColliderCount(1);
				a->GetComponent<cCollider>()->AddCollider(Vec2(0, 0), 10);
			}
			cParticle_Base* b;
			char Name[10];

			if (rand() % 2 == 0)
			{
				for (int i = -5; i <= 5; i += 10)
				{
					sprintf(Name, "Muzzle%d", (rand() % 5) + 1);
					b = PARTICLE->AddParticle(IMAGE->Find(Name), m_pObject->GetPosition() + Vec2(0, 10) + RotateVec(Vec2(45, i), Rot), Rot, true, D3DCOLOR_XRGB(255, 230, 200));
					PARTICLE->SetAlpha(b, 765, -255, 1);
					PARTICLE->SetScale(b, Vec2(0.15, 0.15), Vec2(0, 0), 1);
				}
			}
			else
			{
				for (int i = 5; i >= -5; i -= 10)
				{
					sprintf(Name, "Muzzle%d", (rand() % 5) + 1);
					b = PARTICLE->AddParticle(IMAGE->Find(Name), m_pObject->GetPosition() + Vec2(0, 10) + RotateVec(Vec2(45, i), Rot), Rot, true, D3DCOLOR_XRGB(255, 230, 200));
					PARTICLE->SetAlpha(b, 765, -255, 1);
					PARTICLE->SetScale(b, Vec2(0.15, 0.15), Vec2(0, 0), 1);
				}
			}
			LPDIRECTSOUNDBUFFER Snd = SOUND->Play("Wep_Default_Fire");
			Snd->SetFrequency(Random(40000, 45000));
			Snd->SetVolume(TOVOLUME(85));
			m_pObject->Alarm(1, 5);
			CAMERA->Shake(4, 3);
			break;
		}

		case Wep_Plasma:
		{
			m_AttackAble = false;
			if (m_PlasmaAmmo > 0)
			{
				a = OBJECT->AddObject("Wep_Plasma_Bullet", m_pObject->GetPosition() + Vec2(0, 10) + RotateVec(Vec2(15, 0), Rot), Tag::PlayerBullet, 4);
				a->SetScale(Vec2(0.5, 0.5));
				a->SetRotation(Random(0, 359));
				a->AddComponent<cBullet>()->SetDamage(22);
				a->GetComponent<cBullet>()->SetDirection(Rot);
				a->GetComponent<cBullet>()->SetSpeed(20);
				a->GetComponent<cBullet>()->SetRotateAssignToDirection(false);
				a->GetComponent<cRenderer>()->SetImage(IMAGE->Find("Bullet3"));
				a->GetComponent<cRenderer>()->SetColor(D3DCOLOR_XRGB(0, Random(50, 150), 255));
				a->GetComponent<cCollider>()->SetColliderCount(1);
				a->GetComponent<cCollider>()->AddCollider(Vec2(0, 0), 10);

				char Name[10];
				sprintf(Name, "Spark%d", (rand() % 4) + 1);
				cParticle_Base* b;
				for (int i = 0; i < 3; i++)
				{
					b = PARTICLE->AddParticle(IMAGE->Find(Name), m_pObject->GetPosition() + Vec2(0, 10) + RotateVec(Vec2(15, 0), Rot) + Vec2(Random(-5.f, 5.f), Random(-5.f, 5.f)),
						Random(0, 359), true, D3DCOLOR_XRGB(0, Random(50, 150), 255));
					PARTICLE->SetScale(b, Vec2(0.1, 0.1) * Random(0.75f, 1.25f), Vec2(0, 0), 1);
					PARTICLE->SetAlpha(b, Random(3, 6) * 255, -255, 1);
				}
				b = PARTICLE->AddParticle(IMAGE->Find("Circle1"), m_pObject->GetPosition() + Vec2(0, 10) + RotateVec(Vec2(25, 0), Rot), 0, true, D3DCOLOR_XRGB(0, Random(50, 150), 255));
				PARTICLE->SetScale(b, Vec2(0.05, 0.05), Vec2(0.015, 0.015), 1);
				PARTICLE->SetAlpha(b, 255, -40, 1);

				LPDIRECTSOUNDBUFFER Snd = SOUND->Play("Wep_Plasma_Fire");
				Snd->SetFrequency(Random(40000, 45000));
				Snd->SetVolume(TOVOLUME(85));
				m_pObject->Alarm(1, 4);
				CAMERA->Shake(4, 3);

				m_PlasmaAmmo--;
			}
			else
			{
				SOUND->Play("OutofAmmo")->SetVolume(TOVOLUME(90));
				m_pObject->Alarm(1, 20);
			}
			break;
		}

		case Wep_Chain:
		{
			m_AttackAble = false;
			if (m_ChainAmmo > 0)
			{
				m_Speed = 1;
				for (int i = 0; i < 2; i++)
				{
					a = OBJECT->AddObject("Wep_Chain_Bullet", m_pObject->GetPosition() + Vec2(0, 10) + RotateVec(Vec2(15, 0), Rot), Tag::PlayerBullet, 4);
					a->SetScale(Vec2(1.5, 1.5));
					a->AddComponent<cBullet>()->SetDamage(10);
					a->GetComponent<cBullet>()->SetDirection(Rot + Random(-10.f, 10.f));
					a->GetComponent<cBullet>()->SetSpeed(20);
					a->GetComponent<cRenderer>()->SetImage(IMAGE->Find("Bullet1"));
					a->GetComponent<cRenderer>()->SetColor(D3DCOLOR_XRGB(255, 255, 150));
					a->GetComponent<cCollider>()->SetColliderCount(1);
					a->GetComponent<cCollider>()->AddCollider(Vec2(0, 0), 10);
				}

				char Name[10];
				cParticle_Base* b;
				if (rand() % 2 == 0)
				{
					for (int i = -5; i <= 5; i += 10)
					{
						sprintf(Name, "Muzzle%d", (rand() % 5) + 1);
						b = PARTICLE->AddParticle(IMAGE->Find(Name), m_pObject->GetPosition() + Vec2(0, 10) + RotateVec(Vec2(45, i), Rot), Rot, true, D3DCOLOR_XRGB(255, 230, 175));
						PARTICLE->SetAlpha(b, 510, -255, 1);
						PARTICLE->SetScale(b, Vec2(0.15, 0.15), Vec2(0, 0), 1);
					}
				}
				else
				{
					for (int i = 5; i >= -5; i -= 10)
					{
						sprintf(Name, "Muzzle%d", (rand() % 5) + 1);
						b = PARTICLE->AddParticle(IMAGE->Find(Name), m_pObject->GetPosition() + Vec2(0, 10) + RotateVec(Vec2(45, i), Rot), Rot, true, D3DCOLOR_XRGB(255, 230, 175));
						PARTICLE->SetAlpha(b, 510, -255, 1);
						PARTICLE->SetScale(b, Vec2(0.15, 0.15), Vec2(0, 0), 1);
					}
				}

				LPDIRECTSOUNDBUFFER Snd = SOUND->Play("Wep_Chain_Fire");
				Snd->SetFrequency(Random(40000, 45000));
				Snd->SetVolume(TOVOLUME(85));
				m_pObject->Alarm(1, 2);
				CAMERA->Shake(4, 3);

				m_ChainAmmo--;
			}
			else
			{
				SOUND->Play("OutofAmmo")->SetVolume(TOVOLUME(90));
				m_pObject->Alarm(1, 20);
			}
			break;
		}

		case Wep_Rocket:
		{
			cObject* Nearest = nullptr;
			float NearestDist = 10000;
			float Dist;
			list<cObject*> Temp;
			OBJECT->Find(&Temp, Tag::Enemy);
			for (auto& iter : Temp)
			{
				Dist = D3DXVec2Length(&(INPUT->GetMousePos() - iter->GetPosition()));
				if (Dist < NearestDist)
				{
					Nearest = iter;
					NearestDist = Dist;
				}
			}
			m_AttackAble = false;
			if (m_RocketAmmo > 0)
			{
				a = OBJECT->AddObject("Wep_Rocket_Bullet", m_pObject->GetPosition() + Vec2(0, 10) + RotateVec(Vec2(15, 0), Rot), Tag::PlayerBullet, 4);
				a->SetScale(Vec2(1.5, 1.5));
				a->AddComponent<cBullet_Homing>()->SetDamage(50);
				a->GetComponent<cBullet_Homing>()->SetDirection(Rot + Random(-60.f, 60.f));
				a->GetComponent<cBullet_Homing>()->SetSpeed(15);
				a->GetComponent<cBullet_Homing>()->SetTarget(Nearest);
				a->GetComponent<cBullet_Homing>()->SetRotateSpeed(0.001);
				a->GetComponent<cBullet_Homing>()->SetRotateSpeedVel(0.008);
				a->GetComponent<cRenderer>()->SetImage(IMAGE->Find("Bullet5"));
				a->GetComponent<cCollider>()->SetColliderCount(1);
				a->GetComponent<cCollider>()->AddCollider(Vec2(0, 0), 5);

				char Name[20];
				cParticle_Base* b;


				sprintf(Name, "Wep_Rocket_Fire%d", (rand() % 2) + 1);
				LPDIRECTSOUNDBUFFER Snd = SOUND->Play(Name);
				Snd->SetFrequency(Random(40000, 50000));
				Snd->SetVolume(TOVOLUME(100));
				m_pObject->Alarm(1, 8);
				CAMERA->Shake(10, 4);

				m_RocketAmmo--;
			}
			else
			{
				SOUND->Play("OutofAmmo")->SetVolume(TOVOLUME(90));
				m_pObject->Alarm(1, 20);
			}
			break;
		}

		case Wep_Sniper:
		{
			m_AttackAble = false;
			cParticle_Base* a;
			if (m_SniperAmmo > 0)
			{
				list<cObject*> Temp;
				OBJECT->Find(&Temp, Tag::Enemy);
				Vec2 Vec;
				for (auto& iter : Temp)
				{
					Vec = m_pObject->GetPosition() + RotateVec(iter->GetPosition() + Vec2(0, 10) - m_pObject->GetPosition(), (Rot - DegAngle(m_pObject->GetPosition(), iter->GetPosition())));
					if (D3DXVec2Length(&(Vec - iter->GetPosition())) <= 20 + iter->GetComponent<cCollider>()->GetCollider(0)->Size)
					{
						iter->GetComponent<cEnemyBase>()->AddHp(-125);
						iter->GetComponent<cRenderer>()->SetColor(D3DCOLOR_XRGB(255, 0, 0));
						iter->Alarm(0, 3);
						if (iter->GetComponent<cEnemyBase>()->GetHp() <= 0)
						{
							iter->GetComponent<cEnemyBase>()->SetKilledby(Killedby::Sniper);
						}
						a = PARTICLE->AddParticle(IMAGE->Find("Circle1"), iter->GetPosition(), 0, true, D3DCOLOR_XRGB(255, 0, 0));
						PARTICLE->SetScale(a, Vec2(0.05, 0.05), Vec2(0.04, 0.04), 1);
						PARTICLE->SetAlpha(a, 255, -30, 1);
						char Name[25];
						float Size = iter->GetComponent<cCollider>()->GetCollider(0)->Size;
						for (int i = 0; i < 6; i++)
						{
							sprintf(Name, "Spark%d", (rand() % 4) + 1);
							a = PARTICLE->AddParticle(IMAGE->Find(Name), iter->GetPosition() + Vec2(Random(-Size, Size), Random(-Size, Size)), Random(0, 359), true, D3DCOLOR_XRGB(255, 0, 0));
							PARTICLE->SetScale(a, Vec2(0.15, 0.15) * Random(0.5f, 1.f), Vec2(0, 0), 1);
							PARTICLE->SetAlpha(a, Random(3, 10) * 255, -255, 1);
						}
						sprintf(Name, "Wep_Plasma_Hit%d", (rand() % 3) + 1);
						LPDIRECTSOUNDBUFFER Snd = SOUND->Play(Name);
						Snd->SetVolume(TOVOLUME(82));
					}
				}

				cParticle_Base* a = PARTICLE->AddParticle(IMAGE->Find("Trace1"), m_pObject->GetPosition() + Vec2(0, 10) + RotateVec(Vec2(750, 0), Rot), Rot - 180, true, D3DCOLOR_XRGB(255, 0, 0));
				PARTICLE->SetAlpha(a, 255, -5, 1.1);
				PARTICLE->SetScale(a, Vec2(4, 1), Vec2(0, 0), 1);
				a = PARTICLE->AddParticle(IMAGE->Find("Circle1"), m_pObject->GetPosition() + Vec2(0, 10) + RotateVec(Vec2(35, 0), Rot), 0, true, D3DCOLOR_XRGB(255, 0, 0));
				PARTICLE->SetScale(a, Vec2(0.05, 0.05), Vec2(0.05, 0.05), 1);
				PARTICLE->SetAlpha(a, 255, -30, 1);
				a = PARTICLE->AddParticle(IMAGE->Find("Bullet3"), m_pObject->GetPosition() + Vec2(0, 10) + RotateVec(Vec2(35, 0), Rot), 0, true, D3DCOLOR_XRGB(255, 0, 0));
				PARTICLE->SetScale(a, Vec2(0.2, 0.2), Vec2(0.2, 0.2), 1);
				PARTICLE->SetAlpha(a, 255, -30, 1);

				SOUND->Play("Wep_Sniper_Fire");
				m_pObject->Alarm(1, 45);
				CAMERA->Shake(15, 10);

				m_SniperAmmo--;
			}
			else
			{
				SOUND->Play("OutofAmmo")->SetVolume(TOVOLUME(90));
				m_pObject->Alarm(1, 20);
			}
			break;
		}
		}
	}
}

void cPlayerMenu::Dash(Vec2 Dir)
{
	if (m_InDash == false && m_DashAble)
	{
		m_InDash = true;
		m_DashAble = false;
		m_pObject->Alarm(4, 30);
		D3DXVec2Normalize(&m_DashDirection, &Dir);
		m_DashDirection *= 40;
		m_pObject->Alarm(2, 10);

		cParticle_Base* a;
		for (int i = 0; i < 6; i++)
		{
			a = PARTICLE->AddParticle(IMAGE->Find("Trace1"), m_pObject->GetPosition() + m_DashDirection + Vec2(Random(-20.f, 20.f), Random(-30.f, 30.f)),
				DegAngle(Vec2(0, 0), m_DashDirection), false, D3DCOLOR_XRGB(0, 255, 255));
			PARTICLE->SetScale(a, Vec2(0.1, 0.15), Vec2(0.1, 0), 0.8);
			PARTICLE->SetAlpha(a, 200, -2, 1.4);
		}

		char Name[10];
		sprintf(Name, "Dash%d", (rand() % 6) + 1);
		SOUND->Play(Name)->SetVolume(TOVOLUME(90));

		if (m_Hit)
		{
			SYSTEM->SetTimeScale(0.2, 60);
			SYSTEM->AddScore(5000);
			CAMERA->Shake(45, 20);
			m_pObject->Alarm(3, -100);
			m_Hit = false;
			cParticle_Base* a = PARTICLE->AddParticle(IMAGE->Find("Circle1"), m_pObject->GetPosition(), 0, true, D3DCOLOR_XRGB(50, 255, 255));
			PARTICLE->SetScale(a, Vec2(0.1, 0.1), Vec2(1.5, 1.5), 0.95);
			PARTICLE->SetAlpha(a, 255, -30, 1);

			list<cObject*> Temp;
			OBJECT->Find(&Temp, Tag::Enemy);
			for (auto& iter : Temp)
			{
				iter->GetComponent<cEnemyBase>()->AddHp(-150);
			}
			OBJECT->Find(&Temp, Tag::EnemyBullet);
			for (auto& iter : Temp)
			{
				iter->Destroy();
				cParticle_Base* a = PARTICLE->AddParticle(IMAGE->Find("Circle5"), iter->GetPosition(), 0, false, iter->GetComponent<cRenderer>()->GetColor());
				PARTICLE->SetScale(a, Vec2(0.01, 0.01), Vec2(0.015, 0.015), 0.95);
				PARTICLE->SetAlpha(a, 255, -20, 1);
			}
		}
	}
}

void cPlayerMenu::Melee(float Dir)
{
	if (m_MeleeAble)
	{
		m_MeleeAble = false;
		m_pObject->Alarm(8, 60);
		float Rot = Dir;
		cObject* a = OBJECT->AddObject("Melee_Bullet", m_pObject->GetPosition() + RotateVec(Vec2(45, 0), Rot), Tag::PlayerBullet, 4);
		a->SetScale(Vec2(0.1, 0.1));
		a->AddComponent<cBullet>()->SetDamage(200);
		a->GetComponent<cBullet>()->SetDirection(0);
		a->GetComponent<cBullet>()->SetSpeed(2000);
		a->GetComponent<cRenderer>()->SetImage(IMAGE->Find("Bullet4"));
		a->GetComponent<cRenderer>()->SetColor(D3DCOLOR_ARGB(0, 0, 0, 0));
		a->GetComponent<cCollider>()->SetColliderCount(1);
		a->GetComponent<cCollider>()->AddCollider(Vec2(0, 0), 20);
		cParticle_Base* b = PARTICLE->AddParticle(IMAGE->Find("Bullet4"), m_pObject->GetPosition() + RotateVec(Vec2(-50, 0), Rot), Rot, true, D3DCOLOR_XRGB(255, 0, 0));
		PARTICLE->SetSpeed(b, 20, 0.98, Rot);
		PARTICLE->SetScale(b, Vec2(0.5, 0.25), Vec2(-0.05, 0), 1.15);
		CAMERA->Shake(20, 5);
		SOUND->Play("Melee")->SetVolume(TOVOLUME(90));
	}
}