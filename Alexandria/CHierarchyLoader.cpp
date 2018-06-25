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

	Allocate_Name(&pNewFrame->Name, Name); //이름 초기화

	pNewFrame->matCombinedTransformationMatrix = *D3DXMatrixIdentity(&pNewFrame->TransformationMatrix); //모든 뼈들을 identity

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
			, szFileName, 128); //유니코드 로 바꿈

		lstrcatW(szFullPath, szFileName);

		if (FAILED(D3DXCreateTextureFromFileW(m_pGraphicDev, szFullPath, &pNewMeshContainer->ppTextures[i])))
			return E_FAIL;
	}

	DWORD dwNumFace = pMesh->GetNumFaces(); //폴리곤 개수

	pNewMeshContainer->pAdjacency = new DWORD[dwNumFace * 3]; //폴리곤의 이웃하는 폴리곤의 인덱스를 저장함.
	memcpy(pNewMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * dwNumFace * 3); //복사

	pNewMeshContainer->pSkinInfo = pSkinInfo;
	pNewMeshContainer->pSkinInfo->AddRef();

	pNewMeshContainer->dwNumBones = pNewMeshContainer->pSkinInfo->GetNumBones();

	pNewMeshContainer->ppCombinedTransformationMatrices = new D3DXMATRIX*[pNewMeshContainer->dwNumBones]; //뼈 개수 만큼 동적할당
	ZeroMemory(pNewMeshContainer->ppCombinedTransformationMatrices, sizeof(D3DXMATRIX*) * pNewMeshContainer->dwNumBones);

	pNewMeshContainer->pOffsetMatrices = new D3DXMATRIX[pNewMeshContainer->dwNumBones]; 

	for (int i = 0; i < pNewMeshContainer->dwNumBones; ++i)
		pNewMeshContainer->pOffsetMatrices[i] = *pNewMeshContainer->pSkinInfo->GetBoneOffsetMatrix(i); //메쉬의 오프셋 정보를 받아옴. (오프셋은 안바뀜)

	pNewMeshContainer->pRenderingMatrices = new D3DXMATRIX[pNewMeshContainer->dwNumBones];
	ZeroMemory(pNewMeshContainer->pRenderingMatrices, sizeof(D3DXMATRIX) * pNewMeshContainer->dwNumBones);

	pMesh->CloneMeshFVF(pMesh->GetOptions(), pMesh->GetFVF(), m_pGraphicDev, &pNewMeshContainer->pOriginal_Mesh); //FVF 기준으로 메쉬를 복제
	//FVF를 기준으로 하는 이유는 FVF로 정점이 포함한 정보와 크기를 알수 있기 때문이다.
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