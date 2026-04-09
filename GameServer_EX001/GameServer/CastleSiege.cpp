#include "stdafx.h"
#include "CastleSiege.h"

#if (GS_CASTLE==1)
#include "CastleDeepEvent.h"
#include "CannonTower.h"
#include "DSProtocol.h"
#include "GameMain.h"
#include "TNotice.h"
#include "TUnion.h"
#include "LifeStone.h"
#include "Mercenary.h"
#include "DBSockMng.h"
#include "LogProc.h"
#include "readscript.h"

CCastleSiege g_CastleSiege;

#define CS_CHECK_UPGRADE(value) ( (( (value)   )<0)?FALSE:(( (value)  )>CS_MAX_UPGRADE-1)?FALSE:TRUE  )

#define MACRO1(value) (( value & 0xFF) & 0xFF)
#define MACRO2(value) (( value & 0xFFFF ) & 0xFFFF)

#define MONTH_MACRO(value) ( (( (value)   )<0)?FALSE:(( (value)  )>12)?FALSE:TRUE  )
#define DAY_MACRO(value) ( (( (value - 1)   )<0)?FALSE:(( (value - 1)  )>30)?FALSE:TRUE  )
#define HOUR_MACRO(value) ( (( (value)   )<0)?FALSE:(( (value)  )>23)?FALSE:TRUE  )
#define MINUTE_MACRO(value) ( (( (value)   )<0)?FALSE:(( (value)  )>59)?FALSE:TRUE  )

#define XY_MACRO(value) ( (( (value)   )<0)?FALSE:(( (value)  )>255)?FALSE:TRUE  )

_CS_SCHEDULE_DATA::_CS_SCHEDULE_DATA() //Identical
{
	Clear();
}

_CS_SCHEDULE_DATA::~_CS_SCHEDULE_DATA() //Identical
{
}

void _CS_SCHEDULE_DATA::Clear() //Identical
{
	m_bIN_USE = 0;
	m_iSTATE = -1;
	m_iADD_DAY = -1;
	m_iADD_HOUR = -1;
	m_iADD_MIN = -1;
	m_iGAP_SEC = 0;
}

_CS_REG_GUILD_DATA::_CS_REG_GUILD_DATA() //Identical
{
	Clear();
}

_CS_REG_GUILD_DATA::~_CS_REG_GUILD_DATA() //Identical
{
}

void _CS_REG_GUILD_DATA::Clear() //Identical
{
	m_bIN_USE = 0;
	m_strGuildName = "";
	m_iRegMarkCount = 0;
	m_iGuildMemberCount = 0;
	m_iGuildMasterLevel = 0;
	m_iSeqNum = 0;
	m_i64TotolScore = 0;
}

_CS_TOTAL_GUILD_DATA::_CS_TOTAL_GUILD_DATA() //Identical
{
	Clear();
}

_CS_TOTAL_GUILD_DATA::~_CS_TOTAL_GUILD_DATA() //Identical
{
}

void _CS_TOTAL_GUILD_DATA::Clear() //Identical
{
	m_bIN_USE = 0;
	m_iCsGuildID = 0;
	m_bGuildInvolved = 0;
}

_CS_MINIMAP_DATA::_CS_MINIMAP_DATA() //Identical
{
	Clear();
}

_CS_MINIMAP_DATA::~_CS_MINIMAP_DATA() //Identical
{
}

void _CS_MINIMAP_DATA::Clear() //Identical
{
	m_iGuildMasterIndex = -1;
	memset(m_szGuildName, 0x00, sizeof(m_szGuildName));
	memset(m_stMiniMapPoint, 0x00, sizeof(m_stMiniMapPoint));
	m_iMiniMapPointCount = 0;
}

_CS_NPC_DATA::_CS_NPC_DATA() //Identical
{
	Clear();
	m_iCS_GATE_LEVER_INDEX = -1;
};

_CS_NPC_DATA::~_CS_NPC_DATA() //Identical
{
};

void _CS_NPC_DATA::Clear() //Identical
{
	m_bIN_USE = FALSE; //HermeX Fix @27/01/2010
	m_iNPC_NUM = -1;
	m_iNPC_INDEX = -1;
	m_iNPC_LIVE = 0;
	m_iNPC_AUTH = -1;
	m_bNPC_DBSAVE = FALSE; //HermeX Fix @27/01/2010
	m_iNPC_SIDE = 0;
	m_iNPC_OBJINDEX = -1;
	m_iNPC_DF_LEVEL = 0;
	m_iNPC_RG_LEVEL = 0;
	m_iNPC_MAXHP = 0;
	m_iNPC_HP = 0;
	m_iNPC_SX = -1;
	m_iNPC_SY = -1;
	m_iNPC_DX = -1;
	m_iNPC_DY = -1;
	m_iNPC_DIR = -1;
	m_iNPC_BASE_DF_LEVEL = 0;
	m_iNPC_BASE_RG_LEVEL = 0;
	m_iNPC_BASE_MAXHP = 0;
	m_iNPC_BASE_HP = 0;
	m_iNPC_BASE_SX = -1;
	m_iNPC_BASE_SY = -1;
	m_iNPC_BASE_DX = -1;
	m_iNPC_BASE_DY = -1;
	m_iNPC_BASE_DIR = -1;
	m_iCsNpcExistVal = 0;
}

void _CS_NPC_DATA::SetBaseValue() //Identical
{
	m_iNPC_DF_LEVEL = m_iNPC_BASE_DF_LEVEL;
	m_iNPC_RG_LEVEL = m_iNPC_BASE_RG_LEVEL;
	m_iNPC_MAXHP = m_iNPC_BASE_MAXHP;
	m_iNPC_HP = m_iNPC_BASE_HP;
	m_iNPC_SX = m_iNPC_BASE_SX;
	m_iNPC_SY = m_iNPC_BASE_SY;
	m_iNPC_DX = m_iNPC_BASE_DX;
	m_iNPC_DY = m_iNPC_BASE_DY;
	m_iNPC_DIR = m_iNPC_BASE_DIR;
}

CCastleSiege::CCastleSiege() //Identical
{
	InitializeCriticalSection(&m_critScheduleData);
	InitializeCriticalSection(&m_critNpcData);
	InitializeCriticalSection(&m_critCsTotalGuildInfo);
	InitializeCriticalSection(&m_critCsBasicGuildInfo);
	InitializeCriticalSection(&m_critCsMiniMap);

	Clear();
}

CCastleSiege::~CCastleSiege() //Identical
{
	DeleteCriticalSection(&m_critScheduleData);
	DeleteCriticalSection(&m_critNpcData);
	DeleteCriticalSection(&m_critCsTotalGuildInfo);
	DeleteCriticalSection(&m_critCsBasicGuildInfo);
	DeleteCriticalSection(&m_critCsMiniMap);
}

unsigned char CCastleSiege::ScheduleStateCompFunc(_CS_SCHEDULE_DATA & A, _CS_SCHEDULE_DATA & B) //Identical
{
	if (A.m_iSTATE > B.m_iSTATE)
	{
		return false;
	}

	return true;
}

void CCastleSiege::Clear() //Identical
{
	m_bCastleSiegeEnable = TRUE; //HermeX Fix @27/01/2010
	m_bFileDataLoadOK = FALSE; //HermeX Fix @27/01/2010
	m_bDbDataLoadOK = FALSE; //HermeX Fix @27/01/2010
	m_bDoRun = FALSE; //HermeX Fix @27/01/2010
	m_iMapSvrGroup = -1;
	m_iCastleSiegeCycle = 14;
	m_iCastleSiegeState = -1;
	m_bFixCastleCycleStartDate = FALSE; //HermeX Fix @27/01/2010
	m_i64CastleMoney = 0;

	memset(&m_tmFixCastleCycleStartDate, 0x00, sizeof(m_tmFixCastleCycleStartDate));

	m_iFixCastleSpecificState = 0;
	m_bFixCastleStateStartDate = FALSE;

	memset(&m_tmFixCastleStateStartDate, 0x00, sizeof(m_tmFixCastleStateStartDate));

	m_iCastleDataLoadState = 0;
	m_dwDbDataLoadTickCount = 0;
	m_iCS_REMAIN_MSEC = -1;

	memset(&m_tmStateStartDate, 0x00, sizeof(m_tmStateStartDate));
	memset(&m_tmLeftCastleSiegeDate, 0x00, sizeof(m_tmLeftCastleSiegeDate));

	m_bCsBasicGuildInfoLoadOK = FALSE; //HermeX Fix @27/01/2010
	m_bCsTotalGuildInfoLoadOK = FALSE; //HermeX Fix @27/01/2010
	m_btIsSiegeGuildList = FALSE; //HermeX Fix @27/01/2010
	m_btIsCastleOccupied = FALSE; //HermeX Fix @27/01/2010

	memset(m_szCastleOwnerGuild, 0x00, sizeof(m_szCastleOwnerGuild));

	m_bEnterHuntZone = FALSE; //HermeX Fix @27/01/2010
	m_dwNPC_DBSAVE_TICK_COUNT = GetTickCount();
	m_dwCALC_LEFTSIEGE_TICK_COUNT = 0;
	m_dwEVENT_MSG_TICK_COUNT = 0;
	m_dwCHECK_GATE_ALIVE_COUNT = 0;
	m_dwCS_LEFTTIME_TICK_COUNT = 0;
	m_dwCS_STARTTIME_TICK_COUNT = 0;
	m_dwCS_JOINSIDE_REFRESH_TICK_COUNT = 0;
	m_dwCS_JOINSIDE_REFRESH_TOTAL_COUNT = 0;
	m_dwCS_MINIMAP_SEND_TICK_COUNT = 0;
	m_bCastleTowerAccessable = FALSE; //HermeX Fix @27/01/2010
	m_bRegCrownAvailable = FALSE; //HermeX Fix @27/01/2010
	m_iCastleCrownAccessUser = -1;
	m_btCastleCrownAccessUserX = 0;
	m_btCastleCrownAccessUserY = 0;
	m_iCastleSwitchAccessUser1 = -1;
	m_iCastleSwitchAccessUser2 = -1;
	m_dwCrownAccessTime = 0;

	memset(m_szMiddleWinnerGuild, 0x00, sizeof(m_szMiddleWinnerGuild));

	EnterCriticalSection(&m_critScheduleData);
	m_vtScheduleData.clear();
	LeaveCriticalSection(&m_critScheduleData);

	EnterCriticalSection(&m_critNpcData);
	m_vtNpcData.clear();
	LeaveCriticalSection(&m_critNpcData);

	m_bDbNpcCreated = FALSE; //HermeX Fix @27/01/2010

	ResetAllUserCsJoinSide();
}

int CCastleSiege::Ready(int iMapSvrGroup) //Identical
{
	if (iMapSvrGroup < 0)
		return false;

	Clear();
	ClearAllNPC();

	m_iMapSvrGroup = iMapSvrGroup;
	m_iCastleDataLoadState = 1;

	return true;
}

int CCastleSiege::LoadPreFixData(char * lpszFileName) //Identical
{
	if (lpszFileName == 0)
		return false;

	_SYSTEMTIME tmToDay;

	GetLocalTime(&tmToDay);

	int iTODAY_DATE_NUM = MACRO2((MACRO1(tmToDay.wDay) | MACRO1(tmToDay.wMonth) << 8) & 0xFFFF) | MACRO2(tmToDay.wYear) << 16;
	__int64 iTODAY_DATE_NUM64 = (MACRO2(tmToDay.wMinute) | MACRO2(tmToDay.wHour) << 16) | ((__int64)(MACRO2((MACRO1(tmToDay.wDay) | MACRO1(tmToDay.wMonth) << 8) & 0xFFFF) | MACRO2(tmToDay.wYear) << 16) << 0x20);

	m_bCastleSiegeEnable = GetPrivateProfileInt("GameServerInfo", "CastleSiegeRun", 1, lpszFileName);
	m_tmFixCastleCycleStartDate.wYear = GetPrivateProfileInt("GameServerInfo", "CastleCycleStartYear", 0, lpszFileName);
	m_tmFixCastleCycleStartDate.wMonth = GetPrivateProfileInt("GameServerInfo", "CastleCycleStartMonth", 0, lpszFileName);
	m_tmFixCastleCycleStartDate.wDay = GetPrivateProfileInt("GameServerInfo", "CastleCycleStartDay", 0, lpszFileName);

	m_iFixCastleSpecificState = GetPrivateProfileInt("GameServerInfo", "CastleSpecificState", 0, lpszFileName);

	m_tmFixCastleStateStartDate.wYear = GetPrivateProfileInt("GameServerInfo", "CastleStateStartYear", 0, lpszFileName);
	m_tmFixCastleStateStartDate.wMonth = GetPrivateProfileInt("GameServerInfo", "CastleStateStartMonth", 0, lpszFileName);
	m_tmFixCastleStateStartDate.wDay = GetPrivateProfileInt("GameServerInfo", "CastleStateStartDay", 0, lpszFileName);
	m_tmFixCastleStateStartDate.wHour = GetPrivateProfileInt("GameServerInfo", "CastleStateStartHour", 0, lpszFileName);
	m_tmFixCastleStateStartDate.wMinute = GetPrivateProfileInt("GameServerInfo", "CastleStateStartMinute", 0, lpszFileName);

	if (m_tmFixCastleCycleStartDate.wYear == 0
		|| m_tmFixCastleCycleStartDate.wMonth == 0
		|| m_tmFixCastleCycleStartDate.wDay == 0)
	{
		m_bFixCastleCycleStartDate = 0;
	}
	else
	{
		_SYSTEMTIME tmEndDate = m_tmFixCastleCycleStartDate;
		GetNextDay(&tmEndDate, m_iCastleSiegeCycle, 0, 0, 0);

		int iEVENT_END_DATE_NUM = MACRO2((MACRO1(tmEndDate.wDay) | MACRO1(tmEndDate.wMonth) << 8) & 0xFFFF) | MACRO2(tmEndDate.wYear) << 16;

		if (iEVENT_END_DATE_NUM <= iTODAY_DATE_NUM)
		{
			m_bFixCastleCycleStartDate = 0;
			MsgBox("[CastleSiege] CCastleSiege::LoadPreFixData() - iEVENT_END_DATE_NUM (%04d-%02d-%02d) <= iTODAY_DATE_NUM (%04d-%02d-%02d)",
				tmEndDate.wYear, tmEndDate.wMonth, tmEndDate.wDay, tmToDay.wYear, tmToDay.wMonth, tmToDay.wDay);
		}
		else
		{
			m_bFixCastleCycleStartDate = 1;
		}

		if (MONTH_MACRO(m_tmFixCastleCycleStartDate.wMonth) == FALSE
			|| DAY_MACRO(m_tmFixCastleCycleStartDate.wDay) == FALSE)
		{
			m_bFixCastleCycleStartDate = 0;
		}
	}

	if (m_tmFixCastleStateStartDate.wYear == 0
		|| m_tmFixCastleStateStartDate.wMonth == 0
		|| m_tmFixCastleStateStartDate.wDay == 0)
	{
		m_bFixCastleStateStartDate = 0;
	}
	else if (m_iFixCastleSpecificState < 1 || m_iFixCastleSpecificState > 9)
	{
		m_bFixCastleStateStartDate = 0;
	}
	else
	{
		__int64 iSIEGE_DATE_NUM64 = (MACRO2(m_tmFixCastleStateStartDate.wMinute) | MACRO2(m_tmFixCastleStateStartDate.wHour) << 16) | ((__int64)(MACRO2((MACRO1(m_tmFixCastleStateStartDate.wDay) | MACRO1(m_tmFixCastleStateStartDate.wMonth) << 8) & 0xFFFF) | MACRO2(m_tmFixCastleStateStartDate.wYear) << 16) << 0x20);

		if (iSIEGE_DATE_NUM64 <= iTODAY_DATE_NUM64)
		{
			m_bFixCastleStateStartDate = 0;
			MsgBox("[CastleSiege] CCastleSiege::LoadPreFixData() - iSIEGE_DATE_NUM64 (STATE:%d, %04d-%02d-%02d %02d:%02d:%02d) <= iTODAY_DATE_NUM64 (%04d-%02d-%02d %02d:%02d:%02d)",
				m_iFixCastleSpecificState, m_tmFixCastleStateStartDate.wYear, m_tmFixCastleStateStartDate.wMonth, m_tmFixCastleStateStartDate.wDay, m_tmFixCastleStateStartDate.wHour, m_tmFixCastleStateStartDate.wMinute, m_tmFixCastleStateStartDate.wSecond,
				tmToDay.wYear, tmToDay.wMonth, tmToDay.wDay, tmToDay.wHour, tmToDay.wMinute, tmToDay.wSecond);
		}
		else
		{
			m_bFixCastleStateStartDate = 1;
		}

		if (m_iFixCastleSpecificState == 8)
		{
			MsgBox("[CastleSiege] CCastleSiege::LoadPreFixData() - FIX STATE 'CASTLESIEGE_STATE_ENDSIEGE' CAN'T BE USED");
			m_bFixCastleStateStartDate = 0;
		}

		if (MONTH_MACRO(m_tmFixCastleStateStartDate.wMonth) == FALSE
			|| DAY_MACRO(m_tmFixCastleStateStartDate.wDay) == FALSE
			|| HOUR_MACRO(m_tmFixCastleStateStartDate.wHour) == FALSE
			|| MINUTE_MACRO(m_tmFixCastleStateStartDate.wMinute) == FALSE)
		{
			m_bFixCastleStateStartDate = 0;
		}
	}

	WritePrivateProfileString("GameServerInfo", "CastleCycleStartYear", "0", lpszFileName);
	WritePrivateProfileString("GameServerInfo", "CastleCycleStartMonth", "0", lpszFileName);
	WritePrivateProfileString("GameServerInfo", "CastleCycleStartDay", "0", lpszFileName);
	WritePrivateProfileString("GameServerInfo", "CastleSpecificState", "0", lpszFileName);
	WritePrivateProfileString("GameServerInfo", "CastleStateStartYear", "0", lpszFileName);
	WritePrivateProfileString("GameServerInfo", "CastleStateStartMonth", "0", lpszFileName);
	WritePrivateProfileString("GameServerInfo", "CastleStateStartDay", "0", lpszFileName);
	WritePrivateProfileString("GameServerInfo", "CastleStateStartHour", "0", lpszFileName);
	WritePrivateProfileString("GameServerInfo", "CastleStateStartMinute", "0", lpszFileName);

	return m_bFixCastleCycleStartDate & m_bFixCastleStateStartDate;
}

int CCastleSiege::LoadData(char * lpszFileName) //Identical
{
	using namespace std;

	if (lpszFileName == NULL || strcmp(lpszFileName, "") == NULL)
	{
		MsgBox("[CastleSiege] file load error - File Name Error");
		return false;
	}

	if (m_iCastleDataLoadState != 1)
	{
		LogAddC(2, "[CastleSiege] CCastleSiege::LoadData() - m_iCastleDataLoadState != CASTLESIEGE_DATALOAD_1 (%d)", m_iCastleDataLoadState);
		return false;
	}

	SMDFile = fopen(lpszFileName, "r");

	if (SMDFile == NULL)
	{
		MsgBox("[CastleSiege] file load error - fopen() : %s", lpszFileName);
		return false;
	}

	int type = -1;
	enum SMDToken Token;

	vector<_CS_SCHEDULE_DATA> vtScheduleData;
	vector<_CS_NPC_DATA> vtNpcData;
	map<unsigned int, int> mpNpcDataCheck;

	int iCountDfUpgrade_Gate = 0;
	int iCountDfUpgrade_Statue = 0;
	int iCountHpUpgrade_Gate = 0;
	int iCountHpUpgrade_Statue = 0;
	int iCountRgUpgrade_Statue = 0;
	int iCountDfValue_Gate = 0;
	int iCountDfValue_Statue = 0;

	while (true)
	{
		Token = GetToken();

		if (Token == 2)
		{
			break;
		}

		type = (int)TokenNumber;

		while (true)
		{
			if (type == 0)
			{
				Token = GetToken();
				if (strcmp("end", TokenString) == NULL)
				{
					break;
				}

				int iCastleSiegeCycle = (int)TokenNumber;

				if (iCastleSiegeCycle <= 0)
				{
					LogAddC(2, "[CastleSiege] CCastleSiege::LoadData() - iCastleSiegeCycle <= 0 : %d", iCastleSiegeCycle);
					return false;
				}
				else
				{
					m_iCastleSiegeCycle = iCastleSiegeCycle;
				}
			}
			else if (type == 1)
			{
				int iSTATE = -1;
				int iSTART_DAY = -1;
				int iSTART_HOUR = -1;
				int iSTART_MIN = -1;

				Token = GetToken();
				if (strcmp("end", TokenString) == NULL)
				{
					break;
				}

				iSTATE = (int)TokenNumber;
				Token = GetToken();
				iSTART_DAY = (int)TokenNumber;
				Token = GetToken();
				iSTART_HOUR = (int)TokenNumber;
				Token = GetToken();
				iSTART_MIN = (int)TokenNumber;

				if (!vtScheduleData.empty())
				{
					for (auto it = vtScheduleData.begin(); it != vtScheduleData.end(); it++)
					{
						_CS_SCHEDULE_DATA pScheduleData = _CS_SCHEDULE_DATA(*it);

						if (pScheduleData.m_bIN_USE != 0)
						{
							if (pScheduleData.m_iSTATE == iSTATE)
							{
								LogAddC(2, "[CastleSiege] CCastleSiege::LoadData() - Same State Exist : %d", iSTATE);
								return false;
							}

							if (pScheduleData.m_iSTATE > iSTATE)
							{
								int iSTATE1_TIME = pScheduleData.m_iADD_DAY * 24 * 60 + pScheduleData.m_iADD_HOUR * 60 + pScheduleData.m_iADD_MIN;
								int iSTATE2_TIME = iSTART_DAY * 24 * 60 + iSTART_HOUR * 60 + iSTART_MIN;

								if (iSTATE1_TIME <= iSTATE2_TIME)
								{
									LogAddC(2, "[CastleSiege] CCastleSiege::LoadData() - Date Order is wrong : %d", iSTATE2_TIME);
									return false;
								}
							}
							else
							{
								int iSTATE1_TIME = pScheduleData.m_iADD_DAY * 24 * 60 + pScheduleData.m_iADD_HOUR * 60 + pScheduleData.m_iADD_MIN;
								int iSTATE2_TIME = iSTART_DAY * 24 * 60 + iSTART_HOUR * 60 + iSTART_MIN;
								if (iSTATE1_TIME >= iSTATE2_TIME)
								{
									LogAddC(2, "[CastleSiege] CCastleSiege::LoadData() - Date Order is wrong : %d", iSTATE2_TIME);
									return false;
								}
							}
						}
					}
				}

				_CS_SCHEDULE_DATA pScheduleDataInsert;

				pScheduleDataInsert.m_bIN_USE = 1;
				pScheduleDataInsert.m_iSTATE = iSTATE;
				pScheduleDataInsert.m_iADD_DAY = iSTART_DAY;
				pScheduleDataInsert.m_iADD_HOUR = iSTART_HOUR;
				pScheduleDataInsert.m_iADD_MIN = iSTART_MIN;

				vtScheduleData.push_back(pScheduleDataInsert);
			}
			else if (type == 2)
			{
				int iNPC_NUM = -1;
				int iNPC_INDEX = -1;
				int iNPC_SIDE = 0;
				int iNPC_DBSAVE = 0;
				int iNPC_DF_LEVEL = 0;
				int iNPC_RG_LEVEL = 0;
				int iNPC_MAXHP = 0;
				int iNPC_SX = -1;
				int iNPC_SY = -1;
				int iNPC_DX = -1;
				int iNPC_DY = -1;
				int iNPC_DIR = -1;

				Token = GetToken();
				if (strcmp("end", TokenString) == NULL)
				{
					break;
				}

				iNPC_NUM = (int)TokenNumber;
				Token = GetToken();
				iNPC_INDEX = (int)TokenNumber;
				Token = GetToken();
				iNPC_DBSAVE = (int)TokenNumber;
				Token = GetToken();
				iNPC_SIDE = (int)TokenNumber;
				Token = GetToken();
				iNPC_DF_LEVEL = (int)TokenNumber;
				Token = GetToken();
				iNPC_RG_LEVEL = (int)TokenNumber;
				Token = GetToken();
				iNPC_MAXHP = (int)TokenNumber;
				Token = GetToken();
				iNPC_SX = (int)TokenNumber;
				Token = GetToken();
				iNPC_SY = (int)TokenNumber;
				Token = GetToken();
				iNPC_DX = (int)TokenNumber;
				Token = GetToken();
				iNPC_DY = (int)TokenNumber;
				Token = GetToken();
				iNPC_DIR = (int)TokenNumber;

				if (iNPC_NUM < 0)
				{
					MsgBox("[CastleSiege] CCastleSiege::LoadData() - Data Fail (iNPC_NUM < 0)");
					return false;
				}

				if (iNPC_INDEX < 0)
				{
					MsgBox("[CastleSiege] CCastleSiege::LoadData() - Data Fail (iNPC_INDEX < 0)");
					return false;
				}

				if (iNPC_SIDE < 0)
				{
					MsgBox("[CastleSiege] CCastleSiege::LoadData() - Data Fail (iNPC_SIDE < 0)");
					return false;
				}

				if (iNPC_DF_LEVEL < 0)
				{
					MsgBox("[CastleSiege] CCastleSiege::LoadData() - Data Fail (iNPC_DF_LEVEL < 0)");
					return false;
				}

				if (iNPC_RG_LEVEL < 0)
				{
					MsgBox("[CastleSiege] CCastleSiege::LoadData() - Data Fail (iNPC_RG_LEVEL < 0)");
					return false;
				}

				if (iNPC_MAXHP < 0)
				{
					MsgBox("[CastleSiege] CCastleSiege::LoadData() - Data Fail (iNPC_MAXHP < 0)");
					return false;
				}

				if (iNPC_SX < 0)
				{
					MsgBox("[CastleSiege] CCastleSiege::LoadData() - Data Fail (iNPC_SX < 0)");
					return false;
				}

				if (iNPC_SY < 0)
				{
					MsgBox("[CastleSiege] CCastleSiege::LoadData() - Data Fail (iNPC_SY < 0)");
					return false;
				}

				unsigned int uNpcKey = MACRO2(iNPC_INDEX) | (MACRO2(iNPC_NUM) << 16);

				map<unsigned int, int>::iterator it = mpNpcDataCheck.find(uNpcKey);

				if (it != mpNpcDataCheck.end())
				{
					MsgBox("[CastleSiege] CCastleSiege::LoadData() - Same Npc Key Exist : NUM:%d-IDX:%d", iNPC_NUM, iNPC_INDEX);
					return false;
				}

				mpNpcDataCheck.insert(pair <unsigned int, int >((MACRO2(iNPC_INDEX) | (MACRO2(iNPC_NUM) << 16)), 0));

				_CS_NPC_DATA pNpcDataInsert;

				pNpcDataInsert.m_bIN_USE = 1;
				pNpcDataInsert.m_iNPC_NUM = iNPC_NUM;
				pNpcDataInsert.m_iNPC_INDEX = iNPC_INDEX;
				pNpcDataInsert.m_iNPC_SIDE = iNPC_SIDE;
				pNpcDataInsert.m_bNPC_DBSAVE = iNPC_DBSAVE;

				pNpcDataInsert.m_iNPC_BASE_DF_LEVEL = iNPC_DF_LEVEL;
				pNpcDataInsert.m_iNPC_DF_LEVEL = pNpcDataInsert.m_iNPC_BASE_DF_LEVEL;

				pNpcDataInsert.m_iNPC_BASE_RG_LEVEL = iNPC_RG_LEVEL;
				pNpcDataInsert.m_iNPC_RG_LEVEL = pNpcDataInsert.m_iNPC_BASE_RG_LEVEL;

				pNpcDataInsert.m_iNPC_BASE_MAXHP = iNPC_MAXHP;
				pNpcDataInsert.m_iNPC_MAXHP = pNpcDataInsert.m_iNPC_BASE_MAXHP;

				pNpcDataInsert.m_iNPC_BASE_HP = iNPC_MAXHP;
				pNpcDataInsert.m_iNPC_HP = pNpcDataInsert.m_iNPC_BASE_HP;

				pNpcDataInsert.m_iNPC_BASE_SX = iNPC_SX;
				pNpcDataInsert.m_iNPC_SX = pNpcDataInsert.m_iNPC_BASE_SX;

				pNpcDataInsert.m_iNPC_BASE_SY = iNPC_SY;
				pNpcDataInsert.m_iNPC_SY = pNpcDataInsert.m_iNPC_BASE_SY;

				pNpcDataInsert.m_iNPC_BASE_DX = iNPC_DX;
				pNpcDataInsert.m_iNPC_DX = pNpcDataInsert.m_iNPC_BASE_DX;

				pNpcDataInsert.m_iNPC_BASE_DY = iNPC_DY;
				pNpcDataInsert.m_iNPC_DY = pNpcDataInsert.m_iNPC_BASE_DY;

				pNpcDataInsert.m_iNPC_BASE_DIR = iNPC_DIR;
				pNpcDataInsert.m_iNPC_DIR = pNpcDataInsert.m_iNPC_BASE_DIR;

				vtNpcData.push_back(pNpcDataInsert);
			}
			else if (type == 3)
			{
				int iLEVEL = 0;
				int iGEMCOUNT = 0;
				int iZEN = 0;

				Token = GetToken();
				if (strcmp("end", TokenString) == NULL)
				{
					break;
				}

				iLEVEL = (int)TokenNumber;
				Token = GetToken();
				iGEMCOUNT = (int)TokenNumber;
				Token = GetToken();
				iZEN = (int)TokenNumber;

				if (iCountDfUpgrade_Gate >= CS_MAX_UPGRADE)
					break;

				g_iNpcUpDfLevel_CGATE[iCountDfUpgrade_Gate][0] = iLEVEL;
				g_iNpcUpDfLevel_CGATE[iCountDfUpgrade_Gate][1] = iGEMCOUNT;
				g_iNpcUpDfLevel_CGATE[iCountDfUpgrade_Gate][2] = iZEN;

				iCountDfUpgrade_Gate++;
			}
			else if (type == 4)
			{
				int iLEVEL = 0;
				int iGEMCOUNT = 0;
				int iZEN = 0;

				Token = GetToken();
				if (strcmp("end", TokenString) == NULL)
				{
					break;
				}

				iLEVEL = (int)TokenNumber;
				Token = GetToken();
				iGEMCOUNT = (int)TokenNumber;
				Token = GetToken();
				iZEN = (int)TokenNumber;

				if (iCountDfUpgrade_Statue >= CS_MAX_UPGRADE)
					break;

				g_iNpcUpDfLevel_CSTATUE[iCountDfUpgrade_Statue][0] = iLEVEL;
				g_iNpcUpDfLevel_CSTATUE[iCountDfUpgrade_Statue][1] = iGEMCOUNT;
				g_iNpcUpDfLevel_CSTATUE[iCountDfUpgrade_Statue][2] = iZEN;

				iCountDfUpgrade_Statue++;
			}
			else if (type == 5)
			{
				int iHP = 0;
				int iGEMCOUNT = 0;
				int iZEN = 0;

				Token = GetToken();
				if (strcmp("end", TokenString) == NULL)
				{
					break;
				}

				iHP = (int)TokenNumber;
				Token = GetToken();
				iGEMCOUNT = (int)TokenNumber;
				Token = GetToken();
				iZEN = (int)TokenNumber;

				if (iCountHpUpgrade_Gate >= CS_MAX_UPGRADE)
					break;

				g_iNpcUpMaxHP_CGATE[iCountHpUpgrade_Gate][0] = iHP;
				g_iNpcUpMaxHP_CGATE[iCountHpUpgrade_Gate][1] = iGEMCOUNT;
				g_iNpcUpMaxHP_CGATE[iCountHpUpgrade_Gate][2] = iZEN;

				iCountHpUpgrade_Gate++;
			}
			else if (type == 6)
			{
				int iHP = 0;
				int iGEMCOUNT = 0;
				int iZEN = 0;

				Token = GetToken();
				if (strcmp("end", TokenString) == NULL)
				{
					break;
				}

				iHP = (int)TokenNumber;
				Token = GetToken();
				iGEMCOUNT = (int)TokenNumber;
				Token = GetToken();
				iZEN = (int)TokenNumber;

				if (iCountHpUpgrade_Statue >= CS_MAX_UPGRADE)
					break;

				g_iNpcUpMaxHP_CSTATUE[iCountHpUpgrade_Statue][0] = iHP;
				g_iNpcUpMaxHP_CSTATUE[iCountHpUpgrade_Statue][1] = iGEMCOUNT;
				g_iNpcUpMaxHP_CSTATUE[iCountHpUpgrade_Statue][2] = iZEN;

				iCountHpUpgrade_Statue++;
			}
			else if (type == 7)
			{
				int iLEVEL = 0;
				int iGEMCOUNT = 0;
				int iZEN = 0;

				Token = GetToken();
				if (strcmp("end", TokenString) == NULL)
				{
					break;
				}

				iLEVEL = (int)TokenNumber;
				Token = GetToken();
				iGEMCOUNT = (int)TokenNumber;
				Token = GetToken();
				iZEN = (int)TokenNumber;

				if (iCountRgUpgrade_Statue >= CS_MAX_UPGRADE)
					break;

				g_iNpcUpRgLevel_CSTATUE[iCountRgUpgrade_Statue][0] = iLEVEL;
				g_iNpcUpRgLevel_CSTATUE[iCountRgUpgrade_Statue][1] = iGEMCOUNT;
				g_iNpcUpRgLevel_CSTATUE[iCountRgUpgrade_Statue][2] = iZEN;

				iCountRgUpgrade_Statue++;
			}
			else if (type == 8)
			{
				int iDFVALUE = 0;

				Token = GetToken();
				if (strcmp("end", TokenString) == NULL)
				{
					break;
				}

				iDFVALUE = (int)TokenNumber;

				if (iCountDfValue_Gate >= CS_MAX_UPGRADE + 1)
					break;

				g_iNpcDefense_CGATE[iCountDfValue_Gate] = iDFVALUE;

				iCountDfValue_Gate++;
			}
			else if (type == 9)
			{
				int iDFVALUE = 0;

				Token = GetToken();
				if (strcmp("end", TokenString) == NULL)
				{
					break;
				}

				iDFVALUE = (int)TokenNumber;

				if (iCountDfValue_Statue >= CS_MAX_UPGRADE + 1)
					break;

				g_iNpcDefense_CSTATUE[iCountDfValue_Statue] = iDFVALUE;

				iCountDfValue_Statue++;
			}
		}
	}

	fclose(SMDFile);

	EnterCriticalSection(&m_critScheduleData);

	if (!vtScheduleData.empty())
	{
		for (auto it = vtScheduleData.begin(); it != vtScheduleData.end(); it++)
		{
			m_vtScheduleData.push_back(*it);
		}
	}

	sort(m_vtScheduleData.begin(), m_vtScheduleData.end(), ScheduleStateCompFunc);

	if (!m_vtScheduleData.empty())
	{
		for (int iIDX = 0; iIDX < m_vtScheduleData.size(); iIDX++)
		{
			if (iIDX + 1 < m_vtScheduleData.size())
			{
				int iIDX_SEC1 = m_vtScheduleData[iIDX].m_iADD_DAY * 24 * 60 * 60 + m_vtScheduleData[iIDX].m_iADD_HOUR * 60 * 60 + m_vtScheduleData[iIDX].m_iADD_MIN * 60;
				int iIDX_SEC2 = m_vtScheduleData[iIDX + 1].m_iADD_DAY * 24 * 60 * 60 + m_vtScheduleData[iIDX + 1].m_iADD_HOUR * 60 * 60 + m_vtScheduleData[iIDX + 1].m_iADD_MIN * 60;

				int iIDX_RESULT = iIDX_SEC2 - iIDX_SEC1;

				if (iIDX_RESULT < 0)
				{
					LogAddC(2, "[CastleSiege] CCastleSiege::LoadData() - Date Order is wrong (sort fail) : %d-%d",
						m_vtScheduleData[iIDX].m_iSTATE, m_vtScheduleData[iIDX + 1].m_iSTATE);
				}
				else
				{
					m_vtScheduleData[iIDX].m_iGAP_SEC = iIDX_RESULT;
				}
			}
			else
			{
				m_vtScheduleData[iIDX].m_iGAP_SEC = 0;
			}
		}
	}

	LeaveCriticalSection(&m_critScheduleData);

	EnterCriticalSection(&m_critNpcData);

	if (!vtNpcData.empty())
	{
		for (auto it = vtNpcData.begin(); it != vtNpcData.end(); it++)
		{
			m_vtNpcData.push_back(*it);
		}
	}

	LeaveCriticalSection(&m_critNpcData);

	auto it1 = m_vtScheduleData.begin();

	while (it1 != m_vtScheduleData.end())
	{
		_CS_SCHEDULE_DATA stTEMP = *it1;
		char szTEMP[0x100] = { 0 };

		wsprintf(szTEMP, "STT:%d, DAY:%d, HOUR:%d, MIN:%d, GAP:%d\n",
			stTEMP.m_iSTATE, stTEMP.m_iADD_DAY, stTEMP.m_iADD_HOUR, stTEMP.m_iADD_MIN, stTEMP.m_iGAP_SEC);

		OutputDebugString(szTEMP);
		it1++;
	}

	auto it2 = m_vtNpcData.begin();

	while (it2 != m_vtNpcData.end())
	{
		_CS_NPC_DATA stTEMP = *it2;
		char szTEMP[0x100] = { 0 };

		wsprintf(szTEMP, "NUM:%d, IDX:%d, DBSAVE:%s, SIDE:%d, DFLEVEL:%d, RGLEVEL:%d, MXHP:%d, (%d,%d)-(%d,%d), DIR:%d\n",
			stTEMP.m_iNPC_NUM, stTEMP.m_iNPC_INDEX, (stTEMP.m_bNPC_DBSAVE != 0) ? "YES" : "NO", stTEMP.m_iNPC_SIDE, stTEMP.m_iNPC_DF_LEVEL,
			stTEMP.m_iNPC_RG_LEVEL, stTEMP.m_iNPC_MAXHP, stTEMP.m_iNPC_SX, stTEMP.m_iNPC_SY, stTEMP.m_iNPC_DX, stTEMP.m_iNPC_DY, stTEMP.m_iNPC_DIR);
		OutputDebugString(szTEMP);
		it2++;
	}

	m_bFileDataLoadOK = TRUE;

	return true;
}

int CCastleSiege::DataRequest() //Identical
{
	if (m_bFileDataLoadOK == FALSE)
	{
		LogAddC(2, "[CastleSiege] CCastleSiege::DataRequest() - m_bFileDataLoadOK == FALSE");
		return false;
	}

	if (m_iMapSvrGroup < 0)
	{
		LogAddC(2, "[CastleSiege] CCastleSiege::DataRequest() - m_iMapSvrGroup < 0");
		return false;
	}

	if (m_iCastleDataLoadState != CASTLESIEGE_DATALOAD_2)
	{
		LogAddC(2, "[CastleSiege] CCastleSiege::DataRequest() - m_iCastleDataLoadState != CASTLESIEGE_DATALOAD_2 (%d)", m_iCastleDataLoadState);
		return false;
	}

	int bDbRequestData = FALSE;

	if (m_dwDbDataLoadTickCount == 0)
	{
		bDbRequestData = TRUE;
		m_dwDbDataLoadTickCount = GetTickCount();
		LogAddC(3, "[CastleSiege] CCastleSiege::DataRequest() - REQUEST DATA FIRST");
	}
	else if (GetTickCount() - m_dwDbDataLoadTickCount > 3000)
	{
		bDbRequestData = TRUE;
		m_dwDbDataLoadTickCount = GetTickCount();
		LogAddC(2, "[CastleSiege] CCastleSiege::DataRequest() - REQUEST DATA AGAIN");
	}

	if (bDbRequestData != FALSE)
	{
		GS_GDReqCastleInitData(m_iMapSvrGroup, m_iCastleSiegeCycle);
	}

	return true;
}

int CCastleSiege::Init() //Identical
{
	if (m_iCastleDataLoadState != CASTLESIEGE_DATALOAD_4)
	{
		LogAddC(2, "[CastleSiege] CCastleSiege::Init() - m_iCastleDataLoadState != CASTLESIEGE_DATALOAD_4 (%d)", m_iCastleDataLoadState);
		MsgBox("[CastleSiege] CCastleSiege::Init() - m_iCastleDataLoadState != CASTLESIEGE_DATALOAD_4 (%d)", m_iCastleDataLoadState);
		return false;
	}

	if (m_bFileDataLoadOK == 0 || m_bDbDataLoadOK == 0)
	{
		LogAddC(2, "[CastleSiege] CCastleSiege::Init() - Data Load Fail (FILE:%d, DB:%d)",
			m_bFileDataLoadOK, m_bDbDataLoadOK);
		MsgBox("[CastleSiege] CCastleSiege::Init() - Data Load Fail (FILE:%d, DB:%d)",
			m_bFileDataLoadOK, m_bDbDataLoadOK);
		return false;
	}

	LogAdd("[CastleSiege] CCastleSiege::Init() - START", m_bFileDataLoadOK, m_bDbDataLoadOK);

	m_iCastleDataLoadState = 0;

	CreateAllCsGateLever();

	if (CheckSync() == FALSE)
	{
		LogAddC(2, "[CastleSiege] CCastleSiege::Init() - CheckSync() == FALSE");
		MsgBox("[CastleSiege] CCastleSiege::Init() - CheckSync() == FALSE");
		return false;
	}

	m_bDoRun = TRUE;

	m_dwNPC_DBSAVE_TICK_COUNT = GetTickCount();
	m_dwCALC_LEFTSIEGE_TICK_COUNT = 0;
	m_dwEVENT_MSG_TICK_COUNT = 0;
	m_dwCHECK_GATE_ALIVE_COUNT = 0;
	m_dwCS_STARTTIME_TICK_COUNT = 0;
	m_dwCS_LEFTTIME_TICK_COUNT = 0;
	m_dwCS_JOINSIDE_REFRESH_TICK_COUNT = 0;
	m_dwCS_JOINSIDE_REFRESH_TOTAL_COUNT = 0;
	m_dwCS_MINIMAP_SEND_TICK_COUNT = 0;

	return true;
}

void CCastleSiege::SetState(int iCastleSiegeState, int bSetRemainMsec) //Identical
{
	if (iCastleSiegeState < CASTLESIEGE_STATE_NONE || iCastleSiegeState > CASTLESIEGE_STATE_ENDCYCLE)
		return;

	m_iCastleSiegeState = iCastleSiegeState;

	switch (m_iCastleSiegeState)
	{
	case CASTLESIEGE_STATE_NONE: SetState_NONE(bSetRemainMsec); break;
	case CASTLESIEGE_STATE_IDLE_1: SetState_IDLE_1(bSetRemainMsec); break;
	case CASTLESIEGE_STATE_REGSIEGE: SetState_REGSIEGE(bSetRemainMsec); break;
	case CASTLESIEGE_STATE_IDLE_2: SetState_IDLE_2(bSetRemainMsec); break;
	case CASTLESIEGE_STATE_REGMARK: SetState_REGMARK(bSetRemainMsec); break;
	case CASTLESIEGE_STATE_IDLE_3: SetState_IDLE_3(bSetRemainMsec); break;
	case CASTLESIEGE_STATE_NOTIFY: SetState_NOTIFY(bSetRemainMsec); break;
	case CASTLESIEGE_STATE_READYSIEGE: SetState_READYSIEGE(bSetRemainMsec); break;
	case CASTLESIEGE_STATE_STARTSIEGE: SetState_STARTSIEGE(bSetRemainMsec); break;
	case CASTLESIEGE_STATE_ENDSIEGE: SetState_ENDSIEGE(bSetRemainMsec); break;
	case CASTLESIEGE_STATE_ENDCYCLE: SetState_ENDCYCLE(bSetRemainMsec); break;
	}

	if (m_bDbNpcCreated == FALSE)
	{
		m_bDbNpcCreated = TRUE;
		CreateDbNPC();
	}

	GetLocalTime(&m_tmStateStartDate);
	m_dwEVENT_MSG_TICK_COUNT = 0;
	m_dwCHECK_GATE_ALIVE_COUNT = 0;
}

void CCastleSiege::Run() //Identical
{
	if (this->m_bDoRun == FALSE)
		return;

	if (this->m_bCastleSiegeEnable == FALSE)
		return;

	switch (this->m_iCastleSiegeState)
	{
	case CASTLESIEGE_STATE_NONE:
		this->ProcState_NONE();
		break;
	case CASTLESIEGE_STATE_IDLE_1:
		this->ProcState_IDLE_1();
		break;
	case CASTLESIEGE_STATE_REGSIEGE:
		this->ProcState_REGSIEGE();
		break;
	case CASTLESIEGE_STATE_IDLE_2:
		this->ProcState_IDLE_2();
		break;
	case CASTLESIEGE_STATE_REGMARK:
		this->ProcState_REGMARK();
		break;
	case CASTLESIEGE_STATE_IDLE_3:
		this->ProcState_IDLE_3();
		break;
	case CASTLESIEGE_STATE_NOTIFY:
		this->ProcState_NOTIFY();
		break;
	case CASTLESIEGE_STATE_READYSIEGE:
		this->ProcState_READYSIEGE();
		break;
	case CASTLESIEGE_STATE_STARTSIEGE:
		this->ProcState_STARTSIEGE();
		break;
	case CASTLESIEGE_STATE_ENDSIEGE:
		this->ProcState_ENDSIEGE();
		break;
	case CASTLESIEGE_STATE_ENDCYCLE:
		this->ProcState_ENDCYCLE();
		break;
	}

	if ((GetTickCount() - this->m_dwNPC_DBSAVE_TICK_COUNT) > 300000)
	{
		if (this->m_iCastleSiegeState != CASTLESIEGE_STATE_STARTSIEGE)
		{
			this->StoreDbNpc();
		}
		this->m_dwNPC_DBSAVE_TICK_COUNT = GetTickCount(); //Fixed
	}

	if ((GetTickCount() - this->m_dwCALC_LEFTSIEGE_TICK_COUNT) > 10000)
	{
		this->m_dwCALC_LEFTSIEGE_TICK_COUNT = GetTickCount();
		this->CalcCastleLeftSiegeDate();
	}

	static int g_iLastSiegeUpdate = 0; //DiG Fix @15/01/2010

	if ((GetTickCount() - g_iLastSiegeUpdate) > 3000)
	{
		g_iLastSiegeUpdate = GetTickCount();

		int iLeftSiegeDate = this->CalcCastleLeftSiegeDate();

		if (iLeftSiegeDate >= 0)
		{
			SYSTEMTIME tmLeftDate = this->GetCastleLeftSiegeDate();

			LogAddC(4, "LEFT : SEC(%d), SIEGE-DAY(%04d-%02d-%02d %02d:%02d:%02d)",
				iLeftSiegeDate, tmLeftDate.wYear, tmLeftDate.wMonth, tmLeftDate.wDay,
				tmLeftDate.wHour, tmLeftDate.wMinute, tmLeftDate.wSecond);
		}
		else
		{
			switch (iLeftSiegeDate)
			{
			case CASTLESIEGE_LEFTTIME_ONSIGE:
				LogAddC(4, "[CastleSiege] LEFT-TIME : CASTLESIEGE_LEFTTIME_ONSIGE");
				break;
			case CASTLESIEGE_LEFTTIME_ENDSIEGE:
				LogAddC(4, "[CastleSiege] LEFT-TIME : CASTLESIEGE_LEFTTIME_ENDSIEGE");
				break;
			case CASTLESIEGE_LEFTTIME_NOTRUNNING:
				LogAddC(4, "[CastleSiege] LEFT-TIME : CASTLESIEGE_LEFTTIME_NOTRUNNING");
				break;
			}
		}
	}
}

void CCastleSiege::SetState_NONE(int bSetRemainMsec) //Identical
{
}

void CCastleSiege::SetState_IDLE_1(int bSetRemainMsec) //Identical
{
	LogAdd("SET SetState_IDLE_1()");

	if (bSetRemainMsec != FALSE)
	{
		time_t ttSTime;
		time_t ttETime;
		tm tmETime;
		double dResultSecond;

		memset(&tmETime, 0x00, sizeof(tmETime));

		tmETime.tm_year = m_tmStartDate.wYear - 1900;
		tmETime.tm_mon = m_tmStartDate.wMonth - 1;
		tmETime.tm_mday = m_tmStartDate.wDay;

		ttETime = mktime(&tmETime);
		time(&ttSTime);

		dResultSecond = difftime(ttETime, ttSTime);
		m_iCS_REMAIN_MSEC = dResultSecond * (double)1000.0;
	}
}

void CCastleSiege::SetState_REGSIEGE(int bSetRemainMsec) //Identical
{
	LogAdd("SET SetState_REGSIEGE()");

	if (bSetRemainMsec != FALSE)
	{
		int iGAP_SEC = GetStateGapSec(CASTLESIEGE_STATE_REGSIEGE);

		if (iGAP_SEC < 0)
		{
			m_bDoRun = 0;
			MsgBox("[CastleSiege] CCastleSiege::SetState_REGSIEGE() - iGAP_SEC < 0");
		}

		m_iCS_REMAIN_MSEC = iGAP_SEC * 1000;
	}

	GS_GDReqRestartCastleState(m_iMapSvrGroup);
}

void CCastleSiege::SetState_IDLE_2(int bSetRemainMsec) //Identical
{
	LogAdd("SET SetState_IDLE_2()");

	if (bSetRemainMsec != FALSE)
	{
		int iGAP_SEC = GetStateGapSec(CASTLESIEGE_STATE_IDLE_2);

		if (iGAP_SEC < 0)
		{
			m_bDoRun = 0;
			MsgBox("[CastleSiege] CCastleSiege::SetState_IDLE_2() - iGAP_SEC < 0");
		}

		m_iCS_REMAIN_MSEC = iGAP_SEC * 1000;
	}
}

void CCastleSiege::SetState_REGMARK(int bSetRemainMsec) //Identical
{
	LogAdd("SET SetState_REGMARK()");

	if (bSetRemainMsec != FALSE)
	{
		int iGAP_SEC = GetStateGapSec(CASTLESIEGE_STATE_REGMARK);

		if (iGAP_SEC < 0)
		{
			m_bDoRun = 0;
			MsgBox("[CastleSiege] CCastleSiege::SetState_REGMARK() - iGAP_SEC < 0");
		}

		m_iCS_REMAIN_MSEC = iGAP_SEC * 1000;
	}
}

void CCastleSiege::SetState_IDLE_3(int bSetRemainMsec) //Identical
{
	LogAdd("SET SetState_IDLE_3()");

	if (bSetRemainMsec != FALSE)
	{
		int iGAP_SEC = GetStateGapSec(CASTLESIEGE_STATE_IDLE_3);

		if (iGAP_SEC < 0)
		{
			m_bDoRun = 0;
			MsgBox("[CastleSiege] CCastleSiege::SetState_IDLE_3() - iGAP_SEC < 0");
		}

		m_iCS_REMAIN_MSEC = iGAP_SEC * 1000;
	}
}

void CCastleSiege::SetState_NOTIFY(int bSetRemainMsec) //Identical
{
	LogAdd("SET SetState_NOTIFY()");

	if (bSetRemainMsec != FALSE)
	{
		int iGAP_SEC = GetStateGapSec(CASTLESIEGE_STATE_NOTIFY);

		if (iGAP_SEC < 0)
		{
			m_bDoRun = 0;
			MsgBox("[CastleSiege] CCastleSiege::SetState_NOTIFY() - iGAP_SEC < 0");
		}

		m_iCS_REMAIN_MSEC = iGAP_SEC * 1000;
	}

	CheckBuildCsGuildInfo();
}

void CCastleSiege::SetState_READYSIEGE(int bSetRemainMsec) //Identical
{
	LogAdd("SET SetState_READYSIEGE()");

	if (bSetRemainMsec != FALSE)
	{
		int iGAP_SEC = GetStateGapSec(CASTLESIEGE_STATE_READYSIEGE);

		if (iGAP_SEC < 0)
		{
			m_bDoRun = 0;
			MsgBox("[CastleSiege] CCastleSiege::SetState_READYSIEGE() - iGAP_SEC < 0");
		}

		m_iCS_REMAIN_MSEC = iGAP_SEC * 1000;
	}

	CheckBuildCsGuildInfo();
}

void CCastleSiege::SetState_STARTSIEGE(int bSetRemainMsec) //Identical
{
	LogAdd("SET SetState_STARTSIEGE()");

	if (bSetRemainMsec != FALSE)
	{
		int iGAP_SEC = GetStateGapSec(CASTLESIEGE_STATE_STARTSIEGE);

		if (iGAP_SEC < 0)
		{
			m_bDoRun = 0;
			MsgBox("[CastleSiege] CCastleSiege::SetState_STARTSIEGE() - iGAP_SEC < 0");
		}

		m_iCS_REMAIN_MSEC = iGAP_SEC * 1000;
	}

	m_bCastleTowerAccessable = FALSE;
	m_bRegCrownAvailable = FALSE;
	m_iCastleCrownAccessUser = -1;
	m_btCastleCrownAccessUserX = 0;
	m_btCastleCrownAccessUserY = 0;
	m_iCastleSwitchAccessUser1 = -1;
	m_iCastleSwitchAccessUser2 = -1;
	m_dwCrownAccessTime = 0;
	m_dwCHECK_GATE_ALIVE_COUNT = 0;
	m_dwCS_STARTTIME_TICK_COUNT = 0;
	m_dwCS_LEFTTIME_TICK_COUNT = GetTickCount();
	m_dwCS_JOINSIDE_REFRESH_TICK_COUNT = GetTickCount();
	m_dwCS_JOINSIDE_REFRESH_TOTAL_COUNT = 0;
	m_dwCS_MINIMAP_SEND_TICK_COUNT = GetTickCount();

	memset(m_szMiddleWinnerGuild, 0x00, sizeof(m_szMiddleWinnerGuild));

	if (CheckAttackGuildExist() == FALSE)
	{
		CheckCastleSiegeResult();
		SetState(CASTLESIEGE_STATE_ENDSIEGE, TRUE);
		LogAddC(2, "[CastleSiege] CCastleSiege::SetState_STARTSIEGE() - CheckAttackGuildExist() == FALSE");
	}
	else
	{
		StoreDbNpc();
		ClearNonDbNPC();
		CheckReviveNonDbNPC();

		if (CheckGuardianStatueExist() == FALSE)
		{
			ClearCastleTowerBarrier();
			SetCastleTowerAccessable(TRUE);
		}

		AdjustDbNpcLevel(); //HermeX Fix
		SetAllCastleGateState(FALSE); //HermeX Fix
		SetAllUserCsJoinSide(); //HermeX Fix
		SavePcRoomUserList(); //HermeX Fix
		ReSpawnEnemyUser(TRUE); //HermeX Fix
		NotifyAllUserCsStartState(1); //HermeX Fix
	}
}

void CCastleSiege::SetState_ENDSIEGE(int bSetRemainMsec) //Identical
{
	LogAdd("SET SetState_ENDSIEGE()");

	if (bSetRemainMsec != FALSE)
	{
		time_t ttSTime;
		time_t ttETime;
		tm tmETime;
		double dResultSecond;

		memset(&tmETime, 0x00, sizeof(tmETime));

		tmETime.tm_year = m_tmEndDate.wYear - 1900;
		tmETime.tm_mon = m_tmEndDate.wMonth - 1;
		tmETime.tm_mday = m_tmEndDate.wDay;

		time(&ttSTime);
		ttETime = mktime(&tmETime);

		dResultSecond = difftime(ttETime, ttSTime);
		m_iCS_REMAIN_MSEC = dResultSecond * (double)1000.0;
	}

	ClearNonDbNPC();
	ResetAllUserCsJoinSide();
	SendAllUserAnyMsg(lMsg.Get(MSGGET(6, 84)), 1);
}

void CCastleSiege::SetState_ENDCYCLE(int bSetRemainMsec) //Identical
{
	LogAdd("SET SetState_ENDCYCLE()");

	SYSTEMTIME tmNowDate;

	GetLocalTime(&tmNowDate);

	tmNowDate.wHour = 0; //HermeX Fix
	tmNowDate.wMinute = 0; //HermeX Fix
	tmNowDate.wSecond = 0; //HermeX Fix
	tmNowDate.wMilliseconds = 0; //Dig Fix

	tmNowDate = m_tmSiegeEndSchedule;//Dig Fix
	m_tmStartDate = m_tmSiegeEndSchedule;

	GetNextDay(&tmNowDate, m_iCastleSiegeCycle, 0, 0, 0);

	GetNextDay(&m_tmSiegeEndSchedule, m_iCastleSiegeCycle, 0, 0, 0);

	m_tmEndDate = tmNowDate;

	LogAdd("[CastleSiege] State - End Cycle Schedule : (%d-%d-%d(%d:%d:%d)) (%d-%d-%d(%d:%d:%d))",
		m_tmStartDate.wYear, m_tmStartDate.wMonth, m_tmStartDate.wDay, m_tmStartDate.wHour, m_tmStartDate.wMinute, m_tmStartDate.wSecond,
		m_tmEndDate.wYear, m_tmEndDate.wMonth, m_tmEndDate.wDay, m_tmEndDate.wHour, m_tmEndDate.wMinute, m_tmEndDate.wSecond);

	LogAdd("[CastleSiege] State - End Cycle : Date-Changing Info (%d-%d-%d) (%d-%d-%d)",
		m_tmStartDate.wYear, m_tmStartDate.wMonth, m_tmStartDate.wDay,
		m_tmEndDate.wYear, m_tmEndDate.wMonth, m_tmEndDate.wDay);

	GS_GDReqSiegeDateChange(m_iMapSvrGroup, -1, m_tmStartDate.wYear, m_tmStartDate.wMonth, m_tmStartDate.wDay, m_tmEndDate.wYear, m_tmEndDate.wMonth, m_tmEndDate.wDay);
	GS_GDReqResetRegSiegeInfo(m_iMapSvrGroup);
	GS_GDReqResetSiegeGuildInfo(m_iMapSvrGroup);
	SetState(CASTLESIEGE_STATE_REGSIEGE, 1);
}

void CCastleSiege::ProcState_NONE()
{
}

void CCastleSiege::ProcState_IDLE_1() //Identical
{
	int iTICK_MSEC = (GetTickCount() - this->m_iCS_TICK_COUNT);

	if (iTICK_MSEC >= 1000)
	{
		this->m_iCS_REMAIN_MSEC -= iTICK_MSEC;
		this->m_iCS_TICK_COUNT = GetTickCount();
		LogAddC(3, "RUN ProcState_IDLE_1()\tLEFT-MSEC:%d", this->m_iCS_REMAIN_MSEC);
	}

	if (this->m_iCS_REMAIN_MSEC <= 0)
	{
		this->SetState(CASTLESIEGE_STATE_REGSIEGE, 1);
	}
}

void CCastleSiege::ProcState_REGSIEGE() //Identical
{
	int iTICK_MSEC = (GetTickCount() - this->m_iCS_TICK_COUNT);

	if (iTICK_MSEC >= 1000)
	{
		this->m_iCS_REMAIN_MSEC -= iTICK_MSEC;
		this->m_iCS_TICK_COUNT = GetTickCount();

		if ((GetTickCount() - this->m_dwEVENT_MSG_TICK_COUNT) > 1800000)
		{
			this->SendAllUserAnyMsg(lMsg.Get(MSGGET(6, 78)), 1);
			this->m_dwEVENT_MSG_TICK_COUNT = GetTickCount();
		}

		LogAddC(3, "RUN ProcState_REGSIEGE()\tLEFT-MSEC:%d", this->m_iCS_REMAIN_MSEC);
	}

	if (this->m_iCS_REMAIN_MSEC <= 0)
	{
		this->SetState(CASTLESIEGE_STATE_IDLE_2, 1);
	}
}

void CCastleSiege::ProcState_IDLE_2() //Identical
{
	int iTICK_MSEC = (GetTickCount() - this->m_iCS_TICK_COUNT);

	if (iTICK_MSEC >= 1000)
	{
		this->m_iCS_REMAIN_MSEC -= iTICK_MSEC;
		this->m_iCS_TICK_COUNT = GetTickCount();
		LogAddC(3, "RUN ProcState_IDLE_2()\tLEFT-MSEC:%d", this->m_iCS_REMAIN_MSEC);
	}

	if (this->m_iCS_REMAIN_MSEC <= 0)
	{
		this->SetState(CASTLESIEGE_STATE_REGMARK, 1);
	}
}

void CCastleSiege::ProcState_REGMARK() //Identical
{
	int iTICK_MSEC = (GetTickCount() - this->m_iCS_TICK_COUNT);

	if (iTICK_MSEC >= 1000)
	{
		this->m_iCS_REMAIN_MSEC -= iTICK_MSEC;
		this->m_iCS_TICK_COUNT = GetTickCount();

		if ((GetTickCount() - this->m_dwEVENT_MSG_TICK_COUNT) > 1800000)
		{
			this->SendAllUserAnyMsg(lMsg.Get(MSGGET(6, 79)), 1);
			this->m_dwEVENT_MSG_TICK_COUNT = GetTickCount();
		}

		LogAddC(3, "RUN ProcState_REGMARK()\tLEFT-MSEC:%d", this->m_iCS_REMAIN_MSEC);
	}

	if (this->m_iCS_REMAIN_MSEC <= 0)
	{
		this->SetState(CASTLESIEGE_STATE_IDLE_3, 1);
	}
}

void CCastleSiege::ProcState_IDLE_3()
{
	int iTICK_MSEC = (GetTickCount() - this->m_iCS_TICK_COUNT);

	if (iTICK_MSEC >= 1000)
	{
		this->m_iCS_REMAIN_MSEC -= iTICK_MSEC;
		this->m_iCS_TICK_COUNT = GetTickCount();

		if ((GetTickCount() - this->m_dwEVENT_MSG_TICK_COUNT) > 7200000)
		{
			this->SendAllUserAnyMsg(lMsg.Get(MSGGET(6, 80)), 1);
			this->m_dwEVENT_MSG_TICK_COUNT = GetTickCount();
		}

		LogAddC(3, "RUN ProcState_IDLE_3()\tLEFT-MSEC:%d", this->m_iCS_REMAIN_MSEC);
	}

	if (this->m_iCS_REMAIN_MSEC <= 0)
	{
		this->SetState(CASTLESIEGE_STATE_NOTIFY, 1);
	}
}

void CCastleSiege::ProcState_NOTIFY()
{
	int iTICK_MSEC = (GetTickCount() - this->m_iCS_TICK_COUNT);

	if (iTICK_MSEC >= 1000)
	{
		this->m_iCS_REMAIN_MSEC -= iTICK_MSEC;
		this->m_iCS_TICK_COUNT = GetTickCount();

		if ((GetTickCount() - this->m_dwEVENT_MSG_TICK_COUNT) > 1800000)
		{
			this->SendAllUserAnyMsg(lMsg.Get(MSGGET(6, 81)), 1);
			this->m_dwEVENT_MSG_TICK_COUNT = GetTickCount();
		}

		LogAddC(3, "RUN ProcState_NOTIFY()\tLEFT-MSEC:%d", this->m_iCS_REMAIN_MSEC);
	}

	if (this->m_iCS_REMAIN_MSEC <= 0)
	{
		this->SetState(CASTLESIEGE_STATE_READYSIEGE, 1);
	}
}

void CCastleSiege::ProcState_READYSIEGE() //Identical
{
	int iTICK_MSEC = (GetTickCount() - this->m_iCS_TICK_COUNT);

	if (iTICK_MSEC >= 1000)
	{
		this->m_iCS_REMAIN_MSEC -= iTICK_MSEC;
		this->m_iCS_TICK_COUNT = GetTickCount();

		if ((GetTickCount() - this->m_dwEVENT_MSG_TICK_COUNT) > 1800000)
		{
			this->SendAllUserAnyMsg(lMsg.Get(MSGGET(6, 82)), 1);
			this->m_dwEVENT_MSG_TICK_COUNT = GetTickCount();
		}

		if (this->m_iCS_REMAIN_MSEC <= 300000)
		{
			if ((GetTickCount() - this->m_dwCS_STARTTIME_TICK_COUNT) > 60000)
			{
				char szBuff[256] = { 0 };
				wsprintf(szBuff, lMsg.Get(MSGGET(6, 188)), (this->m_iCS_REMAIN_MSEC / 60000) + 1);
				this->SendAllUserAnyMsg(szBuff, 2);
				this->m_dwCS_STARTTIME_TICK_COUNT = GetTickCount();
			}
		}

		LogAddC(3, "RUN ProcState_READYSIEGE()\tLEFT-MSEC:%d", this->m_iCS_REMAIN_MSEC);
	}

	if (this->m_iCS_REMAIN_MSEC <= 0)
	{
		this->SetState(CASTLESIEGE_STATE_STARTSIEGE, 1);
	}
}

void CCastleSiege::ProcState_STARTSIEGE() //Identical
{
	int iTICK_MSEC = (GetTickCount() - this->m_iCS_TICK_COUNT);

	if (iTICK_MSEC >= 1000)
	{
		this->m_iCS_REMAIN_MSEC -= iTICK_MSEC;
		this->m_iCS_TICK_COUNT = GetTickCount();
		this->CheckMiddleWinnerGuild();

		if ((GetTickCount() - this->m_dwCHECK_GATE_ALIVE_COUNT) > 5000)
		{
			this->CheckCsDbNpcAlive();
			this->m_dwCHECK_GATE_ALIVE_COUNT = GetTickCount();
		}

		if ((GetTickCount() - this->m_dwCS_LEFTTIME_TICK_COUNT) > 180000)
		{
			if (this->m_iCS_REMAIN_MSEC > 180000)
			{
				GCAnsCsLeftTimeAlarm((this->m_iCS_REMAIN_MSEC / 1000) / 3600, ((this->m_iCS_REMAIN_MSEC / 1000) % 3600) / 60);
				this->m_dwCS_LEFTTIME_TICK_COUNT = GetTickCount();
			}
		}

		if (this->m_iCS_REMAIN_MSEC <= 180000)
		{
			if ((GetTickCount() - this->m_dwCS_LEFTTIME_TICK_COUNT) > 60000)
			{
				GCAnsCsLeftTimeAlarm(((this->m_iCS_REMAIN_MSEC / 1000) / 3600), ((this->m_iCS_REMAIN_MSEC / 1000) % 3600) / 60);
				this->m_dwCS_LEFTTIME_TICK_COUNT = GetTickCount();
			}
		}

		if (this->m_dwCS_JOINSIDE_REFRESH_TOTAL_COUNT < 3)
		{
			if ((GetTickCount() - this->m_dwCS_JOINSIDE_REFRESH_TICK_COUNT) > 10000)
			{
				this->SetAllUserCsJoinSide();
				this->m_dwCS_JOINSIDE_REFRESH_TICK_COUNT = GetTickCount();
				this->m_dwCS_JOINSIDE_REFRESH_TOTAL_COUNT++;
			}
		}

		if ((GetTickCount() - this->m_dwCS_MINIMAP_SEND_TICK_COUNT) > 3000)
		{
			this->OperateMiniMapWork();
			this->m_dwCS_MINIMAP_SEND_TICK_COUNT = GetTickCount();
		}

		if ((GetTickCount() - this->m_dwEVENT_MSG_TICK_COUNT) > 1800000)
		{
			this->SendAllUserAnyMsg(lMsg.Get(MSGGET(6, 83)), 1);
			this->m_dwEVENT_MSG_TICK_COUNT = GetTickCount();
		}

		LogAddC(3, "RUN ProcState_READYSIEGE()\tLEFT-MSEC:%d", this->m_iCS_REMAIN_MSEC);
	}

	if (this->m_iCS_REMAIN_MSEC <= 0)
	{
		if (this->CheckCastleSiegeResult() == TRUE)
		{
			GS_GDReqResetCastleTaxInfo(this->m_iMapSvrGroup);
		}
		this->ReSpawnEnemyUser(FALSE);

		if (this->m_btIsCastleOccupied == 1)
		{
			GS_GDReqCastleOwnerChange(this->m_iMapSvrGroup, this->m_btIsCastleOccupied, this->m_szCastleOwnerGuild);
		}

		GS_GDReqSiegeEndedChange(this->m_iMapSvrGroup, TRUE);

		this->StoreDbNpc();
		this->NotifyAllUserCsStartState(0);

		GS_GDReqResetSiegeGuildInfo(this->m_iMapSvrGroup);

		this->SetState(CASTLESIEGE_STATE_ENDSIEGE, 1);
	}
}

void CCastleSiege::ProcState_ENDSIEGE() //Identical
{
	int iTICK_MSEC = (GetTickCount() - this->m_iCS_TICK_COUNT);

	if (iTICK_MSEC >= 1000)
	{
		this->m_iCS_REMAIN_MSEC -= iTICK_MSEC;
		this->m_iCS_TICK_COUNT = GetTickCount();

		LogAddC(3, "RUN ProcState_ENDSIEGE()\tLEFT-MSEC:%d", this->m_iCS_REMAIN_MSEC);
	}

	if (this->m_iCS_REMAIN_MSEC <= 0)
	{
		this->SetState(CASTLESIEGE_STATE_ENDCYCLE, 1);
	}
}

void CCastleSiege::ProcState_ENDCYCLE()
{
	int iTICK_MSEC = (GetTickCount() - this->m_iCS_TICK_COUNT);

	if (iTICK_MSEC >= 1000)
	{
		this->m_iCS_REMAIN_MSEC -= iTICK_MSEC;
		this->m_iCS_TICK_COUNT = GetTickCount();

		LogAddC(3, "RUN ProcState_ENDCYCLE()\tLEFT-MSEC:%d", this->m_iCS_REMAIN_MSEC);
	}

	if (this->m_iCS_REMAIN_MSEC <= 0)
	{
		this->SetState(CASTLESIEGE_STATE_IDLE_1, 1);
	}
}

BOOL CCastleSiege::FirstCreateDbNPC()
{
	char cBUFFER[4240];
	CSP_REQ_NPCSAVEDATA* lpMsg;
	CSP_NPCSAVEDATA* lpMsgBody;

	if (this->m_iCastleDataLoadState != CASTLESIEGE_DATALOAD_4)
	{
		LogAddC(2, "[CastleSiege] CCastleSiege::FirstCreateDbNPC() - m_iCastleDataLoadState != CASTLESIEGE_DATALOAD_4");
		return FALSE;
	}

	lpMsg = (CSP_REQ_NPCSAVEDATA*)cBUFFER;
	lpMsgBody = (CSP_NPCSAVEDATA*)&cBUFFER[sizeof(CSP_REQ_NPCSAVEDATA)];
	int iCOUNT = 0;

	EnterCriticalSection(&this->m_critNpcData);

	auto it = this->m_vtNpcData.begin();
	BOOL bExist = FALSE;

	while (it != this->m_vtNpcData.end())
	{
		_CS_NPC_DATA & pNpcData = _CS_NPC_DATA(*it);

		if (pNpcData.m_bNPC_DBSAVE == TRUE)
		{
			it->SetBaseValue();
			it->m_iNPC_LIVE = 1;
			it->m_iNPC_SIDE = 1;

			lpMsgBody[iCOUNT].iNpcNumber = pNpcData.m_iNPC_NUM;
			lpMsgBody[iCOUNT].iNpcIndex = pNpcData.m_iNPC_INDEX;
			lpMsgBody[iCOUNT].iNpcDfLevel = pNpcData.m_iNPC_BASE_DF_LEVEL;
			lpMsgBody[iCOUNT].iNpcRgLevel = pNpcData.m_iNPC_BASE_RG_LEVEL;
			lpMsgBody[iCOUNT].iNpcMaxHp = pNpcData.m_iNPC_BASE_MAXHP;
			lpMsgBody[iCOUNT].iNpcHp = pNpcData.m_iNPC_BASE_HP;
			lpMsgBody[iCOUNT].btNpcX = pNpcData.m_iNPC_BASE_SX;
			lpMsgBody[iCOUNT].btNpcY = pNpcData.m_iNPC_BASE_SY;
			lpMsgBody[iCOUNT].btNpcDIR = pNpcData.m_iNPC_BASE_DIR;

			iCOUNT++;
		}
		it++;
	}

	LeaveCriticalSection(&this->m_critNpcData);

	lpMsg->wMapSvrNum = this->m_iMapSvrGroup;
	lpMsg->iCount = iCOUNT;
	lpMsg->h.set((LPBYTE)&lpMsg->h, 0x84, (iCOUNT * sizeof(CSP_NPCSAVEDATA)) + sizeof(CSP_REQ_NPCSAVEDATA));
	cDBSMng.Send((PCHAR)lpMsg, (iCOUNT * sizeof(CSP_NPCSAVEDATA)) + sizeof(CSP_REQ_NPCSAVEDATA));

	return TRUE;
}

BOOL CCastleSiege::SetCastleInitData(CSP_ANS_CSINITDATA* lpMsg) //Identical
{
	if (this->m_iCastleDataLoadState != CASTLESIEGE_DATALOAD_3)
	{
		LogAddC(2, "[CastleSiege] CCastleSiege::SetCastleInitData() - m_iCastleDataLoadState != CASTLESIEGE_DATALOAD_3");
		return FALSE;
	}

	if (lpMsg == NULL)
		return FALSE;

	memset(&this->m_tmStartDate, 0, sizeof(this->m_tmStartDate));
	memset(&this->m_tmEndDate, 0, sizeof(this->m_tmEndDate));

	this->m_tmStartDate.wYear = lpMsg->wStartYear;
	this->m_tmStartDate.wMonth = lpMsg->btStartMonth;
	this->m_tmStartDate.wDay = lpMsg->btStartDay;
	this->m_tmEndDate.wYear = lpMsg->wEndYear;
	this->m_tmEndDate.wMonth = lpMsg->btEndMonth;
	this->m_tmEndDate.wDay = lpMsg->btEndDay;
	this->m_btIsSiegeGuildList = lpMsg->btIsSiegeGuildList;
	this->m_btIsSiegeEnded = lpMsg->btIsSiegeEnded;
	this->m_btIsCastleOccupied = lpMsg->btIsCastleOccupied;

	memset(&this->m_szCastleOwnerGuild, 0, sizeof(this->m_szCastleOwnerGuild));
	memcpy(&this->m_szCastleOwnerGuild, lpMsg->szCastleOwnGuild, sizeof(lpMsg->szCastleOwnGuild));

	this->m_i64CastleMoney = lpMsg->i64CastleMoney;
	this->m_iTaxRateChaos = lpMsg->iTaxRateChaos;
	this->m_iTaxRateStore = lpMsg->iTaxRateStore;
	this->m_iTaxHuntZone = lpMsg->iTaxHuntZone;

	int iSTART_DATE_NUM = MACRO2((MACRO1(m_tmStartDate.wDay) | MACRO1(m_tmStartDate.wMonth) << 8) & 0xFFFF) | MACRO2(m_tmStartDate.wYear) << 16;
	int iEND_DATE_NUM = MACRO2((MACRO1(m_tmEndDate.wDay) | MACRO1(m_tmEndDate.wMonth) << 8) & 0xFFFF) | MACRO2(m_tmEndDate.wYear) << 16;

	m_tmSiegeEndSchedule = m_tmStartDate;

	SYSTEMTIME EndTime;
	GetStateDate(CASTLESIEGE_STATE_ENDCYCLE, &EndTime);

	LogAdd("[CastleSiege] CCastleSiege::LoadData() - Siege Schedule Start Date (%d-%d-%d)",
		m_tmStartDate.wYear, m_tmStartDate.wMonth, m_tmStartDate.wDay);

	LogAdd("[CastleSiege] CCastleSiege::LoadData() - Siege Schedule Date (%d-%d-%d)",
		EndTime.wDay, EndTime.wHour, EndTime.wMinute);

	GetNextDay(&m_tmSiegeEndSchedule, EndTime.wDay, EndTime.wHour, EndTime.wMinute, 0);

	LogAdd("[CastleSiege] CCastleSiege::LoadData() - Siege Schedule End Date (%d-%d-%d(%d:%d:%d)",
		m_tmSiegeEndSchedule.wYear, m_tmSiegeEndSchedule.wMonth, m_tmSiegeEndSchedule.wDay,
		m_tmSiegeEndSchedule.wHour, m_tmSiegeEndSchedule.wMinute, m_tmSiegeEndSchedule.wSecond);

	if (iSTART_DATE_NUM > iEND_DATE_NUM)
	{
		LogAddC(2, "[CastleSiege] CCastleSiege::SetCastleInitData() - iSTART_DATE_NUM > iEND_DATE_NUM");
		return FALSE;
	}
	return TRUE;
}

BOOL CCastleSiege::SetCastleNpcData(CSP_CSINITDATA* lpMsg, int iCOUNT) //Identical (HermeX & DiG Fix Applied)
{
	if (this->m_iCastleDataLoadState != CASTLESIEGE_DATALOAD_3)
	{
		LogAddC(2, "[CastleSiege] CCastleSiege::SetCastleNpcData() - m_iCastleDataLoadState != CASTLESIEGE_DATALOAD_3");
		return FALSE;
	}

	if (lpMsg == NULL)
		return FALSE;

	if (iCOUNT < 0)
		return FALSE;

	for (int iNPC_COUNT = 0; iNPC_COUNT < iCOUNT; iNPC_COUNT++)
	{
		EnterCriticalSection(&this->m_critNpcData);

		auto it = this->m_vtNpcData.begin(); //HermeX Fix

		BOOL bExist = FALSE;

		while (it != this->m_vtNpcData.end())
		{
			_CS_NPC_DATA & NpcData = _CS_NPC_DATA(*it);

			if (NpcData.m_iNPC_NUM == lpMsg[iNPC_COUNT].iNpcNumber)
			{
				if (NpcData.m_iNPC_INDEX == lpMsg[iNPC_COUNT].iNpcIndex)
				{
					it->m_iNPC_LIVE = 1;
					it->m_iNPC_DF_LEVEL = lpMsg[iNPC_COUNT].iNpcDfLevel;
					it->m_iNPC_RG_LEVEL = lpMsg[iNPC_COUNT].iNpcRgLevel;
					it->m_iNPC_MAXHP = lpMsg[iNPC_COUNT].iNpcMaxHp;
					it->m_iNPC_HP = lpMsg[iNPC_COUNT].iNpcHp;
					it->m_iNPC_SX = lpMsg[iNPC_COUNT].btNpcX;
					it->m_iNPC_SY = lpMsg[iNPC_COUNT].btNpcY;
					it->m_iNPC_DX = -1;
					it->m_iNPC_DY = -1;
					it->m_iNPC_DIR = lpMsg[iNPC_COUNT].btNpcDIR;
					it->m_iNPC_SIDE = 1;
					bExist = TRUE;

					break;
				}
			}
			it++;
		}

		LeaveCriticalSection(&this->m_critNpcData);

		if (bExist == FALSE) //HermeX Fix
		{
			_CS_NPC_DATA pNpcData2;
			pNpcData2.m_bIN_USE = TRUE;
			pNpcData2.m_iNPC_NUM = lpMsg[iNPC_COUNT].iNpcNumber;
			pNpcData2.m_iNPC_INDEX = lpMsg[iNPC_COUNT].iNpcIndex;
			pNpcData2.m_iNPC_LIVE = 1;
			pNpcData2.m_iNPC_SIDE = 1;
			pNpcData2.m_iNPC_BASE_DF_LEVEL = lpMsg[iNPC_COUNT].iNpcDfLevel;
			pNpcData2.m_iNPC_DF_LEVEL = pNpcData2.m_iNPC_BASE_DF_LEVEL;
			pNpcData2.m_iNPC_BASE_RG_LEVEL = lpMsg[iNPC_COUNT].iNpcRgLevel;
			pNpcData2.m_iNPC_RG_LEVEL = pNpcData2.m_iNPC_BASE_RG_LEVEL;

			pNpcData2.m_iNPC_BASE_MAXHP = lpMsg[iNPC_COUNT].iNpcMaxHp;
			pNpcData2.m_iNPC_MAXHP = pNpcData2.m_iNPC_BASE_MAXHP;
			pNpcData2.m_iNPC_BASE_HP = lpMsg[iNPC_COUNT].iNpcHp;
			pNpcData2.m_iNPC_HP = pNpcData2.m_iNPC_BASE_HP;
			pNpcData2.m_iNPC_BASE_SX = lpMsg[iNPC_COUNT].btNpcX;
			pNpcData2.m_iNPC_SX = pNpcData2.m_iNPC_BASE_SX;
			pNpcData2.m_iNPC_BASE_SY = lpMsg[iNPC_COUNT].btNpcY;
			pNpcData2.m_iNPC_SY = pNpcData2.m_iNPC_BASE_SY;
			pNpcData2.m_iNPC_BASE_DX = -1;
			pNpcData2.m_iNPC_DX = pNpcData2.m_iNPC_BASE_DX;
			pNpcData2.m_iNPC_BASE_DY = -1;
			pNpcData2.m_iNPC_DY = pNpcData2.m_iNPC_BASE_DY;
			pNpcData2.m_iNPC_BASE_DIR = lpMsg[iNPC_COUNT].btNpcDIR;
			pNpcData2.m_iNPC_DIR = pNpcData2.m_iNPC_BASE_DIR;
			EnterCriticalSection(&this->m_critNpcData);
			this->m_vtNpcData.push_back(pNpcData2);
			LeaveCriticalSection(&this->m_critNpcData);
		}
	}
	return TRUE;
}

int CCastleSiege::CheckSync() //Identical
{
	if (m_bFileDataLoadOK == FALSE)
	{
		LogAddC(2, "[CastleSiege] CCastleSiege::CheckSync() - m_bFileDataLoadOK == FALSE");
		return false;
	}

	m_iCS_TICK_COUNT = GetTickCount();

	_SYSTEMTIME tmToDay;

	GetLocalTime(&tmToDay);
	int iTODAY_DATE_NUM = MACRO2((MACRO1(tmToDay.wDay) | MACRO1(tmToDay.wMonth) << 8) & 0xFFFF) | MACRO2(tmToDay.wYear) << 16;
	int iCastleInitState = 0;

	if (m_bFixCastleCycleStartDate != 0)
	{
		m_tmStartDate.wYear = m_tmFixCastleCycleStartDate.wYear;
		m_tmStartDate.wMonth = m_tmFixCastleCycleStartDate.wMonth;
		m_tmStartDate.wDay = m_tmFixCastleCycleStartDate.wDay;

		m_tmEndDate = m_tmStartDate;
		GetNextDay(&m_tmEndDate, m_iCastleSiegeCycle, 0, 0, 0);
	}

	int iEVENT_END_DATE_NUM = MACRO2((MACRO1(m_tmEndDate.wDay) | MACRO1(m_tmEndDate.wMonth) << 8) & 0xFFFF) | MACRO2(m_tmEndDate.wYear) << 16;

	if (iEVENT_END_DATE_NUM <= iTODAY_DATE_NUM)
	{
		m_bFixCastleCycleStartDate = 0;
		MsgBox("[CastleSiege] CCastleSiege::CheckSync() - iEVENT_END_DATE_NUM (%04d-%02d-%02d) <= iTODAY_DATE_NUM (%04d-%02d-%02d)",
			m_tmEndDate.wYear, m_tmEndDate.wMonth, m_tmEndDate.wDay, tmToDay.wYear, tmToDay.wMonth, tmToDay.wDay);
		return false;
	}

	if (m_bFixCastleCycleStartDate != 0)
	{
		GS_GDReqSiegeDateChange(m_iMapSvrGroup, -1, m_tmStartDate.wYear, m_tmStartDate.wMonth, m_tmStartDate.wDay,
			m_tmEndDate.wYear, m_tmEndDate.wMonth, m_tmEndDate.wDay);
	}

	if (m_bFixCastleStateStartDate != 0)
	{
		int bSpecificStateExist = FALSE;

		EnterCriticalSection(&m_critScheduleData);

		auto it = m_vtScheduleData.begin();

		while (it != m_vtScheduleData.end())
		{
			_CS_SCHEDULE_DATA & pScheduleData = (_CS_SCHEDULE_DATA &)*it;

			if (pScheduleData.m_iSTATE == m_iFixCastleSpecificState)
			{
				bSpecificStateExist = TRUE;
				break;
			}

			it++;
		}
		LeaveCriticalSection(&m_critScheduleData);

		if (bSpecificStateExist != FALSE)
		{
			time_t ttSTime;
			time_t ttETime;
			tm tmETime;
			double dResultSecond;
			memset(&tmETime, 0x00, sizeof(tmETime));

			tmETime.tm_year = m_tmFixCastleStateStartDate.wYear - 1900;
			tmETime.tm_mon = m_tmFixCastleStateStartDate.wMonth - 1;
			tmETime.tm_mday = m_tmFixCastleStateStartDate.wDay;
			tmETime.tm_hour = m_tmFixCastleStateStartDate.wHour;
			tmETime.tm_min = m_tmFixCastleStateStartDate.wMinute;

			time(&ttSTime);
			ttETime = mktime(&tmETime);

			dResultSecond = difftime(ttETime, ttSTime);

			m_iCS_REMAIN_MSEC = dResultSecond * (double)1000.0;
			m_iCastleSiegeState = m_iFixCastleSpecificState - 1;
			SetState(m_iCastleSiegeState, 0);
			return true;
		}
		else
		{
			MsgBox("[CastleSiege] CCastleSiege::CheckSync() - FIXED STATE:%d NOT FOUND IN SCHEDULE (P.S.> Check File 'MuCastleData.dat', 'commonserver.cfg')", m_iFixCastleSpecificState);
			m_bFixCastleStateStartDate = 0;
		}
	}

	if (m_btIsSiegeEnded)
	{
		SetState(CASTLESIEGE_STATE_ENDSIEGE, 1);
		return true;
	}

	int iEVENT_START_DATE_NUM = MACRO2((MACRO1(m_tmStartDate.wDay) | MACRO1(m_tmStartDate.wMonth) << 8) & 0xFFFF) | MACRO2(m_tmStartDate.wYear) << 16;

	if (iEVENT_START_DATE_NUM > iTODAY_DATE_NUM)
	{
		SetState(CASTLESIEGE_STATE_IDLE_1, 1);
		return true;
	}
	else
	{
		int bStateSetted = 0;
		_CS_SCHEDULE_DATA pScheData_FR;
		_CS_SCHEDULE_DATA pScheData_RR;

		EnterCriticalSection(&m_critScheduleData);

		auto it = m_vtScheduleData.begin();

		while (it != m_vtScheduleData.end())
		{
			_CS_SCHEDULE_DATA & pScheduleData = (_CS_SCHEDULE_DATA &)*it;;
			_SYSTEMTIME tmSchduleDate;

			tmSchduleDate = m_tmStartDate;
			GetNextDay(&tmSchduleDate, pScheduleData.m_iADD_DAY, 0, 0, 0);
			tmSchduleDate.wHour = pScheduleData.m_iADD_HOUR;
			tmSchduleDate.wMinute = pScheduleData.m_iADD_MIN;

			__int64 i64ScheduleDateNum;
			__int64 i64ToDayDateNum;

			i64ScheduleDateNum = (MACRO2(tmSchduleDate.wMinute) | MACRO2(tmSchduleDate.wHour) << 16) | ((__int64)(MACRO2((MACRO1(tmSchduleDate.wDay) | MACRO1(tmSchduleDate.wMonth) << 8) & 0xFFFF) | MACRO2(tmSchduleDate.wYear) << 16) << 0x20);
			i64ToDayDateNum = (MACRO2(tmToDay.wMinute) | MACRO2(tmToDay.wHour) << 16) | ((__int64)(MACRO2((MACRO1(tmToDay.wDay) | MACRO1(tmToDay.wMonth) << 8) & 0xFFFF) | MACRO2(tmToDay.wYear) << 16) << 0x20);

			if (i64ScheduleDateNum > i64ToDayDateNum)
			{
				bStateSetted = 1;
				pScheData_RR = pScheduleData;
				m_iCastleSiegeState = iCastleInitState;
				break;
			}

			iCastleInitState = pScheduleData.m_iSTATE;
			pScheData_FR = pScheduleData;

			it++;
		}
		LeaveCriticalSection(&m_critScheduleData);

		_SYSTEMTIME tmSchduleDate;

		time_t ttSTime;
		time_t ttETime;
		struct tm tmETime;
		double dResultSecond;

		if (bStateSetted == FALSE)
		{
			MsgBox("[CastleSiege] CCastleSiege::CheckSync() - bStateSetted == FALSE  START_DATE (%04d-%02d-%02d), END_DATE (%04d-%02d-%02d)",
				m_tmStartDate.wYear, m_tmStartDate.wMonth, m_tmStartDate.wDay, m_tmEndDate.wYear, m_tmEndDate.wMonth, m_tmEndDate.wDay);
			return false;
		}

		tmSchduleDate = m_tmStartDate;
		GetNextDay(&tmSchduleDate, pScheData_RR.m_iADD_DAY, 0, 0, 0);
		tmSchduleDate.wHour = pScheData_RR.m_iADD_HOUR;
		tmSchduleDate.wMinute = pScheData_RR.m_iADD_MIN;

		memset(&tmETime, 0x00, sizeof(tmETime));

		tmETime.tm_year = tmSchduleDate.wYear - 1900;
		tmETime.tm_mon = tmSchduleDate.wMonth - 1;
		tmETime.tm_mday = tmSchduleDate.wDay;
		tmETime.tm_hour = tmSchduleDate.wHour;
		tmETime.tm_min = tmSchduleDate.wMinute;

		time(&ttSTime);
		ttETime = mktime(&tmETime);

		dResultSecond = difftime(ttETime, ttSTime);
		m_iCS_REMAIN_MSEC = dResultSecond * (double)1000.0;

		if (m_iCastleSiegeState == CASTLESIEGE_STATE_STARTSIEGE)
		{
			m_iCastleSiegeState = CASTLESIEGE_STATE_READYSIEGE;
			m_iCS_REMAIN_MSEC = 900000;
		}
		else if (m_iCastleSiegeState == CASTLESIEGE_STATE_READYSIEGE)
		{
			if (m_iCS_REMAIN_MSEC < 900000)
			{
				m_iCastleSiegeState = CASTLESIEGE_STATE_READYSIEGE;
				m_iCS_REMAIN_MSEC = 900000;
			}
		}

		SetState(m_iCastleSiegeState, 0);
	}

	return true;
}

void CCastleSiege::GetNextDay(_SYSTEMTIME * st, int iAfterDay, int iAfterHour, int iAfterMin, int iAfterSec) //Identical
{
	__int64 i64;
	_FILETIME fst;
	st->wDayOfWeek = 0;
	st->wMilliseconds = 0;
	st->wSecond = 0;
	SystemTimeToFileTime(st, &fst);
	i64 = ((__int64)fst.dwHighDateTime << 0x20) + fst.dwLowDateTime;
	i64 = i64 + (__int64)iAfterDay * 864000000000 + (__int64)iAfterHour * 36000000000 + (__int64)iAfterMin * 600000000 + (__int64)iAfterSec * 10000000;
	fst.dwHighDateTime = i64 >> 0x20;
	fst.dwLowDateTime = i64 & 0xFFFFFFFF;
	FileTimeToSystemTime(&fst, st);
}

void CCastleSiege::GetStateDate(int iCastleSiegeState, SYSTEMTIME* st) //Identical
{
	EnterCriticalSection(&m_critScheduleData);

	for (auto it = m_vtScheduleData.begin(); it != m_vtScheduleData.end(); it++)
	{
		auto ScheduleData = it;

		if (ScheduleData->m_iSTATE == iCastleSiegeState)
		{
			st->wDay = ScheduleData->m_iADD_DAY;
			st->wHour = ScheduleData->m_iADD_HOUR;
			st->wMinute = ScheduleData->m_iADD_MIN;
			st->wSecond = 0;

			break;
		}
	}
	LeaveCriticalSection(&m_critScheduleData);
}

int CCastleSiege::GetStateGapSec(int iCastleSiegeState) //Identical
{
	int iGAP_SEC = -1;

	EnterCriticalSection(&m_critScheduleData);

	for (auto it = m_vtScheduleData.begin(); it != m_vtScheduleData.end(); it++)
	{
		_CS_SCHEDULE_DATA & pScheduleData = *it;

		if (pScheduleData.m_iSTATE == iCastleSiegeState)
		{
			iGAP_SEC = pScheduleData.m_iGAP_SEC;
			break;
		}
	}

	LeaveCriticalSection(&m_critScheduleData);

	return iGAP_SEC;
}

int CCastleSiege::CalcCastleLeftSiegeDate()
{
	memset(&this->m_tmLeftCastleSiegeDate, 0, sizeof(this->m_tmLeftCastleSiegeDate)); //Identical

	if (this->m_iCastleSiegeState < CASTLESIEGE_STATE_IDLE_1 || CASTLESIEGE_STATE_ENDCYCLE < this->m_iCastleSiegeState) //Fixed
	{
		return CASTLESIEGE_LEFTTIME_NOTRUNNING;
	}

	if (this->m_bDoRun == FALSE)
	{
		return CASTLESIEGE_LEFTTIME_NOTRUNNING;
	}

	if (this->m_iCastleSiegeState == CASTLESIEGE_STATE_STARTSIEGE)
	{
		return CASTLESIEGE_LEFTTIME_ONSIGE;
	}

	if (this->m_btIsSiegeEnded == 1 || this->m_iCastleSiegeState >= CASTLESIEGE_STATE_ENDSIEGE)
	{
		return CASTLESIEGE_LEFTTIME_ENDSIEGE;
	}

	int iGAP_SEC = CASTLESIEGE_LEFTTIME_ONSIGE;
	BOOL bAddStart = FALSE;

	EnterCriticalSection(&this->m_critScheduleData);

	for (auto it = this->m_vtScheduleData.begin(); it != this->m_vtScheduleData.end(); it++)
	{
		auto lpScheduleData = it;

		if (lpScheduleData->m_iSTATE == 7)
		{
			break;
		}

		if (bAddStart)
		{
			iGAP_SEC += lpScheduleData->m_iGAP_SEC;
		}

		if (lpScheduleData->m_iSTATE == this->m_iCastleSiegeState)
		{
			iGAP_SEC = (this->m_iCS_REMAIN_MSEC / 1000);
			bAddStart = TRUE;
		}
	}

	LeaveCriticalSection(&this->m_critScheduleData);

	if (iGAP_SEC >= 0)
	{
		SYSTEMTIME tmLocalTime;
		GetLocalTime(&tmLocalTime);

		this->GetNextDay(&tmLocalTime, 0, 0, 0, iGAP_SEC);

		this->m_tmLeftCastleSiegeDate = tmLocalTime;

		if (iGAP_SEC == 0)
		{
			LogAddC(2, "[CastleSiege] CCastleSiege::CalcCastleLeftSiegeDate() - iGAP_SEC == 0");
		}

		return iGAP_SEC;
	}

	return CASTLESIEGE_LEFTTIME_NOTRUNNING;
}

BOOL CCastleSiege::GetCastleStateTerm(SYSTEMTIME * tmStateStartDate, SYSTEMTIME * tmStateEndDate) //Identical
{
	if (m_iCastleSiegeState < CASTLESIEGE_STATE_IDLE_1 || CASTLESIEGE_STATE_ENDCYCLE < m_iCastleSiegeState) //HermeX Fix
	{
		return FALSE;
	}

	if (m_bDoRun == FALSE)
	{
		return FALSE;
	}

	*tmStateStartDate = m_tmStateStartDate;

	GetLocalTime(tmStateEndDate);

	GetNextDay(tmStateEndDate, 0, 0, 0, m_iCS_REMAIN_MSEC / 1000);

	return TRUE;
}

int CCastleSiege::GetCurRemainSec() //Identical
{
	if (this->m_iCS_REMAIN_MSEC < 0)
		return -1;

	return (this->m_iCS_REMAIN_MSEC / 1000);
}

void CCastleSiege::ClearDbNPC() //Identical
{
	for (int n = 0; n < OBJ_MAXMONSTER; n++)
	{
		if (gObj[n].MapNumber == MAP_INDEX_CASTLESIEGE)
		{
			if (gObj[n].Class == 277 || gObj[n].Class == 283 || gObj[n].Class == 219)
			{
				if (gObj[n].Class == 277)
				{
					this->SetGateBlockState(gObj[n].X, gObj[n].Y, 1);
				}
				gObjDel(n);
			}
		}
	}
}

void CCastleSiege::ClearNonDbNPC() //Identical
{
	for (int n = 0; n < OBJ_MAXMONSTER; n++)
	{
		if (gObjIsConnected(n)
			&& gObj[n].MapNumber == MAP_INDEX_CASTLESIEGE
			&& gObj[n].m_btCsNpcType != NULL
			&& gObj[n].m_btCsNpcType != 1)
		{
			if (gObj[n].Class == 278)
			{
				g_CsNPC_LifeStone.DeleteLifeStone(n);
			}

			if (gObj[n].Class == 287 || gObj[n].Class == 286)
			{
				g_CsNPC_Mercenary.DeleteMercenary(n);
			}

			if (gObj[n].Class == 219)
				continue;

			gObjDel(n);
		}
	}
}

void CCastleSiege::ClearNonDbNPC_MidWin() //Identical
{
	for (int n = 0; n < OBJ_MAXMONSTER; n++)
	{
		if (gObjIsConnected(n))
		{
			if (gObj[n].MapNumber == MAP_INDEX_CASTLESIEGE)
			{
				if (gObj[n].m_btCsNpcType && gObj[n].m_btCsNpcType != 1)
				{
					if (gObj[n].Class == 278)
					{
						g_CsNPC_LifeStone.DeleteLifeStone(n);
					}

					if (gObj[n].Class == 278)
					{
						gObjDel(n);
					}
				}
			}
		}
	}
}

void CCastleSiege::ClearAllNPC() //Identical
{
	for (int n = 0; n < OBJ_MAXMONSTER; n++)
	{
		if (gObj[n].m_btCsNpcType)
		{
			gObjDel(n);
		}
	}
}

void CCastleSiege::CreateDbNPC() //Identical
{
	EnterCriticalSection(&m_critNpcData);

	auto it = m_vtNpcData.begin();
	int bExist = 0;

	while (it != m_vtNpcData.end())
	{
		_CS_NPC_DATA & pNpcData = _CS_NPC_DATA(*it);

		if (pNpcData.m_bIN_USE == 1 && pNpcData.m_iNPC_LIVE == 1)
		{
			int iNPC_INDEX = gObjAddMonster(MAP_INDEX_CASTLESIEGE);

			if (iNPC_INDEX >= 0)
			{
				gObjSetMonster(iNPC_INDEX, pNpcData.m_iNPC_NUM);
				gObj[iNPC_INDEX].m_PosNum = -1;
				gObj[iNPC_INDEX].X = pNpcData.m_iNPC_SX;
				gObj[iNPC_INDEX].Y = pNpcData.m_iNPC_SY;
				gObj[iNPC_INDEX].MapNumber = MAP_INDEX_CASTLESIEGE;
				gObj[iNPC_INDEX].TX = gObj[iNPC_INDEX].X;
				gObj[iNPC_INDEX].TY = gObj[iNPC_INDEX].Y;
				gObj[iNPC_INDEX].m_OldX = gObj[iNPC_INDEX].X;
				gObj[iNPC_INDEX].m_OldY = gObj[iNPC_INDEX].Y;
				gObj[iNPC_INDEX].Dir = pNpcData.m_iNPC_DIR;
				gObj[iNPC_INDEX].StartX = gObj[iNPC_INDEX].X;
				gObj[iNPC_INDEX].StartY = gObj[iNPC_INDEX].Y;
				gObj[iNPC_INDEX].DieRegen = 0;
				gObj[iNPC_INDEX].MaxRegenTime = 0;
				gObj[iNPC_INDEX].Life = pNpcData.m_iNPC_HP;
				gObj[iNPC_INDEX].MaxLife = pNpcData.m_iNPC_MAXHP;
				gObj[iNPC_INDEX].m_btCsNpcType = 1;

				int iNPC_DF_LEVEL = pNpcData.m_iNPC_DF_LEVEL;

				if (iNPC_DF_LEVEL < 0)
				{
					iNPC_DF_LEVEL = 0;
				}

				if (iNPC_DF_LEVEL > CS_MAX_UPGRADE)
				{
					iNPC_DF_LEVEL = CS_MAX_UPGRADE;
				}

				int iNPC_RG_LEVEL = pNpcData.m_iNPC_RG_LEVEL;

				if (iNPC_RG_LEVEL < 0)
				{
					iNPC_RG_LEVEL = 0;
				}

				if (iNPC_RG_LEVEL > CS_MAX_UPGRADE)
				{
					iNPC_RG_LEVEL = CS_MAX_UPGRADE;
				}

				switch (pNpcData.m_iNPC_NUM)
				{
				case 277:
					gObj[iNPC_INDEX].m_Defense = g_iNpcDefense_CGATE[iNPC_DF_LEVEL];
					gObj[iNPC_INDEX].m_MagicDefense = g_iNpcDefense_CGATE[iNPC_DF_LEVEL];
					gObj[iNPC_INDEX].m_btCsNpcDfLevel = iNPC_DF_LEVEL;
					break;
				case 283:
					gObj[iNPC_INDEX].m_Defense = g_iNpcDefense_CSTATUE[iNPC_DF_LEVEL];
					gObj[iNPC_INDEX].m_MagicDefense = g_iNpcDefense_CSTATUE[iNPC_DF_LEVEL];
					gObj[iNPC_INDEX].m_btCsNpcDfLevel = iNPC_DF_LEVEL;
					gObj[iNPC_INDEX].m_btCsNpcRgLevel = iNPC_RG_LEVEL;
					break;
				}

				it->m_btCsNpcExistVal1 = rand() % 255 + 1;
				gObj[iNPC_INDEX].m_btCsNpcExistVal1 = it->m_btCsNpcExistVal1;

				it->m_btCsNpcExistVal2 = rand() % 256;
				gObj[iNPC_INDEX].m_btCsNpcExistVal2 = it->m_btCsNpcExistVal2;

				it->m_btCsNpcExistVal3 = rand() % 256;
				gObj[iNPC_INDEX].m_btCsNpcExistVal3 = it->m_btCsNpcExistVal3;

				it->m_btCsNpcExistVal4 = rand() % 256;
				gObj[iNPC_INDEX].m_btCsNpcExistVal4 = it->m_btCsNpcExistVal4;

				if (pNpcData.m_iNPC_NUM == 277)
				{
					SetGateBlockState(pNpcData.m_iNPC_SX, pNpcData.m_iNPC_SY, 1);
					gObj[iNPC_INDEX].m_btCsGateOpen = TRUE;
					int bCreateLever = FALSE;

					if (pNpcData.m_iCS_GATE_LEVER_INDEX == -1)
					{
						bCreateLever = TRUE;
					}
					else if (CheckLeverAlive(pNpcData.m_iCS_GATE_LEVER_INDEX) == FALSE)
					{
						bCreateLever = TRUE;
					}

					if (bCreateLever != FALSE)
					{
						int iLeverIndex = CreateCsGateLever(pNpcData.m_iNPC_SX, pNpcData.m_iNPC_SY + 4);

						if (OBJMAX_RANGE(iLeverIndex))
						{
							it->m_iCS_GATE_LEVER_INDEX = iLeverIndex;

							int bRETVAL = LinkCsGateLever(iLeverIndex, iNPC_INDEX);

							if (bRETVAL == FALSE)
							{
								LogAddC(2, "[CastleSiege] CCastleSiege::CreateDbNPC() ERROR - Failed to Create Gate Lever : GateIndex:%d", pNpcData.m_iNPC_INDEX);
							}
						}
						else
						{
							it->m_iCS_GATE_LEVER_INDEX = -1;
							LogAddC(2, "[CastleSiege] CCastleSiege::CreateDbNPC() ERROR - Failed to Create Gate Lever : GateIndex:%d", pNpcData.m_iNPC_INDEX);
						}
					}
					else
					{
						int bRETVAL = LinkCsGateLever(pNpcData.m_iCS_GATE_LEVER_INDEX, iNPC_INDEX);

						if (bRETVAL == FALSE)
						{
							LogAddC(2, "[CastleSiege] CCastleSiege::CreateDbNPC() ERROR - Failed to Create Gate Lever : GateIndex:%d", pNpcData.m_iNPC_INDEX);
						}
					}
				}

				it->m_iNPC_OBJINDEX = iNPC_INDEX;
				it->m_iNPC_LIVE = 2;
			}
		}

		it++;
	}
	LeaveCriticalSection(&m_critNpcData);
}

void CCastleSiege::CreateNonDbNPC(int bDelFirst) //Identical
{
	if (bDelFirst)
	{
		ClearNonDbNPC();
	}

	EnterCriticalSection(&m_critNpcData);

	auto it = m_vtNpcData.begin();

	while (it != m_vtNpcData.end())
	{
		_CS_NPC_DATA & pNpcData = _CS_NPC_DATA(*it);

		if (pNpcData.m_bIN_USE == TRUE && pNpcData.m_bNPC_DBSAVE == FALSE)
		{
			int iNPC_INDEX = gObjAddMonster(MAP_INDEX_CASTLESIEGE);

			if (iNPC_INDEX >= 0)
			{
				gObjSetMonster(iNPC_INDEX, pNpcData.m_iNPC_NUM);
				gObj[iNPC_INDEX].m_PosNum = -1;
				gObj[iNPC_INDEX].X = pNpcData.m_iNPC_SX;
				gObj[iNPC_INDEX].Y = pNpcData.m_iNPC_SY;
				gObj[iNPC_INDEX].MapNumber = MAP_INDEX_CASTLESIEGE;
				gObj[iNPC_INDEX].TX = gObj[iNPC_INDEX].X;
				gObj[iNPC_INDEX].TY = gObj[iNPC_INDEX].Y;
				gObj[iNPC_INDEX].m_OldX = gObj[iNPC_INDEX].X;
				gObj[iNPC_INDEX].m_OldY = gObj[iNPC_INDEX].Y;
				gObj[iNPC_INDEX].Dir = pNpcData.m_iNPC_DIR;
				gObj[iNPC_INDEX].StartX = gObj[iNPC_INDEX].X;
				gObj[iNPC_INDEX].StartY = gObj[iNPC_INDEX].Y;
				gObj[iNPC_INDEX].DieRegen = 0;
				gObj[iNPC_INDEX].MaxRegenTime = 0;
				gObj[iNPC_INDEX].Life = pNpcData.m_iNPC_HP;
				gObj[iNPC_INDEX].MaxLife = pNpcData.m_iNPC_MAXHP;

				switch (pNpcData.m_iNPC_SIDE)
				{
				case 1:
					gObj[iNPC_INDEX].m_btCsNpcType = 2;
					break;
				case 2:
					gObj[iNPC_INDEX].m_btCsNpcType = 3;
					break;
				default:
					gObj[iNPC_INDEX].m_btCsNpcType = 3;
					break;
				}

				it->m_btCsNpcExistVal1 = rand() % 255 + 1;
				gObj[iNPC_INDEX].m_btCsNpcExistVal1 = it->m_btCsNpcExistVal1;

				it->m_btCsNpcExistVal2 = rand() % 256;
				gObj[iNPC_INDEX].m_btCsNpcExistVal2 = it->m_btCsNpcExistVal2;

				it->m_btCsNpcExistVal3 = rand() % 256;
				gObj[iNPC_INDEX].m_btCsNpcExistVal3 = it->m_btCsNpcExistVal3;

				it->m_btCsNpcExistVal4 = rand() % 256;
				gObj[iNPC_INDEX].m_btCsNpcExistVal4 = it->m_btCsNpcExistVal4;

				it->m_iNPC_OBJINDEX = iNPC_INDEX;
				it->m_iNPC_LIVE = 2;
			}
		}
		it++;
	}
	LeaveCriticalSection(&m_critNpcData);
}

int CCastleSiege::CheckAddDbNPC(int iIndex, int iNpcType, int iNpcIndex, BYTE & btResult) //Identical
{
	int iRETVAL = 0;

	EnterCriticalSection(&m_critNpcData);

	auto it = m_vtNpcData.begin();

	while (it != m_vtNpcData.end())
	{
		_CS_NPC_DATA & NpcData = _CS_NPC_DATA(*it);

		if (NpcData.m_iNPC_NUM == iNpcType && NpcData.m_iNPC_INDEX == iNpcIndex)
		{
			if (NpcData.m_bIN_USE == TRUE && NpcData.m_iNPC_LIVE > 0 && gObjIsConnected(NpcData.m_iNPC_OBJINDEX) && gObj[NpcData.m_iNPC_OBJINDEX].Class == iNpcType)
			{
				if (gObj[NpcData.m_iNPC_OBJINDEX].Live == 1 && gObj[NpcData.m_iNPC_OBJINDEX].m_iCsNpcExistVal == NpcData.m_iCsNpcExistVal && gObj[NpcData.m_iNPC_OBJINDEX].m_iCsNpcExistVal != 0)
				{
					btResult = 0;
					iRETVAL = 0;

					break;
				}
			}

			int iNpcBuyCost = 0;

			switch (NpcData.m_iNPC_NUM)
			{
			case 277:
				iNpcBuyCost = NpcData.m_iNPC_BASE_MAXHP * 5;
				break;
			case 283:
				iNpcBuyCost = NpcData.m_iNPC_BASE_MAXHP * 3;
				break;
			}

			if (gObj[iIndex].Money < iNpcBuyCost)
			{
				btResult = 3;
				iRETVAL = 0;

				break;
			}

			GS_GDReqCastleNpcBuy(m_iMapSvrGroup, iIndex, iNpcType, iNpcIndex, NpcData.m_iNPC_DF_LEVEL,
				NpcData.m_iNPC_RG_LEVEL, NpcData.m_iNPC_MAXHP, NpcData.m_iNPC_HP, NpcData.m_iNPC_SX, //HermeX FiX @10/02/2010 (double MAXHP)
				NpcData.m_iNPC_SY, NpcData.m_iNPC_DIR, iNpcBuyCost);

			btResult = 1;
			iRETVAL = 1;

			break;
		}

		it++;
	}

	LeaveCriticalSection(&m_critNpcData);

	return iRETVAL;
}

int CCastleSiege::AddDbNPC(int iNpcType, int iNpcIndex) //Identical Func (HermeX & DiG Fix Applied)
{
	int iRETVAL = 0;

	EnterCriticalSection(&this->m_critNpcData);

	auto it = this->m_vtNpcData.begin();

	while (it != this->m_vtNpcData.end())
	{
		_CS_NPC_DATA & NpcData = _CS_NPC_DATA(*it);

		if ((NpcData.m_iNPC_NUM == iNpcType) && (NpcData.m_iNPC_INDEX == iNpcIndex))
		{
			if (gObjIsConnected(NpcData.m_iNPC_OBJINDEX))
			{
				if (gObj[NpcData.m_iNPC_OBJINDEX].Class == iNpcType)
				{
					if (gObj[NpcData.m_iNPC_OBJINDEX].Live == TRUE) //HermeX Fix
					{
						if (gObj[NpcData.m_iNPC_OBJINDEX].m_iCsNpcExistVal == NpcData.m_iCsNpcExistVal)
						{
							if (gObj[NpcData.m_iNPC_OBJINDEX].m_iCsNpcExistVal)
							{
								LogAdd("[CastleSiege] CCastleSiege::AddDbNPC() ERROR - DB NPC EXIST (CLS:%d, IDX:%d(%d), MAXHP:%d, HP:%d, DF:%d, RG:%d)",
									NpcData.m_iNPC_NUM,
									NpcData.m_iNPC_INDEX,
									NpcData.m_iNPC_OBJINDEX,
									gObj[NpcData.m_iNPC_OBJINDEX].MaxLife,
									gObj[NpcData.m_iNPC_OBJINDEX].Life,
									gObj[NpcData.m_iNPC_OBJINDEX].m_btCsNpcDfLevel,
									gObj[NpcData.m_iNPC_OBJINDEX].m_btCsNpcRgLevel);

								break;
							}
						}
					}
				}
			}

			int iObjIndex = gObjAddMonster(MAP_INDEX_CASTLESIEGE);

			if (iObjIndex >= 0)
			{
				::gObjSetMonster(iObjIndex, NpcData.m_iNPC_NUM);

				gObj[iObjIndex].m_PosNum = -1;
				gObj[iObjIndex].X = NpcData.m_iNPC_SX;
				gObj[iObjIndex].Y = NpcData.m_iNPC_SY;
				gObj[iObjIndex].MapNumber = MAP_INDEX_CASTLESIEGE;
				gObj[iObjIndex].TX = gObj[iObjIndex].X;
				gObj[iObjIndex].TY = gObj[iObjIndex].Y;
				gObj[iObjIndex].m_OldX = gObj[iObjIndex].X;
				gObj[iObjIndex].m_OldY = gObj[iObjIndex].Y;
				gObj[iObjIndex].Dir = NpcData.m_iNPC_DIR;
				gObj[iObjIndex].StartX = gObj[iObjIndex].X;
				gObj[iObjIndex].StartY = gObj[iObjIndex].Y;
				gObj[iObjIndex].DieRegen = 0;
				gObj[iObjIndex].MaxRegenTime = 0;

				gObj[iObjIndex].Life = NpcData.m_iNPC_BASE_HP;
				gObj[iObjIndex].MaxLife = NpcData.m_iNPC_BASE_MAXHP;
				gObj[iObjIndex].m_btCsNpcType = 1;

				int iBaseDFLevel = NpcData.m_iNPC_BASE_DF_LEVEL;

				if (iBaseDFLevel < 0)
				{
					iBaseDFLevel = 0;
				}

				if (iBaseDFLevel > 3)
				{
					iBaseDFLevel = 3;
				}

				int iBaseRGLevel = NpcData.m_iNPC_BASE_RG_LEVEL;

				if (iBaseRGLevel < 0)
				{
					iBaseRGLevel = 0;
				}

				if (iBaseRGLevel > 3)
				{
					iBaseRGLevel = 3;
				}

				switch (NpcData.m_iNPC_NUM)
				{
				case 277:
					{
						gObj[iObjIndex].m_Defense = g_iNpcDefense_CGATE[iBaseDFLevel];
						gObj[iObjIndex].m_btCsNpcDfLevel = iBaseDFLevel;
					}
					break;
				case 283:
					{
						gObj[iObjIndex].m_Defense = g_iNpcDefense_CSTATUE[iBaseDFLevel];
						gObj[iObjIndex].m_btCsNpcDfLevel = iBaseDFLevel;
						gObj[iObjIndex].m_btCsNpcRgLevel = iBaseRGLevel;
					}
					break;
				}

				it->m_btCsNpcExistVal1 = (rand() % 255) + 1;
				gObj[iObjIndex].m_btCsNpcExistVal1 = it->m_btCsNpcExistVal1;

				it->m_btCsNpcExistVal2 = (rand() % 256);//Dig Fix
				gObj[iObjIndex].m_btCsNpcExistVal2 = it->m_btCsNpcExistVal2;

				it->m_btCsNpcExistVal3 = (rand() % 256);
				gObj[iObjIndex].m_btCsNpcExistVal3 = it->m_btCsNpcExistVal3;

				it->m_btCsNpcExistVal4 = (rand() % 256);
				gObj[iObjIndex].m_btCsNpcExistVal4 = it->m_btCsNpcExistVal4;

				if (NpcData.m_iNPC_NUM == 277)
				{
					this->SetGateBlockState(NpcData.m_iNPC_SX, NpcData.m_iNPC_SY, 1);
					gObj[iObjIndex].m_btCsGateOpen = 1;

					int bCreateLever = FALSE;//A0//DiG Fix

					if (NpcData.m_iCS_GATE_LEVER_INDEX == -1)
					{
						bCreateLever = TRUE;//DiG Fix
					}
					else if (this->CheckLeverAlive(NpcData.m_iCS_GATE_LEVER_INDEX) == FALSE)
					{
						bCreateLever = TRUE;//DiG Fix
					}

					if (bCreateLever != 0)
					{
						/*A4*/int iLevelerIndex = this->CreateCsGateLever(NpcData.m_iNPC_SX, NpcData.m_iNPC_SY + 4);//DiG Fix

						if (OBJMAX_RANGE(iLevelerIndex))//DiG Fix
						{
							it->m_iCS_GATE_LEVER_INDEX = iLevelerIndex;//DiG Fix

							/*A8*/int iLinkIndex = this->LinkCsGateLever(iLevelerIndex, iObjIndex);//DiG Fix

							if (iLinkIndex == 0)
							{
								::LogAddC(2, "[CastleSiege] CCastleSiege::CreateDbNPC() ERROR - Failed to Create Gate Lever : GateIndex:%d",
									NpcData.m_iNPC_INDEX);
							}
						}
						else
						{
							it->m_iCS_GATE_LEVER_INDEX = -1;
							::LogAddC(2, "[CastleSiege] CCastleSiege::CreateDbNPC() ERROR - Failed to Create Gate Lever : GateIndex:%d",
								NpcData.m_iNPC_INDEX);
						}
					}
					else
					{
						int iLinkIndex = this->LinkCsGateLever(NpcData.m_iCS_GATE_LEVER_INDEX, iObjIndex);

						if (iLinkIndex == 0)
						{
							::LogAddC(2, "[CastleSiege] CCastleSiege::CreateDbNPC() ERROR - Failed to Create Gate Lever : GateIndex:%d",
								NpcData.m_iNPC_INDEX);
						}
					}
				}
				it->m_iNPC_OBJINDEX = iObjIndex;
				it->m_iNPC_LIVE = PLAYER_LOGGED;
				it->m_bIN_USE = TRUE;

				iRETVAL = 1;

				if (NpcData.m_iNPC_NUM == 277 || NpcData.m_iNPC_NUM == 283)
				{
					LogAdd("[CastleSiege][CreateDBNPC] (Index:%d, Num:%d, DF:%d, RG:%d, MaxHP:%d, HP:%d )",
						NpcData.m_iNPC_INDEX, NpcData.m_iNPC_NUM, NpcData.m_iNPC_DF_LEVEL,
						NpcData.m_iNPC_RG_LEVEL, NpcData.m_iNPC_MAXHP, NpcData.m_iNPC_HP);
				}
				break;
			}
		}

		it++;
	}
	LeaveCriticalSection(&this->m_critNpcData);

	return iRETVAL;
}

BOOL CCastleSiege::DelNPC(int iIndex, int iNpcType, int iMonsterExistVal, int bDbSave) //Identical
{
	if (!OBJMAX_RANGE(iIndex))
	{
		return FALSE;
	}

	BOOL bEXIST = FALSE;
	BOOL bNPC_DB = FALSE;

	_CS_NPC_DATA pTempNpcData;

	EnterCriticalSection(&m_critNpcData);

	auto it = m_vtNpcData.begin();

	while (it != m_vtNpcData.end())
	{
		_CS_NPC_DATA NpcData(*it);
		auto pNpcData = &NpcData;

		if (pNpcData->m_iNPC_NUM == iNpcType && pNpcData->m_iNPC_OBJINDEX == iIndex)
		{
			if (pNpcData->m_iCsNpcExistVal == iMonsterExistVal && pNpcData->m_bIN_USE == TRUE)
			{
				if (pNpcData->m_iNPC_LIVE > 0)
				{
					it->SetBaseValue();

					it->m_iNPC_OBJINDEX = OBJ_EMPTY;
					it->m_iNPC_LIVE = FALSE;

					if (pNpcData->m_iNPC_NUM == 277 || pNpcData->m_iNPC_NUM == 283)
					{
						pNpcData->m_iNPC_HP = pNpcData->m_iNPC_BASE_HP;
						pNpcData->m_iNPC_MAXHP = pNpcData->m_iNPC_BASE_MAXHP;
						pNpcData->m_iNPC_RG_LEVEL = pNpcData->m_iNPC_BASE_RG_LEVEL;
						pNpcData->m_iNPC_DF_LEVEL = pNpcData->m_iNPC_BASE_DF_LEVEL;
					}

					bEXIST = TRUE;
					pTempNpcData = *pNpcData;

					if (pNpcData->m_iNPC_NUM == 277)
					{
						SetGateBlockState(pNpcData->m_iNPC_SX, pNpcData->m_iNPC_SY, 1);

						LogAdd("[CastleSiege][ State:%d ] Delete Castle Gate ( CLS:%d, IDX:%d, X:%d. Y:%d )",
							m_iCastleSiegeState, pNpcData->m_iNPC_NUM, pNpcData->m_iNPC_INDEX, pNpcData->m_iNPC_SX, pNpcData->m_iNPC_SY);
					}

					if (pNpcData->m_iNPC_NUM == 283)
					{
						if (m_iCastleSiegeState == CASTLESIEGE_STATE_STARTSIEGE)
						{
							if (CheckGuardianStatueExist() == FALSE)
							{
								ClearCastleTowerBarrier();
								SetCastleTowerAccessable(TRUE);
							}
							LogAdd("[CastleSiege] Defend Statue is Broken (CLS:%d, IDX:%d, X:%d, Y:%d)",
								pNpcData->m_iNPC_NUM, pNpcData->m_iNPC_INDEX, pNpcData->m_iNPC_SX, pNpcData->m_iNPC_SY);
						}
					}
					break;
				}
			}
		}
		it++;
	}
	LeaveCriticalSection(&m_critNpcData);

	if (bEXIST == TRUE && bDbSave == TRUE && m_iCastleSiegeState != CASTLESIEGE_STATE_STARTSIEGE)
	{
		GS_GDReqNpcRemove(m_iMapSvrGroup, pTempNpcData.m_iNPC_NUM, pTempNpcData.m_iNPC_INDEX);
	}

	return TRUE;
}

BOOL CCastleSiege::RepairDbNPC(int iNpcType, int iNpcIndex, int iNpcHP, int iNpcMaxHP) //Identical (HermeX Fix Applied)
{
	BOOL bEXIST = FALSE;

	EnterCriticalSection(&m_critNpcData);

	auto it = m_vtNpcData.begin();

	while (it != m_vtNpcData.end())
	{
		_CS_NPC_DATA & NpcData = _CS_NPC_DATA(*it);

		if (NpcData.m_iNPC_NUM == iNpcType && NpcData.m_iNPC_INDEX == iNpcIndex && NpcData.m_bIN_USE == 1 && NpcData.m_iNPC_LIVE > 0) //100%
		{
			it->m_iNPC_HP = iNpcHP;
			it->m_iNPC_MAXHP = iNpcMaxHP;

			int iObjIndex = NpcData.m_iNPC_OBJINDEX;

			if (gObjIsConnected(iObjIndex) != FALSE && gObj[iObjIndex].m_btCsNpcType != 0 && gObj[iObjIndex].Class == iNpcType && gObj[iObjIndex].m_iCsNpcExistVal == NpcData.m_iCsNpcExistVal && gObj[iObjIndex].m_iCsNpcExistVal != 0)
			{
				gObj[iObjIndex].Life = gObj[iObjIndex].MaxLife;
				bEXIST = TRUE;
			}
			break; //HermeX Fix
		}
		it++;
	}

	LeaveCriticalSection(&m_critNpcData);

	return bEXIST;
}

int CCastleSiege::PayForUpgradeDbNpc(int iIndex, int iNpcType, int iNpcIndex, int iNpcUpType, int iNpcUpValue, int iNpcUpIndex) //Identical
{
	int iNEED_GEMOFDEFEND = 0;
	int iNEED_MONEY = 0;

	if (CS_CHECK_UPGRADE(iNpcUpIndex) == FALSE)
	{
		LogAddC(2, "[CastleSiege] CCastleSiege::PayForUpgradeDbNpc() ERROR - lpMsg->iNpcUpIndex is Out of Bound : %d", iNpcUpIndex);
		return FALSE;
	}

	_CS_NPC_DATA pNpcData;

	BOOL bIsLive = GetNpcData(iNpcType, iNpcIndex, pNpcData);

	if (bIsLive == FALSE)
	{
		LogAddC(2, "[CastleSiege] CCastleSiege::PayForUpgradeDbNpc() ERROR - bIsLive == FALSE", iNpcUpIndex);
		return FALSE;
	}

	switch (iNpcType)
	{
	case 277:
		{
			switch (iNpcUpType)
			{
			case 1:
				{
					iNEED_GEMOFDEFEND = g_iNpcUpDfLevel_CGATE[iNpcUpIndex][1];
					iNEED_MONEY = g_iNpcUpDfLevel_CGATE[iNpcUpIndex][2];

					if (gObj[iIndex].Money < iNEED_MONEY)
					{
						GCAnsNpcUpgrade(iIndex, 3, iNpcType, iNpcIndex, iNpcUpType, iNpcUpValue);
						return FALSE;
					}
					int iDelResult = DelGemOfDefend(iIndex, iNEED_GEMOFDEFEND);

					if (iDelResult == FALSE)
					{
						GCAnsNpcUpgrade(iIndex, 4, iNpcType, iNpcIndex, iNpcUpType, iNpcUpValue);
						return FALSE;
					}

					gObj[iIndex].Money -= iNEED_MONEY;
				}
				break;
			case 3:
				{
					iNEED_GEMOFDEFEND = g_iNpcUpMaxHP_CGATE[iNpcUpIndex][1];
					iNEED_MONEY = g_iNpcUpMaxHP_CGATE[iNpcUpIndex][2];

					if (gObj[iIndex].Money < iNEED_MONEY)
					{
						GCAnsNpcUpgrade(iIndex, 3, iNpcType, iNpcIndex, iNpcUpType, iNpcUpValue);
						return FALSE;
					}
					int iDelResult = DelGemOfDefend(iIndex, iNEED_GEMOFDEFEND);

					if (iDelResult == FALSE)
					{
						GCAnsNpcUpgrade(iIndex, 4, iNpcType, iNpcIndex, iNpcUpType, iNpcUpValue);
						return FALSE;
					}

					gObj[iIndex].Money -= iNEED_MONEY;
				}
				break;
			default:
				{
					GCAnsNpcUpgrade(iIndex, 5, iNpcType, iNpcIndex, iNpcUpType, iNpcUpValue);
					return FALSE;
				}
				break;
			}
		}
		break;
	case 283:
		{
			switch (iNpcUpType)
			{
			case 1:
				{
					iNEED_GEMOFDEFEND = g_iNpcUpDfLevel_CSTATUE[iNpcUpIndex][1];
					iNEED_MONEY = g_iNpcUpDfLevel_CSTATUE[iNpcUpIndex][2];

					if (gObj[iIndex].Money < iNEED_MONEY)
					{
						GCAnsNpcUpgrade(iIndex, 3, iNpcType, iNpcIndex, iNpcUpType, iNpcUpValue);
						return FALSE;
					}
					int iDelResult = DelGemOfDefend(iIndex, iNEED_GEMOFDEFEND);

					if (iDelResult == FALSE)
					{
						GCAnsNpcUpgrade(iIndex, 4, iNpcType, iNpcIndex, iNpcUpType, iNpcUpValue);
						return FALSE;
					}

					gObj[iIndex].Money -= iNEED_MONEY;
				}
				break;
			case 2:
				{
					iNEED_GEMOFDEFEND = g_iNpcUpRgLevel_CSTATUE[iNpcUpIndex][1];
					iNEED_MONEY = g_iNpcUpRgLevel_CSTATUE[iNpcUpIndex][2];

					if (gObj[iIndex].Money < iNEED_MONEY)
					{
						GCAnsNpcUpgrade(iIndex, 3, iNpcType, iNpcIndex, iNpcUpType, iNpcUpValue);
						return FALSE;
					}
					int iDelResult = DelGemOfDefend(iIndex, iNEED_GEMOFDEFEND);

					if (iDelResult == FALSE)
					{
						GCAnsNpcUpgrade(iIndex, 4, iNpcType, iNpcIndex, iNpcUpType, iNpcUpValue);
						return FALSE;
					}

					gObj[iIndex].Money -= iNEED_MONEY;
				}
				break;
			case 3:
				{
					iNEED_GEMOFDEFEND = g_iNpcUpMaxHP_CSTATUE[iNpcUpIndex][1];
					iNEED_MONEY = g_iNpcUpMaxHP_CSTATUE[iNpcUpIndex][2];

					if (gObj[iIndex].Money < iNEED_MONEY)
					{
						GCAnsNpcUpgrade(iIndex, 3, iNpcType, iNpcIndex, iNpcUpType, iNpcUpValue);
						return FALSE;
					}
					int iDelResult = DelGemOfDefend(iIndex, iNEED_GEMOFDEFEND);

					if (iDelResult == FALSE)
					{
						GCAnsNpcUpgrade(iIndex, 4, iNpcType, iNpcIndex, iNpcUpType, iNpcUpValue);
						return FALSE;
					}

					gObj[iIndex].Money -= iNEED_MONEY;
				}
				break;
			default:
				{
					GCAnsNpcUpgrade(iIndex, 5, iNpcType, iNpcIndex, iNpcUpType, iNpcUpValue);
					return FALSE;
				}
				break;
			}
		}
		break;
	}

	GCMoneySend(iIndex, gObj[iIndex].Money);

	return TRUE;
}

BOOL CCastleSiege::UpgradeDbNPC(int iIndex, int iNpcType, int iNpcIndex, int iNpcUpType, int iNpcUpValue, int iNpcUpIndex)//Identical
{
	if (CS_CHECK_UPGRADE(iNpcUpIndex) == FALSE)
	{
		LogAddC(2, "[CastleSiege] CCastleSiege::UpgradeDbNPC() ERROR - lpMsg->iNpcUpIndex is Out of Bound : %d", iNpcUpIndex);
		return FALSE;
	}

	_CS_NPC_DATA pNpcData;
	BOOL bIsLive;

	bIsLive = GetNpcData(iNpcType, iNpcIndex, pNpcData);

	if (bIsLive == FALSE)
	{
		LogAddC(2, "[CastleSiege] CCastleSiege::UpgradeDbNPC() ERROR - bIsLive == FALSE", iNpcUpIndex);
		return FALSE;
	}

	switch (iNpcType)
	{
	case 277:
		{
			switch (iNpcUpType)
			{
			case 1:
				{
					this->UpgradeDbNPC_DFLEVEL(iNpcType, iNpcIndex, iNpcUpValue);
				}
				break;

			case 3:
				{
					this->UpgradeDbNPC_MAXHP(iNpcType, iNpcIndex, iNpcUpValue);
				}
				break;

			default:
				{
					::GCAnsNpcUpgrade(iIndex, 5, iNpcType, iNpcIndex, iNpcUpType, iNpcUpValue);
					return FALSE;
				}
				break;
			}
		}
		break;

	case 283:
		{
			switch (iNpcUpType)
			{
			case 1:
				{
					this->UpgradeDbNPC_DFLEVEL(iNpcType, iNpcIndex, iNpcUpValue);
				}
				break;

			case 2:
				{
					this->UpgradeDbNPC_RGLEVEL(iNpcType, iNpcIndex, iNpcUpValue);
				}
				break;

			case 3:
				{
					this->UpgradeDbNPC_MAXHP(iNpcType, iNpcIndex, iNpcUpValue);
				}
				break;

			default:
				{
					::GCAnsNpcUpgrade(iIndex, 5, iNpcType, iNpcIndex, iNpcUpType, iNpcUpValue);
					return FALSE;
				}
				break;
			}
		}
		break;
	}

	return TRUE;
}

int CCastleSiege::UpgradeDbNPC_DFLEVEL(int iNpcType, int iNpcIndex, int iNpcDfLevel) //Identical (HermeX Fix Applied)
{
	BOOL bEXIST = FALSE;

	EnterCriticalSection(&m_critNpcData);

	auto it = m_vtNpcData.begin();

	while (it != m_vtNpcData.end())
	{
		_CS_NPC_DATA & NpcData = _CS_NPC_DATA(*it);

		if (NpcData.m_iNPC_NUM == iNpcType && NpcData.m_iNPC_INDEX == iNpcIndex && NpcData.m_bIN_USE == 1 && NpcData.m_iNPC_LIVE > 0)
		{
			int iObjIndex = NpcData.m_iNPC_OBJINDEX;

			if (gObjIsConnected(iObjIndex) && gObj[iObjIndex].m_btCsNpcType != 0 && gObj[iObjIndex].m_iCsNpcExistVal == NpcData.m_iCsNpcExistVal && gObj[iObjIndex].m_iCsNpcExistVal != 0)
			{
				it->m_iNPC_DF_LEVEL = iNpcDfLevel;

				bEXIST = TRUE;

				gObj[iObjIndex].m_Defense = g_iNpcDefense_CGATE[iNpcDfLevel];
				gObj[iObjIndex].m_MagicDefense = g_iNpcDefense_CGATE[iNpcDfLevel];
				gObj[iObjIndex].m_btCsNpcDfLevel = iNpcDfLevel;
			}
			break;
		}
		it++;
	}

	LeaveCriticalSection(&m_critNpcData);

	return bEXIST;
}

int CCastleSiege::UpgradeDbNPC_RGLEVEL(int iNpcType, int iNpcIndex, int iNpcRgLevel) //Identical (HermeX Fix Applied)
{
	BOOL bEXIST = FALSE;

	EnterCriticalSection(&m_critNpcData);

	auto it = m_vtNpcData.begin();

	while (it != m_vtNpcData.end())
	{
		_CS_NPC_DATA & NpcData = _CS_NPC_DATA(*it);

		if (NpcData.m_iNPC_NUM == iNpcType && NpcData.m_iNPC_INDEX == iNpcIndex && NpcData.m_bIN_USE == 1 && NpcData.m_iNPC_LIVE > 0)
		{
			int iObjIndex = NpcData.m_iNPC_OBJINDEX;

			if (gObjIsConnected(iObjIndex) && gObj[iObjIndex].m_btCsNpcType != 0 && gObj[iObjIndex].m_iCsNpcExistVal == NpcData.m_iCsNpcExistVal && gObj[iObjIndex].m_iCsNpcExistVal != 0)
			{
				it->m_iNPC_RG_LEVEL = iNpcRgLevel;
				bEXIST = TRUE;
				gObj[iObjIndex].m_btCsNpcRgLevel = iNpcRgLevel;
			}
			break;
		}
		it++;
	}

	LeaveCriticalSection(&m_critNpcData);

	return bEXIST;
}

int CCastleSiege::UpgradeDbNPC_MAXHP(int iNpcType, int iNpcIndex, int iNpcMaxHP) //Identical (HermeX Fix Applied)
{
	BOOL bEXIST = FALSE;

	EnterCriticalSection(&m_critNpcData);

	auto it = m_vtNpcData.begin();

	while (it != m_vtNpcData.end())
	{
		_CS_NPC_DATA & NpcData = _CS_NPC_DATA(*it);

		if (NpcData.m_iNPC_NUM == iNpcType && NpcData.m_iNPC_INDEX == iNpcIndex && NpcData.m_bIN_USE == 1 && NpcData.m_iNPC_LIVE > 0)
		{
			int iObjIndex = NpcData.m_iNPC_OBJINDEX;

			if (gObjIsConnected(iObjIndex) && gObj[iObjIndex].m_btCsNpcType != 0 && gObj[iObjIndex].m_iCsNpcExistVal == NpcData.m_iCsNpcExistVal && gObj[iObjIndex].m_iCsNpcExistVal != 0)
			{
				it->m_iNPC_MAXHP = iNpcMaxHP;
				it->m_iNPC_HP = iNpcMaxHP;
				bEXIST = TRUE;
				gObj[iObjIndex].Life = iNpcMaxHP;
				gObj[iObjIndex].MaxLife = iNpcMaxHP;
			}
			break; //HermeX Fix
		}
		it++;
	}

	LeaveCriticalSection(&m_critNpcData);

	return bEXIST;
}

void CCastleSiege::StoreDbNpc() //Identical
{
	LogAdd("[CastleSiege] CCastleSiege::StoreDbNpc() - << START >>");

	char cBUFFER[0x1090];

	CSP_REQ_NPCUPDATEDATA * lpMsg = (CSP_REQ_NPCUPDATEDATA *)cBUFFER;
	CSP_NPCUPDATEDATA * lpMsgBody = (CSP_NPCUPDATEDATA *)&cBUFFER[sizeof(CSP_REQ_NPCUPDATEDATA)];

	int iCOUNT = 0;

	EnterCriticalSection(&m_critNpcData);
	auto it = m_vtNpcData.begin();
	int bExist = FALSE;

	while (it != m_vtNpcData.end())
	{
		if (iCOUNT >= 150)
			break;

		_CS_NPC_DATA & pNpcData = _CS_NPC_DATA(*it);

		if (pNpcData.m_bNPC_DBSAVE == TRUE
			&& gObjIsConnected(pNpcData.m_iNPC_OBJINDEX)
			&& gObj[pNpcData.m_iNPC_OBJINDEX].Class == pNpcData.m_iNPC_NUM
			&& gObj[pNpcData.m_iNPC_OBJINDEX].m_iCsNpcExistVal == pNpcData.m_iCsNpcExistVal
			&& gObj[pNpcData.m_iNPC_OBJINDEX].m_iCsNpcExistVal != NULL
			&& gObj[pNpcData.m_iNPC_OBJINDEX].Live == TRUE
			&& gObj[pNpcData.m_iNPC_OBJINDEX].Life > 0)
		{
			lpMsgBody[iCOUNT].iNpcNumber = pNpcData.m_iNPC_NUM;
			lpMsgBody[iCOUNT].iNpcIndex = pNpcData.m_iNPC_INDEX;
			lpMsgBody[iCOUNT].iNpcDfLevel = pNpcData.m_iNPC_DF_LEVEL;
			lpMsgBody[iCOUNT].iNpcRgLevel = pNpcData.m_iNPC_RG_LEVEL;
			lpMsgBody[iCOUNT].iNpcMaxHp = gObj[pNpcData.m_iNPC_OBJINDEX].MaxLife;
			lpMsgBody[iCOUNT].iNpcHp = gObj[pNpcData.m_iNPC_OBJINDEX].Life;
			lpMsgBody[iCOUNT].btNpcX = pNpcData.m_iNPC_SX;
			lpMsgBody[iCOUNT].btNpcY = pNpcData.m_iNPC_SY;
			lpMsgBody[iCOUNT].btNpcDIR = pNpcData.m_iNPC_DIR;

			LogAdd("[CastleSiege] CCastleSiege::StoreDbNpc() NPC INFO (CLS:%d, IDX:%d(%d), MAXHP:%d, HP:%d, DF:%d, RG:%d)",
				pNpcData.m_iNPC_NUM, pNpcData.m_iNPC_INDEX, pNpcData.m_iNPC_OBJINDEX, lpMsgBody[iCOUNT].iNpcMaxHp, lpMsgBody[iCOUNT].iNpcHp, lpMsgBody[iCOUNT].iNpcDfLevel, lpMsgBody[iCOUNT].iNpcRgLevel);
			iCOUNT++;
		}

		it++;
	}

	LeaveCriticalSection(&m_critNpcData);

	if (iCOUNT < 0)
	{
		iCOUNT = 0;
	}

	lpMsg->wMapSvrNum = m_iMapSvrGroup;
	lpMsg->iCount = iCOUNT;
	lpMsg->h.set((PBYTE)lpMsg, 0x89, iCOUNT * sizeof(CSP_NPCUPDATEDATA) + sizeof(CSP_REQ_NPCUPDATEDATA));
	cDBSMng.Send((char *)lpMsg, iCOUNT * sizeof(CSP_NPCUPDATEDATA) + sizeof(CSP_REQ_NPCUPDATEDATA));

	LogAdd("[CastleSiege] CCastleSiege::StoreDbNpc() - << END >>");
}

void CCastleSiege::SendNpcStateList(int iIndex, int iNpcType) //Identical
{
	if (gObjIsConnected(iIndex) == FALSE)
		return;

	char cNPC_LIST[(sizeof(PMSG_NPCDBLIST) * 50) + sizeof(PMSG_ANS_NPCDBLIST)] = { 0 };
	int iNPC_COUNT = 0;

	PMSG_ANS_NPCDBLIST* lpMsgSend = (PMSG_ANS_NPCDBLIST*)&cNPC_LIST[0];
	PMSG_NPCDBLIST* lpMsgSendBody = (PMSG_NPCDBLIST*)&cNPC_LIST[sizeof(PMSG_ANS_NPCDBLIST)];

	EnterCriticalSection(&m_critNpcData);

	auto it = m_vtNpcData.begin();

	while (it != m_vtNpcData.end())
	{
		if (iNPC_COUNT >= 50)
			break;

		_CS_NPC_DATA & NpcData = _CS_NPC_DATA(*it);

		if (NpcData.m_iNPC_NUM == iNpcType && NpcData.m_bIN_USE == TRUE)
		{
			int iLife = 0;
			int iMaxLife = 0;
			BYTE btNpcLive = 0;
			int iObjIndex = NpcData.m_iNPC_OBJINDEX;

			if (gObjIsConnected(iObjIndex))
			{
				if (gObj[iObjIndex].Class == iNpcType && gObj[iObjIndex].Live == 1 && gObj[iObjIndex].Life > 0 && gObj[iObjIndex].m_btCsNpcType != 0 && gObj[iObjIndex].m_iCsNpcExistVal == NpcData.m_iCsNpcExistVal && gObj[iObjIndex].m_iCsNpcExistVal != 0) //HermeX Fix
				{
					iLife = gObj[iObjIndex].Life;
					iMaxLife = gObj[iObjIndex].MaxLife;
					btNpcLive = 1;
				}
				else
				{
					iLife = 0;
					iMaxLife = NpcData.m_iNPC_BASE_MAXHP;
					btNpcLive = 0;
				}
			}
			else
			{
				iLife = 0;
				iMaxLife = NpcData.m_iNPC_BASE_MAXHP;
				btNpcLive = 0;
			}
			lpMsgSendBody[iNPC_COUNT].iNpcNumber = NpcData.m_iNPC_NUM;
			lpMsgSendBody[iNPC_COUNT].iNpcIndex = NpcData.m_iNPC_INDEX;
			lpMsgSendBody[iNPC_COUNT].iNpcDfLevel = NpcData.m_iNPC_DF_LEVEL;
			lpMsgSendBody[iNPC_COUNT].iNpcRgLevel = NpcData.m_iNPC_RG_LEVEL;
			lpMsgSendBody[iNPC_COUNT].iNpcHp = iLife;
			lpMsgSendBody[iNPC_COUNT].iNpcMaxHp = iMaxLife;
			lpMsgSendBody[iNPC_COUNT].btNpcX = NpcData.m_iNPC_SX;
			lpMsgSendBody[iNPC_COUNT].btNpcY = NpcData.m_iNPC_SY;
			lpMsgSendBody[iNPC_COUNT].btNpcLive = btNpcLive;

			iNPC_COUNT++;
		}

		it++;
	}
	LeaveCriticalSection(&m_critNpcData);

	lpMsgSend->btResult = 1;
	lpMsgSend->h.set((LPBYTE)&cNPC_LIST, 0xB3, (sizeof(PMSG_NPCDBLIST) * iNPC_COUNT) + sizeof(PMSG_ANS_NPCDBLIST));
	lpMsgSend->iCount = iNPC_COUNT;

	DataSend(iIndex, (LPBYTE)&cNPC_LIST, (sizeof(PMSG_NPCDBLIST) * iNPC_COUNT) + sizeof(PMSG_ANS_NPCDBLIST));
}

int CCastleSiege::GetNpcData(int iNpcType, int iNpcIndex, _CS_NPC_DATA & pRetNpcData) //Identical
{
	pRetNpcData.Clear();
	BOOL bEXIST = FALSE;

	EnterCriticalSection(&m_critNpcData);

	auto it = m_vtNpcData.begin();

	while (it != m_vtNpcData.end())
	{
		_CS_NPC_DATA & NpcData = _CS_NPC_DATA(*it);

		if (NpcData.m_iNPC_NUM == iNpcType && NpcData.m_iNPC_INDEX == iNpcIndex && NpcData.m_bIN_USE == 1 && NpcData.m_iNPC_LIVE > 0)
		{
			int iObjIndex = NpcData.m_iNPC_OBJINDEX;

			if (gObjIsConnected(iObjIndex) && gObj[iObjIndex].m_btCsNpcType != 0 && gObj[iObjIndex].m_iCsNpcExistVal == NpcData.m_iCsNpcExistVal && gObj[iObjIndex].m_iCsNpcExistVal != 0)
			{
				pRetNpcData = NpcData;
				bEXIST = TRUE;
			}
			break;
		}
		it++;
	}

	LeaveCriticalSection(&m_critNpcData);

	return bEXIST;
}

void CCastleSiege::AdjustDbNpcLevel() //Identical
{
	EnterCriticalSection(&m_critNpcData);

	auto it = m_vtNpcData.begin();

	while (it != m_vtNpcData.end())
	{
		_CS_NPC_DATA & pNpcData = _CS_NPC_DATA(*it);

		if (pNpcData.m_bIN_USE == 1
			&& pNpcData.m_iNPC_LIVE > 0)
		{
			int iNPC_INDEX = pNpcData.m_iNPC_OBJINDEX;

			if (gObjIsConnected(iNPC_INDEX)
				&& gObj[iNPC_INDEX].Class == pNpcData.m_iNPC_NUM
				&& gObj[iNPC_INDEX].m_btCsNpcType != FALSE
				&& gObj[iNPC_INDEX].m_iCsNpcExistVal == pNpcData.m_iCsNpcExistVal
				&& gObj[iNPC_INDEX].m_iCsNpcExistVal != NULL)
			{
				switch (gObj[iNPC_INDEX].Class)
				{
				case 277:
					{
						int iDF_LEVEL = pNpcData.m_iNPC_DF_LEVEL;

						if (iDF_LEVEL < 0)
						{
							iDF_LEVEL = 0;
						}

						if (iDF_LEVEL > CS_MAX_UPGRADE)
						{
							iDF_LEVEL = CS_MAX_UPGRADE;
						}

						gObj[iNPC_INDEX].m_btCsNpcDfLevel = iDF_LEVEL;
						gObj[iNPC_INDEX].m_Defense = g_iNpcDefense_CGATE[iDF_LEVEL];
					}
					break;
				case 283:
					{
						int iDF_LEVEL = pNpcData.m_iNPC_DF_LEVEL;

						if (iDF_LEVEL < 0)
						{
							iDF_LEVEL = 0;
						}

						if (iDF_LEVEL > CS_MAX_UPGRADE)
						{
							iDF_LEVEL = CS_MAX_UPGRADE;
						}

						gObj[iNPC_INDEX].m_btCsNpcDfLevel = iDF_LEVEL;
						gObj[iNPC_INDEX].m_Defense = g_iNpcDefense_CSTATUE[iDF_LEVEL];
						gObj[iNPC_INDEX].m_btCsNpcRgLevel = pNpcData.m_iNPC_RG_LEVEL;
					}
					break;
				}
			}

			break;
		}

		it++;
	}

	LeaveCriticalSection(&m_critNpcData);
}

void CCastleSiege::SendCsGateStateViewPort(int iGateIndex, BYTE btOperate) //Identical
{
	if (gObjIsConnected(iGateIndex) == FALSE)
		return;

	LPOBJ lpObj = &gObj[iGateIndex];

	if (lpObj->VPCount2 < 1)
		return;

	int tObjNum = -1;

	for (int i = 0; i < MAX_VIEWPORT; i++)
	{
		tObjNum = lpObj->VpPlayer2[i].number;

		if (tObjNum >= 0)
		{
			if (gObj[tObjNum].Type == OBJ_USER && gObjIsConnected(tObjNum))
			{
				GCAnsCsGateCurState(tObjNum, iGateIndex, btOperate);
			}
		}
	}
}

void CCastleSiege::CreateAllCsGateLever() //Identical
{
	EnterCriticalSection(&m_critNpcData);

	if (!m_vtNpcData.empty())
	{
		for (auto it = m_vtNpcData.begin(); it != m_vtNpcData.end(); it++)
		{
			_CS_NPC_DATA & pNpcData = _CS_NPC_DATA(*it);

			if (pNpcData.m_iNPC_NUM == 277)
			{
				if (pNpcData.m_iCS_GATE_LEVER_INDEX != -1 && CheckLeverAlive(pNpcData.m_iCS_GATE_LEVER_INDEX) == 1)
				{
					continue;
				}

				int iLeverIndex = CreateCsGateLever(pNpcData.m_iNPC_SX, pNpcData.m_iNPC_SY + 4);

				if (OBJMAX_RANGE(iLeverIndex))
				{
					it->m_iCS_GATE_LEVER_INDEX = iLeverIndex;
				}
				else
				{
					it->m_iCS_GATE_LEVER_INDEX = -1;
					LogAddC(2, "[CastleSiege] CCastleSiege::CreateAllCsGateLever() ERROR - Failed to Create Gate Lever : GateIndex:%d", pNpcData.m_iNPC_INDEX);
				}
			}
		}
	}

	LeaveCriticalSection(&m_critNpcData);
}

int CCastleSiege::CreateCsGateLever(int iX, int iY) //Identical
{
	if (XY_MACRO(iX) == FALSE || XY_MACRO(iY) == FALSE)
	{
		return -1;
	}

	int iNPC_INDEX = gObjAddMonster(MAP_INDEX_CASTLESIEGE);

	if (iNPC_INDEX >= 0)
	{
		gObjSetMonster(iNPC_INDEX, 219);

		gObj[iNPC_INDEX].m_PosNum = -1;
		gObj[iNPC_INDEX].X = iX;
		gObj[iNPC_INDEX].Y = iY;
		gObj[iNPC_INDEX].MapNumber = MAP_INDEX_CASTLESIEGE;
		gObj[iNPC_INDEX].TX = gObj[iNPC_INDEX].X;
		gObj[iNPC_INDEX].TY = gObj[iNPC_INDEX].Y;
		gObj[iNPC_INDEX].m_OldX = gObj[iNPC_INDEX].X;
		gObj[iNPC_INDEX].m_OldY = gObj[iNPC_INDEX].Y;
		gObj[iNPC_INDEX].Dir = 1;
		gObj[iNPC_INDEX].StartX = gObj[iNPC_INDEX].X;
		gObj[iNPC_INDEX].StartY = gObj[iNPC_INDEX].Y;
		gObj[iNPC_INDEX].DieRegen = 0;
		gObj[iNPC_INDEX].MaxRegenTime = 0;
		gObj[iNPC_INDEX].Life = 10000.0f;
		gObj[iNPC_INDEX].MaxLife = 10000.0f;
		gObj[iNPC_INDEX].m_btCsNpcType = 2;
		gObj[iNPC_INDEX].m_iCsGateLeverLinkIndex = -1;

		return iNPC_INDEX;
	}

	return -1;
}

int CCastleSiege::LinkCsGateLever(int iLeverIndex, int iGateIndex) //Identical
{
	if (!gObjIsConnected(iLeverIndex) || gObj[iLeverIndex].Class != 219)
		return false;
	if (!gObjIsConnected(iGateIndex) || gObj[iGateIndex].Class != 277)
		return false;

	gObj[iLeverIndex].m_iCsGateLeverLinkIndex = iGateIndex;
	gObj[iGateIndex].m_iCsGateLeverLinkIndex = iLeverIndex;

	return true;
}

int CCastleSiege::CheckLeverAlive(int iLeverIndex) //Identical
{
	if (gObjIsConnected(iLeverIndex) == FALSE || gObj[iLeverIndex].Class != 219)
	{
		return false;
	}
	return true;
}

void CCastleSiege::CheckCsDbNpcAlive() //Identical (HermeX Fix Applied)
{
	if (m_iCastleSiegeState != CASTLESIEGE_STATE_STARTSIEGE)
		return;

	EnterCriticalSection(&m_critNpcData);

	if (m_vtNpcData.empty() == false)
	{
		for (auto it = m_vtNpcData.begin(); it != m_vtNpcData.end(); it++)
		{
			_CS_NPC_DATA & NpcData = _CS_NPC_DATA(*it);

			if ((NpcData.m_iNPC_NUM == 277 || NpcData.m_iNPC_NUM == 283) && NpcData.m_iNPC_OBJINDEX != OBJ_EMPTY)
			{
				if (!gObjIsConnected(NpcData.m_iNPC_OBJINDEX) || gObj[NpcData.m_iNPC_OBJINDEX].m_iCsNpcExistVal != NpcData.m_iCsNpcExistVal || gObj[NpcData.m_iNPC_OBJINDEX].m_iCsNpcExistVal == 0 || (gObj[NpcData.m_iNPC_OBJINDEX].Class != 277 && gObj[NpcData.m_iNPC_OBJINDEX].Class != 283) || gObj[NpcData.m_iNPC_OBJINDEX].Live == FALSE) //HermeX Fix
				{
					NpcData.m_iNPC_HP = NpcData.m_iNPC_BASE_HP;//DiG Fix
					NpcData.m_iNPC_MAXHP = NpcData.m_iNPC_BASE_MAXHP;//DiG Fix
					NpcData.m_iNPC_RG_LEVEL = NpcData.m_iNPC_BASE_RG_LEVEL;//DiG Fix
					NpcData.m_iNPC_DF_LEVEL = NpcData.m_iNPC_BASE_DF_LEVEL;//DiG Fix

					switch (NpcData.m_iNPC_NUM)
					{
					case 277:
						SetGateBlockState(NpcData.m_iNPC_SX, NpcData.m_iNPC_SY, 1);
						LogAdd("[CastleSiege] Castle Gate is Broken (CLS:%d, IDX:%d, X:%d, Y:%d)",
							NpcData.m_iNPC_NUM, NpcData.m_iNPC_INDEX, NpcData.m_iNPC_SX, NpcData.m_iNPC_SY);
						break;
					case 283:
						if (CheckGuardianStatueExist() == FALSE)
						{
							ClearCastleTowerBarrier();
							SetCastleTowerAccessable(TRUE);
						}
						LogAdd("[CastleSiege] Defend Statue is Broken (CLS:%d, IDX:%d, X:%d, Y:%d)",
							NpcData.m_iNPC_NUM, NpcData.m_iNPC_INDEX, NpcData.m_iNPC_SX, NpcData.m_iNPC_SY);
						break;
					}
					it->m_iNPC_OBJINDEX = OBJ_EMPTY;
				}
			}
		}
	}
	LeaveCriticalSection(&m_critNpcData);
}

BOOL CCastleSiege::CheckCsGateAlive(int iGateIndex) //Identical
{
	if (!gObjIsConnected(iGateIndex) || gObj[iGateIndex].Class != 277)
	{
		return FALSE;
	}

	return TRUE;
}

int CCastleSiege::DelGemOfDefend(int iIndex, int iNeedGemOfDefend) //Identical
{
	if (gObjIsConnected(iIndex) == FALSE)
	{
		return FALSE;
	}

	if (iNeedGemOfDefend <= 0)
	{
		return FALSE;
	}

	int iGemOfDefendCount = 0;

	for (int x = 0; x < INVENTORY_SIZE; x++)
	{
		if (gObj[iIndex].pInventory[x].IsItem() == TRUE)
		{
			if (gObj[iIndex].pInventory[x].m_Type == ITEMGET(14, 31))
			{
				iGemOfDefendCount++;
			}
		}
	}

	if (iGemOfDefendCount < iNeedGemOfDefend)
	{
		return FALSE;
	}

	int iGemOfDefendDeletCount = 0;

	for (int x = 0; x < INVENTORY_SIZE; x++)
	{
		if (gObj[iIndex].pInventory[x].IsItem() == TRUE)
		{
			if (gObj[iIndex].pInventory[x].m_Type == ITEMGET(14, 31))
			{
				LogAdd("[CastleSiege] [%s][%s] Deleting Gem of Defend (GUILD:%s) - Serial:%d",
					gObj[iIndex].AccountID, gObj[iIndex].Name, gObj[iIndex].GuildName, gObj[iIndex].pInventory[x].m_Number);

				gObjInventoryItemSet(iIndex, x, 0xff);
				gObjInventoryDeleteItem(iIndex, x);
				GCInventoryItemDeleteSend(iIndex, x, 1);

				iGemOfDefendDeletCount++;

				if (iGemOfDefendDeletCount >= iNeedGemOfDefend)
				{
					break;
				}
			}
		}
	}

	return TRUE;
}

void CCastleSiege::SetTaxRate(int iTaxType, int iTaxRate) //Identical
{
	int iMaxTaxRate = 0;

	switch (iTaxType)
	{
	case 1:
		iMaxTaxRate = 3;
		break;
	case 2:
		iMaxTaxRate = 3;
		break;
	case 3:
		iMaxTaxRate = 300000;
		break;
	}

	if (iTaxRate >= 0 && iTaxRate > iMaxTaxRate)
	{
		return;
	}

	switch (iTaxType)
	{
	case 1:
		this->m_iTaxRateChaos = iTaxRate;
		break;
	case 2:
		this->m_iTaxRateStore = iTaxRate;
		break;
	case 3:
		this->m_iTaxHuntZone = iTaxRate;
		break;
	}

	LogAdd("[CastleSiege] Tax Rate Setted - Type:%d, Rate:%d", iTaxType, iTaxRate);
}

BOOL CCastleSiege::CheckCastleHasMoney(__int64 i64CastleMoney) //Identical
{
	if (this->m_i64CastleMoney >= i64CastleMoney)
	{
		return TRUE;
	}
	return FALSE;
}

void CCastleSiege::SetCastleMoney(__int64 i64CastleMoney) //Identical
{
	this->m_i64CastleMoney = i64CastleMoney;
}

void CCastleSiege::ResetCastleTaxInfo() //Identical
{
	this->m_i64CastleMoney = 0;
	this->m_iTaxRateChaos = 0;
	this->m_iTaxRateStore = 0;
	this->m_iTaxHuntZone = 0;
}

void CCastleSiege::SendCastleStateSync() //Identical
{
	GS_GDReqCastleStateSync(this->m_iMapSvrGroup, this->m_iCastleSiegeState, this->m_iTaxRateChaos,
		this->m_iTaxRateStore, this->m_iTaxHuntZone, this->m_szCastleOwnerGuild);
}

BOOL CCastleSiege::CheckGuildOwnCastle(char* lpszGuildName) //Identical
{
	if (lpszGuildName == NULL)
	{
		return FALSE;
	}

	if (strcmp(this->m_szCastleOwnerGuild, "") == 0)
	{
		return FALSE;
	}

	if (strcmp(this->m_szCastleOwnerGuild, lpszGuildName) == 0)
	{
		return TRUE;
	}

	return FALSE;
}

void CCastleSiege::ResetCastleCycle() //Identical
{
	this->m_bCsBasicGuildInfoLoadOK = FALSE;
	this->m_bCsTotalGuildInfoLoadOK = FALSE;

	EnterCriticalSection(&this->m_critCsBasicGuildInfo);
	this->m_mapCsBasicGuildInfo.clear();
	LeaveCriticalSection(&this->m_critCsBasicGuildInfo);

	EnterCriticalSection(&this->m_critCsTotalGuildInfo);
	this->m_mapCsTotalGuildInfo.clear();
	LeaveCriticalSection(&this->m_critCsTotalGuildInfo);

	this->m_bCastleTowerAccessable = FALSE;
	this->m_bRegCrownAvailable = FALSE;
	this->m_btIsSiegeGuildList = 0;
	this->m_btIsSiegeEnded = 0;
}

void CCastleSiege::SetGateBlockState(int iX, int iY, int iGateState) //Identical
{
	if (XY_MACRO(iX) == FALSE || XY_MACRO(iY) == FALSE)
		return;

	switch (iGateState)
	{
	case 0:
		{
			for (int i = iX - 2; i <= iX + 3; i++)
			{
				for (int j = iY; j <= iY + 2; j++)
				{
					MapC[MAP_INDEX_CASTLESIEGE].m_attrbuf[j * 256 + i] |= 16;
				}
			}
		}
		break;
	case 1:
		{
			for (int i = iX - 2; i <= iX + 3; i++)
			{
				for (int j = iY; j <= iY + 2; j++)
				{
					MapC[MAP_INDEX_CASTLESIEGE].m_attrbuf[j * 256 + i] &= ~16;
				}
			}
		}
		break;
	}
}

void CCastleSiege::CheckBuildCsGuildInfo() //Identical
{
	m_bCsBasicGuildInfoLoadOK = FALSE;
	m_bCsTotalGuildInfoLoadOK = FALSE;

	EnterCriticalSection(&m_critCsBasicGuildInfo);
	m_mapCsBasicGuildInfo.clear();
	LeaveCriticalSection(&m_critCsBasicGuildInfo);

	EnterCriticalSection(&m_critCsTotalGuildInfo);
	m_mapCsTotalGuildInfo.clear();
	LeaveCriticalSection(&m_critCsTotalGuildInfo);

	if (m_btIsSiegeGuildList == TRUE)
	{
		GS_GDReqCsLoadTotalGuildInfo(m_iMapSvrGroup);
	}
	else
	{
		GS_GDReqCalcRegGuildList(m_iMapSvrGroup);
	}
}

void CCastleSiege::SetCalcRegGuildList(CSP_CALCREGGUILDLIST* lpMsg, int iCOUNT) //Identical
{
	if (lpMsg == NULL)
	{
		return;
	}

	if (iCOUNT > 100)
	{
		iCOUNT = 100;
	}

	if (iCOUNT <= 0)
	{
		return;
	}

	m_bCsBasicGuildInfoLoadOK = FALSE;
	m_bCsTotalGuildInfoLoadOK = FALSE;

	std::vector<_CS_REG_GUILD_DATA> vtRegGuildScore;

	for (int iGCNT = 0; iGCNT < iCOUNT; iGCNT++)
	{
		_CS_REG_GUILD_DATA GuildData;

		char szGuildName[16] = { 0 };

		memcpy(szGuildName, lpMsg[iGCNT].szGuildName, MAX_GUILD_LEN);

		GuildData.m_bIN_USE = TRUE;
		GuildData.m_strGuildName = szGuildName;
		GuildData.m_iRegMarkCount = lpMsg[iGCNT].iRegMarkCount;
		GuildData.m_iGuildMasterLevel = lpMsg[iGCNT].iGuildMasterLevel;
		GuildData.m_iGuildMemberCount = lpMsg[iGCNT].iGuildMemberCount;
		GuildData.m_iSeqNum = 0x100000 - lpMsg[iGCNT].iSeqNum;

		int dwHighScore = ((lpMsg[iGCNT].iRegMarkCount * 5) + lpMsg[iGCNT].iGuildMemberCount + (lpMsg[iGCNT].iGuildMasterLevel / 4));

#define MACRO3(value) (((__int64) value & 0xFFFFFFFF ))

		GuildData.m_i64TotolScore = ((__int64)(DWORD)MACRO3(lpMsg[iGCNT].iSeqNum)) | (((__int64)(DWORD)MACRO3(dwHighScore)) << 32);

		vtRegGuildScore.push_back(GuildData);

		LogAdd("[CastleSiege][REG Mark Count] - [%s][%d]", szGuildName, lpMsg[iGCNT].iRegMarkCount);
	}

	if (vtRegGuildScore.empty())
	{
		return;
	}

	sort(vtRegGuildScore.begin(), vtRegGuildScore.end(), CCastleSiege::RegGuildScoreCompFunc);

	int iGUILD_COUNT = vtRegGuildScore.size();

	if (iGUILD_COUNT > 3)
	{
		iGUILD_COUNT = 3;
	}

	EnterCriticalSection(&m_critCsBasicGuildInfo);

	m_mapCsBasicGuildInfo.clear();

	for (int iGCNT = 0; iGCNT < iGUILD_COUNT; iGCNT++)
	{
		_CS_TOTAL_GUILD_DATA GuildData;

		GuildData.m_bIN_USE = TRUE;
		GuildData.m_iCsGuildID = (iGCNT + 2);
		GuildData.m_bGuildInvolved = TRUE;

		m_mapCsBasicGuildInfo.insert(std::pair<string, _CS_TOTAL_GUILD_DATA>(vtRegGuildScore[iGCNT].m_strGuildName, GuildData)); //HermeX Fix
	}

	if (m_btIsCastleOccupied == TRUE)
	{
		if (strcmp(m_szCastleOwnerGuild, "") != 0)
		{
			_CS_TOTAL_GUILD_DATA GuildData;

			GuildData.m_bIN_USE = TRUE;
			GuildData.m_iCsGuildID = 1; //HermeX Fix @27/01/2010
			GuildData.m_bGuildInvolved = TRUE; //HermeX Fix @27/01/2010

			m_mapCsBasicGuildInfo.insert(std::pair<string, _CS_TOTAL_GUILD_DATA>(m_szCastleOwnerGuild, GuildData)); //HermeX Fix
		}
	}

	LeaveCriticalSection(&m_critCsBasicGuildInfo);

	char cBUFFER[2080];

	CSP_REQ_CSGUILDUNIONINFO* lpMsgSend = (CSP_REQ_CSGUILDUNIONINFO*)cBUFFER;
	CSP_CSGUILDUNIONINFO* lpMsgSendBody = (CSP_CSGUILDUNIONINFO*)&cBUFFER[sizeof(CSP_REQ_CSGUILDUNIONINFO)];

	lpMsgSend->wMapSvrNum = m_iMapSvrGroup;
	lpMsgSend->iCount = 0;

	EnterCriticalSection(&m_critCsTotalGuildInfo);

	m_mapCsTotalGuildInfo.clear();

	std::map<string, _CS_TOTAL_GUILD_DATA>::iterator it = this->m_mapCsBasicGuildInfo.begin(); //HermeX Fix

	for (; it != this->m_mapCsBasicGuildInfo.end(); it++) //HermeX Fix
	{
		if (lpMsgSend->iCount > 150)
			break;

		m_mapCsTotalGuildInfo.insert(std::pair<string, _CS_TOTAL_GUILD_DATA>(it->first, it->second)); //HermeX Fix

		string GuildName = it->first;

		memcpy(&lpMsgSendBody[lpMsgSend->iCount].szGuildName, &GuildName[0], 8);
		lpMsgSendBody[lpMsgSend->iCount].iCsGuildID = it->second.m_iCsGuildID;

		lpMsgSend->iCount++;
	}

	LeaveCriticalSection(&m_critCsTotalGuildInfo);

	m_bCsBasicGuildInfoLoadOK = TRUE;

	lpMsgSend->h.set((LPBYTE)lpMsgSend, 0x86, (lpMsgSend->iCount * sizeof(CSP_CSGUILDUNIONINFO)) + sizeof(CSP_REQ_CSGUILDUNIONINFO));
	cDBSMng.Send((PCHAR)lpMsgSend, (lpMsgSend->iCount * sizeof(CSP_CSGUILDUNIONINFO)) + sizeof(CSP_REQ_CSGUILDUNIONINFO));
}

BYTE CCastleSiege::RegGuildScoreCompFunc(_CS_REG_GUILD_DATA & A, _CS_REG_GUILD_DATA & B) //Identical
{
	if (A.m_i64TotolScore < B.m_i64TotolScore)
	{
		return false;
	}
	return true;
}

void CCastleSiege::MakeCsTotalGuildInfo(CSP_CSGUILDUNIONINFO* lpMsg, int iCOUNT) //Identical
{
	if (lpMsg == NULL)
		return;

	if (m_bCsBasicGuildInfoLoadOK == FALSE)
	{
		LogAddC(2, "[CastleSiege] CCastleSiege::MakeCsTotalGuildInfo() ERROR - m_bCsBasicGuildInfoLoadOK == FALSE");
		return;
	}
	if (iCOUNT <= 0)
	{
		LogAddC(2, "[CastleSiege] CCastleSiege::MakeCsTotalGuildInfo() ERROR - iCOUNT <= 0 : %d", iCOUNT);
		return;
	}

	EnterCriticalSection(&m_critCsTotalGuildInfo);

	for (int iGCNT = 0; iGCNT < iCOUNT; iGCNT++)
	{
		char szGuildName[16] = { 0 };

		memcpy(szGuildName, lpMsg[iGCNT].szGuildName, MAX_GUILD_LEN);

		std::map<string, _CS_TOTAL_GUILD_DATA>::iterator it = this->m_mapCsTotalGuildInfo.find(szGuildName); //HermeX Fix

		if (it != m_mapCsTotalGuildInfo.end()) //DiG Fix @22/02/2010
			continue;

		_CS_TOTAL_GUILD_DATA GuildData;

		GuildData.m_bIN_USE = TRUE;
		GuildData.m_iCsGuildID = lpMsg[iGCNT].iCsGuildID;
		GuildData.m_bGuildInvolved = FALSE;

		m_mapCsTotalGuildInfo.insert(std::pair<string, _CS_TOTAL_GUILD_DATA>(szGuildName, GuildData)); //HermeX Fix
	}

	LeaveCriticalSection(&m_critCsTotalGuildInfo);

	m_bCsTotalGuildInfoLoadOK = TRUE;
	SaveCsTotalGuildInfo();
	SetAllUserCsJoinSide();
}

void CCastleSiege::SaveCsTotalGuildInfo() //Identical
{
	if (m_bCsTotalGuildInfoLoadOK == FALSE)
	{
		LogAddC(2, "[CastleSiege] CCastleSiege::SaveCsTotalGuildInfo() ERROR - m_bCsTotalGuildInfoLoadOK == FALSE");
		return;
	}
	char cBUFFER[2684];

	CSP_REQ_CSSAVETOTALGUILDINFO* lpMsgSend = (CSP_REQ_CSSAVETOTALGUILDINFO*)&cBUFFER[0];
	CSP_CSSAVETOTALGUILDINFO* lpMsgSendBody = (CSP_CSSAVETOTALGUILDINFO*)&cBUFFER[sizeof(CSP_REQ_CSSAVETOTALGUILDINFO)];

	lpMsgSend->wMapSvrNum = m_iMapSvrGroup;
	lpMsgSend->iCount = 0;

	EnterCriticalSection(&m_critCsTotalGuildInfo);

	std::map<string, _CS_TOTAL_GUILD_DATA>::iterator it = this->m_mapCsTotalGuildInfo.begin(); //HermeX Fix

	for (; it != this->m_mapCsTotalGuildInfo.end(); it++)
	{
		if (lpMsgSend->iCount > 150)
		{
			break;
		}

		string szGuildName = it->first;

		memcpy(&lpMsgSendBody[lpMsgSend->iCount].szGuildName, &szGuildName[0], MAX_GUILD_LEN);

		lpMsgSendBody[lpMsgSend->iCount].iCsGuildID = it->second.m_iCsGuildID;
		lpMsgSendBody[lpMsgSend->iCount].iGuildInvolved = it->second.m_bGuildInvolved;

		lpMsgSend->iCount++;
	}

	LeaveCriticalSection(&m_critCsTotalGuildInfo);

	lpMsgSend->h.set((LPBYTE)lpMsgSend, 0x87, (lpMsgSend->iCount * sizeof(CSP_CSSAVETOTALGUILDINFO)) + sizeof(CSP_REQ_CSSAVETOTALGUILDINFO)); //HermeX Fix @27/01/2010
	cDBSMng.Send((PCHAR)lpMsgSend, (lpMsgSend->iCount * sizeof(CSP_CSSAVETOTALGUILDINFO)) + sizeof(CSP_REQ_CSSAVETOTALGUILDINFO)); //HermeX Fix @27/01/2010

	EnterCriticalSection(&m_critCsTotalGuildInfo);

	std::map<string, _CS_TOTAL_GUILD_DATA>::iterator it2 = this->m_mapCsTotalGuildInfo.begin(); //HermeX Fix

	for (int iSize = m_mapCsTotalGuildInfo.size(); it2 != m_mapCsTotalGuildInfo.end(); it2++)
	{
		string szGuildName = it2->first;

		_CS_TOTAL_GUILD_DATA GuildData = it2->second;

		LogAdd("[CastleSiege] Siege Guild List Save - GNAME:%s, CSGUID:%d, INVOLVED:%d",
			(char*)&szGuildName[0], GuildData.m_iCsGuildID, GuildData.m_bGuildInvolved);
	}

	LeaveCriticalSection(&m_critCsTotalGuildInfo);
}

void CCastleSiege::SetCsTotalGuildInfo(CSP_CSLOADTOTALGUILDINFO* lpMsg, int iCOUNT) //Identical
{
	if (lpMsg == NULL)
		return;

	if (iCOUNT <= 0)
	{
		LogAddC(2, "[CastleSiege] CCastleSiege::SetCsTotalGuildInfo() ERROR - iCOUNT <= 0 : %d",
			iCOUNT);

		return;
	}

	for (int iGCNT = 0; iGCNT < iCOUNT; iGCNT++)
	{
		char szGuildName[16] = { 0 };

		memcpy(szGuildName, lpMsg[iGCNT].szGuildName, MAX_GUILD_LEN);

		_CS_TOTAL_GUILD_DATA GuildData;

		GuildData.m_bIN_USE = TRUE;
		GuildData.m_iCsGuildID = lpMsg[iGCNT].iCsGuildID;
		GuildData.m_bGuildInvolved = lpMsg[iGCNT].iGuildInvolved;

		EnterCriticalSection(&m_critCsTotalGuildInfo);
		m_mapCsTotalGuildInfo.insert(std::pair<string, _CS_TOTAL_GUILD_DATA>(szGuildName, GuildData)); //HermeX Fix
		LeaveCriticalSection(&m_critCsTotalGuildInfo);

		if (lpMsg[iGCNT].iGuildInvolved == TRUE)
		{
			EnterCriticalSection(&m_critCsBasicGuildInfo);
			m_mapCsBasicGuildInfo.insert(std::pair<string, _CS_TOTAL_GUILD_DATA>(szGuildName, GuildData)); //HermeX Fix
			LeaveCriticalSection(&m_critCsBasicGuildInfo);
		}
	}

	m_bCsBasicGuildInfoLoadOK = TRUE;
	m_bCsTotalGuildInfoLoadOK = TRUE;
	SetAllUserCsJoinSide();

	EnterCriticalSection(&m_critCsTotalGuildInfo);

	std::map<string, _CS_TOTAL_GUILD_DATA>::iterator it2 = this->m_mapCsTotalGuildInfo.begin(); //HermeX Fix

	int iSize = m_mapCsTotalGuildInfo.size();

	for (; it2 != m_mapCsTotalGuildInfo.end(); it2++)
	{
		string GuildName = it2->first;

		_CS_TOTAL_GUILD_DATA GuildData = _CS_TOTAL_GUILD_DATA(it2->second);

		LogAdd("[CastleSiege] Siege Guild List Load - GNAME:%s, CSGUID:%d, INVOLVED:%d",
			&GuildName[0], GuildData.m_iCsGuildID, GuildData.m_bGuildInvolved);
	}

	LeaveCriticalSection(&m_critCsTotalGuildInfo);
}

int CCastleSiege::GetCsJoinSide(char* lpszGuildName, BYTE * btCsJoinSide, BYTE * bCsGuildInvolved) //Identical
{
	*btCsJoinSide = 0;
	*bCsGuildInvolved = 0;

	if (lpszGuildName == NULL)
	{
		return FALSE;
	}

	if (m_bDoRun == FALSE)
	{
		return FALSE;
	}

	if (m_iCastleSiegeState < CASTLESIEGE_STATE_NOTIFY || CASTLESIEGE_STATE_STARTSIEGE < m_iCastleSiegeState) //HermeX Fix
	{
		return FALSE;
	}

	if (m_bCsTotalGuildInfoLoadOK == FALSE)
	{
		return FALSE;
	}

	BOOL bRETVAL = FALSE;

	EnterCriticalSection(&m_critCsTotalGuildInfo);

	std::map<string, _CS_TOTAL_GUILD_DATA>::iterator it = this->m_mapCsTotalGuildInfo.find(lpszGuildName); //HermeX Fix

	if (it != m_mapCsTotalGuildInfo.end())
	{
		*btCsJoinSide = it->second.m_iCsGuildID;
		*bCsGuildInvolved = (it->second.m_bGuildInvolved != 0);

		bRETVAL = TRUE;
	}

	LeaveCriticalSection(&m_critCsTotalGuildInfo);

	return bRETVAL;
}

void CCastleSiege::SetAllUserCsJoinSide() //Identical
{
	if (m_bCsTotalGuildInfoLoadOK == FALSE)
		return;

	EnterCriticalSection(&m_critCsTotalGuildInfo);

	for (int iUSER = OBJ_STARTUSERINDEX; iUSER < OBJMAX; iUSER++)
	{
		if (gObjIsConnected(iUSER) == FALSE)
			continue;

		gObj[iUSER].m_ViewSkillState &= 0xFFF3FFFF;
		gObj[iUSER].m_ViewSkillState &= 0xFFBFFFFF; //HermeX Fix #CHECK
		gObj[iUSER].m_ViewSkillState &= 0xFF7FFFFF; //HermeX Fix

		char szGuildName[16] = { 0 };

		memcpy(szGuildName, gObj[iUSER].GuildName, MAX_GUILD_LEN);

		std::map<string, _CS_TOTAL_GUILD_DATA>::iterator it = this->m_mapCsTotalGuildInfo.find(szGuildName); //HermeX Fix

		if (it != m_mapCsTotalGuildInfo.end())
		{
			gObj[iUSER].m_btCsJoinSide = it->second.m_iCsGuildID;
			gObj[iUSER].m_bCsGuildInvolved = (it->second.m_bGuildInvolved != 0);
		}

		NotifySelfCsJoinSide(iUSER);

		gObj[iUSER].m_iAccumulatedCrownAccessTime = 0; //HermeX Fix
	}

	LeaveCriticalSection(&m_critCsTotalGuildInfo);
}

void CCastleSiege::ResetAllUserCsJoinSide() //Identical
{
	EnterCriticalSection(&m_critCsTotalGuildInfo);

	for (int iUSER = OBJ_STARTUSERINDEX; iUSER < OBJMAX; iUSER++)
	{
		if (::gObjIsConnected(iUSER) == FALSE)
			continue;

		gObj[iUSER].m_btCsJoinSide = 0;
		gObj[iUSER].m_bCsGuildInvolved = 0;
		gObj[iUSER].m_btLifeStoneCount = 0;

		NotifySelfCsJoinSide(iUSER);

		gObj[iUSER].m_iAccumulatedCrownAccessTime = 0; //HermeX Fix
	}

	LeaveCriticalSection(&m_critCsTotalGuildInfo);
}

void CCastleSiege::NotifySelfCsJoinSide(int iIndex) //Identical
{
	if (gObjIsConnected(iIndex) == FALSE)
		return;
	int iState = 0;
	int iViewState = 0;

	unsigned char btCsJoinSide = gObj[iIndex].m_btCsJoinSide;

	PMSG_ANS_NOTIFYCSJOINSIDE pMsg;

	if (btCsJoinSide < 0)
	{
		btCsJoinSide = 0;
	}

	if (btCsJoinSide > 2)
	{
		btCsJoinSide = 2;
	}

	switch (btCsJoinSide)
	{
	case 1:
		iState = 1;
		iViewState = 0x40000;
		break;
	case 2:
		iState = 1;
		iViewState = 0x80000;
		break;
	default:
		iState = 0;
		iViewState = 0xC0000;
	}

	pMsg.h.set((PBYTE)&pMsg, 0xB2, 0x19, sizeof(pMsg));

	if (btCsJoinSide == 2) //HermeX Fix
	{
		pMsg.btCsJoinSide = gObj[iIndex].m_btCsJoinSide;
	}
	else
	{
		pMsg.btCsJoinSide = btCsJoinSide;
	}

	DataSend(iIndex, (PBYTE)&pMsg, pMsg.h.size);
}

int CCastleSiege::OperateGate(int iObjIndex, int iMonsterExistVal, int bOpenType) //Identical (HermeX Fix Applied)
{
	if (gObjIsConnected(iObjIndex) == FALSE)
		return FALSE;

	BOOL bRETVAL = FALSE;

	EnterCriticalSection(&m_critNpcData);

	auto it = m_vtNpcData.begin();

	while (it != m_vtNpcData.end())
	{
		_CS_NPC_DATA & NpcData = _CS_NPC_DATA(*it);

		if (NpcData.m_iNPC_NUM == 277 && NpcData.m_iNPC_OBJINDEX == iObjIndex && NpcData.m_bIN_USE == TRUE && NpcData.m_iNPC_LIVE == 2)
		{
			int iObjNumber = NpcData.m_iNPC_OBJINDEX;

			if (gObj[iObjNumber].m_btCsNpcType != 0 && iMonsterExistVal == NpcData.m_iCsNpcExistVal)
			{
				SetGateBlockState(NpcData.m_iNPC_SX, NpcData.m_iNPC_SY, bOpenType);
				gObj[iObjNumber].m_btCsGateOpen = bOpenType;

				bRETVAL = TRUE;
			}
			break; //HermeX Fix
		}
		it++;
	}

	LeaveCriticalSection(&m_critNpcData);

	return bRETVAL;
}

int CCastleSiege::OperateGate(int iNpcIndex, int bOpenType) //Identical
{
	BOOL bRETVAL = FALSE;

	EnterCriticalSection(&m_critNpcData);

	auto it = m_vtNpcData.begin();

	while (it != m_vtNpcData.end())
	{
		_CS_NPC_DATA & NpcData = _CS_NPC_DATA(*it);

		if (NpcData.m_iNPC_NUM == 277 && NpcData.m_iNPC_INDEX == iNpcIndex && NpcData.m_bIN_USE == TRUE && NpcData.m_iNPC_LIVE == 2)
		{
			int iObjNumber = NpcData.m_iNPC_OBJINDEX;

			if (gObjIsConnected(iObjNumber) &&
				gObj[iObjNumber].m_btCsNpcType != 0 &&
				gObj[iObjNumber].m_iCsNpcExistVal == NpcData.m_iCsNpcExistVal &&
				gObj[iObjNumber].m_iCsNpcExistVal != 0)
			{
				SetGateBlockState(NpcData.m_iNPC_SX, NpcData.m_iNPC_SY, bOpenType);
				gObj[iObjNumber].m_btCsGateOpen = bOpenType;
				bRETVAL = TRUE;
			}
			break;
		}
		it++;
	}

	LeaveCriticalSection(&m_critNpcData);

	return bRETVAL;
}

int CCastleSiege::CheckAttackGuildExist() //Identical
{
	int iRETVAL = FALSE;

	EnterCriticalSection(&m_critCsTotalGuildInfo);
	if (!m_mapCsTotalGuildInfo.empty())
	{
		iRETVAL = TRUE;
	}
	LeaveCriticalSection(&m_critCsTotalGuildInfo);

	return iRETVAL;
}

BOOL CCastleSiege::CheckCastleOwnerMember(int iIndex) //Identical
{
	if (gObjIsConnected(iIndex) == FALSE)
	{
		return FALSE;
	}

	if (strcmp(this->m_szCastleOwnerGuild, "") == 0)
	{
		return FALSE;
	}

	if (strcmp(gObj[iIndex].GuildName, "") == 0)
	{
		return FALSE;
	}

	if (strcmp(gObj[iIndex].GuildName, this->m_szCastleOwnerGuild) != 0)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCastleSiege::CheckCastleOwnerUnionMember(int iIndex) //Identical
{
	_GUILD_INFO_STRUCT* lpGuildInfo;
	TUnionInfo * pUnionInfo;

	if (::gObjIsConnected(iIndex) == FALSE)
	{
		return FALSE;
	}

	if (strcmp(this->m_szCastleOwnerGuild, "") == 0)
	{
		return FALSE;
	}

	if (strcmp(gObj[iIndex].GuildName, "") == 0)
	{
		return FALSE;
	}

	lpGuildInfo = gObj[iIndex].lpGuild;

	if (lpGuildInfo == NULL)
	{
		return FALSE;
	}

	pUnionInfo = UnionManager.SearchUnion(lpGuildInfo->iGuildUnion);

	if (pUnionInfo == NULL)
	{
		return FALSE;
	}

	if (strcmp(pUnionInfo->m_szMasterGuild, this->m_szCastleOwnerGuild) == 0)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CCastleSiege::CheckGuardianStatueExist() //Identical
{
	for (int iIDX = 0; iIDX < OBJ_MAXMONSTER; iIDX++)
	{
		if (gObj[iIDX].Class == 283)
		{
			if (gObj[iIDX].Connected > PLAYER_LOGGED && gObj[iIDX].Live == 1)
			{
				if (gObj[iIDX].MapNumber == MAP_INDEX_CASTLESIEGE)
				{
					return TRUE;
				}
			}
		}
	}

	return FALSE;
}

void CCastleSiege::ChangeWinnerGuild(int iCsJoinSide) //Identical
{
	char szGuildTo[16] = { 0 };
	char szGuildFrom[16] = { 0 };

	EnterCriticalSection(&this->m_critCsTotalGuildInfo);

	std::map<string, _CS_TOTAL_GUILD_DATA>::iterator it = this->m_mapCsTotalGuildInfo.begin(); //HermeX Fix

	for (; it != m_mapCsTotalGuildInfo.end(); it++)
	{
		if (it->second.m_iCsGuildID == iCsJoinSide)
		{
			it->second.m_iCsGuildID = 1;

			if (it->second.m_bGuildInvolved == TRUE)
			{
				memcpy(&szGuildTo, &it->first[0], MAX_GUILD_LEN);
			}
		}
		else if (it->second.m_iCsGuildID == 1)
		{
			it->second.m_iCsGuildID = iCsJoinSide;

			if (it->second.m_bGuildInvolved == TRUE)
			{
				memcpy(&szGuildFrom, &it->first[0], MAX_GUILD_LEN);
			}
		}
	}

	for (int iUSER = OBJ_STARTUSERINDEX; iUSER < OBJMAX; iUSER++)
	{
		if (!gObjIsConnected(iUSER))
		{
			continue;
		}

		gObj[iUSER].m_ViewSkillState &= 0xFFF3FFFF;
		gObj[iUSER].m_ViewSkillState &= 0xFFBFFFFF; //HermeX Fix
		gObj[iUSER].m_ViewSkillState &= 0xFF7FFFFF; //HermeX Fix

		char szNewGuild[16] = { 0 };

		memcpy(&szNewGuild, gObj[iUSER].GuildName, MAX_GUILD_LEN);

		std::map<string, _CS_TOTAL_GUILD_DATA>::iterator it = this->m_mapCsTotalGuildInfo.find(szNewGuild); //HermeX Fix

		if (it != this->m_mapCsTotalGuildInfo.end())
		{
			gObj[iUSER].m_btCsJoinSide = it->second.m_iCsGuildID;
			gObj[iUSER].m_bCsGuildInvolved = (it->second.m_bGuildInvolved != 0);
		}
		gObj[iUSER].m_iAccumulatedCrownAccessTime = 0; //HermeX Fix
	}

	LeaveCriticalSection(&this->m_critCsTotalGuildInfo);

	LogAdd("[CastleSiege] Castle Winner Guild Change From '%s' To '%s'", szGuildFrom, szGuildTo);
}

BOOL CCastleSiege::CheckMiddleWinnerGuild() //Identical
{
	if (this->m_dwCrownAccessTime == 0)
	{
		return FALSE;
	}

	if ((gObjIsConnected(this->m_iCastleCrownAccessUser) == FALSE) ||
		(gObjIsConnected(this->m_iCastleSwitchAccessUser1) == FALSE) ||
		(gObjIsConnected(this->m_iCastleSwitchAccessUser2) == FALSE))
	{
		return FALSE;
	}

	if ((strcmp(gObj[this->m_iCastleCrownAccessUser].GuildName, "") == 0) ||
		(strcmp(gObj[this->m_iCastleSwitchAccessUser1].GuildName, "") == 0) ||
		(strcmp(gObj[this->m_iCastleSwitchAccessUser2].GuildName, "") == 0))
	{
		return FALSE;
	}

	if ((gObj[this->m_iCastleCrownAccessUser].m_btCsJoinSide >= 2) &&
		(gObj[this->m_iCastleSwitchAccessUser1].m_btCsJoinSide >= 2) &&
		(gObj[this->m_iCastleSwitchAccessUser2].m_btCsJoinSide >= 2))
	{
		if (gObj[this->m_iCastleCrownAccessUser].m_bCsGuildInvolved == 1)
		{
			if ((gObj[this->m_iCastleCrownAccessUser].m_btCsJoinSide == gObj[this->m_iCastleSwitchAccessUser1].m_btCsJoinSide) &&
				(gObj[this->m_iCastleCrownAccessUser].m_btCsJoinSide == gObj[this->m_iCastleSwitchAccessUser2].m_btCsJoinSide))
			{
				if (((GetTickCount() - this->m_dwCrownAccessTime) + gObj[this->m_iCastleCrownAccessUser].m_iAccumulatedCrownAccessTime) >= 30000) //DiG Fix
				{
					LogAdd("[CastleSiege] Castle Winner Has been Changed (GUILD:%s)",
						gObj[this->m_iCastleCrownAccessUser].GuildName);

					GCAnsCsAccessCrownState(this->m_iCastleCrownAccessUser, 1); //HermeX Fix
					this->NotifyCrownState(2);

					memset(&this->m_szMiddleWinnerGuild, 0, sizeof(this->m_szMiddleWinnerGuild));
					memcpy(&this->m_szMiddleWinnerGuild, gObj[this->m_iCastleCrownAccessUser].GuildName, 8);

					this->ClearNonDbNPC_MidWin();
					this->ChangeWinnerGuild(gObj[this->m_iCastleCrownAccessUser].m_btCsJoinSide);
					this->NotifyAllUserCsProgState(1, gObj[this->m_iCastleCrownAccessUser].GuildName);
					this->ResetCrownAccessTickCount();
					this->ResetCrownUserIndex();
					this->SetCrownAccessUserX(0);
					this->SetCrownAccessUserY(0);
					this->ResetCrownSwitchUserIndex(217);
					this->ResetCrownSwitchUserIndex(218);
					this->m_bRegCrownAvailable = FALSE;
					this->ReSpawnEnemyUser(FALSE);

					GCAnsCsLeftTimeAlarm((this->m_iCS_REMAIN_MSEC / 1000) / 3600, ((this->m_iCS_REMAIN_MSEC / 1000) % 3600) / 60);

					this->m_dwCS_LEFTTIME_TICK_COUNT = GetTickCount();

					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

int CCastleSiege::CheckCastleSiegeResult() //Identical
{
	char szMsg[0x100] = { 0 };
	int bRETVAL = FALSE;

	if (m_btIsCastleOccupied == TRUE && strcmp(m_szCastleOwnerGuild, "") != FALSE)
	{
		if (strcmp(m_szMiddleWinnerGuild, "") == FALSE || strcmp(m_szMiddleWinnerGuild, m_szCastleOwnerGuild) == FALSE)
		{
			m_btIsCastleOccupied = TRUE;
			wsprintf(szMsg, lMsg.Get(MSGGET(6, 197)), m_szCastleOwnerGuild);
			bRETVAL = FALSE;
		}
		else
		{
			m_btIsCastleOccupied = TRUE;
			memset(m_szCastleOwnerGuild, 0x00, sizeof(m_szCastleOwnerGuild));
			memcpy(m_szCastleOwnerGuild, m_szMiddleWinnerGuild, 0x08);
			wsprintf(szMsg, lMsg.Get(MSGGET(6, 198)), m_szCastleOwnerGuild);
			bRETVAL = TRUE;
		}
	}
	else
	{
		if (strcmp(m_szMiddleWinnerGuild, "") == FALSE)
		{
			m_btIsCastleOccupied = FALSE;
			wsprintf(szMsg, lMsg.Get(MSGGET(6, 199)));
			bRETVAL = FALSE;
		}
		else
		{
			m_btIsCastleOccupied = TRUE;
			memset(m_szCastleOwnerGuild, 0x00, sizeof(m_szCastleOwnerGuild));
			memcpy(m_szCastleOwnerGuild, m_szMiddleWinnerGuild, 0x08);
			wsprintf(szMsg, lMsg.Get(MSGGET(6, 198)), m_szCastleOwnerGuild);
			bRETVAL = TRUE;
		}
	}

	m_btIsSiegeEnded = TRUE;

	LogAdd("[CastleSiege] Castle Final Winner Guild : %s", (strcmp(m_szCastleOwnerGuild, "") == FALSE) ? "NONE" : m_szCastleOwnerGuild);
	SendMapServerGroupMsg(szMsg);

	return bRETVAL;
}

BOOL CCastleSiege::CheckUnionGuildMaster(int iIndex) //Identical
{
	_GUILD_INFO_STRUCT* lpGuildInfo;

	if (gObjIsConnected(iIndex) == FALSE)
	{
		return FALSE;
	}

	lpGuildInfo = gObj[iIndex].lpGuild;

	if (lpGuildInfo == NULL)
	{
		return FALSE;
	}

	if (gObj[iIndex].GuildStatus == GUILD_MASTER)
	{
		if ((lpGuildInfo->Number == lpGuildInfo->iGuildUnion) ||
			(lpGuildInfo->iGuildUnion == 0))
		{
			return TRUE;
		}
	}

	return FALSE;
}

void CCastleSiege::SetCrownSwitchUserIndex(int iMonsterClass, int iIndex) //Identical
{
	switch (iMonsterClass)
	{
	case 217:
		this->m_iCastleSwitchAccessUser1 = iIndex;
		break;
	case 218:
		this->m_iCastleSwitchAccessUser2 = iIndex;
		break;
	}
}

int CCastleSiege::GetCrownSwitchUserIndex(int iMonsterClass) //Identical
{
	int iUserIndex = OBJ_EMPTY;

	switch (iMonsterClass)
	{
	case 217:
		iUserIndex = this->m_iCastleSwitchAccessUser1;
		break;
	case 218:
		iUserIndex = this->m_iCastleSwitchAccessUser2;
		break;
	}
	return iUserIndex;
}

void CCastleSiege::ResetCrownSwitchUserIndex(int iMonsterClass) //Identical
{
	switch (iMonsterClass)
	{
	case 217:
		this->m_iCastleSwitchAccessUser1 = OBJ_EMPTY;
		break;
	case 218:
		this->m_iCastleSwitchAccessUser2 = OBJ_EMPTY;
		break;
	}
}

void CCastleSiege::SetCrownAccessTickCount()
{
	this->m_dwCrownAccessTime = GetTickCount();
}

void CCastleSiege::ResetCrownAccessTickCount()
{
	this->m_dwCrownAccessTime = 0;
}

int CCastleSiege::CheckOverlapCsMarks(int iIndex) //Identical
{
	for (int x = INVETORY_WEAR_SIZE; x < MAIN_INVENTORY_SIZE; x++)
	{
		if (gObj[iIndex].pInventory[x].IsItem() == TRUE)
		{
			if ((gObj[iIndex].pInventory[x].m_Type == ITEMGET(14, 21)) && (gObj[iIndex].pInventory[x].m_Level == 3))
			{
				int dur = gObj[iIndex].pInventory[x].m_Durability;

				if (ITEM_DUR_RANGE(dur))
				{
					return x;
				}
			}
		}
	}
	return -1;
}

int CCastleSiege::GetCsAttkGuildList(PMSG_CSATTKGUILDLIST* lpMsgBody, int & iCount) //Identical
{
	iCount = 0;

	if (lpMsgBody == NULL) return 0;

	if ((this->m_iCastleSiegeState != CASTLESIEGE_STATE_NOTIFY) &&
		(this->m_iCastleSiegeState != CASTLESIEGE_STATE_READYSIEGE)) //HermeX Fix
		return 2;

	if ((this->m_bCsBasicGuildInfoLoadOK == FALSE) ||
		(this->m_bCsTotalGuildInfoLoadOK == FALSE))
		return 3;

	EnterCriticalSection(&this->m_critCsTotalGuildInfo);

	std::map<string, _CS_TOTAL_GUILD_DATA>::iterator it = this->m_mapCsTotalGuildInfo.begin(); //HermeX Fix

	for (; it != this->m_mapCsTotalGuildInfo.end(); it++) //HermeX Fix
	{
		lpMsgBody[iCount].btCsJoinSide = it->second.m_iCsGuildID;
		lpMsgBody[iCount].btGuildInvolved = it->second.m_bGuildInvolved;

		memset(&lpMsgBody[iCount].szGuildName, 0, sizeof(lpMsgBody[iCount].szGuildName));
		memcpy(&lpMsgBody[iCount].szGuildName, &it->first[0], sizeof(lpMsgBody[iCount].szGuildName));

		iCount++;
	}

	LeaveCriticalSection(&this->m_critCsTotalGuildInfo);

	return 1;
}

BOOL CCastleSiege::CheckTeleportMagicAxisY(int iStartY, int iTargetX, int iTargetY) //Identical
{
	for (int iSTEP = 0; iSTEP < 3; iSTEP++)
	{
		if ((g_iCastleWallStepAxisY[iSTEP] >= iStartY) && (g_iCastleWallStepAxisY[iSTEP] <= iTargetY) && (iTargetX < 144)) //HermeX Fix
		{
			return FALSE;
		}
	}
	return TRUE;
}

void CCastleSiege::NotifyCsSelfLeftTime(int iIndex) //Identical
{
	GCAnsSelfCsLeftTimeAlarm(iIndex, (this->m_iCS_REMAIN_MSEC / 1000) / 3600, ((this->m_iCS_REMAIN_MSEC / 1000) % 3600) / 60);
}

void CCastleSiege::CheckReviveNonDbNPC() //Identical
{
	EnterCriticalSection(&m_critNpcData);

	auto it = m_vtNpcData.begin();

	while (it != m_vtNpcData.end())
	{
		_CS_NPC_DATA & pNpcData = _CS_NPC_DATA(*it);

		if (pNpcData.m_bNPC_DBSAVE == 0)
		{
			int iNPC_INDEX = gObjAddMonster(MAP_INDEX_CASTLESIEGE);

			if (iNPC_INDEX >= 0)
			{
				gObjSetMonster(iNPC_INDEX, pNpcData.m_iNPC_NUM);

				gObj[iNPC_INDEX].m_PosNum = -1;
				gObj[iNPC_INDEX].X = pNpcData.m_iNPC_SX;
				gObj[iNPC_INDEX].Y = pNpcData.m_iNPC_SY;
				gObj[iNPC_INDEX].MapNumber = MAP_INDEX_CASTLESIEGE;
				gObj[iNPC_INDEX].TX = gObj[iNPC_INDEX].X;
				gObj[iNPC_INDEX].TY = gObj[iNPC_INDEX].Y;
				gObj[iNPC_INDEX].m_OldX = gObj[iNPC_INDEX].X;
				gObj[iNPC_INDEX].m_OldY = gObj[iNPC_INDEX].Y;
				gObj[iNPC_INDEX].Dir = pNpcData.m_iNPC_DIR;
				gObj[iNPC_INDEX].StartX = gObj[iNPC_INDEX].X;
				gObj[iNPC_INDEX].StartY = gObj[iNPC_INDEX].Y;
				gObj[iNPC_INDEX].DieRegen = 0;
				gObj[iNPC_INDEX].MaxRegenTime = 0;
				gObj[iNPC_INDEX].Life = pNpcData.m_iNPC_HP;
				gObj[iNPC_INDEX].MaxLife = pNpcData.m_iNPC_MAXHP;

				switch (pNpcData.m_iNPC_NUM)
				{
				case 215:
					gObj[iNPC_INDEX].m_btCsNpcType = 2;
					break;
				case 221:
					gObj[iNPC_INDEX].m_btCsNpcType = 3;
					break;
				case 222:
					gObj[iNPC_INDEX].m_btCsNpcType = 2;
					break;
				case 288:
					gObj[iNPC_INDEX].m_btCsNpcType = 2;
					break;
				default:
					gObj[iNPC_INDEX].m_btCsNpcType = 2;
					break;
				}

				it->m_bIN_USE = TRUE;
			}
		}

		it++;
	}

	LeaveCriticalSection(&m_critNpcData);
}

void CCastleSiege::CheckReviveGuardianStatue() //Identical
{
	EnterCriticalSection(&m_critNpcData);

	auto it = m_vtNpcData.begin();

	while (it != m_vtNpcData.end())
	{
		_CS_NPC_DATA & pNpcData = _CS_NPC_DATA(*it);

		if (pNpcData.m_iNPC_NUM == 283
			&& pNpcData.m_iNPC_LIVE == FALSE
			)
		{
			int iNPC_INDEX = gObjAddMonster(MAP_INDEX_CASTLESIEGE);

			if (iNPC_INDEX >= 0)
			{
				gObjSetMonster(iNPC_INDEX, pNpcData.m_iNPC_NUM);

				gObj[iNPC_INDEX].m_PosNum = -1;
				gObj[iNPC_INDEX].X = pNpcData.m_iNPC_SX;
				gObj[iNPC_INDEX].Y = pNpcData.m_iNPC_SY;
				gObj[iNPC_INDEX].MapNumber = MAP_INDEX_CASTLESIEGE;
				gObj[iNPC_INDEX].TX = gObj[iNPC_INDEX].X;
				gObj[iNPC_INDEX].TY = gObj[iNPC_INDEX].Y;
				gObj[iNPC_INDEX].m_OldX = gObj[iNPC_INDEX].X;
				gObj[iNPC_INDEX].m_OldY = gObj[iNPC_INDEX].Y;
				gObj[iNPC_INDEX].Dir = pNpcData.m_iNPC_DIR;
				gObj[iNPC_INDEX].StartX = gObj[iNPC_INDEX].X;
				gObj[iNPC_INDEX].StartY = gObj[iNPC_INDEX].Y;
				gObj[iNPC_INDEX].DieRegen = 0;
				gObj[iNPC_INDEX].MaxRegenTime = 0;
				gObj[iNPC_INDEX].Life = pNpcData.m_iNPC_HP;
				gObj[iNPC_INDEX].MaxLife = pNpcData.m_iNPC_MAXHP;
				gObj[iNPC_INDEX].m_btCsNpcType = 1;

				int iNPC_DF_LEVEL = pNpcData.m_iNPC_BASE_DF_LEVEL;

				if (iNPC_DF_LEVEL < 0)
				{
					iNPC_DF_LEVEL = 0;
				}

				if (iNPC_DF_LEVEL > CS_MAX_UPGRADE)
				{
					iNPC_DF_LEVEL = CS_MAX_UPGRADE;
				}

				int iNPC_RG_LEVEL = pNpcData.m_iNPC_BASE_RG_LEVEL;

				if (iNPC_RG_LEVEL < 0)
				{
					iNPC_RG_LEVEL = 0;
				}

				if (iNPC_RG_LEVEL > CS_MAX_UPGRADE)
				{
					iNPC_RG_LEVEL = CS_MAX_UPGRADE;
				}

				gObj[iNPC_INDEX].m_Defense = g_iNpcDefense_CSTATUE[iNPC_DF_LEVEL];
				gObj[iNPC_INDEX].m_btCsNpcDfLevel = iNPC_DF_LEVEL;
				gObj[iNPC_INDEX].m_btCsNpcRgLevel = iNPC_RG_LEVEL;

				it->m_btCsNpcExistVal1 = rand() % 255 + 1;
				gObj[iNPC_INDEX].m_btCsNpcExistVal1 = it->m_btCsNpcExistVal1;

				it->m_btCsNpcExistVal2 = rand() % 256;
				gObj[iNPC_INDEX].m_btCsNpcExistVal2 = it->m_btCsNpcExistVal2;

				it->m_btCsNpcExistVal3 = rand() % 256;
				gObj[iNPC_INDEX].m_btCsNpcExistVal3 = it->m_btCsNpcExistVal3;

				it->m_btCsNpcExistVal4 = rand() % 256;
				gObj[iNPC_INDEX].m_btCsNpcExistVal4 = it->m_btCsNpcExistVal4;

				it->m_iNPC_OBJINDEX = iNPC_INDEX;
				it->m_iNPC_LIVE = 2;
				it->m_bIN_USE = TRUE;
			}
		}
		it++;
	}

	LeaveCriticalSection(&m_critNpcData);
}

void CCastleSiege::ReSpawnAllUser() //Identical
{
	int iTX, iTY;
	BYTE btMapAttr;

	for (int iUSER = OBJ_STARTUSERINDEX; iUSER < OBJMAX; iUSER++)
	{
		if (gObjIsConnected(iUSER) == FALSE)
			continue;

		if (gObj[iUSER].MapNumber != MAP_INDEX_CASTLESIEGE)
			continue;

		BYTE btJoinSide = gObj[iUSER].m_btCsJoinSide;

		if (btJoinSide < 0)
		{
			btJoinSide = 0;
		}

		if (btJoinSide > 2)
		{
			btJoinSide = 2;
		}

		BOOL bMoveOK = FALSE;

		switch (btJoinSide)
		{
		case 1:
			{
				for (int iCNT = 0; iCNT < 100; iCNT++)
				{
					iTX = (rand() % (g_iCsUserReSpawnArea[1][2] - g_iCsUserReSpawnArea[1][0])) + g_iCsUserReSpawnArea[1][0];
					iTY = (rand() % (g_iCsUserReSpawnArea[1][3] - g_iCsUserReSpawnArea[1][1])) + g_iCsUserReSpawnArea[1][1];

					btMapAttr = MapC[MAP_INDEX_CASTLESIEGE].m_attrbuf[iTY * 256 + iTX];

					if ((btMapAttr & 4) != 4)
					{
						bMoveOK = TRUE;
						break;
					}
				}
			}
			break;
		case 2:
			{
				for (int iCNT = 0; iCNT < 100; iCNT++)
				{
					iTX = (rand() % (g_iCsUserReSpawnArea[2][2] - g_iCsUserReSpawnArea[2][0])) + g_iCsUserReSpawnArea[2][0];
					iTY = (rand() % (g_iCsUserReSpawnArea[2][3] - g_iCsUserReSpawnArea[2][1])) + g_iCsUserReSpawnArea[2][1];

					btMapAttr = MapC[MAP_INDEX_CASTLESIEGE].m_attrbuf[iTY * 256 + iTX];

					if ((btMapAttr & 4) != 4)
					{
						bMoveOK = TRUE;
						break;
					}
				}
			}
			break;
		default:
			{
				for (int iCNT = 0; iCNT < 100; iCNT++)
				{
					iTX = (rand() % (g_iCsUserReSpawnArea[0][2] - g_iCsUserReSpawnArea[0][0])) + g_iCsUserReSpawnArea[0][0];
					iTY = (rand() % (g_iCsUserReSpawnArea[0][3] - g_iCsUserReSpawnArea[0][1])) + g_iCsUserReSpawnArea[0][1];

					btMapAttr = MapC[MAP_INDEX_CASTLESIEGE].m_attrbuf[iTY * 256 + iTX];

					if ((btMapAttr & 4) != 4)
					{
						bMoveOK = TRUE;
						break;
					}
				}
			}
			break;
		}

		if (bMoveOK)
		{
			gObj[iUSER].m_State = 32;
			gObj[iUSER].X = iTX;
			gObj[iUSER].Y = iTY;
			gObj[iUSER].TX = iTX;
			gObj[iUSER].TX = iTY;
			gObj[iUSER].MapNumber = MAP_INDEX_CASTLESIEGE;
			gObj[iUSER].PathCount = 0;
			gObj[iUSER].Teleport = 0;

			gObjClearViewport(&gObj[iUSER]);
			GCTeleportSend(&gObj[iUSER], 0xFF, MAP_INDEX_CASTLESIEGE, gObj[iUSER].X, gObj[iUSER].Y, gObj[iUSER].Dir);

			if (gObj[iUSER].m_Change >= 0)
			{
				gObjViewportListProtocolCreate(&gObj[iUSER]);
			}
			gObj[iUSER].RegenMapNumber = MAP_INDEX_CASTLESIEGE;
			gObj[iUSER].RegenMapX = iTX;
			gObj[iUSER].RegenMapY = iTY;
			gObj[iUSER].RegenOk = TRUE;
		}
	}
}

void CCastleSiege::ReSpawnEnemyUser(int bRefreshOwnerUser) //Identical
{
	int iTX;
	int iTY;
	unsigned char btMapAttr;

	for (int iUSER = OBJ_STARTUSERINDEX; iUSER < OBJMAX; iUSER++)
	{
		if (gObjIsConnected(iUSER) == FALSE)
			continue;

		if (gObj[iUSER].MapNumber != MAP_INDEX_CASTLESIEGE)
			continue;

		unsigned char btCsJoinSide = gObj[iUSER].m_btCsJoinSide;

		if (btCsJoinSide < 0)
		{
			btCsJoinSide = 0;
		}

		if (btCsJoinSide > 2)
		{
			btCsJoinSide = 2;
		}

		int bMoveOK = FALSE;

		switch (btCsJoinSide)
		{
		case 1:
			if (bRefreshOwnerUser != FALSE)
			{
				gObj[iUSER].RegenMapNumber = gObj[iUSER].MapNumber;
				gObj[iUSER].RegenMapX = gObj[iUSER].X;
				gObj[iUSER].RegenMapY = gObj[iUSER].Y;

				gObjClearViewport(&gObj[iUSER]);

				GCTeleportSend(&gObj[iUSER], 0xFF, gObj[iUSER].MapNumber, gObj[iUSER].X, gObj[iUSER].Y, gObj[iUSER].Dir);

				if (gObj[iUSER].m_Change >= 0)
				{
					gObjViewportListProtocolCreate(&gObj[iUSER]);
				}

				gObj[iUSER].RegenOk = TRUE;
			}
			bMoveOK = FALSE;
			break;
		case 2:
			{
				for (int iCNT = 0; iCNT < 100; iCNT++)
				{
					iTX = (rand() % (g_iCsUserReSpawnArea[2][2] - g_iCsUserReSpawnArea[2][0])) + g_iCsUserReSpawnArea[2][0];
					iTY = (rand() % (g_iCsUserReSpawnArea[2][3] - g_iCsUserReSpawnArea[2][1])) + g_iCsUserReSpawnArea[2][1];

					btMapAttr = MapC[MAP_INDEX_CASTLESIEGE].m_attrbuf[iTY * 256 + iTX];

					if ((btMapAttr & 4) != 4)
					{
						bMoveOK = TRUE;
						break;
					}
				}
			}
			break;
		case 0:
			{
				for (int iCNT = 0; iCNT < 100; iCNT++)
				{
					iTX = (rand() % (g_iCsUserReSpawnArea[0][2] - g_iCsUserReSpawnArea[0][0])) + g_iCsUserReSpawnArea[0][0];
					iTY = (rand() % (g_iCsUserReSpawnArea[0][3] - g_iCsUserReSpawnArea[0][1])) + g_iCsUserReSpawnArea[0][1];

					btMapAttr = MapC[MAP_INDEX_CASTLESIEGE].m_attrbuf[iTY * 256 + iTX];

					if ((btMapAttr & 4) != 4)
					{
						bMoveOK = TRUE;
						break;
					}
				}
			}
			break;
		}

		if (bMoveOK != FALSE)
		{
			gObj[iUSER].m_State = 32;
			gObj[iUSER].X = iTX;
			gObj[iUSER].Y = iTY;
			gObj[iUSER].TX = iTX;
			gObj[iUSER].TX = iTY;
			gObj[iUSER].MapNumber = MAP_INDEX_CASTLESIEGE;
			gObj[iUSER].PathCount = 0;
			gObj[iUSER].Teleport = 0;

			gObjClearViewport(&gObj[iUSER]);
			GCTeleportSend(&gObj[iUSER], 0xFF, MAP_INDEX_CASTLESIEGE, gObj[iUSER].X, gObj[iUSER].Y, gObj[iUSER].Dir);

			if (gObj[iUSER].m_Change >= 0)
			{
				gObjViewportListProtocolCreate(&gObj[iUSER]);
			}

			gObj[iUSER].RegenMapNumber = MAP_INDEX_CASTLESIEGE;
			gObj[iUSER].RegenMapX = iTX;
			gObj[iUSER].RegenMapY = iTY;
			gObj[iUSER].RegenOk = TRUE;
		}

		NotifySelfCsJoinSide(iUSER);
		gObj[iUSER].m_iAccumulatedCrownAccessTime = 0; //HermeX Fix
	}
}

void CCastleSiege::NotifyAllUserCsStartState(BYTE btStartState) //Identical
{
	PMSG_ANS_NOTIFYCSSTART pMsg;

	pMsg.h.set((PBYTE)&pMsg, 0xB2, 0x17, sizeof(pMsg));
	pMsg.btStartState = btStartState;

	for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; i++)
	{
		if (gObj[i].Connected == PLAYER_PLAYING && gObj[i].Type == OBJ_USER)
		{
			DataSend(i, (PBYTE)&pMsg, pMsg.h.size);
		}
	}
}

void CCastleSiege::NotifyAllUserCsProgState(BYTE btProgState, char* lpszGuildName) //Identical
{
	PMSG_ANS_NOTIFYCSPROGRESS pMsg;

	pMsg.h.set((LPBYTE)&pMsg, 0xB2, 0x18, sizeof(pMsg));

	pMsg.btCastleSiegeState = btProgState;

	memset(&pMsg.szGuildName, 0, sizeof(pMsg.szGuildName));
	memcpy(&pMsg.szGuildName, lpszGuildName, sizeof(pMsg.szGuildName));

	for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; i++)
	{
		if ((gObj[i].Connected == PLAYER_PLAYING) && (gObj[i].Type == OBJ_USER))
		{
			if (gObj[i].MapNumber == MAP_INDEX_CASTLESIEGE)
			{
				DataSend(i, (LPBYTE)&pMsg, pMsg.h.size);
			}
		}
	}
}

void CCastleSiege::ClearCastleTowerBarrier() //Identical
{
	for (int iIDX = 0; iIDX < OBJ_MAXMONSTER; iIDX++)
	{
		if (::gObjIsConnected(iIDX) == FALSE)
			continue;

		if (gObj[iIDX].Class == 215)
			gObjDel(iIDX);
	}
}

void CCastleSiege::SetAllCastleGateState(int bOpenType) //Identical
{
	EnterCriticalSection(&m_critNpcData);

	auto it = m_vtNpcData.begin();
	int bExist = FALSE;

	while (it != m_vtNpcData.end())
	{
		_CS_NPC_DATA & pNpcData = _CS_NPC_DATA(*it);

		if (pNpcData.m_iNPC_NUM == 277
			&& gObjIsConnected(pNpcData.m_iNPC_OBJINDEX)
			&& gObj[pNpcData.m_iNPC_OBJINDEX].Class == 277)
		{
			switch (bOpenType)
			{
			case 0:
				SetGateBlockState(pNpcData.m_iNPC_SX, pNpcData.m_iNPC_SY, 0);
				gObj[pNpcData.m_iNPC_OBJINDEX].m_btCsGateOpen = 0;
				break;
			case 1:
				SetGateBlockState(pNpcData.m_iNPC_SX, pNpcData.m_iNPC_SY, 1);
				gObj[pNpcData.m_iNPC_OBJINDEX].m_btCsGateOpen = 1;
				break;
			}
		}

		it++;
	}

	LeaveCriticalSection(&m_critNpcData);
}

void CCastleSiege::AddMiniMapDataReqUser(int iIndex) //Identical
{
	EnterCriticalSection(&this->m_critCsMiniMap);

	if (std::find(this->m_vtMiniMapReqUser.begin(), this->m_vtMiniMapReqUser.end(), iIndex) == this->m_vtMiniMapReqUser.end())
	{
		this->m_vtMiniMapReqUser.push_back(iIndex);
	}

	LeaveCriticalSection(&this->m_critCsMiniMap);
}

void CCastleSiege::DelMiniMapDataReqUser(int iIndex) //Identical
{
	EnterCriticalSection(&this->m_critCsMiniMap);

	auto it = std::find(this->m_vtMiniMapReqUser.begin(), this->m_vtMiniMapReqUser.end(), iIndex);

	if (it != this->m_vtMiniMapReqUser.end())
	{
		this->m_vtMiniMapReqUser.erase(it);
	}

	LeaveCriticalSection(&this->m_critCsMiniMap);
}

void CCastleSiege::OperateMiniMapWork()	//Identical (HermeX & DiG Fix Applied)
{
	if (this->m_bCsBasicGuildInfoLoadOK == FALSE)
		return;

	std::map<int, _CS_MINIMAP_DATA> mapMiniMapData;
	BYTE cBUFFER1[2264] = { 0 };

	PMSG_ANS_SENDMINIMAPDATA* lpMsgSend1 = (PMSG_ANS_SENDMINIMAPDATA*)cBUFFER1;
	PMSG_SENDMINIMAPDATA* lpMsgSendBody1 = (PMSG_SENDMINIMAPDATA*)&cBUFFER1[sizeof(PMSG_ANS_SENDMINIMAPDATA)];

	BYTE cBUFFER2[714] = { 0 };

	PMSG_ANS_SENDNPCMINIMAPDATA* lpMsgSend2 = (PMSG_ANS_SENDNPCMINIMAPDATA*)cBUFFER2;

	PMSG_SENDNPCMINIMAPDATA* lpMsgSendBody2 = (PMSG_SENDNPCMINIMAPDATA*)&cBUFFER2[sizeof(PMSG_ANS_SENDNPCMINIMAPDATA)];

	EnterCriticalSection(&m_critCsBasicGuildInfo);

	for (auto it = this->m_mapCsBasicGuildInfo.begin(); it != this->m_mapCsBasicGuildInfo.end(); it++) //HermeX Fix
	{
		_CS_TOTAL_GUILD_DATA* GuildData = &it->second;
		_CS_MINIMAP_DATA MiniMapData;

		memcpy(MiniMapData.m_szGuildName, &it->first[0], MAX_GUILD_LEN);

		mapMiniMapData.insert(pair<int, _CS_MINIMAP_DATA>(GuildData->m_iCsGuildID, MiniMapData));
	}

	LeaveCriticalSection(&m_critCsBasicGuildInfo);

	if (mapMiniMapData.empty())//DiG Fix
	{
		return;
	}

	EnterCriticalSection(&m_critNpcData);

	lpMsgSend2->iCount = 0;

	if (m_vtNpcData.empty() == false)
	{
		for (auto it = m_vtNpcData.begin(); it != m_vtNpcData.end(); it++)
		{
			if (lpMsgSend2->iCount >= 150)
				break;

			_CS_NPC_DATA & NpcData = _CS_NPC_DATA(*it);

			if ((NpcData.m_iNPC_NUM == 277 || NpcData.m_iNPC_NUM == 283) && NpcData.m_iNPC_OBJINDEX != OBJ_EMPTY)
			{
				if (!gObjIsConnected(NpcData.m_iNPC_OBJINDEX) || gObj[NpcData.m_iNPC_OBJINDEX].m_iCsNpcExistVal != NpcData.m_iCsNpcExistVal || (gObj[NpcData.m_iNPC_OBJINDEX].Class != 277 && gObj[NpcData.m_iNPC_OBJINDEX].Class != 283))
				{
					BYTE btNpcType = 0;
					switch (NpcData.m_iNPC_NUM)
					{
					case 277:
						btNpcType = 0;
						break;
					case 283:
						btNpcType = 1;
						break;
					default:
						continue;
						break;
					}

					lpMsgSendBody2[lpMsgSend2->iCount].btNpcType = btNpcType;
					lpMsgSendBody2[lpMsgSend2->iCount].btX = gObj[NpcData.m_iNPC_OBJINDEX].X;
					lpMsgSendBody2[lpMsgSend2->iCount].btY = gObj[NpcData.m_iNPC_OBJINDEX].Y;

					lpMsgSend2->iCount++;
				}
			}
		}
	}

	lpMsgSend2->h.set(cBUFFER2, 0xBB, (lpMsgSend2->iCount * sizeof(PMSG_SENDNPCMINIMAPDATA)) + sizeof(PMSG_ANS_SENDNPCMINIMAPDATA));

	LeaveCriticalSection(&m_critNpcData);

	EnterCriticalSection(&m_critCsMiniMap);

	m_mapMiniMapData.clear();

	map<int, _CS_MINIMAP_DATA>::iterator it2(mapMiniMapData.begin());//DiG Fix

	for (; it2 != mapMiniMapData.end(); it2++)
	{
		m_mapMiniMapData.insert(pair<int, _CS_MINIMAP_DATA>(it2->first, it2->second));
	}

	for (int iIDX = OBJ_STARTUSERINDEX; iIDX < OBJMAX; iIDX++)
	{
		if (gObjIsConnected(iIDX) == FALSE)
			continue;

		if (gObj[iIDX].MapNumber != MAP_INDEX_CASTLESIEGE)
			continue;

		if (gObj[iIDX].m_btCsJoinSide == 0)
			continue;

		map<int, _CS_MINIMAP_DATA>::iterator it3(m_mapMiniMapData.find(gObj[iIDX].m_btCsJoinSide));//DiG Fix

		if (it3 != m_mapMiniMapData.end())
		{
			if (it3->second.m_iMiniMapPointCount >= 1000)
				continue;

			if (gObj[iIDX].GuildStatus == GUILD_MASTER &&
				strcmp(gObj[iIDX].GuildName, "") != 0 &&
				strcmp(gObj[iIDX].GuildName, it3->second.m_szGuildName) == 0)
			{
				it3->second.m_iGuildMasterIndex = iIDX;
				continue; //HermeX Fix @10/02/2010
			}
			it3->second.m_stMiniMapPoint[it3->second.m_iMiniMapPointCount].btX = gObj[iIDX].X;
			it3->second.m_stMiniMapPoint[it3->second.m_iMiniMapPointCount].btY = gObj[iIDX].Y;
			it3->second.m_iMiniMapPointCount++;
		}
	}

	map<int, _CS_MINIMAP_DATA>::iterator it4(m_mapMiniMapData.begin());//DiG Fix

	for (; it4 != m_mapMiniMapData.end(); it4++)
	{
		lpMsgSend1->iCount = 0;

		if (gObjIsConnected(it4->second.m_iGuildMasterIndex) == FALSE)
			continue;

		lpMsgSend1->iCount = it4->second.m_iMiniMapPointCount;

		if (lpMsgSend1->iCount > 1000)
		{
			lpMsgSend1->iCount = 1000;
		}

		memcpy(lpMsgSendBody1, it4->second.m_stMiniMapPoint, (lpMsgSend1->iCount * sizeof(PMSG_SENDMINIMAPDATA)));

		lpMsgSend1->h.set(cBUFFER1, 0xB6, (lpMsgSend1->iCount * sizeof(PMSG_SENDMINIMAPDATA)) + sizeof(PMSG_ANS_SENDMINIMAPDATA));

		DataSend(it4->second.m_iGuildMasterIndex, cBUFFER1, (lpMsgSend1->iCount * sizeof(PMSG_SENDMINIMAPDATA)) + sizeof(PMSG_ANS_SENDMINIMAPDATA));

		DataSend(it4->second.m_iGuildMasterIndex, cBUFFER2, (lpMsgSend2->iCount * sizeof(PMSG_SENDNPCMINIMAPDATA)) + sizeof(PMSG_ANS_SENDNPCMINIMAPDATA));
	}

	LeaveCriticalSection(&m_critCsMiniMap);
}

void CCastleSiege::NotifyCrownState(BYTE btState) //Identical
{
	if (gObjIsConnected(m_iCrownIndex) == FALSE)
	{
		LogAddC(2, "[CastleSiege] CCastleSiege::NotifyCrownState() - m_iCrownIndex isn't Valid");
		return;
	}

	if (gObj[m_iCrownIndex].Class != 216)
	{
		LogAddC(2, "[CastleSiege] CCastleSiege::NotifyCrownState() - m_iCrownIndex isn't Valid");
		return;
	}

	LPOBJ lpObj = &gObj[m_iCrownIndex];

	if (lpObj->VPCount2 < 1)
	{
		return;
	}

	PMSG_ANS_NOTIFYCROWNSTATE pMsg;

	pMsg.h.set((LPBYTE)&pMsg, 0xB2, 0x16, sizeof(pMsg));
	pMsg.btCrownState = btState;

	int tObjNum = OBJ_EMPTY;

	for (int i = 0; i < MAX_VIEWPORT; i++)
	{
		tObjNum = lpObj->VpPlayer2[i].number;

		if (tObjNum >= 0)
		{
			if (gObj[tObjNum].Type == OBJ_USER && gObj[tObjNum].Live)
			{
				DataSend(tObjNum, (LPBYTE)&pMsg, pMsg.h.size);
			}
		}
	}

	LogAdd("[CastleSiege] Crown State Changed (%d)", btState);
}

void CCastleSiege::NotifyCrownSwitchInfo(int iCrownSwitchIndex) //Identical
{
	if (gObjIsConnected(iCrownSwitchIndex) == FALSE)
	{
		LogAddC(2, "[CastleSiege] CCastleSiege::NotifyCrownSwitchInfo() - iCrownSwitchIndex is Invalid");

		return;
	}

	if ((gObj[iCrownSwitchIndex].Class != 217) && (gObj[iCrownSwitchIndex].Class != 218))
	{
		LogAddC(2, "[CastleSiege] CCastleSiege::NotifyCrownSwitchInfo() - iCrownSwitchIndex is Invalid");

		return;
	}

	LPOBJ lpObj = &gObj[iCrownSwitchIndex];

	if (lpObj->VPCount2 < 1)
	{
		return;
	}

	PMSG_ANS_NOTIFY_CROWNSWITCH_INFO pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xB2, 0x20, sizeof(pMsg));

	pMsg.btIndex1 = SET_NUMBERH(LOWORD(iCrownSwitchIndex));
	pMsg.btIndex2 = SET_NUMBERL(LOWORD(iCrownSwitchIndex));

	pMsg.btSwitchState = 0;
	pMsg.btJoinSide = 0;

	memset(&pMsg.szGuildName, 0, MAX_GUILD_LEN);
	memset(&pMsg.szUserName, 0, MAX_ACCOUNT_LEN);

	int iCrownSwitchUserIndex = g_CastleSiege.GetCrownSwitchUserIndex(lpObj->Class); // wtf!

	if (gObjIsConnected(iCrownSwitchUserIndex))
	{
		LPOBJ lpSwitchObj = &gObj[iCrownSwitchUserIndex];
		char szMasterGuildName[MAX_GUILD_LEN];

		pMsg.btSwitchState = TRUE;
		pMsg.btJoinSide = lpSwitchObj->m_btCsJoinSide;

		memcpy(&pMsg.szUserName, lpSwitchObj->Name, MAX_ACCOUNT_LEN);
		memcpy(&pMsg.szGuildName, lpSwitchObj->GuildName, MAX_GUILD_LEN);
		memset(&szMasterGuildName, 0, MAX_GUILD_LEN);

		if (lpSwitchObj->lpGuild)
		{
			if (UnionManager.GetUnionName(lpSwitchObj->lpGuild->iGuildUnion, szMasterGuildName) != -1)
			{
				memcpy(&pMsg.szGuildName, szMasterGuildName, MAX_GUILD_LEN);
			}
		}
		DataSend(iCrownSwitchUserIndex, (LPBYTE)&pMsg, pMsg.h.size);
	}

	int tObjNum = OBJ_EMPTY;

	for (int i = 0; i < MAX_VIEWPORT; i++)
	{
		tObjNum = lpObj->VpPlayer2[i].number;

		if (tObjNum >= 0)
		{
			if (gObj[tObjNum].Type == OBJ_USER && gObj[tObjNum].Live)
			{
				DataSend(tObjNum, (LPBYTE)&pMsg, pMsg.h.size);
			}
		}
	}
}

void CCastleSiege::SendMapServerGroupMsg(char * lpszMsg) //Identical
{
	GS_GDReqMapSvrMsgMultiCast(this->m_iMapSvrGroup, lpszMsg);
}

void CCastleSiege::SendAllUserAnyData(BYTE* lpMsg, int iSize) //Identical
{
	for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; i++)
	{
		if ((gObj[i].Connected == PLAYER_PLAYING) && (gObj[i].Type == OBJ_USER))
		{
			::DataSend(i, lpMsg, iSize);
		}
	}
}

void CCastleSiege::SendAllUserAnyMsg(char * lpszMsg, int iType) //Identical
{
	PMSG_NOTICE pNotice;

	if (lpszMsg == NULL)
		return;

	switch (iType)
	{
	case 1:
		TNotice::MakeNoticeMsg(&pNotice, 0, lpszMsg);
		TNotice::SetNoticeProperty(&pNotice, 10, _ARGB(255, 255, 200, 80), 1, 0, 20);
		TNotice::SendNoticeToAllUser(&pNotice);
		break;

	case 2:
		TNotice::MakeNoticeMsg(&pNotice, 0, lpszMsg);

		for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; i++)
		{
			if ((gObj[i].Connected == PLAYER_PLAYING) && (gObj[i].Type == OBJ_USER))
			{
				::DataSend(i, (LPBYTE)&pNotice, pNotice.h.size);
			}
		}
		break;

	default:
		break;
	}
}

void CCastleSiege::SendCsUserAnyData(BYTE* lpMsg, int iSize) //Identical
{
	for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; i++)
	{
		if ((gObj[i].Connected == PLAYER_PLAYING) && (gObj[i].Type == OBJ_USER))
		{
			if (gObj[i].MapNumber == MAP_INDEX_CASTLESIEGE)
			{
				DataSend(i, lpMsg, iSize);
			}
		}
	}
}

void CCastleSiege::SendCsUserAnyMsg(char* lpszMsg) //Identical
{
	PMSG_NOTICE pNotice;

	if (lpszMsg == NULL)
		return;

	TNotice::MakeNoticeMsg(&pNotice, 0, lpszMsg);

	for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; i++)
	{
		if ((gObj[i].Connected == PLAYER_PLAYING) && (gObj[i].Type == OBJ_USER))
		{
			if (gObj[i].MapNumber == MAP_INDEX_CASTLESIEGE)
			{
				DataSend(i, (LPBYTE)&pNotice, pNotice.h.size);
			}
		}
	}
}

void CCastleSiege::OperateGmCommand(int iIndex, int iGmCommand, void* lpParam) //Identical (HermeX & DiG Fix Applied)
{
	if (gObjIsConnected(iIndex) == FALSE)
		return;

	if ((gObj[iIndex].Authority & 2) != 2)
		return;

	switch (iGmCommand)
	{
	case 0:
		{
			LPSTR szNewOwnerGuild = (char*)lpParam;

			if (szNewOwnerGuild == NULL)
			{
				MsgOutput(iIndex, lMsg.Get(3200));
			}
			else
			{
				if (strcmp(szNewOwnerGuild, "") != 0)
				{
					memset(&this->m_szCastleOwnerGuild, 0, sizeof(this->m_szCastleOwnerGuild));
					memcpy(&this->m_szCastleOwnerGuild, szNewOwnerGuild, 8);
					this->m_btIsCastleOccupied = 1;
					MsgOutput(iIndex, lMsg.Get(3201), this->m_szCastleOwnerGuild);
				}
				else
				{
					strcpy(this->m_szCastleOwnerGuild, "");
					this->m_btIsCastleOccupied = 0;
					MsgOutput(iIndex, lMsg.Get(3200));
				}
			}
		}
		break;
	case 1:
		{
			GetLocalTime(&m_tmStartDate);

			m_tmStartDate.wHour = 0;
			m_tmStartDate.wMinute = 0;
			m_tmStartDate.wSecond = 0;

			this->m_tmEndDate = this->m_tmStartDate;
			this->GetNextDay(&this->m_tmEndDate, m_iCastleSiegeCycle, 0, 0, 0);

			this->m_bFixCastleCycleStartDate = FALSE;
			this->m_btIsSiegeEnded = FALSE;

			GS_GDReqResetRegSiegeInfo(this->m_iMapSvrGroup);

			if (this->CheckSync() == FALSE)
			{
				LogAddC(2, "[CastleSiege] CCastleSiege::Init() - CheckSync() == FALSE");
				MsgBox("[CastleSiege] CCastleSiege::Init() - CheckSync() == FALSE");
				MsgOutput(iIndex, lMsg.Get(3202));
				return; //HermeX Fix
			}
			this->m_bDoRun = TRUE;
			this->m_dwNPC_DBSAVE_TICK_COUNT = GetTickCount();
			this->m_dwCALC_LEFTSIEGE_TICK_COUNT = 0;
			this->m_dwEVENT_MSG_TICK_COUNT = 0;
			this->m_dwCHECK_GATE_ALIVE_COUNT = 0;
			MsgOutput(iIndex, lMsg.Get(3203));
		}
		break;
	case 2:
		{
			this->SetState(CASTLESIEGE_STATE_REGMARK, 1);
			MsgOutput(iIndex, lMsg.Get(3204));
		}
		break;
	case 3:
		{
			this->m_btIsSiegeGuildList = FALSE;
			this->SetState(CASTLESIEGE_STATE_NOTIFY, 1);
			MsgOutput(iIndex, lMsg.Get(3205));
		}
		break;
	case 4:
		{
			this->SetState(CASTLESIEGE_STATE_STARTSIEGE, 1);
			MsgOutput(iIndex, lMsg.Get(3206));
		}
		break;

	case 5:
		{
			if (this->m_iCastleSiegeState == CASTLESIEGE_STATE_STARTSIEGE)
			{
				this->m_iCS_REMAIN_MSEC = 0;
				MsgOutput(iIndex, lMsg.Get(3207));
			}
			else
			{
				MsgOutput(iIndex, lMsg.Get(3208));
			}
		}
		break;
	case 6:
		{
			if (strcmp(this->m_szCastleOwnerGuild, "") == 0)
			{
				MsgOutput(iIndex, lMsg.Get(3209));
			}
			else
			{
				MsgOutput(iIndex, lMsg.Get(3210), this->m_szCastleOwnerGuild);
			}
		}
		break;
	case 7:
		{
			if (this->m_bDoRun == FALSE)
			{
				MsgOutput(iIndex, lMsg.Get(3211));
			}
			else
			{
				switch (this->m_iCastleSiegeState)
				{
				case CASTLESIEGE_STATE_NONE:
					MsgOutput(iIndex, lMsg.Get(3211));
					break;
				case CASTLESIEGE_STATE_IDLE_1:
					MsgOutput(iIndex, lMsg.Get(3212));
					break;
				case CASTLESIEGE_STATE_REGSIEGE:
					MsgOutput(iIndex, lMsg.Get(3213),
						(int((this->m_iCS_REMAIN_MSEC / 1000) / 3600)), //hora
						(int((this->m_iCS_REMAIN_MSEC / 1000) % 3600) / 60),	//minutos
						(int((this->m_iCS_REMAIN_MSEC / 1000) % 3600) % 60));//segundo
					break;
				case CASTLESIEGE_STATE_IDLE_2:
					MsgOutput(iIndex, lMsg.Get(3214),
						(int((this->m_iCS_REMAIN_MSEC / 1000) / 3600)), //hora
						(int((this->m_iCS_REMAIN_MSEC / 1000) % 3600) / 60),	//minutos
						(int((this->m_iCS_REMAIN_MSEC / 1000) % 3600) % 60));//segundo
					break;
				case CASTLESIEGE_STATE_REGMARK:
					MsgOutput(iIndex, lMsg.Get(3215),
						(int((this->m_iCS_REMAIN_MSEC / 1000) / 3600)), //hora
						(int((this->m_iCS_REMAIN_MSEC / 1000) % 3600) / 60),	//minutos
						(int((this->m_iCS_REMAIN_MSEC / 1000) % 3600) % 60));//segundo
					break;
				case CASTLESIEGE_STATE_IDLE_3:
					MsgOutput(iIndex, lMsg.Get(3216),
						(int((this->m_iCS_REMAIN_MSEC / 1000) / 3600)), //hora
						(int((this->m_iCS_REMAIN_MSEC / 1000) % 3600) / 60),	//minutos
						(int((this->m_iCS_REMAIN_MSEC / 1000) % 3600) % 60));//segundo
					break;
				case CASTLESIEGE_STATE_NOTIFY:
					MsgOutput(iIndex, lMsg.Get(3217),
						(int((this->m_iCS_REMAIN_MSEC / 1000) / 3600)), //hora
						(int((this->m_iCS_REMAIN_MSEC / 1000) % 3600) / 60),	//minutos
						(int((this->m_iCS_REMAIN_MSEC / 1000) % 3600) % 60));//segundo
					break;
				case CASTLESIEGE_STATE_READYSIEGE:
					MsgOutput(iIndex, lMsg.Get(3218),
						(int((this->m_iCS_REMAIN_MSEC / 1000) / 3600)), //hora
						(int((this->m_iCS_REMAIN_MSEC / 1000) % 3600) / 60),	//minutos
						(int((this->m_iCS_REMAIN_MSEC / 1000) % 3600) % 60));//segundo
					break;
				case CASTLESIEGE_STATE_STARTSIEGE:
					MsgOutput(iIndex, lMsg.Get(3219),
						(int((this->m_iCS_REMAIN_MSEC / 1000) / 3600)), //hora
						(int((this->m_iCS_REMAIN_MSEC / 1000) % 3600) / 60),	//minutos
						(int((this->m_iCS_REMAIN_MSEC / 1000) % 3600) % 60));//segundo
					break;
				case CASTLESIEGE_STATE_ENDSIEGE:
					MsgOutput(iIndex, lMsg.Get(3220),
						(int((this->m_iCS_REMAIN_MSEC / 1000) / 3600)), //hora
						(int((this->m_iCS_REMAIN_MSEC / 1000) % 3600) / 60),	//minutos
						(int((this->m_iCS_REMAIN_MSEC / 1000) % 3600) % 60));//segundo
					break;
				case CASTLESIEGE_STATE_ENDCYCLE:
					MsgOutput(iIndex, lMsg.Get(3221));
					break;
				default:
					MsgOutput(iIndex, lMsg.Get(3211));
					break;
				}
			}
		}
		break;
	case 8:
		{
			LPSTR szGuildName = (LPSTR)lpParam;

			if (this->m_iCastleSiegeState != CASTLESIEGE_STATE_STARTSIEGE)
			{
				MsgOutput(iIndex, lMsg.Get(3222));
			}
			else if (szGuildName == NULL)
			{
				MsgOutput(iIndex, lMsg.Get(3222));
			}
			else if (strcmp(szGuildName, "") == 0)
			{
				MsgOutput(iIndex, lMsg.Get(3222));
			}
			else
			{
				BYTE btCsJoinSide = 0;
				BYTE bCsGuildInvolved = false;
				int iResult = this->GetCsJoinSide(szGuildName, &btCsJoinSide, &bCsGuildInvolved);

				if (iResult == 1)
				{
					if (btCsJoinSide > 1 && bCsGuildInvolved == 1)
					{
						LogAdd("[CastleSiege] Castle Winner Has been Changed - GM (GUILD:%s)",
							szGuildName);

						this->NotifyCrownState(2);

						memset(&this->m_szMiddleWinnerGuild, 0, sizeof(this->m_szMiddleWinnerGuild));
						memcpy(&this->m_szMiddleWinnerGuild, szGuildName, 8);

						this->ClearNonDbNPC_MidWin();
						this->ChangeWinnerGuild(btCsJoinSide);
						this->NotifyAllUserCsProgState(CASTLESIEGE_STATE_REGSIEGE, szGuildName); //HermeX Fix
						this->ResetCrownAccessTickCount();
						this->ResetCrownUserIndex();
						this->SetCrownAccessUserX(0);
						this->SetCrownAccessUserY(0);
						this->ResetCrownSwitchUserIndex(217);
						this->ResetCrownSwitchUserIndex(218);

						this->m_bRegCrownAvailable = FALSE;
						this->ReSpawnEnemyUser(FALSE);

						GCAnsCsLeftTimeAlarm(((this->m_iCS_REMAIN_MSEC / 1000) / 3600), ((this->m_iCS_REMAIN_MSEC / 1000) % 3600) / 60); //HermeX Fix @10/02/2010

						this->m_dwCS_LEFTTIME_TICK_COUNT = GetTickCount();
					}
					MsgOutput(iIndex, lMsg.Get(3223));
				}
				else
				{
					MsgOutput(iIndex, lMsg.Get(3222)); //HermeX Fix -> HermeX Second Fix @10/02/2010
				}
			}
		}
		break;
	}
}

void CCastleSiege::CreateDbNPC_INS() //Identical
{
	this->ClearDbNPC();

	EnterCriticalSection(&this->m_critNpcData);

	auto it = this->m_vtNpcData.begin();

	while (it != this->m_vtNpcData.end())
	{
		_CS_NPC_DATA NpcData(*it);
		auto pNpcData = &NpcData;

		if (pNpcData->m_bNPC_DBSAVE == TRUE)
		{
			it->SetBaseValue();
			it->m_iNPC_LIVE = TRUE;
			it->m_iNPC_SIDE = 1;
			it->m_iNPC_OBJINDEX = -1;
			it->m_iCS_GATE_LEVER_INDEX = -1;
		}
		it++;
	}

	LeaveCriticalSection(&this->m_critNpcData);

	this->m_bDbNpcCreated = FALSE;
}

void CCastleSiege::SavePcRoomUserList() //Identical
{
}
#endif