#include "DXUT.h"
#include "cParticle_Emitter.h"


cParticle_Emitter::cParticle_Emitter()
{
}


cParticle_Emitter::~cParticle_Emitter()
{
}

void cParticle_Emitter::Init()
{
	m_Scale = Vec2(1, 1);
	m_Alpha = 255;
	m_Speed = 0;
	m_SpeedVel = 1;
	m_Direction = 0;
	m_RotationSpeed = 0;
	m_RotationVel = 1;
	m_ScaleSpeed = Vec2(0, 0);
	m_ScaleVel = 1;
	m_AlphaSpeed = 0;
	m_AlphaVel = 1;
}

void cParticle_Emitter::Update()
{
	float TimeScale = SYSTEM->GetTimeScale();
	float VelTimeScale = 1 / (1 / TimeScale);

	m_Speed *= pow(m_SpeedVel, VelTimeScale);
	m_RotationSpeed *= pow(m_RotationVel, VelTimeScale);
	m_ScaleSpeed *= pow(m_ScaleVel, VelTimeScale);
	m_AlphaSpeed *= pow(m_AlphaVel, VelTimeScale);

	m_Pos += Vec2(cos(D3DXToRadian(m_Direction)), sin(D3DXToRadian(m_Direction))) * m_Speed * TimeScale;
	m_Rot += m_RotationSpeed * TimeScale;
	m_Scale += m_ScaleSpeed * TimeScale;
	m_Alpha += m_AlphaSpeed * TimeScale;

	m_Color = ((((int)min(m_Alpha, 255)) & 0xff) << 24) | ((m_Color >> 16) & 0xff) << 16 | ((m_Color >> 8) & 0xff) << 8 | (m_Color & 0xff);

	m_Timer -= TimeScale;
	if (m_Timer <= 0)
	{
		m_EmitterFunc(this);
		m_Timer = m_EmitterSpeed;
	}
}

void cParticle_Emitter::Render()
{
	IMAGE->CenterRender(m_Image, m_Pos, m_Rot, m_Scale, m_Color);
}

void cParticle_Emitter::Release()
{
}
