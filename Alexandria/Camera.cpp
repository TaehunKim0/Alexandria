#include "stdafx.h"
#include "Camera.h"


Camera::Camera() :
	m_EyePt(0.f,10.f,-30.f)
	, m_fRotX(0.f)
	, m_fRotY(0.f)
	, m_LookAtPt(0.f,0.f,0.f)
	, m_RightVec(0.f,0.f,0.f)
	, m_UpVec(0.f,1.f,0.f)
{
	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4, 1280.f / 720.f, 1.f, 1000.f);
	Renderer::GetInstance()->GetDevice()->SetTransform(D3DTS_PROJECTION, &m_matProj);

	D3DXMatrixIdentity(&m_matWorld);
}


Camera::~Camera()
{
}

void Camera::Update(float deltaTime)
{
	//업데이트
	SetTransform();
}

void Camera::SetTransform()
{
	Renderer::GetInstance()->GetDevice()->SetTransform(D3DTS_WORLD, &m_matWorld);

	D3DXMatrixLookAtLH(&m_matView, &m_EyePt, &m_LookAtPt, &m_UpVec);
	Renderer::GetInstance()->GetDevice()->SetTransform(D3DTS_VIEW, &m_matView);
}
