#pragma once
class Player : public GameObject
{
	Mesh* m_Mesh;

public:
	Player();
	~Player();

	void Init();

	void Update(float deltaTime);
	void Render();
};