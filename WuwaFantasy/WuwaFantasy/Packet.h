#pragma once
enum Msg_Type {
	Msg_Move = 0x101
	, Msg_Idle
	, Msg_Attack
	, Msg_Approach
	, Msg_GetCondition
	, Msg_UseItem
	, Msg_IdleAni
	, Msg_AttackAni
	, Msg_MoveAni
	, Msg_CastingAni
	
	

};

struct Packet_Move
{
	D3DXVECTOR3	vDes = D3DXVECTOR3(0, 0, 0);
	Packet_Move(D3DXVECTOR3 _des)
		:vDes(_des)
	{}
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

struct Packet_Hit
{
	size_t damage = -1;
	Packet_Hit(const size_t& _damage)
		:damage(_damage)
	{}
};

//struct Packet_Move
//{
//	D3DXVECTOR3	vDes = D3DXVECTOR3(0, 0, 0);
//	Packet_Move(D3DXVECTOR3 _des)
//		:vDes(_des)
//	{}
//};

class cGameObject;
struct Packet_Target
{
	cGameObject* pTarget = nullptr;
	Packet_Target(cGameObject* _pTarget)
		:pTarget(_pTarget)
	{}
};


class cCondition;
struct Packet_GetCondition
{
	cCondition* pCondition = nullptr;
	Packet_GetCondition(cCondition*	_pCondition)
		:pCondition(_pCondition)
	{}
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