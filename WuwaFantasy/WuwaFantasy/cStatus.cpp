
#include "stdafx.h"
#include "cStatus.h"

cStatus::cStatus()
{
	memset(&m_stStatus, 0, sizeof(ST_STATUS));
}

cStatus::~cStatus()
{

}

void cStatus::Setup(const ST_STATUS& stChInfo)
{
	memcpy(&m_stStatus, &stChInfo, sizeof(ST_STATUS));
	m_stStatus.nLevel = 1;
	m_stStatus.fExp = 0.0f;
}