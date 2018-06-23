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

	m_WingTrans->SetParent(this);
}

void WindMill::Move()
{
	D3DXVec3TransformNormal(&Dir, &m_Transform->GetDirection(), &m_Transform->GetRotY());
	D3DXVec3Normalize(&Dir, &Dir);


	if (Input::GetInstance()->GetKeyState(VK_RIGHT) == KeyState::Pressed)
	{
		m_Transform->SetRotationY(0.1f);
	}
	if (Input::GetInstance()->GetKeyState(VK_LEFT) == KeyState::Pressed)
	{
		m_Transform->SetRotationY(-0.1f);
	}
	if (Input::GetInstance()->GetKeyState(VK_UP) == KeyState::Pressed)
	{
		Translate(Dir.x, Dir.y, Dir.z);
	}
	if (Input::GetInstance()->GetKeyState(VK_DOWN) == KeyState::Pressed)
	{
		Translate(-Dir.x, -Dir.y, -Dir.z);
	}
}

void WindMill::ShootWing()
{
	m_WingTrans->SetParentMatUse(false);
	mTemp = m_Transform->GetRotY();
	m_WingTrans->SetWorldMatrix(m_Transform->GetWorldMat());
	m_WingTrans->SetDirection(Dir);

	m_TempPosition = m_WingTrans->GetPosition();

	m_bShoot = true;
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

	if (Input::GetInstance()->GetKeyState('1') == KeyState::Up)
	{
		if(m_bShoot == false)
			ShootWing();
	}

	if (m_bShoot)
	{
		m_WingTrans->SetmatRotY(mTemp);
		m_WingTrans->Translate(m_WingTrans->GetDirection());

		printf("%f %f %f\n", m_WingTrans->GetPosition().x, m_WingTrans->GetPosition().y, m_WingTrans->GetPosition().z);

		printf("Direction : %f \n", m_TempPosition.z + m_WingTrans->GetDirection().z * 100);

		if (m_WingTrans->GetPosition() < m_TempPosition + m_WingTrans->GetDirection() * 100)
		{
			m_bShoot = false;
		}
	}
}

void WindMill::Render()
{
	GameObject::Render();

	m_WingTrans->SetTransform(GetDevice());
	m_WindMillWingBuffer->Render();

	m_Transform->SetTransform(GetDevice());
	m_WindMillBodyBuffer->Render();
}