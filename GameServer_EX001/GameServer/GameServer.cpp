#include "stdafx.h"
#include "MonsterHerd.h"
#include "resource.h"
#include "GameServer.h"
#include "Gamemain.h"
#include "Giocp.h"
#include "LogProc.h"
#include "RingAttackEvent.h"
#include "CWhatsUpDummyServer.h"
#include "DBSockMng.h"
#include "DSProtocol.h"
#include "EDSProtocol.h"
#include "SProtocol.h"
#include "ChaosCastle.h"
#include "Protocol.h"
#include "user.h"
#include "MapServerManager.h"
#include "protocol.h"
#include "Shop.h"
#include "Weapon.h"
#include "CastleSiegeSync.h"
#include "BloodCastle.h"
#include "EledoradoEvent.h"
#include "EventManagement.h"
#include "Load.h"
#include "Database.h"

char ExDbIp[16];
char DataServerIp[16];
char JoinServerIp[16];
int gServerReady;
int gCloseMsg;
int gCloseMsgTime;

CRingMonsterHerd g_MonsterHerdTest;
CRingAttackEvent g_RingAttackEvent;
CWhatsUpDummyServer gWhatsUpDummyServer;

HINSTANCE hInst; // Current Instance
HWND ghWnd;
#if(GS_CASTLE==1)
#include "CastleSiege.h"
HWND g_hCsLogDlgProc;
#endif

char szTitle[100];
char szWindowClass[100];

BOOL GameServerStart(void);
int InitInstance(HINSTANCE, int);	// Init GameServer
ATOM MyRegisterClass(HINSTANCE);	// Register Window Class
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);// Brain of the GameServer
LRESULT CALLBACK About(HWND hInst, UINT message, WPARAM wParam, LPARAM lParam);

#if(GS_CASTLE==1)
LRESULT CALLBACK CsLogDlgProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
#endif

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	HACCEL hAccelTable;

	LoadString(hInstance, IDS_APP_TITLE, szTitle, 100);
	LoadString(hInstance, IDS_GAMESERVER, szWindowClass, 100);

	MyRegisterClass(hInstance);

	InitCommonControls();
	
	if (!InitInstance(hInstance, nCmdShow))
	{
		return 0;
	}

	ShowWindow(ghWnd, SW_SHOWMAXIMIZED);

	hAccelTable = LoadAccelerators(hInstance, (LPCSTR)IDA_GAMESERVER);


#if(PROTECT_STATE==1)
	//License.Load();
#else
	//License.Load();
#endif

	Optimize.Load();
	GiocpInit();
	GameMainInit(ghWnd);

	// Offset Corre鏰o bState
//	*(BYTE*)(0x43EEBE) = 0xEB;

	int serverport = 0;	// Server Port

	memset(ExDbIp, 0, sizeof(ExDbIp));
	ExDbPort = 0;

	// Port Configuration from Cmd Line
	if (strlen(lpCmdLine) > 1)
	{
		sscanf(lpCmdLine, "%s %d %s %d %d %s %d", JoinServerIp, &JoinServerPort, DataServerIp, &DataServerPort, &serverport, ExDbIp, &ExDbPort);
	}
	else
	{
		serverport = 55900;
		JoinServerPort = 55970;
		DataServerPort = 55960;
		ExDbPort = 55906;
		MsgBox(lMsg.Get(MSGGET(0, 114)));
	}

	if (ExDbIp[0] == 0)
		memcpy(ExDbIp, DataServerIp, sizeof(ExDbIp));

	if (ExDbPort == 0)
		ExDbPort = 55906;

	GameServerPort = serverport;
	gWhatsUpDummyServer.Start(ghWnd, GameServerPort + 1);
	AllServerStart();

	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

BOOL AllServerStart(void)
{
	if (JoinServerConnected == 0)
	{
		if (GMJoinServerConnect(JoinServerIp, WM_GM_JOIN_CLIENT_MSG_PROC) == 0)
		{
			// LoginServer connect fail
			MsgBox(lMsg.Get(MSGGET(1, 144)));
			return 0;
		}
	}

	if ((DevilSquareEventConnect == 0) && (IsDevilSquareEventConnected == 0))
	{
		if (GMRankingServerConnect(gDevilSquareEventServerIp, WM_GM_RANKING_CLIENT_MSG_PROC) == 0)
		{
			MsgBox("Ranking Server俊 立加 救凳");
			return 0;
		}

		IsDevilSquareEventConnected = 1;
	}

	if ((EventChipServerConnect != 0) && (IsEventChipServerConnected == 0))
	{
		if (GMEventChipServerConnect(gEventChipServerIp, WM_GM_EVENTCHIP_CLIENT_MSG_PROC) == 0)
		{
			MsgBox("Event Chip Server俊 立加 救凳");
			return 0;
		}

		IsEventChipServerConnected = 1;
	}

	cDBSMng.Connect();

	if (wsExDbCli.GetSocket() == INVALID_SOCKET)
	{
		LogAddC(2, "ExDB Server Check..");
		wsExDbCli.CreateSocket(ghWnd);
		ExDataServerConnect(ExDbIp, WM_GM_EXDATA_CLIENT_MSG_PROC);
	}
	else
	{
		if (wsExDbCli.GetConnect() == 0)
		{
			LogAddC(2, "ExDB Server Check..");
			ExDataServerConnect(ExDbIp, WM_GM_EXDATA_CLIENT_MSG_PROC);
		}
	}

	return TRUE;
}

BOOL GameServerStart(void)
{
	if (GameMainServerCreate(WM_GM_SERVER_MSG_PROC, WM_GM_CLIENT_MSG_PROC) == FALSE)
	{
		MsgBox(lMsg.Get(MSGGET(1, 142)));
		return FALSE;
	}

	CreateGIocp(GameServerPort);

	SetTimer(ghWnd, WM_LOG_PAINT, 2000, NULL);
	SetTimer(ghWnd, WM_FIRST_MSG_PROCESS, 1000, NULL);
	SetTimer(ghWnd, WM_SET_DATE, 60000, NULL);
	SetTimer(ghWnd, WM_CONNECT_DATASERVER, 10000, NULL);
	SetTimer(ghWnd, WM_SECOND_MSG_PROCESS, 1000, NULL);
	SetTimer(ghWnd, WM_GS_CLOSE, 1000, NULL);
	SetTimer(ghWnd, WM_MONSTER_AND_MSG_PROC, 500, NULL);
	SetTimer(ghWnd, WM_MOVE_MONSTER_PROC, 300, NULL);
	SetTimer(ghWnd, WM_EVENT_RUN_PROC, 100, NULL);
	SetTimer(ghWnd, WM_GUILD_LIST_REQUEST, 1000, NULL);


	return TRUE;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_NORMAL_V1);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = (LPCSTR)IDR_MENU;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_ICON_MINIMIZED);

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	ghWnd = CreateWindowEx(0, szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (ghWnd == 0)
	{
		return FALSE;
	}

	ShowWindow(ghWnd, nCmdShow);

	UpdateWindow(ghWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	INT wmId, wmEvent;

	switch (message)
	{
	case WM_CREATE:
#if(GS_CASTLE==1)
		g_hCsLogDlgProc = CreateDialogParam(hInst, (LPCTSTR)0x92, hWnd, (DLGPROC)CsLogDlgProc, 0);
#endif
		return 0;
	case WM_COMMAND:
		wmId = wParam & 0xFFFF & 0xFFFF;
		wmEvent = (wParam >> 16) & 0xFFFF;

		switch (wmId)
		{
		case IDM_EXIT:
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		case IDM_ALL_USER_CLOSE:
			gObjAllDisconnect();
			break;
		case IDM_ALL_USER_LOGOUT:
			gObjAllLogOut();
			break;
		case IDM_MONSTER_POSITION_RELOAD:
			GameMonsterAllCloseAndReLoad();
			break;
		case IDM_SHOP_RELOAD:
			ShopDataLoad();
			break;
		case IDM_MAP_SERVER_INFO_RELOAD:
			g_MapServerManager.LoadData("..\\Data\\MapServerInfo.txt");
			break;
		case GBS_RELOADBOSSEVENT:
			BossEvent.Run();
			break;
#if(GS_CASTLE==1)
		case IDM_CASTLE_SIEGE_RELOAD:
			if (g_CastleSiege.Ready(g_MapServerManager.GetMapSvrGroup()) == TRUE)
			{
				if (g_CastleSiege.LoadData("..\\Data\\Event\\MuCastleData.txt"))
				{
					g_CastleSiege.LoadPreFixData(COMMONSERVER_FILE);
					g_CastleSiege.SetDataLoadState(CASTLESIEGE_DATALOAD_2);
				}
			}
			break;
#endif
		case IDM_OPTION_RELOAD:
			ReadCommonServerInfo();
			break;
		case IDM_5_MINUTE_CLOSE:
			if (gCloseMsg == 0)
			{
				gCloseMsgTime = 300;
				gCloseMsg = 1;
				AllSendServerMsg(lMsg.Get(MSGGET(4, 104)));
			}
			break;
		case IDM_3_MINUTE_CLOSE:
			if (gCloseMsg == 0)
			{
				gCloseMsgTime = 180;
				gCloseMsg = 2;
				AllSendServerMsg(lMsg.Get(MSGGET(4, 105)));
			}
			break;
		case IDM_1_MINUTE_CLOSE:
			if (gCloseMsg == 0)
			{
				gCloseMsgTime = 60;
				gCloseMsg = 3;
				AllSendServerMsg(lMsg.Get(MSGGET(4, 106)));
			}
			break;
		case IDM_RELOAD_ALL_EVENT:
			ReadEventInfo(MU_EVENT_ALL);
			break;
		case IDM_RELOAD_DEVILSQUARE:
			ReadEventInfo(MU_EVENT_DEVILSQUARE);
			break;
		case IDM_RELOAD_BLOODCASTLE:
			ReadEventInfo(MU_EVENT_BLOODCASTLE);
			break;
		case IDM_RELOAD_UNDERWORLD_ATTACK:
			ReadEventInfo(MU_EVENT_ATTACKEVENTTROOP);
			break;
		case IDM_RELOAD_GOLDENTROOP_ATTACK:
			ReadEventInfo(MU_EVENT_GOLDENTROOP);
			break;
		case IDM_RELOAD_WHITEMAGE_ATTACK:
			ReadEventInfo(MU_EVENT_WHITEMAGETROOP);
			break;
		case IDM_RELOAD_LOVE_PANGPANG:
			ReadEventInfo(MU_EVENT_LOVEPANGPANG);
			break;
		case IDM_RELOAD_FIRECRACKER:
			ReadEventInfo(MU_EVENT_FIRECRACKER);
			break;
		case IDM_RELOAD_XMAS_STAR:
			ReadEventInfo(MU_EVENT_XMASSTAR);
			break;
		case IDM_RELOAD_HEART_OF_LOVE:
			ReadEventInfo(MU_EVENT_HEARTOFLOVE);
			break;
		case IDM_RELOAD_NPC_SAY_HAPPY_NEW_YEAR:
			ReadEventInfo(MU_EVENT_SAY_HAPPYNEWYEAR);
			break;
		case IDM_RELOAD_NPC_SAY_MERRY_XMAS:
			ReadEventInfo(MU_EVENT_SAY_MERRYXMAS);
			break;
		case IDM_RELOAD_CHAOSCASTLE:
			ReadEventInfo(MU_EVENT_CHAOSCASTLE);
			break;
		case IDM_RELOAD_ALL_ETC_OPTION:
			ReadGameEtcInfo(MU_ETC_ALL);
			break;
		case IDM_RELOAD_CREATE_CHARACTER:
			ReadGameEtcInfo(MU_ETC_CREATECHARACTER);
			break;
		case IDM_RELOAD_GUILD:
			ReadGameEtcInfo(MU_ETC_GUILD);
			break;
		case IDM_RELOAD_TRADE:
			ReadGameEtcInfo(MU_ETC_TRADE);
			break;
		case IDM_RELOAD_CHAOSBOX:
			ReadGameEtcInfo(MU_ETC_USECHAOSBOX);
			break;
		case IDM_RELOAD_PERSONAL_SHOP:
			ReadGameEtcInfo(MU_ETC_PERSONALSHOP);
			break;
		case IDM_RELOAD_PK_ITEM_DROP:
			ReadGameEtcInfo(MU_ETC_PKITEMDROP);
			break;
		case IDM_RELOAD_ITEM_DROP_RATE:
			ReadGameEtcInfo(MU_ETC_ITEMDROPRATE);
			break;
		case IDM_RELOAD_SPEEDHACK:
			ReadGameEtcInfo(MU_ETC_SPEEDHACK);
			break;
		case IDM_RELOAD_GAMEGUARD_CHECKSUM_CHECK:
			ReadGameEtcInfo(MU_ETC_GAMEGUARD);
			break;
		case IDM_CUSTOMS_RELOAD:
			Load();
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}
		break;
	case WM_GM_SERVER_MSG_PROC:
		GMServerMsgProc(wParam, lParam);
		break;
	case WM_GM_CLIENT_MSG_PROC:
		GMClientMsgProc(wParam, lParam);
		break;
	case WM_GM_JOIN_CLIENT_MSG_PROC:
		GMJoinClientMsgProc(wParam, lParam);
		break;
	case WM_GM_RANKING_CLIENT_MSG_PROC:
		GMRankingClientMsgProc(wParam, lParam);
		break;
	case WM_GM_EVENTCHIP_CLIENT_MSG_PROC:
		GMEventChipClientMsgProc(wParam, lParam);
		break;
	case WM_GM_DATA_CLIENT_MSG_PROC:
		cDBSMng.MsgProc(0, wParam, lParam);
		break;
	case WM_GM_EXDATA_CLIENT_MSG_PROC:
		ExDataClientMsgProc(wParam, lParam);
		break;
	case WM_START_SERVER:
		if (gServerReady == 2)
		{
			GameServerStart();
		}
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case WM_GUILD_LIST_REQUEST:
			DGGuildListRequest();
			KillTimer(ghWnd, WM_GUILD_LIST_REQUEST);
			break;
		case WM_LOG_PAINT:
		{
			RECT rect;
			HDC hdc = GetDC(ghWnd);
			GetClientRect(ghWnd, &rect);
			FillRect(hdc, &rect, (HBRUSH)GetStockObject(0));
			ReleaseDC(ghWnd, hdc);

			if (LogTextPaint != NULL)
			{
				LogTextPaint(hWnd);
			}

			Display.ViewPaint(hWnd);
		}
		break;
		case WM_MONSTER_AND_MSG_PROC:
			MonsterAndMsgProc();
			break;
		case WM_MOVE_MONSTER_PROC:
			MoveMonsterProc();
			break;
		case WM_EVENT_RUN_PROC:
			g_BloodCastle.Run();
			g_RingAttackEvent.Run();
			g_ChaosCastle.Run();
#if (GS_CASTLE==1)
			g_CastleSiege.Run();
			g_CastleDeepEvent.Run();
#endif
			g_CsNPC_Weapon.WeaponAttackProc();
			break;
		case WM_FIRST_MSG_PROCESS:
		    {

			   for (int n = 0; n < OBJMAX; n++)
			   {
				  gObjStateSetCreate(n);
			   }

			   for (int n = 0; n < OBJMAX; n++)
			   {
				  gObjViewportListDestroy(n);
				  gObjViewportListCreate(n);
				  gObjViewportListProtocol(n);

				  if (n >= OBJ_STARTUSERINDEX)
				  {
					  if (gDoPShopOpen != FALSE)
					  {
						  PShop_ViewportListRegenarate(n);

						  if (gObjIsConnected(n) != PLAYER_EMPTY)
						  {
							  gObj[n].m_bPShopItemChange = false;
						  }
					  }

					  gObjUnionUpdateProc(n);
				  }
			   }

			    gObjSetState();
			    GameServerInfoSend();
		    }
	        break;
		case WM_SECOND_MSG_PROCESS:
			{
				for (int n = 0; n < MAX_NUMBER_MAP; n++)
				{
					MapC[n].WeatherVariationProcess();
				}

				wsGServer.m_SendSec = wsGServer.m_SendSecTmp;
				wsGServer.m_RecvSec = wsGServer.m_RecvSecTmp;
				wsGServer.m_SendSecTmp = 0;
				wsGServer.m_RecvSecTmp = 0;
				DragonEvent.Run();
				AttackEvent.Run();
				gEledoradoEvent.Run();

				gObjSecondProc();
			}
			break;
		case WM_GS_CLOSE:
			if (gCloseMsg != 0)
			{
				gCloseMsgTime--;

				if (gCloseMsgTime <= 1)
				{
					if (gCloseMsgTime == 1)
					{
						AllSendServerMsg(lMsg.Get(MSGGET(1, 193)));
						LogAddC(2, lMsg.Get(MSGGET(1, 193)));
					}
				}
				else
				{
					if ((gCloseMsgTime % 10) == 0)
					{
						char szTemp[256];

						wsprintf(szTemp, lMsg.Get(MSGGET(1, 194)), gCloseMsgTime);
						AllSendServerMsg(szTemp);
						LogAddC(2, szTemp);
					}
				}

				if (gCloseMsgTime < 0)
				{
					KillTimer(ghWnd, WM_GS_CLOSE);
					gObjAllLogOut();
					gCloseMsgTime = 0;
					gCloseMsg = 0;
				}
			}

#if (GS_CASTLE == 1 )
			if (cDBSMng.GetActiveDS() > DS_UNINITIALIZED && g_CastleSiege.GetDataLoadState() == 2)
			{
				g_CastleSiege.DataRequest();
			}

			g_CastleSiege.SendCastleStateSync();

#endif
			g_CastleSiegeSync.AdjustTributeMoney();
			break;
		case WM_SET_DATE:
			{
				gSetDate();
				WhisperCash.TimeCheckCashDelete();
				g_EventManager.Run();

#if (GS_CASTLE == 1 )
				if (LogDateChange() == TRUE)
				{
					g_iCastleItemMixLimit = 1;
				}
#else
				LogDateChange();
#endif
			}
			break;
		case WM_CONNECT_DATASERVER:
			{
				cDBSMng.Connect();

				if (wsExDbCli.GetSocket() == INVALID_SOCKET)
				{
					LogAddC(2, "ExDB Server Check..");
					wsExDbCli.CreateSocket(ghWnd);
					ExDataServerConnect(ExDbIp, WM_GM_EXDATA_CLIENT_MSG_PROC);
	}
				else
				{
					if (wsExDbCli.GetConnect() == 0)
					{
						LogAddC(2, "ExDB Server Check..");
						ExDataServerConnect(ExDbIp, WM_GM_EXDATA_CLIENT_MSG_PROC);
					}
				}

				gObjCheckAllUserDuelStop();
				GJNotifyMaxUserCount();
}
			break;
		}
		break;
	case WM_CLOSE:
		{
			if (MessageBox(ghWnd, "GameServer close?", TITLE, MB_YESNO | MB_APPLMODAL) == IDYES)
			{
				DestroyWindow(hWnd);
			}
		}
		break;
	case WM_DESTROY:
		{
			GameMainFree();
			GiocpDelete();
			PostQuitMessage(0);
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if ((wParam & 0xFFFF & 0xFFFF) == IDOK || (wParam & 0xFFFF & 0xFFFF) == IDCANCEL)
		{
			EndDialog(hDlg, (wParam & 0xFFFF & 0xFFFF));
			return TRUE;
		}
		break;
	}
	return FALSE;
}

#if(GS_CASTLE==1)
LRESULT CALLBACK CsLogDlgProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	case 0x110:
		{
			SendMessage(hWnd, WM_SIZE, NULL, NULL);
		}
		break;

	case 0x10:
		{
			ShowWindow(hWnd, SW_HIDE);
			return TRUE;
		}
		break;

	case 0x5:
		{
			RECT pRect;
			GetClientRect(hWnd, &pRect);
			MoveWindow(GetDlgItem(hWnd, 0x3EB), pRect.left, pRect.top, pRect.right, pRect.bottom, TRUE);
			return TRUE;
		}
		break;
	}

	return FALSE;
}
#endif