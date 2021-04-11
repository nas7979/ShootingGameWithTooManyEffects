#pragma once
class cTimeLine_Zako5 : public cTimeLine
{
public:
	cTimeLine_Zako5(cObject* Owner);
	~cTimeLine_Zako5();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

private:
	Texture* m_BulletImage;
};

