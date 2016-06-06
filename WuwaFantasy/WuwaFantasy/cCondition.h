#pragma once

class cGameObject;

class cCondition
{
private:
	cGameObject*			m_pOwner = nullptr;
	std::string				m_strConditionName;

protected:
	cCondition();
	~cCondition();
public:

	void			SetOwner(cGameObject* _pOwner);
	cGameObject*	GetOwner() const;
	virtual void	Update(bool& _lifeTime) = 0;
};

