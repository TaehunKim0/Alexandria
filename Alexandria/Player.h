#pragma once
class Player : public GameObject
{
public:
	Player();
	~Player();

	void Update(float deltaTime);
	void Render();
};

