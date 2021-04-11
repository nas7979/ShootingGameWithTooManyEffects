#pragma once
#include "cSingleton.h"
#include "cScene.h"
class cSceneManager : public cSingleton<cSceneManager>
{
public:
	cSceneManager();
	~cSceneManager();

	void Init();
	void Update();
	void Render();
	void Release();
	
private:
	cScene* m_CurScene;
	cScene* m_NewScene;
	map<string, cScene*> m_Scenes;

public:
	void AddScene(string Key, cScene* Scene);
	void ChangeScene(string Key);
	string GetCurScene();
};

#define SCENE cSceneManager::GetInstance()