#pragma once
class cRenderer : public cComponent
{
public:
	cRenderer(cObject* Owner);
	~cRenderer();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

private:
	Texture* m_Image;
	D3DCOLOR m_Color;

public:
	void SetImage(Texture* Image) { m_Image = Image; }
	void SetColor(D3DCOLOR Color) { m_Color = Color; }
	D3DCOLOR GetColor() { return m_Color; }
};

