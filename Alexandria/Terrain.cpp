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

	for (int i = 0; i < dwTerrainZ; i++) //129 * 129 만큼의 정점을 만든다.
	{
		for (int j = 0; j < dwTerrainX; j++)
		{
			int index = j + i * dwTerrainX;

			//int randomIndex = (rand() % 16640);
			if (index > in)
				in = index;

			vertex[index].vPos = D3DXVECTOR3(j, (dwPixel[index] & 0x000000ff) / 10.f, i); //불러온 비트맵의 컬러 중 b 의 값과 AND 연산해서 참인 값을 적절히 10으로 나눠서 Y값을 설정한다.
			vertex[index].vUV = D3DXVECTOR2((20.f * j) / dwTerrainX, (20.f * i) / dwTerrainZ); //0 ~ 128 의 배열을 0 ~ 20의 uv로 바꾸기 위해 Terrain의 X,Z로 나눠준다.
																							   //20을 곱하는 이유는 배열이 129 까지 가면 129 / 129 로 1 이 되니까 20을 곱해준다.
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

	for (int i = 0; i < dwTerrainZ - 1; i++) //인덱스 버퍼
	{
		for (int j = 0; j < dwTerrainX - 1; j++) //-1 을 하는 이유는 사각형을 하나 만들 때는 쓰는 정점은 두개 만들때는 3개가 필요하기 때문에 밑의 indexArr 에서 + 1을 하면 dwTerrain에 -1을 안했으면
												 //129로 넘어가기 때문이다.
		{
			int index = j + i * dwTerrainX;

			int indexArr[] =
			{
				index + dwTerrainX, //그리는 순서의 첫번째는 0번째니까 , 첫번째 줄에서 두번째줄로 갈려면 Terrain의 X만큼 더해준다.
				index + dwTerrainX + 1, //1은 0 에서 +1
				index + 1, //2 는 3에서 +1
				index
			};

			//시계방향으로 그린다.
			pindex[iTriIndex]._1 = indexArr[0];
			pindex[iTriIndex]._2 = indexArr[1];
			pindex[iTriIndex]._3 = indexArr[2];
			//

			//루프를 돌면서 인덱스를 높이면서 삼각형 그리는 순서를 다 설정해준다.
			iTriIndex++;

			//외적 두 a,b 벡터에 동시에 수직하는 벡터를 구한다.

			D3DXVECTOR3 vSrc = vertex[indexArr[1]].vPos - vertex[indexArr[0]].vPos; //a 벡터 구함
			D3DXVECTOR3 vDest = vertex[indexArr[2]].vPos - vertex[indexArr[1]].vPos; //b 벡터 구함
			D3DXVECTOR3 vNormal;
			D3DXVec3Cross(&vNormal, &vSrc, &vDest); //외적

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
