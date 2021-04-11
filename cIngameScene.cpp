#include "DXUT.h"
#include "cIngameScene.h"
#include "cPlayer.h"
#include "cZako.h"
#include "cTimeLine_Zako1.h"
#include "cTimeLine_Zako2.h"
#include "cTimeLine_Zako3.h"
#include "cTimeLine_Zako4.h"
#include "cTimeLine_Zako5.h"
#include "cTimeLine_Zako6.h"
#include "cTimeLine_Zako7.h"

cIngameScene::cIngameScene()
{
}


cIngameScene::~cIngameScene()
{
}

void cIngameScene::Init()
{
	cObject* a = OBJECT->AddObject("Player", Vec2(500, 360), Tag::Player, 5);
	a->AddComponent<cRenderer>()->SetImage(IMAGE->Find(SYSTEM->GetDoot() == false ? "Cruiser3" : "Doot"));
	a->AddComponent<cPlayer>();
	m_Random = 4500;
	cParticle_Base* b = PARTICLE->AddParticle(IMAGE->Find("Background2"), Vec2(640, 360), 0, true, D3DCOLOR_XRGB(0, 0, 0));
	PARTICLE->SetAlpha(b, 255, -2, 1.03);
	SYSTEM->SetScore(0);
	SYSTEM->SetTime(0);
}

void cIngameScene::Update()
{
	m_Random -= 0.1;
	cObject* a;
	int Rand = rand() % (int)m_Random;
	if (Rand < 10)
	{
		int Dir = Random(0, 1);
		a = OBJECT->AddObject("Zako2", Vec2(Dir * 1200 - 100, Random(0, 720)), Tag::Enemy, 4);
		a->AddComponent<cZako>();
		a->GetComponent<cCollider>()->SetColliderCount(1);
		a->GetComponent<cCollider>()->AddCollider(Vec2(0, 0), 20);
		a->AddComponent<cTimeLine_Zako1>();
		a->GetComponent<cPath>()->AddPath(Vec2(abs(Dir - 1) * 1500 - 250, Random(0,720)));
		a->GetComponent<cPath>()->SetSpeed(3);
	}
	else if (Rand >= 10 && Rand < 20)
	{
		int Dir = Random(0, 1);
		a = OBJECT->AddObject("Zako2", Vec2(Dir * 1200 - 100, Random(0, 720)), Tag::Enemy, 4);
		a->AddComponent<cZako>();
		a->GetComponent<cCollider>()->SetColliderCount(1);
		a->GetComponent<cCollider>()->AddCollider(Vec2(0, 0), 20);
		a->AddComponent<cTimeLine_Zako2>();
		a->GetComponent<cPath>()->AddPath(Vec2(abs(Dir - 1) * 1500 - 250, Random(0, 720)));
		a->GetComponent<cPath>()->SetSpeed(3);
	}
	else if (Rand >= 20 && Rand < 23)
	{
		a = OBJECT->AddObject("Zako1", Vec2(Random(50,950), -40), Tag::Enemy, 4);
		a->AddComponent<cZako>();
		a->GetComponent<cCollider>()->SetColliderCount(2);
		a->GetComponent<cCollider>()->AddCollider(Vec2(15, 0), 20);
		a->GetComponent<cCollider>()->AddCollider(Vec2(-15, 0), 20);
		a->AddComponent<cTimeLine_Zako3>();
		a->GetComponent<cPath>()->AddPath(Vec2(a->GetPosition().x, 600));
		a->GetComponent<cPath>()->SetSpeed(Random(3.f, 5.f));
		a->GetComponent<cPath>()->SetFriction(0.98f);
	}
	else if (Rand >= 23 && Rand < 26)
	{
		a = OBJECT->AddObject("Zako1", Vec2(Random(50, 950), -40), Tag::Enemy, 4);
		a->AddComponent<cZako>();
		a->GetComponent<cCollider>()->SetColliderCount(2);
		a->GetComponent<cCollider>()->AddCollider(Vec2(15, 0), 20);
		a->GetComponent<cCollider>()->AddCollider(Vec2(-15, 0), 20);
		a->AddComponent<cTimeLine_Zako6>();
		a->GetComponent<cPath>()->AddPath(Vec2(a->GetPosition().x, 600));
		a->GetComponent<cPath>()->SetSpeed(Random(3.f, 5.f));
		a->GetComponent<cPath>()->SetFriction(0.98f);
	}
	else if (Rand >= 26 && Rand < 29)
	{
		a = OBJECT->AddObject("Zako4", Vec2(Random(50, 950), 760), Tag::Enemy, 4);
		a->AddComponent<cZako>();
		a->GetComponent<cCollider>()->SetColliderCount(2);
		a->GetComponent<cCollider>()->AddCollider(Vec2(0, 15), 20);
		a->GetComponent<cCollider>()->AddCollider(Vec2(0, -15), 20);
		a->AddComponent<cTimeLine_Zako4>();
		a->GetComponent<cPath>()->AddPath(Vec2(Random(50,950),Random(50,670)), Vec2(Random(50, 950), Random(50, 670)));
		a->GetComponent<cPath>()->SetSpeed(3);
	}
	else if (Rand >= 29 && Rand < 32)
	{
		a = OBJECT->AddObject("Zako4", Vec2(Random(50, 950), 760), Tag::Enemy, 4);
		a->AddComponent<cZako>();
		a->GetComponent<cCollider>()->SetColliderCount(2);
		a->GetComponent<cCollider>()->AddCollider(Vec2(0, 15), 20);
		a->GetComponent<cCollider>()->AddCollider(Vec2(0, -15), 20);
		a->AddComponent<cTimeLine_Zako5>();
		a->GetComponent<cPath>()->AddPath(Vec2(Random(50, 950), Random(50, 670)), Vec2(Random(50, 950), Random(50, 670)));
		a->GetComponent<cPath>()->SetSpeed(3);
	}
	else if (Rand >= 32 && Rand < 36)
	{
		a = OBJECT->AddObject("Zako3", Vec2(Random(50, 950), -40), Tag::Enemy, 4);
		a->AddComponent<cZako>();
		a->GetComponent<cCollider>()->SetColliderCount(1);
		a->GetComponent<cCollider>()->AddCollider(Vec2(0, 0), 15);
		a->AddComponent<cTimeLine_Zako7>();
	}
}

void cIngameScene::Render()
{
	IMAGE->Render(IMAGE->Find("Background1"), Vec2(-500, -500), 0, Vec2(1, 1));
}

void cIngameScene::Release()
{
	SOUND->StopAll();
}
