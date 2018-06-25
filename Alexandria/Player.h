#pragma once

class Dynamic_Mesh;

class Player : public GameObject
{
	Mesh* m_Mesh;
	Dynamic_Mesh* m_pMesh = nullptr;
	D3DXVECTOR3 Dir;
public:
	Player();
	~Player();

	void Init();

	void Update(float deltaTime);
	void Render();
};