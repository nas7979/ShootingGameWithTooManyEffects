#pragma once
class cIngameScene : public cScene
{
public:
	cIngameScene();
	~cIngameScene();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	float m_Random;
};

