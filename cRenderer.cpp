#include "DXUT.h"
#include "cRenderer.h"


cRenderer::cRenderer(cObject* Owner)
	:cComponent(Owner)
{
}


cRenderer::~cRenderer()
{
}

void cRenderer::Init()
{
	m_Color = D3DCOLOR_XRGB(255, 255, 255);
}

void cRenderer::Update()
{
}

void cRenderer::Render()
{
	IMAGE->CenterRender(m_Image, m_pObject->GetPosition(), D3DXToRadian(m_pObject->GetRotation()), m_pObject->GetScale(), m_Color);
}

void cRenderer::Release()
{
}
