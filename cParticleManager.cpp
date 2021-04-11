#include "DXUT.h"
#include "cParticleManager.h"


cParticleManager::cParticleManager()
{
	Init();
}


cParticleManager::~cParticleManager()
{
	Release();
}

void cParticleManager::Init()
{
}

void cParticleManager::Update()
{
	for (auto& iter = m_Particles_Up.begin(); iter != m_Particles_Up.end();)
	{
		(*iter)->Update();
		if ((*iter)->m_Alpha <= 0 || (*iter)->m_Scale.x <= 0 || (*iter)->m_Scale.y <= 0)
		{
			(*iter)->Release();
			SAFE_DELETE(*iter);
			iter = m_Particles_Up.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	for (auto& iter = m_Particles_Down.begin(); iter != m_Particles_Down.end();)
	{
		(*iter)->Update();
		if ((*iter)->m_Alpha <= 0 || (*iter)->m_Scale.x <= 0 || (*iter)->m_Scale.y <= 0)
		{
			(*iter)->Release();
			SAFE_DELETE(*iter);
			iter = m_Particles_Down.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void cParticleManager::RenderUp()
{
	for (auto& iter : m_Particles_Up)
	{
		iter->Render();
	}
}

void cParticleManager::RenderDown()
{
	for (auto& iter : m_Particles_Down)
	{
		iter->Render();
	}
}

void cParticleManager::Release()
{
	for (auto& iter : m_Particles_Up)
	{
		iter->Release();
		SAFE_DELETE(iter);
	}
	for (auto& iter : m_Particles_Down)
	{
		iter->Release();
		SAFE_DELETE(iter);
	}
}

cParticle_Base * cParticleManager::AddParticle(Texture * Image, Vec2 Pos, float Rot, bool Up, D3DCOLOR Color)
{
	cParticle_Base* a = new cParticle;
	a->Init();
	a->m_Image = Image;
	a->m_Pos = Pos;
	a->m_Rot = D3DXToRadian(Rot);
	a->m_Color = Color;
	if (Up)
	{
		m_Particles_Up.push_back(a);
	}
	else
	{
		m_Particles_Down.push_back(a);
	}
	return a;
}

void cParticleManager::SetSpeed(cParticle_Base * Part, float Speed, float SpeedVel, float Direction)
{
	Part->m_Speed = Speed;
	Part->m_SpeedVel = SpeedVel;
	Part->m_Direction = Direction;
}

void cParticleManager::SetRotation(cParticle_Base * Part, float Rot, float RotSpeed, float RotVel)
{
	Part->m_Rot = Rot;
	Part->m_RotationSpeed = RotSpeed;
	Part->m_RotationVel = RotVel;
}

void cParticleManager::SetScale(cParticle_Base * Part, Vec2 Scale, Vec2 ScaleSpeed, float ScaleVel)
{
	Part->m_Scale = Scale;
	Part->m_ScaleSpeed = ScaleSpeed;
	Part->m_ScaleVel = ScaleVel;
}

void cParticleManager::SetAlpha(cParticle_Base * Part, float Alpha, float AlphaSpeed, float AlphaVel)
{
	Part->m_Alpha = Alpha;
	Part->m_AlphaSpeed = AlphaSpeed;
	Part->m_AlphaVel = AlphaVel;
}

void cParticleManager::ClearAll()
{
	for (auto& iter : m_Particles_Up)
	{
		iter->Release();
		SAFE_DELETE(iter);
	}
	m_Particles_Up.clear();
	for (auto& iter : m_Particles_Down)
	{
		iter->Release();
		SAFE_DELETE(iter);
	}
	m_Particles_Down.clear();
}