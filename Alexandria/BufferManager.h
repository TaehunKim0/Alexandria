#pragma once
class BufferManager
{
public:
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DINDEXBUFFER9 m_pIB;


public:
	BufferManager();
	~BufferManager();

	void CreateTexture(std::wstring fileName, LPDIRECT3DTEXTURE9 pTexture);


};

