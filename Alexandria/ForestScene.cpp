#include "stdafx.h"
#include "ForestScene.h"
#include"Player.h"

ForestScene::ForestScene()
{
}


ForestScene::~ForestScene()
{
}

void ForestScene::Init()
{
	player = new Player();
	player->Init();
	ObjectManager::GetInstance()->AddObject(player);
}

void ForestScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void ForestScene::Render()
{
	Scene::Render();
}