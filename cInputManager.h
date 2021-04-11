#pragma once
class cInputManager : public cSingleton<cInputManager>
{
public:
	cInputManager();
	~cInputManager();

	void Init();
	void Update();
	void Render();
	void Release();

private:
	bool m_Cur[128];
	bool m_Old[128];
	Vec2 m_MousePos;

public:
	bool KeyDown(int Key);
	bool KeyPress(int Key);
	bool KeyUp(int Key);
	Vec2 GetMousePos();
	void SetMousePos(Vec2 Pos);
};

#define INPUT cInputManager::GetInstance()