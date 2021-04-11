#include "DXUT.h"
#include "cButton.h"
#include "cPlayerMenu.h"
#include "cZako.h"


cButton::cButton(cObject* Owner)
	:cComponent(Owner)
{
}


cButton::~cButton()
{
}

void cButton::Init()
{
}

void cButton::Update()
{
	Vec2 Mouse = INPUT->GetMousePos() - m_pObject->GetPosition();
	if (Mouse.x >= 0 && Mouse.x <= m_Size.x * m_pObject->GetScale().x && Mouse.y >= 0 && Mouse.y <= m_Size.y * m_pObject->GetScale().y && OBJECT->GetPlayer()->GetComponent<cPath>()->GetSpeed() == 0)
	{
		m_pObject->SetScale(Lerp<Vec2>(m_pObject->GetScale(), Vec2(1.2, 1.2), 0.1));
		if (INPUT->KeyPress(VK_LBUTTON))
		{
			if (m_Text == L"Start")
			{
				OBJECT->GetPlayer()->GetComponent<cPath>()->AddPath(Vec2(850, -100));
				OBJECT->GetPlayer()->GetComponent<cPath>()->SetSpeed(0.5);
				OBJECT->GetPlayer()->GetComponent<cPath>()->SetFriction(1.04);
				cParticle_Base* a = PARTICLE->AddParticle(IMAGE->Find("Background2"), Vec2(640, 360), 0, true, D3DCOLOR_XRGB(0, 0, 0));
				PARTICLE->SetAlpha(a, 0, 0.8, 1.02);
			}
			else if (m_Text == L"How to Play")
			{
				list<cObject*> Temp;
				OBJECT->Find(&Temp, Tag::None);
				for (auto& iter : Temp)
				{
					iter->GetComponent<cPath>()->AddPath(Vec2(m_pObject->GetPosition().x, 2000));
					iter->GetComponent<cPath>()->SetSpeed(1.5);
					iter->GetComponent<cPath>()->SetFriction(1.05);
				}
			}
			else if (m_Text == L"Exit")
			{
				exit(0);
			}
			else if (m_Text == L"Back to Menu")
			{
				list<cObject*> Temp;
				OBJECT->Find(&Temp, Tag::None);
				for (auto& iter : Temp)
				{
					iter->GetComponent<cPath>()->AddPath(Vec2(m_pObject->GetPosition().x, 2000));
					iter->GetComponent<cPath>()->SetSpeed(1.5);
					iter->GetComponent<cPath>()->SetFriction(1.05);
				}
			}
			else if (m_Text == L"dO nOt ClIcK tHiS")
			{
				SYSTEM->SetDoot(true);
				SOUND->StopAll();
				SOUND->Play("Doot", true)->SetVolume(TOVOLUME(90));
				m_pObject->Destroy();
				OBJECT->GetPlayer()->Destroy();
				cObject* a = OBJECT->AddObject("Player", Vec2(850, 550), Tag::Player, 5);
				a->AddComponent<cRenderer>()->SetImage(IMAGE->Find(SYSTEM->GetDoot() == false ? "Cruiser3" : "Doot"));
				a->AddComponent<cPlayerMenu>();
				a->AddComponent<cPath>();
			}
		}
		if (m_Text == L"Machine Gun (1)")
		{
			OBJECT->GetPlayer()->GetComponent<cPlayerMenu>()->SetWeapon(Wep_Default);
			OBJECT->GetPlayer()->GetComponent<cPlayerMenu>()->Attack(270);
		}
		else if (m_Text == L"Plasma Rifle (2)")
		{
			OBJECT->GetPlayer()->GetComponent<cPlayerMenu>()->SetWeapon(Wep_Plasma);
			OBJECT->GetPlayer()->GetComponent<cPlayerMenu>()->Attack(270);
		}
		else if (m_Text == L"Chain Gun (3)")
		{
			OBJECT->GetPlayer()->GetComponent<cPlayerMenu>()->SetWeapon(Wep_Chain);
			OBJECT->GetPlayer()->GetComponent<cPlayerMenu>()->Attack(270);
		}
		else if (m_Text == L"Rocket Launcher (4)")
		{
			OBJECT->GetPlayer()->GetComponent<cPlayerMenu>()->SetWeapon(Wep_Rocket);
			OBJECT->GetPlayer()->GetComponent<cPlayerMenu>()->Attack(270);
		}
		else if (m_Text == L"Sniper Rifle (5)")
		{
			OBJECT->GetPlayer()->GetComponent<cPlayerMenu>()->SetWeapon(Wep_Sniper);
			OBJECT->GetPlayer()->GetComponent<cPlayerMenu>()->Attack(270);
		}
		else if (m_Text == L"BFG (6)")
		{
			OBJECT->GetPlayer()->GetComponent<cPlayerMenu>()->SetWeapon(Wep_BFG);
			OBJECT->GetPlayer()->GetComponent<cPlayerMenu>()->FireBFG(270, Random(5, 20));
		}
		else if (m_Text == L"Melee Attack (��Ŭ��)")
		{
			OBJECT->GetPlayer()->GetComponent<cPlayerMenu>()->Melee(270);
		}
		else if (m_Text == L"Dash (�����̽���)")
		{
			OBJECT->GetPlayer()->GetComponent<cPlayerMenu>()->Dash(Vec2(0, -1));
		}
	}
	else
	{
		m_pObject->SetScale(Lerp<Vec2>(m_pObject->GetScale(), Vec2(1, 1), 0.1));
	}

	if (m_pObject->GetPosition().y >= 1000)
	{
		m_pObject->Destroy();
		if (m_Text == L"How to Play")
		{
			list<cObject*> Temp;
			cObject* a = OBJECT->AddObject("Default", Vec2(150, -700), Tag::None, -10);
			a->AddComponent<cButton>()->SetText(L"Machine Gun (1)");
			Temp.push_back(a);
			a = OBJECT->AddObject("Plasma", Vec2(150, -625), Tag::None, -10);
			a->AddComponent<cButton>()->SetText(L"Plasma Rifle (2)");
			Temp.push_back(a);
			a = OBJECT->AddObject("Chain", Vec2(150, -550), Tag::None, -10);
			a->AddComponent<cButton>()->SetText(L"Chain Gun (3)");
			Temp.push_back(a);
			a = OBJECT->AddObject("Rocket", Vec2(150, -475), Tag::None, -10);
			a->AddComponent<cButton>()->SetText(L"Rocket Launcher (4)");
			Temp.push_back(a);
			a = OBJECT->AddObject("Sniper", Vec2(150, -400), Tag::None, -10);
			a->AddComponent<cButton>()->SetText(L"Sniper Rifle (5)");
			Temp.push_back(a);
			a = OBJECT->AddObject("BFG", Vec2(150, -325), Tag::None, -10);
			a->AddComponent<cButton>()->SetText(L"BFG (6)");
			Temp.push_back(a);
			a = OBJECT->AddObject("Melee", Vec2(150, -250), Tag::None, -10);
			a->AddComponent<cButton>()->SetText(L"Melee Attack (��Ŭ��)");
			Temp.push_back(a);
			a = OBJECT->AddObject("Dash", Vec2(150, -175), Tag::None, -10);
			a->AddComponent<cButton>()->SetText(L"Dash (�����̽���)");
			Temp.push_back(a);
			a = OBJECT->AddObject("Back", Vec2(150, -100), Tag::None, -10);
			a->AddComponent<cButton>()->SetText(L"Back to Menu");
			Temp.push_back(a);
			for (auto& iter : Temp)
			{
				iter->GetComponent<cButton>()->SetSize(Vec2(400, 64));
				iter->AddComponent<cPath>()->AddPath(Vec2(iter->GetPosition().x, iter->GetPosition().y + 720));
				iter->GetComponent<cPath>()->SetSpeed(22.5);
				iter->GetComponent<cPath>()->SetFriction(0.97);
			}
			a = OBJECT->AddObject("Zako2", Vec2(850, -100), Tag::Enemy, 4);
			a->AddComponent<cZako>()->SetHp(3000);
			a->GetComponent<cCollider>()->SetColliderCount(1);
			a->GetComponent<cCollider>()->AddCollider(Vec2(0, 0), 20);
			a->GetComponent<cPath>()->AddPath(Vec2(850, 250));
			a->GetComponent<cPath>()->SetSpeed(7.5);
			a->GetComponent<cPath>()->SetFriction(0.98);
			a->SetRotation(90);
		}
		else if (m_Text == L"Plasma Rifle (2)")
		{
			list<cObject*> Temp;
			bool Doot = true;
			OBJECT->Find(&Temp, Tag::Enemy);
			for (auto& iter : Temp)
			{
				Doot = false;
				iter->GetComponent<cEnemyBase>()->SetHp(0);
			}
			Temp.clear();

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
			if (Doot && !SYSTEM->GetDoot())
			{
				a = OBJECT->AddObject("Doot", Vec2(150, -120), Tag::None, -10);
				a->AddComponent<cButton>()->SetSize(Vec2(400, 64));
				a->GetComponent<cButton>()->SetText(L"dO nOt ClIcK tHiS");
				Temp.push_back(a);
			}
			for (auto& iter : Temp)
			{
				iter->AddComponent<cPath>()->AddPath(Vec2(iter->GetPosition().x, iter->GetPosition().y + 720));
				iter->GetComponent<cPath>()->SetSpeed(22.5);
				iter->GetComponent<cPath>()->SetFriction(0.97);
			}
		}
	}
}

void cButton::Render()
{
	IMAGE->RenderTextView(m_Text, m_pObject->GetPosition() - Vec2(0, (m_pObject->GetScale().y - 1) * 32), 0, m_pObject->GetScale().x * 64);

	if (m_Text == L"Start")
	{
		IMAGE->Render(IMAGE->Find("Title"), m_pObject->GetPosition() + Vec2(0, -100), 0, Vec2(1, 1));
	}

	Vec2 Mouse = INPUT->GetMousePos() - m_pObject->GetPosition();
	if (Mouse.x >= 0 && Mouse.x <= m_Size.x * m_pObject->GetScale().x && Mouse.y >= 0 && Mouse.y <= m_Size.y * m_pObject->GetScale().y && OBJECT->GetPlayer()->GetComponent<cPath>()->GetSpeed() == 0)
	{
		if (m_Text == L"Machine Gun (1)")
		{
			IMAGE->RenderTextView(L"ź���� �Ҹ����� �ʴ� �⺻ �����Դϴ�.", Vec2(750, 10), 0, 20);
		}
		else if (m_Text == L"Plasma Rifle (2)")
		{
			IMAGE->RenderTextView(L"��� ���� ���ӿ� �����ϴ� �����Դϴ�.", Vec2(750, 10), 0, 20);
		}
		else if (m_Text == L"Chain Gun (3)")
		{
			IMAGE->RenderTextView(L"�߻��ϴ� ���� �̵��ӵ��� �������ϴ�.", Vec2(750, 10), 0, 20);
		}
		else if (m_Text == L"Rocket Launcher (4)")
		{
			IMAGE->RenderTextView(L"�߻� ��� ���콺���� ���� ������� ������ ���ư��ϴ�.", Vec2(750, 10), 0, 20);
		}
		else if (m_Text == L"Sniper Rifle (5)")
		{
			IMAGE->RenderTextView(L"���� �����մϴ�.", Vec2(750, 10), 0, 20);
		}
		else if (m_Text == L"BFG (6)")
		{
			IMAGE->RenderTextView(L"��� ���� ���ӿ� �����ϴ� �����Դϴ�.\n�߻�� �ö�� ź�� 30~50���� �Ҹ��մϴ�.\n�����Ͽ� �� �� �ֽ��ϴ�.\n�Ѿ� ������ �ִ� ���鿡�� ���ظ� �ְ�,\n�Ѿ��� �Ҹ��� �� ���� ���ظ� �ݴϴ�.\n�ִ�ġ�� �����ϸ� ��ź�� ��� �����մϴ�.", Vec2(750, 10), 0, 20);
		}
		else if (m_Text == L"Melee Attack (��Ŭ��)")
		{
			IMAGE->RenderTextView(L"���� �������� ���� óġ�ϸ� ���� ź���� ����մϴ�.", Vec2(750, 10), 0, 20);
		}
		else if (m_Text == L"Dash (�����̽���)")
		{
			IMAGE->RenderTextView(L"�뽬 ���߿� �����Դϴ�.\n�ǰݰ� ���ÿ� �뽬�ϸ� ��� �Ҹ� ���� ��Ȱ�ϰ�\n���� �� ź�� ��� �����մϴ�.", Vec2(750, 10), 0, 20);
		}
	}
}

void cButton::Release()
{
}
