#include "StdAfx.h"

cDuelEvent::cDuelEvent() : _State(Empty)
{
}

cDuelEvent::~cDuelEvent()
{
}

bool cDuelEvent::Load()
{
	this->_List = 0;

	this->_Players[0] = std::vector<DuelPlayer>();
	this->_Players[1] = std::vector<DuelPlayer>();

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Eventos\\MataMata.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[0], sizeof(this->_Syntax[0]), (Section.Rows[0].GetStringPtr(1)));
		strcpy_s(this->_Syntax[1], sizeof(this->_Syntax[1]), (Section.Rows[0].GetStringPtr(2)));

		this->_MapNumber[0] = Section.Rows[1].GetInt(0);
		this->_X[0] = Section.Rows[1].GetInt(1);
		this->_Y[0] = Section.Rows[1].GetInt(2);
		this->_MapNumber[1] = Section.Rows[1].GetInt(3);
		this->_X[1] = Section.Rows[1].GetInt(4);
		this->_Y[1] = Section.Rows[1].GetInt(5);

		strcpy_s(this->_Notice, sizeof(this->_Notice), (Section.Rows[2].GetStringPtr(0)));
	}

	if (Group.GetSection(1, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->EventStruct[this->_List].Day = Section.Rows[i].GetInt(0);
			this->EventStruct[this->_List].Hours = Section.Rows[i].GetInt(1);
			this->EventStruct[this->_List].Minutes = Section.Rows[i].GetInt(2);
			this->EventStruct[this->_List].Time = Section.Rows[i].GetInt(3);
			this->EventStruct[this->_List].Class = Section.Rows[i].GetInt(4);
			this->_List++;
		}
	}

	return true;
}

bool cDuelEvent::Check(LPOBJ lpObj, const char* Text)
{
	if (Authority.Check(lpObj, 8) == true)
	{
		char Buffer[60], *Token = nullptr, *Context = nullptr;

		strcpy_s(Buffer, Text);
		Token = strtok_s(Buffer, " ", &Context);

		if (this->_State == Empty && !_stricmp(Token, this->_Syntax[1]))
		{
			char* Time = strtok_s(nullptr, " ", &Context);
			char* Class = strtok_s(nullptr, " ", &Context);

			if (!Time || !Class)
			{
				Function.MsgOutput(lpObj->m_Index, 1, "Erro de sintaxe!");
				Function.MsgOutput(lpObj->m_Index, 1, "Digite: %s <tempo> <class>", this->_Syntax[1]);
				Function.MsgOutput(lpObj->m_Index, 1, "Exemplo -> Evento para BKs: %s 3 1", this->_Syntax[1]);
				Function.MsgOutput(lpObj->m_Index, 1, "ID de classes: ");
				Function.MsgOutput(lpObj->m_Index, 1, "0: Wizard    | 1: Knight    | 2: Elf");
				Function.MsgOutput(lpObj->m_Index, 1, "3: Gladiator | 4: Dark Lord | 5: Todos");
				return true;
			}

			gObjTeleport(lpObj->m_Index, this->_MapNumber[0], this->_X[0], this->_Y[0]);

			this->Start(atoi(Time), atoi(Class));
			return true;
		}
	}
	else
	{
		if (!_stricmp(Text, this->_Syntax[0]))
		{
			if (this->_State == Register)
			{
				if (this->_Type != 5 && lpObj->Class != this->_Type)
				{
					switch (this->_Type)
					{
					case 0:
						Function.MsgOutput(lpObj->m_Index, 1, "Mata-Mata exclusivo para Dark Wizards e Soul Masters");
						break;
					case 1:
						Function.MsgOutput(lpObj->m_Index, 1, "Mata-Mata exclusivo para Dark Knights e Blade Knights");
						break;
					case 2:
						Function.MsgOutput(lpObj->m_Index, 1, "Mata-Mata exclusivo para Elfs e Muse Elfs");
						break;
					case 3:
						Function.MsgOutput(lpObj->m_Index, 1, "Mata-Mata exclusivo para Magic Gladiators");
						break;
					case 4:
						Function.MsgOutput(lpObj->m_Index, 1, "Mata-Mata exclusivo para Dark Lords");
						break;
					}

					return true;
				}

				if (this->_Players[0].size() > 0)
				{
					for (auto it = this->_Players[0].cbegin(); it != this->_Players[0].cend(); ++it)
					{
						if (it->lpObj == lpObj)
						{
							Function.MsgOutput(lpObj->m_Index, 1, "Você já está registrado no evento. Aguarde.");
							return true;
						}
					}
				}
				else if (lpObj->Level < 50)
				{
					Function.MsgOutput(lpObj->m_Index, 1, "É necessário 50 de level.");
					return true;
				}
				else if (lpObj->Custom->InDuel == true)
				{
					Function.MsgOutput(lpObj->m_Index, 1, "Saia do Evento para participar.");
					return true;
				}

				DuelPlayer Player;

				Player.Die = false;

				Player.lpObj = lpObj;

				lpObj->Custom->InEvent = true;

				this->_Players[0].push_back(Player);

				gObjTeleport(lpObj->m_Index, this->_MapNumber[0], this->_X[0], this->_Y[0]);

				Function.MsgOutput(lpObj->m_Index, 1, "Você foi registrado no evento. Aguarde...");
			}

			return true;
		}
	}

	return false;
}

void cDuelEvent::Start(int Time, int Class)
{
	if (Time == 0)
	{
		Time++;
	}

	if (this->_Players[0].size() > 0)
	{
		this->_Players[0].clear();
	}

	if (this->_Players[1].size() > 0)
	{
		this->_Players[1].clear();
	}

	this->_State = Register;
	this->_Count = (Time * 60) + 1;
	this->_Type = (BYTE)(Class);
}

void cDuelEvent::Run()
{
	SYSTEMTIME Now;
	GetLocalTime(&Now);

	for (int i = 0; i < this->_List; i++)
	{
		if (Now.wDayOfWeek == this->EventStruct[i].Day && Now.wHour == this->EventStruct[i].Hours && Now.wMinute == this->EventStruct[i].Minutes && Now.wSecond == 0)
		{
			if (this->_State == Empty)
			{
				this->Start(this->EventStruct[i].Time, this->EventStruct[i].Class);
			}
		}
	}

	if (this->_State == Empty)
	{
		return;
	}

	if (this->_Count > 0)
	{
		this->_Count--;
	}

	switch (this->_State)
	{
	case Register:
	{
		if (this->_Count == 0)
		{
			if (this->_Players[0].size() < 2)
			{
				for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
				{
					if (gObj[i].Connected == 3)
					{
						Function.MsgOutput(i, 0, "[   MATA-MATA   ]");
						Function.MsgOutput(i, 0, "Evento encerrado. Mínimo de participantes não atingido.");

						if (gObj[i].Custom->InEvent == true)
						{
							gObj[i].Custom->InEvent = false;

							gObj[i].Custom->Move = true;
						}
					}
				}

				this->_State = Empty;
				this->_Count = 0;
			}
			else
			{
				for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
				{
					if (gObj[i].Connected == 3)
					{
						Function.MsgOutput(i, 0, "Inscrições para o evento encerradas.");

						Function.MsgOutput(i, 0, "PRIMEIRA RODADA!");
					}
				}

				this->_State = Select;
				this->_Count = 3;
			}
		}
		else
		{
			if ((this->_Count % 60) == 0)
			{
				for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
				{
					if (gObj[i].Connected == 3)
					{
						Function.MsgOutput(i, 0, "Mata-Mata começará em %d Minuto(s)", (this->_Count / 60));
						Function.MsgOutput(i, 0, "Para participar, utilize o comando: %s", this->_Syntax[0]);
					}
				}
			}
		}
	}
	break;
	case Select:
	{
		if (this->_Count == 0)
		{
			switch (this->_Players[0].size())
			{
			case 0:
			{
				this->_State = NextStage;
				this->_Count = 0;
			}
			break;
			case 1:
			{
			SelectWO:
				this->_Selected[0] = this->_Players[0].front();

				Function.AllServerAnnounce("[    MATA-MATA    ]");

				Function.AllServerAnnounce("%s venceu de W.O.", this->_Selected[0].lpObj->Name);

				this->_Players[1].push_back(this->_Selected[0]);

				this->_State = NextStage;
				this->_Count = 0;
			}
			break;
			default:
			{
				auto Player1 = this->_Players[0].begin();
				auto Player2 = (--this->_Players[0].end());

				while (true)
				{
					if (Player1->lpObj->m_socket == INVALID_SOCKET || Player1->lpObj->Connected != 3)
					{
						this->_Players[0].erase(Player1);
						Player1 = this->_Players[0].begin();
					}
					else if (Player2->lpObj->m_socket == INVALID_SOCKET || Player2->lpObj->Connected != 3)
					{
						this->_Players[0].erase(Player2);
						Player2 = (--this->_Players[0].end());
					}
					else
					{
						break;
					}
				}

				if (Player1 == Player2)
				{
					goto SelectWO;
				}
				else
				{
					this->_Selected[0] = *Player1;
					this->_Selected[1] = *Player2;

					this->_Selected[0].Die = false;
					this->_Selected[0].Quit = false;
					this->_Selected[0].Select = true;
					this->_Selected[0].Score = 0;
					this->_Selected[1].Die = false;
					this->_Selected[1].Quit = false;
					this->_Selected[1].Select = true;
					this->_Selected[1].Score = 0;

					for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
					{
						if (gObj[i].Connected == 3)
						{
							Function.MsgOutput(i, 0, "[   MATA-MATA   ]");

							Function.MsgOutput(i, 0, "%s  vs  %s", this->_Selected[0].lpObj->Name, this->_Selected[1].lpObj->Name);

							Function.MsgOutput(i, 0, "[    ATENÇÃO    ]");
						}
					}

					this->_Sended = false;

					this->_State = Progress;
					this->_Count = 6;

					gObjTeleport(this->_Selected[0].lpObj->m_Index, this->_MapNumber[1], this->_X[1], this->_Y[1] - 1);
					gObjTeleport(this->_Selected[1].lpObj->m_Index, this->_MapNumber[1], this->_X[1], this->_Y[1] + 1);

					this->_Selected[0].lpObj->m_PK_Level = 6;
					this->_Selected[1].lpObj->m_PK_Level = 6;

					GCPkLevelSend(this->_Selected[0].lpObj->m_Index, 6);
					GCPkLevelSend(this->_Selected[1].lpObj->m_Index, 6);

					this->_Players[0].erase(Player2);
					this->_Players[0].erase(Player1);
				}
			}
			break;
			}
		}
	}
	break;
	case Progress:
	{
		switch (this->_Count)
		{
		case 3:
		case 2:
		case 1:
		{
			Function.AllServerAnnounce("Você poderá atacar em %d", this->_Count);
		}
		break;
		case 0:
		{
			if (this->_Sended == false)
			{
				Function.AllServerAnnounce("Já!", this->_Count);

				this->_Sended = true;
			}
		}
		break;
		default:
			break;
		}
	}
	break;
	case Died:
	{
		if (this->_Count == 0)
		{
			if (this->_Selected[0].Die && this->_Selected[1].Die)
			{
				Function.AllServerAnnounce("Draw!");

				this->_Sended = false;

				this->_State = Progress;
				this->_Count = 6;
			}
			else
			{
				BYTE Winner = (this->_Selected[0].Die) ? 1 : 0;
				BYTE Loser = (Winner == 1) ? 0 : 1;

				this->_Selected[Winner].Score++;

				for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
				{
					if (gObj[i].Connected == 3)
					{
						Function.MsgOutput(i, 0, "[    PLACAR    ]");

						Function.MsgOutput(i, 0, "%s  vs  %s", this->_Selected[0].lpObj->Name, this->_Selected[1].lpObj->Name);

						Function.MsgOutput(i, 0, "%d   x   %d", this->_Selected[0].Score, this->_Selected[1].Score);
					}
				}

				if (this->_Selected[Winner].Score >= 3)
				{
					Function.AllServerAnnounce("%s venceu!", this->_Selected[Winner].lpObj->Name);

					this->_Players[1].push_back(this->_Selected[Winner]);

					this->_Selected[0].lpObj->m_PK_Level = 3;
					this->_Selected[0].Select = false;
					this->_Selected[1].lpObj->m_PK_Level = 3;
					this->_Selected[1].Select = false;

					GCPkLevelSend(this->_Selected[0].lpObj->m_Index, 3);
					GCPkLevelSend(this->_Selected[1].lpObj->m_Index, 3);

					gObjTeleport(this->_Selected[Winner].lpObj->m_Index, this->_MapNumber[0], this->_X[0], this->_Y[0]);
					gObjTeleport(this->_Selected[Loser].lpObj->m_Index, 0, 125, 125);

					this->_Selected[Loser].lpObj->Custom->InEvent = false;

					this->_State = Select;
					this->_Count = 0;
				}
				else
				{
					Function.AllServerAnnounce("[    ATENÇÃO    ]");

					this->_Sended = false;

					this->_State = Progress;
					this->_Count = 6;
				}
			}

			this->_Selected[0].Die = false;
			this->_Selected[1].Die = false;
		}
	}
	break;
	case NextStage:
	{
		if (this->_Players[0].size() > 0)
		{
			this->_Players[0].clear();
		}

		this->_Players[0] = this->_Players[1];

		if (this->_Players[1].size() > 0)
		{
			this->_Players[1].clear();
		}

		this->_Selected[0].lpObj = NULL;
		this->_Selected[1].lpObj = NULL;

		switch (this->_Players[0].size())
		{
		case 0:
		{
			this->_State = Empty;
			this->_Count = 0;
		}
		break;
		case 1:
		{
			this->_State = Final;
			this->_Count = 0;
		}
		break;
		default:
		{
			if ((this->_Players[0].size() % 2) == 0)
			{
				Function.AllServerAnnounce("RODADA FINAL!");
			}
			else
			{
				Function.AllServerAnnounce("PRÓXIMA RODADA!");
			}

			this->_State = Select;
			this->_Count = 0;
		}
		break;
		}
	}
	break;
	case WO:
	{
		BYTE Winner = (this->_Selected[0].Quit) ? 1 : 0;
		BYTE Loser = (Winner == 1) ? 0 : 1;

		for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
		{
			if (gObj[i].Connected == 3)
			{
				if (this->_Players[0].size() > 1)
				{
					Function.MsgOutput(i, 0, "[    PLACAR    ]");

					Function.MsgOutput(i, 0, "%s  vs  %s", this->_Selected[0].lpObj->Name, this->_Selected[1].lpObj->Name);
				}

				Function.MsgOutput(i, 0, "%s venceu por W.O.", this->_Selected[Winner].lpObj->Name);
			}
		}

		this->_Players[1].push_back(this->_Selected[Winner]);

		this->_Selected[0].lpObj->m_PK_Level = 3;
		this->_Selected[0].Select = false;
		this->_Selected[1].lpObj->m_PK_Level = 3;
		this->_Selected[1].Select = false;

		GCPkLevelSend(this->_Selected[0].lpObj->m_Index, 3);
		GCPkLevelSend(this->_Selected[1].lpObj->m_Index, 3);

		gObjTeleport(this->_Selected[Winner].lpObj->m_Index, this->_MapNumber[0], this->_X[0], this->_Y[0]);
		gObjTeleport(this->_Selected[Loser].lpObj->m_Index, 0, 125, 125);

		this->_Selected[Loser].lpObj->Custom->InEvent = false;

		this->_State = Select;
		this->_Count = 0;
	}
	break;
	case Final:
	{
		if (this->_Players[0].size() == 0)
		{
			Function.AllServerAnnounce("O Mata-Mata não teve vencedor!");

			this->_Players[0].clear();
			this->_Players[1].clear();

			this->_State = Empty;
			this->_Count = 0;
		}
		else
		{
			LPOBJ lpObj = this->_Players[0].front().lpObj;

			Manager.ExecFormat(Query._Query[9], lpObj->Name);
			Manager.ExecFormat(Query._Query[10], lpObj->AccountID);

			for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
			{
				if (gObj[i].Connected == 3)
				{
					Function.MsgOutput(i, 0, "%s é o campeão do Mata-Mata!", lpObj->Name);

					Function.MsgOutput(i, 0, this->_Notice);
				}
			}

			gObjTeleport(lpObj->m_Index, 0, 125, 125);

			lpObj->Custom->InEvent = false;

			this->_Players[0].clear();
			this->_Players[1].clear();

			this->_State = Empty;
			this->_Count = 0;
		}
	}
	break;
	}
}

bool cDuelEvent::Attack(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	if (this->_State == Progress)
	{
		if (this->_Selected[0].lpObj != lpObj && this->_Selected[1].lpObj != lpObj &&
			this->_Selected[0].lpObj != lpTargetObj && this->_Selected[1].lpObj != lpTargetObj)
		{
			return true;
		}

		if (this->_Selected[0].lpObj == lpObj && this->_Selected[1].lpObj == lpTargetObj ||
			this->_Selected[1].lpObj == lpObj && this->_Selected[0].lpObj == lpTargetObj)
		{
			if (this->_Count == 0)
			{
				return true;
			}

			return false;
		}

		if (this->_Selected[0].lpObj == lpObj && this->_Selected[1].lpObj->Type == OBJ_MONSTER ||
			this->_Selected[1].lpObj == lpObj && this->_Selected[0].lpObj->Type == OBJ_MONSTER)
		{
			return true;
		}

		return false;
	}

	return true;
}

void cDuelEvent::Die(LPOBJ lpObj)
{
	if (this->_State == Progress || this->_State == Died)
	{
		if (this->_Selected[0].lpObj == lpObj)
		{
			this->_Selected[0].Die = true;
		}

		if (this->_Selected[1].lpObj == lpObj)
		{
			this->_Selected[1].Die = true;
		}

		if (this->_State == Progress && (this->_Selected[0].Die || this->_Selected[1].Die))
		{
			this->_State = Died;
			this->_Count = 4;
		}
	}
}

void cDuelEvent::Quit(LPOBJ lpObj)
{
	if (this->_State != Empty)
	{
		if (this->_Selected[0].lpObj == lpObj)
		{
			if (this->_Selected[0].Select == true)
			{
				this->_Selected[0].Quit = true;

				this->_Selected[0].lpObj->MapNumber = 0;

				this->_Selected[0].lpObj->X = 125;

				this->_Selected[0].lpObj->Y = 125;

				this->_Selected[0].lpObj->m_PK_Level = 3;

				GCPkLevelSend(this->_Selected[0].lpObj->m_Index, 3);

				this->_State = WO;
				this->_Count = 0;
			}
		}
		else if (this->_Selected[1].lpObj == lpObj)
		{
			if (this->_Selected[1].Select == true)
			{
				this->_Selected[1].Quit = true;

				this->_Selected[1].lpObj->MapNumber = 0;

				this->_Selected[1].lpObj->X = 125;

				this->_Selected[1].lpObj->Y = 125;

				this->_Selected[1].lpObj->m_PK_Level = 3;

				GCPkLevelSend(this->_Selected[1].lpObj->m_Index, 3);

				this->_State = WO;
				this->_Count = 0;
			}
		}
		else
		{
			if (this->_Players[0].size() > 0)
			{
				for (auto it = this->_Players[0].cbegin(); it != this->_Players[0].cend(); ++it)
				{
					if (it->lpObj == lpObj)
					{
						lpObj->MapNumber = 0; lpObj->X = 125; lpObj->Y = 125;

						lpObj->Custom->InEvent = false;

						lpObj->m_PK_Level = 3;

						GCPkLevelSend(lpObj->m_Index, 3);

						this->_Players[0].erase(it);
						break;
					}
				}
			}

			if (this->_Players[1].size() > 0)
			{
				for (auto it = this->_Players[1].cbegin(); it != this->_Players[1].cend(); ++it)
				{
					if (it->lpObj == lpObj)
					{
						lpObj->MapNumber = 0; lpObj->X = 125; lpObj->Y = 125;

						lpObj->Custom->InEvent = false;

						lpObj->m_PK_Level = 3;

						GCPkLevelSend(lpObj->m_Index, 3);

						this->_Players[1].erase(it);
						break;
					}
				}
			}
		}
	}
}

cDuelEvent DuelEvent;