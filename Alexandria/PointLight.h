#pragma once
class PointLight
{
	D3DLIGHT9 m_Light;

public:
	PointLight();
	~PointLight();

	void Init(D3DXCOLOR Diffuse, float Attenuation, float Range);

	inline void SetPosition(D3DXVECTOR3 vec) {
		m_Light.Position = vec;
	}

	inline D3DLIGHT9 GetLight() {
		return m_Light;
	}
	inline D3DXVECTOR3 GetPosition() {
		return m_Light.Position;
	}


};

