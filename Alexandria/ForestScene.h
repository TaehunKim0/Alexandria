#pragma once

class Player;
class WindMill;
class Terrain;

class ForestScene : public Scene
{
public:
	Player * player;
	WindMill* windMill;
	Terrain* terrain;

public:
	ForestScene();
	virtual ~ForestScene();

	void Init();

	void Update(float deltaTime);
	void Render();
};