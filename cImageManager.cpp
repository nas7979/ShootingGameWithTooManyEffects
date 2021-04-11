#include "DXUT.h"
#include "cImageManager.h"


cImageManager::cImageManager()
{
	Init();
}


cImageManager::~cImageManager()
{
	Release();
}

void cImageManager::Init()
{
	D3DXCreateSprite(g_Device, &m_Sprite);
	D3DXCreateFontW(g_Device, 32, 16, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"System", &m_Font[32]);
	D3DXCreateFontW(g_Device, 16, 8, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"µ¸¿ò", &m_Font[16]);
}

void cImageManager::Release()
{
	m_Sprite->Release();
	for (auto& iter : m_Font)
	{
		if (iter != nullptr)
		{
			iter->Release();
		}
	}
	for (auto& iter : m_Images)
	{
		iter.second->Image->Release();
		SAFE_DELETE(iter.second);
	}
	for (auto& iter : m_Animations)
	{
		SAFE_DELETE(iter.second);
	}
}

void cImageManager::Begin()
{
	m_Sprite->Begin(D3DXSPRITE_ALPHABLEND);
	g_Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DX_FILTER_NONE);
	g_Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DX_FILTER_NONE);
	g_Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DX_FILTER_NONE);
}

void cImageManager::End()
{
	m_Sprite->End();
}

void cImageManager::OnLostDevice()
{
	m_Sprite->OnLostDevice();
}

void cImageManager::OnResetDevice()
{
	m_Sprite->OnResetDevice();
}

void cImageManager::AddImage(string Key, string Path)
{
	Texture* Tex = new Texture;
	if (D3DXCreateTextureFromFileExA(g_Device, Path.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_POINT, D3DX_FILTER_POINT, 0, &Tex->Info, 0, &Tex->Image) == S_OK)
	{
		m_Images.insert(make_pair(Key, Tex));
	}
	else
	{
		SAFE_DELETE(Tex);
	}
}

Texture * cImageManager::Find(string Key)
{
	return m_Images[Key];
}

vector<Texture*>* cImageManager::FindAnimation(string Key)
{
	return m_Animations[Key];
}

void cImageManager::Render(Texture * Image, Vec2 Pos, float Rot, Vec2 Scale, D3DCOLOR Color)
{
	Matrix mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0, &Scale, NULL, Rot, &Pos);
	m_Sprite->SetTransform(&mat);
	m_Sprite->Draw(Image->Image, nullptr, nullptr, nullptr, Color);
}

void cImageManager::CenterRender(Texture * Image, Vec2 Pos, float Rot, Vec2 Scale, D3DCOLOR Color)
{
	Vec2 Center = Vec2(Image->Info.Width * 0.5, Image->Info.Height * 0.5);
	Matrix mat;
	D3DXMatrixTransformation2D(&mat, &Center, 0, &Scale, &Center, Rot, &(Pos - Center));
	m_Sprite->SetTransform(&mat);
	m_Sprite->Draw(Image->Image, nullptr, nullptr, nullptr, Color);
}

void cImageManager::RenderView(Texture * Image, Vec2 Pos, float Rot, Vec2 Scale, D3DCOLOR Color)
{
	Matrix mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0, &Scale, NULL, Rot, &(Pos + CAMERA->GetPosition()));
	m_Sprite->SetTransform(&mat);
	m_Sprite->Draw(Image->Image, nullptr, nullptr, nullptr, Color);
}

void cImageManager::CenterRenderView(Texture * Image, Vec2 Pos, float Rot, Vec2 Scale, D3DCOLOR Color)
{
}

void cImageManager::RenderText(LPWSTR Text, Vec2 Pos, float Rot, float Scale, D3DCOLOR Color)
{
	Matrix mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0, &Vec2(Scale / 32, Scale / 32), NULL, Rot, &Pos);
	m_Sprite->SetTransform(&mat);
	m_Font[32]->DrawTextW(m_Sprite, Text, -1, NULL, DT_NOCLIP, Color);
}

void cImageManager::RenderTextView(LPWSTR Text, Vec2 Pos, float Rot, float Scale, D3DCOLOR Color)
{
	Matrix mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0, &Vec2(Scale / 32, Scale / 32), NULL, Rot, &(Pos + CAMERA->GetPosition()));
	m_Sprite->SetTransform(&mat);
	m_Font[32]->DrawTextW(m_Sprite, Text, -1, NULL, DT_NOCLIP, Color);
}

void cImageManager::MakeAnimation(string Key)
{
	vector<Texture*>* Temp = new vector<Texture*>();
	char Name[50];
	for (int i = 1; true; i++)
	{
		sprintf(Name, "%s%d", Key.c_str(), i);
		auto Find = m_Images.find(Name);
		if (Find != m_Images.end())
		{
			Temp->push_back(m_Images[Name]);
		}
		else
		{
			break;
		}
	}
	m_Animations.insert(make_pair(Key, Temp));
}
