#include "StdAfx.h"
#include "DSProtocol.h"

bool cQuest::Load()
{
	this->_Count[0] = 0; this->_Count[1] = 0;

	memset(this->QuestStruct, 0, sizeof(this->QuestStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Customs\\Quest.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
	}

	if (Group.GetSection(1, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->QuestStruct[this->_Count[0]]._Monster = Section.Rows[i].GetInt(0);
			this->QuestStruct[this->_Count[0]]._Quantity[0] = Section.Rows[i].GetInt(1);
			this->QuestStruct[this->_Count[0]]._Reward = Section.Rows[i].GetInt(2);
			
			strcpy_s(this->QuestStruct[this->_Count[0]]._Message, sizeof(this->QuestStruct[this->_Count[0]]._Message), (Section.Rows[i].GetStringPtr(3)));
			strcpy_s(this->QuestStruct[this->_Count[0]]._Name[0], sizeof(this->QuestStruct[this->_Count[0]]._Name[0]), (Section.Rows[i].GetStringPtr(4)));

			this->QuestStruct[this->_Count[0]]._Amount = Section.Rows[i].GetInt(5);

			strcpy_s(this->QuestStruct[this->_Count[0]]._Column, sizeof(this->QuestStruct[this->_Count[0]]._Column), (Section.Rows[i].GetStringPtr(6)));
			strcpy_s(this->QuestStruct[this->_Count[0]]._Coin, sizeof(this->QuestStruct[this->_Count[0]]._Coin), (Section.Rows[i].GetStringPtr(7)));
			this->_Count[0]++;
		}
	}

	if (Group.GetSection(2, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->QuestStruct[this->_Count[1]]._Type = Section.Rows[i].GetInt(0);
			this->QuestStruct[this->_Count[1]]._Index = Section.Rows[i].GetInt(1);
			this->QuestStruct[this->_Count[1]]._Level = Section.Rows[i].GetInt(2);
			this->QuestStruct[this->_Count[1]]._Luck = Section.Rows[i].GetInt(3);
			this->QuestStruct[this->_Count[1]]._Skill = Section.Rows[i].GetInt(4);
			this->QuestStruct[this->_Count[1]]._Option = Section.Rows[i].GetInt(5);
			this->QuestStruct[this->_Count[1]]._Excelente = Section.Rows[i].GetInt(6);
			this->QuestStruct[this->_Count[1]]._Ancient = Section.Rows[i].GetInt(7);
			this->QuestStruct[this->_Count[1]]._Quantity[1] = Section.Rows[i].GetInt(8);
			strcpy_s(this->QuestStruct[this->_Count[1]]._Name[1], sizeof(this->QuestStruct[this->_Count[1]]._Name[1]), (Section.Rows[i].GetStringPtr(9)));
			this->_Count[1]++;
		}
	}

	return true;
}

void cQuest::Connect(int aIndex)
{
	Manager.QuestCount(aIndex, gObj[aIndex].Name);
}

void cQuest::Talk(OBJECTSTRUCT* Npc, OBJECTSTRUCT* lpObj)
{
	if (this->PlayerStruct[lpObj->m_Index]._Index < this->_Count[0])
	{
		if (this->PlayerStruct[lpObj->m_Index]._Start == 0)
		{
			if (this->PlayerStruct[lpObj->m_Index]._Index == 0)
			{
				this->PlayerStruct[lpObj->m_Index]._Start = 1;

				ChatTargetSend(Npc, "Boa sorte em sua missão jovem guerreiro(a)!", lpObj->m_Index);

				Manager.ExecFormat("UPDATE Character SET Start = 1 WHERE Name = '%s'", lpObj->Name);

				Function.Golden(lpObj->m_Index, "Quest número: %d", this->PlayerStruct[lpObj->m_Index]._Index + 1);

				Function.Golden(lpObj->m_Index, "%s", this->QuestStruct[this->PlayerStruct[lpObj->m_Index]._Index]._Message);

				Function.Golden(lpObj->m_Index, "%s [%d/%d]", this->QuestStruct[this->PlayerStruct[lpObj->m_Index]._Index]._Name[0], this->PlayerStruct[lpObj->m_Index]._Kills, this->QuestStruct[this->PlayerStruct[lpObj->m_Index]._Index]._Quantity[0]);
			}
			else
			{
				this->PlayerStruct[lpObj->m_Index]._Start = 1;

				ChatTargetSend(Npc, "Boa sorte em sua nova missão!", lpObj->m_Index);

				Manager.ExecFormat("UPDATE Character SET Start = 1 WHERE Name = '%s'", lpObj->Name);

				Function.Golden(lpObj->m_Index, "Quest número: %d", this->PlayerStruct[lpObj->m_Index]._Index + 1);

				Function.Golden(lpObj->m_Index, "%s", this->QuestStruct[this->PlayerStruct[lpObj->m_Index]._Index]._Message);

				Function.Golden(lpObj->m_Index, "%s [%d/%d]", this->QuestStruct[this->PlayerStruct[lpObj->m_Index]._Index]._Name[0], this->PlayerStruct[lpObj->m_Index]._Kills, this->QuestStruct[this->PlayerStruct[lpObj->m_Index]._Index]._Quantity[0]);
			}
		}
		else if (this->PlayerStruct[lpObj->m_Index]._Start == 1)
		{
			if (this->PlayerStruct[lpObj->m_Index]._Kills >= this->QuestStruct[this->PlayerStruct[lpObj->m_Index]._Index]._Quantity[0])
			{
				if (this->PlayerStruct[lpObj->m_Index]._Index == this->_Count[0])
				{
					ChatTargetSend(Npc, "Você já finalizou essa missão.", lpObj->m_Index);
					return;
				}

				this->Reward(lpObj->m_Index);

				this->PlayerStruct[lpObj->m_Index]._Start = 0;

				this->PlayerStruct[lpObj->m_Index]._Index++;

				this->PlayerStruct[lpObj->m_Index]._Kills = 0;

				Manager.ExecFormat("UPDATE Character SET Kills = 0 WHERE Name = '%s'", lpObj->Name);

				Manager.ExecFormat("UPDATE Character SET Start = 0 WHERE Name = '%s'", lpObj->Name);

				Manager.ExecFormat("UPDATE Character SET Number = Number + 1 WHERE Name = '%s'", lpObj->Name);

				ChatTargetSend(Npc, "Você completou a missão, parabéns!", lpObj->m_Index);
			}
			else
			{
				ChatTargetSend(Npc, "Você não completou a missão.", lpObj->m_Index);

				Function.Golden(lpObj->m_Index, "%s", this->QuestStruct[this->PlayerStruct[lpObj->m_Index]._Index]._Message);

				Function.Golden(lpObj->m_Index, "%s [%d/%d]", this->QuestStruct[this->PlayerStruct[lpObj->m_Index]._Index]._Name[0], this->PlayerStruct[lpObj->m_Index]._Kills, this->QuestStruct[this->PlayerStruct[lpObj->m_Index]._Index]._Quantity[0]);
			}
		}
	}
	else
	{
		ChatTargetSend(Npc, "Você completou todas as missões, parabéns!", lpObj->m_Index);
	}
}

void cQuest::Kill(int aIndex)
{
	if (this->PlayerStruct[aIndex]._Kills < this->QuestStruct[this->PlayerStruct[aIndex]._Index]._Quantity[0])
	{
		this->PlayerStruct[aIndex]._Kills++;

		Function.Golden(aIndex, "%s [%d/%d]", this->QuestStruct[this->PlayerStruct[aIndex]._Index]._Name[0], this->PlayerStruct[aIndex]._Kills, this->QuestStruct[this->PlayerStruct[aIndex]._Index]._Quantity[0]);

		if (this->PlayerStruct[aIndex]._Kills == this->QuestStruct[this->PlayerStruct[aIndex]._Index]._Quantity[0])
		{
			Function.Golden(aIndex, "Você completou a missão!");
			Function.Golden(aIndex, "Resgate as recompensas.");
		}
	}
}

void cQuest::Reward(int aIndex)
{
	if (this->QuestStruct[this->PlayerStruct[aIndex]._Index]._Reward == 1)
	{
		Function.Golden(aIndex, "Parabéns, prêmio: %d %s", this->QuestStruct[this->PlayerStruct[aIndex]._Index]._Amount, this->QuestStruct[this->PlayerStruct[aIndex]._Index]._Coin);

		Manager.ExecFormat("UPDATE MEMB_INFO SET %s = %s + %d WHERE memb___id = '%s'", this->QuestStruct[this->PlayerStruct[aIndex]._Index]._Column, this->QuestStruct[this->PlayerStruct[aIndex]._Index]._Column, this->QuestStruct[this->PlayerStruct[aIndex]._Index]._Amount, gObj[aIndex].AccountID);
	}
	else if (this->QuestStruct[this->PlayerStruct[aIndex]._Index]._Reward == 2)
	{
		int Sortear = rand() % this->_Count[1];

		int Item = ITEMGET(this->QuestStruct[Sortear]._Type, this->QuestStruct[Sortear]._Index);

		int Check = Function.InventoryFullCheck(aIndex, Item);

		if (this->QuestStruct[Sortear]._Quantity[1] > Check)
		{
			for (int i = 0; i < this->QuestStruct[Sortear]._Quantity[1]; i++)
			{
				ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, Item, this->QuestStruct[Sortear]._Level, 0, this->QuestStruct[Sortear]._Skill, this->QuestStruct[Sortear]._Luck, this->QuestStruct[Sortear]._Option, aIndex, this->QuestStruct[Sortear]._Excelente, this->QuestStruct[Sortear]._Ancient);
			}
		}
		else
		{
			for (int i = 0; i < this->QuestStruct[Sortear]._Quantity[1]; i++)
			{
				ItemSerialCreateSend(aIndex, 236, gObj[aIndex].X, gObj[aIndex].Y, Item, this->QuestStruct[Sortear]._Level, 0, this->QuestStruct[Sortear]._Skill, this->QuestStruct[Sortear]._Luck, this->QuestStruct[Sortear]._Option, aIndex, this->QuestStruct[Sortear]._Excelente, this->QuestStruct[Sortear]._Ancient);
			}
		}

		Function.Golden(aIndex, "Parabéns, prêmio: %s", this->QuestStruct[Sortear]._Name[1]);
	}
}

void cQuest::Quit(LPOBJ lpObj)
{
	if (lpObj->Type == OBJ_USER)
	{
		if (this->PlayerStruct[lpObj->m_Index]._Kills > 0)
		{
			Manager.ExecFormat("UPDATE Character SET Kills = %d WHERE Name = '%s'", this->PlayerStruct[lpObj->m_Index]._Kills, lpObj->Name);

			this->PlayerStruct[lpObj->m_Index]._Kills = 0;
		}
	}
}

cQuest Quest;