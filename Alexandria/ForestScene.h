#pragma once

class Player;
class WindMill;
class Terrain;
class PointLight;

class ForestScene : public Scene
{
public:
	Player * player;
	WindMill* windMill;
	Terrain* terrain;
	PointLight* m_PointLight1;

public:
	ForestScene();
	virtual ~ForestScene();

	void Init();

	void Update(float deltaTime);
	void Render();
};