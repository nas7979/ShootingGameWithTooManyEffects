#pragma once
class cCameraManager : public cSingleton<cCameraManager>
{
public:
	cCameraManager();
	~cCameraManager();

	void Init();
	void Update();
	void Render();
	void Release();

private:
	Matrix m_Mat;
	Vec2 m_Pos;
	Vec2 m_ShakePos;
	float m_Rot;
	bool m_InShake;
	float m_ShakeForce;
	float m_ShakeForcePerFrame;
	int m_ShakeTime;

public:
	void SetPosition(Vec2 Pos) { m_Pos = Pos; }
	Vec2 GetPosition() { return m_Pos - m_ShakePos; }
	void SetRotation(float Rot) { m_Rot = Rot; }
	float GetRotation() { return m_Rot; }
	void Shake(int Time, float Force);
	Matrix GetMatrix() { return m_Mat; }
};

#define CAMERA cCameraManager::GetInstance()