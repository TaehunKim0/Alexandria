#include "stdafx.h"
#include "Scene.h"


Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::Update(float deltaTime)
{
	Camera::GetInstance()->Update(deltaTime);
	ObjectManager::GetInstance()->Update(deltaTime);
}

void Scene::Render()
{
	ObjectManager::GetInstance()->Render();
}
