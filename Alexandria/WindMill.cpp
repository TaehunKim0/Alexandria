#include "stdafx.h"
#include "WindMill.h"

TEXVERTEX WindMillBody[] =
{
	{ D3DXVECTOR3(0.f,5.f,0.f),   D3DXVECTOR3(0.f,1.f,0.f),    D3DXVECTOR2(0.25f,0.f) },
	{ D3DXVECTOR3(2.f,0.f,-2.f),  D3DXVECTOR3(0.f,0.f,1.f),    D3DXVECTOR2(0.5f,1.f) },
	{ D3DXVECTOR3(-2.f,0.f,-2.f), D3DXVECTOR3(0.f,0.f,1.f),    D3DXVECTOR2(0.f,1.f) },
	{ D3DXVECTOR3(-2.f,0.f,2.f),  D3DXVECTOR3(0.f,0.f,-1.f),   D3DXVECTOR2(0.5f,1.f) },
	{ D3DXVECTOR3(2.f,0.f,2.f),   D3DXVECTOR3(0.f,0.f,-1.f),   D3DXVECTOR2(0.f,1.f) },

};

VERTEX WindMillWing[] =
{
	{ D3DXVECTOR3(-0.5f, 1.f ,0.f), D3DXVECTOR3(0.f,0.f,0.f), D3DXCOLOR(1.f,1.f,1.f,1.f) },
	{ D3DXVECTOR3(0.5f, 1.f ,0.f), D3DXVECTOR3(0.f,0.f,0.f), D3DXCOLOR(1.f,1.f,1.f,1.f) },
	{ D3DXVECTOR3(1.f, 0.5f ,0.f), D3DXVECTOR3(0.f,0.f,0.f), D3DXCOLOR(1.f,1.f,1.f,1.f) },
	{ D3DXVECTOR3(1.f, -0.5f ,0.f), D3DXVECTOR3(0.f,0.f,0.f), D3DXCOLOR(1.f,1.f,1.f,1.f) },

	{ D3DXVECTOR3(0.5f, -1.f , 0.f), D3DXVECTOR3(0.f,0.f,0.f), D3DXCOLOR(1.f,1.f,1.f,1.f) },
	{ D3DXVECTOR3(-0.5f, -1.f , 0.f), D3DXVECTOR3(0.f,0.f,0.f), D3DXCOLOR(1.f,1.f,1.f,1.f) },
	{ D3DXVECTOR3(-1.f, -0.5f , 0.f), D3DXVECTOR3(0.f,0.f,0.f), D3DXCOLOR(1.f,1.f,1.f,1.f) },
	{ D3DXVECTOR3(-1.f, 0.5f, 0.f), D3DXVECTOR3(0.f,0.f,0.f), D3DXCOLOR(1.f,1.f,1.f,1.f) },

	{ D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR3(0.f,0.f,0.f), D3DXCOLOR(1.f,1.f,1.f,1.f) }
};



WindMill::WindMill()
{
}


WindMill::~WindMill()
{
	m_WindMillBodyBuffer->Release();
}

void WindMill::Init()
{
	m_WindMillBodyBuffer = new BufferManager();
	m_WindMillBodyBuffer->CreateTexture(L"./Resource/windmill_512.jpg");

	SetWindMillVertex();
	SetWindMillIndex();
}

void WindMill::SetWindMillVertex()
{
	m_WindMillBodyBuffer->SetVertexBuffer(5, sizeof(TEXVERTEX), TexVertexFVF, 4);

	TEXVERTEX* vertex = nullptr;
	m_WindMillBodyBuffer->GetVB()->Lock(0, 0, (VOID**)&vertex, 0);

	memcpy(vertex, WindMillBody, sizeof(WindMillBody));

	m_WindMillBodyBuffer->GetVB()->Unlock();
}

void WindMill::SetWindMillIndex()
{
	m_WindMillBodyBuffer->SetIndexBuffer(4, sizeof(INDEX));

	INDEX* index = nullptr;

	m_WindMillBodyBuffer->GetIB()->Lock(0, 0, (void**)&index, 0);
	index[0]._1 = 0;
	index[0]._2 = 1;
	index[0]._3 = 2;

	index[1]._1 = 0;
	index[1]._2 = 2;
	index[1]._3 = 3;

	index[2]._1 = 0;
	index[2]._2 = 3;
	index[2]._3 = 4;

	index[3]._1 = 0;
	index[3]._2 = 4;
	index[3]._3 = 1;
	m_WindMillBodyBuffer->GetIB()->Unlock();
}

void WindMill::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
}

void WindMill::Render()
{
	GameObject::Render();

	m_WindMillBodyBuffer->Render();

}
