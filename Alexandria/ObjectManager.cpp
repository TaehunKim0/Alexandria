#include "stdafx.h"
#include "ObjectManager.h"



ObjectManager::~ObjectManager()
{
	Release();
}

void ObjectManager::Release()
{
	//오브젝트 릴리즈
	for (auto iter = m_ObjectList.begin(); iter != m_ObjectList.end(); iter++)
	{
		delete (*iter);
	}
	m_ObjectList.clear();

	for (auto iter = m_CollisionList.begin(); iter != m_CollisionList.end(); iter++)
	{
		m_CollisionList.remove((*iter));
	}
	m_CollisionList.clear();
}

void ObjectManager::AddObject(GameObject * obj)
{
	if (obj)
		m_ObjectList.push_back(obj);
	else
		MessageBox(Application::GetInstance()->GetHandle(), L"오브젝트 추가 실패", L"Error", MB_OK);
}

void ObjectManager::AddCollisionObject(GameObject * obj)
{
	if (obj)
		m_CollisionList.push_back(obj);
	else
		MessageBox(Application::GetInstance()->GetHandle(), L"콜리젼 오브젝트 추가 실패", L"Error", MB_OK);
}

void ObjectManager::RemoveObject(GameObject * obj)
{
	obj->IsDestroyed = true;
}

void ObjectManager::RemoveCollisionObject(GameObject * obj)
{
	m_CollisionList.remove(obj);
}

void ObjectManager::Update(float deltaTime)
{
	for (auto iter = m_ObjectList.begin(); iter != m_ObjectList.end(); )
	{
		if ((*iter)->IsDestroyed == true)
		{
			GameObject* temp = (*iter);
			iter = m_ObjectList.erase(iter);
			m_CollisionList.remove(temp);
			delete temp;
		}
		else
			iter++;
	}

	for (auto iter = m_ObjectList.begin(); iter != m_ObjectList.end(); iter++)
	{
		(*iter)->Update(deltaTime);
	}
}

bool operator < (const GameObject& rhs1, const GameObject& rhs2) {
	return rhs1.m_UseBlending < rhs2.m_UseBlending;
}

void ObjectManager::Render()
{
	m_ObjectList.sort();

	for (auto iter = m_ObjectList.begin(); iter != m_ObjectList.end(); iter++)
	{
		(*iter)->Render();
	}
}