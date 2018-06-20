#pragma once
class ObjectManager : public Singleton<ObjectManager>
{
private:
	std::list<GameObject*> m_ObjectList;
	std::list<GameObject*> m_CollisionList;

public:
	virtual ~ObjectManager();

	void Release();

public:
	void AddObject(GameObject* obj);
	void AddCollisionObject(GameObject* obj);

	void RemoveObject(GameObject* obj);
	void RemoveCollisionObject(GameObject* obj);


	bool Compare (const GameObject* obj1, const GameObject* obj2) const
	{
		if (obj1->m_UseBlending == true && obj2->m_UseBlending == false)
		{
			return true;
		}
		else
			return false;
	/*	if (obj1->m_UseBlending == true && obj2->m_UseBlending == true)
		{
			return false;
		}*/
	}
	

public:
	void Update(float deltaTime);
	void Render();

};

