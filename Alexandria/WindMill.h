#pragma once
class WindMill : public GameObject
{
	BufferManager* m_WindMillBodyBuffer;
	BufferManager* m_WindMillWingBuffer;

	Transform* m_WingTrans;

	D3DXMATRIX ww;
public:
	WindMill();
	~WindMill();

public:
	void Init();

private:
	void Move();
	void ShootWing();

private:
	void SetWindMillVertex();
	void SetWindMillIndex();

public:
	void Update(float deltaTime) override;
	void Render() override;
};