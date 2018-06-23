#include "stdafx.h"
#include "ForestScene.h"
#include"Player.h"
#include"WindMill.h"
#include"Terrain.h"
#include"PointLight.h"

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
	terrain->m_UseBlending = 1;
	ObjectManager::GetInstance()->AddObject(terrain);

	m_PointLight1 = new PointLight();
	m_PointLight1->Init(D3DXCOLOR(255.f, 0.f, 0.f, 0.f), 1.f, 10000);
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