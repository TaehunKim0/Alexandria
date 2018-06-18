#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject() :
	m_Transform(new Transform())
	, m_Device(Renderer::GetInstance()->GetDevice())
{
}

GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::Render()
{
}
