#pragma once
class cItem : public cComponent
{
public:
	cItem(cObject* Owner);
	~cItem();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

private:
	Vec2 m_Spread;
	float m_Speed;
};

