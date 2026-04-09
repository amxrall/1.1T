#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_NO_DEPRECATED_WARNINGS

#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT			0x500

#define USE_REG_SYSTEM_IPGET	0

#define PROTO_WALK				0xD3
#define PROTO_SETPOS			0xDF
#define PROTO_ATTACK			0xD7
#define PROTO_BEATTACK			0x10




#if(GS_CASTLE == 0)
#define TITLE				   "[GameServer] Emulador Season I - GBTeam"
#else
#define TITLE				   "[GameServer] Emulador Season I - GBTeam"
#endif

// Premium or Free //
#ifndef PROTECT_STATE
#define PROTECT_STATE 1
#endif

#if(PROTECT_STATE==1)
#define GAMESERVER_NAME "Premium"
#else
#define GAMESERVER_NAME "Free"
#endif

#define UPDATES "Update : 05"

#define Version_GS "Season 1"

#include <atltime.h>
#include <Windows.h>
#include <winbase.h>
#include <winsock2.h>
#include <CommCtrl.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <math.h>
#include <process.h>
#include <direct.h>
#include <iostream>
#include <iomanip>
#include <map>
#include <fstream>
#include <string>
#include <ios>
#include <algorithm>
#include <vector>
#include <set>
#include <sql.h>
#include <sqlext.h>
#include <unordered_map>
#include <array>
#include <list>

// - Includes

#include "user.h"
#include "Tokenizer.h"
#include "Database.h"
#include "Manager.h"
#include "Setting.h"
#include "Connect.h"
#include "Functions.h"
#include "BossEvent.h"
#include "Character.h"
#include "Dropping.h"
#include "BloodEvent.h"
#include "ChaosEvent.h"
#include "DuelEvent.h"
#include "PegaEvent.h"
#include "SobreEvent.h"
#include "QuizEvent.h"
#include "DeathEvent.h"
#include "TheftEvent.h"
#include "HappyEvent.h"
#include "CoinEvent.h"
#include "RaffleEvent.h"
#include "Balancer.h"
#include "News.h"
#include "Command.h"
#include "Querys.h"
#include "Reset.h"
#include "Master.h"
#include "Buffs.h"
#include "Teleport.h"
#include "Message.h"
#include "License.h"
#include "Authority.h"
#include "Display.h"
#include "Bronze.h"
#include "Steel.h"
#include "Black.h"
#include "Silver.h"
#include "Golden.h"
#include "Disconnect.h"
#include "Unicode.h"
#include "Speed.h"
#include "Attack.h"
#include "Bank.h"
#include "Collector.h"
#include "Bonus.h"
#include "Rank.h"
#include "Potion.h"
#include "Optimize.h"
#include "Roleta.h"
#include "MuMsg.h"
#include "Flood.h"
#include "Duel.h"
#include "Quest.h"
#include "Pick.h"


#pragma comment( lib , "wsock32.lib")
#pragma comment( lib , "ws2_32.lib")
#pragma comment( lib , "COMCTL32.lib")
#pragma comment( lib , "rpcrt4.lib")