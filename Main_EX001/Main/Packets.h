#pragma once

struct PBMSG_HEAD
{
public:
	void Set(LPBYTE lpBuf, BYTE head, BYTE size)
	{
		lpBuf[0] = 0xC1;
		lpBuf[1] = size;
		lpBuf[2] = head;
	}

	void SetE(LPBYTE lpBuf, BYTE head, BYTE size)
	{
		lpBuf[0] = 0xC3;
		lpBuf[1] = size;
		lpBuf[2] = head;
	};

	BYTE c;
	BYTE size;
	BYTE headcode;
};

struct PWMSG_HEAD
{
	BYTE c;
	BYTE sizeH;
	BYTE sizeL;
	BYTE headcode;
};

struct PMSG_DIEPLAYER
{
	PBMSG_HEAD h;
	BYTE NumberH;
	BYTE NumberL;
	BYTE Skill;
	BYTE KillerNumberH;
	BYTE KillerNumberL;
};

struct PMSG_REFILL
{
	PBMSG_HEAD h;
	BYTE IPos;
	BYTE LifeH;
	BYTE LifeL;
	BYTE Flag;
	int Life;
};

struct PMSG_MANASEND
{
	PBMSG_HEAD h;
	BYTE IPos;
	BYTE ManaH;
	BYTE ManaL;
	BYTE BPH;
	BYTE BPL;
	int Mana;
	int BP;
};

struct PMSG_JOINRESULT
{
	PBMSG_HEAD h;
	BYTE scode;
	BYTE result;
	BYTE NumberH;
	BYTE NumberL;
	BYTE CliVersion[5];
};

struct PMSG_CHARINFOMAIN
{
	PBMSG_HEAD h;
	BYTE Code;
	WORD Class;
	int LevelUpPoint;
};

struct PMSG_UPDATECHARACTER
{
	PBMSG_HEAD h;
	BYTE Code;
	DWORD Experience;
	DWORD NextExperience;
	WORD Level;
	int LevelUpPoint;
	WORD Strength;
	WORD Dexterity;
	WORD Vitality;
	WORD Energy;
	WORD Leadership;
	int Life;
	int MaxLife;
	int Mana;
	int MaxMana;
	int BP;
	int MaxBP;
};

struct PMSG_LEVELUP
{
	PBMSG_HEAD h;
	BYTE subcode;
	WORD Level;
	WORD LevelUpPoint;
	WORD MaxLife;
	WORD MaxMana;
	WORD MaxBP;
	short AddPoint;
	short MaxAddPoint;
	short MinusPoint;
	short MaxMinusPoint;

	WORD Strength;
	WORD Dexterity;
	WORD Vitality;
	WORD Energy;
	WORD Leadership;
};

struct PMSG_LVPOINTADDRESULT
{
	PBMSG_HEAD h;
	BYTE subcode;
	BYTE ResultType;
	WORD MaxLifeAndMana;
	WORD MaxBP;
};

struct PMSG_UPDATEPOINTS
{
	PBMSG_HEAD h;
	BYTE subcode;
	int LevelUpPoint;
};

struct PMSG_ATTACKRESULT
{
	PBMSG_HEAD h;
	unsigned char NumberH;
	unsigned char NumberL;
	unsigned char DamageH;
	unsigned char DamageL;
	unsigned char DamageType;
	int AttackDamage;
};

struct PMSG_HEALTHBAR
{
	PWMSG_HEAD h;
	BYTE Code;
	BYTE Count;
};

struct PMSG_HEALTHBAR_INFO
{
	short Index;
	BYTE Rate;
};