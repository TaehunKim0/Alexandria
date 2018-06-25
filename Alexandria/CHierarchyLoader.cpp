#include "stdafx.h"
#include "CHierarchyLoader.h"

CHierarchyLoader::CHierarchyLoader(LPDIRECT3DDEVICE9 pGraphicDev, const wchar_t* pFilePath)
	: m_pGraphicDev(pGraphicDev)
	, m_pFilePath(pFilePath)
{
	m_pGraphicDev->AddRef();
}


CHierarchyLoader::~CHierarchyLoader()
{
	m_pGraphicDev->Release();
}

STDMETHODIMP CHierarchyLoader::CreateFrame(LPCSTR Name, LPD3DXFRAME * ppNewFrame)
{
	D3DXFRAME_DERIVED*			pNewFrame = new D3DXFRAME_DERIVED;
	ZeroMemory(pNewFrame, sizeof(D3DXFRAME_DERIVED));

	Allocate_Name(&pNewFrame->Name, Name); //�̸� �ʱ�ȭ

	pNewFrame->matCombinedTransformationMatrix = *D3DXMatrixIdentity(&pNewFrame->TransformationMatrix); //��� ������ identity

	*ppNewFrame = pNewFrame;

	return S_OK;
}

STDMETHODIMP CHierarchyLoader::CreateMeshContainer(LPCSTR Name, const D3DXMESHDATA * pMeshData, const D3DXMATERIAL * pMaterials, const D3DXEFFECTINSTANCE * pEffectInstances, DWORD NumMaterials, const DWORD * pAdjacency, LPD3DXSKININFO pSkinInfo, LPD3DXMESHCONTAINER * ppNewMeshContainer)
{
	D3DXMESHCONTAINER_DERIVED*			pNewMeshContainer = new D3DXMESHCONTAINER_DERIVED;
	ZeroMemory(pNewMeshContainer, sizeof(D3DXMESHCONTAINER_DERIVED));

	Allocate_Name(&pNewMeshContainer->Name, Name);

	pNewMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;
	pNewMeshContainer->MeshData.pMesh = pMeshData->pMesh;

	LPD3DXMESH			pMesh = pNewMeshContainer->MeshData.pMesh;
	pMesh->AddRef();

	pNewMeshContainer->NumMaterials = NumMaterials;

	pNewMeshContainer->pMaterials = new D3DXMATERIAL[NumMaterials];
	pNewMeshContainer->ppTextures = new LPDIRECT3DTEXTURE9[NumMaterials];

	for (size_t i = 0; i < pNewMeshContainer->NumMaterials; ++i)
	{
		pNewMeshContainer->pMaterials[i] = pMaterials[i];

		wchar_t			szFullPath[128] = L"";
		lstrcpyW(szFullPath, m_pFilePath);

		wchar_t			szFileName[128] = L"";

		MultiByteToWideChar(CP_ACP, 0, pNewMeshContainer->pMaterials[i].pTextureFilename, strlen(pNewMeshContainer->pMaterials[i].pTextureFilename)
			, szFileName, 128); //�����ڵ� �� �ٲ�

		lstrcatW(szFullPath, szFileName);

		if (FAILED(D3DXCreateTextureFromFileW(m_pGraphicDev, szFullPath, &pNewMeshContainer->ppTextures[i])))
			return E_FAIL;
	}

	DWORD dwNumFace = pMesh->GetNumFaces(); //������ ����

	pNewMeshContainer->pAdjacency = new DWORD[dwNumFace * 3]; //�������� �̿��ϴ� �������� �ε����� ������.
	memcpy(pNewMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * dwNumFace * 3); //����

	pNewMeshContainer->pSkinInfo = pSkinInfo;
	pNewMeshContainer->pSkinInfo->AddRef();

	pNewMeshContainer->dwNumBones = pNewMeshContainer->pSkinInfo->GetNumBones();

	pNewMeshContainer->ppCombinedTransformationMatrices = new D3DXMATRIX*[pNewMeshContainer->dwNumBones]; //�� ���� ��ŭ �����Ҵ�
	ZeroMemory(pNewMeshContainer->ppCombinedTransformationMatrices, sizeof(D3DXMATRIX*) * pNewMeshContainer->dwNumBones);

	pNewMeshContainer->pOffsetMatrices = new D3DXMATRIX[pNewMeshContainer->dwNumBones]; 

	for (int i = 0; i < pNewMeshContainer->dwNumBones; ++i)
		pNewMeshContainer->pOffsetMatrices[i] = *pNewMeshContainer->pSkinInfo->GetBoneOffsetMatrix(i); //�޽��� ������ ������ �޾ƿ�. (�������� �ȹٲ�)

	pNewMeshContainer->pRenderingMatrices = new D3DXMATRIX[pNewMeshContainer->dwNumBones];
	ZeroMemory(pNewMeshContainer->pRenderingMatrices, sizeof(D3DXMATRIX) * pNewMeshContainer->dwNumBones);

	pMesh->CloneMeshFVF(pMesh->GetOptions(), pMesh->GetFVF(), m_pGraphicDev, &pNewMeshContainer->pOriginal_Mesh); //FVF �������� �޽��� ����
	//FVF�� �������� �ϴ� ������ FVF�� ������ ������ ������ ũ�⸦ �˼� �ֱ� �����̴�.
	pMesh->AddRef();

	pMesh->Release();
	pMesh = nullptr;

	*ppNewMeshContainer = pNewMeshContainer;

	return S_OK;
}

STDMETHODIMP CHierarchyLoader::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	return S_OK;
}

STDMETHODIMP CHierarchyLoader::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	return S_OK;
}

HRESULT CHierarchyLoader::Allocate_Name(char ** ppSour, const char * pDest)
{
	if (nullptr == pDest)
		return E_FAIL;

	DWORD dwLength = strlen(pDest) + 1;

	*ppSour = new char[dwLength];
	ZeroMemory(*ppSour, sizeof(char) * dwLength);

	strcpy(*ppSour, pDest);

	return S_OK;
}