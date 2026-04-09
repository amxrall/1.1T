// GuardianStatue.cpp: implementation of the CGuardianStatue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GuardianStatue.h"
#include "user.h"

#if (GS_CASTLE==1)
CGuardianStatue g_CsNPC_GuardianStatue;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGuardianStatue::CGuardianStatue()
{
}

CGuardianStatue::~CGuardianStatue()
{
}

void CGuardianStatue::GuardianStatueAct(int iIndex)
{
	if (::gObjIsConnected(iIndex) == FALSE)
		return;

	LPOBJ lpObj = &gObj[iIndex];

	if (lpObj->VPCount < 1)
		return;

	int tObjNum = -1;

	for (int i = 0; i < MAX_VIEWPORT; i++)
	{
		tObjNum = lpObj->VpPlayer[i].number;

		if (tObjNum >= 0)
		{
			if (gObj[tObjNum].Type == OBJ_USER)
			{
				if (gObj[tObjNum].Live != FALSE) //HermeX Fix
				{
					if (gObj[tObjNum].m_btCsJoinSide == 1) //3D9AB2E - 3D995F8
					{
						//3D99702 - 3D995F8									//3D99700 - 3D995F8
						if (abs(lpObj->Y - gObj[tObjNum].Y) <= 3 && abs(lpObj->X - gObj[tObjNum].X) <= 3) //HermeX Fix
						{
							BOOL bIsMaxLife = FALSE;
							BOOL bIsMaxMana = FALSE;
							BOOL bIsMaxBP = FALSE;

							//3D996B8 - 3D995F8			//3D996BC - 3D995F8			//3D99708 - 3D995F8
							if (gObj[tObjNum].Life < (gObj[tObjNum].MaxLife + gObj[tObjNum].AddLife)) //HermeX Fix
							{
								gObj[tObjNum].Life += ((gObj[tObjNum].MaxLife + gObj[tObjNum].AddLife) * (lpObj->m_btCsNpcRgLevel + 1) / 100); //HermeX Fix

								if (gObj[tObjNum].Life > (gObj[tObjNum].MaxLife + gObj[tObjNum].AddLife)) //HermeX Fix
								{
									gObj[tObjNum].Life = gObj[tObjNum].MaxLife + gObj[tObjNum].AddLife; //HermeX Fix
								}
								bIsMaxLife = TRUE;
							}
							//3D996CC - 3D995F8			//3D996D0 - 3D995F8			//3D9970C - 3D995F8
							if (gObj[tObjNum].Mana < (gObj[tObjNum].MaxMana + gObj[tObjNum].AddMana)) //HermeX Fix
							{
								gObj[tObjNum].Mana += ((gObj[tObjNum].MaxMana + gObj[tObjNum].AddMana) * (lpObj->m_btCsNpcRgLevel + 1)) / 100; //HermeX Fix

								if (gObj[tObjNum].Mana > (gObj[tObjNum].MaxMana + gObj[tObjNum].AddMana)) //HermeX Fix
								{
									gObj[tObjNum].Mana = gObj[tObjNum].MaxMana + gObj[tObjNum].AddMana; //HermeX Fix
								}
								bIsMaxMana = TRUE; //HermeX Fix
							}
							//3D996E4 - 3D995F8			//3D996EC - 3D995F8			//3D996E8 - 3D995F8
							if (gObj[tObjNum].BP < (gObj[tObjNum].MaxBP + gObj[tObjNum].AddBP))
							{
								gObj[tObjNum].BP += ((gObj[tObjNum].MaxBP + gObj[tObjNum].AddBP) * (lpObj->m_btCsNpcRgLevel + 1) / 100); //HermeX Fix

								if (gObj[tObjNum].BP > (gObj[tObjNum].MaxBP + gObj[tObjNum].AddBP)) //HermeX Fix
								{
									gObj[tObjNum].BP = gObj[tObjNum].MaxBP + gObj[tObjNum].AddBP; //HermeX Fix
								}
								bIsMaxBP = TRUE; //HermeX Fix
							}

							if (bIsMaxLife != FALSE) //HermeX Fix
							{
								::GCReFillSend(tObjNum, gObj[tObjNum].Life, 0xFF, 1);
							}
							if (bIsMaxMana != FALSE || bIsMaxBP != FALSE) //HermeX Fix
							{
								::GCManaSend(tObjNum, gObj[tObjNum].Mana, 0xFF, 0, gObj[tObjNum].BP); //HermeX Fix
							}
						}
					}
				}
			}
		}
	}
}

#endif