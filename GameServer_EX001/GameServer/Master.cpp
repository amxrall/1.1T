#include "StdAfx.h"

cMaster::cMaster() : _Active(false)
{
}

bool cMaster::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Comandos\\Master.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		strcpy_s(this->_Syntax, sizeof(this->_Syntax), (Section.Rows[0].GetStringPtr(1)));

		this->_Level[0] = Section.Rows[1].GetInt(0);
		this->_Zen[0] = Section.Rows[1].GetInt(1);
		this->_Remove[0] = Section.Rows[1].GetInt(2);
		this->_Return[0] = Section.Rows[1].GetInt(3);
		this->_NeedFor[0] = Section.Rows[1].GetInt(4);
		this->_NeedAgi[0] = Section.Rows[1].GetInt(5);
		this->_NeedVit[0] = Section.Rows[1].GetInt(6);
		this->_NeedEne[0] = Section.Rows[1].GetInt(7);
		this->_Resets[0] = Section.Rows[1].GetInt(8);

		this->_Level[1] = Section.Rows[2].GetInt(0);
		this->_Zen[1] = Section.Rows[2].GetInt(1);
		this->_Remove[1] = Section.Rows[2].GetInt(2);
		this->_Return[1] = Section.Rows[2].GetInt(3);
		this->_NeedFor[1] = Section.Rows[2].GetInt(4);
		this->_NeedAgi[1] = Section.Rows[2].GetInt(5);
		this->_NeedVit[1] = Section.Rows[2].GetInt(6);
		this->_NeedEne[1] = Section.Rows[2].GetInt(7);
		this->_Resets[1] = Section.Rows[2].GetInt(8);

		this->_Level[2] = Section.Rows[3].GetInt(0);
		this->_Zen[2] = Section.Rows[3].GetInt(1);
		this->_Remove[2] = Section.Rows[3].GetInt(2);
		this->_Return[2] = Section.Rows[3].GetInt(3);
		this->_NeedFor[2] = Section.Rows[3].GetInt(4);
		this->_NeedAgi[2] = Section.Rows[3].GetInt(5);
		this->_NeedVit[2] = Section.Rows[3].GetInt(6);
		this->_NeedEne[2] = Section.Rows[3].GetInt(7);
		this->_Resets[2] = Section.Rows[3].GetInt(8);

		this->_Level[3] = Section.Rows[4].GetInt(0);
		this->_Zen[3] = Section.Rows[4].GetInt(1);
		this->_Remove[3] = Section.Rows[4].GetInt(2);
		this->_Return[3] = Section.Rows[4].GetInt(3);
		this->_NeedFor[3] = Section.Rows[4].GetInt(4);
		this->_NeedAgi[3] = Section.Rows[4].GetInt(5);
		this->_NeedVit[3] = Section.Rows[4].GetInt(6);
		this->_NeedEne[3] = Section.Rows[4].GetInt(7);
		this->_Resets[3] = Section.Rows[4].GetInt(8);
	}

	return true;
}

void cMaster::Run(int aIndex)
{
	if (this->_Active)
	{
		gObj[aIndex].Custom->ResetCount = Manager.ResetCount(gObj[aIndex].Name);

		if (this->_Level[gObj[aIndex].Custom->VipCount] > gObj[aIndex].Level)
		{
			Function.MsgOutput(aIndex, 1, "É necessário %d de level.", this->_Level[gObj[aIndex].Custom->VipCount]);
			return;
		}
		else if (this->_Zen[gObj[aIndex].Custom->VipCount] > gObj[aIndex].Money)
		{
			Function.MsgOutput(aIndex, 1, "É necessário %d de zen.", this->_Zen[gObj[aIndex].Custom->VipCount]);
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
		else if (gObj[aIndex].Strength < this->_NeedFor[gObj[aIndex].Custom->VipCount] && this->_NeedFor[gObj[aIndex].Custom->VipCount] > 0)
		{
			Function.MsgOutput(aIndex, 1, "Você não possui força %d", this->_NeedFor[gObj[aIndex].Custom->VipCount]);
			return;
		}
		else if (gObj[aIndex].Dexterity < this->_NeedAgi[gObj[aIndex].Custom->VipCount] && this->_NeedAgi[gObj[aIndex].Custom->VipCount] > 0)
		{
			Function.MsgOutput(aIndex, 1, "Você não possui agilidade %d", this->_NeedAgi[gObj[aIndex].Custom->VipCount]);
			return;
		}
		else if (gObj[aIndex].Vitality < this->_NeedVit[gObj[aIndex].Custom->VipCount] && this->_NeedVit[gObj[aIndex].Custom->VipCount] > 0)
		{
			Function.MsgOutput(aIndex, 1, "Você não possui vitalidade %d", this->_NeedVit[gObj[aIndex].Custom->VipCount]);
			return;
		}
		else if (gObj[aIndex].Energy < this->_NeedEne[gObj[aIndex].Custom->VipCount] && this->_NeedEne[gObj[aIndex].Custom->VipCount] > 0)
		{
			Function.MsgOutput(aIndex, 1, "Você não possui energia %d", this->_NeedEne[gObj[aIndex].Custom->VipCount]);
			return;
		}
		else if (gObj[aIndex].Custom->ResetCount < this->_Resets[gObj[aIndex].Custom->VipCount] && this->_Resets[gObj[aIndex].Custom->VipCount] > 0)
		{
			Function.MsgOutput(aIndex, 1, "Você não possui resets %d", this->_Resets[gObj[aIndex].Custom->VipCount]);
			return;
		}
		else
		{
			gObj[aIndex].Custom->MasterCount = Manager.MasterCount(gObj[aIndex].Name) + 1;

			gObj[aIndex].Experience = 0;

			gObj[aIndex].Level = 1;

			gObj[aIndex].Money -= this->_Zen[gObj[aIndex].Custom->VipCount];

			GCMoneySend(aIndex, gObj[aIndex].Money);

			if (this->_Resets[gObj[aIndex].Custom->VipCount] == -1)
			{
				Manager.ExecFormat("UPDATE Character SET Resets = 0 WHERE Name = '%s'", gObj[aIndex].Name);

				gObj[aIndex].LevelUpPoint = 0;

				gObj[aIndex].Custom->ResetCount = 0;
			}
			else if (this->_Resets[gObj[aIndex].Custom->VipCount] > 0)
			{
				Manager.ExecFormat("UPDATE Character SET Resets = Resets - %d WHERE Name = '%s'", this->_Resets[gObj[aIndex].Custom->VipCount], gObj[aIndex].Name);

				gObj[aIndex].Custom->ResetCount -= this->_Resets[gObj[aIndex].Custom->VipCount];

				for (int i = 0; i < Reset._Count; i++)
				{
					if (gObj[aIndex].Custom->VipCount == Reset.ResetStruct[i]._VipCount)
					{
						gObj[aIndex].LevelUpPoint = 0;

						for (int x = (i - 1); x >= 0; x--)
						{
							if (Reset.ResetStruct[x]._VipCount != Reset.ResetStruct[i]._VipCount) break;

							gObj[aIndex].LevelUpPoint += (Reset.ResetStruct[x]._ResetsMax - (Reset.ResetStruct[x]._ResetsMin - 1)) * Reset.ResetStruct[x]._Points;

							gObj[aIndex].Custom->ResetCount -= Reset.ResetStruct[x]._ResetsMax - (Reset.ResetStruct[x]._ResetsMin - 1);
						}

						gObj[aIndex].LevelUpPoint += gObj[aIndex].Custom->ResetCount * Reset.ResetStruct[i]._Points;
					}
				}
			}

			WORD Class = gObj[aIndex].Class;

			gObj[aIndex].Strength = Class == 0 ? 18 : Class == 1 ? 28 : Class == 2 ? 22 : Class == 3 ? 26 : 26;
			gObj[aIndex].Dexterity = Class == 0 ? 18 : Class == 1 ? 20 : Class == 2 ? 25 : Class == 3 ? 26 : 20;
			gObj[aIndex].Vitality = Class == 0 ? 15 : Class == 1 ? 25 : Class == 2 ? 20 : Class == 3 ? 26 : 20;
			gObj[aIndex].Energy = Class == 0 ? 30 : Class == 1 ? 10 : Class == 2 ? 15 : Class == 3 ? 26 : 15;

			gObj[aIndex].Life = gObj[aIndex].MaxLife;
			gObj[aIndex].AddLife = 0;
			gObj[aIndex].Mana = gObj[aIndex].MaxMana;
			gObj[aIndex].AddMana = 0;
			gObj[aIndex].MaxLife = Function.GetStatus(aIndex, Class, 0);
			gObj[aIndex].MaxMana = Function.GetStatus(aIndex, Class, 1);
			gObjSetBP(aIndex);
			gObj[aIndex].BP = gObj[aIndex].MaxBP / 2;
			gObj[aIndex].AddBP = 0;

			Manager.ExecFormat(Query._Query[1], gObj[aIndex].Name);

			switch (gObj[aIndex].Custom->VipCount)
			{
			case 0:
			{
				Manager.ExecFormat(Query._Query[2], gObj[aIndex].AccountID);
			}
			break;
			case 1:
			{
				Manager.ExecFormat(Query._Query[3], gObj[aIndex].AccountID);
			}
			break;
			case 2:
			{
				Manager.ExecFormat(Query._Query[4], gObj[aIndex].AccountID);
			}
			break;
			case 3:
			{
				Manager.ExecFormat(Query._Query[5], gObj[aIndex].AccountID);
			}
			break;
			}

			if (this->_Return[gObj[aIndex].Custom->VipCount] == 1)
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

			Function.MsgOutput(aIndex, 1, "Master reset efetuado com sucesso!");

			if (this->_Resets[gObj[aIndex].Custom->VipCount] > 0 || this->_Resets[gObj[aIndex].Custom->VipCount] == -1)
			{
				Function.MsgOutput(aIndex, 1, "Master resets: %d / Resets: %d", gObj[aIndex].Custom->MasterCount, gObj[aIndex].Custom->ResetCount);
			}
		}
	}
}

cMaster Master;