#pragma once
class cTimeLine_Zako7 : public cTimeLine
{
public:
	cTimeLine_Zako7(cObject* Owner);
	~cTimeLine_Zako7();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

private:
	float m_Direction;
};

