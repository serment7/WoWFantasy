
#pragma once

#include"cStateMachine.h"
class cCondition;

//interface
class iObject
{

protected:
	int				nRefCount = 0;
	virtual ~iObject() {};
public:
	virtual D3DXMATRIXA16 GetWorldMatrix() PURE;
	void AddRef() { ++nRefCount; };
	void Release()
	{
		--nRefCount;
		if (nRefCount <= 0)
			delete this;
	};
};

//cObject
class cObject : public iObject
{
private:
	D3DXMATRIXA16	m_matS;
	D3DXMATRIXA16	m_matT;
	D3DXMATRIXA16	m_matR;

	D3DXMATRIXA16	m_matWorld;

	D3DXVECTOR3		m_vPos;
	D3DXVECTOR3		m_vDir;

	float			m_angleY = 0.0f;


public:
	cObject();
	virtual ~cObject();

	void SetScaling(const float& sx, const float& sy, const float& sz)
	{
		D3DXMatrixScaling(&m_matS, sx, sy, sz);
	}

	void SetRotation(float angle, char axis = 'y')
	{
		//stdafx¿¡ enum¹® Ãß°¡ÇØÁÖ¼Åµµ µÊ
		if(axis == 'x')
		{
			D3DXMatrixRotationX(&m_matR, angle);			
		}
		else if(axis == 'z')
		{
			D3DXMatrixRotationZ(&m_matR, angle);
		}
		else
		{
			D3DXMatrixRotationY(&m_matR, angle);
		}
	}

	virtual void Update();
	virtual void Render() {};

	//Getter, Setter
	D3DXMATRIXA16 GetWorldMatrix() { return m_matWorld; }
	D3DXMATRIXA16 GetScalingMatrix() { return m_matS; }
	D3DXVECTOR3	GetVPos() { return m_vPos; }
	D3DXVECTOR3 GetVDir() { return m_vDir; }
	const int& GetCountRef() { return nRefCount; }

	void SetScalingMatrix( const D3DXMATRIXA16& matS ) { m_matS = matS; }
	void SetRotationMatirx( const D3DXMATRIXA16& matR ) { m_matT = matR; }
	void SetVPos( D3DXVECTOR3 vPos ) { m_vPos = vPos; }
	void SetVDir( D3DXVECTOR3 vDir ) { m_vDir = vDir; }

	void			SetRotationY(const float& _angle);
	void			TurnRotationY(const float& _angle);
	const float&	GetRotationY() const;
};