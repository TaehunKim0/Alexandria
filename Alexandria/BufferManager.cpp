#include "stdafx.h"
#include "BufferManager.h"


BufferManager::BufferManager()
	: m_dFVF(0)
	, m_iVertex(0)
	, m_uSize(0)
	, m_iTriangleNum(0)
	, m_bUseMtrl(false)
{
	m_Texture = nullptr;

	ZeroMemory(&m_Mtrl, sizeof(D3DMATERIAL9));
	m_Mtrl.Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	m_Mtrl.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	m_Mtrl.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	m_Mtrl.Power = 3;
}


BufferManager::~BufferManager()
{
}

void BufferManager::Release()
{
	m_pVB->Release();
	m_pIB->Release();
}

void BufferManager::CreateTexture(std::wstring fileName)
{
	if (FAILED(D3DXCreateTextureFromFile(Renderer::GetInstance()->GetDevice(), fileName.c_str(), &m_Texture)))
	{
		printf("텍스쳐 생성 실패\n");
	}
}

void BufferManager::CreateVertexBuffer(int vertexs, UINT size, DWORD FVF , int trianglenum)
{
	m_iVertex = vertexs;
	m_uSize = size;
	m_dFVF = FVF;
	m_iTriangleNum = trianglenum;

	if (FAILED(Renderer::GetInstance()->GetDevice()->CreateVertexBuffer(vertexs * size, 0, FVF, D3DPOOL_MANAGED, &m_pVB, nullptr)))
	{
		printf("버텍스 버퍼 생성 실패\n");
	}
}

void BufferManager::CreateIndexBuffer(int vertexs, UINT size)
{
	if (FAILED(Renderer::GetInstance()->GetDevice()->CreateIndexBuffer(vertexs * size , 0, D3DFMT_INDEX32, D3DPOOL_MANAGED, &m_pIB, nullptr)))
	{
		printf("인덱스 버퍼 생성 실패\n");
	}
}

void BufferManager::SetMaterial(D3DXCOLOR ambient, D3DXCOLOR diffuse, D3DXCOLOR specular, float power)
{
	m_Mtrl.Ambient = ambient;
	m_Mtrl.Diffuse = diffuse;
	m_Mtrl.Specular = specular;
	m_Mtrl.Power = power;
}

void BufferManager::VertexLock(VERTEX * vertex)
{
	m_pVB->Lock(0, 0, (VOID**)&vertex, 0);
}

void BufferManager::VertexLock(TEXVERTEX * vertex)
{
	m_pVB->Lock(0, 0, (VOID**)&vertex, 0);
}

void BufferManager::VertexUnLock()
{
	m_pVB->Unlock();
}

void BufferManager::IndexLock(INDEX * index)
{
	m_pIB->Lock(0, 0, (void**)&index, 0);
}

void BufferManager::IndexUnLock()
{
	m_pIB->Unlock();
}

void BufferManager::Render()
{
	if (m_bUseMtrl)
		Renderer::GetInstance()->GetDevice()->SetMaterial(&m_Mtrl);

	Renderer::GetInstance()->GetDevice()->SetTexture(0, m_Texture);
	Renderer::GetInstance()->GetDevice()->SetIndices(m_pIB);
	Renderer::GetInstance()->GetDevice()->SetFVF(m_dFVF);
	Renderer::GetInstance()->GetDevice()->SetStreamSource(0, m_pVB, 0, m_uSize);
	Renderer::GetInstance()->GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iVertex, 0, m_iTriangleNum);
}