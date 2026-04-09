#include "stdafx.h"
#include "GMMng.h"
#include "LogProc.h"
#include "GameMain.h"
#include "protocol.h"
#include "winutil.h"
#include "MoveCommand.h"
#include "GuildClass.h"
#include "TNotice.h"
#include "BattleSoccerManager.h"
#include "giocp.h"
#include "SkillAdditionInfo.h"
#include "ObjCalCharacter.h"
#include "DSProtocol.h"

CGMMng cManager;

CGMMng::CGMMng()
{
	this->ManagerInit();
}

CGMMng::~CGMMng()
{
	return;
}

void CGMMng::Init() //Identical
{
	this->cCommand.Init();

	this->cCommand.Add(lMsg.Get(MSGGET(11, 184)), 100);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 185)), 101);
	//this->cCommand.Add(lMsg.Get(MSGGET(11, 186)), 102);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 187)), 103);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 188)), 105);
	//this->cCommand.Add(lMsg.Get(MSGGET(11, 189)), 104);

	//this->cCommand.Add(lMsg.Get(MSGGET(11, 190)), 106);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 191)), 108);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 192)), 112);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 193)), 111);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 194)), 109);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 195)), 110);

	//this->cCommand.Add(lMsg.Get(MSGGET(11, 197)), 201);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 198)), 200);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 199)), 202);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 200)), 203);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 204)), 100);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 205)), 101);
	this->cCommand.Add("/gmove", 421); // /gmove
	this->cCommand.Add(lMsg.Get(MSGGET(11, 206)), 102);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 207)), 103);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 208)), 105);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 209)), 104);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 210)), 106);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 211)), 108);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 212)), 112);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 213)), 111);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 214)), 109);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 215)), 110);

	//this->cCommand.Add(lMsg.Get(MSGGET(11, 217)), 201);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 218)), 200);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 219)), 202);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 220)), 203);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 201)), 214);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 202)), 215);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 203)), 216);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 221)), 214);
	//this->cCommand.Add(lMsg.Get(MSGGET(11, 222)), 215);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 223)), 216);

	// KUNDUN Commands
	this->cCommand.Add("/쿤둔상태", 320);	// #translation
	this->cCommand.Add("/쿤둔피", 321);	// #translation
	this->cCommand.Add("/쿤둔회복량", 322);	// #translation
	this->cCommand.Add("/쿤둔초당회복량", 323);	// #translation
	this->cCommand.Add("/쿤둔회복시간", 324);	// #translation

#if(GS_CASTLE == 1)
	// CASTLESIEGE Commands
	this->cCommand.Add("/cschangeowner", 331);
	this->cCommand.Add("/cssetregsiege", 332);
	this->cCommand.Add("/cssetregmark", 333);
	this->cCommand.Add("/cssetnotify", 334);
	this->cCommand.Add("/cssetstart", 335);
	this->cCommand.Add("/cssetend", 336);
	this->cCommand.Add("/cscurowner", 337);
	this->cCommand.Add("/cscurstate", 338);
	this->cCommand.Add("/cschangeside", 340);

	// CRYWOLF Commands
	this->cCommand.Add(lMsg.Get(3338), 345);
	this->cCommand.Add(lMsg.Get(3339), 346);
	this->cCommand.Add(lMsg.Get(3340), 347);
	this->cCommand.Add(lMsg.Get(3341), 348);
#endif

	this->cCommand.Add("/fcracker", 217);	// Fire Cracker Effect	// #translation

	this->WatchTargetIndex = -1;
}

void CGMMng::ManagerInit()
{
	for (int n = 0; n < MAX_GAME_MASTER; n++)
	{
		this->ManagerIndex[n] = -1;
	}
}

int CGMMng::ManagerAdd(char* name, int aIndex)
{
	for (int n = 0; n < MAX_GAME_MASTER; n++)
	{
		if (this->ManagerIndex[n] == -1)
		{
			strcpy(this->szManagerName[n], name);
			this->ManagerIndex[n] = aIndex;
			return n;
		}
	}

	return -1;
}

void CGMMng::ManagerDel(char* name)
{
	for (int n = 0; n < MAX_GAME_MASTER; n++)
	{
		if (this->ManagerIndex[n] != -1)
		{
			if (strcmp(this->szManagerName[n], name) == 0)
			{
				this->ManagerIndex[n] = -1;
				return;
			}
		}
	}
}

void CGMMng::ManagerSendData(LPSTR szMsg, int size)
{
	for (int n = 0; n < MAX_GAME_MASTER; n++)
	{
		if (this->ManagerIndex[n] != -1)
		{
			GCServerMsgStringSend(szMsg, this->ManagerIndex[n], 0);
		}
	}
}

void CGMMng::DataSend(unsigned char* szMsg, int size)
{
	for (int n = 0; n < MAX_GAME_MASTER; n++)
	{
		if (this->ManagerIndex[n] != -1)
		{
			::DataSend(this->ManagerIndex[n], szMsg, size);
		}
	}
}

void CGMMng::BattleInfoSend(char* Name1, BYTE score1, char* Name2, BYTE score2)
{
	for (int n = 0; n < MAX_GAME_MASTER; n++)
	{
		if (this->ManagerIndex[n] != -1)
		{
			GCGoalSend(this->ManagerIndex[n], Name1, score1, Name2, score2);
		}
	}
}

int CGMMng::GetCmd(char* szCmd)
{
	for (int n = 0; n < MAX_GM_COMMAND; n++)
	{
		if (this->cCommand.nCmdCode[n] > 0)
		{
			if (_stricmp(szCmd, this->cCommand.szCmd[n]) == 0)
			{
				return this->cCommand.nCmdCode[n];
			}
		}
	}

	return 0;
}

char* CGMMng::GetTokenString()
{
	//Original Code (GS 0.65)
	char seps[] = " ";
	return strtok(NULL, seps);
}

int CGMMng::GetTokenNumber()
{
	char seps[] = " ";
	char * szToken;

	szToken = strtok(NULL, seps);

	if (szToken != NULL)
	{
		return atoi(szToken);
	}
	return 0;
}

int CGMMng::ManagementProc(LPOBJ lpObj, char* szCmd, int aIndex) // Identical
{
	char seps[] = " ";
	char *szCmdToken;
	char string[256];
	char szId[20];
	char *pId = szId;

	char szMsg[256];

	int len = strlen(szCmd);
	if (len < 1 || len > 250) return FALSE;

	memset(szId, 0, 20);

	strcpy(string, szCmd);

	szCmdToken = strtok(string, seps);

	int command_number = GetCmd(szCmdToken);

	switch (command_number)
	{
	case 217:	//116:
		{
			if ((lpObj->Authority & 2) != 2 && (lpObj->Authority & 0x20) != 0x20)
			{
				return 0;
			}

			LogAdd("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, "FIRECRACK.");
			int x = lpObj->X;
			int y = lpObj->Y;
			PMSG_SERVERCMD pMsg;

			PHeadSubSetB((LPBYTE)&pMsg, 0xF3, 0x40, sizeof(pMsg));
			pMsg.CmdType = 0;

			for (int i = 0; i < 15; i++)
			{
				pMsg.X = x + (rand() % 5) * 2 - 4;
				pMsg.Y = y + (rand() % 5) * 2 - 4;
				MsgSendV2(lpObj, (UCHAR*)&pMsg, sizeof(pMsg));
				::DataSend(lpObj->m_Index, (UCHAR*)&pMsg, sizeof(pMsg));
			}
		}
		break;

	case 216:	//115:
		{
			if ((lpObj->Authority & 2) != 2 && (lpObj->Authority & 0x20) != 0x20)
			{
				return 0;
			}

			pId = this->GetTokenString();

			if (pId == NULL)
			{
				return 0;
			}

			LPOBJ lpTargetObj = gObjFind(pId);

			if (lpTargetObj == NULL)
			{
				return 0;
			}

			LogAdd("Use GM Command -> [ %s ]	[ %s ]	[ %s ] / Target : [%s][%s] : %s ",
				lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, lpTargetObj->AccountID,
				lpTargetObj->Name, "User Watching");

			char szTemp[256];

			if (this->WatchTargetIndex == lpTargetObj->m_Index)
			{
				this->WatchTargetIndex = -1;

				wsprintf(szTemp, "%s : 감시해제", lpTargetObj->Name);	// #translation
				GCServerMsgStringSend(szTemp, lpObj->m_Index, 1);
			}
			else
			{
				wsprintf(szTemp, "%s : 감시시작", lpTargetObj->Name);	// #translation
				GCServerMsgStringSend(szTemp, lpObj->m_Index, 1);
				this->WatchTargetIndex = lpTargetObj->m_Index;
			}
		}
		break;

	case 215:	//114:
		{
			if (lpObj->Authority != 32)
			{
				return 0;
			}

			pId = this->GetTokenString();

			if (pId == NULL)
			{
				return 0;
			}

			int map;
			int iX;
			int iY;
			LPOBJ lpTargetObj = gObjFind(pId);
			int iIndex;

			if (lpTargetObj == NULL)
			{
				return 0;
			}

			LogAdd("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] / Target : [%s][%s] : %s",
				lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, lpTargetObj->AccountID,
				lpTargetObj->Name, "User Tracking");
			map = lpTargetObj->MapNumber;
			iX = lpTargetObj->X;
			iY = lpTargetObj->Y;
			iIndex = lpObj->m_Index;

			if (iIndex >= 0)
			{
				gObjTeleport(iIndex, map, iX, iY);
			}
		}
		break;

	case 214:	//113:
		{
			if ((lpObj->Authority & 2) != 2)
			{
				return 0;
			}

			LogAdd("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
				lpObj->Ip_addr, lpObj->AccountID, lpObj->Name,
				"User Stat (connection)");

			int lc151 = 0;
			int lc152 = 400;
			int iTokenNumber = this->GetTokenNumber();

			if (iTokenNumber > 0)
			{
				lc151 = iTokenNumber;
			}

			int iTokenNumber2 = this->GetTokenNumber();

			if (iTokenNumber2 > 0)
			{
				lc152 = iTokenNumber2;
			}

			gObjSendUserStatistic(lpObj->m_Index, lc151, lc152);
		}
		break;

	case 100:	//100:
		{
			if (lpObj->Authority != 32)
			{
				return 0;
			}

			pId = this->GetTokenString();

			if (pId == NULL)
			{
				return 0;
			}

			int iTargetIndex = gObjGetIndex(pId);

			if (iTargetIndex >= 0)
			{
				LPOBJ lpTargetObj = gObjFind(pId);

				if (lpTargetObj == NULL)
				{
					return 0;
				}

				LogAdd("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] / Target : [%s][%s] : %s",
					lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, lpTargetObj->AccountID,
					lpTargetObj->Name, "User Disconnect");
				LogAdd(lMsg.Get(MSGGET(1, 191)), pId);
				CloseClient(iTargetIndex);
			}
		}
		break;

	case 112:	//108:
		{
			if ((lpObj->AuthorityCode & 4) != 4)
			{
				return 0;
			}

			LogAdd("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
				lpObj->Ip_addr, lpObj->AccountID, lpObj->Name,
				"Guild Disconnect");

			pId = this->GetTokenString();

			if (pId == NULL)
			{
				return 0;
			}

			_GUILD_INFO_STRUCT * lpGuild = Guild.SearchGuild(pId);
			int iIndex;

			if (lpGuild != NULL)
			{
				for (int i = 0; i < MAX_USER_GUILD; i++)
				{
					if (lpGuild->Index[i] >= 0)
					{
						iIndex = lpGuild->Index[i];

						if (iIndex >= 0)
						{
							LogAdd(lMsg.Get(MSGGET(1, 191)), pId);
							CloseClient(iIndex);
						}
					}
				}
			}
		}
		break;

	case 421: // /gmove
		{
			if ((lpObj->AuthorityCode & 8) == 8)
			{
				pId = this->GetTokenString();

				if (pId == NULL)
				{
					return 0;
				}

				int iTokenNumber1 = this->GetTokenNumber();
				int iTokenNumber2 = this->GetTokenNumber();
				int iTokenNumber3 = this->GetTokenNumber();
				int iIndex = gObjGetIndex(pId);
				LPOBJ lpTargetObj;

				if (iIndex >= 0)
				{
					lpTargetObj = gObjFind(pId);

					if (lpTargetObj == NULL)
					{
						return 0;
					}

					LogAdd("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] / Target : [%s][%s] : %s",
						lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, lpTargetObj->AccountID,
						lpTargetObj->Name, "User SetPosition");

					gObjTeleport(iIndex, iTokenNumber1, iTokenNumber2, iTokenNumber3);
				}
			}
		}
		break;
	case 101:	//101: // move
		{
			pId = this->GetTokenString();

			if (pId != NULL)
			{
				int lc165 = -1;
				int lc166 = 0;
				int lc167 = 0;

				if (lpObj->Teleport != 0)
				{
					GCServerMsgStringSend(lMsg.Get(MSGGET(6, 68)), lpObj->m_Index, 1);
					return 0;
				}

				if ((lpObj->m_IfState.use) != 0)
				{
					if (lpObj->m_IfState.type == 3)
					{
						lpObj->TargetShopNumber = -1;
						lpObj->m_IfState.type = 0;
						lpObj->m_IfState.use = 0;
					}
				}

				if (lpObj->m_IfState.use > 0)
				{
					GCServerMsgStringSend(lMsg.Get(MSGGET(6, 68)), lpObj->m_Index, 1);
					return 0;
				}

				if (gObj[aIndex].IsInBattleGround != false)
				{
					GCServerMsgStringSend(lMsg.Get(MSGGET(6, 68)), lpObj->m_Index, 1);
					return 0;
				}

				if (lpObj->m_PK_Level >= 6)
				{
					GCServerMsgStringSend(lMsg.Get(MSGGET(4, 101)), lpObj->m_Index, 1);
					return 0;
				}

				gMoveCommand.Move(lpObj, pId);
			}
		}
		break;

	case 108:	//104:
		{
			if ((lpObj->AuthorityCode & 8) != 8)
			{
				return 0;
			}

			LogAdd("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
				lpObj->Ip_addr, lpObj->AccountID, lpObj->Name,
				"Guild SetPosition");

			pId = this->GetTokenString();

			if (pId == NULL)
			{
				return 0;
			}

			int iTokenNumber1 = this->GetTokenNumber();
			int iTokenNumber2 = this->GetTokenNumber();
			int iTokenNumber3 = this->GetTokenNumber();
			_GUILD_INFO_STRUCT* lpGuild = Guild.SearchGuild(pId);
			int iIndex;

			if (lpGuild != NULL)
			{
				for (int i = 0; i < MAX_USER_GUILD; i++)
				{
					if (lpGuild->Index[i] >= 0)
					{
						iIndex = lpGuild->Index[i];
						gObjTeleport(iIndex, iTokenNumber1, iTokenNumber2++, iTokenNumber3);
					}
				}
			}
		}
		break;

	case 109:	//105:
		{
			if ((lpObj->Authority & 2) == 2)
			{
				LogAdd("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
					lpObj->Ip_addr, lpObj->AccountID, lpObj->Name,
					"Start BattleSoccer");

				BattleSoccerGoalStart(0);
			}
		}
		break;

	case 110:	//106:
		{
			if ((lpObj->Authority & 2) == 2)
			{
				LogAdd("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
					lpObj->Ip_addr, lpObj->AccountID, lpObj->Name,
					"Stop BattleSoccer");

				BattleSoccerGoalEnd(0);
			}
			else
			{
				if (gObj[aIndex].lpGuild != NULL)
				{
					if (gObj[aIndex].lpGuild->WarType == 1)
					{
						strcmp(gObj[aIndex].Name, gObj[aIndex].lpGuild->Names[0]);
					}
				}
			}
		}

		break;

	case 111:	//107:
		{
			if ((lpObj->Authority & 2) == 2)
			{
				LogAdd("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
					lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, "End GuildWar");

				char * szGuild = this->GetTokenString();

				if (szGuild != NULL)
				{
					GCManagerGuildWarEnd(szGuild);
				}
			}
			else
			{
				if (gObj[aIndex].lpGuild != NULL && gObj[aIndex].lpGuild->lpTargetGuildNode != NULL)
				{
					if (strcmp(gObj[aIndex].Name, gObj[aIndex].lpGuild->Names[0]) == 0)
					{
						if (gObj[aIndex].lpGuild->BattleGroundIndex >= 0 && gObj[aIndex].lpGuild->WarType == 1)
						{
							::gObjAddMsgSendDelay(&gObj[aIndex], 7, aIndex, 10000, 0);

							char szTemp[100];

							wsprintf(szTemp, lMsg.Get(MSGGET(4, 129)), gObj[aIndex].lpGuild->Names[0]);
							::GCServerMsgStringSendGuild(gObj[aIndex].lpGuild, szTemp, 1);
							::GCServerMsgStringSendGuild(gObj[aIndex].lpGuild->lpTargetGuildNode, szTemp, 1);
						}
					}
				}
			}
		}
		break;
	case 102:
		{
			int x;
			int y;
			if (lpObj->Authority != 32)
			{
				return FALSE;
			}

			LogAdd("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, "cmd /trans");

			pId = this->GetTokenString();

			if (pId == NULL)
			{
				return FALSE;
			}

			int Index = ::gObjGetIndex(pId);

			if (Index >= 0)
			{
				x = lpObj->X + (rand() % 2);
				y = lpObj->Y + (rand() % 2);
				gObjTeleport(Index, lpObj->MapNumber, x, y);
				LogAdd("Use GM Command -> [ %s ] [ %s ] [ %s ] : %s Target [Name %s ] [Map %d ] [X/Y %d %d ] ",
					lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, "cmd /trans", gObj[Index].Name, gObj[Index].MapNumber, gObj[Index].X, gObj[Index].Y);
			}
		}
		break;
	case 104:	//102:
		{
			if ((lpObj->AuthorityCode & 0x20) != 0x20)
			{
				return FALSE;
			}

			LogAdd("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
				lpObj->Name, "Ban Chatting");

			pId = this->GetTokenString();

			if (pId == NULL)
			{
				return FALSE;
			}

			int Index = ::gObjGetIndex(pId);

			if (Index >= 0)
			{
				gObj[Index].Penalty |= 2;
			}
		}
		break;

	case 106:	//103:
		{
			if ((lpObj->AuthorityCode & 32) != 32)
			{
				return FALSE;
			}

			LogAdd("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
				lpObj->Name, "Free Ban-Chatting");

			pId = this->GetTokenString();

			if (pId == NULL)
			{
				return FALSE;
			}

			int Index = ::gObjGetIndex(pId);

			if (Index >= 0)
			{
				gObj[Index].Penalty &= ~2;
			}
		}
		break;

	case 200:	//109:
		{
			pId = this->GetTokenString();

			if (pId != NULL)
			{
				if (strlen(pId) >= 1)
				{
					::GCGuildWarRequestResult(pId, aIndex, 0);
				}
			}
		}

		break;

	case 202:	//111:
		{
			if ((lpObj->Authority & 2) == 2)
			{
				LogAdd("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
					lpObj->Name, "Set GuildWar");

				pId = this->GetTokenString();

				if (pId != NULL)
				{
					char * Rival = this->GetTokenString();

					if (Rival != NULL)
					{
						if (strlen(pId) >= 1)
						{
							if (strlen(Rival) >= 1)
							{
								::GCManagerGuildWarSet(pId, Rival, 1);
							}
						}
					}
				}
			}
			else
			{
				if (gEnableBattleSoccer != FALSE)
				{
					pId = this->GetTokenString();

					if (pId != NULL)
					{
						if (strlen(pId) >= 1)
						{
							::GCGuildWarRequestResult(pId, aIndex, 1);
						}
					}
				}
			}
		}

		break;

	case 203:	//112:
		{
			pId = this->GetTokenString();

			if (pId != NULL)
			{
				BOOL bState = FALSE; //Crash bState = FALSE.

				if (strcmp(pId, "on") == 0)
				{
					bState = TRUE;
				}
				else if (strcmp(pId, "off") == 0)
				{
					bState = FALSE;
				}

				if (bState >= FALSE && bState <= TRUE)
				{
					::gObjSetTradeOption(aIndex, bState);
					::gObjSetDuelOption(aIndex, bState);
				}
			}
		}
		break;

	case 320:	//117:
		{
			if ((lpObj->Authority & 2) != 2)
			{
				return FALSE;
			}

			LogAdd("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
				lpObj->Name, "쿤둔상태보기");	// #translation Require Translation

			for (int n = 0; n < MAX_VIEWPORT; n++)
			{
				if (lpObj->VpPlayer[n].state != 0)
				{
					if (lpObj->VpPlayer[n].type == OBJ_MONSTER)
					{
						if (lpObj->VpPlayer[n].number >= 0)
						{
							LPOBJ lpTarget = &gObj[lpObj->VpPlayer[n].number];

							if (lpTarget->Class == 275)
							{
								TNotice pNotice(1);

								pNotice.SendToUser(lpObj->m_Index, "쿤둔 HP = %7.0f / %7.0f", lpTarget->Life, lpTarget->MaxLife); //Require Translation
								pNotice.SendToUser(lpObj->m_Index, "쿤둔 HP 초당회복량 = %d 회복량 = %d 회복시간 = %d", giKundunRefillHPSec, giKundunRefillHP, giKundunRefillHPTime);	// Require Translation
							}
						}
					}
				}
			}
		}
		break;

	case 321:	//118:
		{
			if ((lpObj->Authority & 2) != 2)
			{
				return FALSE;
			}

			LogAdd("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
				lpObj->Name, "쿤둔HP설정");	// Require Translation

			int iLife = this->GetTokenNumber();

			for (int n = 0; n < MAX_VIEWPORT; n++)
			{
				if (lpObj->VpPlayer[n].state != FALSE)
				{
					if (lpObj->VpPlayer[n].type == OBJ_MONSTER)
					{
						if (lpObj->VpPlayer[n].number >= 0)
						{
							LPOBJ lpTarget = &gObj[lpObj->VpPlayer[n].number];

							if (lpTarget->Class == 275)
							{
								if (iLife <= 5000)
								{
									iLife = 5000;
								}

								if (iLife > lpTarget->MaxLife)
								{
									iLife = lpTarget->MaxLife;
								}

								lpTarget->Life = iLife;

								TNotice pNotice(1);

								pNotice.SendToUser(lpObj->m_Index, "쿤둔 HP = %7.0f / %7.0f", lpTarget->Life, lpTarget->MaxLife); //Require Translation
							}
						}
					}
				}
			}
		}
		break;

	case 322:	//119:
		{
			if ((lpObj->Authority & 2) != 2)
			{
				return FALSE;
			}

			LogAdd("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
				lpObj->Name, "쿤둔HP회복량설정");	// Require Translation

			int RefillHP = this->GetTokenNumber();

			if (RefillHP <= 0 || RefillHP > 5000000)
			{
				return 0;
			}

			giKundunRefillHP = RefillHP;

			TNotice pNotice(0);

			pNotice.SendToUser(lpObj->m_Index, "쿤둔 HP 초당회복량 = %d 회복량 = %d 회복시간 = %d", giKundunRefillHPSec, giKundunRefillHP, giKundunRefillHPTime);	// Require Translation
		}

		break;

	case 323:	//120:
		{
			if ((lpObj->Authority & 2) != 2)
			{
				return FALSE;
			}

			LogAdd("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
				lpObj->Name, "쿤둔HP초당회복량설정");	// Require Translation

			int RefillHPSec = this->GetTokenNumber();

			if (RefillHPSec <= 0 || RefillHPSec > 10000)
			{
				return 0;
			}

			giKundunRefillHPSec = RefillHPSec;

			TNotice pNotice(0);

			pNotice.SendToUser(lpObj->m_Index, "쿤둔 HP 초당회복량 = %d 회복량 = %d 회복시간 = %d",
				giKundunRefillHPSec, giKundunRefillHP, giKundunRefillHPTime);	// Require Translation
		}

		break;

	case 324:	//121:
		{
			if ((lpObj->Authority & 2) != 2)
			{
				return FALSE;
			}

			LogAdd("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
				lpObj->Name, "쿤둔HP회복시간설정");	// Require Translation

			int RefillHPTime = this->GetTokenNumber();

			if (RefillHPTime < 0 || RefillHPTime > 60000)
			{
				return 0;
			}

			giKundunRefillHPTime = RefillHPTime;

			TNotice pNotice(0);

			pNotice.SendToUser(lpObj->m_Index, "쿤둔 HP 초당회복량 = %d 회복량 = %d 회복시간 = %d", giKundunRefillHPSec, giKundunRefillHP, giKundunRefillHPTime);	// Require Translation
		}
		break;
#if(GS_CASTLE==1)
	case 331:
		char *szNewOwnerGuild;
		szNewOwnerGuild = this->GetTokenString();
		g_CastleSiege.OperateGmCommand(lpObj->m_Index, 0, szNewOwnerGuild);
		break;
	case 332:
		g_CastleSiege.OperateGmCommand(lpObj->m_Index, 1, 0);
		break;
	case 333:
		g_CastleSiege.OperateGmCommand(lpObj->m_Index, 2, 0);
		break;
	case 334:
		g_CastleSiege.OperateGmCommand(lpObj->m_Index, 3, 0);
		break;
	case 335:
		g_CastleSiege.OperateGmCommand(lpObj->m_Index, 4, 0);
		break;
	case 336:
		g_CastleSiege.OperateGmCommand(lpObj->m_Index, 5, 0);
		break;
	case 337:
		g_CastleSiege.OperateGmCommand(lpObj->m_Index, 6, 0);
		break;
	case 338:
		g_CastleSiege.OperateGmCommand(lpObj->m_Index, 7, 0);
		break;
	case 340:
		char *szGuildName;
		szGuildName = this->GetTokenString();
		g_CastleSiege.OperateGmCommand(lpObj->m_Index, 8, szGuildName);
		break;
#endif
	case 1000:
		{
			int Map = this->GetTokenNumber();
			int X = this->GetTokenNumber();
			int Y = this->GetTokenNumber();

			gObjTeleport(lpObj->m_Index, Map, X, Y);
		}
		break;
	}

	return 0;
}

void CGMMng::GetInfinityArrowMPConsumption(LPOBJ lpObj)
{
	MsgOutput(lpObj->m_Index, "인피니티 애로우 MP 소모량[+0:%d] [+1:%d] [+2:%d]",
		g_SkillAdditionInfo.GetInfinityArrowMPConsumptionPlus0(),
		g_SkillAdditionInfo.GetInfinityArrowMPConsumptionPlus1(),
		g_SkillAdditionInfo.GetInfinityArrowMPConsumptionPlus2());
}

void CGMMng::ControlInfinityArrowMPConsumption0(LPOBJ lpObj, int iValue)
{
	g_SkillAdditionInfo.SetInfinityArrowMPConsumptionPlus0(iValue);
	MsgOutput(lpObj->m_Index, "인피니티 애로우 MP 소모량 변경(+0) : %d", iValue);
}

void CGMMng::ControlInfinityArrowMPConsumption1(LPOBJ lpObj, int iValue)
{
	g_SkillAdditionInfo.SetInfinityArrowMPConsumptionPlus1(iValue);
	MsgOutput(lpObj->m_Index, "인피니티 애로우 MP 소모량 변경(+1) : %d", iValue);
}

void CGMMng::ControlInfinityArrowMPConsumption2(LPOBJ lpObj, int iValue)
{
	g_SkillAdditionInfo.SetInfinityArrowMPConsumptionPlus2(iValue);
	MsgOutput(lpObj->m_Index, "인피니티 애로우 MP 소모량 변경(+2) : %d", iValue);
}

void CGMMng::SetInfinityArrowTime(LPOBJ lpObj, int iValue)
{
	if (lpObj->Class == ELF && lpObj->Type == OBJ_USER && lpObj->ChangeUP == 1)
	{
		lpObj->m_iMuseElfInfinityArrowSkillTime = iValue;
		MsgOutput(lpObj->m_Index, "인피니티 애로우 시간 강제 설정 : %d초", iValue);
	}
	else
	{
		MsgOutput(lpObj->m_Index, "220레벨 이상 뮤즈엘프만 사용가능합니다.");
	}
}

void CGMMng::ControlFireScreamDoubleAttackDistance(LPOBJ lpObj, int iValue)
{
	g_SkillAdditionInfo.SetFireScreamExplosionAttackDistance(iValue);
	MsgOutput(lpObj->m_Index, "파이어스크림 더블데미지 폭발거리 변경:%d", iValue);
}