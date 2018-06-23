#include "stdafx.h"
#include "PointLight.h"


PointLight::PointLight()
{
	m_Light.Type = D3DLIGHT_POINT;
	m_Light.Position = D3DXVECTOR3(0.f, 0.f, 0.f);
}


PointLight::~PointLight()
{
}

void PointLight::Init(D3DXCOLOR Diffuse, float Attenuation, float Range)
{
	m_Light.Diffuse.r = Diffuse.r;
	m_Light.Diffuse.g = Diffuse.g;
	m_Light.Diffuse.b = Diffuse.b;
	m_Light.Diffuse.a = Diffuse.a;

	m_Light.Attenuation0 = Attenuation;
	m_Light.Range = Range;
	
	Renderer::GetInstance()->SetLights(&m_Light);
}
