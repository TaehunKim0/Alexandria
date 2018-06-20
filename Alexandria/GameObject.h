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
	bool m_UseBlending;

	int m_Layer;

public:
	GameObject();
	virtual ~GameObject();

public:
	virtual void Update(float deltaTime);
	virtual void Render();

public:
	inline void SetPosition(float x, float y, float z) {
		m_Transform->m_Position.x = x;
		m_Transform->m_Position.y = y;
		m_Transform->m_Position.z = z;
	}
	inline void Translate(float x, float y, float z) {
		m_Transform->m_Position.x += x;
		m_Transform->m_Position.y += y;
		m_Transform->m_Position.z += z;
	}
	inline void SetRotationX(float angle) {
		m_Transform->m_fRotX += angle;
	}
	inline void SetRotationY(float angle) {
		m_Transform->m_fRotY += angle;
	}
	inline void SetRotationZ(float angle) {
		m_Transform->m_fRotZ += angle;
	}
	inline Transform* GetTransform() {
		return m_Transform;
	}

};