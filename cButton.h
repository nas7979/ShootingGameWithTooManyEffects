#pragma once
class cButton : public cComponent
{
public:
	cButton(cObject* Owner);
	~cButton();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

private:
	Vec2 m_Size;
	LPWSTR m_Text;

public:
	void SetSize(Vec2 Size) { m_Size = Size; }
	void SetText(LPWSTR Text) { m_Text = Text; }
};

