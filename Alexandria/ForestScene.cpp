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


	terrain = new Terrain();
	terrain->Init();
	ObjectManager::GetInstance()->AddObject(terrain);

	windMill = new WindMill();
	windMill->Init();
	ObjectManager::GetInstance()->AddObject(windMill);

	//m_PointLight1 = new PointLight();
	//m_PointLight1->Init(D3DXCOLOR(255.f, 0.f, 0.f, 0.f), 1.f, 10000);

	//m_PointLight1->SetPosition(D3DXVECTOR3(0.f, 0.f, 0.f));
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