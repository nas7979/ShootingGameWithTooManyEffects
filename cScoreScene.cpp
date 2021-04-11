#include "DXUT.h"
#include "cScoreScene.h"


cScoreScene::cScoreScene()
{
}


cScoreScene::~cScoreScene()
{
}

void cScoreScene::Init()
{
	cParticle_Base* b = PARTICLE->AddParticle(IMAGE->Find("Background2"), Vec2(640, 360), 0, true, D3DCOLOR_XRGB(0, 0, 0));
	PARTICLE->SetAlpha(b, 255, -2, 1.03);
}

void cScoreScene::Update()
{
	if (INPUT->KeyPress(VK_LBUTTON))
	{
		SCENE->ChangeScene("MENU");
	}
}

void cScoreScene::Render()
{
	if (SYSTEM->GetDoot())
	{
		IMAGE->Render(IMAGE->Find("ScoreDoot"), Vec2(0, 0), 0, Vec2(1, 1));
	}
	else
	{
		IMAGE->Render(IMAGE->Find("Background2"), Vec2(0, 0), 0, Vec2(1, 1));
	}

	wchar_t Text[100];
	wsprintf(Text, L"Score : %d", SYSTEM->GetScore());
	IMAGE->RenderText(Text, Vec2(300, 260), 0, 64);
	wsprintf(Text, L"Time : %d:%d", (int)(SYSTEM->GetTime() / 60 / 60), (SYSTEM->GetTime() / 60) % 60);
	IMAGE->RenderText(Text, Vec2(300, 340), 0, 64);
}

void cScoreScene::Release()
{
}
