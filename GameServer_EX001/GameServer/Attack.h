#pragma once

struct sAttack
{
	int                     _MapNumber;
	int                     _Magic;
};

struct sAttackPlayer
{
	bool                    _Attack;
	bool                    _OffAttack;
	int                     _Time[2];
	int                     _Skill;
};

class cAttack
{
public:
	cAttack();

public:
	bool Load();
	void Connect(int aIndex);
	int Inventory(LPOBJ lpObj, int aIndex);
	bool MapCheck(LPOBJ lpObj);
	bool SkillCheck(LPOBJ lpObj, int Magic);
	void Command(int aIndex, char* msg);
	bool Start(int aIndex, int Attack);
	void Run(LPOBJ lpObj);
	void Finish(int aIndex, char* msg);
	void Check(LPOBJ lpObj, CMagicInf * lpMagic, short Max);

public:
	bool                    _Active;
	int                     _Level;
	int                     _Zen;
	int                     _Count[2];
	int                     _Time[2];
	char                    _Name[255];
	char                    _Syntax[25];

public:
	sAttack			        AttackStruct[1000];

	sAttackPlayer			PlayerStruct[OBJMAX];
};

extern cAttack Attack;