#pragma once
class GameObject;
class Transform
{
private:
	D3DXMATRIX m_wMatrix;
	D3DXMATRIX m_ParentMat;

	GameObject* m_Parent;

	bool m_ParentMatUse;
private:
	D3DXMATRIX m_matScale;
	D3DXVECTOR3 m_Scale;

private:
	D3DXVECTOR3 m_Direction;

	D3DXMATRIX m_matRotation;
	D3DXMATRIX m_matRotX;
	D3DXMATRIX m_matRotY;
	D3DXMATRIX m_matRotZ;

	float m_fRotY;
	float m_fRotX;
	float m_fRotZ;

private:
	D3DXMATRIX m_matTranslation;
	D3DXVECTOR3 m_Position;

public:
	Transform();
	virtual ~Transform();

	void SetTransform(LPDIRECT3DDEVICE9 device);

public:
	inline void SetScale(D3DXVECTOR3 scale) {
		m_Scale = scale;
	}

	inline void SetWorldMatrix(D3DXMATRIX wMat) {
		m_wMatrix = wMat;
	}

	inline void SetPosition(float x, float y, float z) {
		m_Position.x = x;
		m_Position.y = y;
		m_Position.z = z;
	}
	inline void Translate(D3DXVECTOR3 mat) {
		m_Position += mat;
	}
	inline void Translate(float x, float y, float z) {
		m_Position.x += x;
		m_Position.y += y;
		m_Position.z += z;
	}
	inline void SetmatRotX(D3DXMATRIX rot) {
		m_matRotX = rot;
	}
	inline void SetmatRotY(D3DXMATRIX rot) {
		m_matRotY = rot;
	}
	inline void SetmatRotZ(D3DXMATRIX rot) {
		m_matRotZ = rot;
	}
	inline void SetRotationX(float angle) {
		m_fRotX += angle;
	}
	inline void SetRotationY(float angle) {
		m_fRotY += angle;
	}
	inline void SetRotationZ(float angle) {
		m_fRotZ += angle;
	}
	inline void SetParent(GameObject* obj) {
		//m_ParentMat = mat;
		m_Parent = obj;
		m_ParentMatUse = true;
	}
	inline void SetParentMatUse(bool use) {
			m_ParentMatUse = use;
	}
	inline void SetDirection(D3DXVECTOR3 direction) {
		m_Direction = direction;
	}
	inline void SetDirection(float x, float y, float z) {
		m_Direction.x = x;
		m_Direction.y = y;
		m_Direction.z = z;
	}

public:
	inline D3DXMATRIX GetTranslation() {
		return m_matTranslation;
	}
	inline D3DXVECTOR3 GetPosition() {
		return m_Position;
	}
	inline D3DXMATRIX GetWorldMat() {
		return m_wMatrix;
	}
	inline float GetRotY() {
		return m_fRotY;
	}
	inline float GetRotX() {
		return m_fRotX;
	}
	inline float GetRotZ() {
		return m_fRotZ;
	}
	inline D3DXVECTOR3 GetDirection() {
		return m_Direction;
	}

};

