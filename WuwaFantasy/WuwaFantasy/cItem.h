#pragma once

class cGameObject;

class cItem
{
private:
	std::string					m_itemname;
	std::vector<std::string>	m_effect;

public:
	cItem();
	~cItem();

	void				SetItemName(const std::string& _itemname);
	const std::string&	GetItemName() const;
	void				AddEffect(const std::string& _effectName);
	virtual void		Use(cGameObject* _pTarget) = 0;
};

