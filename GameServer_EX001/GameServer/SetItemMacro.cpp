// SetItemMacro.cpp: implementation of the CSetItemMacro class.
//	GS-N	1.00.18	JPN	0x0051ECB0
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SetItemMacro.h"
#include "readscript.h"
#include "zzzitem.h"
#include "SetItemOption.h"
#include "DSProtocol.h"
#include "user.h"
#include "LogProc.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSetItemMacro g_SetItemMacro;

CSetItemMacro::CSetItemMacro()
{
}

CSetItemMacro::~CSetItemMacro()
{
}

BOOL CSetItemMacro::Load(char * szFileName)
{
	if ((SMDFile = fopen(szFileName, "r")) == NULL)
	{
		LogAdd("í+ For BroadCasting Server Set Item Macro Load!!");
		return FALSE;
	}

	SMDToken Token;
	int n = 0;
	char szName[255];
	char szLog[255];
	int iSetIndex;
	int iType;
	int iIndex;
	int iLevel;
	int iSkill;
	int iLuck;
	int iOption;
	int iExOption1;
	int iExOption2;
	int iExOption3;
	int iExOption4;
	int iExOption5;
	int iExOption6;
	int i = 0;
	int iName = 0;

	Token = GetToken();

	while (1)
	{
		if (Token == END) break;

		if (Token == NAME)
		{
			strcpy(szName, "");
			sprintf(szLog, "%d - %s", iName, szName);
			this->bLoadItemName[iName] = TRUE;
			strcpy(this->sMakeItemName[iName], szName);
			OutputDebugString(szLog);

			Token = GetToken();
			i = 0;

			if (Token == END) break;

			do
			{
				iSetIndex = (int)TokenNumber;
				Token = GetToken();
				iType = (int)TokenNumber;
				Token = GetToken();
				iIndex = (int)TokenNumber;
				Token = GetToken();
				iLevel = (int)TokenNumber;
				Token = GetToken();
				iSkill = (int)TokenNumber;
				Token = GetToken();
				iLuck = (int)TokenNumber;
				Token = GetToken();
				iOption = (int)TokenNumber;
				Token = GetToken();
				iExOption1 = (int)TokenNumber;
				Token = GetToken();
				iExOption2 = (int)TokenNumber;
				Token = GetToken();
				iExOption3 = (int)TokenNumber;
				Token = GetToken();
				iExOption4 = (int)TokenNumber;
				Token = GetToken();
				iExOption5 = (int)TokenNumber;
				Token = GetToken();
				iExOption6 = (int)TokenNumber;

				this->SubItemList[iName][i].SetIndex = iSetIndex;
				this->SubItemList[iName][i].ItemIndex = ITEMGET(iType, iIndex);
				this->SubItemList[iName][i].Level = iLevel;
				this->SubItemList[iName][i].Skill = iSkill;
				this->SubItemList[iName][i].Luck = iLuck;
				this->SubItemList[iName][i].Option = iOption;
				this->SubItemList[iName][i].Ex1 = iExOption1;
				this->SubItemList[iName][i].Ex2 = iExOption2;
				this->SubItemList[iName][i].Ex3 = iExOption3;
				this->SubItemList[iName][i].Ex4 = iExOption4;
				this->SubItemList[iName][i].Ex5 = iExOption5;
				this->SubItemList[iName][i].Ex6 = iExOption6;

				wsprintf(szLog, "[%d] %s level:%d skill:%d luck:%d option:%d [%d,%d,%d,%d,%d,%d]",
					i,
					ItemAttribute[ITEMGET(iType, iIndex)].Name,
					iLevel,
					iSkill,
					iLuck,
					iOption,
					iExOption1,
					iExOption2,
					iExOption3,
					iExOption4,
					iExOption5,
					iExOption6);
				OutputDebugStringA(szLog);

				i += 1;
			}
			while ((Token = GetToken()) == NUMBER);

			iName += 1;
		}
		else
		{
			LogAdd("í+ For BroadCasting Server Set Item Macro Load!!");
			return FALSE;
		}
	}

	fclose(SMDFile);
	return TRUE;
}

BOOL CSetItemMacro::MakeItem(int aIndex, char * szSetName)
{
	BOOL bFindItem = FALSE;//8
	int i;//c

	for (i = 0; i < MAX_SET_ITEM_MACRO; i++)
	{
		if (this->bLoadItemName[i] != FALSE)
		{
			if (strcmp(this->sMakeItemName[i], szSetName) == NULL)
			{
				bFindItem = TRUE;

				for (int j = 0; j < 15; i++)
				{
					if (this->SubItemList[i][j].ItemIndex != NULL)
					{
						int iLevel = 0;//14
						int iSkill = 0;//18
						int iLuck = 0;//1c
						int iOption = 0;//20
						BYTE btNewOption = 0;//24
						int iDur = 0;//28
						int iAddStat = 0;//2c
						int iSetOption = 0;//30

						if (this->SubItemList[i][j].SetIndex != -1)
						{
							iSkill = this->SubItemList[i][j].Skill;
							iLuck = this->SubItemList[i][j].Luck;
							iOption = this->SubItemList[i][j].Option;
							iLevel = this->SubItemList[i][j].Level;
							btNewOption = (BYTE)(32 * this->SubItemList[i][j].Ex1);
							btNewOption |= (BYTE)(16 * this->SubItemList[i][j].Ex2);
							btNewOption |= (BYTE)(8 * this->SubItemList[i][j].Ex3);
							btNewOption |= (BYTE)(4 * this->SubItemList[i][j].Ex4);
							btNewOption |= (BYTE)(2 * this->SubItemList[i][j].Ex5);
							btNewOption |= (BYTE)(this->SubItemList[i][j].Ex6);
							gSetItemOption.GetSetOptionName(this->SubItemList[i][j].SetIndex);
							iSetOption = 1;

							if (rand() % 100 < 80)
								iSetOption |= 4;
							else
								iSetOption |= 8;

							ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y,
								this->SubItemList[i][j].ItemIndex, iLevel, iDur, iSkill, iLuck, iOption, -1, btNewOption, iSetOption);
						}
						else
						{
							iSkill = this->SubItemList[i][j].Skill;
							iLuck = this->SubItemList[i][j].Luck;
							iOption = this->SubItemList[i][j].Option;
							iLevel = this->SubItemList[i][j].Level;
							btNewOption = (BYTE)(32 * this->SubItemList[i][j].Ex1);
							btNewOption |= (BYTE)(16 * this->SubItemList[i][j].Ex2);
							btNewOption |= (BYTE)(8 * this->SubItemList[i][j].Ex3);
							btNewOption |= (BYTE)(4 * this->SubItemList[i][j].Ex4);
							btNewOption |= (BYTE)(2 * this->SubItemList[i][j].Ex5);
							btNewOption |= (BYTE)(this->SubItemList[i][j].Ex6);

							ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y,
								this->SubItemList[i][j].ItemIndex, iLevel, iDur, iSkill, iLuck, iOption, -1, btNewOption, iSetOption);
						}
					}
				}
			}
		}
	}

	return bFindItem;
}