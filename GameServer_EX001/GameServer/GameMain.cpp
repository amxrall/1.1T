#include "StdAfx.h"
#include "gamemain.h"
#include "winutil.h"
#include "GameServer.h"
#include "LogProc.h"
#include "wsJoinServerCli.h"
#include "DSProtocol.h"
#include "MapClass.h"
#include "classdef.h"
#include "prodef.h"
#include "wsGameServer.h"
#include "EledoradoEvent.h"
#include "WhisperCash.h"
#include "SProtocol.h"
#include "ChaosCastle.h"
#include "DevilSquare.h"
#include "Gate.h"
#include "user.h"
#include "Event.h"
#include "PacketCheckSum.h"
#include "DragonEvent.h"
#include "AttackEvent.h"
#include "SimpleModulus.h"
#include "MapServerManager.h"
#include "QuestInfo.h"
#include "SkillHitBox.h"
#include "EventManagement.h"
#include "SetItemOption.h"
#include "EDSProtocol.h"
#include "MonsterItemMng.h"
#include "GMMng.h"
#include "BattleSoccerManager.h"
#include "GuildClass.h"
#include "MoveCommand.h"
#include "ChaosBox.h"
#include "BloodCastle.h"
#include "Shop.h"
#include "SkillAdditionInfo.h"
#include "Load.h"
#include "ObjBotStore.h"
//------------------------------------------
// GameMain.cpp Variables
//------------------------------------------

BOOL JoinServerConnected;
BOOL DataServerConnected;
BOOL GameServerCreated;
BOOL DevilSquareEventConnect;
BOOL IsDevilSquareEventConnected;
BOOL EventChipServerConnect;
BOOL IsEventChipServerConnected;
CDragonEvent DragonEvent;
CAttackEvent AttackEvent;
CItemBag LuckboxItemBag;
CItemBag Mon55;
CItemBag Mon53;
CItemBagEx StarOfXMasItemBag;
CItemBag FireCrackerItemBag;
CItemBag HeartOfLoveItemBag;
CItemBag GoldMedalItemBag;
CItemBag SilverMedalItemBag;
CItemBag EventChipItemBag;
CItemBag GoldGoblenItemBag;
CItemBag TitanItemBag;
CItemBag GoldDerconItemBag;
CItemBag DevilLizardKingItemBag;
CItemBag KanturItemBag;
CItemBag RingEventItemBag;
CItemBag FriendShipItemBag;
CItemBag DarkLordHeartItemBag;
CItemBagEx KundunEventItemBag;
CItemBagEx HiddenTreasureBoxItemBag;

BOOL SpeedHackPlayerBlock;
BOOL gApplyHeroSystem;
BOOL gEnableEventNPCTalk;
BOOL gEnableServerDivision;
BOOL gEvent1;
int  gMonsterHp;
BOOL gMerryXMasNpcEvent;
BOOL gHappyNewYearNpcEvent;
int  gEvent1ItemDropTodayCount;
BOOL gChaosEvent;
char gChaosEventServerIp[20];
char gDevilSquareEventServerIp[20];
char gHackLogServerIp[20];
char gEventChipServerIp[20];
char gStalkProtocolId[11];
BOOL gNonPK;
BOOL gPkLimitFree;
BOOL gXMasEvent;
BOOL gFireCrackerEvent;
BOOL gHeartOfLoveEvent;
BOOL gMedalEvent;
BOOL gEventChipEvent;
BOOL gDevilSquareEvent;
BOOL gWriteSkillLog;
BOOL g_bStoneItemDrop;
BOOL g_bDoRingEvent;
BOOL g_bEventManagerOn;
int  g_iKundunMarkDropRate;
int  g_iMarkOfTheLord;
int  g_iDarkLordHeartDropRate;
int  g_iDarkLordHeartOffEventRate;
int g_iMysteriousBeadDropRate1;
int g_iMysteriousBeadDropRate2;
int g_iHiddenTreasureBoxOfflineRate;
BOOL gIsItemDropRingOfTransform;
BOOL gDoPShopOpen;
BOOL gWriteChatLog;
BOOL gDisconnectHackUser;
int g_iBlockCastleSiegeMapEnter;
BOOL GSInfoSendFlag;

///////////////////////////////////////////////////////////////////////////////

int  GameServerPort;
int  JoinServerPort;
int  DataServerPort;
int  ExDbPort;

CwsGameServer wsGServer;	// line : 213GameServer

wsJoinServerCli wsJServerCli;	// line : 214 Join Server
wsJoinServerCli wsDataCli;	// line : 215 DataServer
wsJoinServerCli wsExDbCli;	// line : 239 Extra DataBase Server
wsJoinServerCli wsRServerCli;	// line : 244 Ranking Server
wsJoinServerCli wsEvenChipServerCli; // line : 246 EVENT_MU2003

MapClass MapC[MAX_NUMBER_MAP];	// line 249	// Map Manager
CMonsterAttr gMAttr;	// line 250
CMonsterSetBase gMSetBase;	// line 251
classdef DCInfo;	// line 252:
CWhisperCash WhisperCash;	// line 253
PartyClass gParty;	// line 254

WzUdp gUdpSoc;	// line 256
WzUdp gUdpSocCE;	// line 258
WzUdp gUdpSocCER;	// line 259
WzUdp gUdpSocCRank;	// line 261
WzUdp gUdpSocCRankR;	//line 262

CGuildClass Guild;	// line 265
CMsg lMsg;	// line 324

NSerialCheck gNSerialCheck[OBJMAX];	// line 326
DWORD  gLevelExperience[400 + 1];
char szServerName[50];
BOOL gIsDropDarkLordItem;
int  gSleeveOfLordDropRate;
int  gSleeveOfLordDropLevel;

int  gSoulOfDarkHorseDropRate;
int  gSoulOfDarkHorseropLevel;
int  gSoulOfDarkSpiritDropRate;
int  gSoulOfDarkSpiritDropLevel;
float gDarkSpiritAddExperience;
BOOL gIsDropGemOfDefend;
int  gGemOfDefendDropRate;
int  gGemOfDefendDropLevel;
int  g_iUseCharacterAutoRecuperationSystem;
int  g_iCharacterRecuperationMaxLevel;
int g_iServerGroupGuildChatting;
int g_iServerGroupUnionChatting;

int g_iSkillDistanceCheck;
int g_iSkillDistanceCheckTemp;
int g_iSkillDistanceKick;
int g_iSkillDistanceKickCount;
int g_iSkillDiatanceKickCheckTime;

DWORD dwgCheckSum[MAX_CHECKSUM_KEY];
char connectserverip[20];
int  connectserverport;
short gGameServerCode;
int  gPkTime;
BOOL g_bCastleGuildDestoyLimit;
DWORD  gItemNumberCount;
BOOL gStalkProtocol;
DWORD  gAttackEventRegenTime;
int  gYear;
BOOL gOnlyFireCrackerEffectUse;
int  g_iRingOrcKillGiftRate;
int  g_iRingDropGiftRate;

CSimpleModulus g_SimpleModulusCS;	// line 751
CSimpleModulus g_SimpleModulusSC;	// line 752

int  gEledoradoGoldGoblenItemDropRate;
int  gEledoradoTitanItemDropRate;
int  gEledoradoGoldDerconItemDropRate;
int  gEledoradoDevilLizardKingItemDropRate;
int  gEledoradoDevilTantarosItemDropRate;
int  gEledoradoGoldGoblenExItemDropRate;
int  gEledoradoTitanExItemDropRate;
int  gEledoradoGoldDerconExItemDropRate;
int  gEledoradoDevilLizardKingExItemDropRate;
int  gEledoradoDevilTantarosExItemDropRate;
int  giKundunRefillHPSec;
int  giKundunRefillHP;
int  giKundunRefillHPTime;
int  giKundunHPLogSaveTime;
int g_PKLevelIncreaseOff;
char gMapName[MAX_NUMBER_MAP][50];
char szClientVersion[8] = "000000";
BOOL bCanTrade = 1;
BOOL bCanChaosBox = 1;
BOOL bCanWarehouseLock = 1;
// Here Appears Ring Data :
int  MapMinUserLevel[MAX_NUMBER_MAP] = { 0, 20, 15, 10, 80, 0, 0, 60, 130, 0, 160, 10, 36, 80, 130, 170, 210,
										310, 15, 30, 100, 160, 220, 280, 15, 50, 120, 180, 240, 300, 10, 10 };
BOOL gEnableBattleSoccer = 1;
int  gLootingTime = 3;
int  gPkItemDrop = 1;
int  gItemDropPer = 10;
int  gEvent1ItemDropTodayMax = 1;
int  gEvent1ItemDropTodayPercent = 80;
int  gCharacterDeleteMinLevel = 40;
BOOL gCreateCharacter = 1;
BOOL gGuildCreate = 1;
BOOL gGuildDestroy = 1;
int  gGuildCreateLevel = 100;
BOOL gItemSerialCheck = 1;
int  g_XMasEvent_StarOfXMasDropRate = 80;
int  g_XMasEvent_ItemDropRateForStarOfXMas = 2;
int  gFireCrackerDropRate = 80;
int  g_ItemDropRateForgFireCracker = 2;
int  gHeartOfLoveDropRate = 80;
int  g_ItemDropRateForgHeartOfLove = 2;
int  gGoldMedalDropRate = 2;
int  gSilverMedalDropRate = 2;
int  g_ItemDropRateForGoldMedal = 2;
int  g_ItemDropRateForSilverMedal = 2;
int  gBoxOfGoldDropRate = 2;
int  g_ItemDropRateForBoxOfGold = 2;
int  g_EventChipDropRateForBoxOfGold = 2;
int  gEyesOfDevilSquareDropRate = 2;
int  gKeyOfDevilSquareDropRate = 2;
int  gDQChaosSuccessRateLevel1 = 75;
int  gDQChaosSuccessRateLevel2 = 70;
int  gDQChaosSuccessRateLevel3 = 65;
int  gDQChaosSuccessRateLevel4 = 60;
int  gDQChaosSuccessRateLevel5 = 55;
int  gDQChaosSuccessRateLevel6 = 50;
BOOL g_bBloodCastle = 1;
int  g_iBloodCastle_StartHour = 1;
int  g_iStoneDropRate = 60;
int  g_iAngelKingsPaperDropRate = 10;
int  g_iBloodBoneDropRate = 20;
BOOL g_bChaosCastle = 1;
BOOL gItemDropRingOfTransform = 1;
int  gQuestNPCTeleportTime = 60;
DWORD  gEledoradoGoldGoblenRegenTime = 60;
DWORD  gEledoradoTitanRegenTime = 60;
DWORD  gEledoradoGoldDerconRegenTime = 60;
DWORD  gEledoradoDevilLizardKingRegenTime = 60;
DWORD  gEledoradoDevilTantarosRegenTime = 60;
int  gZenDurationTime = 30;
int gMonsterHPAdjust = 100;
BOOL gEnableCheckPenetrationSkill = TRUE;

//DevGamesX 18/11/2018 - BotSystem
int CmdBotPetAF;
int TradeLog;
bool AlreadyReaded = false;

#if (GS_CASTLE==1)
BOOL g_bDoCastleDeepEvent;
int gIsDropSetItemInCastleHuntZone;
int gSetItemInCastleHuntZoneDropRate;
int gSetItemInCastleHuntZoneDropLevel;
int g_iCastleItemMixLimit = 1;
CItemBagEx CastleItemMixItemBag;
CItemBagEx CastleHuntZoneBossItemBag;
#endif

void CheckSumFileLoad(char* szCheckSum);

void gSetDate() // Good
{
	tm *today;
	time_t ltime;

	time(&ltime);
	today = localtime(&ltime);

	today->tm_year = today->tm_year + 1900;
	gYear = today->tm_year;
}

BOOL gJoomin15Check(char* szJN) // Status : Good
{
	int tyear = 1900;
	char szTyear[3] = "";

	if (szJN[6] == 51 || szJN[6] == 52)
	{
		tyear = 2000;
	}

	memcpy(&szTyear[0], szJN, sizeof(szTyear) - 1);

	tyear = tyear + atoi(&szTyear[0]);
	if ((gYear - 15) < tyear)
	{
		return 0;
	}
	return 1;
}

BOOL gJoominCheck(char* szJN, int iLimitAge)
{
	if (iLimitAge < 0)
	{
		return 1;
	}

	int tyear = 1900;
	char szTyear[3] = "";

	if (szJN[6] == 51 || szJN[6] == 52)
	{
		tyear = 2000;
	}

	memcpy(&szTyear[0], szJN, sizeof(szTyear) - 1);

	tyear = tyear + atoi(&szTyear[0]);

	if ((gYear - iLimitAge) < tyear)
	{
		return 0;
	}

	return 1;
}

void GameMainInit(HWND hWnd)
{
	srand(time(NULL));

	ReadServerInfo();
	gSetDate();
	LogInit(TRUE);
	ReadCommonServerInfo();
	Manager.Initialize();
	Load();

	_beginthread(&cFunctions::Thread, 0, NULL);
	_beginthread(&cPotion::Thread1, 0, NULL);
	_beginthread(&cPotion::Thread2, 0, NULL);

	g_MapServerManager.LoadData("..\\Data\\MapServerInfo.txt");

#if (GS_CASTLE == 1)
	if (g_CastleSiege.Ready(g_MapServerManager.GetMapSvrGroup()) == TRUE)
	{
		if (g_CastleSiege.LoadData("..\\Data\\Event\\MuCastleData.txt"))
		{
			g_CastleSiege.LoadPreFixData(COMMONSERVER_FILE);
			g_CastleSiege.SetDataLoadState(CASTLESIEGE_DATALOAD_2);
		}
	}
#endif

	if (gEnableServerDivision != 0)
	{
		MessageBox(NULL, "서버분할이 가능한 서버입니다.", "Warning", MB_OK);
	}

	if (gUdpSoc.CreateSocket() == 0)
	{
		MsgBox("UDP Socket create error");
		return;
	}

	gObjInit();
	InitBattleSoccer();

	gMAttr.LoadAttr("..\\Data\\Monster\\Monster.txt");

#if (GS_CASTLE == 1)
	gMSetBase.LoadSetBase("..\\Data\\Monster\\MonsterSetBase_CS.txt");
#else
	gMSetBase.LoadSetBase("..\\Data\\Monster\\MonsterSetBase.txt");
#endif

	g_MonsterItemMng.Init();

	gLevelExperience[0] = 0;

	int LevelOver = 1;

	for (int i = 1; i < 400 + 1; i++)
	{
		gLevelExperience[i] = (((i + 9) * i) * i) * 10;

		if (i > 255)
		{
			gLevelExperience[i] += ((((LevelOver + 9) * LevelOver) * LevelOver) * 1000);
			LevelOver++;
		}
	}

	char MapAttrName[MAX_NUMBER_MAP][34] =
	{
		"..\\Data\\Terrain\\Terrain1.att",
		"..\\Data\\Terrain\\Terrain2.att",
		"..\\Data\\Terrain\\Terrain3.att",
		"..\\Data\\Terrain\\Terrain4.att",
		"..\\Data\\Terrain\\Terrain5.att",
		"..\\Data\\Terrain\\Terrain6.att",
		"..\\Data\\Terrain\\Terrain7.att",
		"..\\Data\\Terrain\\Terrain8.att",
		"..\\Data\\Terrain\\Terrain9.att",
		"..\\Data\\Terrain\\Terrain10.att",
		"..\\Data\\Terrain\\Terrain11.att",
		"..\\Data\\Terrain\\Terrain12.att",
		"..\\Data\\Terrain\\Terrain12.att",
		"..\\Data\\Terrain\\Terrain12.att",
		"..\\Data\\Terrain\\Terrain12.att",
		"..\\Data\\Terrain\\Terrain12.att",
		"..\\Data\\Terrain\\Terrain12.att",
		"..\\Data\\Terrain\\Terrain12.att",
		"..\\Data\\Terrain\\Terrain19.att",
		"..\\Data\\Terrain\\Terrain19.att",
		"..\\Data\\Terrain\\Terrain19.att",
		"..\\Data\\Terrain\\Terrain19.att",
		"..\\Data\\Terrain\\Terrain19.att",
		"..\\Data\\Terrain\\Terrain19.att",
		"..\\Data\\Terrain\\Terrain25.att",
		"..\\Data\\Terrain\\Terrain25.att",
		"..\\Data\\Terrain\\Terrain25.att",
		"..\\Data\\Terrain\\Terrain25.att",
		"..\\Data\\Terrain\\Terrain25.att",
		"..\\Data\\Terrain\\Terrain25.att",
		"..\\Data\\Terrain\\Terrain31.att",
		"..\\Data\\Terrain\\Terrain32.att",
		"..\\Data\\Terrain\\Terrain33.att",
		"..\\Data\\Terrain\\Terrain34.att",
		"..\\Data\\Terrain\\Terrain35.att",
		"..\\Data\\Terrain\\Terrain36.att",
		"..\\Data\\Terrain\\Terrain37.att",
	};

	for (int i = 0; i < MAX_NUMBER_MAP; i++)
	{
		MapC[i].ItemInit();
		MapC[i].LoadMapAttr(MapAttrName[i], i);
	}

	DCInfo.Init();
	ShopDataLoad();
	wsGServer.CreateSocket(hWnd);
	wsJServerCli.CreateSocket(hWnd);
	wsDataCli.CreateSocket(hWnd);
	wsRServerCli.CreateSocket(hWnd);
	wsEvenChipServerCli.CreateSocket(hWnd);
	GameServerInfoSend();
	GameMonsterAllAdd();
}

int GetWarehouseUsedHowMuch(int UserLevel, BOOL IsLock)
{
	int rZen = 0;
	rZen = (UserLevel * UserLevel)* 0.1 * 0.4;

	if (bCanWarehouseLock == TRUE)
	{
		if (IsLock != 0)
		{
			rZen = rZen + (UserLevel * 2);
		}
	}
	if (rZen < 1)
	{
		rZen = 1;
	}

	if (rZen >= 1000)
	{
		rZen = (rZen / 100) * 100;
	}

	else if (rZen >= 100)
	{
		rZen = (rZen / 10) * 10;
	}

	if (rZen == 0)
	{
		rZen = 1;
	}

	return rZen;
}

void GameMonsterAllAdd()
{
	int result;

	for (int n = 0; n < gMSetBase.m_Count; n++)
	{
		if (DS_MAP_RANGE(gMSetBase.m_Mp[n].m_MapNumber) != FALSE)
		{
			continue;
		}

		if (BC_MAP_RANGE(gMSetBase.m_Mp[n].m_MapNumber) != FALSE)
		{
			if (gMSetBase.m_Mp[n].m_Type != 232)
			{
				continue;
			}
		}

		if (CC_MAP_RANGE(gMSetBase.m_Mp[n].m_MapNumber) != FALSE)
		{
			continue;
		}

		result = gObjAddMonster(gMSetBase.m_Mp[n].m_MapNumber);

		if (result >= 0)
		{
			gObjSetPosMonster(result, n);
			gObjSetMonster(result, gMSetBase.m_Mp[n].m_Type);

			if (BC_MAP_RANGE(gObj[result].MapNumber))
			{
				if (gObj[result].Class == 232)
				{
					gObj[result].m_cBloodCastleIndex = gObj[result].MapNumber - MAP_INDEX_BLOODCASTLE1;
				}
			}
#if(GS_CASTLE==1)
			if (gObj[result].Class == 216)
			{
				g_CastleSiege.SetCrownIndex(result);
			}
#endif
		}
	}

#if(GS_CASTLE==1)
	gDevilSquareEvent = FALSE;
	g_bChaosCastle = FALSE;
#endif

	g_DevilSquare.Init();
	g_BloodCastle.LoadItemDropRate();

#if(GS_CASTLE==1)
	g_bBloodCastle = FALSE;
#endif

	if (g_bBloodCastle != FALSE)
	{
		g_BloodCastle.Init(TRUE);
	}
	else
	{
		g_BloodCastle.Init(FALSE);
	}

	if (g_bChaosCastle != FALSE)
	{
		g_ChaosCastle.Init(TRUE);
	}
	else
	{
		g_ChaosCastle.Init(FALSE);
	}
#if (FREE_GAMESERVER==0)
	
	//DevGamesX 11/03/2018 - BotStore
	BotStore.MakeBot();

#endif
}

void GameMonsterAllCloseAndReLoad()
{
	for (int i = 0; i < OBJ_MAXMONSTER; i++)
	{
		if (gObj[i].Type == OBJ_MONSTER || gObj[i].Type == OBJ_NPC)
		{
			gObj[i].Live = FALSE;
			gObjViewportListProtocolDestroy(&gObj[i]);
			gObjViewportClose(&gObj[i]);
            gObjDel(i);
		}
	}

	gMAttr.LoadAttr("..\\Data\\Monster\\Monster.txt");

#if (GS_CASTLE == 1)
	gMSetBase.LoadSetBase("..\\Data\\Monster\\MonsterSetBase_CS.txt");
#else
	gMSetBase.LoadSetBase("..\\Data\\Monster\\MonsterSetBase.txt");
#endif

	g_MonsterItemMng.Init();
	gObjMonCount = 0;
	GameMonsterAllAdd();
}

void GameMainFree()
{
	GDGameServerInfoSave();
	gObjEnd();
	ClearBattleSoccer();
}

BOOL GMJoinServerConnect(LPSTR ConnectServer, DWORD wMsg)
{
	wsJServerCli.SetProtocolCore(SProtocolCore);
	int result = wsJServerCli.Connect(ConnectServer, JoinServerPort, wMsg);

	if (result == 0)
	{
		return FALSE;
	}

	GJServerLogin();

	LogAdd(lMsg.Get(MSGGET(1, 145)), ConnectServer);
	return TRUE;
}

BOOL GMRankingServerConnect(char* RankingServer, DWORD wMsg)
{
	wsRServerCli.SetProtocolCore(DevilSquareProtocolCore);

	int result = wsRServerCli.Connect(RankingServer, RANKING_SERVER_PORT, wMsg);

	if (result == 0)
	{
		return FALSE;
	}

	LogAdd("RankingServer Connect IP [ %s ]", RankingServer);
	return TRUE;
}

BOOL GMEventChipServerConnect(char* ServerIP, DWORD wMsg)
{
	wsEvenChipServerCli.SetProtocolCore(EventChipEventProtocolCore);

	int result = wsEvenChipServerCli.Connect(ServerIP, EVENT_CHIP_SERVER_PORT, wMsg);

	if (result == 0)
	{
		return FALSE;
	}

	LogAdd("EventChip Connect IP [ %s ]", ServerIP);
	return TRUE;
}

BOOL GMDataServerConnect(char* ConnectServer, WPARAM wMsg)
{
	wsDataCli.SetProtocolCore(DataServerProtocolCore);

	int result = wsDataCli.Connect(ConnectServer, DataServerPort, wMsg);

	if (result == 0)
	{
		LogAdd(lMsg.Get(MSGGET(1, 147)), ConnectServer, DataServerPort);
		return FALSE;
	}

	DataServerLogin(0);

	LogAdd(lMsg.Get(MSGGET(1, 146)), ConnectServer, DataServerPort);
	return TRUE;
}

BOOL ExDataServerConnect(char* ConnectServer, DWORD wMsg)
{
	wsExDbCli.SetProtocolCore(ExDataServerProtocolCore);

	int result = wsExDbCli.Connect(ConnectServer, ExDbPort, wMsg);

	if (result == 0)
	{
		LogAdd(lMsg.Get(MSGGET(1, 147)), ConnectServer, ExDbPort);
		return FALSE;
	}

	ExDataServerLogin();
	LogAddC(2, "ExDB Server Online");
	return TRUE;
}

BOOL GameMainServerCreate(DWORD sMsg, DWORD cMsg)
{
	LogAdd(lMsg.Get(MSGGET(1, 148)), GameServerPort);
	return TRUE;
}

void GMServerMsgProc(WPARAM wParam, LPARAM lParam)
{
	{
		int unk = lParam & 0xFFFF & 0xFFFF;	// HERE is a switch here goes a macro
	}
}

void GMClientMsgProc(WPARAM wParam, LPARAM lParam)
{
	int wp = wParam;
	int lp = lParam;

	switch (lParam & 0xFFFF & 0xFFFF)
	{
		SOCKET socket;

	case 1:
		wsGServer.DataRecv(wParam);
		break;

	case 2:
		wsGServer.FDWRITE_MsgDataSend(wParam);
		break;

	case 32:
		socket = gObjGetSocket(wParam);
		break;
	}
}

void GMJoinClientMsgProc(WPARAM wParam, LPARAM lParam)
{
	switch (lParam & 0xFFFF & 0xFFFF)
	{
	case 1:
		wsJServerCli.DataRecv();
		break;

	case 2:
		wsJServerCli.FDWRITE_MsgDataSend();
		break;

	case 32:
		LogAddC(2, lMsg.Get(MSGGET(1, 149)));
		SendMessage(ghWnd, WM_CLOSE, 0, 0);
	}
}

void GMRankingClientMsgProc(WPARAM wParam, LPARAM lParam)
{
	switch (lParam & 0xFFFF & 0xFFFF)
	{
	case 1:
		wsRServerCli.DataRecv();
		break;

	case 2:
		wsRServerCli.FDWRITE_MsgDataSend();
		break;

	case 32:
		IsDevilSquareEventConnected = FALSE;
	}
}

void GMEventChipClientMsgProc(WPARAM wParam, LPARAM lParam)
{
	switch (lParam & 0xFFFF & 0xFFFF)
	{
	case 1:
		wsEvenChipServerCli.DataRecv();
		break;

	case 2:
		wsEvenChipServerCli.FDWRITE_MsgDataSend();
		break;

	case 32:
		IsEventChipServerConnected = FALSE;
	}
}

void ExDataClientMsgProc(WPARAM wParam, LPARAM lParam)
{
	switch (lParam & 0xFFFF & 0xFFFF)
	{
	case 1:
		wsExDbCli.DataRecv();
		break;

	case 2:
		wsExDbCli.FDWRITE_MsgDataSend();
		break;

	case 32:
		LogAddC(2, lMsg.Get(MSGGET(1, 150)));
		wsExDbCli.Close();

		for (int i = 0; i < OBJMAX; i++)
		{
			if (gObjIsConnectedGP(i) == TRUE)
			{
				PMSG_FRIEND_STATE pMsg;

				pMsg.h.set((LPBYTE)&pMsg, 0xC4, sizeof(pMsg));
				pMsg.State = -4;

				DataSend(i, (unsigned char*)&pMsg, sizeof(pMsg));

				gObj[i].m_FriendServerOnline = FRIEND_SERVER_STATE_OFFLINE;
			}
		}

		LogAdd("Error-L1 : Friend Server Down (State Send Ok)");
		LogAddC(2, "Error-L1 : Friend Server Down (State Send Ok)");
		break;
	}
}

void GMDataClientMsgProc(WPARAM wParam, LPARAM lParam)
{
	switch (lParam & 0xFFFF & 0xFFFF)
	{
	case 1:
		wsDataCli.DataRecv();
		break;

	case 2:
		wsDataCli.FDWRITE_MsgDataSend();
		break;

	case 32:
		LogAddC(2, lMsg.Get(MSGGET(1, 150)));
	}
}

void ReadServerInfo()
{
	if (!IsFile("DATA\\Serverinfo.dat"))
	{
		MsgBox("ServerInfo.dat file not found");
	}

	GetPrivateProfileString("GameServerInfo","ServerName","",szServerName,50,"DATA\\Serverinfo.dat");
	gGameServerCode = GetPrivateProfileInt("GameServerInfo","ServerCode", 0,"DATA\\Serverinfo.dat");
}

void ReadCommonServerInfo()
{
	char szTemp[256];
	char szCheckSum[256];
	char* cvstr;
	char szlMsgName[256];

	ReadServerInfo();

	gGateC.Load("..\\Data\\Move\\Gate.txt");

	if (!IsFile(COMMONSERVER_FILE))
	{
		MsgBox("[commonserver.ini] file not found");
	}

	gStalkProtocol = GetPrivateProfileInt("GameServerInfo", "StalkProtocol", 0, COMMONSERVER_FILE);
	GetPrivateProfileString("GameServerInfo", "StalkProtocolId", "0", gStalkProtocolId, 10, COMMONSERVER_FILE);

	if (gStalkProtocol != 0)
	{
		LogAdd("Stalk Protocol ID = '%s' ", gStalkProtocolId);
	}

	if (g_SimpleModulusCS.LoadDecryptionKey("..\\Data\\Security\\Decrypt.dat") == FALSE)
	{
		MsgBox("Decrypt.dat file not found");
	}
	if (g_SimpleModulusSC.LoadEncryptionKey("..\\Data\\Security\\Encrypt.dat") == FALSE)
	{
		MsgBox("Encrypt.dat file not found");
	}

	gNonPK = GetPrivateProfileInt("GameServerInfo", "NonPK", 0, ".\\Data\\Serverinfo.dat");

	if (gNonPK != 0)
	{
		LogAdd("NON-PK Server");
	}

	gPkLimitFree = GetPrivateProfileInt("GameServerInfo", "PkLimitFree", 0, ".\\Data\\Serverinfo.dat");

	if (gPkLimitFree != 0)
	{
		LogAdd("PK Limit Free Server");
	}

	CheckSumFileLoad("..\\Data\\Security\\Checksum.dat");
	lMsg.Load("..\\Data\\Message.txt");
	SetMapName();

	OpenItemScript("..\\Data\\Item\\Item.txt");
	MagicDamageC.LogSkillList("..\\Data\\Skill\\Skill.txt");
	gSetItemOption.LoadOptionInfo("..\\Data\\Item\\ItemSetOption.txt");
	gSetItemOption.LoadTypeInfo("..\\Data\\Item\\ItemSetType.txt");
	g_QuestInfo.LoadQuestInfo("..\\Data\\Quest\\Quest.txt");
	gMoveCommand.Load("..\\Data\\Move\\MoveReq.txt");
	SkillSpearHitBox.Load("..\\Data\\Skill\\SkillSpear.hit");
	SkillElectricSparkHitBox.Load("..\\Data\\Skill\\SkillElect.hit");
	gMoveCommand.LoadMoveLevel("..\\Data\\Move\\MoveLevel.txt");

	GetPrivateProfileString("GameServerInfo", "ClientExeVersion", "", szTemp, sizeof(szTemp), COMMONSERVER_FILE);
	
	GetPrivateProfileString("GameServerInfo", "ClientExeSerial", "", Setting._Serial, sizeof(Setting._Serial), COMMONSERVER_FILE);

	cvstr = strtok(szTemp, ".");
	szClientVersion[0] = cvstr[0];
	cvstr = strtok(NULL, ".");
	szClientVersion[1] = cvstr[0];
	szClientVersion[2] = cvstr[1];
	cvstr = strtok(NULL, ".");
	szClientVersion[3] = cvstr[0];
	szClientVersion[4] = cvstr[1];

	// Skill Addition
	g_SkillAdditionInfo.Load("..\\Data\\Skill\\SkillAdditionInfo.txt");

	GetPrivateProfileString("GameServerInfo", "CreateCharacter", "1", szTemp, 5, COMMONSERVER_FILE);
	gCreateCharacter = atoi(szTemp);
	GetPrivateProfileString("GameServerInfo", "CharacterDeleteMinLevel", "40", szTemp, 5, COMMONSERVER_FILE);
	gCharacterDeleteMinLevel = atoi(szTemp);

#if(GS_CASTLE==0)
	int iMaxUser = GetPrivateProfileInt("GameServerInfo", "NumberOfMaxUser", 500, COMMONSERVER_FILE);
#else
	int iMaxUser = GetPrivateProfileInt("GameServerInfo", "NumberOfCastleSiegeMaxUser", 1500, COMMONSERVER_FILE);
#endif

	if (iMaxUser >= 0 && iMaxUser <= OBJMAXUSER)
	{
		gServerMaxUser = iMaxUser;
		LogAdd("[Option Reload] ★★★ MaxUser ☆☆☆  : %d", gServerMaxUser);
	}

	// Guild Settingss
	g_iServerGroupGuildChatting = GetPrivateProfileInt("GameServerInfo", "ServerGroupGuildChatting", 0, COMMONSERVER_FILE);
	g_iServerGroupUnionChatting = GetPrivateProfileInt("GameServerInfo", "ServerGroupUnionChatting", 0, COMMONSERVER_FILE);
	GetPrivateProfileString("GameServerInfo", "GuildCreate", "1", szTemp, 5, COMMONSERVER_FILE);
	gGuildCreate = atoi(szTemp);
	// Guild creation option %d
	LogAdd(lMsg.Get(MSGGET(2, 57)), gGuildCreate);
	GetPrivateProfileString("GameServerInfo", "GuildDestroy", "1", szTemp, 5, COMMONSERVER_FILE);
	// Guild delete option %d
	gGuildDestroy = atoi(szTemp);
	LogAdd(lMsg.Get(MSGGET(2, 58)), gGuildDestroy);
	GetPrivateProfileString("GameServerInfo", "GuildCreateLevel", "100", szTemp, 5, COMMONSERVER_FILE);
	gGuildCreateLevel = atoi(szTemp);
	// Above level %d can create guild
	LogAdd(lMsg.Get(MSGGET(2, 59)), gGuildCreateLevel);

	g_bCastleGuildDestoyLimit = GetPrivateProfileInt("GameServerInfo", "CastleOwnerGuildDestroyLimit", 1, COMMONSERVER_FILE);

	GetPrivateProfileString("GameServerInfo", "SpeedHackPlayerBlock", "0", szTemp, 5, COMMONSERVER_FILE);
	SpeedHackPlayerBlock = atoi(szTemp);
	GetPrivateProfileString("GameServerInfo", "ItemSerialCheck", "1", szTemp, 5, COMMONSERVER_FILE);
	gItemSerialCheck = atoi(szTemp);

	GetPrivateProfileString("GameServerInfo", "Trade", "1", szTemp, 5, COMMONSERVER_FILE);
	bCanTrade = atoi(szTemp);

	if (bCanTrade != 0)
	{
		LogAdd(lMsg.Get(407));
	}
	else
	{
		LogAdd(lMsg.Get(408));
	}

	bCanChaosBox = GetPrivateProfileInt("GameServerInfo", "ChaosBox", 0, COMMONSERVER_FILE);
	gChaosEvent = GetPrivateProfileInt("GameServerInfo", "ChaosEvent", 0, COMMONSERVER_FILE);
	GetPrivateProfileString("GameServerInfo", "ChaosEventServer", "210.181.89.241", gChaosEventServerIp, 20, COMMONSERVER_FILE);
	LogAdd("[Option] ChaosBox = %d", bCanChaosBox);
	LogAdd("[Option] ChaosEvent = %d", gChaosEvent);
	LogAdd("[Option] ChaosEventServer = %s", gChaosEventServerIp);
	LogAdd("[Option] AttackEventRegenTime = %d", gAttackEventRegenTime);
	GetPrivateProfileString("GameServerInfo", "PKTIME", "1", szTemp, 5, COMMONSERVER_FILE);
	gPkTime = atoi(szTemp);

	if (gPkTime != 0)
	{
		LogAdd(lMsg.Get(409), gPkTime);
	}

	GetPrivateProfileString("GameServerInfo", "MonsterHp", "0", szTemp, 5, COMMONSERVER_FILE);
	gMonsterHp = atoi(szTemp);

	if (gMonsterHp != 0)
	{
		LogAdd(lMsg.Get(410), gMonsterHp);
	}

	GetPrivateProfileString("GameServerInfo", "LootingTime", "3", szTemp, 5, COMMONSERVER_FILE);
	gLootingTime = atoi(szTemp);

	if (gLootingTime != 0)
	{
		LogAdd("[Option] Auto Looting Time Set : %d", gLootingTime);
	}

	GetPrivateProfileString("GameServerInfo", "PKItemDrop", "1", szTemp, 5, COMMONSERVER_FILE);
	gPkItemDrop = atoi(szTemp);

	if (gPkItemDrop != 0)
	{
		LogAdd(lMsg.Get(MSGGET(1, 155)));
	}
	else
	{
		LogAdd(lMsg.Get(MSGGET(1, 156)));
	}

	GetPrivateProfileString("GameServerInfo", "ItemDropPer", "10", szTemp, 5, COMMONSERVER_FILE);
	gItemDropPer = atoi(szTemp);
	LogAddTD(lMsg.Get(413), gItemDropPer);

	gZenDurationTime = GetPrivateProfileInt("GameServerInfo", "ZenDurationTime", 30, COMMONSERVER_FILE);
	gEventChipEvent = GetPrivateProfileInt("GameServerInfo", "EventChipEvent", 0, COMMONSERVER_FILE);
	gBoxOfGoldDropRate = GetPrivateProfileInt("GameServerInfo", "BoxOfGoldDropRate", 2, COMMONSERVER_FILE);
	g_ItemDropRateForBoxOfGold = GetPrivateProfileInt("GameServerInfo", "ItemDropRateForBoxOfGold", 2, COMMONSERVER_FILE);
	g_EventChipDropRateForBoxOfGold = GetPrivateProfileInt("GameServerInfo", "EventChipDropRateForBoxOfGold", 2, COMMONSERVER_FILE);

	if (gDevilSquareEvent == FALSE)
	{
		g_DevilSquare.SetClose();
	}

	// Ring of Transform
	gIsItemDropRingOfTransform = GetPrivateProfileInt("GameServerInfo", "IsItemDropRingOfTransform", 0, COMMONSERVER_FILE);
	gItemDropRingOfTransform = GetPrivateProfileInt("GameServerInfo", "ItemDropRingOfTransform", 1, COMMONSERVER_FILE);

	// Hack Settinhs
	gDisconnectHackUser = GetPrivateProfileInt("GameServerInfo", "DisconnectHackUser", 0, COMMONSERVER_FILE);

	// Devil Square Event
	gDQChaosSuccessRateLevel1 = GetPrivateProfileInt("GameServerInfo", "DQChaosSuccessRateLevel1", 75, COMMONSERVER_FILE);
	gDQChaosSuccessRateLevel2 = GetPrivateProfileInt("GameServerInfo", "DQChaosSuccessRateLevel2", 70, COMMONSERVER_FILE);
	gDQChaosSuccessRateLevel3 = GetPrivateProfileInt("GameServerInfo", "DQChaosSuccessRateLevel3", 65, COMMONSERVER_FILE);
	gDQChaosSuccessRateLevel4 = GetPrivateProfileInt("GameServerInfo", "DQChaosSuccessRateLevel4", 60, COMMONSERVER_FILE);
	gDQChaosSuccessRateLevel5 = GetPrivateProfileInt("GameServerInfo", "DQChaosSuccessRateLevel5", 55, COMMONSERVER_FILE);
	gDQChaosSuccessRateLevel6 = GetPrivateProfileInt("GameServerInfo", "DQChaosSuccessRateLevel6", 50, COMMONSERVER_FILE);

	// Skill Log
	gWriteSkillLog = GetPrivateProfileInt("GameServerInfo", "WriteSkillLog", 0, COMMONSERVER_FILE);

	// Marlon Teleport
	gQuestNPCTeleportTime = GetPrivateProfileInt("GameServerInfo", "QuestNPCTeleportTime", 900, COMMONSERVER_FILE);

	// Mark Lord
	g_iMarkOfTheLord = GetPrivateProfileInt("GameServerInfo", "MarkOfTheLord", 0, COMMONSERVER_FILE);

	// KUNDUN Settings
	giKundunRefillHPSec = GetPrivateProfileInt("GameServerInfo", "KundunRefillHPSec", 500, COMMONSERVER_FILE);
	giKundunRefillHP = GetPrivateProfileInt("GameServerInfo", "KundunRefillHP", 10000, COMMONSERVER_FILE);
	giKundunRefillHPTime = GetPrivateProfileInt("GameServerInfo", "KundunRefillHPTime", 600, COMMONSERVER_FILE);
	giKundunHPLogSaveTime = GetPrivateProfileInt("GameServerInfo", "KundunHPLogSaveTime", 120, COMMONSERVER_FILE);

	// Servers
	GetPrivateProfileString("ConnectServerInfo", "IP", "", connectserverip, 20, COMMONSERVER_FILE);
	GetPrivateProfileString("ConnectServerInfo", "PORT", "", szTemp, 10, COMMONSERVER_FILE);
	connectserverport = atoi(szTemp);
	// (Option) Connect Server IP(%s) / PORT(%d)
	LogAdd(lMsg.Get(MSGGET(1, 158)), connectserverip, connectserverport);
	gUdpSoc.SendSet(connectserverip, connectserverport);
	gUdpSocCE.SendSet(gChaosEventServerIp, 60005);
	DevilSquareEventConnect = GetPrivateProfileInt("GameServerInfo", "DevilSquareEventConnect", 1, COMMONSERVER_FILE);
	GetPrivateProfileString("GameServerInfo", "DevilSquareEventServer", "210.181.89.241", gDevilSquareEventServerIp, 20, COMMONSERVER_FILE);
	EventChipServerConnect = GetPrivateProfileInt("GameServerInfo", "EventChipServerConnect", 0, COMMONSERVER_FILE);
	GetPrivateProfileString("GameServerInfo", "EventChipServerIp", "192.168.10.150", gEventChipServerIp, 20, COMMONSERVER_FILE);

	// Hero System
	gApplyHeroSystem = GetPrivateProfileInt("GameServerInfo", "ApplyHeroSystem", 0, COMMONSERVER_FILE);

	// Battle Soccer
	gEnableBattleSoccer = GetPrivateProfileInt("GameServerInfo", "EnableBattleSoccer", 1, COMMONSERVER_FILE);

	// NPC Talk
	gEnableEventNPCTalk = GetPrivateProfileInt("GameServerInfo", "EnableEventNPCTalk", 0, COMMONSERVER_FILE);

	// Server Division
	gEnableServerDivision = GetPrivateProfileInt("GameServerInfo", "EnableServerDivision", 0, COMMONSERVER_FILE);

	// Monster HP Adjust
	gMonsterHPAdjust = GetPrivateProfileInt("GameServerInfo", "MonsterHPAdjust", 100, COMMONSERVER_FILE);

	// COMMANDS Init ( /make / Create /trace etc...)
	cManager.Init();

	// Penetration Skill
	gEnableCheckPenetrationSkill = GetPrivateProfileInt("GameServerInfo", "EnableCheckPenetrationSkill", 1, COMMONSERVER_FILE);

	// PK LEvel
	g_PKLevelIncreaseOff = GetPrivateProfileInt("GameServerInfo", "PKLevelIncreaseOff", 0, COMMONSERVER_FILE);

	// Item Bag Load
	LoadItemBag();

	// Eledorado Event Start
	gEledoradoEvent.Init();

	char WindowsText[512] = { 0 };

	wsprintf(WindowsText, "Servidor: %s, %s", szServerName, TITLE);

	SetWindowText(ghWnd, WindowsText);

	gPacketCheckSum.Init();

	gDoPShopOpen = GetPrivateProfileInt("GameServerInfo", "PersonalShopOpen", 0, COMMONSERVER_FILE);

	ReadEventInfo(MU_EVENT_ALL);

	// AutoRecuperation Level
	g_iUseCharacterAutoRecuperationSystem = GetPrivateProfileInt("GameServerInfo", "UseCharacterAutoRecuperationSystem", 0, COMMONSERVER_FILE);
	g_iCharacterRecuperationMaxLevel = GetPrivateProfileInt("GameServerInfo", "CharacterRecuperationMaxLevel", 100, COMMONSERVER_FILE);

	// Skill Check Settings
	g_iSkillDistanceCheck = GetPrivateProfileInt("GameServerInfo", "SkillDistanceCheck", 0, COMMONSERVER_FILE);
	g_iSkillDistanceCheckTemp = GetPrivateProfileInt("GameServerInfo", "SkillDistanceCheckTemp", 2, COMMONSERVER_FILE);
	g_iSkillDistanceKick = GetPrivateProfileInt("GameServerInfo", "SkillDistanceKick", 0, COMMONSERVER_FILE);
	g_iSkillDistanceKickCount = GetPrivateProfileInt("GameServerInfo", "SkillDistanceKickCount", 5, COMMONSERVER_FILE);
	g_iSkillDiatanceKickCheckTime = GetPrivateProfileInt("GameServerInfo", "SkillDistanceKickCheckTime", 10, COMMONSERVER_FILE);
#if (FREE_GAMESERVER==0)
	//DevGamesX 11/03/2018 - BotStore
	BotStore.Read("..\\Data\\Custom\\BotSystem\\BotStore.txt");
#endif

#if (FREE_GAMESERVER==0)
if (AlreadyReaded)
{
		for (int n = OBJ_MAXMONSTER; n < OBJ_STARTUSERINDEX; n++)
		{
			if (gObj[n].Type == OBJ_MONSTER || gObj[n].Type == OBJ_NPC)
			{
				if (gObj[n].IsBot >= 1 && gObj[n].BotNumOwner <= 0 && gObj[n].m_RecallMon <= 0)
				{
					/*if (gObj[n].m_iCurrentAI)
					{
						gObj[n].Live = FALSE;
						gObjViewportListProtocolDestroy(&gObj[n]);
						gObjViewportClose(&gObj[n]);
					}*/
					gObjCallMonCount--;
					gObjDel(n);
				}
			}
		}

		BotStore.MakeBot();
}

	AlreadyReaded = true;
#endif
}

void GameServerInfoSendStop()
{
	GSInfoSendFlag = 0;
}

void GameServerInfoSendStart()
{
	GSInfoSendFlag = 1;
}

struct PMSG_SERVERINFO
{
	PBMSG_HEAD h;	// C1:01
	short ServerCode;	// 4
	BYTE Percent;	// 6
	short UserCount;	// 8
	short AccountCount;	// A
	short PCbangCount;	// C
	short MaxUserCount;	// E
};

void GameServerInfoSend()
{
	PMSG_SERVERINFO pMsg;

	if (gDisconnect == TRUE)
	{
		return;
	}

	pMsg.h.c = 0xC1;
	pMsg.h.headcode = 0x01;
	pMsg.h.size = sizeof(pMsg);

	if (gObjTotalUser == 0)
	{
		pMsg.Percent = 0;
	}
	else
	{
		pMsg.Percent = (gObjTotalUser * 100) / gServerMaxUser;
	}

	pMsg.ServerCode = gGameServerCode;
	pMsg.UserCount = gObjTotalUser;
	pMsg.AccountCount = 0;
	pMsg.PCbangCount = 0;
	pMsg.MaxUserCount = gServerMaxUser;

	gUdpSoc.SendData((LPBYTE)&pMsg, pMsg.h.size);
}

void CheckSumFileLoad(char * szCheckSum)
{
	FILE* fp = fopen(szCheckSum, "rb");

	if (fp == NULL)
	{
		MsgBox("%s file not found", szCheckSum);
		return;
	}

	fread(dwgCheckSum, 1024 * sizeof(DWORD), 1, fp);
	fclose(fp);
}

void LoadItemBag() //Identical
{
	LuckboxItemBag.Init("..\\Data\\Bag\\Bag01.txt");
	Mon55.Init("..\\Data\\Bag\\Bag02.txt");
	Mon53.Init("..\\Data\\Bag\\Bag03.txt");
	StarOfXMasItemBag.Init("..\\Data\\Bag\\Bag04.txt");
	FireCrackerItemBag.Init("..\\Data\\Bag\\Bag05.txt");
	HeartOfLoveItemBag.Init("..\\Data\\Bag\\Bag05.txt");
	GoldMedalItemBag.Init("..\\Data\\Bag\\Bag06.txt");
	SilverMedalItemBag.Init("..\\Data\\Bag\\Bag07.txt");
	GoldGoblenItemBag.Init("..\\Data\\Bag\\Bag08.txt");
	TitanItemBag.Init("..\\Data\\Bag\\Bag09.txt");
	GoldDerconItemBag.Init("..\\Data\\Bag\\Bag10.txt");
	DevilLizardKingItemBag.Init("..\\Data\\Bag\\Bag11.txt");
	KanturItemBag.Init("..\\Data\\Bag\\Bag12.txt");
	RingEventItemBag.Init("..\\Data\\Bag\\Bag13.txt");
	FriendShipItemBag.Init("..\\Data\\Bag\\Bag14.txt");
	DarkLordHeartItemBag.Init("..\\Data\\Bag\\Bag15.txt");
	KundunEventItemBag.Init("..\\Data\\Bag\\Bag17.txt");

#if(GS_CASTLE==1)
	CastleHuntZoneBossItemBag.Init("..\\Data\\Bag\\Bag18.txt");
	CastleItemMixItemBag.Init("..\\Data\\Bag\\Bag19.txt");
#endif

	HiddenTreasureBoxItemBag.Init("..\\Data\\Bag\\Bag20.txt");
}

void SetMapName()
{
	strcpy(gMapName[0], lMsg.Get(MSGGET(7, 208)));
	strcpy(gMapName[1], lMsg.Get(MSGGET(7, 209)));
	strcpy(gMapName[2], lMsg.Get(MSGGET(7, 210)));
	strcpy(gMapName[3], lMsg.Get(MSGGET(7, 211)));
	strcpy(gMapName[4], lMsg.Get(MSGGET(7, 212)));
	strcpy(gMapName[5], "Reserved");
	strcpy(gMapName[6], lMsg.Get(MSGGET(7, 214)));
	strcpy(gMapName[7], lMsg.Get(MSGGET(7, 213)));
	strcpy(gMapName[8], lMsg.Get(MSGGET(7, 216)));
	strcpy(gMapName[9], lMsg.Get(MSGGET(7, 217)));
	strcpy(gMapName[10], lMsg.Get(MSGGET(7, 221)));
	strcpy(gMapName[11], lMsg.Get(MSGGET(7, 222)));
	strcat(gMapName[11], "1");
	strcpy(gMapName[12], lMsg.Get(MSGGET(7, 222)));
	strcat(gMapName[12], "2");
	strcpy(gMapName[13], lMsg.Get(MSGGET(7, 222)));
	strcat(gMapName[13], "3");
	strcpy(gMapName[14], lMsg.Get(MSGGET(7, 222)));
	strcat(gMapName[14], "4");
	strcpy(gMapName[15], lMsg.Get(MSGGET(7, 222)));
	strcat(gMapName[15], "5");
	strcpy(gMapName[16], lMsg.Get(MSGGET(7, 222)));
	strcat(gMapName[16], "6");
}

void ReadEventInfo(MU_EVENT_TYPE eEventType)
{
	char szTemp[256];
	switch (eEventType)
	{
	case 0: //All Events
		g_DevilSquare.Load("..\\Data\\Event\\DevilSquare.txt");
		gDevilSquareEvent = GetPrivateProfileInt("GameServerInfo", "DevilSquareEvent", 0, COMMONSERVER_FILE);
		gEyesOfDevilSquareDropRate = GetPrivateProfileInt("GameServerInfo", "EyesOfDevilSquareDropRate", 2, COMMONSERVER_FILE);
		gKeyOfDevilSquareDropRate = GetPrivateProfileInt("GameServerInfo", "KeyOfDevilSquareDropRate", 2, COMMONSERVER_FILE);
		g_BloodCastle.Load("..\\Data\\Event\\BloodCastle.txt");
		g_bBloodCastle = GetPrivateProfileInt("GameServerInfo", "BloodCastleEvent", 0, COMMONSERVER_FILE);
		g_iBloodCastle_StartHour = GetPrivateProfileInt("GameServerInfo", "BloodCastleStartHour", 1, COMMONSERVER_FILE);
		g_iAngelKingsPaperDropRate = GetPrivateProfileInt("GameServerInfo", "AngelKingsPaperDropRate", 0, COMMONSERVER_FILE);
		g_iBloodBoneDropRate = GetPrivateProfileInt("GameServerInfo", "BloodBoneDropRate", 0, COMMONSERVER_FILE);
		g_iStoneDropRate = GetPrivateProfileInt("GameServerInfo", "StoneDropRate", 0, COMMONSERVER_FILE);
		gIsDropDarkLordItem = GetPrivateProfileInt("GameServerInfo", "IsDropDarkLordItem", 0, COMMONSERVER_FILE);
		gSleeveOfLordDropRate = GetPrivateProfileInt("GameServerInfo", "SleeveOfLordDropRate", 10, COMMONSERVER_FILE);
		gSleeveOfLordDropLevel = GetPrivateProfileInt("GameServerInfo", "SleeveOfLordDropLevel", 86, COMMONSERVER_FILE);
		gSoulOfDarkHorseDropRate = GetPrivateProfileInt("GameServerInfo", "SoulOfDarkHorseDropRate", 10, COMMONSERVER_FILE);
		gSoulOfDarkHorseropLevel = GetPrivateProfileInt("GameServerInfo", "SoulOfDarkHorseropLevel", 125, COMMONSERVER_FILE);
		g_iAngelKingsPaperDropRate = GetPrivateProfileInt("GameServerInfo", "AngelKingsPaperDropRate", 0, COMMONSERVER_FILE);
		gSoulOfDarkSpiritDropRate = GetPrivateProfileInt("GameServerInfo", "SoulOfDarkSpiritDropRate", 10, COMMONSERVER_FILE);
		gSoulOfDarkSpiritDropLevel = GetPrivateProfileInt("GameServerInfo", "SoulOfDarkSpiritDropLevel", 96, COMMONSERVER_FILE);
		GetPrivateProfileString("GameServerInfo", "DarkSpiritAddExperience", "1", szTemp, 5, COMMONSERVER_FILE);
		gDarkSpiritAddExperience = (float)atof(szTemp);

		gIsDropGemOfDefend = GetPrivateProfileInt("GameServerInfo", "IsDropGemOfDefend", 0, COMMONSERVER_FILE);
		gGemOfDefendDropRate = GetPrivateProfileInt("GameServerInfo", "GemOfDefendDropRate", 5, COMMONSERVER_FILE);
		gGemOfDefendDropLevel = GetPrivateProfileInt("GameServerInfo", "GemOfDefendDropLevel", 75, COMMONSERVER_FILE);

#if (GS_CASTLE==1)
		gIsDropSetItemInCastleHuntZone = GetPrivateProfileInt("GameServerInfo", "IsDropSetItemInCastleHuntZone", 0, COMMONSERVER_FILE);
		gSetItemInCastleHuntZoneDropRate = GetPrivateProfileInt("GameServerInfo", "SetItemInCastleHuntZoneDropRate", 1, COMMONSERVER_FILE);
		gSetItemInCastleHuntZoneDropLevel = GetPrivateProfileInt("GameServerInfo", "SetItemInCastleHuntZoneDropLevel", 75, COMMONSERVER_FILE);
#endif
		gAttackEventRegenTime = GetPrivateProfileInt("GameServerInfo", "AttackEventRegenTime", 10, COMMONSERVER_FILE);
		gEledoradoEvent.EventState = GetPrivateProfileInt("GameServerInfo", "IsEledoradoEvent", 0, COMMONSERVER_FILE);
		gEledoradoGoldGoblenRegenTime = GetPrivateProfileInt("GameServerInfo", "EledoradoGoldGoblenRegenTime", 180, COMMONSERVER_FILE);
		gEledoradoTitanRegenTime = GetPrivateProfileInt("GameServerInfo", "EledoradoTitanRegenTime", 180, COMMONSERVER_FILE);
		gEledoradoGoldDerconRegenTime = GetPrivateProfileInt("GameServerInfo", "EledoradoGoldDerconRegenTime", 720, COMMONSERVER_FILE);
		gEledoradoDevilLizardKingRegenTime = GetPrivateProfileInt("GameServerInfo", "EledoradoDevilLizardKingRegenTime", 360, COMMONSERVER_FILE);
		gEledoradoDevilTantarosRegenTime = GetPrivateProfileInt("GameServerInfo", "EledoradoDevilTantarosRegenTime", 360, COMMONSERVER_FILE);
		gEledoradoGoldGoblenItemDropRate = GetPrivateProfileInt("GameServerInfo", "EledoradoGoldGoblenItemDropRate", 10, COMMONSERVER_FILE);
		gEledoradoTitanItemDropRate = GetPrivateProfileInt("GameServerInfo", "EledoradoTitanItemDropRate", 10, COMMONSERVER_FILE);
		gEledoradoGoldDerconItemDropRate = GetPrivateProfileInt("GameServerInfo", "EledoradoGoldDerconItemDropRate", 10, COMMONSERVER_FILE);
		gEledoradoDevilLizardKingItemDropRate = GetPrivateProfileInt("GameServerInfo", "EledoradoDevilLizardKingItemDropRate", 10, COMMONSERVER_FILE);
		gEledoradoDevilTantarosItemDropRate = GetPrivateProfileInt("GameServerInfo", "EledoradoDevilTantarosItemDropRate", 10, COMMONSERVER_FILE);
		gEledoradoGoldGoblenExItemDropRate = GetPrivateProfileInt("GameServerInfo", "EledoradoGoldGoblenExItemDropRate", 10, COMMONSERVER_FILE);
		gEledoradoTitanExItemDropRate = GetPrivateProfileInt("GameServerInfo", "EledoradoTitanExItemDropRate", 10, COMMONSERVER_FILE);
		gEledoradoGoldDerconExItemDropRate = GetPrivateProfileInt("GameServerInfo", "EledoradoGoldDerconExItemDropRate", 10, COMMONSERVER_FILE);
		gEledoradoDevilLizardKingExItemDropRate = GetPrivateProfileInt("GameServerInfo", "EledoradoDevilLizardKingExItemDropRate", 10, COMMONSERVER_FILE);
		gEledoradoDevilTantarosExItemDropRate = GetPrivateProfileInt("GameServerInfo", "EledoradoDevilTantarosExItemDropRate", 10, COMMONSERVER_FILE);
		GetPrivateProfileString("GameServerInfo", "RingAttackEvent", "0", szTemp, 5, COMMONSERVER_FILE);
		g_bDoRingEvent = atoi(szTemp);
		GetPrivateProfileString("GameServerInfo", "RingOrcKillGiftRate", "10000", szTemp, 10, COMMONSERVER_FILE);
		g_iRingOrcKillGiftRate = atoi(szTemp);
		GetPrivateProfileString("GameServerInfo", "RingDropGiftRate", "10000", szTemp, 10, COMMONSERVER_FILE);
		g_iRingDropGiftRate = atoi(szTemp);
		g_RingAttackEvent.Load("..\\Data\\Event\\RingAttackEvent.txt");
#if (GS_CASTLE==1)
		g_bDoRingEvent = FALSE; //HermeX Fix
#endif
		g_RingAttackEvent.EnableEvent(g_bDoRingEvent);

#if (GS_CASTLE==1)
		GetPrivateProfileString("GameServerInfo", "CastleDeepEvent", "0", szTemp, 5, COMMONSERVER_FILE);
		g_bDoCastleDeepEvent = atoi(szTemp);
		g_CastleDeepEvent.Load("..\\Data\\Event\\CastleDeepEvent.txt");
		g_CastleDeepEvent.EnableEvent(g_bDoCastleDeepEvent);
#endif

		GetPrivateProfileString("GameServerInfo", "EVENT1", "0", szTemp, 5, COMMONSERVER_FILE);
		gEvent1 = atoi(szTemp);
		GetPrivateProfileString("GameServerInfo", "Event1ItemDropTodayMax", "1", szTemp, 5, COMMONSERVER_FILE);
		gEvent1ItemDropTodayCount = 0;
		gEvent1ItemDropTodayMax = atoi(szTemp);
		GetPrivateProfileString("GameServerInfo", "Event1ItemDropTodayPercent", "10000000", szTemp, 5, COMMONSERVER_FILE);
		gEvent1ItemDropTodayPercent = atoi(szTemp);
		gFireCrackerEvent = GetPrivateProfileInt("GameServerInfo", "FireCrackerEvent", 0, COMMONSERVER_FILE);
		gFireCrackerDropRate = GetPrivateProfileInt("GameServerInfo", "FireCrackerDropRate", 5000, COMMONSERVER_FILE);
		g_ItemDropRateForgFireCracker = GetPrivateProfileInt("GameServerInfo", "ItemDropRateForFireCracker", 2, COMMONSERVER_FILE);
		gOnlyFireCrackerEffectUse = GetPrivateProfileInt("GameServerInfo", "OnlyFireCrackerEffectUse", 0, COMMONSERVER_FILE);
		gMedalEvent = GetPrivateProfileInt("GameServerInfo", "MedalEvent", 0, COMMONSERVER_FILE);
		gGoldMedalDropRate = GetPrivateProfileInt("GameServerInfo", "GoldMedalDropRate", 2, COMMONSERVER_FILE);
		gSilverMedalDropRate = GetPrivateProfileInt("GameServerInfo", "SilverMedalDropRate", 2, COMMONSERVER_FILE);
		g_ItemDropRateForGoldMedal = GetPrivateProfileInt("GameServerInfo", "ItemDropRateForGoldMedal", 2, COMMONSERVER_FILE);
		g_ItemDropRateForSilverMedal = GetPrivateProfileInt("GameServerInfo", "ItemDropRateForSilverMedal", 2, COMMONSERVER_FILE);
		gXMasEvent = GetPrivateProfileInt("GameServerInfo", "XMasEvent", 0, COMMONSERVER_FILE);
		g_XMasEvent_StarOfXMasDropRate = GetPrivateProfileInt("GameServerInfo", "XMasEvent_StarOfXMasDropRate", 5000, COMMONSERVER_FILE);
		g_XMasEvent_ItemDropRateForStarOfXMas = GetPrivateProfileInt("GameServerInfo", "XMasEvent_ItemDropRateForStarOfXMas", 2, COMMONSERVER_FILE);
		gHeartOfLoveEvent = GetPrivateProfileInt("GameServerInfo", "HeartOfLoveEvent", 0, COMMONSERVER_FILE);
		gHeartOfLoveDropRate = GetPrivateProfileInt("GameServerInfo", "HeartOfLoveDropRate", 5000, COMMONSERVER_FILE);
		g_ItemDropRateForgHeartOfLove = GetPrivateProfileInt("GameServerInfo", "ItemDropRateForHeartOfLove", 2, COMMONSERVER_FILE);
		GetPrivateProfileString("GameServerInfo", "HappyNewYearTalkNpc", "0", szTemp, 5, COMMONSERVER_FILE);
		gHappyNewYearNpcEvent = atoi(szTemp);

		if (gHappyNewYearNpcEvent != 0)
		{
			// (Option) Happy-new-year NPC speaks
			LogAdd(lMsg.Get(MSGGET(2, 61)));
		}

		GetPrivateProfileString("GameServerInfo", "MerryXMasTalkNpc", "0", szTemp, 5, COMMONSERVER_FILE);
		gMerryXMasNpcEvent = atoi(szTemp);

		if (gMerryXMasNpcEvent != 0)
		{
			// (Option) Christmas NPC speaks
			LogAdd(lMsg.Get(MSGGET(2, 60)));
		}

		g_ChaosCastle.Load("..\\Data\\Event\\ChaosCastle.txt");
		g_bChaosCastle = GetPrivateProfileInt("GameServerInfo", "ChaosCastleEvent", 0, COMMONSERVER_FILE);

		g_iKundunMarkDropRate = GetPrivateProfileInt("GameServerInfo", "KundunMarkDropRate", 0, COMMONSERVER_FILE);

		g_iMysteriousBeadDropRate1 = GetPrivateProfileInt("GameServerInfo", "MysteriouseBeadDropRate1", 0, COMMONSERVER_FILE);
		g_iMysteriousBeadDropRate2 = GetPrivateProfileInt("GameServerInfo", "MysteriouseBeadDropRate2", 0, COMMONSERVER_FILE);

		g_iHiddenTreasureBoxOfflineRate = GetPrivateProfileInt("GameServerInfo", "HiddenTreasureBoxOfflineRate", 0, COMMONSERVER_FILE);

		GetPrivateProfileString("GameServerInfo", "EventManagerOn", "0", szTemp, 5, COMMONSERVER_FILE);
		g_bEventManagerOn = atoi(szTemp);
		g_EventManager.Load("..\\Data\\Event\\Management.txt");
		g_EventManager.RegEvent(0, &DragonEvent);
		g_EventManager.RegEvent(1, &AttackEvent);
		g_EventManager.RegEvent(2, &gEledoradoEvent);
		g_EventManager.RegEvent(3, &g_RingAttackEvent);
		g_EventManager.Init(g_bEventManagerOn);

		g_iDarkLordHeartDropRate = GetPrivateProfileInt("GameServerInfo", "DarkLordHeartDropRate", 0, COMMONSERVER_FILE);
		g_iDarkLordHeartOffEventRate = GetPrivateProfileInt("GameServerInfo", "DarkLoadHeartOffEventRate", 0, COMMONSERVER_FILE);

		break;

	case 1: //Devil Square
		g_DevilSquare.Load("..\\Data\\Event\\DevilSquare.txt");
		gDevilSquareEvent = GetPrivateProfileInt("GameServerInfo", "DevilSquareEvent", 0, COMMONSERVER_FILE);
		gEyesOfDevilSquareDropRate = GetPrivateProfileInt("GameServerInfo", "EyesOfDevilSquareDropRate", 2, COMMONSERVER_FILE);
		gKeyOfDevilSquareDropRate = GetPrivateProfileInt("GameServerInfo", "KeyOfDevilSquareDropRate", 2, COMMONSERVER_FILE);
		break;

	case 2: //Blood Castle
		g_BloodCastle.Load("..\\Data\\Event\\BloodCastle.txt");
		g_bBloodCastle = GetPrivateProfileInt("GameServerInfo", "BloodCastleEvent", 0, COMMONSERVER_FILE);
		g_iBloodCastle_StartHour = GetPrivateProfileInt("GameServerInfo", "BloodCastleStartHour", 1, COMMONSERVER_FILE);
		g_iAngelKingsPaperDropRate = GetPrivateProfileInt("GameServerInfo", "AngelKingsPaperDropRate", 0, COMMONSERVER_FILE);
		g_iBloodBoneDropRate = GetPrivateProfileInt("GameServerInfo", "BloodBoneDropRate", 0, COMMONSERVER_FILE);
		g_iStoneDropRate = GetPrivateProfileInt("GameServerInfo", "StoneDropRate", 0, COMMONSERVER_FILE);
		break;

	case 3: //Attack Event
		gAttackEventRegenTime = GetPrivateProfileInt("GameServerInfo", "AttackEventRegenTime", 10, COMMONSERVER_FILE);
		break;

	case 4: //Eledorado Event
		gEledoradoEvent.EventState = GetPrivateProfileInt("GameServerInfo", "IsEledoradoEvent", 0, COMMONSERVER_FILE);
		gEledoradoGoldGoblenRegenTime = GetPrivateProfileInt("GameServerInfo", "EledoradoGoldGoblenRegenTime", 180, COMMONSERVER_FILE);
		gEledoradoTitanRegenTime = GetPrivateProfileInt("GameServerInfo", "EledoradoTitanRegenTime", 180, COMMONSERVER_FILE);
		gEledoradoGoldDerconRegenTime = GetPrivateProfileInt("GameServerInfo", "EledoradoGoldDerconRegenTime", 720, COMMONSERVER_FILE);
		gEledoradoDevilLizardKingRegenTime = GetPrivateProfileInt("GameServerInfo", "EledoradoDevilLizardKingRegenTime", 360, COMMONSERVER_FILE);
		gEledoradoDevilTantarosRegenTime = GetPrivateProfileInt("GameServerInfo", "EledoradoDevilTantarosRegenTime", 360, COMMONSERVER_FILE);
		gEledoradoGoldGoblenItemDropRate = GetPrivateProfileInt("GameServerInfo", "EledoradoGoldGoblenItemDropRate", 10, COMMONSERVER_FILE);
		gEledoradoTitanItemDropRate = GetPrivateProfileInt("GameServerInfo", "EledoradoTitanItemDropRate", 10, COMMONSERVER_FILE);
		gEledoradoGoldDerconItemDropRate = GetPrivateProfileInt("GameServerInfo", "EledoradoGoldDerconItemDropRate", 10, COMMONSERVER_FILE);
		gEledoradoDevilLizardKingItemDropRate = GetPrivateProfileInt("GameServerInfo", "EledoradoDevilLizardKingItemDropRate", 10, COMMONSERVER_FILE);
		gEledoradoDevilTantarosItemDropRate = GetPrivateProfileInt("GameServerInfo", "EledoradoDevilTantarosItemDropRate", 10, COMMONSERVER_FILE);
		gEledoradoGoldGoblenExItemDropRate = GetPrivateProfileInt("GameServerInfo", "EledoradoGoldGoblenExItemDropRate", 10, COMMONSERVER_FILE);
		gEledoradoTitanExItemDropRate = GetPrivateProfileInt("GameServerInfo", "EledoradoTitanExItemDropRate", 10, COMMONSERVER_FILE);
		gEledoradoGoldDerconExItemDropRate = GetPrivateProfileInt("GameServerInfo", "EledoradoGoldDerconExItemDropRate", 10, COMMONSERVER_FILE);
		gEledoradoDevilLizardKingExItemDropRate = GetPrivateProfileInt("GameServerInfo", "EledoradoDevilLizardKingExItemDropRate", 10, COMMONSERVER_FILE);
		gEledoradoDevilTantarosExItemDropRate = GetPrivateProfileInt("GameServerInfo", "EledoradoDevilTantarosExItemDropRate", 10, COMMONSERVER_FILE);
		break;

	case 5: //Ring Event
		{
			char szTemp[256];

			GetPrivateProfileString("GameServerInfo", "RingAttackEvent", "0", szTemp, 5, COMMONSERVER_FILE);
			g_bDoRingEvent = atoi(szTemp);
			GetPrivateProfileString("GameServerInfo", "RingOrcKillGiftRate", "10000", szTemp, 10, COMMONSERVER_FILE);
			g_iRingOrcKillGiftRate = atoi(szTemp);
			GetPrivateProfileString("GameServerInfo", "RingDropGiftRate", "10000", szTemp, 10, COMMONSERVER_FILE);
			g_iRingDropGiftRate = atoi(szTemp);
			g_RingAttackEvent.Load("..\\Data\\Event\\RingAttackEvent.txt");
			g_RingAttackEvent.EnableEvent(g_bDoRingEvent);
		}
		break;

	case 6: //Event 1
		GetPrivateProfileString("GameServerInfo", "EVENT1", "0", szTemp, 5, COMMONSERVER_FILE);
		gEvent1 = atoi(szTemp);
		GetPrivateProfileString("GameServerInfo", "Event1ItemDropTodayMax", "1", szTemp, 5, COMMONSERVER_FILE);
		gEvent1ItemDropTodayCount = 0;
		gEvent1ItemDropTodayMax = atoi(szTemp);
		GetPrivateProfileString("GameServerInfo", "Event1ItemDropTodayPercent", "10000000", szTemp, 5, COMMONSERVER_FILE);
		gEvent1ItemDropTodayPercent = atoi(szTemp);
		break;

	case 7: //Fire Cracker
		gFireCrackerEvent = GetPrivateProfileInt("GameServerInfo", "FireCrackerEvent", 0, COMMONSERVER_FILE);
		gFireCrackerDropRate = GetPrivateProfileInt("GameServerInfo", "FireCrackerDropRate", 5000, COMMONSERVER_FILE);
		g_ItemDropRateForgFireCracker = GetPrivateProfileInt("GameServerInfo", "ItemDropRateForFireCracker", 2, COMMONSERVER_FILE);
		gOnlyFireCrackerEffectUse = GetPrivateProfileInt("GameServerInfo", "OnlyFireCrackerEffectUse", 0, COMMONSERVER_FILE);
		break;

	case 8: //Medal Event
		gMedalEvent = GetPrivateProfileInt("GameServerInfo", "MedalEvent", 0, COMMONSERVER_FILE);
		gGoldMedalDropRate = GetPrivateProfileInt("GameServerInfo", "GoldMedalDropRate", 2, COMMONSERVER_FILE);
		gSilverMedalDropRate = GetPrivateProfileInt("GameServerInfo", "SilverMedalDropRate", 2, COMMONSERVER_FILE);
		g_ItemDropRateForGoldMedal = GetPrivateProfileInt("GameServerInfo", "ItemDropRateForGoldMedal", 2, COMMONSERVER_FILE);
		g_ItemDropRateForSilverMedal = GetPrivateProfileInt("GameServerInfo", "ItemDropRateForSilverMedal", 2, COMMONSERVER_FILE);
		break;

	case 9: //XMax Event
		gXMasEvent = GetPrivateProfileInt("GameServerInfo", "XMasEvent", 0, COMMONSERVER_FILE);
		g_XMasEvent_StarOfXMasDropRate = GetPrivateProfileInt("GameServerInfo", "XMasEvent_StarOfXMasDropRate", 5000, COMMONSERVER_FILE);
		g_XMasEvent_ItemDropRateForStarOfXMas = GetPrivateProfileInt("GameServerInfo", "XMasEvent_ItemDropRateForStarOfXMas", 2, COMMONSERVER_FILE);
		break;

	case 10: //Heart Of Love Event
		gHeartOfLoveEvent = GetPrivateProfileInt("GameServerInfo", "HeartOfLoveEvent", 0, COMMONSERVER_FILE);
		gHeartOfLoveDropRate = GetPrivateProfileInt("GameServerInfo", "HeartOfLoveDropRate", 5000, COMMONSERVER_FILE);
		g_ItemDropRateForgHeartOfLove = GetPrivateProfileInt("GameServerInfo", "ItemDropRateForHeartOfLove", 2, COMMONSERVER_FILE);
		break;

	case 11: //Happy New Year Event
		GetPrivateProfileString("GameServerInfo", "HappyNewYearTalkNpc", "0", szTemp, 5, COMMONSERVER_FILE);
		gHappyNewYearNpcEvent = atoi(szTemp);

		if (gHappyNewYearNpcEvent != 0)
		{
			// (Option) Happy-new-year NPC speaks
			LogAdd(lMsg.Get(MSGGET(2, 61)));
		}

		break;

	case 12: //Merry  XMax Event NPC talk
		GetPrivateProfileString("GameServerInfo", "MerryXMasTalkNpc", "0", szTemp, 5, COMMONSERVER_FILE);
		gMerryXMasNpcEvent = atoi(szTemp);

		if (gMerryXMasNpcEvent != 0)
		{
			// (Option) Christmas NPC speaks
			LogAdd(lMsg.Get(MSGGET(2, 60)));
		}

		break;

	case 13: //Chaos Castle
		g_ChaosCastle.Load("..\\Data\\Event\\ChaosCastle.txt");
		g_bChaosCastle = GetPrivateProfileInt("GameServerInfo", "ChaosCastleEvent", 0, COMMONSERVER_FILE);
		break;
	}
}

void ReadGameEtcInfo(MU_ETC_TYPE eGameEtcType)
{
	char szTemp[256];

	switch (eGameEtcType)
	{
	case 0:
		GetPrivateProfileString("GameServerInfo", "CreateCharacter", "1", szTemp, 5, COMMONSERVER_FILE);
		gCreateCharacter = atoi(szTemp);

		GetPrivateProfileString("GameServerInfo", "GuildCreate", "1", szTemp, 5, COMMONSERVER_FILE);
		gGuildCreate = atoi(szTemp);
		LogAdd(lMsg.Get(MSGGET(2, 57)), gGuildCreate);
		GetPrivateProfileString("GameServerInfo", "GuildDestroy", "1", szTemp, 5, COMMONSERVER_FILE);
		gGuildDestroy = atoi(szTemp);
		LogAdd(lMsg.Get(MSGGET(2, 58)), gGuildDestroy);
		GetPrivateProfileString("GameServerInfo", "GuildCreateLevel", "100", szTemp, 5, COMMONSERVER_FILE);
		gGuildCreateLevel = atoi(szTemp);
		LogAdd(lMsg.Get(MSGGET(2, 59)), gGuildCreateLevel);

		g_bCastleGuildDestoyLimit = GetPrivateProfileInt("GameServerInfo", "CastleOwnerGuildDestroyLimit", 1, COMMONSERVER_FILE);

		GetPrivateProfileString("GameServerInfo", "Trade", "1", szTemp, 5, COMMONSERVER_FILE);
		bCanTrade = atoi(szTemp);

		bCanChaosBox = GetPrivateProfileInt("GameServerInfo", "ChaosBox", 0, COMMONSERVER_FILE);

		GetPrivateProfileString("GameServerInfo", "PKItemDrop", "1", szTemp, 5, COMMONSERVER_FILE);
		gPkItemDrop = atoi(szTemp);

		GetPrivateProfileString("GameServerInfo", "ItemDropPer", "10", szTemp, 5, COMMONSERVER_FILE);
		gItemDropPer = atoi(szTemp);

		gDoPShopOpen = GetPrivateProfileInt("GameServerInfo", "PersonalShopOpen", 0, COMMONSERVER_FILE);
		break;

	case 1:
		GetPrivateProfileString("GameServerInfo", "CreateCharacter", "1", szTemp, 5, COMMONSERVER_FILE);
		gCreateCharacter = atoi(szTemp);

		break;

	case 2:
		GetPrivateProfileString("GameServerInfo", "GuildCreate", "1", szTemp, 5, COMMONSERVER_FILE);
		gGuildCreate = atoi(szTemp);
		LogAdd(lMsg.Get(MSGGET(2, 57)), gGuildCreate);
		GetPrivateProfileString("GameServerInfo", "GuildDestroy", "1", szTemp, 5, COMMONSERVER_FILE);
		gGuildDestroy = atoi(szTemp);
		LogAdd(lMsg.Get(MSGGET(2, 58)), gGuildDestroy);
		GetPrivateProfileString("GameServerInfo", "GuildCreateLevel", "100", szTemp, 5, COMMONSERVER_FILE);
		gGuildCreateLevel = atoi(szTemp);
		LogAdd(lMsg.Get(MSGGET(2, 59)), gGuildCreateLevel);
		g_bCastleGuildDestoyLimit = GetPrivateProfileInt("GameServerInfo", "CastleOwnerGuildDestroyLimit", 1, COMMONSERVER_FILE);
		break;

	case 3:
		GetPrivateProfileString("GameServerInfo", "Trade", "1", szTemp, 5, COMMONSERVER_FILE);
		bCanTrade = atoi(szTemp);

		break;
	case 4:
		bCanChaosBox = GetPrivateProfileInt("GameServerInfo", "ChaosBox", 0, COMMONSERVER_FILE);
		break;

	case 5:
		gDoPShopOpen = GetPrivateProfileInt("GameServerInfo", "PersonalShopOpen", 0, COMMONSERVER_FILE);
		break;

	case 6:
		GetPrivateProfileString("GameServerInfo", "PKItemDrop", "1", szTemp, 5, COMMONSERVER_FILE);
		gPkItemDrop = atoi(szTemp);
		break;

	case 7:
		GetPrivateProfileString("GameServerInfo", "ItemDropPer", "10", szTemp, 5, COMMONSERVER_FILE);
		gItemDropPer = atoi(szTemp);
		break;
	}
}