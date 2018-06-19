#pragma once
class Scene : public GameObject
{
public:
	Scene();
	virtual ~Scene();

	virtual void Update(float deltaTime);
	virtual void Render();
};