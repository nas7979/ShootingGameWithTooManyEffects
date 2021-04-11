#pragma once
class cTimeLine_Zako2 : public cTimeLine
{
public:
	cTimeLine_Zako2(cObject* Owner);
	~cTimeLine_Zako2();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

private:
	Texture* m_BulletImage;
};

