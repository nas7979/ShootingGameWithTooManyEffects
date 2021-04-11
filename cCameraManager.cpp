#include "DXUT.h"
#include "cCameraManager.h"


cCameraManager::cCameraManager()
{
	Init();
}


cCameraManager::~cCameraManager()
{
	Release();
}

void cCameraManager::Init()
{
	Matrix Proj;
	D3DXMatrixOrthoLH(&Proj, WINSIZEX, WINSIZEY, 0, 10000);
	g_Device->SetTransform(D3DTS_PROJECTION, &Proj);
	m_Pos = Vec2(0, 0);
	m_Rot = 0;
	m_InShake = false;
	m_ShakePos = Vec2(0, 0);
	m_ShakeForce = 0;
}

void cCameraManager::Update()
{
	if (m_InShake)
	{
		m_ShakePos = Vec2((int)Random(-m_ShakeForce, m_ShakeForce), (int)Random(-m_ShakeForce, m_ShakeForce));
		m_ShakeForce -= m_ShakeForcePerFrame;
		m_ShakeTime--;
		if (m_ShakeTime == 0)
		{
			m_InShake = false;
			m_ShakePos = Vec2(0, 0);
		}
	}
	D3DXMatrixTransformation2D(&m_Mat, NULL, 0, &Vec2(1, 1), &Vec2(WINSIZEX * 0.5, WINSIZEY * 0.5), m_Rot, &(m_Pos + m_ShakePos));
}

void cCameraManager::Render()
{
	g_Device->SetTransform(D3DTS_VIEW, &m_Mat);
}

void cCameraManager::Release()
{
}

void cCameraManager::Shake(int Time, float Force)
{
	if (m_InShake)
	{
		if (m_ShakeForce < Force)
		{
			m_ShakeForce = Force;
			m_ShakeTime = Time;
			m_ShakeForcePerFrame = Force / Time;
		}
	}
	else
	{
		m_InShake = true;
		m_ShakeForce = Force;
		m_ShakeTime = Time;
		m_ShakeForcePerFrame = Force / Time;
	}
}
