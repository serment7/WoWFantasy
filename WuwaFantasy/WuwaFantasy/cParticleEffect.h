#pragma once

class cParticle;

const std::string PARTICLE_PATH = "./Resource/Particle/";

class cParticleEffect
{
private:
	LPDIRECT3DTEXTURE9			texture = nullptr;
	LPDIRECT3DVERTEXBUFFER9		vertexBuffer = nullptr;

	int							m_nParticleNum = 0;
	float						m_fSize=0.0f;

	D3DXMATRIXA16				m_matWorld;

	DWORD vbSize = 2048;							// ���ؽ� ���� ũ��
	DWORD vbOffset = 0;								// ���ؽ� ���۸� ��ױ� ���� offset(��ƼŬ ���� ����)
	DWORD vbBatchSize = 512;

	std::list<cParticle*> particles;

public:
	cParticleEffect();
	virtual ~cParticleEffect();

	void	Update(const float _delta);
	void	Render();
	void	AddParticle(cParticle* _particle);
	void	SetSize(const float& _size);
	const float&		GetSize();
	void	SetTexture(const std::string& _texture);

	void					SetMatrix(const D3DXMATRIXA16& _matrix);
	const D3DXMATRIXA16&	GetMatrix();
};

