#pragma once
#include "cParticle_Base.h"
#include "cParticle_Anim.h"
#include "cParticle.h"
#include "cParticle_Emitter.h"

class cParticleManager : public cSingleton<cParticleManager>
{
public:
	cParticleManager();
	~cParticleManager();

	void Init();
	void Update();
	void RenderUp();
	void RenderDown();
	void Release();

private:
	list<cParticle_Base*> m_Particles_Up;
	list<cParticle_Base*> m_Particles_Down;

public:
	cParticle_Base* AddParticle(Texture* Image, Vec2 Pos, float Rot, bool Up, D3DCOLOR Color = 0xffffffff);
	void SetSpeed(cParticle_Base* Part, float Speed, float SpeedVel, float Direction);
	void SetRotation(cParticle_Base * Part, float Rot, float RotSpeed, float RotVel);
	void SetScale(cParticle_Base * Part, Vec2 Scale, Vec2 ScaleSpeed, float ScaleVel);
	void SetAlpha(cParticle_Base * Part, float Alpha, float AlphaSpeed, float AlphaVel);
	void ClearAll();

	template <typename T>
	T* AddParticle(Texture* Image, Vec2 Pos, float Rot, bool Up, D3DCOLOR Color = 0xffffffff)
	{
		T* a = new T;
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
};

#define PARTICLE cParticleManager::GetInstance()