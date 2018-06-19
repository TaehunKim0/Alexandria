#pragma once
class SceneManager : public Singleton<SceneManager>
{
private:
	Scene * m_CurrentScene;

public:
	SceneManager();
	~SceneManager();

	void SetScene(Scene* scene);

	void Update(float deltaTime);
	void Render();

};

