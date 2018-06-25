#include "stdafx.h"
#include "Dynamic_Mesh.h"
#include "CHierarchyLoader.h"
#include "CAnimationCtrl.h"

Dynamic_Mesh::Dynamic_Mesh(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
{
	m_pGraphicDev->AddRef();
}


Dynamic_Mesh::~Dynamic_Mesh()
{
}

HRESULT Dynamic_Mesh::Init_Dynamic_Mesh(const wchar_t * pFilePath, const wchar_t * pFileName)
{
	wchar_t	szFullPath[128] = L"";

	lstrcpyW(szFullPath, pFilePath);
	lstrcatW(szFullPath, pFileName);

	m_pLoader = new CHierarchyLoader(m_pGraphicDev, pFilePath);

	if (nullptr == m_pLoader)
		return E_FAIL;

	LPD3DXANIMATIONCONTROLLER			pAniCtrl = nullptr;

	if (FAILED(D3DXLoadMeshHierarchyFromXW(szFullPath, D3DXMESH_MANAGED, m_pGraphicDev, m_pLoader, nullptr, &m_pRootFrame, &pAniCtrl)))
		return E_FAIL;

	m_pAnimationCtrl = new CAnimationCtrl(m_pGraphicDev, pAniCtrl);
	if (nullptr == m_pAnimationCtrl)
		return E_FAIL;

	pAniCtrl->Release();

	m_pAnimationCtrl->Set_AnimationSet(55);
	//걷기 54


	D3DXMATRIX			matPivot;
	Update_CombiendTransformationMatrices((D3DXFRAME_DERIVED*)m_pRootFrame, *D3DXMatrixRotationY(&matPivot, D3DXToRadian(180.0f)));

	SetUp_CombinedMatricesPointer((D3DXFRAME_DERIVED*)m_pRootFrame);

	return S_OK;
}

void Dynamic_Mesh::Update_CombiendTransformationMatrices(D3DXFRAME_DERIVED * pFrame, D3DXMATRIX matParent)
{
	pFrame->matCombinedTransformationMatrix = pFrame->TransformationMatrix * matParent;

	if (nullptr != pFrame->pFrameSibling)
		Update_CombiendTransformationMatrices(((D3DXFRAME_DERIVED*)pFrame->pFrameSibling), matParent);

	if (nullptr != pFrame->pFrameFirstChild)
		Update_CombiendTransformationMatrices(((D3DXFRAME_DERIVED*)pFrame->pFrameFirstChild), pFrame->matCombinedTransformationMatrix);
}

void Dynamic_Mesh::SetUp_CombinedMatricesPointer(D3DXFRAME_DERIVED * pFrame)
{
	if (nullptr != pFrame->pMeshContainer)
	{
		D3DXMESHCONTAINER_DERIVED*	pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pFrame->pMeshContainer;

		m_MeshContainerList.push_back(pMeshContainer);

		for (int i = 0; i < pMeshContainer->dwNumBones; ++i)
		{

			const char* pName = pMeshContainer->pSkinInfo->GetBoneName(i);

			D3DXFRAME_DERIVED*	pFrame_Find = (D3DXFRAME_DERIVED*)D3DXFrameFind(m_pRootFrame, pName);

			pMeshContainer->ppCombinedTransformationMatrices[i] = &pFrame_Find->matCombinedTransformationMatrix;
		}
	}

	if (nullptr != pFrame->pFrameSibling)
		SetUp_CombinedMatricesPointer(((D3DXFRAME_DERIVED*)pFrame->pFrameSibling));

	if (nullptr != pFrame->pFrameFirstChild)
		SetUp_CombinedMatricesPointer(((D3DXFRAME_DERIVED*)pFrame->pFrameFirstChild));
}

void Dynamic_Mesh::Render_Mesh()
{
	for (auto& pMeshContainer : m_MeshContainerList)
	{
		for (DWORD j = 0; j < pMeshContainer->dwNumBones; ++j)
		{
			pMeshContainer->pRenderingMatrices[j]
				= pMeshContainer->pOffsetMatrices[j] * *pMeshContainer->ppCombinedTransformationMatrices[j];
		}

		void		*pVerticesSrc = nullptr, *pVerticesDst = nullptr;
		
		pMeshContainer->pOriginal_Mesh->LockVertexBuffer(0, &pVerticesSrc);
		pMeshContainer->MeshData.pMesh->LockVertexBuffer(0, &pVerticesDst);

		pMeshContainer->pSkinInfo->UpdateSkinnedMesh(pMeshContainer->pRenderingMatrices, nullptr, pVerticesSrc, pVerticesDst); //소프트웨어 스키닝 ( 느림 )

		pMeshContainer->pOriginal_Mesh->UnlockVertexBuffer();
		pMeshContainer->MeshData.pMesh->UnlockVertexBuffer();


		for (DWORD i = 0; i < pMeshContainer->NumMaterials; ++i)
		{
			m_pGraphicDev->SetTexture(0, pMeshContainer->ppTextures[i]);
			pMeshContainer->MeshData.pMesh->DrawSubset(i);

		}
	}
}

void Dynamic_Mesh::Set_AnimationSet(const unsigned int & iIndex)
{
	m_pAnimationCtrl->Set_AnimationSet(iIndex);
}

void Dynamic_Mesh::Play_AnimationSet(const float & fTime)
{
	m_pAnimationCtrl->Play_AnimationSet(fTime);

	D3DXMATRIX			matPivot;
	Update_CombiendTransformationMatrices((D3DXFRAME_DERIVED*)m_pRootFrame, *D3DXMatrixRotationY(&matPivot, D3DXToRadian(180.0f)));
}
