#pragma once
class cScoreScene : public cScene
{
public:
	cScoreScene();
	~cScoreScene();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

private:
};

