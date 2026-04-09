#pragma once

struct sDeath
{
	int                  _Day;
	int                  _Hours;
	int                  _Minutes;
	int                  _Duration;
};

struct sDeathPlayer
{
	bool                 _InEvent;
	bool                 _AttackBlock;
	int                  _Kills;
};

class cDeathEvent
{
public:
	cDeathEvent();

public:
	bool Load();
	void Run();
	bool Attack(LPOBJ lpObj, LPOBJ Target);
	void Killer(LPOBJ lpObj, LPOBJ Target);
	void Winner();
	void Finish();
	void Quit(LPOBJ lpObj);

public:
	bool                _Active;
	bool                _Portal;
	bool                _Progress;
	int                 _Level;
	int                 _Zen;
	BYTE                _MapNumber;
	BYTE                _X;
	BYTE                _Y;
	int                 _Count;
	int                 _Value;
	int                 _Players;
	char                _Notice[255];
	char                _Buffer[255];

public:
	sDeath			    DeathStruct[255];

	sDeathPlayer	    PlayerStruct[OBJMAX];
};

extern cDeathEvent DeathEvent;