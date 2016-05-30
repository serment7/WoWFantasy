#pragma once
class cCamera
{
private:
	D3DXVECTOR3				m_vEye;
	D3DXVECTOR3				m_vLookAt;
	D3DXVECTOR3				m_vUp;

	D3DXMATRIXA16			m_matView;
	D3DXMATRIXA16			m_matProj;

	float					m_fFovy;
	float					m_fAspect;
	float					m_fMinFov;
	float					m_fMaxFov;

public:
	cCamera();
	~cCamera();

	void Update();

	void SetEye(const D3DXVECTOR3& _vPos);
	void SetEye(const float& _x, const float& _y, const float& _z);
	void SetLookAt(const D3DXVECTOR3& _vLookAt);
	void SetLookAt(const float& _x, const float& _y, const float& _z);

	void SetFovy(const float& _fovy);
	void SetAspect(const float& _aspect);
	void SetMinFov(const float& _minFov);
	void SetMaxFov(const float& _maxFov);
};