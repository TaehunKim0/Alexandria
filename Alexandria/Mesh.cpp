#include "stdafx.h"
#include "Mesh.h"


Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

Mesh * Mesh::Create(std::wstring fileName, std::wstring Name)
{
	Mesh* mesh = new (std::nothrow) Mesh();
	if (mesh && mesh->Init(fileName, Name))
	{
		return mesh;
	}

	SafeDelete(mesh);
	return nullptr;
}

bool Mesh::Init(std::wstring fileName, std::wstring Name)
{
	LPD3DXBUFFER mtrBuffer;
	std::wstring bf;

	bf = fileName + Name;

	if (FAILED(D3DXLoadMeshFromX(bf.c_str(), D3DXMESH_SYSTEMMEM,
		Renderer::GetInstance()->GetDevice(), NULL, &mtrBuffer, NULL, &m_NumsMaterial, &m_Mesh)))
	{
		MessageBox(NULL, L"X File None", L"3DWorld.exe", MB_OK);
		return false;
	}

	//재질정보와 텍스쳐 정보 따로 뽑아낸다.
	D3DXMATERIAL* d3dMaterials = (D3DXMATERIAL*)mtrBuffer->GetBufferPointer();

	m_MeshMaterials = new D3DMATERIAL9[m_NumsMaterial]; //재질 개수 만큼 재질구조체 배열 생성
	m_MeshTextures = new LPDIRECT3DTEXTURE9[m_NumsMaterial]; //재질 개수 만큼 텍스쳐 배열 생성

	D3DVERTEXELEMENT9 dcl[65];

	ZeroMemory(dcl, sizeof(D3DVERTEXELEMENT9) * 65);

	m_Mesh->GetDeclaration(dcl);

	for (DWORD i = 0; i < m_NumsMaterial; i++)
	{
		//재질정보를 복사
		m_MeshMaterials[i] = d3dMaterials[i].MatD3D;

		//주변 광원정보를 Diffuse 정보로
		m_MeshMaterials[i].Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 0.f);
		m_MeshMaterials[i].Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		m_MeshMaterials[i].Diffuse.a = 0.f;

		m_MeshMaterials[i].Power = 20;
		m_MeshTextures[i] = NULL;

		bf = fileName;

		std::string mycstr(bf.begin(), bf.end());

		if (d3dMaterials[i].pTextureFilename != NULL)
		{
			mycstr += d3dMaterials[i].pTextureFilename;

			//텍스쳐를 파일에서 로드한다.
			if (FAILED(D3DXCreateTextureFromFileA(Renderer::GetInstance()->GetDevice(), mycstr.c_str(), &m_MeshTextures[i])))
			{
				MessageBox(NULL, L"Texture is None", L"3DWorld.exe", MB_OK);
				return false;
			}

			/*	if (FAILED(D3DXCreateTextureFromFileEx(D3DRenderer::GetInstance()->GetDevice(), (d3dMaterials[i].pTextureFilename),
			D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
			1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
			D3DX_DEFAULT, D3DX_DEFAULT, NULL, NULL, NULL,
			&m_MeshTextures[i])))
			{
			MessageBox(NULL, "Texture is None", "3DWorld.exe", MB_OK);
			return false;
			}*/
		}
	}

	mtrBuffer->Release();

	return true;
}

void Mesh::Update(float deltaTime)
{
}

void Mesh::Render()
{
	for (DWORD i = 0; i < m_NumsMaterial; i++)
	{
		Renderer::GetInstance()->GetDevice()->SetMaterial(&m_MeshMaterials[i]);
		Renderer::GetInstance()->GetDevice()->SetTexture(0, m_MeshTextures[i]);

		m_Mesh->DrawSubset(i);
	}

	Renderer::GetInstance()->GetDevice()->SetTexture(0, nullptr);
}
