
#pragma once

#include"cStateMachine.h"
class cCondition;

//interface
class iObject
{
public:
	int				nRefCount;

public:
	virtual D3DXMATRIXA16 GetWorldMatrix() PURE;
	virtual void AddRef() PURE;
	virtual void Release() PURE;
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
	int nRefCount;

	size_t			m_unID = -1;
	size_t			m_unTag = -1;

	cStateMachine<cObject>*			m_pStateMachine;
	std::list<cCondition*>	m_listCondition;

public:
	cObject();
	virtual ~cObject();

	void SetID(const size_t& _id);
	void SetTag(const size_t& _tag);
	const size_t& GetID();
	const size_t& GetTag();

	void			AddCondition(cCondition* _pCondition);
	
	void SetScaling(const float& sx, const float& sy, const float& sz)
	{
		D3DXMatrixScaling(&m_matS, sx, sy, sz);
	}

	void SetRotation(float angle, char axis = 'y')
	{
		//stdafxø° enumπÆ √ﬂ∞°«ÿ¡÷º≈µµ µ 
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

	void Update();
	void Render() {};

	void AddRef();
	virtual void Release();

	//Getter, Setter
	D3DXMATRIXA16 GetWorldMatrix() { return m_matWorld; }
	D3DXMATRIXA16 GetScalingMatrix() { return m_matS; }
	D3DXVECTOR3	GetVPos() { return m_vPos; }
	D3DXVECTOR3 GetVDir() { return m_vDir; }
	int GetCountRef() { return nRefCount; }

	void SetScalingMatrix( const D3DXMATRIXA16& matS ) { m_matS = matS; }
	void SetRotationMatirx( const D3DXMATRIXA16& matR ) { m_matT = matR; }
	void SetVPos( D3DXVECTOR3 vPos ) { m_vPos = vPos; }
	void SetVDir( D3DXVECTOR3 vDir ) { m_vDir = vDir; }

	void			SetRotationY(const float& _angle);
	void			TurnRotationY(const float& _angle);
	const float&	GetRotationY() const;

	void			OnMessage(const ST_PACKET& _packet);
};