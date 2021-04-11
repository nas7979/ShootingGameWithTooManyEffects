#include "DXUT.h"
#include "cInputManager.h"


cInputManager::cInputManager()
{
}


cInputManager::~cInputManager()
{
}

void cInputManager::Init()
{
}

void cInputManager::Update()
{
	memcpy(m_Old, m_Cur, sizeof(bool) * 128);
	memset(m_Cur, false, sizeof(bool) * 128);

	for (int i = 0; i < 128; i++)
	{
		if (GetAsyncKeyState(i) & 0x8000)
		{
			m_Cur[i] = true;
		}
	}

	POINT pPos;
	GetCursorPos(&pPos);
	ScreenToClient(DXUTGetHWND(), &pPos);
	m_MousePos = Vec2(pPos.x, pPos.y);
}

void cInputManager::Render()
{
}

void cInputManager::Release()
{
}

bool cInputManager::KeyDown(int Key)
{
	return m_Cur[Key];
}

bool cInputManager::KeyPress(int Key)
{
	return m_Cur[Key] && !m_Old[Key];
}

bool cInputManager::KeyUp(int Key)
{
	return !m_Cur[Key] && m_Old[Key];
}

Vec2 cInputManager::GetMousePos()
{
	return m_MousePos;
}

void cInputManager::SetMousePos(Vec2 Pos)
{
	POINT pPos = { Pos.x,Pos.y };
	ScreenToClient(DXUTGetHWND(), &pPos);
	SetCursorPos(pPos.x, pPos.y);
}
