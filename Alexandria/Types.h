#pragma once
#include"stdafx.h"

struct tagVertex
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vNormal;
	D3DXCOLOR Diffuse;
}typedef VERTEX;

struct tagTexVertex
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vNormal;
	D3DXVECTOR2 vUV;
}typedef TEXVERTEX;

struct tagIndex
{
	DWORD _1, _2, _3;


}typedef INDEX;

typedef struct tagMeshContainer_Derived : public D3DXMESHCONTAINER
{
	LPD3DXMESH				pOriginal_Mesh; //원본 메쉬 ( 행렬곱의 중복을 방지하기 위해서 메쉬를 복제함 ) , 애니메이션을 하고 난 뒤 행렬이 계속 누적되니까 그걸 방지한다.
	LPDIRECT3DTEXTURE9*		ppTextures; //텍스쳐
	unsigned long			dwNumBones; //뼈 개수
	D3DXMATRIX**			ppCombinedTransformationMatrices; //루트뼈에서 현재 메쉬 컨테이너를 가지고 있는 뼈의 행렬까지 곱한 행렬
	D3DXMATRIX*				pOffsetMatrices; //뼈 자체의 월드 행렬 여기다가 위의 행렬을 곱함.
	D3DXMATRIX*				pRenderingMatrices; //위 두개를 곱해서 최종 행렬을 만듬.

}D3DXMESHCONTAINER_DERIVED;

typedef struct tagFrame_Derived : public D3DXFRAME
{
	D3DXMATRIX			matCombinedTransformationMatrix; //루트 뼈에서 현재 뼈까지....
}D3DXFRAME_DERIVED;

extern DWORD VertexFVF;  /*D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE;*/
extern DWORD TexVertexFVF; /*D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;*/