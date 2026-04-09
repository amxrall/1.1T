#include "StdAfx.h"

cCoinEvent::cCoinEvent() : _Active(false)
{
}

bool cCoinEvent::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Eventos\\CoinEvent.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_Amount = Section.Rows[0].GetInt(1);
		strcpy_s(this->_Name, sizeof(this->_Name), (Section.Rows[0].GetStringPtr(2)));
	}

	return true;
}

void cCoinEvent::Run(LPOBJ lpObj)
{
	if (this->_Active && lpObj->Type == OBJ_USER)
	{
		if (this->_Time > 0 && (this->_Time % 60) == 0)
		{
			lpObj->Custom->Hours++; this->_Time = 0;

			if (lpObj->Custom->Hours >= 60 && (lpObj->Custom->Hours % 60) == 0)
			{
				int Hour = lpObj->Custom->Hours / 60;

				Function.MsgOutput(lpObj->m_Index, 1, "Você está a %d hora(s) online!", Hour);
				Function.MsgOutput(lpObj->m_Index, 1, "Prêmio: %d %s.", this->_Amount, this->_Name);

				Manager.ExecFormat(Query._Query[21], lpObj->Name);
				Manager.ExecFormat(Query._Query[22], this->_Amount, lpObj->AccountID);
			}
		}
		else
		{
			this->_Time++;
		}
	}
}

void cCoinEvent::Quit(LPOBJ lpObj)
{
	if (this->_Active && lpObj->Type == OBJ_USER)
	{
		lpObj->Custom->Hours = 0;
	}
}

cCoinEvent CoinEvent;