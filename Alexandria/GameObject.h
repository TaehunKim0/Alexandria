#pragma once

class GameObject
{
private:
	Transform * m_Transform;
	LPDIRECT3DDEVICE9 m_Device;

public:
	GameObject * m_Parent;
	std::string m_Name;

	bool IsDestroyed;

public:
	GameObject();
	virtual ~GameObject();

public:
	virtual void Update(float deltaTime);
	virtual void Render();
};