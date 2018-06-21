#pragma once
class WindMill : public GameObject
{
	BufferManager* m_WindMillBodyBuffer;

public:
	WindMill();
	~WindMill();

public:
	void Init();

	void SetWindMillVertex();
	void SetWindMillIndex();

	void Update(float deltaTime) override;
	void Render() override;
};