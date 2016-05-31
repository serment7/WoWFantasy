
#pragma once

//interface
class iObject
{
public:
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

	int nRefCount;

public:
	cObject();
	virtual ~cObject();

	void Update();
	virtual void Render() = 0;

	void AddRef();
	void Release();

	//Getter, Setter
	D3DXMATRIXA16 GetWorldMatrix() { return m_matWorld; }

	D3DXMATRIXA16 GetScalingMatrix() { return m_matS; }
	float GetScalingX() { return m_matS._11; }
	float GetScalingY() { return m_matS._22; }
	float GetScalingZ() { return m_matS._33; }

	D3DXVECTOR3	GetVPos() { return m_vPos; }
	float GetVPosX() { return m_vPos.x; }
	float GetVPosY() { return m_vPos.y; }
	float GetVPosZ() { return m_vPos.z; }

	D3DXVECTOR3 GetVDir() { return m_vDir; }
	float GetVDirX() { return m_vDir.x; }
	float GetVDirY() { return m_vDir.y; }
	float GetVDirZ() { return m_vDir.z; }

	void SetScalingMatrix( const D3DXMATRIX& matS ) { m_matS = matS; }
	void SetScalingMatrix( const float& x, const float& y, const float& z ) 
	{
		D3DXMatrixScaling(&m_matS, x, y, z);
	}

	//있으면 편할 거 같아서 그냥 오버로딩
	void SetRotationMatirx( const D3DXMATRIX& matR ) { m_matR = matR; }
	void SetRotationMatrix( const float& angle, char axis = 'y')
	{
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

	void SetVPos( const D3DXVECTOR3& vPos ) { m_vPos = vPos; }
	void SetVPos( const float& x, const float& y, const float& z) 
	{
		//함수가 생각이 안난다...누가 보면 추가해줘요
		m_vPos.x = x;
		m_vPos.y = y;
		m_vPos.z = z;
	}

	void SetVDir( const D3DXVECTOR3& vDir ) { m_vDir = vDir; }
	void IncRefCount() { ++nRefCount; }

};