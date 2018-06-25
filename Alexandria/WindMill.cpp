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

TEXVERTEX WindMillWing[] =
{
	{ D3DXVECTOR3(-0.5f, 2.f ,0.f), D3DXVECTOR3(0.f,0.f,0.f),D3DXVECTOR2(0.57f,0.98f) }, //0
	{ D3DXVECTOR3(0.5f, 2.f ,0.f), D3DXVECTOR3(0.f,0.f,0.f), D3DXVECTOR2(0.72f,0.98f) }, //1
	{ D3DXVECTOR3(2.f, 0.5f ,0.f), D3DXVECTOR3(0.f,0.f,0.f), D3DXVECTOR2(0.57f,0.98f) }, //2
	{ D3DXVECTOR3(2.f, -0.5f ,0.f), D3DXVECTOR3(0.f,0.f,0.f),D3DXVECTOR2(0.72f,0.98f) }, //3

	{ D3DXVECTOR3(0.5f, -2.f , 0.f), D3DXVECTOR3(0.f,0.f,0.f),  D3DXVECTOR2(0.72f,0.98f) }, //4
	{ D3DXVECTOR3(-0.5f, -2.f , 0.f), D3DXVECTOR3(0.f,0.f,0.f), D3DXVECTOR2(0.57f,0.98f) }, // 5
	{ D3DXVECTOR3(-2.f, 0.5f , 0.f), D3DXVECTOR3(0.f,0.f,0.f),  D3DXVECTOR2(0.57f,0.98f) },
	{ D3DXVECTOR3(-2.f, -0.5f, 0.f), D3DXVECTOR3(0.f,0.f,0.f),  D3DXVECTOR2(0.72f,0.98f) },

	{ D3DXVECTOR3(0.f, -0.5f, 0.f), D3DXVECTOR3(0.f,0.f,0.f),  D3DXVECTOR2(0.72f,0.47f) },
	{ D3DXVECTOR3(0.f, 0.5f, 0.f), D3DXVECTOR3(0.f,0.f,0.f),   D3DXVECTOR2(0.57f,0.47f) },

	{ D3DXVECTOR3(-0.5f, 0.f, 0.f), D3DXVECTOR3(0.f,0.f,0.f), D3DXVECTOR2(0.57f,0.47f) },
	{ D3DXVECTOR3(0.5f, 0.f, 0.f), D3DXVECTOR3(0.f,0.f,0.f),  D3DXVECTOR2(0.72f,0.47f) }
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
	m_WindMillBodyBuffer->CreateTexture(L"./Resource/windmill_512.png");

	m_WindMillWingBuffer = new BufferManager();
	m_WindMillWingBuffer->CreateTexture(L"./Resource/windmill_512.png");

	SetWindMillVertex();
	SetWindMillIndex();

	m_WingTrans->SetParent(this);
}

void WindMill::Move()
{
	D3DXMATRIX rotY;
	D3DXMatrixRotationY(&rotY, m_Transform->GetRotY());
	D3DXVec3TransformNormal(&Dir, &m_Transform->GetDirection(), &rotY);

	if (Input::GetInstance()->GetKeyState(VK_RIGHT) == KeyState::Pressed)
	{
		m_Transform->SetRotationY(0.1f);
	}
	if (Input::GetInstance()->GetKeyState(VK_LEFT) == KeyState::Pressed)
	{
		m_Transform->SetRotationY(-0.1f);
	}
	if (Input::GetInstance()->GetKeyState(VK_DOWN) == KeyState::Pressed)
	{
		Translate(Dir.x, Dir.y, Dir.z);
	}
	if (Input::GetInstance()->GetKeyState(VK_UP) == KeyState::Pressed)
	{
		Translate(-Dir.x, -Dir.y, -Dir.z);
		//m_pMesh->Set_AnimationSet(54);

	}
}

void WindMill::ShootWing()
{
	m_WingTrans->SetParentMatUse(false);
	m_WingTrans->SetRotationY(m_Transform->GetRotY());
	m_WingTrans->SetPosition(m_Transform->GetPosition().x, m_Transform->GetPosition().y, m_Transform->GetPosition().z);

	mTemp = m_Transform->GetRotY() * m_Transform->GetTranslation();

	D3DXMATRIX rotY;
	D3DXMatrixRotationY(&rotY, m_Transform->GetRotY());

	m_WingTrans->SetmatRotY(rotY);

	D3DXVec3TransformNormal(&mDirTemp, &m_Transform->GetDirection(), &rotY);
	D3DXVec3Normalize(&mDirTemp, &mDirTemp);

	m_WingTrans->SetDirection(mDirTemp);
	m_WingTrans->SetWorldMatrix(mTemp);

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

	m_WindMillWingBuffer->CreateVertexBuffer(12, sizeof(TEXVERTEX), TexVertexFVF, 8);

	TEXVERTEX* wvertex = nullptr;
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
	m_WindMillWingBuffer->CreateIndexBuffer(8, sizeof(INDEX));

	INDEX* windex = nullptr;

	m_WindMillWingBuffer->GetIB()->Lock(0, 0, (VOID**)&windex, 0);
	windex[0]._1 = 0;
	windex[0]._2 = 1;
	windex[0]._3 = 11;

	windex[1]._1 = 0;
	windex[1]._2 = 11;
	windex[1]._3 = 10;

	windex[2]._1 = 10;
	windex[2]._2 = 11;
	windex[2]._3 = 4;

	windex[3]._1 = 10;
	windex[3]._2 = 4;
	windex[3]._3 = 5;

	windex[4]._1 = 7;
	windex[4]._2 = 8;
	windex[4]._3 = 6;

	windex[5]._1 = 6;
	windex[5]._2 = 8;
	windex[5]._3 = 9;

	windex[6]._1 = 9;
	windex[6]._2 = 2;
	windex[6]._3 = 3;

	windex[7]._1 = 8;
	windex[7]._2 = 3;
	windex[7]._3 = 9;


	m_WindMillWingBuffer->GetIB()->Unlock();
}
void WindMill::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
	Move();

	if (Input::GetInstance()->GetKeyState('1') == KeyState::Up)
	{
		if (m_bShoot == false)
		{
			ShootWing();
		}
	}

	if (m_bShoot)
	{
		if (m_bReturn == false)
		{
			m_WingTrans->Translate(m_WingTrans->GetDirection());
			m_fDistance += D3DXVec3Length(&m_WingTrans->GetDirection());
		}

		if (m_fDistance > 30)
		{
			m_bReturn = true;
		}

		if (m_bReturn)
		{
			reDir = m_Transform->GetPosition() - m_WingTrans->GetPosition();
			D3DXVec3Normalize(&reDir, &reDir);

			m_WingTrans->Translate(reDir);

			if (D3DXVec3Length(&D3DXVECTOR3(m_Transform->GetPosition() - m_WingTrans->GetPosition())) < 2)
			{
				m_WingTrans->SetParentMatUse(true);
				m_bShoot = false;
				m_bReturn = false;

				m_WingTrans->SetPosition(0.f, 3.f, -2.f);
				m_WingTrans->SetRotationY(0.f);
			}
		}

	}

}

void WindMill::Render()
{
	GameObject::Render();
	m_WindMillBodyBuffer->Render();

	m_WingTrans->SetTransform(GetDevice());
	m_WindMillWingBuffer->Render();
}