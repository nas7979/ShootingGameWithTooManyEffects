#pragma once
class cTimeLine_Zako1 : public cTimeLine
{
public:
	cTimeLine_Zako1(cObject* Owner);
	~cTimeLine_Zako1();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

private:
	Texture* m_BulletImage;
};

