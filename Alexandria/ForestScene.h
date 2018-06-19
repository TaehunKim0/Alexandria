#pragma once

class Player;
class ForestScene : public Scene
{
public:
	Player * player;

public:
	ForestScene();
	virtual ~ForestScene();

	void Init();

	void Update(float deltaTime);
	void Render();
};