#include "StdAfx.h"

cPegaEvent::cPegaEvent() : _State(Empty)
{
}

cPegaEvent::~cPegaEvent()
{
}

bool cPegaEvent::Load()
{
	this->_Players = std::vector<LPOBJ>();

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Eventos\\PegaPega.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[0], sizeof(this->_Syntax[0]), (Section.Rows[0].GetStringPtr(1)));
		strcpy_s(this->_Syntax[1], sizeof(this->_Syntax[1]), (Section.Rows[0].GetStringPtr(2)));

		this->_MapNumber = Section.Rows[1].GetInt(0);
		this->_X = Section.Rows[1].GetInt(1);
		this->_Y = Section.Rows[1].GetInt(2);

		strcpy_s(this->_Notice[2], sizeof(this->_Notice[2]), (Section.Rows[2].GetStringPtr(0)));
		strcpy_s(this->_Notice[1], sizeof(this->_Notice[1]), (Section.Rows[3].GetStringPtr(0)));
		strcpy_s(this->_Notice[0], sizeof(this->_Notice[0]), (Section.Rows[4].GetStringPtr(0)));
	}

	return true;
}

bool cPegaEvent::Check(LPOBJ lpObj, const char* Text)
{
	if (Authority.Check(lpObj, 9) == true)
	{
		char Buffer[60], *Token = nullptr, *Context = nullptr;

		strcpy_s(Buffer, Text);
		Token = strtok_s(Buffer, " ", &Context);

		if (this->_State == Empty && !_stricmp(Token, this->_Syntax[1]))
		{
			char* Time = strtok_s(nullptr, " ", &Context);

			if (!Time)
			{
				Function.MsgOutput(lpObj->m_Index, 1, "Erro de sintaxe! Digite: %s <tempo>", this->_Syntax[1]);
				Function.MsgOutput(lpObj->m_Index, 1, "Exemplo -> %s 3", this->_Syntax[1]);
				return true;
			}

			gObjTeleport(lpObj->m_Index, this->_MapNumber, this->_X, this->_Y);

			this->Start(atoi(Time));
			return true;
		}
	}
	else
	{
		if (!_stricmp(Text, this->_Syntax[0]))
		{
			if (this->_State == Register)
			{
				if (!this->CheckItem(lpObj))
				{
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

				gObjTeleport(lpObj->m_Index, this->_MapNumber, this->_X, this->_Y);

				Function.MsgOutput(lpObj->m_Index, 1, "Você foi registrado no evento. Aguarde...");
			}

			return true;
		}
	}

	return false;
}

void cPegaEvent::Start(int Time)
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
}

void cPegaEvent::Run()
{
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
			if (this->_Players.size() < 5)
			{
				for (auto it = this->_Players.cbegin(); it != this->_Players.cend(); ++it)
				{
					if ((*it)->Connected == 3)
					{
						gObj[(*it)->m_Index].Custom->Move = true;

						BYTE SendEvent[4] = { 0xC1, 0x04, 0xFE, 0x0A };
						DataSend((*it)->m_Index, SendEvent, 4);
					}
				}

				for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
				{
					if (gObj[i].Connected == 3)
					{
						Function.MsgOutput(i, 0, "[   PEGA-PEGA   ]");
						Function.MsgOutput(i, 0, "Evento encerrado. Mínimo de participantes não atingido.");
					}
				}

				this->_State = Empty;
				this->_Count = 0;
			}
			else
			{
				Function.AllServerAnnounce("Inscrições para o evento encerradas!");

				this->_State = Capture;
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
						Function.MsgOutput(i, 0, "Pega-Pega começará em %d Minuto(s)", (this->_Count / 60));
						Function.MsgOutput(i, 0, "Para participar, utilize o comando: %s", this->_Syntax[0]);
					}
				}
			}
		}
	}
	break;
	case Capture:
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
					Function.MsgOutput((*it)->m_Index, 0, "O GM começará a pegar em %d Segundo(s)", this->_Count);
				}
			}
		}
		break;
		case 0:
		{
			Function.AllServerAnnounce("Corra! O GM começou a capturar!");

			this->_State = Progress;
		}
		break;
		}
	}
	break;
	case Progress:
		break;
	case Final:
	{
		if (this->_Players.size() > 0)
		{
			this->_State = Progress;
		}
		else
		{
			Manager.ExecFormat(Query._Query[11], this->_Name[2]);

			Manager.ExecFormat(Query._Query[12], this->_Account[2]);
			Manager.ExecFormat(Query._Query[13], this->_Account[1]);
			Manager.ExecFormat(Query._Query[14], this->_Account[0]);

			for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
			{
				if (gObj[i].Connected == 3)
				{
					Function.MsgOutput(i, 0, "[   PEGA-PEGA   ]");

					Function.MsgOutput(i, 0, "1º Lugar: %s / %s", this->_Name[2], this->_Notice[2]);

					Function.MsgOutput(i, 0, "2º Lugar: %s / %s", this->_Name[1], this->_Notice[1]);

					Function.MsgOutput(i, 0, "3º Lugar: %s / %s", this->_Name[0], this->_Notice[0]);
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

bool cPegaEvent::CheckItem(LPOBJ lpObj)
{
	if (lpObj->pInventory[7].IsItem())
	{
		Function.MsgOutput(lpObj->m_Index, 1, "Você não pode participar do evento!");
		Function.MsgOutput(lpObj->m_Index, 1, "Proibido usar asas ou capas.");
		return false;
	}

	if (lpObj->pInventory[8].IsItem() && lpObj->pInventory[8].m_Type == ITEMGET(13, 2))
	{
		Function.MsgOutput(lpObj->m_Index, 1, "Você não pode participar do evento!");
		Function.MsgOutput(lpObj->m_Index, 1, "Proibido usar o uniria.");
		return false;
	}
	else if (lpObj->pInventory[8].IsItem() && lpObj->pInventory[8].m_Type == ITEMGET(13, 3))
	{
		Function.MsgOutput(lpObj->m_Index, 1, "Você não pode participar do evento!");
		Function.MsgOutput(lpObj->m_Index, 1, "Proibido usar o dinorant.");
		return false;
	}
	else if (lpObj->pInventory[8].IsItem() && lpObj->pInventory[8].m_Type == ITEMGET(13, 4))
	{
		Function.MsgOutput(lpObj->m_Index, 1, "Você não pode participar do evento!");
		Function.MsgOutput(lpObj->m_Index, 1, "Proibido usar o dark horse.");
		return false;
	}

	return true;
}

bool cPegaEvent::Attack(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	auto it = std::find(this->_Players.cbegin(), this->_Players.cend(), lpTargetObj);

	if (it != this->_Players.cend())
	{
		if (this->_State == Register || this->_State == Capture)
		{
			if ((*it)->Type == OBJ_USER)
			{
				return false;
			}
		}
	}

	if (this->_State == Progress)
	{
		if (lpObj->Authority > 1)
		{
			if (this->_Players.size() > 0)
			{
				auto it = std::find(this->_Players.cbegin(), this->_Players.cend(), lpTargetObj);

				if (it != this->_Players.cend())
				{
					Function.AllServerAnnounce("%s - Capturado!", lpTargetObj->Name);

					switch (this->_Players.size())
					{
					case 3:
					{
						strcpy_s(this->_Name[0], lpTargetObj->Name);
						strcpy_s(this->_Account[0], lpTargetObj->AccountID);
					}
					break;
					case 2:
					{
						strcpy_s(this->_Name[1], lpTargetObj->Name);
						strcpy_s(this->_Account[1], lpTargetObj->AccountID);

						gObjTeleport(lpTargetObj->m_Index, 0, 125, 125);

						this->_Players.erase(it);

						it = this->_Players.cbegin();

						strcpy_s(this->_Name[2], (*it)->Name);
						strcpy_s(this->_Account[2], (*it)->AccountID);

						gObjTeleport((*it)->m_Index, 0, 125, 125);
					}
					break;
					case 1:
					{
						strcpy_s(this->_Name[2], lpTargetObj->Name);
						strcpy_s(this->_Account[2], lpTargetObj->AccountID);
					}
					break;
					}

					gObjTeleport(lpTargetObj->m_Index, 0, 125, 125);

					this->_Players.erase(it);

					this->_State = Final;
				}
			}
		}
		else
		{
			if (this->_Players.size() > 0)
			{
				auto it = std::find(this->_Players.cbegin(), this->_Players.cend(), lpObj);

				if (it != this->_Players.cend())
				{
					return false;
				}

				it = std::find(this->_Players.cbegin(), this->_Players.cend(), lpTargetObj);

				if (it != this->_Players.cend())
				{
					return false;
				}
			}
		}
	}

	return true;
}

void cPegaEvent::Quit(LPOBJ lpObj)
{
	if (this->_State != Empty)
	{
		if (this->_Players.size() > 0)
		{
			auto it = std::find(this->_Players.cbegin(), this->_Players.cend(), lpObj);

			if (it != this->_Players.cend())
			{
				if (this->_State == Capture || this->_State == Progress)
				{
					switch (this->_Players.size())
					{
					case 3:
					{
						strcpy_s(this->_Name[0], lpObj->Name);
						strcpy_s(this->_Account[0], lpObj->AccountID);
					}
					break;
					case 2:
					{
						strcpy_s(this->_Name[1], lpObj->Name);
						strcpy_s(this->_Account[1], lpObj->AccountID);

						lpObj->MapNumber = 0;
						lpObj->X = 125;
						lpObj->Y = 125;

						this->_Players.erase(it);

						it = this->_Players.cbegin();

						strcpy_s(this->_Name[2], (*it)->Name);
						strcpy_s(this->_Account[2], (*it)->AccountID);

						this->_State = Final;
						this->_Count = 0;
					}
					break;
					case 1:
					{
						strcpy_s(this->_Name[2], lpObj->Name);
						strcpy_s(this->_Account[2], lpObj->AccountID);
					}
					break;
					}

					(*it)->MapNumber = 0;
					(*it)->X = 125;
					(*it)->Y = 125;

					this->_Players.erase(it);
				}
				else
				{
					lpObj->MapNumber = 0;
					lpObj->X = 125;
					lpObj->Y = 125;

					this->_Players.erase(it);
				}
			}
		}
	}
}

bool cPegaEvent::Equip(LPOBJ lpObj, BYTE SourcePos, BYTE TargetPos)
{
	if (this->_State != Empty)
	{
		if (this->_Players.size() > 0)
		{
			auto it = std::find(this->_Players.cbegin(), this->_Players.cend(), lpObj);

			if (it != this->_Players.cend())
			{
				if (TargetPos == 7)
				{
					Function.MsgOutput(lpObj->m_Index, 1, "Você não pode equipar asas ou capas no evento.");
					return false;
				}

				if (TargetPos == 8)
				{
					if (lpObj->pInventory[SourcePos].m_Type == ITEMGET(13, 2))
					{
						Function.MsgOutput(lpObj->m_Index, 1, "Você não pode equipar o uniria no evento.");
						return false;
					}
					else if (lpObj->pInventory[SourcePos].m_Type == ITEMGET(13, 3))
					{
						Function.MsgOutput(lpObj->m_Index, 1, "Você não pode equipar o dinorant no evento.");
						return false;
					}
					else if (lpObj->pInventory[SourcePos].m_Type == ITEMGET(13, 4))
					{
						Function.MsgOutput(lpObj->m_Index, 1, "Você não pode equipar o dark horse no evento.");
						return false;
					}
				}
			}
		}
	}

	return true;
}

cPegaEvent PegaEvent;