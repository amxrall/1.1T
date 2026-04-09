#pragma once

struct sSpeed
{
	bool                    _Sended;
	int                     _Attack;
	int                     _Skill;
	int                     _Moviment;
};

struct sSkill
{
	int                     _Magic;
	int                     _Velocity;
};

class cSpeed
{
public:
	cSpeed();

public:
	bool Load();
	void Connect(int aIndex);
	void Run(LPOBJ lpObj);
	bool Attack(LPOBJ lpObj, LPOBJ Target, class CMagicInf* lpMagic);
	void Skill(LPOBJ lpObj, int Magic);

public:
	bool					_Active;
	int                     _Attack;
	int                     _Moviment;
	int                     _Display[3];
	int                     _Count;

public:
	sSkill			        SkillStruct[1000];

	sSpeed			        SpeedStruct[OBJMAX];
};

extern cSpeed Speed;