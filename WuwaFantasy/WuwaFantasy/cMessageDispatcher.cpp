#include "stdafx.h"
#include "cMessageDispatcher.h"


cMessageDispatcher::cMessageDispatcher()
{
}


cMessageDispatcher::~cMessageDispatcher()
{
}

void cMessageDispatcher::Discharge()
{
	if (!pReceiver->HandleMessage(telegram))
	{
		//telegram could not be handled
		cout << "Message not handled";
	}
}

void cMessageDispatcher::Dispatch(const size_t & _sender, const size_t & _receiver, 
	const float& _delay, size_t msg_type, void * _info)
{
	static ST_PACKET packet;
	packet.sender = _sender;
	packet.receiver = _receiver;
	packet.delayTime = _delay;
	packet.msg_type = msg_type;
	packet.info = _info;
	
	if (_delay <= 0.0f)
	{
		cObject* pReceiver=g_pObjectManager->FindObjectByID(_receiver);
	}
}
