#include "StdAfx.h"

cTheftEvent::cTheftEvent() : _Active(false), _Progress(false), _Portal(false), _Players(0)
{
}

bool cTheftEvent::Load()
{
	this->_Count = 0;

	memset(this->TheftStruct, 0, sizeof(this->TheftStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Eventos\\TheftEvent.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_Level = Section.Rows[0].GetInt(1);
		this->_Zen = Section.Rows[0].GetInt(2);
		this->_MapNumber = Section.Rows[0].GetInt(3);
		this->_X = Section.Rows[0].GetInt(4);
		this->_Y = Section.Rows[0].GetInt(5);

		strcpy_s(this->_Notice, sizeof(this->_Notice), (Section.Rows[1].GetStringPtr(0)));
	}

	if (Group.GetSection(1, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->TheftStruct[this->_Count]._Day = Section.Rows[i].GetInt(0);
			this->TheftStruct[this->_Count]._Hours = Section.Rows[i].GetInt(1);
			this->TheftStruct[this->_Count]._Minutes = Section.Rows[i].GetInt(2);
			this->TheftStruct[this->_Count]._Duration = Section.Rows[i].GetInt(3) * 60 * 1000;
			this->_Count++;
		}
	}

	return true;
}

void cTheftEvent::Run()
{
	if (this->_Active)
	{
		SYSTEMTIME Now;
		GetLocalTime(&Now);

		for (int i = 0; i < this->_Count; i++)
		{
			if (Now.wDayOfWeek == this->TheftStruct[i]._Day && Now.wHour == this->TheftStruct[i]._Hours && Now.wMinute == this->TheftStruct[i]._Minutes && Now.wSecond == 0)
			{
				this->_Value = 0; this->_Players = 0; this->_Portal = true;

				for (int Index = OBJ_STARTUSERINDEX; Index < OBJMAX; ++Index)
				{
					if (gObj[Index].Connected == 3)
					{
						Function.MsgOutput(Index, 0, "[   THEFT OF POINTS   ]");
						Function.MsgOutput(Index, 0, "O evento inicia em 5 Minuto(s)");
					}
				}

				Sleep(60000);

				for (int Index = OBJ_STARTUSERINDEX; Index < OBJMAX; ++Index)
				{
					if (gObj[Index].Connected == 3)
					{
						Function.MsgOutput(Index, 0, "[   THEFT OF POINTS   ]");
						Function.MsgOutput(Index, 0, "O evento inicia em 4 Minuto(s)");
					}
				}

				Sleep(60000);

				for (int Index = OBJ_STARTUSERINDEX; Index < OBJMAX; ++Index)
				{
					if (gObj[Index].Connected == 3)
					{
						Function.MsgOutput(Index, 0, "[   THEFT OF POINTS   ]");
						Function.MsgOutput(Index, 0, "O evento inicia em 3 Minuto(s)");
					}
				}

				Sleep(60000);

				for (int Index = OBJ_STARTUSERINDEX; Index < OBJMAX; ++Index)
				{
					if (gObj[Index].Connected == 3)
					{
						Function.MsgOutput(Index, 0, "[   THEFT OF POINTS   ]");
						Function.MsgOutput(Index, 0, "O evento inicia em 2 Minuto(s)");
					}
				}

				Sleep(60000);

				for (int Index = OBJ_STARTUSERINDEX; Index < OBJMAX; ++Index)
				{
					if (gObj[Index].Connected == 3)
					{
						Function.MsgOutput(Index, 0, "[   THEFT OF POINTS   ]");
						Function.MsgOutput(Index, 0, "O evento inicia em 1 Minuto(s)");
					}
				}

				Sleep(60000);

				if (this->_Players > 1)
				{
					for (int Index = OBJ_STARTUSERINDEX; Index < OBJMAX; ++Index)
					{
						if (gObj[Index].Connected == 3)
						{
							if (this->PlayerStruct[Index]._InEvent == true)
							{
								this->PlayerStruct[Index]._Kills = 1;
								this->PlayerStruct[Index]._AttackBlock = false;
							}

							Function.MsgOutput(Index, 0, "[   THEFT OF POINTS   ]");

							Function.MsgOutput(Index, 0, "Inscrições para o evento encerradas.");

							Function.MsgOutput(Index, 0, "O evento começou!");
						}
					}

					this->_Portal = false; this->_Progress = true;
				}
				else
				{
					for (int Index = OBJ_STARTUSERINDEX; Index < OBJMAX; ++Index)
					{
						if (gObj[Index].Connected == 3)
						{
							if (this->PlayerStruct[Index]._InEvent == true)
							{
								this->PlayerStruct[Index]._InEvent = false;
								this->PlayerStruct[Index]._Kills = 0;
								this->PlayerStruct[Index]._AttackBlock = false;

								gObj[Index].Custom->Move = true;

								gObj[Index].m_PK_Level = 3;
								GCPkLevelSend(Index, gObj[Index].m_PK_Level);
							}

							Function.MsgOutput(Index, 0, "[   THEFT OF POINTS   ]");

							Function.MsgOutput(Index, 0, "Evento encerrado. Mínimo de participantes não atingido.");
						
							BYTE SendEvent[4] = { 0xC1, 0x04, 0xFE, 0x0A };
							DataSend(Index, SendEvent, 4);
						}
					}

					this->_Players = 0; this->_Portal = false;
				}

				if (this->_Progress == true)
				{
					Sleep(this->TheftStruct[i]._Duration);

					this->Winner();
				}
			}
		}
	}
}

bool cTheftEvent::Attack(LPOBJ lpObj, LPOBJ Target)
{
	if (this->_Portal == true)
	{
		if (lpObj->Type == OBJ_USER && Target->Type == OBJ_USER)
		{
			if (this->PlayerStruct[lpObj->m_Index]._AttackBlock == true)
			{
				return false;
			}
		}
	}

	return true;
}

void cTheftEvent::Killer(LPOBJ lpObj, LPOBJ Target)
{
	if (this->_Progress == true)
	{
		if (lpObj->Type == OBJ_USER && Target->Type == OBJ_USER)
		{
			if (this->PlayerStruct[lpObj->m_Index]._InEvent == true && this->PlayerStruct[Target->m_Index]._InEvent == true)
			{
				this->PlayerStruct[lpObj->m_Index]._Kills += this->PlayerStruct[Target->m_Index]._Kills;

				Function.MsgOutput(lpObj->m_Index, 1, "%d Score recebido. Total: %d", this->PlayerStruct[Target->m_Index]._Kills, this->PlayerStruct[lpObj->m_Index]._Kills);

				Function.MsgOutput(Target->m_Index, 1, "Você morreu e teve seus pontos roubados. Total: %d", this->PlayerStruct[Target->m_Index]._Kills);

				this->PlayerStruct[Target->m_Index]._Kills = 1;

				for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
				{
					if (gObj[i].Connected == 3 && this->PlayerStruct[i]._InEvent == true)
					{
						Function.MsgOutput(i, 0, "[    PLACAR    ]");

						Function.MsgOutput(i, 0, "%s, Score: %d", lpObj->Name, this->PlayerStruct[lpObj->m_Index]._Kills);
					}
				}
			}
		}
	}
}

void cTheftEvent::Winner()
{
	for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
	{
		if (gObj[i].Connected == 3)
		{
			if (this->_Progress == true && this->PlayerStruct[i]._InEvent == true)
			{
				if (this->PlayerStruct[i]._Kills > this->PlayerStruct[this->_Value]._Kills)
				{
					this->_Value = i;
				}
			}
		}
	}

	if (this->_Value && this->PlayerStruct[this->_Value]._Kills > 0)
	{
		Manager.ExecFormat(Query._Query[25], this->PlayerStruct[this->_Value]._Kills, gObj[this->_Value].Name);
		Manager.ExecFormat(Query._Query[26], gObj[this->_Value].AccountID);

		for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
		{
			if (gObj[i].Connected == 3 && gObj[i].Type == OBJ_USER)
			{
				Function.MsgOutput(i, 0, "[   THEFT OF POINTS   ]");

				Function.MsgOutput(i, 0, "%s Winner, %d Pontos", gObj[this->_Value].Name, this->PlayerStruct[this->_Value]._Kills);

				Function.MsgOutput(i, 0, this->_Notice);
			}
		}

		this->_Value = 0; this->_Players = 0; this->_Progress = false;

		Finish();
	}
	else
	{
		for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
		{
			if (gObj[i].Connected == 3)
			{
				Function.MsgOutput(i, 0, "[   THEFT OF POINTS   ]");

				Function.MsgOutput(i, 0, "O evento não teve vencedor.");
			}
		}

		this->_Value = 0; this->_Players = 0; this->_Progress = false;

		Finish();
	}
}

void cTheftEvent::Finish()
{
	for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
	{
		if (gObj[i].Connected == 3 && this->PlayerStruct[i]._InEvent == true)
		{
			this->PlayerStruct[i]._InEvent = false;

			this->PlayerStruct[i]._AttackBlock = false;

			this->PlayerStruct[i]._Kills = 0;

			gObj[i].Custom->Move = true;

			gObj[i].m_PK_Level = 3;
			GCPkLevelSend(i, gObj[i].m_PK_Level);

			BYTE SendEvent[4] = { 0xC1, 0x04, 0xFE, 0x0A };
			DataSend(i, SendEvent, 4);
		}
	}
}

void cTheftEvent::Quit(LPOBJ lpObj)
{
	if (lpObj->Type == OBJ_USER && this->PlayerStruct[lpObj->m_Index]._InEvent == true)
	{
		this->PlayerStruct[lpObj->m_Index]._InEvent = false;

		this->PlayerStruct[lpObj->m_Index]._AttackBlock = false;

		this->PlayerStruct[lpObj->m_Index]._Kills = 0;

		lpObj->MapNumber = 0; lpObj->X = 125; lpObj->Y = 125;

		this->_Players--;

		lpObj->m_PK_Level = 3;

		GCPkLevelSend(lpObj->m_Index, lpObj->m_PK_Level);

		BYTE SendEvent[4] = { 0xC1, 0x04, 0xFE, 0x0A };
		DataSend(lpObj->m_Index, SendEvent, 4);
	}
}

cTheftEvent TheftEvent;