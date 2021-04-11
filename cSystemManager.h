#pragma once
class cSystemManager : public cSingleton<cSystemManager>
{
public:
	cSystemManager();
	~cSystemManager();

	void Init();
	void Update();
	void Render();
	void Release();

private:
	float m_TimeScale;
	float m_TimeScaleTimer;
	float m_ScoreScale;
	int m_Score;
	bool m_Doot;
	int m_Time;

	Texture* m_Sidebar;
	Texture* m_Life;

public:
	float GetTimeScale() { return m_TimeScale; }
	void SetTimeScale(float Scale, int Time) { m_TimeScale = Scale; m_TimeScaleTimer = Time; }
	int GetScore() { return m_Score; }
	void SetScore(int Score) { m_Score = Score; }
	void AddScore(int Score) { m_Score += Score; m_ScoreScale = max(40, min(64, Score * 0.01)); }
	void SetDoot(bool Doot) { m_Doot = Doot; }
	bool GetDoot() { return m_Doot; }
	void SetTime(int Time) { m_Time = Time; }
	int GetTime() { return m_Time; }
};

#define SYSTEM cSystemManager::GetInstance()