#pragma once

class cGameObject;
class cParticle;
class cParticleEffect;
class cActionDelegate;
class cSkill;
class cStatus;

enum skilltype
{
	Support,
	Long,
	Short,
	continuous
};

class cSklilDelegate
{
public:
	virtual void OnSkillDelegate(cSkill* _pSender) = 0;
};

class cSkill
{
private:
	std::string			m_skillname;
	std::string			m_path;
	cGameObject*		m_pOwner = nullptr;
	cGameObject*		m_pTarget = nullptr;
	bool				m_bCast = false;
	bool				m_bCanMove = false;
	int					m_nEffectValue = 0;
	skilltype			m_skilltype=Short;
	
protected:
	cStatus*			m_pOwnerStatus = nullptr;
	size_t				m_ownerID=MAXSIZE_T;
	float				m_fDistance = 0.0f;
	cSklilDelegate*		m_pDelegate = nullptr;
	cParticleEffect*	m_pParticleEffect=nullptr;

	float				m_fCoolDownPassedTime = 0.0f;
	float				m_fCoolDownTime = 0.0f;
	bool				m_bCoolDown = false;

	int					m_nNecessaryHP = 0;
	int					m_nNecessaryMP = 0;

public:
	cSkill();
	virtual ~cSkill();

	void				SetDelegate(cSklilDelegate* _pDelegate);

	void				SetPath(const std::string& _path);
	const std::string&	GetPath();

	void				SetSkillName(const std::string& _skillname);
	const std::string&	GetSkillName() const;
	virtual void		Start() = 0;
	virtual void		Update(const float& _delta)=0;
	virtual void		Render()=0;
	virtual void		Stop()=0;

	void				SetOwner(cGameObject* _pOwner);
	void				SetTarget(cGameObject* _pTarget);
	cGameObject*		GetOwner();
	cGameObject*		GetTarget();
	bool				IsCast();
	void				SetCast(const bool _bCast);
	
	void				SetEffectValue(const int& _effectValue);
	const int&			GetEffectValue();
	
	void				SetSkillType(const skilltype& _type);
	const skilltype&	GetSKillType();

	const float&		GetPassedCoolTime();

	void				SetCoolDownTime(const float& _fCoolDownTime);
	const float&		GetCoolDownTime();
	void				InitSkill();
	
	void				SetCoolDown(const bool& _isCooldown);
	bool				IsCoolDown();

	virtual bool		CanUse();

	void				SetNecessaryHP(const int& _hp);
	const int&			GetNecessaryHP();
	void				SetNecessaryMP(const int& _mp);
	const int&			GetNecessaryMP();

	void				SetCanMove(const bool& _canmove);
	bool				CanMove();

	void				SetDistance(const float& _distance);
	const float&		GetDistance();
};

