#pragma once
enum Msg_Type {
	Msg_Move = 0x101
	, Msg_Idle
	, Msg_Attack
	, Msg_GetCondition
	, Msg_UseItem
	, Msg_IdleAni
	, Msg_AttackAni
	, Msg_AttackEnd
	, Msg_MoveAni
	, Msg_CastingAni
	, Msg_UseSkill
	, Msg_SetSkill
	, Msg_Target
	, Msg_Death
	, Msg_Hit
	, Msg_StunAni
	, Msg_Standby
	, Msg_JoinParty
	, Msg_Render
	, Msg_NeedHeal
	, Msg_WoundAni
	, Msg_BattleRoarAni
	, Msg_FindTarget
	, Msg_LostTarget
	, Msg_Stun
	, Msg_Active
	, Msg_AddCondition
	, Msg_SupportEnd
	, Msg_CastEnd
	, Msg_Patrol
	, Msg_Respawn
	, Msg_StunEnd
	, Msg_ThrowAni
};

struct Packet_Pos
{
	D3DXVECTOR3	vPos = D3DXVECTOR3(0, 0, 0);
	Packet_Pos(D3DXVECTOR3 _des)
		:vPos(_des)
	{}
};

struct Packet_Time
{
	float fTime = 0.0f;
	Packet_Time(const float& _time)
		:fTime(_time)
	{}
};

class cCondition;

struct Packet_AddCondition
{
	cCondition*	pCondition = nullptr;
	Packet_AddCondition(cCondition* _pCondition)
		:pCondition(_pCondition)
	{}
};

struct Packet_SetSkill
{
	cSkill* skill=nullptr;
	char key=CHAR_MAX;
	Packet_SetSkill(const char& _key, cSkill* _skill)
		:key(_key), skill(_skill)
	{}
};

struct Packet_UseSkill
{
	char key = CHAR_MAX;
	Packet_UseSkill(const char& _key)
		:key(_key)
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

class cGameObject;
struct Packet_Attack
{
	cGameObject*	pTarget = nullptr;
	cSkill*			pSKill = nullptr;
	Packet_Attack(cGameObject* _pTarget,cSkill* _pSkill)
		:pTarget(_pTarget), pSKill(_pSkill)
	{}
};

class cGameObject;
struct Packet_Target
{
	cGameObject*	pTarget = nullptr;
	Packet_Target(cGameObject* _pTarget)
		:pTarget(_pTarget)
	{}
};

struct Packet_Party
{
	size_t id;
	Packet_Party(const size_t& _id)
		:id(_id)
	{}
	~Packet_Party()
	{
		
	}
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