#include "stdafx.h"
#include "Renderer.h"


Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

bool Renderer::Init()
{
	m_D3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS pp = {};
	pp.Windowed = (Application::GetInstance()->GetWindowed());
	pp.BackBufferWidth = Application::GetInstance()->GetWindowWidth();
	pp.BackBufferHeight = Application::GetInstance()->GetWindowHeight();
	pp.BackBufferFormat = D3DFMT_A8R8G8B8;
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp.AutoDepthStencilFormat = D3DFMT_D16;
	pp.EnableAutoDepthStencil = true;

	if (FAILED(m_D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Application::GetInstance()->GetHandle(), D3DCREATE_SOFTWARE_VERTEXPROCESSING, &pp, &m_D3DDevice)))
	{
		MessageBox(nullptr, L"Devide Create Arror", L"Arror", MB_OK);
		return false;
	}

	m_D3DDevice->SetRenderState(D3DRS_ZENABLE, true); //���� �׽�Ʈ 
	m_D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //�ø� 
	m_D3DDevice->SetRenderState(D3DRS_LIGHTING, true); //������ 

	m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true); //���� ����
	m_D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); //�ؽ��İ� ���� ���� �״�� ��
	m_D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); //�ؽ��İ� ���� ���ĸ� 1 - srcalpha

	m_D3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR); //�ָ� �ִ� �ؽ��� ���
	m_D3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); //������ �ִ� �ؽ��� Ȯ��
	m_D3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR); //�ڿ������� ����

	ZeroMemory(&Light, sizeof(D3DLIGHT9));

	Light.Type = D3DLIGHT_DIRECTIONAL;

	Light.Direction = D3DXVECTOR3(0.f, -1.f, 1.f);

	Light.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f); //���ݻ籤 (�ټ��� �������� �ݻ��)
	Light.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.f); //�ֺ��� (Ư���� ������� �ֺ��� ���� �ִ� ��)
	Light.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f); //���ݻ籤 (�� �������θ� �ݻ�Ǵ� ��)

	m_D3DDevice->SetLight(0, &Light);
	m_D3DDevice->LightEnable(0, true);

	return true;
}

bool Renderer::Release()
{
	m_D3D->Release();
	m_D3DDevice->Release();

	return true;
}

bool Renderer::Begin()
{
	if (m_bWireFrame)
		m_D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	else
		m_D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	if (GetAsyncKeyState(VK_SPACE))
	{
		m_bWireFrame ^= true;
	}

	m_D3DDevice->BeginScene();
	m_D3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 125, 125), 1.f, 0.f);

	return true;
}

bool Renderer::End()
{
	m_D3DDevice->EndScene();
	m_D3DDevice->Present(NULL, NULL, NULL, NULL);

	return true;
}