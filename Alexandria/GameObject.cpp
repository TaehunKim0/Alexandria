#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject() :
	m_Transform(new Transform())
	, m_Device(Renderer::GetInstance()->GetDevice())
	, m_Parent(nullptr) , IsDestroyed(0) , m_UseBlending(0)
	, m_Layer(0)
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
	m_Transform->SetTransform(m_Device);
}
