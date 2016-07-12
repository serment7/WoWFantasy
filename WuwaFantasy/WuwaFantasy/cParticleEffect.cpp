#include "stdafx.h"
#include "cParticleEffect.h"
#include "cParticle.h"

cParticleEffect::cParticleEffect()
{
	g_pD3DDevice->CreateVertexBuffer(vbSize * sizeof(stParticle),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		cParticle::FVF,
		D3DPOOL_DEFAULT,
		&vertexBuffer, 0);
	texture = g_pTextureManager->GetTexture(PARTICLE_PATH+"fireworks_flare.bmp");
	D3DXMatrixIdentity(&m_matWorld);
}


cParticleEffect::~cParticleEffect()
{
	for (auto iter = particles.begin(); iter != particles.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
	particles.clear();
	texture = nullptr;
	SAFE_RELEASE(vertexBuffer);
}

void cParticleEffect::Update(const float _delta)
{
	if (particles.empty())
		return;
	auto iter = particles.begin();
	while (iter != particles.end())
	{
		if ((*iter)->IsLive())
		{
			(*iter)->Update(_delta);
			++iter;
		}
		else
		{
			if ((*iter)->IsRecycle())
				(*iter)->Reset();
			else
			{
				cParticle* delParticle = (*iter);
				particles.erase(iter++);
				SAFE_DELETE(delParticle);
			}
		}
	}
}

void cParticleEffect::Render()
{
	if (particles.empty())
		return;
	cParticle::PreRender(m_fSize);
	g_pD3DDevice->SetTexture(0, texture);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(stParticle));
	m_nParticleNum = particles.size();

	stParticle* v = 0;

	vertexBuffer->Lock(
		0,
		m_nParticleNum * sizeof(stParticle),
		(void**)&v,
		D3DLOCK_DISCARD);

	int numParticleDraw = 0;
	for (auto iter = particles.begin(); iter != particles.end(); ++iter)
	{
		if ((*iter)->IsLive()&&(*iter)->IsShow())
		{
			v->vPos = (*iter)->GetPos();
			v->color = (*iter)->GetColor();
			++v;
			++numParticleDraw;
		}
	}
	vertexBuffer->Unlock();

	g_pD3DDevice->DrawPrimitive(
		D3DPT_POINTLIST,
		0,
		numParticleDraw);

	cParticle::PostRender();
}

void cParticleEffect::AddParticle(cParticle * _particle)
{
	particles.push_back(_particle);
}

void cParticleEffect::SetSize(const float & _size)
{
	m_fSize = _size;
}

const float & cParticleEffect::GetSize()
{
	return m_fSize;
}

void cParticleEffect::SetTexture(const std::string & _texture)
{
	texture = g_pTextureManager->GetTexture(PARTICLE_PATH+_texture);
}

void cParticleEffect::SetMatrix(const D3DXMATRIXA16 & _matrix)
{
	m_matWorld = _matrix;
}

const D3DXMATRIXA16 & cParticleEffect::GetMatrix()
{
	return m_matWorld;
}
