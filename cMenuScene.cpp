#include "DXUT.h"
#include "cMenuScene.h"
#include "cButton.h"
#include "cPlayerMenu.h"


cMenuScene::cMenuScene()
{
}


cMenuScene::~cMenuScene()
{
}

void cMenuScene::Init()
{
	SOUND->Play(SYSTEM->GetDoot() == false ? "BGM" : "Doot", true)->SetVolume(TOVOLUME(90));

	list<cObject*> Temp;
	cObject* a = OBJECT->AddObject("Start", Vec2(150, -570), Tag::None, -10);
	a->AddComponent<cButton>()->SetSize(Vec2(120, 64));
	a->GetComponent<cButton>()->SetText(L"Start");
	Temp.push_back(a);
	a = OBJECT->AddObject("How to Play", Vec2(150, -420), Tag::None, -10);
	a->AddComponent<cButton>()->SetSize(Vec2(295, 64));
	a->GetComponent<cButton>()->SetText(L"How to Play");
	Temp.push_back(a);
	a = OBJECT->AddObject("Exit", Vec2(150, -270), Tag::None, -10);
	a->AddComponent<cButton>()->SetSize(Vec2(100, 64));
	a->GetComponent<cButton>()->SetText(L"Exit");
	Temp.push_back(a);
	for (auto& iter : Temp)
	{
		iter->AddComponent<cPath>()->AddPath(Vec2(iter->GetPosition().x, iter->GetPosition().y + 720));
		iter->GetComponent<cPath>()->SetSpeed(22.5);
		iter->GetComponent<cPath>()->SetFriction(0.97);
	}

	a = OBJECT->AddObject("Player", Vec2(850, 800), Tag::Player, 5);
	a->AddComponent<cRenderer>()->SetImage(IMAGE->Find(SYSTEM->GetDoot() == false ? "Cruiser3" : "Doot"));
	a->AddComponent<cPlayerMenu>();
	a->AddComponent<cPath>()->AddPath(Vec2(850, 550));
	a->GetComponent<cPath>()->SetSpeed(8);
	a->GetComponent<cPath>()->SetFriction(0.97);
}

void cMenuScene::Update()
{
}

void cMenuScene::Render()
{
	IMAGE->Render(IMAGE->Find("Background2"), Vec2(0, 0), 0, Vec2(1, 1));
}

void cMenuScene::Release()
{
}
