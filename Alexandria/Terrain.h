#pragma once
class Terrain : public GameObject
{
private:
	BufferManager * m_TerrainBuffer;

	DWORD dwTerrainX;
	DWORD dwTerrainZ;

	DWORD* dwPixel;

	TEXVERTEX* vertex;
public:
	Terrain();
	virtual ~Terrain();

	void HeightInit();
	void Init();

	void TerrainVertexInit();
	void TerrainIndexInit();

	void Update(float deltaTime);
	void Render();

};

