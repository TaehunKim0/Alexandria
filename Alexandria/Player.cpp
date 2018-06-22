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


}

void Player::Render()
{
	GameObject::Render();

	m_Mesh->Render();
}
