#include "StdAfx.h"
#include "GameMain.h"

cHappyEvent::cHappyEvent() : _Active(false), _Experience(0), _Drop(0)
{
}

bool cHappyEvent::Load()
{
	this->_Count = 0;

	memset(this->HappyStruct, 0, sizeof(this->HappyStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Eventos\\HappyEvent.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
	}

	if (Group.GetSection(1, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->HappyStruct[this->_Count]._Day = Section.Rows[i].GetInt(0);
			this->HappyStruct[this->_Count]._Hours = Section.Rows[i].GetInt(1);
			this->HappyStruct[this->_Count]._Minutes = Section.Rows[i].GetInt(2);
			this->HappyStruct[this->_Count]._Experience = Section.Rows[i].GetInt(3);
			this->HappyStruct[this->_Count]._Drop = Section.Rows[i].GetInt(4);
			this->HappyStruct[this->_Count]._Duration = Section.Rows[i].GetInt(5) * 60 * 1000;
			this->_Count++;
		}
	}

	return true;
}

void cHappyEvent::Run()
{
	if (this->_Active)
	{
		SYSTEMTIME Now;
		GetLocalTime(&Now);

		for (int i = 0; i < this->_Count; i++)
		{
			if (Now.wDayOfWeek == this->HappyStruct[i]._Day && Now.wHour == this->HappyStruct[i]._Hours && Now.wMinute == this->HappyStruct[i]._Minutes && Now.wSecond == 0)
			{
				for (int Index = OBJ_STARTUSERINDEX; Index < OBJMAX; ++Index)
				{
					if (gObj[Index].Connected == 3)
					{
						Function.MsgOutput(Index, 0, "[   HAPPY HOUR   ]");
						Function.MsgOutput(Index, 0, "O evento inicia em 5 Minuto(s)");
					}
				}

				Sleep(60000);

				for (int Index = OBJ_STARTUSERINDEX; Index < OBJMAX; ++Index)
				{
					if (gObj[Index].Connected == 3)
					{
						Function.MsgOutput(Index, 0, "[   HAPPY HOUR   ]");
						Function.MsgOutput(Index, 0, "O evento inicia em 4 Minuto(s)");
					}
				}

				Sleep(60000);

				for (int Index = OBJ_STARTUSERINDEX; Index < OBJMAX; ++Index)
				{
					if (gObj[Index].Connected == 3)
					{
						Function.MsgOutput(Index, 0, "[   HAPPY HOUR   ]");
						Function.MsgOutput(Index, 0, "O evento inicia em 3 Minuto(s)");
					}
				}

				Sleep(60000);

				for (int Index = OBJ_STARTUSERINDEX; Index < OBJMAX; ++Index)
				{
					if (gObj[Index].Connected == 3)
					{
						Function.MsgOutput(Index, 0, "[   HAPPY HOUR   ]");
						Function.MsgOutput(Index, 0, "O evento inicia em 2 Minuto(s)");
					}
				}

				Sleep(60000);

				for (int Index = OBJ_STARTUSERINDEX; Index < OBJMAX; ++Index)
				{
					if (gObj[Index].Connected == 3)
					{
						Function.MsgOutput(Index, 0, "[   HAPPY HOUR   ]");
						Function.MsgOutput(Index, 0, "O evento inicia em 1 Minuto(s)");
					}
				}

				Sleep(60000);

				this->_Experience = this->HappyStruct[i]._Experience;

				this->_Drop = this->HappyStruct[i]._Drop;

				for (int Index = OBJ_STARTUSERINDEX; Index < OBJMAX; ++Index)
				{
					if (gObj[Index].Connected == 3)
					{
						Function.MsgOutput(Index, 0, "[   HAPPY HOUR   ]");
						Function.MsgOutput(Index, 0, "Experiência + %d, Drop + %d", this->_Experience, this->_Drop);
					}
				}

				for (int Index = OBJ_STARTUSERINDEX; Index < OBJMAX; ++Index)
				{
					if (gObj[Index].Connected == 3)
					{
						for (int x = 0; x < Reset._Count; x++)
						{
							if (gObj[Index].Custom->VipCount == Reset.ResetStruct[x]._VipCount)
							{
								if (gObj[Index].Custom->ResetCount >= Reset.ResetStruct[x]._ResetsMin && gObj[Index].Custom->ResetCount <= Reset.ResetStruct[x]._ResetsMax || Reset.ResetStruct[x]._ResetsMax == -1)
								{
									Reset.ResetStruct[x]._Experience += this->_Experience;
								}
							}
						}
					}
				}

				gItemDropPer += this->_Drop;

				Sleep(this->HappyStruct[i]._Duration);

				this->Finish();
			}
		}
	}
}

void cHappyEvent::Finish()
{
	for (int Index = OBJ_STARTUSERINDEX; Index < OBJMAX; ++Index)
	{
		if (gObj[Index].Connected == 3)
		{
			Function.MsgOutput(Index, 0, "[   HAPPY HOUR   ]");
			Function.MsgOutput(Index, 0, "Evento encerrado.");

			for (int i = 0; i < Reset._Count; i++)
			{
				if (gObj[Index].Custom->VipCount == Reset.ResetStruct[i]._VipCount)
				{
					if (gObj[Index].Custom->ResetCount >= Reset.ResetStruct[i]._ResetsMin && gObj[Index].Custom->ResetCount <= Reset.ResetStruct[i]._ResetsMax || Reset.ResetStruct[i]._ResetsMax == -1)
					{
						Reset.ResetStruct[i]._Experience -= this->_Experience;
					}
				}
			}
		}
	}

	gItemDropPer -= this->_Drop;
}

cHappyEvent HappyEvent;