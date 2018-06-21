#include "stdafx.h"
#include "ForestScene.h"
#include"Player.h"
#include"WindMill.h"
#include"Terrain.h"

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

	windMill = new WindMill();
	windMill->Init();
	ObjectManager::GetInstance()->AddObject(windMill);

	terrain = new Terrain();
	terrain->Init();
	ObjectManager::GetInstance()->AddObject(terrain);
}

void ForestScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
	Camera::GetInstance()->Update(deltaTime);
}

void ForestScene::Render()
{
	Scene::Render();
}