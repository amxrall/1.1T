#include "stdafx.h"
#include "Mercenary.h"
#include "protocol.h"
#include "GameMain.h"
#include "LogProc.h"
// GS-N 0.99.60T 0x0051A200
/*	GS-N	1.00.18	JPN	0x0054BB70	-	Completed
		BOOL CMercenary::CreateMercenary(int iIndex, int iMercenaryTypeIndex, BYTE cTX, BYTE cTY) Weird Compilation
	*/

#if(GS_CASTLE==1)
#include "CastleSiegeSync.h"
#endif

CMercenary g_CsNPC_Mercenary;

CMercenary::CMercenary()
{
	this->m_iMercenaryCount = 0;
}

CMercenary::~CMercenary()
{
	return;
}

BOOL CMercenary::CreateMercenary(int iIndex, int iMercenaryTypeIndex, BYTE cTX, BYTE cTY)
{
	LPOBJ lpObj = &gObj[iIndex];
	int iMonsterIndex = -1;
	BYTE cX = cTX;
	BYTE cY = cTY;

	BYTE btMapAttr = MapC[lpObj->MapNumber].GetAttr(cX, cY);

	if (lpObj->MapNumber != MAP_INDEX_CASTLESIEGE)
	{
		::MsgOutput(iIndex, lMsg.Get(MSGGET(6, 91)));

		return FALSE;
	}

#if(GS_CASTLE==1) //HermeX Decompilation 100%
	if (g_CastleSiegeSync.GetCastleState() != 7)
	{
		::MsgOutput(iIndex, lMsg.Get(1630));
		return FALSE;
	}

	if (iMercenaryTypeIndex == 286 || iMercenaryTypeIndex == 287)
	{
		if (lpObj->m_btCsJoinSide != 1)
		{
			::MsgOutput(iIndex, lMsg.Get(1628));
			return FALSE;
		}
		if (lpObj->GuildStatus != 128 && lpObj->GuildStatus != 64)
		{
			::MsgOutput(iIndex, lMsg.Get(1629));
			return FALSE;
		}
	}

	if (this->m_iMercenaryCount > 100)
	{
		::MsgOutput(iIndex, lMsg.Get(1631));
		return FALSE;
	}

	iMonsterIndex = gObjAddMonster(lpObj->MapNumber);

	if (iMonsterIndex >= 0)
	{
		LPMONSTER_ATTRIBUTE lpattr = gMAttr.GetAttr(iMercenaryTypeIndex);

		if (lpattr == NULL)
		{
			gObjDel(iMonsterIndex);
			return FALSE;
		}

		gObjSetMonster(iMonsterIndex, iMercenaryTypeIndex);

		//3D9965E - 3D995F8
		gObj[iMonsterIndex].Live = 1; //100%

		//3D996B8 - 3D995F8
		gObj[iMonsterIndex].Life = lpattr->m_Hp; //100%

		//3D996BC - 3D995F8
		gObj[iMonsterIndex].MaxLife = lpattr->m_Hp; //100%

		//3D99828 - 3D995F8
		gObj[iMonsterIndex].m_PosNum = -1; //100%

		//3D99700 - 3D995F8
		gObj[iMonsterIndex].X = cX; //100%

		//3D99702 - 3D995F8
		gObj[iMonsterIndex].Y = cY; //100%

		//3D9973C - 3D995F8
		gObj[iMonsterIndex].MTX = cX; //100%

		//3D9973E - 3D995F8
		gObj[iMonsterIndex].MTY = cY; //100%

		//3D99738 - 3D995F8
		gObj[iMonsterIndex].TX = cX; //100%

		//3D9973A - 3D995F8
		gObj[iMonsterIndex].TY = cY; //100%

		//3D99734 - 3D995F8
		gObj[iMonsterIndex].m_OldX = cX; //100%

		//3D99736 - 3D995F8
		gObj[iMonsterIndex].m_OldY = cY; //100%

		//3D99732 - 3D995F8
		gObj[iMonsterIndex].StartX = cX; //100%

		//3D99733 - 3D995F8
		gObj[iMonsterIndex].StartY = cY; //100%

		//3D99705 - 3D995F8
		gObj[iMonsterIndex].MapNumber = lpObj->MapNumber; //100%

		//3D99936 - 3D995F8
		gObj[iMonsterIndex].m_MoveRange = 0; //100%

		//3D99698 - 3D995F8
		gObj[iMonsterIndex].Level = lpattr->m_Level; //100%

		//3D9965C - 3D995F8
		gObj[iMonsterIndex].Type = 2; //100%

		//3D99824 - 3D995F8
		gObj[iMonsterIndex].MaxRegenTime = 1000; //100%

		//3D99704 - 3D995F8
		gObj[iMonsterIndex].Dir = 1; //100%

		//3D99820 - 3D995F8
		gObj[iMonsterIndex].RegenTime = GetTickCount(); //100%

		//3D9993E - 3D995F8
		gObj[iMonsterIndex].m_Attribute = 0; //100%

		//3D9981A - 3D995F8
		gObj[iMonsterIndex].DieRegen = 0; //100%

		//3D9AB24 - 3D995F8
		gObj[iMonsterIndex].m_btCsNpcType = 2; //100%

		//3D9AB2E - 3D995F8
		gObj[iMonsterIndex].m_btCsJoinSide = 1; //100%

		::MsgOutput(iIndex, lMsg.Get(1632));

		this->m_iMercenaryCount++;

		if (lpObj->lpGuild != NULL)
		{
			LogAdd("[CastleSiege] Mercenary is summoned [%d] - [%d][%d] [%s][%s][%d] - (Guild : %s)", iMonsterIndex, iMercenaryTypeIndex, this->m_iMercenaryCount, lpObj->AccountID, lpObj->Name, lpObj->GuildStatus, lpObj->lpGuild->Name);
		}
		else
		{
			LogAdd("[CastleSiege] Mercenary is summoned [%d] - [%d][%d] [%s][%s][%d]", iMonsterIndex, iMercenaryTypeIndex, this->m_iMercenaryCount, lpObj->AccountID, lpObj->Name, lpObj->GuildStatus);
		}
	}
	else
	{
		::MsgOutput(iIndex, lMsg.Get(1633));
		return FALSE;
	}
#endif
	return TRUE;
}

BOOL CMercenary::DeleteMercenary(int iIndex)
{
	if (iIndex < 0 || iIndex > OBJMAX - 1)
	{
		return FALSE;
	}

	this->m_iMercenaryCount--;

	LogAdd("[CastleSiege] Mercenary is broken [%d] - [%d]", iIndex, this->m_iMercenaryCount);

	if (this->m_iMercenaryCount < 0)
	{
		this->m_iMercenaryCount = 0;
	}

	return TRUE;
}

int  CMercenary::SearchEnemy(LPOBJ lpObj)
{
#if(GS_CASTLE==1)
	int iTargetNumber = -1;
	int iAttackRange = 0;

	lpObj->TargetNumber = -1;

	if (lpObj->Class == 286)
	{
		iAttackRange = 5;
	}
	else if (lpObj->Class == 287)
	{
		iAttackRange = 3;
	}

	int i;
	for (i = 0; i < MAX_VIEWPORT; i++)
	{
		iTargetNumber = lpObj->VpPlayer2[i].number;

		if (iTargetNumber >= 0 && gObj[iTargetNumber].Type == 1 && gObj[iTargetNumber].Live != FALSE && gObj[iTargetNumber].Teleport == FALSE)
		{
			if (gObj[iTargetNumber].m_btCsJoinSide == lpObj->m_btCsJoinSide)
			{
				continue;
			}

			//Mr.Marin Decompilation 100%
			int iTargetDisX = lpObj->X - gObj[iTargetNumber].X;
			int iTargetDisY = lpObj->Y - gObj[iTargetNumber].Y;
			int iTargetDist;
			int cY;
			int cX;
			int SquareDist = (iTargetDisX*iTargetDisX) + (iTargetDisY*iTargetDisY);

			iTargetDist = int(sqrt(float(SquareDist)));

			lpObj->VpPlayer2[i].dis = iTargetDist;

			if (lpObj->Dir == 1 && abs(iTargetDisX) <= 2)
			{
				cY = lpObj->Y - iAttackRange;
				if (cY <= gObj[iTargetNumber].Y)
				{
					if (lpObj->Y >= gObj[iTargetNumber].Y)
					{
						lpObj->TargetNumber = iTargetNumber;
						return 1;
					}
				}
			}

			if (lpObj->Dir == 3 && abs(iTargetDisY) <= 2)
			{
				cX = lpObj->X - iAttackRange;
				if (cX <= gObj[iTargetNumber].X)
				{
					if (lpObj->X >= gObj[iTargetNumber].X)
					{
						lpObj->TargetNumber = iTargetNumber;
						return 1;
					}
				}
			}
		}
	}
#endif
	return 0;
}

void CMercenary::MercenaryAct(int iIndex)
{
	if (::gObjIsConnected(iIndex) == FALSE)
	{
		return;
	}

	LPOBJ lpObj = &gObj[iIndex];

	if (lpObj->VPCount2 < 1)
	{
		return;
	}

	if (this->SearchEnemy(lpObj) != 0 && lpObj->TargetNumber >= 0)
	{
		lpObj->m_ActState.Attack = 1;
		lpObj->NextActionTime = lpObj->m_AttackSpeed;
	}
	else
	{
		lpObj->NextActionTime = lpObj->m_MoveSpeed;
	}
}