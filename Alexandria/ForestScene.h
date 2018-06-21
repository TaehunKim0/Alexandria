#pragma once

class Player;
class WindMill;
class ForestScene : public Scene
{
public:
	Player * player;
	WindMill* windMill;

public:
	ForestScene();
	virtual ~ForestScene();

	void Init();

	void Update(float deltaTime);
	void Render();
};