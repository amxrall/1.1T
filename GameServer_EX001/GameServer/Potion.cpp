#include "StdAfx.h"

bool cPotion::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Customs\\Potion.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active[0] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_Delay = Section.Rows[0].GetInt(1);
	}

	if (Group.GetSection(1, Section))
	{
		this->_Active[1] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_VipCount = Section.Rows[0].GetInt(1);
		strcpy_s(this->_Syntax, sizeof(this->_Syntax), (Section.Rows[0].GetStringPtr(2)));
	}

	return true;
}

int cPotion::Inventory(LPOBJ lpObj, int aIndex)
{
	for (int i = 12; i < 76; i++)
	{
		if (lpObj->pInventory[i].m_Type == aIndex)
		{
			return i;
		}
	}

	return FALSE;
}

void cPotion::Thread1(void* lpParam)
{
	while (true)
	{
		Sleep(Potion._Delay);

		for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
		{
			if (gObj[i].Connected == 3 && gObj[i].Custom->Time > 0)
			{
				--gObj[i].Custom->Time;
			}
		}
	}

	_endthread();
}

void cPotion::Thread2(void* lpParam)
{
	while (true)
	{
		for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
		{
			if (gObj[i].Connected == 3 && gObj[i].Custom->Start == true)
			{
				if (gObj[i].Custom->VipCount >= Potion._VipCount)
				{
					PMSG_USEITEM Result1;
					Result1.inventoryPos = Potion.Inventory(&gObj[i], ITEMGET(14, 3));
					Result1.invenrotyTarget = 0;

					if (Result1.inventoryPos != 0x0)
					{
						CGUseItemRecv(&Result1, i);
					}

					PMSG_USEITEM Result2;
					Result2.inventoryPos = Potion.Inventory(&gObj[i], ITEMGET(14, 2));
					Result2.invenrotyTarget = 0;

					if (Result2.inventoryPos != 0x0)
					{
						CGUseItemRecv(&Result2, i);
					}
				}
			}
		}

		Sleep(40);
	}

	_endthread();
}

void cPotion::Command(int aIndex, char* msg)
{
	if (this->_Active[1])
	{
		memset(this->_Name, 0, sizeof(this->_Name));

		sscanf(msg, "%s", &this->_Name);

		if (strlen(msg) < 2 || this->_Name[0] == 0 || strcmpi(this->_Name, "on") && strcmpi(this->_Name, "off"))
		{
			Function.MsgOutput(aIndex, 1, "Erro de sintaxe!");
			Function.MsgOutput(aIndex, 1, "Digite: %s on ou off.", this->_Syntax);
			return;
		}
		else if (gObj[aIndex].Custom->VipCount < this->_VipCount)
		{
			Function.MsgOutput(aIndex, 1, "Você não possui o plano vip necessário!");
			return;
		}

		if (!strcmpi(this->_Name, "on"))
		{
			Function.MsgOutput(aIndex, 1, "Auto potion ativado com sucesso.");

			gObj[aIndex].Custom->Start = true;
		}
		else if (!strcmpi(this->_Name, "off"))
		{
			Function.MsgOutput(aIndex, 1, "Auto potion desativado com sucesso.");

			gObj[aIndex].Custom->Start = false;
		}
	}
}

void cPotion::Quit(LPOBJ lpObj)
{
	if (lpObj->Type == OBJ_USER && lpObj->Custom->Start == true)
	{
		lpObj->Custom->Start = false;
	}
}

cPotion Potion;