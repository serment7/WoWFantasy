#include "stdafx.h"
#include "cMessageDispatcher.h"
#include"cGameObject.h"

cMessageDispatcher::cMessageDispatcher()
{
}


cMessageDispatcher::~cMessageDispatcher()
{
}

void cMessageDispatcher::Update()
{	
	if (m_message.empty())
		return;
	ST_PACKET packet= *m_message.begin();
	while(packet.delayTime < g_pTimeManager->GetCurTime())
	{
		cGameObject* pReceiver = g_pObjectManager->FindObjectByID(packet.receiver);
		pReceiver->OnMessage(packet);
		m_message.erase(m_message.begin());
		if (m_message.empty())
			break;
		packet = *m_message.begin();
	}
}

void cMessageDispatcher::Dispatch(const size_t & _sender, const size_t & _receiver, 
	const float& _delay, Msg_Type msg_type, void * _info)
{
	static ST_PACKET packet;
	packet.sender = _sender;
	packet.receiver = _receiver;
	packet.delayTime = _delay;
	packet.msg_type = msg_type;
	packet.info = _info;
	
	if (_delay <= 0.0f)
	{
		cGameObject* pReceiver=g_pObjectManager->FindObjectByID(_receiver);
		pReceiver->OnMessage(packet);
	}
	else
	{
		packet.delayTime = g_pTimeManager->GetCurTime() + _delay;
		m_message.insert(packet);
	}
}

void cMessageDispatcher::Clear()
{
	m_message.clear();
}
