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

extern DWORD VertexFVF;  /*D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE;*/
extern DWORD TexVertexFVF; /*D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;*/