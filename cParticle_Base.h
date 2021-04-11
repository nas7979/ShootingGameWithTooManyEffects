#pragma once

class cParticle_Base
{
	friend class cParticleManager;
public:
	cParticle_Base();
	virtual ~cParticle_Base();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

public:
	Vec2 m_Pos;
	Vec2 m_Scale;
	float m_Rot;
	float m_Alpha;

	Texture* m_Image;
	D3DCOLOR m_Color;
	float m_Speed;
	float m_SpeedVel;
	float m_Direction;
	float m_RotationSpeed;
	float m_RotationVel;
	Vec2 m_ScaleSpeed;
	float m_ScaleVel;
	float m_AlphaSpeed;
	float m_AlphaVel;
};

