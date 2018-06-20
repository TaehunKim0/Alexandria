#pragma once
class Transform
{
public:
	D3DXMATRIX m_wMatrix;

public:
	D3DXMATRIX m_matScale;
	D3DXVECTOR3 m_Scale;

public:
	D3DXMATRIX m_matRotation;
	D3DXMATRIX m_matRotX;
	D3DXMATRIX m_matRotY;
	D3DXMATRIX m_matRotZ;

	float m_fRotY;
	float m_fRotX;
	float m_fRotZ;

public:
	D3DXMATRIX m_matTranslation;
	D3DXVECTOR3 m_Position;

public:
	Transform();
	virtual ~Transform();


	void SetTransform(LPDIRECT3DDEVICE9 device);
};

