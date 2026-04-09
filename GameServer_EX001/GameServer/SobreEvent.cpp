#include "StdAfx.h"

cSobreEvent::cSobreEvent() : _State(Empty)
{
}

cSobreEvent::~cSobreEvent()
{
}

bool cSobreEvent::Load()
{
	this->_List = 0;

	this->_Players = std::vector<LPOBJ>();

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Eventos\\Sobrevivencia.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(&this->_Syntax[0][0], sizeof(this->_Syntax[0]), (Section.Rows[0].GetStringPtr(1)));
		strcpy_s(&this->_Syntax[1][0], sizeof(this->_Syntax[1]), (Section.Rows[0].GetStringPtr(2)));

		this->_MapNumber = Section.Rows[1].GetInt(0);
		this->_X = Section.Rows[1].GetInt(1);
		this->_Y = Section.Rows[1].GetInt(2);

		strcpy_s(&this->_Notice[0], sizeof(this->_Notice), (Section.Rows[2].GetStringPtr(0)));
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

bool cSobreEvent::Check(LPOBJ lpObj, const char* Text)
{
	if (Authority.Check(lpObj, 10) == true)
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

			gObjTeleport(lpObj->m_Index, this->_MapNumber, this->_X, this->_Y);

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
						Function.MsgOutput(lpObj->m_Index, 1, "Sobrevivência exclusivo para Dark Wizards e Soul Masters");
						break;
					case 1:
						Function.MsgOutput(lpObj->m_Index, 1, "Sobrevivência exclusivo para Dark Knights e Blade Knights");
						break;
					case 2:
						Function.MsgOutput(lpObj->m_Index, 1, "Sobrevivência exclusivo para Elfs e Muse Elfs");
						break;
					case 3:
						Function.MsgOutput(lpObj->m_Index, 1, "Sobrevivência exclusivo para Magic Gladiators");
						break;
					case 4:
						Function.MsgOutput(lpObj->m_Index, 1, "Sobrevivência exclusivo para Dark Lords");
						break;
					}

					return true;
				}

				auto it = std::find(this->_Players.cbegin(), this->_Players.cend(), lpObj);

				if (it != this->_Players.cend())
				{
					Function.MsgOutput(lpObj->m_Index, 1, "Você já está registrado no evento. Aguarde.");
					return true;
				}
				else if (lpObj->Level < 50)
				{
					Function.MsgOutput(lpObj->m_Index, 1, "É necessário 50 de level.");
					return true;
				}
				else if (lpObj->Custom->InDuel == true)
				{
					Function.MsgOutput(lpObj->m_Index, 1, "Saia do duelo para participar.");
					return true;
				}

				this->_Players.push_back(lpObj);

				lpObj->Custom->InEvent = true;

				lpObj->m_PK_Level = 6;
				GCPkLevelSend(lpObj->m_Index, lpObj->m_PK_Level);

				gObjTeleport(lpObj->m_Index, this->_MapNumber, this->_X, this->_Y);

				Function.MsgOutput(lpObj->m_Index, 1, "Você foi registrado no evento. Aguarde...");
			}

			return true;
		}
	}

	return false;
}

void cSobreEvent::Start(int Time, int Class)
{
	if (Time == 0)
	{
		Time++;
	}

	if (this->_Players.size() > 0)
	{
		this->_Players.clear();
	}

	this->_State = Register;
	this->_Count = (Time * 60) + 1;
	this->_Type = (BYTE)(Class);
}

void cSobreEvent::Run()
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
			if (this->_Players.size() < 2)
			{
				for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
				{
					if (gObj[i].Connected == 3)
					{
						Function.MsgOutput(i, 0, "[    Sobrevivência    ]");
						Function.MsgOutput(i, 0, "Evento encerrado. Mínimo de participantes não atingido.");

						if (gObj[i].Custom->InEvent == true)
						{
							gObj[i].Custom->InEvent = false;

							gObj[i].Custom->Move = true;

							gObj[i].m_PK_Level = 3;
							GCPkLevelSend(i, gObj[i].m_PK_Level);
						}
					}
				}

				this->_State = Empty;
				this->_Count = 0;
			}
			else
			{
				Function.AllServerAnnounce("Inscrições para o evento encerradas.");

				this->_State = Progress;
				this->_Count = 6;
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
						Function.MsgOutput(i, 0, "Sobrevivência começará em %d Minuto(s)", (this->_Count / 60));
						Function.MsgOutput(i, 0, "Para participar, utilize o comando: %s", this->_Syntax[0]);
					}
				}
			}
		}
	}
	break;
	case Progress:
	{
		switch (this->_Count)
		{
		case 5:
		case 4:
		case 3:
		case 2:
		case 1:
		{
			for (auto it = this->_Players.cbegin(); it != this->_Players.cend(); ++it)
			{
				if ((*it)->Connected == 3)
				{
					Function.MsgOutput((*it)->m_Index, 0, "A Sobrevivência começará em %d Segundo(s)", this->_Count);
				}
			}
		}
		break;
		case 0:
		{
			Function.AllServerAnnounce("A Sobrevivência começou!");

			this->_State = Fight;
		}
		break;
		}
	}
	break;
	case Fight:
	{
		if (this->_Players.size() == 1 || this->_Players.size() == 0)
		{
			this->_State = Final;
			this->_Count = 0;
		}
	}
	break;
	case Final:
	{
		if (this->_Players.size() == 0)
		{
			Function.AllServerAnnounce("A Sobrevivência não teve vencedor!");

			this->_Players.clear();

			this->_State = Empty;
			this->_Count = 0;
		}
		else
		{
			LPOBJ lpObj = this->_Players.front();

			strcpy_s(this->_Name, lpObj->Name);
			strcpy_s(this->_Account, lpObj->AccountID);

			lpObj->Custom->InEvent = false;
			lpObj->Custom->Move = true;

			lpObj->m_PK_Level = 3;
			GCPkLevelSend(lpObj->m_Index, 3);

			Manager.ExecFormat(Query._Query[15], this->_Name);
			Manager.ExecFormat(Query._Query[16], this->_Account);

			for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
			{
				if (gObj[i].Connected == 3)
				{
					Function.MsgOutput(i, 0, "%s venceu a Sobrevivência!", this->_Name);
					Function.MsgOutput(i, 0, this->_Notice);
				}
			}

			this->_Players.clear();

			this->_State = Empty;
			this->_Count = 0;
		}
	}
	break;
	}
}

bool cSobreEvent::Attack(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	auto it = std::find(this->_Players.cbegin(), this->_Players.cend(), lpTargetObj);

	if (it != this->_Players.cend())
	{
		if (this->_State == Register || this->_State == Progress)
		{
			if ((*it)->Type == OBJ_USER)
			{
				return false;
			}
		}
	}

	return true;
}

void cSobreEvent::Die(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	if (this->_State == Fight)
	{
		if (this->_Players.size() > 1 && lpObj->Custom->InEvent == true)
		{
			auto it = std::find(this->_Players.cbegin(), this->_Players.cend(), lpObj);

			if (it != this->_Players.cend())
			{
				if (lpObj->Type == OBJ_USER && lpTargetObj->Type == OBJ_USER)
				{
					Function.AllServerAnnounce("%s Eliminado(a) da Sobrevivência!", lpObj->Name);

					lpObj->Custom->Dead = true;

					lpObj->Custom->InEvent = false;

					this->_Players.erase(it);
				}
			}
		}
	}
}

void cSobreEvent::Quit(LPOBJ lpObj)
{
	if (this->_State != Empty)
	{
		if (this->_Players.size() > 0)
		{
			auto it = std::find(this->_Players.cbegin(), this->_Players.cend(), lpObj);

			if (it != this->_Players.cend())
			{
				if (this->_State == Progress || this->_State == Fight)
				{
					switch (this->_Players.size())
					{
					case 2:
					{
						lpObj->MapNumber = 0;
						lpObj->X = 125;
						lpObj->Y = 125;

						lpObj->Custom->InEvent = false;

						lpObj->m_PK_Level = 3;
						GCPkLevelSend(lpObj->m_Index, 3);

						this->_Players.erase(it);

						it = this->_Players.cbegin();

						strcpy_s(this->_Name, (*it)->Name);
						strcpy_s(this->_Account, (*it)->AccountID);

						this->_State = Final;

					}
					break;
					case 1:
					{
						strcpy_s(this->_Name, lpObj->Name);
						strcpy_s(this->_Account, lpObj->AccountID);
					}
					break;
					}

					(*it)->MapNumber = 0;
					(*it)->X = 125;
					(*it)->Y = 125;

					gObj[(*it)->m_Index].Custom->InEvent = false;

					(*it)->m_PK_Level = 3;
					GCPkLevelSend((*it)->m_Index, 3);

					this->_Players.erase(it);
				}
				else
				{
					lpObj->MapNumber = 0;
					lpObj->X = 125;
					lpObj->Y = 125;

					lpObj->Custom->InEvent = false;

					lpObj->m_PK_Level = 3;
					GCPkLevelSend(lpObj->m_Index, 3);

					this->_Players.erase(it);
				}
			}
		}
	}
}

cSobreEvent SobreEvent;