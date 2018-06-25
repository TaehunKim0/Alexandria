#pragma once
#include "stdafx.h"

class CHierarchyLoader : public ID3DXAllocateHierarchy
{
public:
	CHierarchyLoader(LPDIRECT3DDEVICE9 pGraphicDev, const wchar_t* pFilePath);
	~CHierarchyLoader();
public:
	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name,
		LPD3DXFRAME *ppNewFrame);
	STDMETHOD(CreateMeshContainer)(THIS_
		LPCSTR Name,
		CONST D3DXMESHDATA *pMeshData,
		CONST D3DXMATERIAL *pMaterials,
		CONST D3DXEFFECTINSTANCE *pEffectInstances,
		DWORD NumMaterials,
		CONST DWORD *pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer);
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree);
public:
	HRESULT Allocate_Name(char** ppSour, const char* pDest);
private:
	LPDIRECT3DDEVICE9			m_pGraphicDev = nullptr;
	const wchar_t*				m_pFilePath = nullptr;
};

