#ifndef GAMEMAIN_H
#define	GAMEMAIN_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wsJoinServerCli.h"
#include "wsGameServer.h"
#include "MapClass.h"
#include "NSerialCheck.h"
#include "classdef.h"
#include "DragonEvent.h"
#include "AttackEvent.h"
#include "WzUdp.h"
#include "WhisperCash.h"
#include "SimpleModulus.h"
#include "MonsterAttr.h"
#include "MonsterSetBase.h"
#include "PartyClass.h"
#include "ItemBagEx.h"
#include "Setting.h"

#if (GS_CASTLE==1)
#include "CastleSiege.h"
#include "CastleDeepEvent.h"
#endif

#define FIRST_PATH "c:\\Muproject\\data\\" //Original Path

#define COMMONSERVER_MAINSECTION "GameServerInfo"
#define COMMONSERVER_FILE "..\\Data\\CommonServer.ini"

struct PMSG_FRIEND_STATE
{
	PBMSG_HEAD h;	// C1:C4
	char Name[10];	// 3
	BYTE State;	// D
};

enum MU_EVENT_TYPE
{
	MU_EVENT_ALL = 0x0,
	MU_EVENT_DEVILSQUARE = 0x1,
	MU_EVENT_BLOODCASTLE = 0x2,
	MU_EVENT_ATTACKEVENTTROOP = 0x3,
	MU_EVENT_GOLDENTROOP = 0x4,
	MU_EVENT_WHITEMAGETROOP = 0x5,
	MU_EVENT_LOVEPANGPANG = 0x6,
	MU_EVENT_FIRECRACKER = 0x7,
	MU_EVENT_MEDALION = 0x8,
	MU_EVENT_XMASSTAR = 0x9,
	MU_EVENT_HEARTOFLOVE = 0xa,
	MU_EVENT_SAY_HAPPYNEWYEAR = 0xb,
	MU_EVENT_SAY_MERRYXMAS = 0xc,
	MU_EVENT_CHAOSCASTLE = 0xd,
};

enum MU_ETC_TYPE
{
	MU_ETC_ALL = 0x0,
	MU_ETC_CREATECHARACTER = 0x1,
	MU_ETC_GUILD = 0x2,
	MU_ETC_TRADE = 0x3,
	MU_ETC_USECHAOSBOX = 0x4,
	MU_ETC_PERSONALSHOP = 0x5,
	MU_ETC_PKITEMDROP = 0x6,
	MU_ETC_ITEMDROPRATE = 0x7,
	MU_ETC_SPEEDHACK = 0x8,
	MU_ETC_GAMEGUARD = 0x9,
};

extern BOOL JoinServerConnected;
extern BOOL DataServerConnected;
extern BOOL GameServerCreated;
extern BOOL DevilSquareEventConnect;
extern BOOL IsDevilSquareEventConnected;
extern BOOL EventChipServerConnect;
extern BOOL IsEventChipServerConnected;
extern CDragonEvent DragonEvent;
extern CAttackEvent AttackEvent;
extern CItemBag LuckboxItemBag;
extern CItemBag Mon55;
extern CItemBag Mon53;
extern CItemBagEx StarOfXMasItemBag;
extern CItemBag FireCrackerItemBag;
extern CItemBag HeartOfLoveItemBag;
extern CItemBag GoldMedalItemBag;
extern CItemBag SilverMedalItemBag;
extern CItemBag EventChipItemBag;
extern CItemBag GoldGoblenItemBag;
extern CItemBag TitanItemBag;
extern CItemBag GoldDerconItemBag;
extern CItemBag DevilLizardKingItemBag;
extern CItemBag KanturItemBag;
extern CItemBag RingEventItemBag;
extern CItemBag FriendShipItemBag;
extern CItemBag DarkLordHeartItemBag;
extern CItemBagEx KundunEventItemBag;
extern CItemBagEx HiddenTreasureBoxItemBag;

#if(GS_CASTLE==1)
extern CItemBagEx CastleHuntZoneBossItemBag;
extern CItemBagEx CastleItemMixItemBag;
#endif

extern BOOL SpeedHackPlayerBlock;
extern BOOL gApplyHeroSystem;
extern BOOL gEnableEventNPCTalk;
extern BOOL gEnableServerDivision;
extern BOOL gEvent1;
extern int  gMonsterHp;
extern BOOL gMerryXMasNpcEvent;
extern BOOL gHappyNewYearNpcEvent;
extern int  gEvent1ItemDropTodayCount;
extern BOOL gChaosEvent;
extern char gChaosEventServerIp[20];
extern char gDevilSquareEventServerIp[20];
extern char gHackLogServerIp[20];
extern char gEventChipServerIp[20];
extern char gStalkProtocolId[11];
extern BOOL gNonPK;
extern BOOL gPkLimitFree;
extern BOOL gXMasEvent;
extern BOOL gFireCrackerEvent;
extern BOOL gHeartOfLoveEvent;
extern BOOL gMedalEvent;
extern BOOL gEventChipEvent;
extern BOOL gDevilSquareEvent;
extern BOOL gWriteSkillLog;
extern BOOL g_bStoneItemDrop;
extern BOOL g_bDoRingEvent;
extern BOOL g_bEventManagerOn;
extern int  g_iKundunMarkDropRate;
extern int  g_iMarkOfTheLord;
extern int  g_iDarkLordHeartDropRate;
extern int  g_iDarkLordHeartOffEventRate;
extern int g_iMysteriousBeadDropRate1;
extern int g_iMysteriousBeadDropRate2;
extern int g_iHiddenTreasureBoxOfflineRate;

extern BOOL gIsItemDropRingOfTransform;
extern BOOL gDoPShopOpen;
extern BOOL gDisconnectHackUser;
extern int g_iBlockCastleSiegeMapEnter;
extern BOOL GSInfoSendFlag;
extern int  GameServerPort;
extern int  JoinServerPort;
extern int  DataServerPort;
extern int  ExDbPort;
extern CwsGameServer wsGServer;	// line : 213GameServer
extern wsJoinServerCli wsJServerCli;	// line : 214 Join Server
extern wsJoinServerCli wsDataCli;	// line : 215 DataServer
extern wsJoinServerCli wsExDbCli;	// line : 239 Extra DataBase Server
extern wsJoinServerCli wsRServerCli;	// line : 244 Ranking Server
extern wsJoinServerCli wsEvenChipServerCli; // line : 246 EVENT_MU2003
extern MapClass MapC[MAX_NUMBER_MAP];	// line 249	// Map Manager
extern CMonsterAttr gMAttr;	// line 250
extern CMonsterSetBase gMSetBase;	// line 251
extern classdef DCInfo;	// line 252:
extern CWhisperCash WhisperCash;	// line 253
extern PartyClass gParty;	// line 254
extern WzUdp gUdpSoc;	// line 256
extern WzUdp gUdpSocCE;	// line 258
extern WzUdp gUdpSocCER;	// line 259
extern WzUdp gUdpSocCRank;	// line 261
extern WzUdp gUdpSocCRankR;	//line 262
extern CGuildClass Guild;	// line 265
extern CMsg lMsg;	// line 324
extern NSerialCheck gNSerialCheck[OBJMAX];	// line 326
extern DWORD  gLevelExperience[400 + 1];
extern char szServerName[50];
extern BOOL gIsDropDarkLordItem;
extern int  gSleeveOfLordDropRate;
extern int  gSleeveOfLordDropLevel;
extern int  gSoulOfDarkHorseDropRate;
extern int  gSoulOfDarkHorseropLevel;
extern int  gSoulOfDarkSpiritDropRate;
extern int  gSoulOfDarkSpiritDropLevel;
extern float gDarkSpiritAddExperience;
extern BOOL gIsDropGemOfDefend;
extern int  gGemOfDefendDropRate;
extern int  gGemOfDefendDropLevel;
extern int  g_iUseCharacterAutoRecuperationSystem;
extern int  g_iCharacterRecuperationMaxLevel;
extern int g_iServerGroupGuildChatting;
extern int g_iServerGroupUnionChatting;
extern int g_iSkillDistanceCheck;
extern int g_iSkillDistanceCheckTemp;
extern int g_iSkillDistanceKick;
extern int g_iSkillDistanceKickCount;
extern int g_iSkillDiatanceKickCheckTime;

extern DWORD dwgCheckSum[MAX_CHECKSUM_KEY];
extern char connectserverip[20];
extern int  connectserverport;
extern short gGameServerCode;
extern int  gPkTime;
extern BOOL g_bCastleGuildDestoyLimit;
extern DWORD  gItemNumberCount;
extern BOOL gStalkProtocol;
extern DWORD  gAttackEventRegenTime;
extern int  gYear;
extern BOOL gOnlyFireCrackerEffectUse;
extern int  g_iRingOrcKillGiftRate;
extern int  g_iRingDropGiftRate;
extern CSimpleModulus g_SimpleModulusCS;	// line 751
extern CSimpleModulus g_SimpleModulusSC;	// line 752
extern int  gEledoradoGoldGoblenItemDropRate;
extern int  gEledoradoTitanItemDropRate;
extern int  gEledoradoGoldDerconItemDropRate;
extern int  gEledoradoDevilLizardKingItemDropRate;
extern int  gEledoradoDevilTantarosItemDropRate;
extern int  gEledoradoGoldGoblenExItemDropRate;
extern int  gEledoradoTitanExItemDropRate;
extern int  gEledoradoGoldDerconExItemDropRate;
extern int  gEledoradoDevilLizardKingExItemDropRate;
extern int  gEledoradoDevilTantarosExItemDropRate;
extern int  giKundunRefillHPSec;
extern int  giKundunRefillHP;
extern int  giKundunRefillHPTime;
extern int  giKundunHPLogSaveTime;

extern int g_PKLevelIncreaseOff;
extern char gMapName[MAX_NUMBER_MAP][50];
extern char szClientVersion[8];
extern BOOL bCanTrade;
extern BOOL bCanChaosBox;
extern BOOL bCanWarehouseLock;
extern int  MapMinUserLevel[MAX_NUMBER_MAP];
extern BOOL gEnableBattleSoccer;
extern int  gLootingTime;
extern int  gPkItemDrop;
extern int  gItemDropPer;
extern int  gEvent1ItemDropTodayMax;
extern int  gEvent1ItemDropTodayPercent;
extern int  gCharacterDeleteMinLevel;
extern BOOL gCreateCharacter;
extern BOOL gGuildCreate;
extern BOOL gGuildDestroy;
extern int  gGuildCreateLevel;
extern BOOL gItemSerialCheck;
extern int  g_XMasEvent_StarOfXMasDropRate;
extern int  g_XMasEvent_ItemDropRateForStarOfXMas;
extern int  gFireCrackerDropRate;
extern int  g_ItemDropRateForgFireCracker;
extern int  gHeartOfLoveDropRate;
extern int  g_ItemDropRateForgHeartOfLove;
extern int  gGoldMedalDropRate;
extern int  gSilverMedalDropRate;
extern int  g_ItemDropRateForGoldMedal;
extern int  g_ItemDropRateForSilverMedal;
extern int  gBoxOfGoldDropRate;
extern int  g_ItemDropRateForBoxOfGold;
extern int  g_EventChipDropRateForBoxOfGold;
extern int  gEyesOfDevilSquareDropRate;
extern int  gKeyOfDevilSquareDropRate;
extern int  gDQChaosSuccessRateLevel1;
extern int  gDQChaosSuccessRateLevel2;
extern int  gDQChaosSuccessRateLevel3;
extern int  gDQChaosSuccessRateLevel4;
extern int  gDQChaosSuccessRateLevel5;
extern int  gDQChaosSuccessRateLevel6;
extern BOOL g_bBloodCastle;
extern int  g_iBloodCastle_StartHour;
extern int  g_iStoneDropRate;
extern int  g_iAngelKingsPaperDropRate;
extern int  g_iBloodBoneDropRate;
extern BOOL g_bChaosCastle;
extern BOOL gItemDropRingOfTransform;
extern int  gQuestNPCTeleportTime;
extern DWORD  gEledoradoGoldGoblenRegenTime;
extern DWORD  gEledoradoTitanRegenTime;
extern DWORD  gEledoradoGoldDerconRegenTime;
extern DWORD  gEledoradoDevilLizardKingRegenTime;
extern DWORD  gEledoradoDevilTantarosRegenTime;
extern int  gZenDurationTime;
extern int gMonsterHPAdjust;
extern BOOL gEnableCheckPenetrationSkill;

#if (GS_CASTLE==1)
extern CCastleSiege g_CastleSiege;
extern CCastleDeepEvent g_CastleDeepEvent;
extern int g_iCastleItemMixLimit;

extern int gIsDropSetItemInCastleHuntZone;
extern int gSetItemInCastleHuntZoneDropRate;
extern int gSetItemInCastleHuntZoneDropLevel;
extern BOOL g_bDoCastleDeepEvent;

#endif

//------------------------------------------
// GameMain.cpp Funcs - Prototypes List - Completed
//------------------------------------------
void gSetDate();
BOOL gJoomin15Check(char* szJN);
BOOL gJoominCheck(char* szJN, int iLimitAge);
void GameMainInit(HWND hWnd);
int GetWarehouseUsedHowMuch(int UserLevel, BOOL IsLock);
void GameMonsterAllAdd();
void GameMonsterAllCloseAndReLoad();
void GameMainFree();
BOOL GMJoinServerConnect(char* ConnectServer, DWORD wMsg);
BOOL GMRankingServerConnect(char* RankingServer, DWORD wMsg);
BOOL GMEventChipServerConnect(char* ServerIP, DWORD wMsg);
BOOL GMDataServerConnect(char* ConnectServer, WPARAM wMsg);
BOOL ExDataServerConnect(char* ConnectServer, DWORD wMsg);
BOOL GameMainServerCreate(DWORD sMsg, DWORD cMsg);
void GMServerMsgProc(WPARAM wParam, LPARAM lParam);
void GMClientMsgProc(WPARAM wParam, LPARAM lParam);
void GMJoinClientMsgProc(WPARAM wParam, LPARAM lParam);
void GMRankingClientMsgProc(WPARAM wParam, LPARAM lParam);
void GMEventChipClientMsgProc(WPARAM wParam, LPARAM lParam);
void ExDataClientMsgProc(WPARAM wParam, LPARAM lParam);
void GMDataClientMsgProc(WPARAM wParam, LPARAM lParam);
void ReadServerInfo();
void ReadCommonServerInfo();
void GameServerInfoSendStop();
void GameServerInfoSendStart();
void GameServerInfoSend();
void CheckSumFileLoad(char * szCheckSum);
void LoadItemBag();
void SetMapName();
void ReadEventInfo(MU_EVENT_TYPE eEventType);
void ReadGameEtcInfo(MU_ETC_TYPE eGameEtcType);

#endif