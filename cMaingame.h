#pragma once
class cMaingame
{
public:
	cMaingame();
	~cMaingame();

	void Init();
	void Update();
	void Render();
	void Release();
	void OnLostDevice();
	void OnResetDevice();
};

