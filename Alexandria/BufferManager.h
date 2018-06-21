#pragma once
class BufferManager
{
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DINDEXBUFFER9 m_pIB;
	LPDIRECT3DTEXTURE9 m_Texture;
	D3DMATERIAL9 m_Mtrl;

public:
	VERTEX * vertex;
	INDEX * index;


public:
	int m_iVertex;
	UINT m_uSize;
	DWORD m_dFVF;
	int m_iTriangleNum;
	bool m_bUseMtrl;

public:
	BufferManager();
	~BufferManager();

	void Release();

public:
	void CreateTexture(std::wstring fileName);
	void CreateVertexBuffer(int vertexs, UINT size, DWORD FVF , int trianglenum);
	void CreateIndexBuffer(int vertexs, UINT size);
	void SetMaterial(D3DXCOLOR ambient, D3DXCOLOR diffuse, D3DXCOLOR specular, float power);

public:
	void VertexLock(TEXVERTEX* vertex);
	void VertexLock(VERTEX* vertex);
	void VertexUnLock();

public:
	void IndexLock(INDEX* index);
	void IndexUnLock();

public:
	void Render();

	inline LPDIRECT3DVERTEXBUFFER9 GetVB() {
		return m_pVB;
	}
	inline LPDIRECT3DINDEXBUFFER9 GetIB() {
		return m_pIB;
	}
	inline D3DMATERIAL9 GetMtrl() {
		return m_Mtrl;
	}
	inline void UseMtrl(bool use) {
		m_bUseMtrl = use;
	}

};