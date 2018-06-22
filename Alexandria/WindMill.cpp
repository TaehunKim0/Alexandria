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
	m_WingTrans = new Transform();
	m_WingTrans->SetPosition(0.f, 3.f, -2.f);

	m_WindMillBodyBuffer = new BufferManager();
	m_WindMillBodyBuffer->CreateTexture(L"./Resource/windmill_512.jpg");

	m_WindMillWingBuffer = new BufferManager();

	SetWindMillVertex();
	SetWindMillIndex();
}

void WindMill::Move()
{
	if (Input::GetInstance()->GetKeyState(VK_RIGHT) == KeyState::Pressed)
	{
		Translate(1.f, 0.f, 0.f);
	}
	if (Input::GetInstance()->GetKeyState(VK_LEFT) == KeyState::Pressed)
	{
		Translate(-1.f, 0.f, 0.f);
	}
	if (Input::GetInstance()->GetKeyState(VK_UP) == KeyState::Pressed)
	{
		Translate(0.f, 0.f, 1.f);
	}
	if (Input::GetInstance()->GetKeyState(VK_DOWN) == KeyState::Pressed)
	{
		Translate(0.f, 0.f, -1.f);
	}
}

void WindMill::ShootWing()
{
	D3DXVECTOR3 vDir(0, 0, -1);
	D3DXVec3TransformNormal(&vDir, &vDir, &m_WingTrans->GetRotY());
	D3DXVec3Normalize(&vDir, &vDir);



}

void WindMill::SetWindMillVertex()
{
	m_WindMillBodyBuffer->CreateVertexBuffer(5, sizeof(TEXVERTEX), TexVertexFVF, 4);

	TEXVERTEX* vertex = nullptr;
	m_WindMillBodyBuffer->GetVB()->Lock(0, 0, (VOID**)&vertex, 0);

	memcpy(vertex, WindMillBody, sizeof(WindMillBody));

	m_WindMillBodyBuffer->GetVB()->Unlock();

	//

	m_WindMillWingBuffer->CreateVertexBuffer(9, sizeof(VERTEX), VertexFVF, 4);

	VERTEX* wvertex = nullptr;
	m_WindMillWingBuffer->GetVB()->Lock(0, 0, (VOID**)&wvertex, 0);

	memcpy(wvertex, WindMillWing, sizeof(WindMillWing));

	m_WindMillWingBuffer->GetVB()->Unlock();
}

void WindMill::SetWindMillIndex()
{
	m_WindMillBodyBuffer->CreateIndexBuffer(4, sizeof(INDEX));

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

	//
	m_WindMillWingBuffer->CreateIndexBuffer(4, sizeof(INDEX));

	INDEX* windex = nullptr;

	m_WindMillWingBuffer->GetIB()->Lock(0, 0, (VOID**)&windex, 0);
	windex[0]._1 = 0;
	windex[0]._2 = 1;
	windex[0]._3 = 8;

	windex[1]._1 = 2;
	windex[1]._2 = 3;
	windex[1]._3 = 8;

	windex[2]._1 = 8;
	windex[2]._2 = 4;
	windex[2]._3 = 5;

	windex[3]._1 = 7;
	windex[3]._2 = 8;
	windex[3]._3 = 6;

	m_WindMillWingBuffer->GetIB()->Unlock();
}

void WindMill::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
	Move();

	if (Input::GetInstance()->GetKeyState(VK_SPACE) == KeyState::Up)
	{
		ShootWing();
	}

}

void WindMill::Render()
{
	GameObject::Render();
	m_WindMillBodyBuffer->Render();

	m_WingTrans->SetParent(m_Transform->GetWorldMat());
	m_WingTrans->SetTransform(GetDevice());

	m_WindMillWingBuffer->Render();
}
