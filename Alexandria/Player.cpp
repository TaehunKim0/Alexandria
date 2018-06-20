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

	printf("플레이어 업데이트!\n");
}

void Player::Render()
{
	GameObject::Render();

	m_Mesh->Render();
}
