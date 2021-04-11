#include "DXUT.h"
#include "cSoundManager.h"


cSoundManager::cSoundManager()
{
	Init();
}


cSoundManager::~cSoundManager()
{
	Release();
}

void cSoundManager::Init()
{
	m_Manager.Initialize(DXUTGetHWND(), 1);
}

void cSoundManager::Update()
{
	DWORD Status;
	for (auto& iter = m_Buffers.begin(); iter != m_Buffers.end();)
	{
		(*iter)->GetStatus(&Status);
		if ((Status & DSBSTATUS_PLAYING) == 0)
		{
			(*iter)->Release();
			iter = m_Buffers.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void cSoundManager::Release()
{
	for (auto& iter : m_Sounds)
	{
		SAFE_DELETE(iter.second);
	}
	for (auto& iter : m_Buffers)
	{
		iter->Release();
	}
}

void cSoundManager::AddSound(string Key, LPWSTR Path)
{
	CSound* a;
	m_Manager.Create(&a, Path, DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME);
	m_Sounds.insert(make_pair(Key, a));
}

void cSoundManager::StopAll()
{
	for (auto& iter : m_Buffers)
	{
		iter->Release();
	}
	m_Buffers.clear();
}

LPDIRECTSOUNDBUFFER cSoundManager::Play(string Key, bool Loop)
{
	LPDIRECTSOUNDBUFFER a;
	m_Manager.GetDirectSound()->DuplicateSoundBuffer(m_Sounds[Key]->GetBuffer(0), &a);
	a->Play(0, 0, Loop ? DSBPLAY_LOOPING : 0);
	m_Buffers.push_back(a);
	return a;
}
