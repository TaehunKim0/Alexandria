#pragma once
class Transform
{
private:
	D3DXMATRIX m_wMatrix;
	D3DXMATRIX m_ParentMat;

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
	inline void SetPosition(float x, float y, float z) {
		m_Position.x = x;
		m_Position.y = y;
		m_Position.z = z;
	}
	inline void Translate(float x, float y, float z) {
		m_Position.x += x;
		m_Position.y += y;
		m_Position.z += z;
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
	inline void SetParent(D3DXMATRIX mat) {
		m_ParentMat = mat;
		m_ParentMatUse = true;
	}
	inline void SetParentMatUse(bool use) {
		if (m_ParentMat != 0)
			m_ParentMatUse = false;
	}
	inline void SetDirection(float x, float y, float z) {
		m_Direction.x = x;
		m_Direction.y = y;
		m_Direction.z = z;
	}

public:
	inline D3DXVECTOR3 GetPosition() {
		return m_Position;
	}
	inline D3DXMATRIX GetWorldMat() {
		return m_wMatrix;
	}
	inline D3DXMATRIX GetRotY() {
		return m_matRotY;
	}
	inline D3DXMATRIX GetRotX() {
		return m_matRotX;
	}
	inline D3DXMATRIX GetRotZ() {
		return m_matRotZ;
	}
	inline D3DXVECTOR3 GetDirection() {
		return m_Direction;
	}

};

