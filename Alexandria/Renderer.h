#pragma once
class Renderer : public Singleton<Renderer>
{
public:
	LPDIRECT3D9 m_D3D;
	LPDIRECT3DDEVICE9 m_D3DDevice;
	LPD3DXSPRITE m_Sprite;

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
	inline LPDIRECT3D9 GetD3D() {
		return m_D3D;
	}
	inline LPDIRECT3DDEVICE9 GetDevice() {
		return m_D3DDevice;
	}
};

