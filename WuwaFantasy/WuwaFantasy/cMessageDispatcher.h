#pragma once

class cGameObject;

#define ENTITY_TYPE cGameObject

enum Msg_Type{
	Msg_MessageHandle
	, Msg_Attack
};

struct ST_PACKET
{
	int		sender;
	int		receiver;
	int		msg_type;
	float	delayTime;
	void*	info;
	

	ST_PACKET() :sender(0),
		receiver(0),
		msg_type(0),
		delayTime(0.0f),
		info(nullptr)
	{}

	ST_PACKET(int _sender,
		int _receiver,
		int _msg_type,
		float _delayTime,
		void* _info)
		: sender(_sender)
		, receiver(_receiver)
		, msg_type(_msg_type)
		, delayTime(_delayTime)
		, info((void*)_info)
	{}
};
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
	typedef std::map<int, ENTITY_TYPE*>		EntityMap;
	typedef std::map<int, ENTITY_TYPE*>		EntityMap;
	typedef std::set<ST_PACKET>				MsgSet;

private:
	MsgSet		m_message;
	MsgSet		m_delayMessage;

public:
	cMessageDispatcher();
	~cMessageDispatcher();

	void RegisterEntity(ENTITY_TYPE* _pTarget);
	void UnregisterEntityByID(int _id);
	void UnregisterEntityByTag(int _id);
	void ClearEntity();
	ENTITY_TYPE* GetEntityFromID(int _id) const;
	void Discharge();
	void DispatchMessage();
};
