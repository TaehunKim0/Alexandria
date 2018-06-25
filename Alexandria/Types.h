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
	LPD3DXMESH				pOriginal_Mesh; //���� �޽� ( ��İ��� �ߺ��� �����ϱ� ���ؼ� �޽��� ������ ) , �ִϸ��̼��� �ϰ� �� �� ����� ��� �����Ǵϱ� �װ� �����Ѵ�.
	LPDIRECT3DTEXTURE9*		ppTextures; //�ؽ���
	unsigned long			dwNumBones; //�� ����
	D3DXMATRIX**			ppCombinedTransformationMatrices; //��Ʈ������ ���� �޽� �����̳ʸ� ������ �ִ� ���� ��ı��� ���� ���
	D3DXMATRIX*				pOffsetMatrices; //�� ��ü�� ���� ��� ����ٰ� ���� ����� ����.
	D3DXMATRIX*				pRenderingMatrices; //�� �ΰ��� ���ؼ� ���� ����� ����.

}D3DXMESHCONTAINER_DERIVED;

typedef struct tagFrame_Derived : public D3DXFRAME
{
	D3DXMATRIX			matCombinedTransformationMatrix; //��Ʈ ������ ���� ������....
}D3DXFRAME_DERIVED;

extern DWORD VertexFVF;  /*D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE;*/
extern DWORD TexVertexFVF; /*D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;*/