#include "stdafx.h"
#include "Transform.h"


Transform::Transform() :
	m_fRotX(0.f)
	, m_fRotY(0.f)
	, m_fRotZ(0.f)
	, m_Position(0.f,0.f,0.f)
	, m_Scale(1.f,1.f,1.f)
{
	D3DXMatrixIdentity(&m_wMatrix);
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixIdentity(&m_matRotation);
	D3DXMatrixIdentity(&m_matTranslation);
}


Transform::~Transform()
{
}

void Transform::SetTransform(LPDIRECT3DDEVICE9 device)
{
	device->AddRef();

	//Scale ����
	D3DXMatrixScaling(&m_matScale, m_Scale.x, m_Scale.y, m_Scale.z);

	//Rotation ����
	D3DXMatrixRotationX(&m_matRotX, m_fRotX); //X �� ������ ȸ�� ��Ʈ���� ����
	D3DXMatrixRotationY(&m_matRotY, m_fRotY); //Y �� ������ ȸ�� ��Ʈ���� ����
	D3DXMatrixRotationZ(&m_matRotZ, m_fRotZ); //Z �� ������ ȸ�� ��Ʈ���� ����
	D3DXMATRIX matR = m_matRotZ * m_matRotX * m_matRotY;

	//Translation ����
	D3DXMatrixTranslation(&m_matTranslation, m_Position.x, m_Position.y, m_Position.z);
	
	//S * R * T
	m_wMatrix = m_matScale * matR * m_matTranslation;


	device->SetTransform(D3DTS_WORLD, &m_wMatrix);
}
