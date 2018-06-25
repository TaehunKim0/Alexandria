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
	D3DXFRAME*									m_pRootFrame = nullptr; //��Ʈ ��
	CHierarchyLoader*							m_pLoader = nullptr; //�޽��� �ε����� �� ȣ��Ǵ� �Լ��� ��Ƴ��� Ŭ���� (������ �س�)
	list<D3DXMESHCONTAINER_DERIVED*>			m_MeshContainerList; //�޽� �����̳ʵ��� ��Ƴ�
	typedef list<D3DXMESHCONTAINER_DERIVED*>	MESHCONTAINERLIST; 
	CAnimationCtrl*								m_pAnimationCtrl = nullptr; //�ִϸ��̼� ��Ʈ�ѷ�
};