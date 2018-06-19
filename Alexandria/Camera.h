#pragma once
class Camera : public Singleton<Camera>
{
private:
	D3DXMATRIXA16 m_matWorld;
	D3DXMATRIXA16 m_matView;
	D3DXMATRIXA16 m_matProj;

private:
	D3DXVECTOR3 m_EyePt;
	D3DXVECTOR3 m_LookAtPt;
	D3DXVECTOR3 m_UpVec;
	D3DXVECTOR3 m_RightVec;

private:
	GameObject* m_Target;

private:
	bool CameraFreeView;

	float m_fRotX;
	float m_fRotY;

public:
	Camera();
	virtual ~Camera();

	void Update(float deltaTime);
	void SetTransform();

public:
	void SetTarget(GameObject* target);
	void SetCameraThirdPerson(GameObject* target);
	void SetCameraFreeView();
};

