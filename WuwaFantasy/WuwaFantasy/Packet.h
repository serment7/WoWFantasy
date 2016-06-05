#pragma once
enum Msg_Type {
	Msg_MessageHandle = 0x101
	, Msg_Attack
	, Msg_GetCondition
	, Msg_UseItem

};

struct Packet_MessageHandle
{
	HWND hWnd;
	UINT iMessage;
	WPARAM wParam;
	LPARAM lParam;
	Packet_MessageHandle(const HWND& _hWnd, const UINT& _iMessage,
		const WPARAM& _wParam, const LPARAM& _lParam)
		:hWnd(_hWnd), iMessage(_iMessage), wParam(_wParam), lParam(_lParam)
	{}
};

struct Packet_Attack
{
	size_t Damage = -1;
};

class cCondition;
struct Packet_TakeCondition
{
	cCondition* pCondition = nullptr;
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