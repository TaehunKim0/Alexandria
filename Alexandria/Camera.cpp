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

	//ī�޶� SRT ������ �ؾ���
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
			D3DXVec3TransformCoord(&m_EyePt, &m_EyePt, &matRot); //�� ��ġ ���


	D3DXVec3TransformNormal(&vLook, &D3DXVECTOR3(0, 0, 1), &matRot); //�� ������ ���
	D3DXVec3Cross(&m_RightVec, &m_UpVec, &m_LookAtPt);
	D3DXVec3Normalize(&m_RightVec, &m_RightVec);


	//D3DXVec3TransformNormal(&vLook, &D3DXVECTOR3(0,0,1), &matRot); //ȸ���� ���� ������ vLook�� ����
	//D3DXVec3TransformNormal -> �� �Լ��� 3���� ���Ϳ� ����� ���̰� ���� ��ȯ�� (�̵� , ũ�� , ȸ��)�� ������ �� ����.
	//vLook �� ������ �ǹ��ϰ� �ȴ�.
	//D3DXVec3TransformCoord -> �� �Լ��� 3���� ���Ϳ� ����� ���ε� 3���� ���͸� 4���� ���ͷ� �ٲ� �� �������� 1 �� �� �̵��� ���� ��Ŵ
	//vLook �� ��ǥ ������ �ȴ�.

	//LookAtPt = EyePt + vLook;//������ �ٶ� ������ ����
	//�� �ڸ��� Ÿ���� ��ġ�� ������ ī�޶� �� Ÿ���� �ٶ�.

	if (CameraFreeView == false)
	{
		if (m_Target)
		{
			m_LookAtPt = m_Target->GetTransform()->GetPosition();		// ī�޶�� �׻� Ÿ���� �ٶ󺻴�. (3��Ī ����)
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

	//������Ʈ
	SetTransform();
}

void Camera::SetTransform()
{
	Renderer::GetInstance()->GetDevice()->SetTransform(D3DTS_WORLD, &m_matWorld);

	D3DXMatrixLookAtLH(&m_matView, &m_EyePt, &m_LookAtPt, &m_UpVec);
	Renderer::GetInstance()->GetDevice()->SetTransform(D3DTS_VIEW, &m_matView);
}
