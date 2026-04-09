#include "StdAfx.h"
#include "DSProtocol.h"
#include "LogProc.h"

bool Commands::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Comandos\\Comandos.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active[0] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[0], sizeof(this->_Syntax[0]), (Section.Rows[0].GetStringPtr(1)));
		strcpy_s(this->_Formato, sizeof(this->_Formato), (Section.Rows[0].GetStringPtr(2)));

		this->_Level[0] = Section.Rows[1].GetInt(0);
		this->_Zen[0] = Section.Rows[1].GetInt(1);
		this->_VipCount[0] = Section.Rows[1].GetInt(2);
		this->_Delay = Section.Rows[1].GetInt(3);
		this->_Color = Section.Rows[1].GetInt(4);
	}

	if (Group.GetSection(1, Section))
	{
		this->_Active[1] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[1], sizeof(this->_Syntax[1]), (Section.Rows[0].GetStringPtr(1)));
		strcpy_s(this->_Syntax[2], sizeof(this->_Syntax[2]), (Section.Rows[0].GetStringPtr(2)));
		strcpy_s(this->_Syntax[3], sizeof(this->_Syntax[3]), (Section.Rows[0].GetStringPtr(3)));
		strcpy_s(this->_Syntax[4], sizeof(this->_Syntax[4]), (Section.Rows[0].GetStringPtr(4)));
		strcpy_s(this->_Syntax[5], sizeof(this->_Syntax[5]), (Section.Rows[0].GetStringPtr(5)));

		this->_Level[1] = Section.Rows[1].GetInt(0);
		this->_Zen[1] = Section.Rows[1].GetInt(1);
	}

	if (Group.GetSection(2, Section))
	{
		this->_Active[2] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[6], sizeof(this->_Syntax[6]), (Section.Rows[0].GetStringPtr(1)));

		this->_Level[2] = Section.Rows[1].GetInt(0);
		this->_Zen[2] = Section.Rows[1].GetInt(1);
		this->_Comando = Section.Rows[1].GetInt(2);
	}

	if (Group.GetSection(3, Section))
	{
		this->_Active[3] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[7], sizeof(this->_Syntax[7]), (Section.Rows[0].GetStringPtr(1)));

		this->_Level[3] = Section.Rows[1].GetInt(0);
		this->_Zen[3] = Section.Rows[1].GetInt(1);
	}

	if (Group.GetSection(4, Section))
	{
		this->_Active[4] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[8], sizeof(this->_Syntax[8]), (Section.Rows[0].GetStringPtr(1)));

		this->_Level[4] = Section.Rows[1].GetInt(0);
		this->_Zen[4] = Section.Rows[1].GetInt(1);
		this->_Ware[0] = Section.Rows[1].GetInt(2);
		this->_Ware[1] = Section.Rows[1].GetInt(3);
		this->_Ware[2] = Section.Rows[1].GetInt(4);
		this->_Ware[3] = Section.Rows[1].GetInt(5);
	}

	if (Group.GetSection(5, Section))
	{
		this->_Active[5] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[9], sizeof(this->_Syntax[9]), (Section.Rows[0].GetStringPtr(1)));

		this->_VipCount[1] = Section.Rows[1].GetInt(0);
		this->_Zen[5] = Section.Rows[1].GetInt(1);
	}

	if (Group.GetSection(6, Section))
	{
		this->_Active[6] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[10], sizeof(this->_Syntax[10]), (Section.Rows[0].GetStringPtr(1)));

		this->_Zen[6] = Section.Rows[1].GetInt(1);
	}

	if (Group.GetSection(7, Section))
	{
		this->_Active[7] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[11], sizeof(this->_Syntax[11]), (Section.Rows[0].GetStringPtr(1)));

		strcpy_s(this->_Notice, sizeof(this->_Notice), (Section.Rows[1].GetStringPtr(0)));
	}

	if (Group.GetSection(8, Section))
	{
		this->_Active[8] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[12], sizeof(this->_Syntax[12]), (Section.Rows[0].GetStringPtr(1)));
	}

	if (Group.GetSection(9, Section))
	{
		this->_Active[9] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[13], sizeof(this->_Syntax[13]), (Section.Rows[0].GetStringPtr(1)));
	}

	if (Group.GetSection(10, Section))
	{
		this->_Active[10] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[14], sizeof(this->_Syntax[14]), (Section.Rows[0].GetStringPtr(1)));
	}

	if (Group.GetSection(11, Section))
	{
		this->_Active[11] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[15], sizeof(this->_Syntax[15]), (Section.Rows[0].GetStringPtr(1)));
	}

	if (Group.GetSection(12, Section))
	{
		this->_Active[12] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[16], sizeof(this->_Syntax[16]), (Section.Rows[0].GetStringPtr(1)));
	}

	if (Group.GetSection(13, Section))
	{
		this->_Active[13] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[17], sizeof(this->_Syntax[17]), (Section.Rows[0].GetStringPtr(1)));
		strcpy_s(this->_Syntax[18], sizeof(this->_Syntax[18]), (Section.Rows[0].GetStringPtr(2)));
	}

	if (Group.GetSection(14, Section))
	{
		this->_Active[14] = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax[19], sizeof(this->_Syntax[19]), (Section.Rows[0].GetStringPtr(1)));
	}

	return true;
}

bool Commands::Management(PMSG_CHATDATA* lpMsg, int aIndex)
{
#if(GS_CASTLE == 0)
	if (DuelEvent.Check(&gObj[aIndex], (const char*)lpMsg->chatmsg))
	{
		return true;
	}

	if (PegaEvent.Check(&gObj[aIndex], (const char*)lpMsg->chatmsg))
	{
		return true;
	}

	if (SobreEvent.Check(&gObj[aIndex], (const char*)lpMsg->chatmsg))
	{
		return true;
	}


	if (!_stricmp((const char*)(lpMsg->chatmsg), Duel._Syntax[1]))
	{
		Duel.Accept(aIndex);
		return true;
	}

#endif

	if (!_stricmp((const char*)(lpMsg->chatmsg), "/info"))
	{
		//Function.MsgOutput(aIndex, 1, "Resets: %d || Master Reset: %d", gObj[aIndex].Custom->ResetCount, gObj[aIndex].Custom->MasterCount);
		Function.MsgOutput(aIndex, 1, "Saldo Cash : %d", gObj[aIndex].m_Cash);
		Function.MsgOutput(aIndex, 1, "Saldo Golds : %d", gObj[aIndex].m_Gold);
		return true;
	}

	if (!_stricmp((const char*)(lpMsg->chatmsg), this->_Syntax[18]))
	{
		this->Ir(aIndex);
		return true;
	}

	if (!_stricmp((const char*)(lpMsg->chatmsg), "/full"))
	{
		this->Full(aIndex);
		return true;
	}

	for (int i = 0; i < Teleport._Count; i++)
	{
		if (!_stricmp((const char*)(lpMsg->chatmsg), Teleport.TeleportStruct[i]._Syntax))
		{
#if(GS_CASTLE == 0)
			DuelEvent.Quit(&gObj[aIndex]);
			PegaEvent.Quit(&gObj[aIndex]);
			SobreEvent.Quit(&gObj[aIndex]);
			DeathEvent.Quit(&gObj[aIndex]);
			TheftEvent.Quit(&gObj[aIndex]);
			Duel.Quit(&gObj[aIndex]);
#endif
			Potion.Quit(&gObj[aIndex]);

			Teleport.Run(aIndex, i);
			return true;
		}
	}

	if (!_stricmp((const char*)(lpMsg->chatmsg), this->_Syntax[6]))
	{
		this->ReAdd(aIndex);
		return true;
	}

	if (!_stricmp((const char*)(lpMsg->chatmsg), this->_Syntax[7]))
	{
		this->Clear(aIndex);
		return true;
	}

	if (!_stricmp((const char*)(lpMsg->chatmsg), this->_Syntax[9]))
	{
		this->Money(aIndex);
		return true;
	}

	if (!_stricmp((const char*)(lpMsg->chatmsg), this->_Syntax[10]))
	{
		this->Online(aIndex);
		return true;
	}

	if (!_stricmp((const char*)(lpMsg->chatmsg), Reset._Syntax))
	{
		Reset.Run(aIndex);
		return true;
	}

	if (!_stricmp((const char*)(lpMsg->chatmsg), Master._Syntax))
	{
		Master.Run(aIndex);
		return true;
	}

	if (!_stricmp((const char*)(lpMsg->chatmsg), this->_Syntax[15]))
	{
		this->FireWork(aIndex);
		return true;
	}

	if (!_stricmp((const char*)(lpMsg->chatmsg), Bonus._Syntax))
	{
		Bonus.Command(aIndex);
		return true;
	}

	if (!_stricmp((const char*)(lpMsg->chatmsg), Roleta._Syntax))
	{
		Roleta.Command(aIndex);
		return true;
	}

	if (!_memicmp(lpMsg->chatmsg, this->_Syntax[0], strlen(this->_Syntax[0])))
	{
		this->Post(aIndex, (char*)(lpMsg->chatmsg + strlen(this->_Syntax[0])));
		return true;
	}

	if (!_memicmp(lpMsg->chatmsg, this->_Syntax[1], strlen(this->_Syntax[1])))
	{
		this->Add(aIndex, (char*)(lpMsg->chatmsg + strlen(this->_Syntax[1])), 1);
		return true;
	}

	if (!_memicmp(lpMsg->chatmsg, this->_Syntax[2], strlen(this->_Syntax[2])))
	{
		this->Add(aIndex, (char*)(lpMsg->chatmsg + strlen(this->_Syntax[2])), 2);
		return true;
	}

	if (!_memicmp(lpMsg->chatmsg, this->_Syntax[3], strlen(this->_Syntax[3])))
	{
		this->Add(aIndex, (char*)(lpMsg->chatmsg + strlen(this->_Syntax[3])), 3);
		return true;
	}

	if (!_memicmp(lpMsg->chatmsg, this->_Syntax[4], strlen(this->_Syntax[4])))
	{
		this->Add(aIndex, (char*)(lpMsg->chatmsg + strlen(this->_Syntax[4])), 4);
		return true;
	}

	if (!_memicmp(lpMsg->chatmsg, this->_Syntax[5], strlen(this->_Syntax[5])))
	{
		this->Add(aIndex, (char*)(lpMsg->chatmsg + strlen(this->_Syntax[5])), 5);
		return true;
	}

	if (!_memicmp(lpMsg->chatmsg, this->_Syntax[8], strlen(this->_Syntax[8])))
	{
		this->Ware(aIndex, (char*)(lpMsg->chatmsg + strlen(this->_Syntax[8])));
		return true;
	}

	if (!_memicmp(lpMsg->chatmsg, this->_Syntax[11], strlen(this->_Syntax[11])))
	{
		this->Premiar(aIndex, (char*)(lpMsg->chatmsg + strlen(this->_Syntax[11])));
		return true;
	}

	if (!_memicmp(lpMsg->chatmsg, this->_Syntax[12], strlen(this->_Syntax[12])))
	{
		this->MoveAll(aIndex, (char*)(lpMsg->chatmsg + strlen(this->_Syntax[12])));
		return true;
	}

	if (!_memicmp(lpMsg->chatmsg, this->_Syntax[13], strlen(this->_Syntax[13])))
	{
		this->Skin(aIndex, (char*)(lpMsg->chatmsg + strlen(this->_Syntax[13])));
		return true;
	}

	if (!_memicmp(lpMsg->chatmsg, this->_Syntax[14], strlen(this->_Syntax[14])))
	{
		this->Move(aIndex, (char*)(lpMsg->chatmsg + strlen(this->_Syntax[14])));
		return true;
	}

	if (!_memicmp(lpMsg->chatmsg, this->_Syntax[16], strlen(this->_Syntax[16])))
	{
		this->Drop(aIndex, (char*)(lpMsg->chatmsg + strlen(this->_Syntax[16])));
		return true;
	}

	if (!_memicmp(lpMsg->chatmsg, this->_Syntax[17], strlen(this->_Syntax[17])))
	{
		this->Evento(aIndex, (char*)(lpMsg->chatmsg + strlen(this->_Syntax[17])));
		return true;
	}

	if (!_memicmp(lpMsg->chatmsg, this->_Syntax[19], strlen(this->_Syntax[19])))
	{
		this->Hide(aIndex, (char*)(lpMsg->chatmsg + strlen(this->_Syntax[19])));
		return true;
	}

	if (!_memicmp(lpMsg->chatmsg, Attack._Syntax, strlen(Attack._Syntax)))
	{
		Attack.Command(aIndex, (char*)(lpMsg->chatmsg + strlen(Attack._Syntax)));
		return true;
	}

	if (!_memicmp(lpMsg->chatmsg, Bank._Syntax, strlen(Bank._Syntax)))
	{
		Bank.Command(aIndex, (char*)(lpMsg->chatmsg + strlen(Bank._Syntax)));
		return true;
	}

#if(GS_CASTLE == 0)
	if (!_memicmp(lpMsg->chatmsg, QuizEvent._Syntax, strlen(QuizEvent._Syntax)))
	{
		QuizEvent.Command(aIndex, (char*)(lpMsg->chatmsg + strlen(QuizEvent._Syntax)));
		return true;
	}

	if (!_memicmp(lpMsg->chatmsg, Rank._Syntax, strlen(Rank._Syntax)))
	{
		Rank.Command(aIndex, (char*)(lpMsg->chatmsg + strlen(Rank._Syntax)));
		return true;
	}

	if (!_memicmp(lpMsg->chatmsg, Duel._Syntax[0], strlen(Duel._Syntax[0])))
	{
		Duel.Invitation(aIndex, (char*)(lpMsg->chatmsg + strlen(Duel._Syntax[0])));
		return true;
	}
#endif

	if (!_memicmp(lpMsg->chatmsg, Potion._Syntax, strlen(Potion._Syntax)))
	{
		Potion.Command(aIndex, (char*)(lpMsg->chatmsg + strlen(Potion._Syntax)));
		return true;
	}

	return false;
}

void Commands::Post(int aIndex, char* msg)
{
	if (strlen(msg) >= 1 && this->_Active[0] == true)
	{
		if (gObj[aIndex].Level < this->_Level[0])
		{
			Function.MsgOutput(aIndex, 1, "É necessário %d de level.", this->_Level[0]);
			return;
		}
		else if (gObj[aIndex].Money < this->_Zen[0])
		{
			Function.MsgOutput(aIndex, 1, "É necessário %d de zen.", this->_Zen[0]);
			return;
		}
		else if (this->_VipCount[0] == 1 && gObj[aIndex].Custom->VipCount < 1)
		{
			Function.MsgOutput(aIndex, 1, "Exclusivo apenas para vip's.");
			return;
		}

		DWORD Delay = (GetTickCount() - gObj[aIndex].Custom->Delay[0]) / 1000;

		if (Delay < this->_Delay)
		{
			Function.MsgOutput(aIndex, 1, "Aguarde %d %s para usar novamente.", (this->_Delay - Delay), (this->_Delay - Delay == 1) ? "segundo" : "segundos");
			return;
		}

		QuizEvent.Winner(aIndex, msg);

		sprintf(this->_Buffer, this->_Formato, msg);

		if (this->_Color == 0)
		{
			Function.Blue(gObj[aIndex].Name, this->_Buffer, aIndex);
		}
		else if (this->_Color == 1)
		{
			Function.Green(gObj[aIndex].Name, this->_Buffer, aIndex);
		}
		else if (this->_Color == 2)
		{
			Function.Yellow(gObj[aIndex].Name, this->_Buffer, aIndex);
		}

		gObj[aIndex].Custom->Delay[0] = GetTickCount();

		GCMoneySend(aIndex, gObj[aIndex].Money -= this->_Zen[0]);
	}
}

void Commands::Add(int aIndex, char* msg, int Status)
{
	int Pontos = atoi(msg);

	if (!this->_Active[1])
	{
		Function.MsgOutput(aIndex, 1, "Comando desabilitado.");
		return;
	}
	else if (strlen(msg) < 1 || Pontos <= 0)
	{
		Function.MsgOutput(aIndex, 1, "Erro de sintaxe!");
		Function.MsgOutput(aIndex, 1, "Exemplo -> %s <Número>", this->_Syntax[1]);
		Function.MsgOutput(aIndex, 1, "Exemplo -> %s <Número>", this->_Syntax[2]);
		Function.MsgOutput(aIndex, 1, "Exemplo -> %s <Número>", this->_Syntax[3]);
		Function.MsgOutput(aIndex, 1, "Exemplo -> %s <Número>", this->_Syntax[4]);
		Function.MsgOutput(aIndex, 1, "Exemplo -> %s <Número>", this->_Syntax[5]);
		return;
	}
	else if (gObj[aIndex].Level < this->_Level[1])
	{
		Function.MsgOutput(aIndex, 1, "É necessário %d de level.", this->_Level[1]);
		return;
	}
	else if (gObj[aIndex].Money < this->_Zen[1])
	{
		Function.MsgOutput(aIndex, 1, "É necessário %d de zen.", this->_Zen[1]);
		return;
	}
	else if (Pontos > gObj[aIndex].LevelUpPoint)
	{
		Function.MsgOutput(aIndex, 1, "Faltam %d pontos.", (Pontos - gObj[aIndex].LevelUpPoint));
		return;
	}
	else
	{
		if (Status == 1)
		{
			if ((gObj[aIndex].Strength + Pontos) > Setting._MaxStatus)
			{
				Function.MsgOutput(aIndex, 1, "O limite de pontos é %d", Setting._MaxStatus);
				return;
			}
			else
			{
				gObj[aIndex].Strength += Pontos;

				Function.MsgOutput(aIndex, 1, "Adicionado %d pontos em força.", Pontos);
			}
		}
		else if (Status == 2)
		{
			if ((gObj[aIndex].Dexterity + Pontos) > Setting._MaxStatus)
			{
				Function.MsgOutput(aIndex, 1, "O limite de pontos é %d", Setting._MaxStatus);
				return;
			}
			else
			{
				gObj[aIndex].Dexterity += Pontos;

				Function.MsgOutput(aIndex, 1, "Adicionado %d pontos em agilidade.", Pontos);
			}
		}
		else if (Status == 3)
		{
			if ((gObj[aIndex].Vitality + Pontos) > Setting._MaxStatus)
			{
				Function.MsgOutput(aIndex, 1, "O limite de pontos é %d", Setting._MaxStatus);
				return;
			}
			else
			{
				gObj[aIndex].Vitality += Pontos;

				gObj[aIndex].MaxLife += gObj[aIndex].VitalityToLife * Pontos;
				gObj[aIndex].Life = gObj[aIndex].MaxLife;
				gObj[aIndex].AddLife = 0;

				Function.MsgOutput(aIndex, 1, "Adicionado %d pontos em vitalidade.", Pontos);
			}
		}
		else if (Status == 4)
		{
			if ((gObj[aIndex].Energy + Pontos) > Setting._MaxStatus)
			{
				Function.MsgOutput(aIndex, 1, "O limite de pontos é %d", Setting._MaxStatus);
				return;
			}
			else
			{
				gObj[aIndex].Energy += Pontos;

				gObj[aIndex].MaxMana += gObj[aIndex].EnergyToMana * Pontos;
				gObj[aIndex].Mana = gObj[aIndex].MaxMana;
				gObj[aIndex].AddMana = 0;

				gObjSetBP(aIndex);
				gObj[aIndex].BP = gObj[aIndex].MaxBP / 2;
				gObj[aIndex].AddBP = 0;

				Function.MsgOutput(aIndex, 1, "Adicionado %d pontos em energia.", Pontos);
			}
		}
		else if (Status == 5 && gObj[aIndex].Class == LORD)
		{
			if ((gObj[aIndex].Leadership + Pontos) > Setting._MaxStatus)
			{
				Function.MsgOutput(aIndex, 1, "O limite de pontos é %d", Setting._MaxStatus);
				return;
			}
			else
			{
				gObj[aIndex].Leadership += Pontos;

				Function.MsgOutput(aIndex, 1, "Adicionado %d pontos em carisma.", Pontos);
			}
		}

		GCMoneySend(aIndex, gObj[aIndex].Money -= this->_Zen[1]);
		gObj[aIndex].LevelUpPoint -= Pontos;

		Function.UpdateCharacter(aIndex, false);
	}
}

void Commands::ReAdd(int aIndex)
{
	if (!this->_Active[2])
	{
		Function.MsgOutput(aIndex, 1, "Comando desabilitado.");
		return;
	}
	else if (gObj[aIndex].Level < this->_Level[2])
	{
		Function.MsgOutput(aIndex, 1, "É necessário %d de level.", this->_Level[2]);
		return;
	}
	else if (gObj[aIndex].Money < this->_Zen[2])
	{
		Function.MsgOutput(aIndex, 1, "É necessário %d de zen.", this->_Zen[2]);
		return;
	}

	int Pontos, Resto; WORD Class = gObj[aIndex].Class;

	Resto = Class == 0 ? 81 : Class == 1 ? 83 : Class == 2 ? 82 : Class == 3 ? 104 : 106;

	if (this->_Comando == 1)
	{
		Pontos = (gObj[aIndex].Strength + gObj[aIndex].Dexterity + gObj[aIndex].Vitality + gObj[aIndex].Energy + (Class == 4 ? gObj[aIndex].Leadership : 0)) - Resto;
	}
	else
	{
		Pontos = (gObj[aIndex].Strength + gObj[aIndex].Dexterity + gObj[aIndex].Vitality + gObj[aIndex].Energy) - Resto;
	}

	if (Pontos <= 0)
	{
		Function.MsgOutput(aIndex, 1, "Pontos insuficientes para redistribuição.");
		return;
	}

	gObj[aIndex].LevelUpPoint += Pontos;

	GCMoneySend(aIndex, gObj[aIndex].Money -= this->_Zen[2]);

	gObj[aIndex].Strength = Class == 0 ? 18 : Class == 1 ? 28 : Class == 2 ? 22 : Class == 3 ? 26 : 26;
	gObj[aIndex].Dexterity = Class == 0 ? 18 : Class == 1 ? 20 : Class == 2 ? 25 : Class == 3 ? 26 : 20;
	gObj[aIndex].Vitality = Class == 0 ? 15 : Class == 1 ? 25 : Class == 2 ? 20 : Class == 3 ? 26 : 20;
	gObj[aIndex].Energy = Class == 0 ? 30 : Class == 1 ? 10 : Class == 2 ? 15 : Class == 3 ? 26 : 15;

	if (this->_Comando == 1)
	{
		gObj[aIndex].Leadership = Class == 4 ? 25 : 0;
	}

	gObj[aIndex].MaxLife = Function.GetStatus(aIndex, Class, 0);
	gObj[aIndex].Life = gObj[aIndex].MaxLife;
	gObj[aIndex].AddLife = 0;
	gObj[aIndex].MaxMana = Function.GetStatus(aIndex, Class, 1);
	gObj[aIndex].Mana = gObj[aIndex].MaxMana;
	gObj[aIndex].AddMana = 0;
	gObjSetBP(aIndex);
	gObj[aIndex].BP = gObj[aIndex].MaxBP / 2;
	gObj[aIndex].AddBP = 0;

	Function.UpdateCharacter(aIndex, false);

	Function.MsgOutput(aIndex, 1, "%d disponiveis para distribuição.", gObj[aIndex].LevelUpPoint);
}

void Commands::Clear(int aIndex)
{
	if (!this->_Active[3])
	{
		Function.MsgOutput(aIndex, 1, "Comando desabilitado.");	
		return;
	}
	else if (gObj[aIndex].Level < this->_Level[3])
	{
		Function.MsgOutput(aIndex, 1, "É necessário %d de level.", this->_Level[3]);
		return;
	}
	else if (gObj[aIndex].Money < this->_Zen[3])
	{
		Function.MsgOutput(aIndex, 1, "É necessário %d de zen.", this->_Zen[3]);
		return;
	}
	else if (gObj[aIndex].Custom->InEvent == true || DeathEvent.PlayerStruct[aIndex]._InEvent == true 
		|| TheftEvent.PlayerStruct[aIndex]._InEvent == true)
	{
		Function.MsgOutput(aIndex, 1, "Proibido usar o comando no evento.");
		return;
	}
	else
	{
		if (gObj[aIndex].m_PK_Level != 3)
		{
			gObj[aIndex].m_PK_Level = 3;
			gObj[aIndex].m_PK_Count = 0;
			gObj[aIndex].m_PK_Time = 0;

			GCMoneySend(aIndex, gObj[aIndex].Money -= this->_Zen[3]);

			GCPkLevelSend(aIndex, gObj[aIndex].m_PK_Level);

			Function.MsgOutput(aIndex, 1, "Seu PK/Hero foi limpo com sucesso.");
		}
		else
		{
			Function.MsgOutput(aIndex, 1, "Você não é pk nem hero.");
		}
	}
}

void Commands::Ware(int aIndex, char* msg)
{
	gObj[aIndex].Custom->Vault = Manager.CheckVault(gObj[aIndex].AccountID);

	this->_Number = atoi(msg);

	gObj[aIndex].Custom->Delay[1] = (GetTickCount() - gObj[aIndex].Custom->Delay[2]) / 1000;

	if (!this->_Active[4])
	{
		Function.MsgOutput(aIndex, 1, "Comando desabilitado.");
		return;
	}
	else if (strlen(msg) < 1 || this->_Number < 0)
	{
		Function.MsgOutput(aIndex, 1, "Erro de sintaxe!");
		Function.MsgOutput(aIndex, 1, "Digite: %s <Número>", this->_Syntax[8]);
		Function.MsgOutput(aIndex, 1, "Exemplo -> %s 1", this->_Syntax[8]);
		return;
	}
	else if (gObj[aIndex].Level < this->_Level[4])
	{
		Function.MsgOutput(aIndex, 1, "É necessário %d de level.", this->_Level[4]);
		return;
	}
	else if (gObj[aIndex].Money < this->_Zen[4])
	{
		Function.MsgOutput(aIndex, 1, "É necessário %d de zen.", this->_Zen[4]);
		return;
	}
	else if (gObj[aIndex].m_IfState.use != 0)
	{
		Function.MsgOutput(aIndex, 1, "Feche todas as janelas para mudar de baú.");
		return;
	}
	else if (gObj[aIndex].Custom->Delay[1] < 10)
	{
		Function.MsgOutput(aIndex, 1, "Aguarde %d %s para usar novamente.", (10 - gObj[aIndex].Custom->Delay[1]), (10 - gObj[aIndex].Custom->Delay[1] == 1) ? "segundo" : "segundos");
		return;
	}
	else if (gObj[aIndex].Custom->Vault == this->_Number)
	{
		Function.MsgOutput(aIndex, 1, "O baú %d já está sendo utilizado.", this->_Number);
		return;
	}

	switch (gObj[aIndex].Custom->VipCount)
	{
	case 0:
	{
		if (this->_Number > this->_Ware[0])
		{
			Function.MsgOutput(aIndex, 1, "O seu limite de baús é %d", this->_Ware[0]);
			return;
		}
	}
	break;
	case 1:
	{
		if (this->_Number > this->_Ware[1])
		{
			Function.MsgOutput(aIndex, 1, "O seu limite de baús é %d", this->_Ware[1]);
			return;
		}
	}
	break;
	case 2:
	{
		if (this->_Number > this->_Ware[2])
		{
			Function.MsgOutput(aIndex, 1, "O seu limite de baús é %d", this->_Ware[2]);
			return;
		}
	}
	break;
	case 3:
	{
		if (this->_Number > this->_Ware[3])
		{
			Function.MsgOutput(aIndex, 1, "O seu limite de baús é %d", this->_Ware[3]);
			return;
		}
	}
	break;
	}

	Manager.ExecFormat("EXEC MuOnline.dbo.MUDAR_BAU '%s', %d", gObj[aIndex].AccountID, this->_Number);

	gObj[aIndex].m_IfState.state = 0;
	gObj[aIndex].m_IfState.type = 0;
	gObj[aIndex].m_IfState.use = 0;
	gObj[aIndex].LoadWareHouseInfo = 0;
	gObj[aIndex].WarehouseSave = 0;

	gObj[aIndex].Custom->Delay[2] = GetTickCount();

	GCMoneySend(aIndex, gObj[aIndex].Money -= this->_Zen[4]);

	Function.MsgOutput(aIndex, 1, "O baú %d foi selecionado com sucesso.", this->_Number);
}

void Commands::Money(int aIndex)
{
	if (this->_Active[5] == true)
	{
		if (this->_VipCount[1] == 1 && gObj[aIndex].Custom->VipCount < 1)
		{
			Function.MsgOutput(aIndex, 1, "Exclusivo apenas para vip's.");
			return;
		}

		Function.MsgOutput(aIndex, 1, "Zen adicionado com sucesso.");

		GCMoneySend(aIndex, gObj[aIndex].Money = this->_Zen[5]);
	}
}

void Commands::Online(int aIndex)
{
	if (!this->_Active[6])
	{
		Function.MsgOutput(aIndex, 1, "Comando desabilitado.");
		return;
	}
	else if (gObj[aIndex].Money < this->_Zen[6])
	{
		Function.MsgOutput(aIndex, 1, "É necessário %d de zen.", this->_Zen[4]);
		return;
	}

	DWORD PlayerCount = 0, GMCount = 0;

	for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
	{
		if (gObj[i].Authority == 1 && gObj[i].Connected == PLAYER_PLAYING)
		{
			PlayerCount++;
		}
		else if (gObj[i].Authority > 1 && gObj[i].Connected == 3)
		{
			GMCount++;
		}
	}

	Function.MsgOutput(aIndex, 1, "Players onlines: %d :: GM'S onlines: %d :: Total: %d", PlayerCount, GMCount, (PlayerCount + GMCount));

	GCMoneySend(aIndex, gObj[aIndex].Money -= this->_Zen[6]);
}

void Commands::Premiar(int aIndex, char* msg)
{
	if (Authority.Check(&gObj[aIndex], 0) == true)
	{
		if (!this->_Active[7])
		{
			Function.MsgOutput(aIndex, 1, "Comando desabilitado.");
			return;
		}

		memset(this->_Name, 0, sizeof(this->_Name));

		this->_Number = 0;

		sscanf(msg, "%s %d", this->_Name, &this->_Number);

		int Index = Function.GetPlayerIndex(this->_Name);

		if (strlen(msg) < 1 || this->_Number <= 0)
		{
			Function.MsgOutput(aIndex, 1, "Erro de sintaxe!");
			Function.MsgOutput(aIndex, 1, "Digite: %s <Nome> <Número>", this->_Syntax[11]);
			Function.MsgOutput(aIndex, 1, "Exemplo -> %s Angel 1", this->_Syntax[11]);
			return;
		}
		else if (gObj[Index].Connected < 3)
		{
			Function.MsgOutput(aIndex, 1, "O Personagem não se encontra.");
			return;
		}

		Manager.ExecFormat(Query._Query[6], this->_Number, gObj[Index].AccountID);

		Function.AllServerAnnounce(this->_Notice, this->_Name, this->_Number);
	}
	else
	{
		Function.MsgOutput(aIndex, 1, "Você não possui autoridade.");
	}
}

void Commands::MoveAll(int aIndex, char* msg)
{
	if (Authority.Check(&gObj[aIndex], 1) == true)
	{
		if (!this->_Active[8])
		{
			Function.MsgOutput(aIndex, 1, "Comando desabilitado.");
			return;
		}
		else if (strlen(msg) < 1)
		{
			Function.MsgOutput(aIndex, 1, "Erro de sintaxe!");
			Function.MsgOutput(aIndex, 1, "Digite: %s <Mapa> <X> <Y>", this->_Syntax[12]);
			Function.MsgOutput(aIndex, 1, "Exemplo -> %s 0 125 125", this->_Syntax[12]);
			return;
		}

		int Mapa, X, Y;

		sscanf(msg, "%d %d %d", &Mapa, &X, &Y);

		for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
		{
			if (gObj[i].AuthorityCode == 0)
			{
				gObjTeleport(i, Mapa, X, Y);
			}
		}

		Function.MsgOutput(aIndex, 1, "Movidos com sucesso.");
	}
	else
	{
		Function.MsgOutput(aIndex, 1, "Você não possui autoridade.");
	}
}

void Commands::Skin(int aIndex, char* msg)
{
	if (Authority.Check(&gObj[aIndex], 2) == true)
	{
		if (!this->_Active[9])
		{
			Function.MsgOutput(aIndex, 1, "Comando desabilitado.");
			return;
		}
		else if (strlen(msg) < 1)
		{
			Function.MsgOutput(aIndex, 1, "Erro de sintaxe!");
			Function.MsgOutput(aIndex, 1, "Digite: %s <Nome> <Número>", this->_Syntax[13]);
			Function.MsgOutput(aIndex, 1, "Exemplo -> %s Angel 10", this->_Syntax[13]);
			return;
		}

		memset(this->_Name, 0, sizeof(this->_Name));

		this->_Number = -1;

		sscanf(msg, "%s %d", this->_Name, &this->_Number);

		int Index = Function.GetPlayerIndex(this->_Name);

		if (gObj[Index].Connected < 3)
		{
			Function.MsgOutput(aIndex, 1, "Personagem não se encontra.");
			return;
		}

		gObj[Index].m_Change = this->_Number;
		gObjViewportListProtocolCreate(&gObj[Index]);

		if (Index == aIndex)
		{
			Function.MsgOutput(aIndex, 1, "Você mudou de skin com sucesso.");
		}
		else
		{
			Function.MsgOutput(aIndex, 1, "Skin adicionada.");
			Function.MsgOutput(Index, 1, "Skin adicionada por %s", gObj[aIndex].Name);
		}
	}
	else
	{
		Function.MsgOutput(aIndex, 1, "Você não possui autoridade.");
	}
}

void Commands::Move(int aIndex, char* msg)
{
	if (Authority.Check(&gObj[aIndex], 3) == true)
	{
		if (!this->_Active[10])
		{
			Function.MsgOutput(aIndex, 1, "Comando desabilitado.");
			return;
		}
		else if (strlen(msg) < 1)
		{
			Function.MsgOutput(aIndex, 1, "Erro de sintaxe!");
			Function.MsgOutput(aIndex, 1, "Digite: %s <Nome> <Mapa> <X> <Y>", this->_Syntax[14]);
			Function.MsgOutput(aIndex, 1, "Exemplo -> %s Angel 0 125 125", this->_Syntax[14]);
			return;
		}

		memset(this->_Name, 0, sizeof(this->_Name));

		int Mapa, X, Y;

		sscanf(msg, "%s %d %d %d", &this->_Name, &Mapa, &X, &Y);

		int Index = Function.GetPlayerIndex(this->_Name);

		if (gObj[Index].Connected < 3)
		{
			Function.MsgOutput(aIndex, 1, "Personagem não se encontra.");
			return;
		}

		gObjTeleport(gObj[Index].m_Index, Mapa, X, Y);

		if (Index == aIndex)
		{
			Function.MsgOutput(aIndex, 1, "Você foi movido com sucesso.");
		}
		else
		{
			Function.MsgOutput(aIndex, 1, "Movido com sucesso.");
			Function.MsgOutput(Index, 1, "Você foi movido por %s", gObj[aIndex].Name);
		}
	}
	else
	{
		Function.MsgOutput(aIndex, 1, "Você não possui autoridade.");
	}
}

void Commands::FireWork(int aIndex)
{
	if (Authority.Check(&gObj[aIndex], 4) == true)
	{
		if (!this->_Active[11])
		{
			Function.MsgOutput(aIndex, 1, "Comando desabilitado.");
			return;
		}

		Function.FireWork(aIndex);
	}
	else
	{
		Function.MsgOutput(aIndex, 1, "Você não possui autoridade.");
	}
}

void Commands::Drop(int aIndex, char* msg)
{
	if (Authority.Check(&gObj[aIndex], 5) == true)
	{
		if (!this->_Active[12])
		{
			Function.MsgOutput(aIndex, 1, "Comando desabilitado.");
			return;
		}

		int Type = -1, Index = -1, Level = -1, Skill, Luck, Option, Excelente, Ancient;

		sscanf(msg, "%d %d %d %d %d %d %d %d", &Type, &Index, &Level, &Skill, &Luck, &Option, &Excelente, &Ancient);

		if (strlen(msg) < 1 || Type == -1 || Index == -1 || Level == -1)
		{
			Function.MsgOutput(aIndex, 1, "Erro de sintaxe!");
			Function.MsgOutput(aIndex, 1, "Digite: %s <Type> <Index> <Level> <Skill> <Luck> <Option> <Exc> <Anc>", this->_Syntax[16]);
			return;
		}

		int Item = ITEMGET(Type, Index);

		ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, Item, Level, 0, Skill, Luck, Option, aIndex, Excelente, Ancient);

		Function.MsgOutput(aIndex, 1, "Item criado com sucesso.");
	}
	else
	{
		Function.MsgOutput(aIndex, 1, "Você não possui autoridade.");
	}
}

void Commands::Evento(int aIndex, char* msg)
{
	if (Authority.Check(&gObj[aIndex], 6) == true && this->_Active[13] == true)
	{
		memset(this->_Name, 0, sizeof(this->_Name));

		this->_MapNumber = -1, this->_X = -1, this->_Y = -1;

		sscanf(msg, "%s %d %d %d", &this->_Name, &this->_MapNumber, &this->_X, &this->_Y);

		if (strlen(msg) < 1 || this->_MapNumber == -1 || this->_X == -1 || this->_Y == -1 || this->_Count > 60)
		{
			Function.MsgOutput(aIndex, 1, "Erro de sintaxe!");
			Function.MsgOutput(aIndex, 1, "Digite: %s <Nome do evento> <Mapa> <X> <Y>", this->_Syntax[17]);
			return;
		}

		for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
		{
			if (gObj[i].Connected == PLAYER_PLAYING)
			{
				Function.MsgOutput(i, 0, "Evento %s Inicializado!", this->_Name);
				Function.MsgOutput(i, 0, "Para participar, utilize o comando: %s", this->_Syntax[18]);
			}
		}

		this->_Event = true; this->_Count = 20;

		_beginthread(&Commands::Thread, NULL, 0);

		gObjTeleport(aIndex, this->_MapNumber, this->_X, this->_Y);
	}
}

void Commands::Ir(int aIndex)
{
	if (gObj[aIndex].AuthorityCode < 1 && this->_Active[13] == true)
	{
		if (gObj[aIndex].Level < 50)
		{
			Function.MsgOutput(aIndex, 1, "É necessário 50 de level.");
			return;
		}
		else if (gObj[aIndex].Custom->Waiting[1] == true)
		{
			Function.MsgOutput(aIndex, 1, "Você já está registrado no evento. Aguarde.");
			return;
		}
		else if (this->_Event == true)
		{
			Function.MsgOutput(aIndex, 1, "Aguarde você será movido em instantes.");

			gObj[aIndex].Custom->Waiting[1] = true;
		}
		else
		{
			Function.MsgOutput(aIndex, 1, "Nenhum evento inicializado.");
		}
	}
}

void Commands::Thread(void * lpParam)
{
	while (Command._Count > 1)
	{
		Command._Count--;

		for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
		{
			if (gObj[i].Connected == 3)
			{
				Function.MsgOutput(i, 0, "Evento %s inicia em %d Segundo(s)", Command._Name, Command._Count);

				Function.MsgOutput(i, 1, "Para participar, utilize o comando: %s", Command._Syntax[18]);
			}
		}

		Sleep(1000);
	}

	Function.AllServerAnnounce("Inscrições para o evento encerradas!");

	Command._Event = false; Command._Count = 0;

	for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
	{
		if (gObj[i].Connected == PLAYER_PLAYING)
		{
			if (gObj[i].Custom->Waiting[1] == true)
			{
				gObjTeleport(i, Command._MapNumber, Command._X, Command._Y);

				gObj[i].Custom->Waiting[1] = false;
			}
		}
	}
}

void Commands::Hide(int aIndex, char* msg)
{
	if (Authority.Check(&gObj[aIndex], 7) == true && this->_Active[14] == true)
	{
		memset(this->_Name, 0, sizeof(this->_Name));

		sscanf(msg, "%s", &this->_Name);

		if (strlen(msg) < 2 || this->_Name == 0 || strcmpi(this->_Name, "on") && strcmpi(this->_Name, "off"))
		{
			Function.MsgOutput(aIndex, 1, "Erro de sintaxe!");
			Function.MsgOutput(aIndex, 1, "Digite: %s on/off.", this->_Syntax[19]);
			return;
		}

		if (!strcmpi(this->_Name, "off"))
		{
			if (gObj[aIndex].Custom->Hidden == true)
			{
				gObj[aIndex].Custom->Hidden = false;

				gObj[aIndex].m_ViewSkillState &= ~16384;

				GCStateInfoSend(&gObj[aIndex], 0, 16384);
				gObjViewportListProtocolCreate(&gObj[aIndex]);

				Function.MsgOutput(aIndex, 1, "Invisibilidade removida.");
			}
		}
		else if (!strcmpi(this->_Name, "on"))
		{
			if (gObj[aIndex].Custom->Hidden == false)
			{
				gObj[aIndex].Custom->Hidden = true;

				gObj[aIndex].m_ViewSkillState |= 16384;

				GCStateInfoSend(&gObj[aIndex], 1, 16384);
				gObjViewportListProtocolDestroy(&gObj[aIndex]);

				Function.MsgOutput(aIndex, 1, "Você está invisível!");
			}
		}
	}
}

void Commands::Full(int aIndex)
{
	int Points = 0;

	Points += 32767 - gObj[aIndex].Strength;
    Points += 32767 - gObj[aIndex].Dexterity;
	Points += 32767 - gObj[aIndex].Vitality;
	Points += 32767 - gObj[aIndex].Energy;

	if (gObj[aIndex].Class == LORD)
	{
		Points += 32767 - gObj[aIndex].Leadership;
	}

	if (Points == 0)
	{
		Function.MsgOutput(aIndex, 1, "Você já está com o máximo de pontos em todos atributos.");
		return;
	}
	else if (gObj[aIndex].LevelUpPoint < Points)
	{
		Function.MsgOutput(aIndex, 1, "Você não possui pontos suficientes.");
		return;
	}
	else if (gObj[aIndex].m_IfState.use != 0)
	{
		Function.MsgOutput(aIndex, 1, "Feche todas as janelas para executar o comando.");
		return;
	}

	gObj[aIndex].LevelUpPoint -= Points;

	gObj[aIndex].Strength = 32767;
	gObj[aIndex].Dexterity = 32767;
	gObj[aIndex].Vitality = 32767;
	gObj[aIndex].Energy = 32767;

	if (gObj[aIndex].Class == LORD)
	{
		gObj[aIndex].Leadership = 32767;
	}

	gObj[aIndex].Life = gObj[aIndex].MaxLife;
	gObj[aIndex].AddLife = 0;
	gObj[aIndex].Mana = gObj[aIndex].MaxMana;
	gObj[aIndex].AddMana = 0;
	gObj[aIndex].MaxLife = Function.GetStatus(aIndex, gObj[aIndex].Class, 0);
	gObj[aIndex].MaxMana = Function.GetStatus(aIndex, gObj[aIndex].Class, 1);
	gObjSetBP(aIndex);
	gObj[aIndex].BP = gObj[aIndex].MaxBP / 2;
	gObj[aIndex].AddBP = 0;

	Function.UpdateCharacter(aIndex, false);

	Function.MsgOutput(aIndex, 1, "Pontos distribuidos com sucesso!");
}

Commands Command;