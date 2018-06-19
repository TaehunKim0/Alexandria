#include "stdafx.h"
#include "SceneManager.h"


SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void SceneManager::SetScene(Scene * scene)
{
	if (scene)
	{
		if (m_CurrentScene != nullptr)
		{
			SafeDelete(m_CurrentScene);
		}

		m_CurrentScene = scene;
	}
}

void SceneManager::Update(float deltaTime)
{
	m_CurrentScene->Update(deltaTime);
}

void SceneManager::Render()
{
	m_CurrentScene->Render();
}
