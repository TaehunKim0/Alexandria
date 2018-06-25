#include "stdafx.h"
#include "Player.h"
#include"Dynamic_Mesh.h"

Player::Player()
{
}


Player::~Player()
{
}

void Player::Init()
{
	m_Mesh = Mesh::Create(L"./Resource/Mesh/", L"TombStone.x");

	m_pMesh = new Dynamic_Mesh(GetDevice());

	m_pMesh->Init_Dynamic_Mesh(L"./Resource/Mesh/Player/", L"Player.x");
	m_Transform->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
}

void Player::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	m_pMesh->Play_AnimationSet(deltaTime);

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
		m_pMesh->Set_AnimationSet(54);

	}
}

void Player::Render()
{
	GameObject::Render();

	//m_Mesh->Render();

	m_pMesh->Render_Mesh();
}
