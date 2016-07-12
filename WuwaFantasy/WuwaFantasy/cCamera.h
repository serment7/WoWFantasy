#pragma once

struct Packet_Zoom;

class cFrustum;


class cCamera
{
private:
	D3DXVECTOR3				m_vEye;
	D3DXVECTOR3				m_vLookAt;
	D3DXVECTOR3				m_vUp;
	D3DXVECTOR3				m_vPos;

	D3DXMATRIXA16			m_matView;
	D3DXMATRIXA16			m_matProj;
	D3DXMATRIXA16			m_matWorld;

	D3DXMATRIXA16			m_matTrans;
	D3DXMATRIXA16			m_matRotX, m_matRotY;
	float					m_fAngleX = 15.0f;
	float					m_fAngleY = 0.0f;
	
	float					m_fDistance = 10.0f;
	float					m_fMinDistance = 2.0f;
	float					m_fMaxDistance = 20.0f;

	float					m_fFovy;
	float					m_fAspect;
	float					m_fMinFov=1;
	float					m_fMaxFov=1000;

	bool					m_isLButtonDown=false;
	POINT					m_ptPrevMouse;

	cFrustum*				m_pFrustum = nullptr;

public:
	cCamera();
	~cCamera();

	virtual void Update();

	void SetEye(const D3DXVECTOR3& _vPos);
	void MoveEye(const D3DXVECTOR3& _vPos);
	void SetEye(const float& _x, const float& _y, const float& _z);
	void SetLookAt(const D3DXVECTOR3& _vLookAt);
	void SetLookAt(const float& _x, const float& _y, const float& _z);
	void MoveLookAt(const D3DXVECTOR3& _vPos);

	const D3DXVECTOR3& GetEye();
	const D3DXVECTOR3& GetLookAt();

	void SetAngleX(const float& _angleX);
	void SetAngleY(const float& _angleY);
	void MoveAngleX(const float& _angleX);
	void MoveAngleY(const float& _angleY);
	const float& GetAngleX();
	const float& GetAngleY();

	void SetFovy(const float& _fovy);
	void SetAspect(const float& _aspect);
	void SetMinFov(const float& _minFov);
	void SetMaxFov(const float& _maxFov);

	void SetDistance(const float& _distance);
	const float& GetDistance();

	bool			MessageHandle(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	BOOL IsItCulling(BoundingSphere* bs);

	BOOL IsIn(D3DXVECTOR3& vec);
};