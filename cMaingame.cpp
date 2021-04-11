#include "DXUT.h"
#include "cMaingame.h"
#include "cLoadingScene.h"
#include "cIngameScene.h"
#include "cMenuScene.h"
#include "cScoreScene.h"

cMaingame::cMaingame()
{
}


cMaingame::~cMaingame()
{
}

void cMaingame::Init()
{
	SCENE->CreateInstance();
	IMAGE->CreateInstance();
	OBJECT->CreateInstance();
	INPUT->CreateInstance();
	PARTICLE->CreateInstance();
	SYSTEM->CreateInstance();
	SOUND->CreateInstance();
	CAMERA->CreateInstance();

	SCENE->AddScene("LOADING", new cLoadingScene);
	SCENE->AddScene("INGAME", new cIngameScene);
	SCENE->AddScene("MENU", new cMenuScene);
	SCENE->AddScene("SCORE", new cScoreScene);

	SCENE->ChangeScene("LOADING");
}

void cMaingame::Update()
{
	INPUT->Update();
	SYSTEM->Update();
	SCENE->Update();
	OBJECT->Update();
	SOUND->Update();
	PARTICLE->Update();
	CAMERA->Update();
}

void cMaingame::Render()
{
	IMAGE->Begin();
	CAMERA->Render();
	SCENE->Render();
	PARTICLE->RenderDown();
	OBJECT->Render();
	PARTICLE->RenderUp();
	SYSTEM->Render();
	IMAGE->End();
}

void cMaingame::Release()
{
	OBJECT->ReleaseInstance();
	SCENE->ReleaseInstance();
	IMAGE->ReleaseInstance();
	INPUT->ReleaseInstance();
	PARTICLE->ReleaseInstance();
	SYSTEM->ReleaseInstance();
	SOUND->ReleaseInstance();
	CAMERA->ReleaseInstance();
}

void cMaingame::OnLostDevice()
{
	IMAGE->OnLostDevice();
}

void cMaingame::OnResetDevice()
{
	IMAGE->OnResetDevice();
}
