#pragma once
struct Texture
{
	LPDIRECT3DTEXTURE9 Image;
	D3DXIMAGE_INFO Info;
};
class cImageManager : public cSingleton<cImageManager>
{
public:
	cImageManager();
	~cImageManager();

	void Init();
	void Release();
	void Begin();
	void End();
	void OnLostDevice();
	void OnResetDevice();

private:
	map<string, Texture*> m_Images;
	map<string, vector<Texture*>*> m_Animations;
	LPD3DXSPRITE m_Sprite;
	LPD3DXFONT m_Font[33] = { nullptr, };

public:
	void AddImage(string Key, string Path);
	Texture* Find(string Key);
	vector<Texture*>* FindAnimation(string Key);

	void Render(Texture* Image, Vec2 Pos, float Rot, Vec2 Scale, D3DCOLOR Color = D3DCOLOR_XRGB(255, 255, 255));
	void CenterRender(Texture* Image, Vec2 Pos, float Rot, Vec2 Scale, D3DCOLOR Color = D3DCOLOR_XRGB(255, 255, 255));
	void RenderView(Texture* Image, Vec2 Pos, float Rot, Vec2 Scale, D3DCOLOR Color = D3DCOLOR_XRGB(255, 255, 255));
	void CenterRenderView(Texture* Image, Vec2 Pos, float Rot, Vec2 Scale, D3DCOLOR Color = D3DCOLOR_XRGB(255, 255, 255));
	void RenderText(LPWSTR Text, Vec2 Pos, float Rot, float Scale, D3DCOLOR Color = D3DCOLOR_XRGB(255, 255, 255));
	void RenderTextView(LPWSTR Text, Vec2 Pos, float Rot, float Scale, D3DCOLOR Color = D3DCOLOR_XRGB(255, 255, 255));
	void MakeAnimation(string Key);
};

#define IMAGE cImageManager::GetInstance()