#pragma once

class cParticle;

class cParticleDelgate
{
public:
	virtual void OnParticleDelegate(cParticle* _pSender)=0;
};

struct stParticle
{
	D3DXVECTOR3 vPos;
	D3DCOLOR	color;
};

class cParticle
{
public:
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };

private:
	D3DXVECTOR3				m_vPos=D3DXVECTOR3(0,0,0);
	float					m_fPointSize=1.0f;
	D3DXVECTOR3				m_vDir=D3DXVECTOR3(0,0,0);
	float					m_fSpeed=0.0f;

	float					m_fLifeTime = 0.0f;
	float					m_fAge = 0.0f;
	D3DXCOLOR				m_color = D3DCOLOR_XRGB(255, 255, 255);
	bool					m_bIsAlive = false;
	bool					m_bRecycle = false;
	bool					m_bShow = true;

public:
	cParticle();
	~cParticle();

	virtual void		Update(const float& _delta);
	static void			PreRender(const float& _fSize);
	static void			PostRender();
	virtual void		Reset();

	void				SetPos(const D3DXVECTOR3& _vPos);
	void				SetPos(const float& _x, const float& _y, const float& _z);
	void				MovePos(const D3DXVECTOR3& vPos);
	void				SetDir(const D3DXVECTOR3& _vDir);
	void				SetDir(const float& _x, const float& _y, const float& _z);
	void				SetSize(const float& _size);
	void				SetSpeed(const float& _speed);
	void				SetAge(const float& _age);
	void				SetLifeTime(const float& _lifetime);
	void				SetColor(const D3DXCOLOR& _color);
	const D3DCOLOR&		GetColor();
	void				SetLive(const bool& _isLive);
	
	const D3DXVECTOR3&  GetPos();
	const D3DXVECTOR3&  GetDir();
	const float&		GetSize();
	const float&		GetSpeed();
	bool				IsLive();
	const float&		GetAge();
	const float&		GetLifeTime();
	void				SetRecycle(const bool& _isRecycle);
	bool				IsRecycle();
	void				SetShow(const bool& _bIsShow);
	bool				IsShow();
};

