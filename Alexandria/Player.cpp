#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::Init()
{
	m_Mesh = Mesh::Create(L"./Resource/Mesh/", L"TombStone.x");
}

void Player::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

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

void Player::Render()
{
	GameObject::Render();

	m_Mesh->Render();
}
