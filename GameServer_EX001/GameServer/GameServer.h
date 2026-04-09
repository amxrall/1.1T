// GameServer.h
// ------------------------------
// Decompiled by Deathway
// Date : 2007-03-09
// ------------------------------
#ifndef	GAMESERVER_H

#define	GAMESERVER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RingAttackEvent.h"
#include "CWhatsUpDummyServer.h"

#define WM_GM_SERVER_MSG_PROC			0x401
#define WM_GM_CLIENT_MSG_PROC			0x402
#define WM_GM_JOIN_CLIENT_MSG_PROC		0x403
#define WM_START_SERVER					0x405
#define WM_GM_DATA_CLIENT_MSG_PROC		0x40A
#define WM_GM_RANKING_CLIENT_MSG_PROC	0x40C
#define WM_GM_EVENTCHIP_CLIENT_MSG_PROC	0x40D
#define WM_GM_EXDATA_CLIENT_MSG_PROC	0x40E
#define WM_GM_CONNECT_SERVER_MSG		0x40F

#define	WM_LOG_PAINT					0x64
#define WM_FIRST_MSG_PROCESS			0x65
#define WM_SECOND_MSG_PROCESS			0x3E8
#define WM_SET_DATE						0x3E9
#define WM_GS_CLOSE						0x3EA
#define WM_EVENT_RUN_PROC				0x3EC
#define WM_MOVE_MONSTER_PROC			0x3ED
#define WM_MONSTER_AND_MSG_PROC			0x3EE
#define WM_CONNECT_DATASERVER			0x3EF
#define WM_GUILD_LIST_REQUEST			0x3F0

#define FINAL_PATH			"..\\Data\\"
#define COMMONSERVER_PATH	"..\\Data\\commonserver.cfg"

extern char ExDbIp[16];
extern char DataServerIp[16];
extern char JoinServerIp[16];
extern int gServerReady;
extern int gCloseMsg;
extern int gCloseMsgTime;
extern CRingMonsterHerd g_MonsterHerdTest;
extern CRingAttackEvent g_RingAttackEvent;
extern CWhatsUpDummyServer gWhatsUpDummyServer;

extern HINSTANCE hInst; // Current Instance
extern HWND ghWnd;

#if(GS_CASTLE==1)
extern HWND g_hCsLogDlgProc;
#endif

extern char szTitle[100];
extern char szWindowClass[100];

#define RANKING_SERVER_PORT 44455
#define EVENT_CHIP_SERVER_PORT 44456

BOOL AllServerStart(void); // Start all Servers

#endif