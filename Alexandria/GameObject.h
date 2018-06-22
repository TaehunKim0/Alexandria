#pragma once

class GameObject
{
private:
	LPDIRECT3DDEVICE9 m_Device;

public:
	GameObject * m_Parent;
	std::string m_Name;

	Transform * m_Transform;

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
		m_Transform->SetPosition(x, y, z);
	}
	inline void Translate(float x, float y, float z) {
		m_Transform->Translate(x, y, z);
	}
	inline void SetRotationX(float angle) {
		m_Transform->SetRotationX(angle);
	}
	inline void SetRotationY(float angle) {
		m_Transform->SetRotationY(angle);
	}
	inline void SetRotationZ(float angle) {
		m_Transform->SetRotationZ(angle);
	}
	inline Transform* GetTransform() {
		return m_Transform;
	}
	inline LPDIRECT3DDEVICE9 GetDevice() {
		return m_Device;
	}

};