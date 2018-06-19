#pragma once
class ObjectManager : public Singleton<ObjectManager>
{
private:
	std::list<GameObject*> m_ObjectList;
	std::list<GameObject*> m_CollisionList;

public:
	ObjectManager();
	virtual ~ObjectManager();

	void Release();

public:
	void AddObject(GameObject* obj);
	void AddCollisionObject(GameObject* obj);

	void RemoveObject(GameObject* obj);
	void RemoveCollisionObject(GameObject* obj);

public:
	void Update(float deltaTime);
	void Render();

};

