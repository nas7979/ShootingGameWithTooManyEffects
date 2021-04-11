#pragma once
class cLoadingScene : public cScene
{
public:
	cLoadingScene();
	~cLoadingScene();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

private:
	void AddImage(string Key, string Path, int Amount = 1);
	void AddSound(string Key, LPWSTR Path, int Amount = 1);
};

