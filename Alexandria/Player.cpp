#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	printf("�÷��̾� ������Ʈ!\n");
}

void Player::Render()
{
	GameObject::Render();
}
