#pragma once
class WindMill : public GameObject
{
	BufferManager m_Buffer;

public:
	WindMill();
	~WindMill();

public:
	void Init();

	void Update(float deltaTime) override;
	void Render() override;
};

