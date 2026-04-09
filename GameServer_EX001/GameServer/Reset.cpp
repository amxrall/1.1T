#include "StdAfx.h"

bool cReset::Load()
{
	this->_Count = 0;

	memset(this->ResetStruct, 0, sizeof(this->ResetStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Comandos\\Reset.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_Type = Section.Rows[0].GetInt(1);
		strcpy_s(&this->_Syntax[0], sizeof(this->_Syntax), (Section.Rows[0].GetStringPtr(2)));

		this->_Teleport[0] = Section.Rows[1].GetInt(0);
		this->_Teleport[1] = Section.Rows[2].GetInt(0);
		this->_Teleport[2] = Section.Rows[3].GetInt(0);
		this->_Teleport[3] = Section.Rows[4].GetInt(0);

		this->_Remove[0] = Section.Rows[1].GetInt(1);
		this->_Remove[1] = Section.Rows[2].GetInt(1);
		this->_Remove[2] = Section.Rows[3].GetInt(1);
		this->_Remove[3] = Section.Rows[4].GetInt(1);

		this->_Comando[0] = Section.Rows[1].GetInt(2);
		this->_Comando[1] = Section.Rows[2].GetInt(2);
		this->_Comando[2] = Section.Rows[3].GetInt(2);
		this->_Comando[3] = Section.Rows[4].GetInt(2);

		this->_Level[1] = Section.Rows[1].GetInt(3);
		this->_Level[2] = Section.Rows[2].GetInt(3);
		this->_Level[3] = Section.Rows[3].GetInt(3);
		this->_Level[4] = Section.Rows[4].GetInt(3);

		this->_Experience[1] = Section.Rows[1].GetInt(4);
		this->_Experience[2] = Section.Rows[2].GetInt(4);
		this->_Experience[3] = Section.Rows[3].GetInt(4);
		this->_Experience[4] = Section.Rows[4].GetInt(4);
	}

	if (Group.GetSection(1, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->ResetStruct[this->_Count]._VipCount = Section.Rows[i].GetInt(0);
			this->ResetStruct[this->_Count]._ResetsMin = Section.Rows[i].GetInt(1);
			this->ResetStruct[this->_Count]._ResetsMax = Section.Rows[i].GetInt(2);
			this->ResetStruct[this->_Count]._Points = Section.Rows[i].GetInt(3);
			this->ResetStruct[this->_Count]._Level = Section.Rows[i].GetInt(4);
			this->ResetStruct[this->_Count]._Money = Section.Rows[i].GetInt(5);
			this->ResetStruct[this->_Count]._Experience = Section.Rows[i].GetInt(6);
			this->ResetStruct[this->_Count]._NpcIndex = Section.Rows[i].GetInt(7);
			this->ResetStruct[this->_Count]._MapNPC = Section.Rows[i].GetInt(8);
			this->ResetStruct[this->_Count]._CordX = Section.Rows[i].GetInt(9);
			this->ResetStruct[this->_Count]._CordY = Section.Rows[i].GetInt(10);
			this->_Count++;
		}
	}

	return true;
}
void cReset::GetNpcReset(int aIndex, LPOBJ lpNpc) // OK
{
	int ResetCount = Manager.ResetCount(gObj[aIndex].Name) + 1;

	for (int i = 0; i < this->_Count; i++)
	{
		if (gObj[aIndex].Custom->VipCount == this->ResetStruct[i]._VipCount)
		{
			if (lpNpc->Class == this->ResetStruct[i]._NpcIndex && lpNpc->MapNumber == this->ResetStruct[i]._MapNPC && lpNpc->X == this->ResetStruct[i]._CordX && lpNpc->Y == this->ResetStruct[i]._CordY && (ResetCount >= this->ResetStruct[i]._ResetsMin && ResetCount <= this->ResetStruct[i]._ResetsMax))
			{
				//LogAddTD("Linha vip: %d / %d", this->ResetStruct[i]._VipCount, gObj[aIndex].Custom->VipCount);
				Reset.Run(aIndex);
			}
		}
	}
}
void cReset::Run(int aIndex)
{
	if (this->_Active == true)
	{
		int ResetCount = Manager.ResetCount(gObj[aIndex].Name) + 1;

		for (int i = 0; i < this->_Count; i++)
		{
			if (gObj[aIndex].Custom->VipCount == this->ResetStruct[i]._VipCount)
			{
				if (ResetCount >= this->ResetStruct[i]._ResetsMin && ResetCount <= this->ResetStruct[i]._ResetsMax || this->ResetStruct[i]._ResetsMax == -1)
				{
					if (gObj[aIndex].Level < this->ResetStruct[i]._Level)
					{
						Function.MsgOutput(aIndex, 1, "É necessário %d de level.", this->ResetStruct[i]._Level);
						return;
					}
					else if (gObj[aIndex].Money < this->ResetStruct[i]._Money)
					{
						Function.MsgOutput(aIndex, 1, "É necessário %d de zen.", this->ResetStruct[i]._Money);
						return;
					}
					else if (this->_Remove[gObj[aIndex].Custom->VipCount] == 0 && !Function.CheckItem(aIndex))
					{
						Function.MsgOutput(aIndex, 1, "Remova todos os itens.");
						return;
					}
					else if (gObj[aIndex].Custom->InEvent == true || DeathEvent.PlayerStruct[aIndex]._InEvent == true 
						|| TheftEvent.PlayerStruct[aIndex]._InEvent == true)
					{
						Function.MsgOutput(aIndex, 1, "Proibido usar o comando no evento.");
						return;
					}

					gObj[aIndex].Custom->ResetCount = ResetCount;

					gObj[aIndex].Experience = 0;

					gObj[aIndex].Money -= this->ResetStruct[i]._Money;

					if (this->_Teleport[gObj[aIndex].Custom->VipCount] == 1)
					{
						gObj[aIndex].Level = 1;
					}
					else if (this->_Teleport[gObj[aIndex].Custom->VipCount] == 0)
					{
						gObj[aIndex].Level = 6;
					}

					GCMoneySend(aIndex, gObj[aIndex].Money);

					if (this->_Type == 2)
					{
						WORD Class = gObj[aIndex].Class;

						gObj[aIndex].LevelUpPoint = 0;

						for (int x = (i - 1); x >= 0; x--)
						{
							if (this->ResetStruct[x]._VipCount != this->ResetStruct[i]._VipCount) break;

							gObj[aIndex].LevelUpPoint += (this->ResetStruct[x]._ResetsMax - (this->ResetStruct[x]._ResetsMin - 1)) * this->ResetStruct[x]._Points;

							ResetCount -= this->ResetStruct[x]._ResetsMax - (this->ResetStruct[x]._ResetsMin - 1);
						}

						gObj[aIndex].LevelUpPoint += ResetCount * this->ResetStruct[i]._Points;

						gObj[aIndex].Strength = Class == 0 ? 18 : Class == 1 ? 28 : Class == 2 ? 22 : Class == 3 ? 26 : 26;
						gObj[aIndex].Dexterity = Class == 0 ? 18 : Class == 1 ? 20 : Class == 2 ? 25 : Class == 3 ? 26 : 20;
						gObj[aIndex].Vitality = Class == 0 ? 15 : Class == 1 ? 25 : Class == 2 ? 20 : Class == 3 ? 26 : 20;
						gObj[aIndex].Energy = Class == 0 ? 30 : Class == 1 ? 10 : Class == 2 ? 15 : Class == 3 ? 26 : 15;

						if (this->_Comando[gObj[aIndex].Custom->VipCount] == 1)
						{
							gObj[aIndex].Leadership = Class == 4 ? 25 : 0;
						}

						gObj[aIndex].Life = gObj[aIndex].MaxLife;
						gObj[aIndex].AddLife = 0;
						gObj[aIndex].Mana = gObj[aIndex].MaxMana;
						gObj[aIndex].AddMana = 0;
						gObj[aIndex].MaxLife = Function.GetStatus(aIndex, Class, 0);
						gObj[aIndex].MaxMana = Function.GetStatus(aIndex, Class, 1);
						gObjSetBP(aIndex);
						gObj[aIndex].BP = gObj[aIndex].MaxBP / 2;
						gObj[aIndex].AddBP = 0;
					}

					if (this->_Teleport[gObj[aIndex].Custom->VipCount] == 1)
					{
						if (gObj[aIndex].Class == ELF)
						{
							int X = 171 + rand() % 6;
							int Y = 108 + rand() % 8;

							gObjTeleport(aIndex, 3, X, Y);
						}
						else
						{
							int X = 133 + rand() % 15;
							int Y = 118 + rand() % 15;

							gObjTeleport(aIndex, 0, X, Y);
						}
					}

					Function.UpdateCharacter(aIndex, true);

					Manager.ExecFormat(Query._Query[0], gObj[aIndex].Name);

					if (gObj[aIndex].DbClass == 3 || gObj[aIndex].DbClass == 19 || gObj[aIndex].DbClass == 35 || gObj[aIndex].DbClass == 50 || gObj[aIndex].DbClass == 66)
					{
						BYTE Effect = (gObj[aIndex].Class * 32) + 24;
						GCSendQuestPrize(aIndex, 0xDC, Effect);
						gObjViewportListProtocolCreate(&gObj[aIndex]);
					}

					Function.MsgOutput(aIndex, 1, "Reset efetuado com sucesso!");
					Function.MsgOutput(aIndex, 1, "Resets: %d / Pontos: %d", gObj[aIndex].Custom->ResetCount, gObj[aIndex].LevelUpPoint);
				}
			}
		}
	}
}

cReset Reset;
