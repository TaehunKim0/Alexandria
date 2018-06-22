#include "stdafx.h"
#include "Camera.h"


Camera::Camera() :
	m_EyePt(0.f,0.f,-30.f)
	, m_fRotX(0.f)
	, m_fRotY(0.f)
	, m_LookAtPt(0.f,0.f,0.f)
	, m_RightVec(0.f,0.f,0.f)
	, m_UpVec(0.f,1.f,0.f)
	, CameraFreeView(1)
	, m_Target(nullptr)
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
	auto device = Renderer::GetInstance()->GetDevice();

	//카메라 SRT 순서로 해야함
	D3DXMATRIXA16 matRot;
	D3DXMATRIXA16 matRotX;
	D3DXMATRIXA16 matRotY;
	D3DXVECTOR3 vLook;

	if (CameraFreeView == false)
	{
		m_fRotX = 0.f;
		m_fRotY = 0.f;
	}

	if (Input::GetInstance()->GetKeyState(VK_RBUTTON) == KeyState::Pressed)
	{
		m_fRotX -= Input::GetInstance()->GetDeltaMove().x / 300;
		m_fRotY -= Input::GetInstance()->GetDeltaMove().y / 300;
	}

	D3DXMatrixRotationY(&matRotX, m_fRotX);
	D3DXMatrixRotationX(&matRotY, m_fRotY);

	matRot = matRotY * matRotX;

	if (CameraFreeView == false)
		if (Input::GetInstance()->GetButtonDown() == true)
			D3DXVec3TransformCoord(&m_EyePt, &m_EyePt, &matRot); //눈 위치 계산


	D3DXVec3TransformNormal(&vLook, &D3DXVECTOR3(0, 0, 1), &matRot); //볼 방향을 계산
	D3DXVec3Cross(&m_RightVec, &m_UpVec, &m_LookAtPt);
	D3DXVec3Normalize(&m_RightVec, &m_RightVec);


	//D3DXVec3TransformNormal(&vLook, &D3DXVECTOR3(0,0,1), &matRot); //회전한 곳의 방향을 vLook에 넣음
	//D3DXVec3TransformNormal -> 이 함수는 3차원 벡터와 행렬의 곱이고 여러 변환들 (이동 , 크기 , 회전)을 적용할 때 쓰임.
	//vLook 은 방향을 의미하게 된다.
	//D3DXVec3TransformCoord -> 이 함수도 3차원 벡터와 행렬의 곱인데 3차원 벡터를 4차원 벡터로 바꿀 때 마지막을 1 로 해 이동을 적용 시킴
	//vLook 은 좌표 개념이 된다.

	//LookAtPt = EyePt + vLook;//눈에서 바라볼 방향을 더함
	//이 자리에 타겟의 위치를 넣으면 카메라가 그 타겟을 바라봄.

	if (CameraFreeView == false)
	{
		if (m_Target)
		{
			m_LookAtPt = m_Target->GetTransform()->GetPosition();		// 카메라는 항상 타겟을 바라본다. (3인칭 시점)
		}
	}
	else
	{
		m_LookAtPt = m_EyePt + vLook;
	}

	vLook *= 0.5f;
	m_RightVec *= 0.5f;
	if (Input::GetInstance()->GetKeyState('W') == KeyState::Pressed)
	{
		m_EyePt += vLook;
		m_LookAtPt += vLook;
	}
	if (Input::GetInstance()->GetKeyState('S') == KeyState::Pressed)
	{
		m_EyePt -= vLook;
		m_LookAtPt -= vLook;
	}
	if (Input::GetInstance()->GetKeyState('A') == KeyState::Pressed)
	{
		m_EyePt += m_RightVec;
		m_LookAtPt += m_RightVec;
	}
	if (Input::GetInstance()->GetKeyState('D') == KeyState::Pressed)
	{
		m_EyePt -= m_RightVec;
		m_LookAtPt -= m_RightVec;
	}

	//업데이트
	SetTransform();
}

void Camera::SetTransform()
{
	Renderer::GetInstance()->GetDevice()->SetTransform(D3DTS_WORLD, &m_matWorld);

	D3DXMatrixLookAtLH(&m_matView, &m_EyePt, &m_LookAtPt, &m_UpVec);
	Renderer::GetInstance()->GetDevice()->SetTransform(D3DTS_VIEW, &m_matView);
}
