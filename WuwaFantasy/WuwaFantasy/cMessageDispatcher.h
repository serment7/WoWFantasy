#pragma once

#define g_pMessageDispatcher cMessageDispatcher::GetInstance()

const double SmallestDelay = 0.25;
inline bool operator==(const ST_PACKET& _packet1, const ST_PACKET& _packet2)
{
	return (fabs(_packet1.delayTime - _packet2.delayTime) < SmallestDelay) &&
		(_packet1.sender == _packet2.sender) &&
		(_packet1.receiver == _packet2.receiver) &&
		(_packet1.msg_type == _packet2.msg_type);
}

inline bool operator<(const ST_PACKET& _packet1, const ST_PACKET& _pakcet2)
{
	if (_packet1 == _pakcet2)
	{
		return false;
	}
	else
	{
		return  (_packet1.delayTime < _pakcet2.delayTime);
	}
}

class cMessageDispatcher
{
private:
	typedef std::set<ST_PACKET>				MsgSet;

private:
	MsgSet		m_message;
	MsgSet		m_delayMessage;

public:
	cMessageDispatcher();
	~cMessageDispatcher();

	cMessageDispatcher* GetInstance()
	{
		static cMessageDispatcher instance;
		return &instance;
	}

	void Discharge();
	void Dispatch(const size_t& _sender, const size_t& _receiver,const float& _delay, 
		size_t _msg_type, void* _info);
};
