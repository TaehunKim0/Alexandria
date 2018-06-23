#pragma once
class Renderer : public Singleton<Renderer>
{
public:
	LPDIRECT3D9 m_D3D;
	LPDIRECT3DDEVICE9 m_D3DDevice;
	LPD3DXSPRITE m_Sprite;
	D3DLIGHT9 Light;

	int m_iLightChannel;

	bool m_bWireFrame;

public:
	Renderer();
	virtual ~Renderer();

public:
	bool Init();
	bool Release();

	bool Begin();
	bool End();

public:
	void SetLights(D3DLIGHT9* light);

	inline LPDIRECT3D9 GetD3D() {
		return m_D3D;
	}
	inline LPDIRECT3DDEVICE9 GetDevice() {
		return m_D3DDevice;
	}
};

