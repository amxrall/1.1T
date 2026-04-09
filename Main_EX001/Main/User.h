#pragma once

struct	ObjectItem
{
	/*+0*/		short 	ItemID;
	/*+2*/		int		Level;
	/*+6*/		BYTE	Unknown6;
	/*+7*/		BYTE	Unknown7;
	/*+8*/		BYTE	Unknown8;
	/*+9*/		short	DamageMin;
	/*+11*/		short	DamageMax;
	/*+13*/		BYTE	Unknown13;
	/*+14*/		short	Unknown14;
	/*+16*/		short	Unknown16;
	/*+18*/		BYTE	Unknown18;
	/*+19*/		BYTE	Unknown19;
	/*+20*/		short	Unknown20;
	/*+22*/		BYTE	Durability;
	/*+23*/		BYTE	ExcellentOption;
	/*+24*/		BYTE	AncientOption;
	/*+25*/		short	ReqStrenght;
	/*+27*/		short	ReqDextirity;
	/*+29*/		short	ReqEnergy;
	/*+31*/		short	ReqVitality;
	/*+33*/		short	ReqCommand;
	/*+35*/		short	ReqLevel;
	/*+37*/		char    SpecialCount;
	/*+38*/		BYTE	SpecialType[8];
	/*+54*/		BYTE	SpecialValue[8];
	/*+62*/		int		UniqueID;
	/*+66*/		char	Unknown66;
	/*+67*/		char 	PosX;
	/*+68*/		char 	PosY;
	/*+69*/		WORD 	HarmonyType;
	/*+71*/		short	HarmonyValue;
	/*+73*/		char 	Is380Item;
	// -------------------
	DWORD GetTime;
	int aIndex;
	int Life;
	int MaxLife;
	short Reset;
	short VipLevel;
	short MReset;
};

class CUser
{
public:
	ObjectItem m_ItemStat;
};
// ---
extern CUser gUser;