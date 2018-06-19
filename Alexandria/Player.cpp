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

	printf("플레이어 업데이트!\n");
}

void Player::Render()
{
	GameObject::Render();
}
