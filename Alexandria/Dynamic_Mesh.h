#pragma once

#include "stdafx.h"

class CHierarchyLoader;
class CAnimationCtrl;

class Dynamic_Mesh
{
public:
	Dynamic_Mesh(LPDIRECT3DDEVICE9 pGraphicDev);
	~Dynamic_Mesh();

public:
	HRESULT Init_Dynamic_Mesh(const wchar_t* pFilePath, const wchar_t* pFileName);
	void Update_CombiendTransformationMatrices(D3DXFRAME_DERIVED* pFrame, D3DXMATRIX matParent);
	void SetUp_CombinedMatricesPointer(D3DXFRAME_DERIVED* pFrame);
	void Render_Mesh();
	void Set_AnimationSet(const unsigned int& iIndex);
	void Play_AnimationSet(const float& fTime);
private:
	LPDIRECT3DDEVICE9							m_pGraphicDev = nullptr;
	D3DXFRAME*									m_pRootFrame = nullptr; //루트 뼈
	CHierarchyLoader*							m_pLoader = nullptr; //메쉬를 로딩했을 때 호출되는 함수를 모아놓은 클래스 (재정의 해놈)
	list<D3DXMESHCONTAINER_DERIVED*>			m_MeshContainerList; //메쉬 컨테이너들을 모아놈
	typedef list<D3DXMESHCONTAINER_DERIVED*>	MESHCONTAINERLIST; 
	CAnimationCtrl*								m_pAnimationCtrl = nullptr; //애니메이션 컨트롤러
};