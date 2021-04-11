#pragma once
class cTimeLine_Zako6 : public cTimeLine
{
public:
	cTimeLine_Zako6(cObject* Owner);
	~cTimeLine_Zako6();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

private:
	Texture* m_BulletImage;
};

