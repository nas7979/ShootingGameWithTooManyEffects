#pragma once
class cMenuScene : public cScene
{
public:
	cMenuScene();
	~cMenuScene();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

private:
	string m_State;
};

