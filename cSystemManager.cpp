#include "DXUT.h"
#include "cSystemManager.h"
#include "cPlayer.h"

cSystemManager::cSystemManager()
{
	Init();
}


cSystemManager::~cSystemManager()
{
	Release();
}

void cSystemManager::Init()
{
	m_TimeScale = 1;
	m_Score = 0;
	m_ScoreScale = 32;
	m_Sidebar = nullptr;
	m_Doot = false;
	m_Time = 0;
}

void cSystemManager::Update()
{
	m_TimeScaleTimer--;
	if (m_TimeScaleTimer == 0)
	{
		m_TimeScale = 1;
	}
	m_ScoreScale = Lerp<float>(m_ScoreScale, 32, 0.2);
}

void cSystemManager::Render()
{
	if (SCENE->GetCurScene() == "INGAME")
	{
		m_Time++;
		cPlayer* Player = OBJECT->GetPlayer()->GetComponent<cPlayer>();
		if (m_Sidebar == nullptr)
		{
			m_Sidebar = IMAGE->Find("Sidebar");
			m_Life = IMAGE->Find("Cruiser3");
		}

		IMAGE->RenderView(m_Sidebar, Vec2(1000, 0), 0, Vec2(1, 1));
		wchar_t Text[20];
		wsprintf(Text, L"%d", m_Score);
		IMAGE->RenderTextView(L"Score\n\n\nLife", Vec2(1020, 30), 0, 32);
		IMAGE->RenderTextView(Text, Vec2(1020, 80 - m_ScoreScale * 0.5), 0, m_ScoreScale, D3DCOLOR_XRGB(255, 255, 255 - (int)(m_ScoreScale - 32) * 20));
		for (int i = 0; i < Player->m_Hp; i++)
		{
			IMAGE->RenderView(m_Life, Vec2(1075 + i * 40, 126), 0, Vec2(0.12, 0.12));
		}

		int Plasma = min(255, Player->m_PlasmaAmmo * 13.6);
		int Chain = min(255, Player->m_ChainAmmo * 10.2);
		int Rocket = min(255, Player->m_RocketAmmo * 68);
		int Sniper = min(255, Player->m_SniperAmmo * 85);

		IMAGE->RenderTextView(L"Plasma", Vec2(1020, 160), 0, 32, D3DCOLOR_XRGB(255, Plasma, Plasma));
		wsprintf(Text, L"%d", Player->m_PlasmaAmmo);
		IMAGE->RenderTextView(Text, Vec2(1030, 192), 0, 32, D3DCOLOR_XRGB(255, Plasma, Plasma));
		IMAGE->RenderTextView(L"/  75", Vec2(1090, 192), 0, 32, D3DCOLOR_XRGB(255, Plasma, Plasma));
		IMAGE->RenderTextView(L"\n\nChaingun", Vec2(1020, 160), 0, 32, D3DCOLOR_XRGB(255, Chain, Chain));
		wsprintf(Text, L"\n\n%d", Player->m_ChainAmmo);
		IMAGE->RenderTextView(Text, Vec2(1030, 192), 0, 32, D3DCOLOR_XRGB(255, Chain, Chain));
		IMAGE->RenderTextView(L"\n\n/  100", Vec2(1090, 192), 0, 32, D3DCOLOR_XRGB(255, Chain, Chain));
		IMAGE->RenderTextView(L"\n\n\n\nRocket", Vec2(1020, 160), 0, 32, D3DCOLOR_XRGB(255, Rocket, Rocket));
		wsprintf(Text, L"\n\n\n\n%d", Player->m_RocketAmmo);
		IMAGE->RenderTextView(Text, Vec2(1030, 192), 0, 32, D3DCOLOR_XRGB(255, Rocket, Rocket));
		IMAGE->RenderTextView(L"\n\n\n\n/  15", Vec2(1090, 192), 0, 32, D3DCOLOR_XRGB(255, Rocket, Rocket));
		IMAGE->RenderTextView(L"\n\n\n\n\n\nSniper", Vec2(1020, 160), 0, 32, D3DCOLOR_XRGB(255, Sniper, Sniper));
		wsprintf(Text, L"\n\n\n\n\n\n%d", Player->m_SniperAmmo);
		IMAGE->RenderTextView(Text, Vec2(1030, 192), 0, 32, D3DCOLOR_XRGB(255, Sniper, Sniper));
		IMAGE->RenderTextView(L"\n\n\n\n\n\n/  10", Vec2(1090, 192), 0, 32, D3DCOLOR_XRGB(255, Sniper, Sniper));

		if (Player->m_Weapon != Wep_Plasma && Player->m_Weapon != Wep_BFG)
		{
			IMAGE->RenderTextView(L"Plasma", Vec2(1020, 160), 0, 32, D3DCOLOR_ARGB(150, 0, 0, 0));
			wsprintf(Text, L"%d", Player->m_PlasmaAmmo);
			IMAGE->RenderTextView(Text, Vec2(1030, 192), 0, 32, D3DCOLOR_ARGB(150, 0, 0, 0));
			IMAGE->RenderTextView(L"/  75", Vec2(1090, 192), 0, 32, D3DCOLOR_ARGB(150, 0, 0, 0));
		}
		if (Player->m_Weapon != Wep_Chain)
		{
			IMAGE->RenderTextView(L"\n\nChaingun", Vec2(1020, 160), 0, 32, D3DCOLOR_ARGB(150, 0, 0, 0));
			wsprintf(Text, L"\n\n%d", Player->m_ChainAmmo);
			IMAGE->RenderTextView(Text, Vec2(1030, 192), 0, 32, D3DCOLOR_ARGB(150, 0, 0, 0));
			IMAGE->RenderTextView(L"\n\n/  100", Vec2(1090, 192), 0, 32, D3DCOLOR_ARGB(150, 0, 0, 0));
		}
		if (Player->m_Weapon != Wep_Rocket)
		{
			IMAGE->RenderTextView(L"\n\n\n\nRocket", Vec2(1020, 160), 0, 32, D3DCOLOR_ARGB(150, 0, 0, 0));
			wsprintf(Text, L"\n\n\n\n%d", Player->m_RocketAmmo);
			IMAGE->RenderTextView(Text, Vec2(1030, 192), 0, 32, D3DCOLOR_ARGB(150, 0, 0, 0));
			IMAGE->RenderTextView(L"\n\n\n\n/  15", Vec2(1090, 192), 0, 32, D3DCOLOR_ARGB(150, 0, 0, 0));
		}
		if (Player->m_Weapon != Wep_Sniper)
		{
			IMAGE->RenderTextView(L"\n\n\n\n\n\nSniper", Vec2(1020, 160), 0, 32, D3DCOLOR_ARGB(150, 0, 0, 0));
			wsprintf(Text, L"\n\n\n\n\n\n%d", Player->m_SniperAmmo);
			IMAGE->RenderTextView(Text, Vec2(1030, 192), 0, 32, D3DCOLOR_ARGB(150, 0, 0, 0));
			IMAGE->RenderTextView(L"\n\n\n\n\n\n/  10", Vec2(1090, 192), 0, 32, D3DCOLOR_ARGB(150, 0, 0, 0));
		}
	}
}

void cSystemManager::Release()
{
}
