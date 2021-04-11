#include "DXUT.h"
#include "cSceneManager.h"


cSceneManager::cSceneManager()
{
	Init();
}


cSceneManager::~cSceneManager()
{
	Release();
}

void cSceneManager::Init()
{
	m_CurScene = nullptr;
	m_NewScene = nullptr;
}

void cSceneManager::Update()
{
	if (m_NewScene)
	{
		if (m_CurScene)
			m_CurScene->Release();
		OBJECT->ClearAll();
		PARTICLE->ClearAll();
		m_CurScene = m_NewScene;
		m_NewScene = nullptr;
		m_CurScene->Init();
	}
	if (m_CurScene)
	{
		m_CurScene->Update();
	}
}

void cSceneManager::Render()
{
	if (m_CurScene)
	{
		m_CurScene->Render();
	}
}

void cSceneManager::Release()
{
	for (auto& iter : m_Scenes)
	{
		SAFE_DELETE(iter.second);
	}
}

void cSceneManager::AddScene(string Key, cScene * Scene)
{
	m_Scenes.insert(make_pair(Key, Scene));
}

void cSceneManager::ChangeScene(string Key)
{
	m_NewScene = m_Scenes[Key];
}

string cSceneManager::GetCurScene()
{
	for (auto& iter : m_Scenes)
	{
		if (iter.second == m_CurScene)
		{
			return iter.first;
		}
	}
}
