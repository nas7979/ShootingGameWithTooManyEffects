#pragma once
class cTimeLine_Zako4 : public cTimeLine
{
public:
	cTimeLine_Zako4(cObject* Owner);
	~cTimeLine_Zako4();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

private:
	Texture* m_BulletImage;
};

