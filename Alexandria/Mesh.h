#pragma once
class Mesh
{
private:
	LPD3DXMESH m_Mesh;
	D3DMATERIAL9 * m_MeshMaterials;
	LPDIRECT3DTEXTURE9* m_MeshTextures;
	
	DWORD m_NumsMaterial;

private:
	explicit Mesh();
	~Mesh();

public:
	static Mesh* Create(std::wstring fileName, std::wstring Name);
	bool Init(std::wstring fileName, std::wstring Name);

public:
	void Update(float deltaTime);
	void Render();

public:
	inline LPD3DXMESH GetMesh() {
		return m_Mesh;
	}
};