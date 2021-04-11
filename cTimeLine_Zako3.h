#pragma once
class cTimeLine_Zako3 : public cTimeLine
{
public:
	cTimeLine_Zako3(cObject* Owner);
	~cTimeLine_Zako3();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

private:
	Texture* m_BulletImage;
};