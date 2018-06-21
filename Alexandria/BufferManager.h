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

public:
	BufferManager();
	~BufferManager();

	void Release();

public:
	void CreateTexture(std::wstring fileName);
	void SetVertexBuffer(int vertexs, UINT size, DWORD FVF , int trianglenum);
	void SetIndexBuffer(int vertexs, UINT size);

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

};