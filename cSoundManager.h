#pragma once
class cSoundManager : public cSingleton<cSoundManager>
{
public:
	cSoundManager();
	~cSoundManager();

	void Init();
	void Update();
	void Release();

private:
	CSoundManager m_Manager;
	map<string, CSound*> m_Sounds;
	list<LPDIRECTSOUNDBUFFER> m_Buffers;

public:
	void AddSound(string Key, LPWSTR Path);
	void StopAll();
	LPDIRECTSOUNDBUFFER Play(string Key, bool Loop = false);

};

#define SOUND cSoundManager::GetInstance()
#define TOVOLUME(Vol) (DWORD)(-100 * (100 - Vol))