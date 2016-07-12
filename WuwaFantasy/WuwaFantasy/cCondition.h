#pragma once

class cGameObject;
class cParticleEffect;

class cCondition
{
private:
	cGameObject*			m_pOwner = nullptr;
	std::string				m_strConditionName;

protected:
	cParticleEffect*	m_pParticleEffect = nullptr;

public:
	cCondition();
	virtual ~cCondition();

	void			SetOwner(cGameObject* _pOwner);
	cGameObject*	GetOwner() const;
	virtual void	Update(const float& _delta,bool& _lifeTime);
	virtual void	Render();
	virtual void	PostRender();
};

