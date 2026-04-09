#include "StdAfx.h"
#include "GameMain.h"
#include "DSProtocol.h"

bool cPick::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Customs\\Pick.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_VipCount = Section.Rows[0].GetInt(1);
	}

	return true;
}

void cPick::Run(LPOBJ lpObj)
{
	if (this->_Active == true && lpObj->Custom->VipCount >= this->_VipCount)
	{
		if (gObjIsConnected(lpObj->m_Index) == 0)
		{
			return;
		}

		if ((MapC[lpObj->MapNumber].GetAttr(lpObj->X, lpObj->Y) & 1) != 0)
		{
			return;
		}

		if (lpObj->m_IfState.use != 0)
		{
			return;
		}

		int Index = -1;

		for (int i = 0; i < MAX_MAPITEM; i++)
		{
			if (Function.Position(lpObj->m_Index, lpObj->MapNumber, lpObj->X, lpObj->Y, 12) != 0)
			{
				Index = i;
			}

			if (Index < 0)
			{
				continue;
			}

			if (MapC[lpObj->MapNumber].m_cItem[i].live == 0)
			{
				continue;
			}

			if (MAX_ITEM_TYPE_RANGE(Index) == 0)
			{
				continue;
			}

			if (MAX_MAP_RANGE(lpObj->MapNumber) == 0)
			{
				continue;
			}

			CMapItem* Item = &MapC[lpObj->MapNumber].m_cItem[Index];

			if (Item->m_Type == ITEMGET(14, 15))
			{
				if (MapC[lpObj->MapNumber].ItemGive(lpObj->m_Index, Index, true) == TRUE)
				{
					if (gObjCheckMaxZen(lpObj->m_Index, Item->m_BuyMoney) == FALSE)
					{
						GCServerMsgStringSend(lMsg.Get(MSGGET(4, 226)), lpObj->m_Index, 1);
						return;
					}
					else
					{
						lpObj->Money += Item->m_BuyMoney;
						GCMoneySend(lpObj->m_Index, lpObj->Money);
					}

					Item->Clear();
				}
			}

			if (Item->m_Type == ITEMGET(12, 15) || Item->m_Type == ITEMGET(14, 13) || Item->m_Type == ITEMGET(14, 14) 
				|| Item->m_Type == ITEMGET(14, 16) || Item->m_Type == ITEMGET(14, 22) || Item->m_Type == ITEMGET(14, 31))
			{
				if (MapC[lpObj->MapNumber].ItemGive(lpObj->m_Index, Index, true) == TRUE)
				{
					if (!Function.InventoryFullCheck(lpObj->m_Index, Item->m_Type))
					{
						Function.MsgOutput(lpObj->m_Index, 1, "O inventário está cheio!");
						return;
					}

					ItemSerialCreateSend(lpObj->m_Index, 236, 0, 0, Item->m_Type, 0, 0, 0, 0, 0, lpObj->m_Index, 0, 0);

					Item->Clear();
				}
			}
		}
	}
}

cPick Pick;