// ------------------------------
// Decompiled by Deathway
// Date : 2007-05-09
// ------------------------------
#ifndef PROTOCOL_H
#define PROTOCOL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "prodef.h"
#include "GuildClass.h"
#include "user.h"
#include "MapClass.h"

extern int iCount;

struct PMSG_ANS_MAPSVRTAXINFO
{
	PBMSG_HEAD2 h;	// C1:B2:1A
	BYTE btTaxType;	// 4
	BYTE btTaxRate;	// 5
};

struct PMSG_KILLPLAYER_EXT
{
	PBMSG_HEAD h;	// C3:9C
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	WORD ExpH;	// 6
	WORD ExpL;	// 8
	BYTE DamageH;	// A
	BYTE DamageL;	// B
};

struct PMSG_ANS_CRYWOLF_BENEFIT_PLUS_CHAOSRATE
{
	PBMSG_HEAD2 h;	// C1:BD:09
	BYTE btPlusChaosRate;	// 4
};

struct PMSG_KEYACCESS
{
	PBMSG_HEAD h;
	BYTE subcode;
	BYTE Keys[7];
};

struct PMSG_JOINRESULT
{
	PBMSG_HEAD h;	// C1:F1
	BYTE scode;	// 3
	BYTE result;	// 4
	BYTE NumberH;	// 5
	BYTE NumberL;	// 6
	BYTE CliVersion[5];	// 7
};

struct PMSG_ANS_DUEL_SCORE
{
	PBMSG_HEAD h;	// C1:AD
	BYTE NumberH1;	// 3
	BYTE NumberL1;	// 4
	BYTE NumberH2;	// 5
	BYTE NumberL2;	// 6
	BYTE btDuelScore1;	// 7
	BYTE btDuelScore2;	// 8
};

struct SDHP_CHARACTER_TRANSFER
{
	PBMSG_HEAD h;	// C1:CF
	char Account[10];	// 3
	short Number;	// E
};

struct PMSG_ANS_CRYWOLF_ALTAR_CONTRACT
{
	PBMSG_HEAD2 h;	// C1:BD:03
	BYTE btResult;	// 4
	BYTE btAltarState;	// 5
	BYTE btObjIndexH;	// 6
	BYTE btObjIndexL;	// 7
};

struct PMSG_REQ_2ANIV_SERIAL
{
	PBMSG_HEAD h;	// C1:08
	int iINDEX;	// 8
	char szUID[MAX_ACCOUNT_LEN + 1];	// 8
	char SERIAL1[5];	// 13
	char SERIAL2[5];	// 18
	char SERIAL3[5];	// 1D
	int iMEMB_GUID;	// 24
};

struct PMSG_RESULT_MOVECHAOSCASTLE
{
	PBMSG_HEAD2 h;	// C1:AF:01
	BYTE Result;	// 4
};

struct PMSG_SETQUEST_PRIZE
{
	PBMSG_HEAD h;	// C1:A3
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	BYTE Type;	// 5
	BYTE Count;	// 6
};

struct PMSG_SETQUEST_RESULT
{
	PBMSG_HEAD h;	// C1:A2
	BYTE QuestIndex;	// 3
	BYTE Result;	// 4
	BYTE State;	// 5
};

struct PMSG_SEND_QEUSTINFO
{
	PBMSG_HEAD h;	// C1:A0
	BYTE Count;	// 3
	BYTE State[50];	// 4
};

struct PMSG_REQ_RESET_EVENTCHIP
{
	PBMSG_HEAD h;	// C1:[04:Rena] [09:Stone]
	int iINDEX;	// 4
	char szUID[11];	// 8
};

struct PMSG_REQ_REGISTER_MUTONUM
{
	PBMSG_HEAD h;	// C1:03
	int iINDEX;	// 4
	char szUID[11];	// 8
};

struct PMSG_REQ_REGISTER_STONES
{
	PBMSG_HEAD h;	// C1:06
	int iINDEX;	// 4
	BYTE iPosition;	// 8
	char szUID[11];	// 9
};

struct PMSG_PING
{
	PBMSG_HEAD h;	// C1:71
};

struct PMSG_RESULT_DEVILSQUARE_REMAINTIME
{
	PBMSG_HEAD h;	// C1:91
	BYTE hEventType;	// 3
	BYTE RemainTime;	// 4
	BYTE EnteredUser;	// 5
	BYTE RemainTime_LOW;	// 6
};

struct PMSG_RESULT_MOVEDEVILSQUARE
{
	PBMSG_HEAD h;	// C1:90
	BYTE Result;	// 3
};

struct PMSG_WEATHER
{
	PBMSG_HEAD h;	// C1:0F
	BYTE Weather;	// 3
};

struct PMSG_ITEMUSESPECIALTIME
{
	PBMSG_HEAD h;	// C1:29
	BYTE Number;	// 3
	WORD Time;	// 4
};

struct PMSG_INVENTORYDELETE
{
	PBMSG_HEAD h;	// C1:28
	BYTE IPos;	// 3
	BYTE Flag;	// 4
};

struct PMSG_CHARINFOMAIN
{
	PBMSG_HEAD h;
	BYTE Code;
	WORD Class;
	int LevelUpPoint;
};

struct PMSG_UPDATEPOINTS
{
	PBMSG_HEAD h;
	BYTE subcode;
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

struct PMSG_MANASEND
{
	PBMSG_HEAD h;	// C1:27
	BYTE IPos;	// 3
	BYTE ManaH;	// 4
	BYTE ManaL;	// 5
	BYTE BPH;	// 6
	BYTE BPL;	// 7
	int Mana;
	int BP;
};

struct PMSG_REFILL
{
	// static data ------------------------------------

	// non-static data --------------------------------
	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char IPos;
	/*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char LifeH;
	/*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char LifeL;
	/*<thisrel this+0x6>*/ /*|0x1|*/ unsigned char Flag;
	int Life;

	// base classes -----------------------------------

	// friends ----------------------------------------

	// static Funcs -------------------------------

	// non-virtual Funcs --------------------------

	// virtual Funcs ------------------------------
};
// <size 0x7>

struct PMSG_USERMAPJOIN
{
	PBMSG_HEAD h;	// C1:F3:03
	BYTE subcode;	// 3
	BYTE NumberH;	// 4
	BYTE NumberL;	// 5
	BYTE X;	// 6
	BYTE Y;	// 7
	BYTE MapNumber;	// 8
	BYTE Dir;	// 9
};

struct PMSG_EFFECTINFO
{
	PBMSG_HEAD h;	// C1:48
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	BYTE btType;	// 5
};

struct PMSG_ANS_GUILDVIEWPORT
{
	PBMSG_HEAD h;	// C1:66
	int GuildNumber;	// 4
	BYTE btGuildType;	// 8
	BYTE UnionName[8];	// 9
	char GuildName[8];	// 11
	BYTE Mark[32];	// 19
};

struct PMSG_ANS_MAPSERVERAUTH
{
	PBMSG_HEAD2 h;	// C1:B1:01
	BYTE iResult;	// 4
};

#if(GS_CASTLE)
struct PMSG_ANS_CASTLESIEGESTATE
{// <size 0x2e>
	/*<thisrel this+0x0>*/ /*|0x4|*/ PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char btResult;
	/*<thisrel this+0x5>*/ /*|0x1|*/ char cCastleSiegeState;
	/*<thisrel this+0x6>*/ /*|0x1|*/ unsigned char btStartYearH;
	/*<thisrel this+0x7>*/ /*|0x1|*/ unsigned char btStartYearL;
	/*<thisrel this+0x8>*/ /*|0x1|*/ unsigned char btStartMonth;
	/*<thisrel this+0x9>*/ /*|0x1|*/ unsigned char btStartDay;
	/*<thisrel this+0xa>*/ /*|0x1|*/ unsigned char btStartHour;
	/*<thisrel this+0xb>*/ /*|0x1|*/ unsigned char btStartMinute;
	/*<thisrel this+0xc>*/ /*|0x1|*/ unsigned char btEndYearH;
	/*<thisrel this+0xd>*/ /*|0x1|*/ unsigned char btEndYearL;
	/*<thisrel this+0xe>*/ /*|0x1|*/ unsigned char btEndMonth;
	/*<thisrel this+0xf>*/ /*|0x1|*/ unsigned char btEndDay;
	/*<thisrel this+0x10>*/ /*|0x1|*/ unsigned char btEndHour;
	/*<thisrel this+0x11>*/ /*|0x1|*/ unsigned char btEndMinute;
	/*<thisrel this+0x12>*/ /*|0x1|*/ unsigned char btSiegeStartYearH;
	/*<thisrel this+0x13>*/ /*|0x1|*/ unsigned char btSiegeStartYearL;
	/*<thisrel this+0x14>*/ /*|0x1|*/ unsigned char btSiegeStartMonth;
	/*<thisrel this+0x15>*/ /*|0x1|*/ unsigned char btSiegeStartDay;
	/*<thisrel this+0x16>*/ /*|0x1|*/ unsigned char btSiegeStartHour;
	/*<thisrel this+0x17>*/ /*|0x1|*/ unsigned char btSiegeStartMinute;
	/*<thisrel this+0x18>*/ /*|0x8|*/ char cOwnerGuild[8];
	/*<thisrel this+0x20>*/ /*|0xa|*/ char cOwnerGuildMaster[10];
	/*<thisrel this+0x2a>*/ /*|0x1|*/ char btStateLeftSec1;
	/*<thisrel this+0x2b>*/ /*|0x1|*/ char btStateLeftSec2;
	/*<thisrel this+0x2c>*/ /*|0x1|*/ char btStateLeftSec3;
	/*<thisrel this+0x2d>*/ /*|0x1|*/ char btStateLeftSec4;
};

struct PMSG_ANS_REGCASTLESIEGE
{ // <size 0xd>
	/*<thisrel this+0x0>*/ /*|0x4|*/ PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char btResult;
	/*<thisrel this+0x5>*/ /*|0x8|*/ char szGuildName[8];
};

struct PMSG_ANS_GIVEUPCASTLESIEGE
{ // <size 0xe>
	/*<thisrel this+0x0>*/ /*|0x4|*/ PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char btResult;
	/*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char btIsGiveUp;
	/*<thisrel this+0x6>*/ /*|0x8|*/ char szGuildName[8];
};

struct PMSG_ANS_GUILDREGINFO
{// <size 0x13>
	/*<thisrel this+0x0>*/ /*|0x4|*/ PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char btResult;
	/*<thisrel this+0x5>*/ /*|0x8|*/ char szGuildName[8];
	/*<thisrel this+0xd>*/ /*|0x1|*/ unsigned char btGuildMark1;
	/*<thisrel this+0xe>*/ /*|0x1|*/ unsigned char btGuildMark2;
	/*<thisrel this+0xf>*/ /*|0x1|*/ unsigned char btGuildMark3;
	/*<thisrel this+0x10>*/ /*|0x1|*/ unsigned char btGuildMark4;
	/*<thisrel this+0x11>*/ /*|0x1|*/ unsigned char btIsGiveUp;
	/*<thisrel this+0x12>*/ /*|0x1|*/ unsigned char btRegRank;
};

struct PMSG_ANS_REGGUILDMARK
{ // <size 0x11>
	/*<thisrel this+0x0>*/ /*|0x4|*/ PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char btResult;
	/*<thisrel this+0x5>*/ /*|0x8|*/ char szGuildName[8];
	/*<thisrel this+0xd>*/ /*|0x1|*/ unsigned char btGuildMark1;
	/*<thisrel this+0xe>*/ /*|0x1|*/ unsigned char btGuildMark2;
	/*<thisrel this+0xf>*/ /*|0x1|*/ unsigned char btGuildMark3;
	/*<thisrel this+0x10>*/ /*|0x1|*/ unsigned char btGuildMark4;
};

struct PMSG_ANS_NPCBUY
{ // <size 0x10>
	/*<thisrel this+0x0>*/ /*|0x4|*/ PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char btResult;
	/*<thisrel this+0x8>*/ /*|0x4|*/ int iNpcNumber;
	/*<thisrel this+0xc>*/ /*|0x4|*/ int iNpcIndex;
};

struct PMSG_ANS_NPCREPAIR
{ // <size 0x18>
	/*<thisrel this+0x0>*/ /*|0x4|*/ PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char btResult;
	/*<thisrel this+0x8>*/ /*|0x4|*/ int iNpcNumber;
	/*<thisrel this+0xc>*/ /*|0x4|*/ int iNpcIndex;
	/*<thisrel this+0x10>*/ /*|0x4|*/ int iNpcHP;
	/*<thisrel this+0x14>*/ /*|0x4|*/ int iNpcMaxHP;
};

struct PMSG_ANS_NPCUPGRADE
{ // <size 0x18>
	/*<thisrel this+0x0>*/ /*|0x4|*/ PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char btResult;
	/*<thisrel this+0x8>*/ /*|0x4|*/ int iNpcNumber;
	/*<thisrel this+0xc>*/ /*|0x4|*/ int iNpcIndex;
	/*<thisrel this+0x10>*/ /*|0x4|*/ int iNpcUpType;
	/*<thisrel this+0x14>*/ /*|0x4|*/ int iNpcUpValue;
};

struct PMSG_ANS_TAXMONEYINFO
{ // <size 0xf>
	/*<thisrel this+0x0>*/ /*|0x4|*/ PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char btResult;
	/*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char btTaxRateChaos;
	/*<thisrel this+0x6>*/ /*|0x1|*/ unsigned char btTaxRateStore;
	/*<thisrel this+0x7>*/ /*|0x1|*/ unsigned char btMoney1;
	/*<thisrel this+0x8>*/ /*|0x1|*/ unsigned char btMoney2;
	/*<thisrel this+0x9>*/ /*|0x1|*/ unsigned char btMoney3;
	/*<thisrel this+0xa>*/ /*|0x1|*/ unsigned char btMoney4;
	/*<thisrel this+0xb>*/ /*|0x1|*/ unsigned char btMoney5;
	/*<thisrel this+0xc>*/ /*|0x1|*/ unsigned char btMoney6;
	/*<thisrel this+0xd>*/ /*|0x1|*/ unsigned char btMoney7;
	/*<thisrel this+0xe>*/ /*|0x1|*/ unsigned char btMoney8;
};

struct PMSG_ANS_TAXRATECHANGE
{// <size 0xa>
	/*<thisrel this+0x0>*/ /*|0x4|*/ PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char btResult;
	/*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char btTaxType;
	/*<thisrel this+0x6>*/ /*|0x1|*/ unsigned char btTaxRate1;
	/*<thisrel this+0x7>*/ /*|0x1|*/ unsigned char btTaxRate2;
	/*<thisrel this+0x8>*/ /*|0x1|*/ unsigned char btTaxRate3;
	/*<thisrel this+0x9>*/ /*|0x1|*/ unsigned char btTaxRate4;
};

struct PMSG_ANS_MONEYDRAWOUT
{// <size 0xd>
	/*<thisrel this+0x0>*/ /*|0x4|*/ PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char btResult;
	/*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char btMoney1;
	/*<thisrel this+0x6>*/ /*|0x1|*/ unsigned char btMoney2;
	/*<thisrel this+0x7>*/ /*|0x1|*/ unsigned char btMoney3;
	/*<thisrel this+0x8>*/ /*|0x1|*/ unsigned char btMoney4;
	/*<thisrel this+0x9>*/ /*|0x1|*/ unsigned char btMoney5;
	/*<thisrel this+0xa>*/ /*|0x1|*/ unsigned char btMoney6;
	/*<thisrel this+0xb>*/ /*|0x1|*/ unsigned char btMoney7;
	/*<thisrel this+0xc>*/ /*|0x1|*/ unsigned char btMoney8;
};

struct PMSG_ANS_CSGATESTATE
{// <size 0x7>
	/*<thisrel this+0x0>*/ /*|0x4|*/ PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char btResult;
	/*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char btIndex1;
	/*<thisrel this+0x6>*/ /*|0x1|*/ unsigned char btIndex2;
};

struct PMSG_ANS_CSGATEOPERATE
{// <size 0x8>
	/*<thisrel this+0x0>*/ /*|0x4|*/ PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char btResult;
	/*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char btOperate;
	/*<thisrel this+0x6>*/ /*|0x1|*/ unsigned char btIndex1;
	/*<thisrel this+0x7>*/ /*|0x1|*/ unsigned char btIndex2;
};

struct PMSG_ANS_CSGATECURSTATE
{// <size 0x7>
	/*<thisrel this+0x0>*/ /*|0x4|*/ PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char btOperate;
	/*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char btIndex1;
	/*<thisrel this+0x6>*/ /*|0x1|*/ unsigned char btIndex2;
};

struct PMSG_ANS_NOTIFYSWITCHPROC
{ // <size 0x9>
	/*<thisrel this+0x0>*/ /*|0x4|*/ PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char btIndex1;
	/*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char btIndex2;
	/*<thisrel this+0x6>*/ /*|0x1|*/ unsigned char btUserIndex1;
	/*<thisrel this+0x7>*/ /*|0x1|*/ unsigned char btUserIndex2;
	/*<thisrel this+0x8>*/ /*|0x1|*/ unsigned char btSwitchState;
};

struct PMSG_ANS_NOTIFYCROWNPROC
{// <size 0xc>
	/*<thisrel this+0x0>*/ /*|0x4|*/ PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char btCrownState;
	/*<thisrel this+0x8>*/ /*|0x4|*/ unsigned long dwAccumulatedCrownAccessTime;
};

struct PMSG_ANS_CSCOMMAND
{// <size 0x8>
	/*<thisrel this+0x0>*/ /*|0x4|*/ PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char btTeam;
	/*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char btX;
	/*<thisrel this+0x6>*/ /*|0x1|*/ unsigned char btY;
	/*<thisrel this+0x7>*/ /*|0x1|*/ unsigned char btCommand;
};

struct PMSG_ANS_NPCDBLIST
{// <size 0xc>
	/*<thisrel this+0x0>*/ /*|0x4|*/ PWMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char btResult;
	/*<thisrel this+0x8>*/ /*|0x4|*/ int iCount;
};

struct PMSG_ANS_CSATTKGUILDLIST
{ // <size 0xc>
	/*<thisrel this+0x0>*/ /*|0x4|*/ PWMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char btResult;
	/*<thisrel this+0x8>*/ /*|0x4|*/ int iCount;
};

struct PMSG_NOTIFY_OBJECT_CREATION_STATE
{
	// static data ------------------------------------

	// non-static data --------------------------------
	/*<thisrel this+0x0>*/ /*|0x4|*/ struct PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char btObjIndexH;
	/*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char btObjIndexL;
	/*<thisrel this+0x6>*/ /*|0x1|*/ unsigned char btCreationState;
};

struct PMSG_ANS_MOVE_TO_CASTLE_HUNTZONE // 0x5
{
	PBMSG_HEAD2 h; // +0x0(0x4)
	BYTE btResult; // +0x4(0x1)
};

#endif

struct PMSG_ANS_GUILDMARK_OF_CASTLEOWNER
{
	PBMSG_HEAD2 h;	// C1:B9:02
	BYTE GuildMarkOfCastleOwner[32];	// 4
};

struct PMSG_ANS_USEWEAPON
{
	PBMSG_HEAD2 h;	// C1:B7:01
	BYTE btResult;	// [1:Attacker] [2:Targets]	4
	BYTE btObjIndexH;	// 5
	BYTE btObjIndexL;	// 6
	BYTE btWeaponType;	// [1:Slingshot attack] [2:Slingshot defense]	7
	BYTE btPointX;	// 8
	BYTE btPointY;	// 9
};

struct PMSG_ANS_CSHUNTZONEENTER
{
	PBMSG_HEAD2 h;	// C1:B2:1F
	BYTE btResult;	// 4
	BYTE btHuntZoneEnter;	// 5
};

struct PMSG_ANS_NOTIFYCSPROGRESS
{
	PBMSG_HEAD2 h;	// C1:B2:18
	BYTE btCastleSiegeState;	// 4
	BYTE szGuildName[8];	// 5
};

struct PMSG_ANS_JEWEL_UNMIX
{
	PBMSG_HEAD2 h;	// C1:BC:[00:01]
	BYTE btResult;	// 4
};

struct PMSG_ANS_MINIMAPDATA
{
	PBMSG_HEAD2 h;
	BYTE btResult;	// 4
};

struct PMSG_ANS_CSLEFTTIMEALARM
{
	PBMSG_HEAD2 h;	// C1:B2:1E
	BYTE btHour;	// 4
	BYTE btMinute;	// 5
};
struct PMSG_GETITEMINFO_FOR_PARTY
{
	PBMSG_HEAD h;	// C1:47
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	UINT ItemInfo;	// 8
	BYTE Level;	// C
};

struct PMSG_ITEMDUR
{
	PBMSG_HEAD h;	// C1:2A
	BYTE IPos;	// 3
	BYTE Dur;	// 4
	BYTE Flag;	// 5
};

struct PMSG_REQ_REGISTER_EVENTCHIP
{
	PBMSG_HEAD h;	// C1:02
	int iINDEX;	// 4
	BYTE Pos;	// 8
	char szUID[11];	// 9
};

struct PMSG_RESULT_MOVEBLOODCASTLE
{
	PBMSG_HEAD h;	// C1:9A
	BYTE Result;	// 3
};

struct PMSG_ANS_START_DUEL
{
	PBMSG_HEAD h;	// C1:AA
	bool bDuelStart;	// 3
	BYTE NumberH;	// 4
	BYTE NumberL;	// 5
	char szName[10];	// 6
};

struct PMSG_REQ_DUEL_OK
{
	PBMSG_HEAD h;	// C1:AC
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	char szName[10];	// 5
};

struct PMSG_TELEPORT_RESULT
{
	PBMSG_HEAD h;	// C3:1C
	BYTE MoveNumber;	// 3
	BYTE MapNumber;	// 4
	BYTE MapX;	// 5
	BYTE MapY;	// 6
	BYTE Dir;	// 7
};

struct SDHP_IDPASS
{
	PBMSG_HEAD h;	// C1:01	[11::LOGIN-TEST]
	char Account[10];	// 3
	char Password[10];	// D
	short Number;	// 18
	char IpAddress[17];	// 1A
};

struct SDHP_BILLSEARCH
{
	PBMSG_HEAD h;	// C1:06
	char Id[10];	// 3
	short Number;	// E
};

struct SDHP_CREATECHAR
{
	PBMSG_HEAD h;	// C1:04
	int UserNumber;	// 4
	int DBNumber;	// 8
	short Number;	// C
	char AccountId[10];	// E
	char Name[10];	// 18
	BYTE ClassSkin;	// 22
};

struct SDHP_CHARDELETE
{
	PBMSG_HEAD h;	// C1:05
	short Number;	// 4
	char AccountID[10];	// 6
	char Name[10];	// 10
	BYTE Guild;	// [0:NoGuild] [1:Master] [2:Member] 1A
	char GuildName[8];	// 1B
};

struct PMSG_LVPOINTADDRESULT
{
	// static data ------------------------------------

	// non-static data --------------------------------
	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char subcode;
	/*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char ResultType;
	/*<thisrel this+0x6>*/ /*|0x2|*/ unsigned short MaxLifeAndMana;
	/*<thisrel this+0x8>*/ /*|0x2|*/ unsigned short MaxBP;

	// base classes -----------------------------------

	// friends ----------------------------------------

	// static Funcs -------------------------------

	// non-virtual Funcs --------------------------

	// virtual Funcs ------------------------------
};
// <size 0xa>

struct PMSG_PKLEVEL
{
	PBMSG_HEAD h;	// C1:F3:08
	BYTE subcode;	// 3
	BYTE NumberH;	// 4
	BYTE NumberL;	// 5
	BYTE PkLevel;	// 6
};

struct PMSG_MAGICLIST
{
	char Pos;	// 0
	BYTE MagicInfo[MAX_MAGIC_INFO];	// 1
};

struct PMSG_MAGICLISTCOUNT
{
	PBMSG_HEAD h;	// C1:F3:11
	BYTE subcode;	// 3
	BYTE Count;	// [0xFE:AddOne] [0xFF:DelOne] 4
	BYTE btListType;	// 5
};

struct PMSG_EQUIPMENTLIST
{
	PBMSG_HEAD h;	// C1:F3:13
	BYTE subcode;	// 3
	BYTE NumberH;	// 4
	BYTE NumberL;	// 5
	BYTE Equipment[CHAR_SET_SIZE];	// 6
};

struct PMSG_RECALLMONLIFE
{
	PBMSG_HEAD h;	// C1:F3:20
	BYTE subcode;	// 3
	BYTE Life;	// 4
};

struct PMSG_TIMEVIEW
{
	PBMSG_HEAD h;	// C1:F3:22
	BYTE subcode;	// 3
	WORD Second;	// 4
};

struct PMSG_GOALSEND
{
	PBMSG_HEAD h;	// C1:F3:23
	BYTE subcode;	// 3
	char RedTeamName[8];	// 4
	BYTE RedTeamScore;	// C
	char BlueTeamName[8];	// D
	BYTE BlueTeamScore;	// 15
};

struct PMSG_GUILDWARSEND
{
	PBMSG_HEAD h;	// C1:61
	char GuildName[8];	// 3
	BYTE Type;	// B
};

struct PMSG_ITEMGETRESULT
{
	PBMSG_HEAD h;	// C1:22
	BYTE result;	// [0xFE:Money] 3
	BYTE Data[MAX_ITEM_INFO];	// 4
};

struct PMSG_INVENTORYITEMMODIFY
{
	PBMSG_HEAD h;	// C1:F3:14
	BYTE subcode;	// 3
	BYTE Pos;	// 4
	BYTE ItemInfo[MAX_ITEM_INFO];	// 5
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

struct PMSG_SERVERMSG
{
	PBMSG_HEAD h;	// C1:0C
	BYTE MsgNumber;	// 3
};

struct PMSG_EVENT
{
	PBMSG_HEAD h;	// C1:0B
	BYTE State;	// 3
	BYTE Event;	// 4
};

struct CHAT_LOG_DATA
{
	PBMSG_HEAD h;	// C1:02
	WORD wServer;	// 4
	char AccountID[11];	// 6
	char Name[11];	// 11
	BYTE btType;	// 1C
	char szChatMsg[61];	// 1D
	char szTargetName[5][11];	// 5A
};

struct PMSG_GUILDMASTERMANAGER_RUN
{
	PBMSG_HEAD h;	// C1:55
};

struct PMSG_GUILDMASTERQUESTION
{
	PBMSG_HEAD h;	// C1:54
};

struct PMSG_CHECK_MAINEXE
{
	PBMSG_HEAD h;	// C1:03
	WORD m_wKey;	// 4
};

struct PMSG_ANS_END_DUEL
{
	PBMSG_HEAD h;	// C1:AB
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	char szName[10];	// 5
};

/* * * * * * * * * * * * * * * * * * * * *
 *	Mu Send Warehouse Info Packet
 *	Direction : GameServer -> Client
 *  Code      : 0xC3
 *	HeadCode  : 0x30
 */
struct PMSG_TALKRESULT
{
	PBMSG_HEAD h;
	unsigned char result;	// 3
	BYTE level1;	// 4
	BYTE level2;	// 5
	BYTE level3;	// 6
	BYTE level4;	// 7
	BYTE level5;	// 8
	BYTE level6;	// 9
};

/* * * * * * * * * * * * * * * * * * * * *
 *	Mu Result Packet
 *	Direction : GameServer -> Client
 *  Code     : 0xC1
 *	HeadCode : 0xF3
 *	SubCode  : 0x02
 */
struct PMSG_RESULT
{
	PBMSG_HEAD h;
	unsigned char subcode;	// 3
	unsigned char result;	// 4
};

/* * * * * * * * * * * * * * * * * * * * *
 *	Packet to Send Blod Castle State
 *	Direction : GameServer -> Client
 *	Code      : 0xC1
 *	HeadCode  : 0x9B
 */
struct PMSG_STATEBLOODCASTLE
{
	PBMSG_HEAD h;	// C1:9B
	BYTE btPlayState;		// 3
	WORD wRemainSec;	// 4
	WORD wMaxKillMonster;	// 6
	WORD wCurKillMonster;	// 8
	WORD wUserHaveWeapon;	// A
	BYTE btWeaponNum;	// C
};

struct PMSG_KILLCOUNT
{
	PBMSG_HEAD2 h;
	BYTE btKillCount;
};

struct SDHP_DBCHARINFOREQUEST
{
	PBMSG_HEAD h;	// C1:06
	char AccountID[11];	// 3
	char Name[11];	// E
	short Number;	// 1A
};

struct PMSG_ATTACKRESULT
{
	// static data ------------------------------------

	// non-static data --------------------------------
	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char NumberH;
	/*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char NumberL;
	/*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char DamageH;
	/*<thisrel this+0x6>*/ /*|0x1|*/ unsigned char DamageL;
	/*<thisrel this+0x7>*/ /*|0x1|*/ unsigned char DamageType;
	int AttackDamage;

	// base classes -----------------------------------

	// friends ----------------------------------------

	// static Funcs -------------------------------

	// non-virtual Funcs --------------------------

	// virtual Funcs ------------------------------
};
// <size 0x8>

struct PMSG_RECV_POSISTION_SET
{
	PBMSG_HEAD h;	// C1:D6
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	BYTE X;	// 5
	BYTE Y;	// 6
};

struct PMSG_USEREQUIPMENTCHANGED
{
	PBMSG_HEAD h;
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	BYTE ItemInfo[MAX_ITEM_INFO];	// 5
};

struct PMSG_SERVERCMD
{
	PBMSG_HEAD h;
	BYTE subcode;	// 3
	BYTE CmdType;	// 4
	BYTE X;	// 5
	BYTE Y;	// 6
};

struct PMSG_ITEMTHROW_RESULT
{
	PBMSG_HEAD h;	// C1:23
	unsigned char Result;	// 3
	BYTE Ipos;	// 4
};

struct PMSG_GUILDCREATED_RESULT
{
	PBMSG_HEAD h;	// C1:56
	BYTE Result;	// 3
	BYTE btGuildType;	// 4
};

struct PMSG_SIMPLE_GUILDVIEWPORT_COUNT
{
	PWMSG_HEAD h;	// C2:65
	BYTE Count;	// 4
};

struct PMSG_SIMPLE_GUILDVIEWPORT
{
	int GuildNumber;	// 0
	BYTE btGuildStatus;	// 4
	BYTE btGuildType;	// 5
	BYTE btGuildRelationShip;	// 6
	BYTE NumberH;	// 7
	BYTE NumberL;	// 8
};

struct PMSG_RECVMOVE
{
	PBMSG_HEAD h;
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	BYTE X;	// 5
	BYTE Y;	// 6
	BYTE Path;	// 7
};

struct PMSG_MAGICATTACK_RESULT
{
	PBMSG_HEAD h;	// C3:19
	BYTE MagicNumber;	// 3
	BYTE SourceNumberH;	// 4
	BYTE SourceNumberL;	// 5
	BYTE TargetNumberH;	// 6
	BYTE TargetNumberL;	// 7
};

struct PMSG_BEATTACK_COUNT
{
	PBMSG_HEAD h;	// C1:D7
	BYTE MagicNumber;	// 3
	BYTE X;	// 4
	BYTE Y;	// 5
	BYTE Serial;	// 6
	BYTE Count;	// 7
};

struct PMSG_BEATTACK
{
	BYTE NumberH;	// 0
	BYTE NumberL;	// 1
	BYTE MagicKey;	// 2
};

struct PMSG_SET_DEVILSQUARE
{
	PBMSG_HEAD h;	// C1:92
	BYTE Type;	// 3
};

struct PMSG_GUILD_ASSIGN_STATUS_RESULT
{
	PBMSG_HEAD h;	// C1:E1
	BYTE btType;	// 3
	BYTE btResult;	// 4
	char szTagetName[10];	// 5
};

struct PMSG_GUILD_ASSIGN_TYPE_RESULT
{
	PBMSG_HEAD h;	// C1:E2
	BYTE btGuildType;	// 3
	BYTE btResult;	// 4
};

//////////////////////////////////////////////////////////////////////////////
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//////////////////////////////////////////////////////////////////////////////

struct PMSG_CLIENTTIME
{
	PBMSG_HEAD h;
	DWORD Time;	// 4
	WORD AttackSpeed;	// 8
	WORD MagicSpeed;	// A
};

struct PMSG_CHECK_MAINEXE_RESULT
{
	PBMSG_HEAD h;
	DWORD m_dwKey;	// 4
};

struct PMSG_CHATDATA
{
	PBMSG_HEAD h;	//
	char chatid[10];	//	3
	char chatmsg[60];	//	D
};

struct PMSG_CHATDATA_NUMBER
{
	PBMSG_HEAD h;
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	char chatmsg[60];	// 5
};

struct PMSG_CHATDATA_WHISPER
{
	PBMSG_HEAD h;	// C1:02
	char id[10];	// 3
	char chatmsg[60];	// D
};

struct PMSG_IDPASS
{
	PBMSG_HEAD h;
	BYTE subcode;	// 3
	char Account[10];	// 4
	char Password[10];	// E
	DWORD TickCount;	// 18
	BYTE ClientVersion[5]; // 1C
	BYTE ClientSerial[16]; // 21
};

struct PMSG_CLIENTCLOSE
{
	PBMSG_HEAD h;
	BYTE SubCode;	// 3
	BYTE Flag;	// 4
};

struct PMSG_CLIENTMSG
{
	PBMSG_HEAD h;
	BYTE SubCode;	// 3
	BYTE Flag;	// 4
	BYTE subFlag;	// 5
};

struct PMSG_CHARCREATE
{
	PBMSG_HEAD h;
	BYTE subcode;	// 3
	char Name[10];	// 4
	BYTE ClassSkin;	// E
};

struct PMSG_CHARDELETE
{
	PBMSG_HEAD h;
	BYTE subcode;	// 3
	char Name[10];	// 4
	char LastJoominNumber[10];	// E
};

struct PMSG_CHARMAPJOIN
{
	PBMSG_HEAD h;
	BYTE subcode;	// 3
	char Name[10];	// 4
};

struct PMSG_LVPOINTADD
{
	PBMSG_HEAD h;
	BYTE subcode;	// 3
	BYTE Type;	// 4
};

struct PMSG_SKILLKEY
{
	PBMSG_HEAD h;	// C1:F3:30
	BYTE subcode;	// 3
	BYTE SKillKey[10];	// 4
	BYTE GameOption;	// E
	BYTE QkeyDefine;	// F
	BYTE WkeyDefine;	// 10
	BYTE EkeyDefine;	// 11
	BYTE ChatWindow;	// 12
};

struct PMSG_ITEMGETREQUEST
{
	PBMSG_HEAD h;
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
};

struct PMSG_ITEMTHROW
{
	PBMSG_HEAD h;
	BYTE px;	// 3
	BYTE py;	// 4
	BYTE Ipos;	// 5
};

struct PMSG_INVENTORYITEMMOVE
{
	PBMSG_HEAD h;
	BYTE sFlag;	// 3
	BYTE source_item_num;	// 4
	BYTE sItemInfo[MAX_ITEM_INFO];	// 5
	BYTE tFlag;	// C
	BYTE target_item_num;	// D
};

struct PMSG_TALKREQUEST
{
	PBMSG_HEAD h;
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
};

struct PMSG_BUYREQUEST
{
	PBMSG_HEAD h;
	BYTE Pos;	// 3
};

struct PMSG_SELLREQUEST
{
	PBMSG_HEAD h;
	BYTE Pos;	// 3
};

struct PMSG_ITEMDURREPAIR
{
	PBMSG_HEAD h;
	BYTE Position;	// [0xFF:Repair ALL] 3
	BYTE Requestpos;	// 4
};

struct PMSG_TRADE_REQUEST
{
	PBMSG_HEAD h;
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
};

struct PMSG_TRADE_RESPONSE
{
	PBMSG_HEAD h;	// C1:37
	BYTE Response;	// 3
	BYTE Id[10];	// 4
	WORD Level;	// E
	int GuildNumber;	// 10
};

struct PMSG_TRADE_GOLD
{
	PBMSG_HEAD h;
	DWORD Money;	// 4
};

struct PMSG_TRADE_OKBUTTON
{
	PBMSG_HEAD h;	// C1:3C
	BYTE Flag;	// 3
};

struct PMSG_REQ_PSHOP_SETITEMPRICE
{
	PBMSG_HEAD2 h;
	BYTE btItemPos;	// 4
	BYTE sItemPrice1;	// 5
	BYTE sItemPrice2;	// 6
	BYTE sItemPrice3;	// 7
	BYTE sItemPrice4;	// 8
};

struct PMSG_REQ_PSHOP_OPEN
{
	PBMSG_HEAD2 h;
	char szPShopText[36];	// 4
};

struct PMSG_REQ_BUYLIST_FROM_PSHOP
{
	PBMSG_HEAD2 h;
	BYTE NumberH;	// 4
	BYTE NumberL;	// 5
	BYTE btName[10];	// 6
};

struct PMSG_REQ_BUYITEM_FROM_PSHOP
{
	PBMSG_HEAD2 h;
	BYTE NumberH;	// 4
	BYTE NumberL;	// 5
	BYTE btName[10];	// 6
	BYTE btItemPos;	// 10
};

struct PMSG_REQ_PSHOPDEAL_CLOSE
{
	PBMSG_HEAD2 h;
	BYTE NumberH;	// 4
	BYTE NumberL;	// 5
	BYTE btName[10];	// 6
};

struct PMSG_PARTYREQUEST
{
	PBMSG_HEAD h;
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
};

struct PMSG_PARTYREQUESTRESULT
{
	PBMSG_HEAD h;
	BYTE Result;	// 3
	BYTE NumberH;	// 4
	BYTE NumberL;	// 5
};

struct PMSG_PARTYDELUSER
{
	PBMSG_HEAD h;
	BYTE Number;	// 3
};

struct PMSG_GUILDJOINQ
{
	PBMSG_HEAD h;
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
};

struct PMSG_GUILDQRESULT
{
	PBMSG_HEAD h;
	BYTE Result;	// 3
	BYTE NumberH;	// 4
	BYTE NumberL;	// 5
};

struct PMSG_GUILDDELUSER
{
	PBMSG_HEAD h;
	char Name[10];	// 3
	char JoominNumber[10];	// D
};

struct PMSG_GUILDMASTERANSWER
{
	PBMSG_HEAD h;
	BYTE Result;	// 3
};

struct PMSG_GUILDINFOSAVE
{
	PBMSG_HEAD h;
	BYTE btGuildType;	// 3
	char GuildName[8];	// 4
	BYTE Mark[32];	// C
};

struct PMSG_GUILDWARSEND_RESULT
{
	PBMSG_HEAD h;
	BYTE Result;	// 3
};

struct PMSG_WAREHOUSEMONEYINOUT
{
	PBMSG_HEAD h;
	BYTE Type;	// [0x01:Deposit] [0x02:Withdraw] 3
	int Money;	// 4
};

struct PMSG_WAREHOUSEPASSSEND
{
	PBMSG_HEAD h;
	BYTE Type;	// [0x00:Open Warehouse] [0x01:Set Pass] [0x02:Delete Pass] 3
	short Pass;	// 4
	char LastJoominNumber[10];	// 6
};

struct PMSG_CHAOSMIX
{
	PBMSG_HEAD h;
	BYTE Type;	// 3
};

struct PMSG_MOVE
{
	PBMSG_HEAD h;	// C1:1D
	BYTE X;	// 3
	BYTE Y;	// 4
	BYTE Path[8];	// 5
};

struct PMSG_POSISTION_SET
{
	PBMSG_HEAD h;
	BYTE X;	// 3
	BYTE Y;	// 4
};

struct PMSG_ATTACK
{
	PBMSG_HEAD h;
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	BYTE AttackAction;	// 5
	BYTE DirDis;	// 6
};

struct PMSG_ACTION
{
	PBMSG_HEAD h;
	BYTE Dir;	// 3
	BYTE ActionNumber;	// 4
	BYTE iTargetIndexH;	// 5
	BYTE iTargetIndexL;	// 6
};

struct PMSG_MAGICATTACK
{
	PBMSG_HEAD h;
	BYTE MagicNumber;	// 3
	BYTE NumberH;	// 4
	BYTE NumberL;	// 5
	BYTE Dis;	// 6
};

struct PMSG_MAGICCANCEL
{
	PBMSG_HEAD h;
	BYTE MagicNumber;	// 3
	BYTE NumberH;	// 4
	BYTE NumberL;	// 5
};

struct PMSG_TELEPORT
{
	PBMSG_HEAD h;
	BYTE MoveNumber;	// 3
	BYTE MapX;	// 4
	BYTE MapY;	// 5
};

struct PMSG_TARGET_TELEPORT
{
	PBMSG_HEAD h;
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	BYTE MapX;	// 5
	BYTE MapY;	// 6
};

struct PMSG_DURATION_MAGIC_RECV
{
	PBMSG_HEAD h;
	BYTE MagicNumber;	// 3
	BYTE X;	// 4
	BYTE Y;	// 5
	BYTE Dir;	// 6
	BYTE Dis;	// 7
	BYTE TargetPos;	// 8
	BYTE NumberH;	// 9
	BYTE NumberL;	// A
	BYTE MagicKey;	// B
};

struct PMSG_USEITEM
{
	PBMSG_HEAD h;
	BYTE inventoryPos;	// 3
	BYTE invenrotyTarget;	// 4
	BYTE btItemUseType;	// 5
};

struct PMSG_REQ_MOVEDEVILSQUARE
{
	PBMSG_HEAD h;
	BYTE SquareNumber;	// 3
	BYTE InvitationItemPos;	// 4
};

struct PMSG_REQ_DEVILSQUARE_REMAINTIME
{
	PBMSG_HEAD h;
	BYTE hEventType;	// 3
	BYTE btItemLevel;	// 4
};

struct PMSG_PING_RESULT
{
	PBMSG_HEAD h;
};

struct PMSG_REGEVENTCHIP
{
	PBMSG_HEAD h;
	BYTE Type;	// 3
	BYTE ChipPos;	// 4
};

struct PMSG_GETMUTONUMBER
{
	PBMSG_HEAD h;
};

struct PMSG_EXCHANGE_EVENTCHIP
{
	PBMSG_HEAD h;
	BYTE btType;	// [0x00:Change Renas] [0x01:Change Stones]	3
};

struct PMSG_SETQUEST
{
	PBMSG_HEAD h;	// C1:A1
	BYTE QuestIndex;	// 3
	BYTE State;	// 4
};

struct PMSG_REQ_MOVEBLOODCASTLE
{
	PBMSG_HEAD h;
	BYTE iBridgeNumber;	// 3
	BYTE iItemPos;	// 4
};

struct PMSG_REQ_MOVECHAOSCASTLE
{
	PBMSG_HEAD2 h;
	BYTE iChaosCastleNumber;	// 4
	BYTE iItemPos;	// 5
};

struct PMSG_REQ_REPOSUSER_IN_CC
{
	PBMSG_HEAD2 h;
	BYTE btPX;	// 4
	BYTE btPY;	// 5
};

struct PMSG_REQ_CL_ENTERCOUNT
{
	PBMSG_HEAD h;
	BYTE btEventType;	// 3
};

struct PMSG_REQ_2ANV_LOTTO_EVENT
{
	PBMSG_HEAD h;
	char SERIAL1[5];	// 3
	char SERIAL2[5];	// 8
	char SERIAL3[5];	// D
};

struct PMSG_REQ_MOVE_OTHERSERVER
{
	PBMSG_HEAD h;
	char LastJoominNumber[10];	// 3
};

struct PMSG_PACKETCHECKSUM
{
	PBMSG_HEAD h;
	BYTE funcindex;	// 3
	DWORD CheckSum;	// 4
};

/*
struct _GG_AUTH_DATA
{
	unsigned long dwIndex;
	unsigned long dwValue1;
	unsigned long dwValue2;
	unsigned long dwValue3;
};
*/

struct PMSG_REQ_START_DUEL
{
	PBMSG_HEAD h;
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	char szName[10];	// 5
};

struct PMSG_REQ_END_DUEL
{
	PBMSG_HEAD h;
};

struct PMSG_ANS_DUEL_OK
{
	PBMSG_HEAD h;
	bool bDuelOK;	// 3
	BYTE NumberH;	// 4
	BYTE NumberL;	// 5
	char szName[10];	// 6
};

struct PMSG_REQUEST_PET_ITEM_COMMAND
{
	PBMSG_HEAD h;
	BYTE PetType;	// 3
	BYTE Command;	// 4
	BYTE NumberH;	// 5
	BYTE NumberL;	// 6
};

struct PMSG_REQUEST_PET_ITEMINFO
{
	PBMSG_HEAD h;
	BYTE PetType;	// 3
	BYTE InvenType;	// 4
	BYTE nPos;	// 5
};

struct PMSG_REQ_GUILDVIEWPORT
{
	PBMSG_HEAD h;
	int GuildNumber;	// 4
};

struct PMSG_GUILD_ASSIGN_STATUS_REQ
{
	PBMSG_HEAD h;
	BYTE btType;	// 3
	BYTE btGuildStatus;	// 4
	char szTagetName[10];	// 5
};

struct PMSG_GUILD_ASSIGN_TYPE_REQ
{
	PBMSG_HEAD h;
	BYTE btGuildType;	// 3
};

struct PMSG_RELATIONSHIP_JOIN_BREAKOFF_REQ
{
	PBMSG_HEAD h;	// C1:E5
	BYTE btRelationShipType;	// 3
	BYTE btRequestType;	// 4
	BYTE btTargetUserIndexH;	// 5
	BYTE btTargetUserIndexL;	// 6
};

struct PMSG_RELATIONSHIP_JOIN_BREAKOFF_ANS
{
	PBMSG_HEAD h;	// C1:E6
	BYTE btRelationShipType;	// 3
	BYTE btRequestType;	// 4
	BYTE btResult;	// 5
	BYTE btTargetUserIndexH;	// 6
	BYTE btTargetUserIndexL;	// 7
};

struct PMSG_UNIONLIST_REQ
{
	PBMSG_HEAD h;
};

struct PMSG_KICKOUT_UNIONMEMBER_REQ
{
	PBMSG_HEAD2 h;
	char szTargetGuildName[8];	// 4
};

struct PMSG_REQ_MAPSERVERAUTH
{
	PBMSG_HEAD2 h;
	char Account[12];	// 4
	char Name[12];	// 10
	int iJoinAuthCode1;	// 1C
	int iJoinAuthCode2;	// 20
	int iJoinAuthCode3;	// 24
	int iJoinAuthCode4;	// 28
	int iTickCount;	// 2C
	BYTE ClientVersion[5]; // 30
	BYTE ClientSerial[16]; // 35
};

struct PMSG_REQ_CASTLESIEGESTATE
{
	/*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
};

struct PMSG_REQ_REGCASTLESIEGE
{
	/*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
};

struct PMSG_REQ_GIVEUPCASTLESIEGE
{
	/*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ BYTE btGiveUp;
};

struct PMSG_REQ_GUILDREGINFO
{
	/*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
};

struct CSP_ANS_GUILDREGINFO
{
	PBMSG_HEAD2 h;
	int iResult;	// 4
	WORD wMapSvrNum;	// 8
	int iIndex;	// C
	char szGuildName[8];	// 10
	int iRegMarkCount;	// 18
	unsigned char bIsGiveUp;	// 1C
	BYTE btRegRank;	// 1D
};

struct PMSG_REQ_REGGUILDMARK
{
	/*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ BYTE btItemPos;
};

struct CSP_ANS_GUILDREGMARK
{
	// static data ------------------------------------

	// non-static data --------------------------------
	/*<thisrel this+0x0>*/ /*|0x4|*/ struct PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x4|*/ int iResult;
	/*<thisrel this+0x8>*/ /*|0x2|*/ unsigned short wMapSvrNum;
	/*<thisrel this+0xc>*/ /*|0x4|*/ int iIndex;
	/*<thisrel this+0x10>*/ /*|0x8|*/ char szGuildName[8];
	/*<thisrel this+0x18>*/ /*|0x4|*/ int iItemPos;
	/*<thisrel this+0x1c>*/ /*|0x4|*/ int iRegMarkCount;

	// base classes -----------------------------------

	// friends ----------------------------------------

	// static Funcs -------------------------------

	// non-virtual Funcs --------------------------

	// virtual Funcs ------------------------------
};
// <size 0x20>

struct PMSG_REQ_NPCBUY
{
	/*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x4|*/ int iNpcNumber;
	/*<thisrel this+0x8>*/ /*|0x4|*/ int iNpcIndex;
};

struct PMSG_REQ_NPCREPAIR
{
	/*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x4|*/ int iNpcNumber;
	/*<thisrel this+0x8>*/ /*|0x4|*/ int iNpcIndex;
};

struct PMSG_REQ_NPCUPGRADE
{
	/*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x4|*/ int iNpcNumber;
	/*<thisrel this+0x8>*/ /*|0x4|*/ int iNpcIndex;
	/*<thisrel this+0xc>*/ /*|0x4|*/ int iNpcUpType;
	/*<thisrel this+0x10>*/ /*|0x4|*/ int iNpcUpValue;
};

struct PMSG_REQ_TAXMONEYINFO
{
	/*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
};

struct PMSG_REQ_TAXRATECHANGE
{
	/*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ BYTE btTaxType;
	/*<thisrel this+0x5>*/ /*|0x1|*/ BYTE btTaxRate1;
	/*<thisrel this+0x6>*/ /*|0x1|*/ BYTE btTaxRate2;
	/*<thisrel this+0x7>*/ /*|0x1|*/ BYTE btTaxRate3;
	/*<thisrel this+0x8>*/ /*|0x1|*/ BYTE btTaxRate4;
};

struct PMSG_REQ_MONEYDRAWOUT
{
	/*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ BYTE btMoney1;
	/*<thisrel this+0x5>*/ /*|0x1|*/ BYTE btMoney2;
	/*<thisrel this+0x6>*/ /*|0x1|*/ BYTE btMoney3;
	/*<thisrel this+0x7>*/ /*|0x1|*/ BYTE btMoney4;
};

struct PMSG_REQ_CSGATEOPERATE
{
	/*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ BYTE btOperate;
	/*<thisrel this+0x5>*/ /*|0x1|*/ BYTE btIndex1;
	/*<thisrel this+0x6>*/ /*|0x1|*/ BYTE btIndex2;
};

struct PMSG_REQ_MINIMAPDATA
{
	/*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
};

struct PMSG_REQ_STOPMINIMAPDATA
{
	/*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
};

struct PMSG_REQ_CSCOMMAND
{
	/*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ BYTE btTeam;
	/*<thisrel this+0x5>*/ /*|0x1|*/ BYTE btX;
	/*<thisrel this+0x6>*/ /*|0x1|*/ BYTE btY;
	/*<thisrel this+0x7>*/ /*|0x1|*/ BYTE btCommand;
};

struct PMSG_REQ_CSHUNTZONEENTER
{
	/*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ BYTE btHuntZoneEnter;
};

struct PMSG_REQ_NPCDBLIST
{
	PBMSG_HEAD h;
	/*<thisrel this+0x3>*/ /*|0x1|*/ BYTE btMonsterCode;
};

struct PMSG_REQ_CSREGGUILDLIST
{
	PBMSG_HEAD h;
};

struct PMSG_REQ_CSATTKGUILDLIST
{
	PBMSG_HEAD h;
};

struct PMSG_REQ_USEWEAPON
{
	/*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ BYTE btObjIndexH;
	/*<thisrel this+0x5>*/ /*|0x1|*/ BYTE btObjIndexL;
	/*<thisrel this+0x6>*/ /*|0x1|*/ BYTE btTargetIndex;
};

struct PMSG_REQ_WEAPON_DAMAGE_VALUE
{
	/*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ BYTE btObjIndexH;
	/*<thisrel this+0x5>*/ /*|0x1|*/ BYTE btObjIndexL;
};

struct PMSG_REQ_GUILDMARK_OF_CASTLEOWNER
{
	/*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
};

struct PMSG_REQ_JEWEL_MIX
{
	/*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ BYTE btJewelType;
	/*<thisrel this+0x5>*/ /*|0x1|*/ BYTE btJewelMix;
};

struct PMSG_REQ_JEWEL_UNMIX
{
	/*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ BYTE btJewelType;
	/*<thisrel this+0x5>*/ /*|0x1|*/ BYTE btJewelLevel;
	/*<thisrel this+0x6>*/ /*|0x1|*/ BYTE btJewelPos;
};

struct PMSG_REQ_CRYWOLF_INFO
{
	/*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
};

struct PMSG_REQ_CRYWOLF_ALTAR_CONTRACT
{
	/*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
	/*<thisrel this+0x4>*/ /*|0x1|*/ BYTE btObjIndexH;
	/*<thisrel this+0x5>*/ /*|0x1|*/ BYTE btObjIndexL;
};

struct PMSG_REQ_CRYWOLF_BENEFIT_PLUS_CHAOSRATE
{
	/*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
};

struct PMSG_REQ_KANTURU_STATE_INFO
{
	/*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
};

struct PMSG_REQ_ENTER_KANTURU_BOSS_MAP
{
	/*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
};

#if(GS_CASTLE==1)
struct CSP_ANS_CSINITDATA
{ // <size 0x40>
	PWMSG_HEAD h;	// 0
	int iResult;		// 4
	WORD wMapSvrNum;	// 8
	WORD wStartYear;	// a
	BYTE btStartMonth;	// c
	BYTE btStartDay;	// d
	WORD wEndYear; // e
	BYTE btEndMonth; // 10
	BYTE btEndDay;	// 11
	BYTE btIsSiegeGuildList;	// 12
	BYTE btIsSiegeEnded;	// 13
	BYTE btIsCastleOccupied;	// 14
	char szCastleOwnGuild[8]; // 15
	__int64 i64CastleMoney; // 20
	int iTaxRateChaos; // 28
	int iTaxRateStore; // 2c
	int iTaxHuntZone; // 30
	int iFirstCreate; // 34
	int iCount; // 38
};

struct CSP_CSINITDATA
{// <size 0x1c>
	int iNpcNumber; // 0
	int iNpcIndex; // 4
	int iNpcDfLevel; // 8
	int iNpcRgLevel; // c
	int iNpcMaxHp; // 10
	int iNpcHp; // 14
	unsigned char btNpcX; // 18
	unsigned char btNpcY; // 19
	unsigned char btNpcDIR; // 1a
};

struct CSP_CALCREGGUILDLIST
{ // <size 0x18>
	char szGuildName[8]; // 0
	int iRegMarkCount; // 8
	int iGuildMemberCount; // c
	int iGuildMasterLevel; // 10
	int iSeqNum; // 14
};

struct CSP_CSGUILDUNIONINFO
{ // <size 0xc>
	char szGuildName[8]; // 0
	int iCsGuildID; // 8
};

struct CSP_CSLOADTOTALGUILDINFO
{ // <size 0x10>
	char szGuildName[8]; // 0
	int iCsGuildID; // 8
	int iGuildInvolved; // c
};

struct PMSG_CSATTKGUILDLIST
{ // <size 0xa>
	unsigned char btCsJoinSide; // 0
	unsigned char btGuildInvolved; // 1
	char szGuildName[8]; // 2
};

struct CSP_ANS_NPCDATA
{ // <size 0x14>
	PWMSG_HEAD h; // 0
	int iResult; // 4
	unsigned short wMapSvrNum; // 8
	int iIndex; // c
	int iCount; // 10
};

struct PMSG_ANS_NOTIFYCSSTART
{ // <size 0x5>
	PBMSG_HEAD2 h; // 0
	unsigned char btStartState; // 4
};

struct PMSG_REQ_MOVE_TO_CASTLE_HUNTZONE // 0x8
{
	PBMSG_HEAD2 h; // +0x0(0x4)
	int iPrice; // +0x4(0x4)
};
#endif

void ProtocolCore(BYTE protoNum, LPBYTE aRecv, int aLen, int aIndex, BOOL Encrypt, int serial);
void TestSend();
void MsgSendV2(LPOBJ lpObj, unsigned char* Msg, int size);
void CGLiveClient(PMSG_CLIENTTIME* lpClientTime, short aIndex);
void GCCheckMainExeKeySend(int aIndex);
WORD EncryptCheckSumKey(WORD wSource);
void CGCheckMainRecv(PMSG_CHECK_MAINEXE_RESULT* lpMsg, int aIndex);
void PEchoProc(unsigned char* aMsg, int aLen, short aIndex);
void GCResultSend(int aIndex, unsigned char headcode, unsigned char result);
void ChatSend(LPOBJ lpObj, char* szChat);
void vChatSend(LPOBJ lpObj, char* szChat, ...);
void AllSendServerMsg(char* chatmsg);
void DataSendAll(unsigned char* lpMsg, int iMsgSize);
void ChatTargetSend(LPOBJ lpObj, char* szChat, int senduser);
void PChatProc(PMSG_CHATDATA* lpChat, short aIndex);
void CGChatRecv(PMSG_CHATDATA_NUMBER* lpMsg, int aIndex);
void GCServerMsgSend(unsigned char msg, int aIndex);
void GCServerMsgStringSend(char* szMsg, int aIndex, BYTE type);
void GCServerMsgStringSendGuild(_GUILD_INFO_STRUCT* lpNode, char* szMsg, unsigned char type);
void GCEventStateSend(int aIndex, unsigned char state, unsigned char event);
void GCMapEventStateSend(int map, unsigned char state, unsigned char event);
void CGChatWhisperRecv(PMSG_CHATDATA_WHISPER* lpMsg, int aIndex);
void SCPJoinResultSend(int aIndex, unsigned char result);
void CSPJoinIdPassRequest(PMSG_IDPASS* lpMsg, int aIndex);
void GCJoinResult(unsigned char result, int aIndex);
void GCJoinSocketResult(unsigned char result, SOCKET Socket);
void CGClientCloseMsg(PMSG_CLIENTCLOSE* lpMsg, int aIndex);
void GCCloseMsgSend(int aIndex, unsigned char result);
void CGClientMsg(PMSG_CLIENTMSG* lpMsg, int aIndex);
void CGPCharacterCreate(PMSG_CHARCREATE* lpMsg, int aIndex);
void CGPCharDel(PMSG_CHARDELETE* lpMsg, int aIndex);
void CGPCharacterMapJoinRequest(PMSG_CHARMAPJOIN* lpMsg, int aIndex);
void GCLevelUpMsgSend(int aIndex, int iSendEffect);
void CGLevelUpPointAdd(PMSG_LVPOINTADD* lpMsg, int aIndex);
void GCInventoryItemOneSend(int aIndex, int pos);
void GCPkLevelSend(int aIndex, unsigned char pklevel);
void GCMagicListOneSend(int aIndex, char Pos, unsigned char type, unsigned char level, unsigned char skill, BYTE btListType);
void GCMagicListOneDelSend(int aIndex, char Pos, BYTE type, BYTE level, BYTE skill, BYTE btListType);
void GCMagicListMultiSend(LPOBJ lpObj, BYTE btListType);
void GCEquipmentSend(int aIndex);
void GCRecallMonLife(int aIndex, int maxlife, int life);
void GCTimeViewSend(int aIndex, int second);
void GCGoalSend(int aIndex, char* Name1, unsigned char score1, char* Name2, unsigned char score2);
void GCSkillKeyRecv(PMSG_SKILLKEY* lpMsg, int aIndex);
void GCSkillKeySend(int aIndex, unsigned char* keybuffer, unsigned char GO, unsigned char Qk, unsigned char Wk, unsigned char Ek, /*<regrel ebp+0x20>*/ /*|0x1|*/ unsigned char ChatWnd);
void GCMoneySend(int aIndex, unsigned long money);
void GCItemInventoryPutSend(int aIndex, unsigned char result, unsigned char iteminfo1, unsigned char iteminfo2);
void CGItemGetRequest(PMSG_ITEMGETREQUEST* lpMsg, int aIndex);
BOOL CGItemDropRequest(PMSG_ITEMTHROW* lpMsg, int aIndex, int drop_type);
void GCItemMoveResultSend(int aIndex, unsigned char result, unsigned char pos, unsigned char* const ItemInfo);
void CGInventoryItemMove(PMSG_INVENTORYITEMMOVE* lpMsg, int aIndex);
void GCEquipmentChange(int aIndex, int pos);
void CGTalkRequestRecv(PMSG_TALKREQUEST* lpMsg, int aIndex);
void GCUserWarehouseSend(LPOBJ lpObj);
void CGBuyRequestRecv(PMSG_BUYREQUEST* lpMsg, int aIndex);
void CGSellRequestRecv(PMSG_SELLREQUEST* lpMsg, int aIndex);
int  GetNeedMoneyItemDurRepaire(class CItem* DurItem, int RequestPos);
void ItemDurRepaire(LPOBJ lpObj, class CItem* DurItem, int pos, int RequestPos);
void CGModifyRequestItem(PMSG_ITEMDURREPAIR* lpMsg, int aIndex);
void CGTradeRequestSend(PMSG_TRADE_REQUEST* lpMsg, int aIndex);
void CGTradeResponseRecv(PMSG_TRADE_RESPONSE* lpMsg, int aIndex);
BOOL GCTradeResponseSend(BYTE response, int aIndex, LPSTR id, WORD level, int GuildNumber);
int GCTradeOtherDel(int aIndex, BYTE tradeindex);
int GCTradeOtherAdd(int aIndex, BYTE tradeindex, LPBYTE iteminfo);
void CGTradeMoneyRecv(PMSG_TRADE_GOLD* lpMsg, int aIndex);
BOOL GCTradeMoneyOther(int aIndex, DWORD money);
BOOL GCTradeOkButtonSend(int aIndex, unsigned char flag);
void CGTradeOkButtonRecv(PMSG_TRADE_OKBUTTON* lpMsg, int aIndex);
void CGTradeCancelButtonRecv(int aIndex);
void CGTradeResult(int aIndex, unsigned char result);
void CGPShopReqSetItemPrice(PMSG_REQ_PSHOP_SETITEMPRICE* lpMsg, int aIndex);
void CGPShopAnsSetItemPrice(int aIndex, BYTE btResult, BYTE btItemPos);
void CGPShopReqOpen(PMSG_REQ_PSHOP_OPEN* lpMsg, int aIndex);
void CGPShopAnsOpen(int aIndex, BYTE btResult);
void CGPShopReqClose(int aIndex);
void CGPShopAnsClose(int aIndex, BYTE btResult);
void CGPShopReqBuyList(PMSG_REQ_BUYLIST_FROM_PSHOP* lpMsg, int aSourceIndex);
void CGPShopAnsBuyList(int aSourceIndex, int aTargetIndex, BYTE btResult, bool bResend);
void CGPShopReqBuyItem(PMSG_REQ_BUYITEM_FROM_PSHOP* lpMsg, int aSourceIndex);
void CGPShopAnsBuyItem(int aSourceIndex, int aTargetIndex, int iItemPos, BYTE btResult);
void CGPShopReqCloseDeal(PMSG_REQ_PSHOPDEAL_CLOSE* lpMsg, int aIndex);
void CGPShopAnsSoldItem(int aSourceIndex, int aTargetIndex, int iItemPos);
void CGPShopAnsDealerClosedShop(int aSourceIndex, int aTargetIndex);
void CGPartyRequestRecv(PMSG_PARTYREQUEST* lpMsg, int aIndex);
void CGPartyRequestResultRecv(PMSG_PARTYREQUESTRESULT* lpMsg, int aIndex);
void CGPartyList(int aIndex);
void CGPartyListAll(int pnumber);
void CGPartyDelUser(PMSG_PARTYDELUSER* lpMsg, int aIndex);
void GCPartyDelUserSend(int aIndex);
void CGGuildRequestRecv(PMSG_GUILDJOINQ* lpMsg, int aIndex);
void CGGuildRequestResultRecv(PMSG_GUILDQRESULT* lpMsg, int aIndex);
void CGGuildListAll(int pnumber);
void CGGuildDelUser(PMSG_GUILDDELUSER* lpMsg, int aIndex);
void GCGuildDelUserResult(int aIndex, unsigned char Result);
void GCGuildMasterQuestionSend(int aIndex);
void CGGuildMasterAnswerRecv(PMSG_GUILDMASTERANSWER* lpMsg, int aIndex);
void GCGuildMasterManagerRun(int aIndex);
void CGGuildMasterInfoSave(int aIndex, PMSG_GUILDINFOSAVE* lpMsg);
void CGGuildMasterCreateCancel(int aIndex);
void GCGuildViewportNowPaint(int aIndex, char* guildname, unsigned char* Mark, int isGuildMaster);
void GCGuildViewportDelNow(int aIndex, int isGuildMaster);
void GCManagerGuildWarEnd(char* GuildName);
void GCManagerGuildWarSet(char* GuildName1, char* GuildName2, int type);
void GCGuildWarRequestResult(char* GuildName, int aIndex, int type);
void GCGuildWarRequestSend(char* GuildName, int aIndex, int type);
void GCGuildWarRequestSendRecv(PMSG_GUILDWARSEND_RESULT* lpMsg, int aIndex);
void GCGuildWarDeclare(int aIndex, char* _guildname);
void GCGuildWarEnd(int aIndex, unsigned char result, char* _guildname);
void GCGuildWarScore(int aIndex);
void CGWarehouseMoneyInOut(int aIndex, PMSG_WAREHOUSEMONEYINOUT* lpMsg);
void GCWarehouseInventoryMoneySend(int aIndex, unsigned char result, int money, int wmoney);
void CGWarehouseUseEnd(int aIndex);
void GCWarehouseStateSend(int aIndex, unsigned char state);
void GCWarehouseRecivePassword(int aIndex, PMSG_WAREHOUSEPASSSEND* lpMsg);
void GCUserChaosBoxSend(LPOBJ lpObj, int iChaosBoxType);
void CGChaosBoxItemMixButtonClick(PMSG_CHAOSMIX* aRecv, int aIndex);
void CGChaosBoxUseEnd(int aIndex);
void PMoveProc(PMSG_MOVE* lpMove, int aIndex);
void RecvPositionSetProc(PMSG_POSISTION_SET* lpMove, int aIndex);
void CGAttack(PMSG_ATTACK* lpMsg, int aIndex);
void GCDamageSend(int aIndex, int damage);
void GCDamageSend(int aIndex, int TargetIndex, int AttackDamage, int MSBFlag, int MSBDamage);
void GCKillPlayerExpSend(int aIndex, int TargetIndex, int exp, int AttackDamage, int MSBFlag);
void GCDiePlayerSend(LPOBJ lpObj, int TargetIndex, BYTE skill, int KillerIndex);
void GCActionSend(LPOBJ lpObj, BYTE ActionNumber, int aIndex, int aTargetIndex);
void CGActionRecv(PMSG_ACTION* lpMsg, int aIndex);
void CGMagicAttack(PMSG_MAGICATTACK* lpMsg, int aIndex);
void GCMagicAttackNumberSend(LPOBJ lpObj, BYTE MagicNumber, int usernumber, unsigned char skillsuccess);
void GCMagicCancelSend(LPOBJ lpObj, BYTE MagicNumber);
void GCMagicCancel(PMSG_MAGICCANCEL * lpMsg, int aIndex);
void GCUseEffectItem(LPOBJ lpObj, int iEffectUseOption, int iOptionType, int iEffectType, int iLeftTime);
void CGMagicCancel(PMSG_MAGICCANCEL* lpMsg, int aIndex);
void GCUseMonsterSkillSend(LPOBJ lpObj, LPOBJ lpTargetObj, int iSkillNumber);
void GCStateInfoSend(LPOBJ lpObj, unsigned char state, int ViewSkillState);
void CGTeleportRecv(PMSG_TELEPORT* lpMsg, int aIndex);
void CGTargetTeleportRecv(PMSG_TARGET_TELEPORT* lpMsg, int aIndex);
void GCTeleportSend(LPOBJ lpObj, unsigned char MoveNumber, BYTE MapNumber, BYTE MapX, BYTE MapY, BYTE Dir);
void CGBeattackRecv(unsigned char* lpRecv, int aIndex, int magic_send);
void CGDurationMagicRecv(PMSG_DURATION_MAGIC_RECV* lpMsg, int aIndex);
void ObjectMapJoinPositionSend(short aIndex);
void CGUseItemRecv(PMSG_USEITEM* lpMsg, int aIndex);
void GCReFillSend(int aIndex, int Life, BYTE Ipos, unsigned char flag);
void GCManaSend(int aIndex, int Mana, BYTE Ipos, unsigned char flag, int BP);
void GCInventoryItemDeleteSend(int aIndex, BYTE pos, unsigned char flag);
void GCItemUseSpecialTimeSend(int aIndex, unsigned char number, int time);
void GCItemDurSend(int aIndex, BYTE pos, unsigned char dur, unsigned char flag);
void GCItemDurSend2(int aIndex, BYTE pos, unsigned char dur, unsigned char flag);
void CGWeatherSend(int aIndex, BYTE weather);
void GCServerCmd(int aIndex, BYTE type, unsigned char Cmd1, unsigned char Cmd2);
void GCReqmoveDevilSquare(PMSG_REQ_MOVEDEVILSQUARE* lpMsg, int aIndex);
void GCReqDevilSquareRemainTime(PMSG_REQ_DEVILSQUARE_REMAINTIME* lpMsg, int aIndex);
void AllSendMsg(unsigned char* Msg, int size);
void AllSendSameMapMsg(unsigned char* Msg, int size, unsigned char mapnumber);
void GCSendPing(int aIndex);
void GCPingSendRecv(PMSG_PING_RESULT* aRecv, int aIndex);
void GCRegEventChipRecv(PMSG_REGEVENTCHIP* lpMsg, int aIndex);
void GCGetMutoNumRecv(PMSG_GETMUTONUMBER* lpMsg, int aIndex);
void GCUseEndEventChipRescv(int aIndex);
void GCUseRenaChangeZenRecv(PMSG_EXCHANGE_EVENTCHIP* lpMsg, int aIndex);
void CGRequestQuestInfo(int aIndex);
void GCSendQuestInfo(int aIndex, int QuestIndex);
void CGSetQuestState(PMSG_SETQUEST* lpMsg, int aIndex);
void GCSendQuestPrize(int aIndex, unsigned char Type, unsigned char Count);
void CGCloseWindow(int aIndex);
void CGRequestEnterBloodCastle(PMSG_REQ_MOVEBLOODCASTLE* lpMsg, int iIndex);
void CGRequestEnterChaosCastle(PMSG_REQ_MOVECHAOSCASTLE* lpMsg, int iIndex);
void CGRequestRepositionUserInChaosCastle(PMSG_REQ_REPOSUSER_IN_CC* lpMsg, int aIndex);
void CGRequestEventEnterCount(PMSG_REQ_CL_ENTERCOUNT* lpMsg, int aIndex);
void CGRequestLottoRegister(PMSG_REQ_2ANV_LOTTO_EVENT* lpMsg, int aIndex);
void CGReqMoveOtherServer(PMSG_REQ_MOVE_OTHERSERVER* lpMsg, int aIndex);
void GCPacketCheckSumRecv(PMSG_PACKETCHECKSUM* aRecv, int aIndex);
void CGDuelStartRequestRecv(PMSG_REQ_START_DUEL* lpMsg, int aIndex);
void CGDuelEndRequestRecv(PMSG_REQ_END_DUEL* lpMsg, int aIndex);
void CGDuelOkRequestRecv(PMSG_ANS_DUEL_OK* lpMsg, int aIndex);
void GCSendDuelScore(int aIndex1, int aIndex2);
void GCSendGetItemInfoForParty(int aIndex, class CMapItem* lpItem);
void GCSendEffectInfo(int aIndex, BYTE btType);
void CGRequestPetItemCommand(PMSG_REQUEST_PET_ITEM_COMMAND* lpMsg, int aIndex);
void CGRequestPetItemInfo(PMSG_REQUEST_PET_ITEMINFO* lpMsg, int aIndex);
void GCGuildViewportInfo(PMSG_REQ_GUILDVIEWPORT* aRecv, int aIndex);
void CGGuildAssignStatus(PMSG_GUILD_ASSIGN_STATUS_REQ* aRecv, int aIndex);
void CGGuildAssignType(PMSG_GUILD_ASSIGN_TYPE_REQ* aRecv, int aIndex);
void CGRelationShipReqJoinBreakOff(PMSG_RELATIONSHIP_JOIN_BREAKOFF_REQ* aRecv, int aIndex);
void CGRelationShipAnsJoinBreakOff(PMSG_RELATIONSHIP_JOIN_BREAKOFF_ANS* aRecv, int aIndex);
void CGUnionList(PMSG_UNIONLIST_REQ* aRecv, int aIndex);
void CGRelationShipReqKickOutUnionMember(PMSG_KICKOUT_UNIONMEMBER_REQ* aRecv, int aIndex);
void CGReqMapSvrAuth(PMSG_REQ_MAPSERVERAUTH* lpMsg, int iIndex);
void GCAnsMapSvrAuth(int iIndex, int iResult);
void CGReqCastleSiegeState(PMSG_REQ_CASTLESIEGESTATE* lpMsg, int iIndex);
void GCAnsCastleSiegeState(int iIndex, int iResult, char* lpszGuildName, char* lpszGuildMaster);
void CGReqRegCastleSiege(PMSG_REQ_REGCASTLESIEGE* lpMsg, int iIndex);
void GCAnsRegCastleSiege(int iIndex, int iResult, char* lpszGuildName);
void CGReqGiveUpCastleSiege(PMSG_REQ_GIVEUPCASTLESIEGE* lpMsg, int iIndex);
void GCAnsGiveUpCastleSiege(int iIndex, int iResult, int bGiveUp, int iMarkCount, char* lpszGuildName);
void CGReqGuildRegInfo(PMSG_REQ_GUILDREGINFO* lpMsg, int iIndex);
void GCAnsGuildRegInfo(int iIndex, int iResult, CSP_ANS_GUILDREGINFO* lpMsgResult);
void CGReqRegGuildMark(PMSG_REQ_REGGUILDMARK* lpMsg, int iIndex);
void GCAnsRegGuildMark(int iIndex, int iResult, CSP_ANS_GUILDREGMARK* lpMsgResult);
void CGReqNpcBuy(PMSG_REQ_NPCBUY* lpMsg, int iIndex);
void GCAnsNpcBuy(int iIndex, int iResult, int iNpcNumber, int iNpcIndex);
void CGReqNpcRepair(PMSG_REQ_NPCREPAIR* lpMsg, int iIndex);
void GCAnsNpcRepair(int iIndex, int iResult, int iNpcNumber, int iNpcIndex, int iNpcHP, int iNpcMaxHP);
void CGReqNpcUpgrade(PMSG_REQ_NPCUPGRADE* lpMsg, int iIndex);
void GCAnsNpcUpgrade(int iIndex, int iResult, int iNpcNumber, int iNpcIndex, int iNpcUpType, int iNpcUpValue);
void CGReqTaxMoneyInfo(PMSG_REQ_TAXMONEYINFO* lpMsg, int iIndex);
void GCAnsTaxMoneyInfo(int iIndex, int iResult, BYTE btTaxRateChaos, BYTE btTaxRateStore, __int64 i64Money);
void CGReqTaxRateChange(PMSG_REQ_TAXRATECHANGE* lpMsg, int iIndex);
void GCAnsTaxRateChange(int iIndex, int iResult, BYTE btTaxType, int iTaxRate);
void CGReqMoneyDrawOut(PMSG_REQ_MONEYDRAWOUT* lpMsg, int iIndex);
void GCAnsMoneyDrawOut(int iIndex, int iResult, __int64 i64Money);
void GCAnsCsGateState(int iIndex, int iResult, int iGateIndex);
void CGReqCsGateOperate(PMSG_REQ_CSGATEOPERATE* lpMsg, int iIndex);
void GCAnsCsGateOperate(int iIndex, int iResult, int iGateIndex, int iGateOperate);
void GCAnsCsGateCurState(int iIndex, int iGateIndex, int iGateOperate);
void GCAnsCsAccessSwitchState(int iIndex, int iSwitchIndex, int iSwitchUserIndex, BYTE btSwitchState);
void GCAnsCsAccessCrownState(int iIndex, BYTE btCrownState);
void GCAnsCsNotifyStart(int iIndex, BYTE btStartState);
void GCAnsCsNotifyProgress(int iIndex, BYTE btCastleSiegeState, char* lpszGuildName);
void GCAnsCsMapSvrTaxInfo(int iIndex, BYTE btTaxType, BYTE btTaxRate);
void CGReqCsMiniMapData(PMSG_REQ_MINIMAPDATA* lpMsg, int iIndex);
void GCAnsCsMiniMapData(int iIndex, BYTE btResult);
void CGReqStopCsMiniMapData(PMSG_REQ_STOPMINIMAPDATA* lpMsg, int iIndex);
void CGReqCsSendCommand(PMSG_REQ_CSCOMMAND* lpMsg, int iIndex);
void GCAnsCsSendCommand(int iCsJoinSide, BYTE btTeam, BYTE btX, BYTE btY, BYTE btCommand);
void GCAnsCsLeftTimeAlarm(BYTE btHour, BYTE btMinute);
void GCAnsSelfCsLeftTimeAlarm(int iIndex, BYTE btHour, BYTE btMinute);
void CGReqCsSetEnterHuntZone(PMSG_REQ_CSHUNTZONEENTER* lpMsg, int iIndex);
void GCAnsCsSetEnterHuntZone(int iIndex, BYTE btResult, BYTE btEnterHuntZone);
void CGReqNpcDbList(PMSG_REQ_NPCDBLIST* lpMsg, int iIndex);
void CGReqCsRegGuildList(PMSG_REQ_CSREGGUILDLIST* lpMsg, int iIndex);
void CGReqCsAttkGuildList(PMSG_REQ_CSATTKGUILDLIST* lpMsg, int iIndex);
void CGReqWeaponUse(PMSG_REQ_USEWEAPON* aRecv, int iIndex);
void CGReqWeaponDamageValue(PMSG_REQ_WEAPON_DAMAGE_VALUE* aRecv, int iIndex);

#if(GS_CASTLE==1)
void GCSendObjectCreationState(int iObjectIndex);
#endif

void CGReqGuildMarkOfCastleOwner(PMSG_REQ_GUILDMARK_OF_CASTLEOWNER* aRecv, int iIndex);

#if(GS_CASTLE==1)
void CGReqCastleHuntZoneEntrance(PMSG_REQ_MOVE_TO_CASTLE_HUNTZONE* aRecv, int aIndex);
#endif

void CGReqJewelMix(PMSG_REQ_JEWEL_MIX* lpMsg, int iIndex);
void GCAnsJewelMix(int iIndex, int iResult);
void CGReqJewelUnMix(PMSG_REQ_JEWEL_UNMIX* lpMsg, int iIndex);
void GCAnsJewelUnMix(int iIndex, int iResult);

#endif