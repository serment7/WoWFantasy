#include "stdafx.h"
#include "cItem.h"


cItem::cItem()
{
}


cItem::~cItem()
{
}

void cItem::SetItemName(const std::string & _itemname)
{
	m_itemname = _itemname;
}

const std::string & cItem::GetItemName() const
{
	return m_itemname;
}

void cItem::AddEffect(const std::string & _effectName)
{
	m_effect.push_back(_effectName);
}
