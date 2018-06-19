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
	ObjectManager::GetInstance()->AddObject(player);
}

void ForestScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);

	printf("씬 업데이트 중!!\n");
}

void ForestScene::Render()
{
	Scene::Render();
}
