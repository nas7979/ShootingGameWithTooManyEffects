#include "DXUT.h"
#include "cLoadingScene.h"


cLoadingScene::cLoadingScene()
{
}


cLoadingScene::~cLoadingScene()
{
}

void cLoadingScene::Init()
{
	AddImage("Cruiser3", "Ships and Stations/Cruiser 3");
	AddImage("Flame", "Effect/flame_0", 4);
	AddImage("Muzzle", "Effect/Rotated/muzzle_0", 5);
	AddImage("Bullet", "Bullets/Bullet", 5);
	AddImage("Bullet_BFG", "Bullets/Bullet_BFG", 2);
	IMAGE->MakeAnimation("Bullet_BFG");
	AddImage("Sniper_Trail", "Effect/Exhaust");
	AddImage("Trace", "Effect/Rotated/trace_0", 7);
	AddImage("Laser", "Effect/Rotated/Laser", 3);
	AddImage("Burst", "Effect/Burst");
	AddImage("Smoke", "Effect/Smoke ", 3);
	AddImage("Spark", "Effect/spark_0", 4);
	AddImage("Explosion_Small", "Effect/Explosion_Small", 31);
	IMAGE->MakeAnimation("Explosion_Small");
	AddImage("BFGHit", "Effect/BFGHit", 6);
	IMAGE->MakeAnimation("BFGHit");
	AddImage("Circle", "Effect/circle_0", 5);
	AddImage("Debris", "Debris/Debris", 6);
	AddImage("Turret_Large", "Turrets/Turret Large ", 2);
	AddImage("Turret_Medium", "Turrets/Turret Medium ", 4);
	AddImage("Turret_Small", "Turrets/Turret Small ", 4);
	AddImage("Coll_Circle", "Coll_Circle");
	AddImage("Zako", "Ships and Stations/Alien ", 4);
	AddImage("Background", "Backgrounds/Red Nebula 2048/background", 2);
	AddImage("Sidebar", "Sidebar");
	AddImage("Ammo", "Ammo");
	AddImage("Doot", "Ships and Stations/Doot");
	AddImage("Title", "Title");
	AddImage("ScoreDoot", "ScoreDoot");

	AddSound("Wep_Default_Fire", L"Wep_Default_Fire");
	AddSound("Wep_Default_Hit", L"supersonic_snap_0", 9);
	AddSound("Wep_Plasma_Fire", L"Wep_Plasma_Fire");
	AddSound("Wep_Plasma_Hit", L"Wep_Plasma_Hit", 3);
	AddSound("Wep_Chain_Fire", L"Wep_Chain_Fire");
	AddSound("Wep_Rocket_Fire", L"Wep_Rocket_Fire", 2);
	AddSound("Wep_Rocket_Hit", L"Wep_Rocket_Hit");
	AddSound("Wep_Sniper_Fire", L"Wep_Sniper_Fire");
	AddSound("Wep_BFG_Charge", L"Wep_BFG_Charge");
	AddSound("Wep_BFG_Fire", L"Wep_BFG_Fire");
	AddSound("Wep_BFG_Hit", L"Wep_BFG_Hit");
	AddSound("Dash", L"subsonic_0", 6);
	AddSound("Explosion_Small", L"mortar_strike_far_0", 4);
	AddSound("BGM", L"BGM");
	AddSound("Doot", L"Doot");
	AddSound("PlayerHit", L"se_pldead00");
	AddSound("Melee", L"Melee");
	AddSound("Ammo", L"Ammo");
	AddSound("OutofAmmo", L"OutofAmmo");

	SCENE->ChangeScene("MENU");
}

void cLoadingScene::Update()
{
}

void cLoadingScene::Render()
{
}

void cLoadingScene::Release()
{
}

void cLoadingScene::AddImage(string Key, string Path, int Amount)
{
	char _Path[100];
	if (Amount == 1)
	{
		sprintf(_Path, "Resource/Image/%s.png", Path.c_str());
		IMAGE->AddImage(Key, _Path);
	}
	else
	{
		char _Key[50];
		for (int i = 1; i <= Amount; i++)
		{
			sprintf(_Path, "Resource/Image/%s%d.png", Path.c_str(), i);
			sprintf(_Key, "%s%d", Key.c_str(), i);
			IMAGE->AddImage(_Key, _Path);
		}
	}
}

void cLoadingScene::AddSound(string Key, LPWSTR Path, int Amount)
{
	wchar_t _Path[100];
	if (Amount == 1)
	{
		wsprintf(_Path, L"Resource/Sound/%s.wav", Path);
		SOUND->AddSound(Key, LPWSTR(_Path));
	}
	else
	{
		char _Key[50];
		for (int i = 1; i <= Amount; i++)
		{
			wsprintf(_Path, L"Resource/Sound/%s%d.wav", Path, i);
			sprintf(_Key, "%s%d", Key.c_str(), i);
			SOUND->AddSound(_Key, LPWSTR(_Path));
		}
	}
}
