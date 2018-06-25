#include "stdafx.h"
#include "Terrain.h"

Terrain::Terrain()
{
	dwTerrainX = 129;
	dwTerrainZ = 129;
}

Terrain::~Terrain()
{
}

void Terrain::HeightInit()
{

}

void Terrain::Init()
{
	m_TerrainBuffer = new BufferManager();

	HANDLE hFile = CreateFile(L"./Resource/Height.bmp", GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (0 == hFile)
		return;

	DWORD dwByte = 0;

	BITMAPFILEHEADER bitmapfileHeader;
	ReadFile(hFile, &bitmapfileHeader, sizeof(BITMAPFILEHEADER), &dwByte, nullptr);

	BITMAPINFOHEADER bitmapInfoHeader;
	ReadFile(hFile, &bitmapInfoHeader, sizeof(BITMAPINFOHEADER), &dwByte, nullptr);

	dwPixel = new DWORD[bitmapInfoHeader.biWidth * bitmapInfoHeader.biHeight];
	ReadFile(hFile, dwPixel, sizeof(DWORD) * bitmapInfoHeader.biWidth * bitmapInfoHeader.biHeight, &dwByte, nullptr);



	m_TerrainBuffer->CreateTexture(L"./Resource/Tile.tga");
	m_TerrainBuffer->UseMtrl(true);

	TerrainVertexInit();
	TerrainIndexInit();

	CloseHandle(hFile);
}

void Terrain::TerrainVertexInit()
{
	m_TerrainBuffer->CreateVertexBuffer(dwTerrainX * dwTerrainZ, sizeof(TEXVERTEX), TexVertexFVF, (dwTerrainX - 1) * (dwTerrainZ - 1) * 2);

	vertex = nullptr;

	m_TerrainBuffer->GetVB()->Lock(0, 0, (void**)&vertex, 0);
	static int in;

	for (int i = 0; i < dwTerrainZ; i++) //129 * 129 ��ŭ�� ������ �����.
	{
		for (int j = 0; j < dwTerrainX; j++)
		{
			int index = j + i * dwTerrainX;

			//int randomIndex = (rand() % 16640);
			if (index > in)
				in = index;

			vertex[index].vPos = D3DXVECTOR3(j, (dwPixel[index] & 0x000000ff) / 10.f, i); //�ҷ��� ��Ʈ���� �÷� �� b �� ���� AND �����ؼ� ���� ���� ������ 10���� ������ Y���� �����Ѵ�.
			vertex[index].vUV = D3DXVECTOR2((20.f * j) / dwTerrainX, (20.f * i) / dwTerrainZ); //0 ~ 128 �� �迭�� 0 ~ 20�� uv�� �ٲٱ� ���� Terrain�� X,Z�� �����ش�.
																							   //20�� ���ϴ� ������ �迭�� 129 ���� ���� 129 / 129 �� 1 �� �Ǵϱ� 20�� �����ش�.
		}
	}



	m_TerrainBuffer->GetVB()->Unlock();
}

void Terrain::TerrainIndexInit()
{
	m_TerrainBuffer->CreateIndexBuffer(128 * 128 * 2, sizeof(INDEX));
	INDEX* pindex = nullptr;

	int iTriIndex = 0;

	m_TerrainBuffer->GetIB()->Lock(0, 0, (void**)&pindex, 0);

	for (int i = 0; i < dwTerrainZ - 1; i++) //�ε��� ����
	{
		for (int j = 0; j < dwTerrainX - 1; j++) //-1 �� �ϴ� ������ �簢���� �ϳ� ���� ���� ���� ������ �ΰ� ���鶧�� 3���� �ʿ��ϱ� ������ ���� indexArr ���� + 1�� �ϸ� dwTerrain�� -1�� ��������
												 //129�� �Ѿ�� �����̴�.
		{
			int index = j + i * dwTerrainX;

			int indexArr[] =
			{
				index + dwTerrainX, //�׸��� ������ ù��°�� 0��°�ϱ� , ù��° �ٿ��� �ι�°�ٷ� ������ Terrain�� X��ŭ �����ش�.
				index + dwTerrainX + 1, //1�� 0 ���� +1
				index + 1, //2 �� 3���� +1
				index
			};

			//�ð�������� �׸���.
			pindex[iTriIndex]._1 = indexArr[0];
			pindex[iTriIndex]._2 = indexArr[1];
			pindex[iTriIndex]._3 = indexArr[2];
			//

			//������ ���鼭 �ε����� ���̸鼭 �ﰢ�� �׸��� ������ �� �������ش�.
			iTriIndex++;

			//���� �� a,b ���Ϳ� ���ÿ� �����ϴ� ���͸� ���Ѵ�.

			D3DXVECTOR3 vSrc = vertex[indexArr[1]].vPos - vertex[indexArr[0]].vPos; //a ���� ����
			D3DXVECTOR3 vDest = vertex[indexArr[2]].vPos - vertex[indexArr[1]].vPos; //b ���� ����
			D3DXVECTOR3 vNormal;
			D3DXVec3Cross(&vNormal, &vSrc, &vDest); //����

			vertex[indexArr[0]].vNormal += vNormal;
			vertex[indexArr[1]].vNormal += vNormal;
			vertex[indexArr[2]].vNormal += vNormal;

			//
			pindex[iTriIndex]._1 = indexArr[0];
			pindex[iTriIndex]._2 = indexArr[2];
			pindex[iTriIndex]._3 = indexArr[3];

			iTriIndex++;

			vSrc = vertex[indexArr[3]].vPos - vertex[indexArr[2]].vPos;
			vDest = vertex[indexArr[0]].vPos - vertex[indexArr[3]].vPos;
			D3DXVec3Cross(&vNormal, &vSrc, &vDest);

			vertex[indexArr[2]].vNormal += vNormal;
			vertex[indexArr[3]].vNormal += vNormal;
			vertex[indexArr[0]].vNormal += vNormal;
		}
	}

	m_TerrainBuffer->GetIB()->Unlock();

	for (int i = 0; i < dwTerrainZ * dwTerrainX; i++)
	{
		D3DXVec3Normalize(&vertex[i].vNormal, &vertex[i].vNormal);
	}
}

void Terrain::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
}

void Terrain::Render()
{
	GameObject::Render();

	m_TerrainBuffer->Render();
}
