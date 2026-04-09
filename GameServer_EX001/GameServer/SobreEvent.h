#pragma once

struct sSobreEvent
{
	int Day;
	int Hours;
	int Minutes;
	int Time;
	int Class;
};

class cSobreEvent
{
public:
	cSobreEvent();
	~cSobreEvent();

public:
	bool Load();
	bool Check(LPOBJ lpObj, const char* Text);
	void Start(int Time, int Class);
	void Run();
	bool Attack(LPOBJ lpObj, LPOBJ lpTargetObj);
	void Die(LPOBJ lpObj, LPOBJ lpTargetObj);
	void Quit(LPOBJ lpObj);

private:
	bool				_Active;
	char				_Syntax[2][25];
	char                _Notice[255];
	BYTE				_MapNumber;
	BYTE				_X;
	BYTE				_Y;
	BYTE				_State;
	BYTE				_Type;
	int                 _List;
	int			        _Count;
	std::vector<LPOBJ>	_Players;
	char				_Account[11];
	char				_Name[11];

private:
	sSobreEvent			EventStruct[255];

private:
	enum State
	{
		Empty, Register, Progress, Fight, Final
	};
};

extern cSobreEvent SobreEvent;