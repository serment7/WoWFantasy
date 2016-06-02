#pragma once

class cGameObject;

class cItem
{
private:
	std::string			m_itemname;

public:
	cItem();
	~cItem();

	void SetItemName(const std::string& _itemname);
	const std::string& GetItemName() const;
	virtual void Use(cGameObject*) = 0;
};

