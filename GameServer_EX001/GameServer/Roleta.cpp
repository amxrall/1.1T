#include "StdAfx.h"
#include "DSProtocol.h"

cRoleta::cRoleta() : _Active(false)
{
}

bool cRoleta::Load()
{
	this->_Count = 0;

	memset(this->RoletaStruct, 0, sizeof(this->RoletaStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Customs\\Roleta.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_Amount = Section.Rows[0].GetInt(1);

		strcpy_s(this->_Column, sizeof(this->_Column), (Section.Rows[0].GetStringPtr(2)));
		strcpy_s(this->_Name, sizeof(this->_Name), (Section.Rows[0].GetStringPtr(3)));
		strcpy_s(this->_Syntax, sizeof(this->_Syntax), (Section.Rows[0].GetStringPtr(4)));
	}

	if (Group.GetSection(1, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->RoletaStruct[this->_Count]._Type = Section.Rows[i].GetInt(0);
			this->RoletaStruct[this->_Count]._Index = Section.Rows[i].GetInt(1);
			this->RoletaStruct[this->_Count]._Level = Section.Rows[i].GetInt(2);
			this->RoletaStruct[this->_Count]._Luck = Section.Rows[i].GetInt(3);
			this->RoletaStruct[this->_Count]._Skill = Section.Rows[i].GetInt(4);
			this->RoletaStruct[this->_Count]._Option = Section.Rows[i].GetInt(5);
			this->RoletaStruct[this->_Count]._Excelente = Section.Rows[i].GetInt(6);
			this->RoletaStruct[this->_Count]._Ancient = Section.Rows[i].GetInt(7);
			this->RoletaStruct[this->_Count]._Quantity = Section.Rows[i].GetInt(8);
			strcpy_s(this->RoletaStruct[this->_Count]._Name, sizeof(this->RoletaStruct[this->_Count]._Name), (Section.Rows[i].GetStringPtr(9)));
			this->_Count++;
		}
	}

	return true;
}

void cRoleta::Command(int aIndex)
{
	if (this->_Active && this->_Count > 0)
	{
		if (gObj[aIndex].Custom->Coin[0] < this->_Amount)
		{
			Function.MsgOutput(aIndex, 1, "É necessário %d de %s.", this->_Amount, this->_Name);
			return;
		}

		gObj[aIndex].Custom->Coin[0] -= this->_Amount;

		Manager.ExecFormat("UPDATE MEMB_INFO SET %s = %s - %d WHERE memb___id = '%s'", this->_Column, this->_Column, this->_Amount, gObj[aIndex].AccountID);

		int Sortear = rand() % this->_Count;

		for (int i = 0; i < this->RoletaStruct[Sortear]._Quantity; i++)
		{
			int Item = ITEMGET(this->RoletaStruct[Sortear]._Type, this->RoletaStruct[Sortear]._Index);

			if (!Function.InventoryFullCheck(aIndex, Item))
			{
				ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, Item, this->RoletaStruct[Sortear]._Level, 0, this->RoletaStruct[Sortear]._Skill, this->RoletaStruct[Sortear]._Luck, this->RoletaStruct[Sortear]._Option, aIndex, this->RoletaStruct[Sortear]._Excelente, this->RoletaStruct[Sortear]._Ancient);
			}
			else
			{
				ItemSerialCreateSend(aIndex, 236, gObj[aIndex].X, gObj[aIndex].Y, Item, this->RoletaStruct[Sortear]._Level, 0, this->RoletaStruct[Sortear]._Skill, this->RoletaStruct[Sortear]._Luck, this->RoletaStruct[Sortear]._Option, aIndex, this->RoletaStruct[Sortear]._Excelente, this->RoletaStruct[Sortear]._Ancient);
			}
		}

		for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
		{
			if (gObj[i].Connected == 3)
			{
				Function.MsgOutput(i, 0, "[    ROLETA    ]");

				Function.MsgOutput(i, 0, "O jogador %s acabou de girar!", gObj[aIndex].Name);

				Function.MsgOutput(i, 0, "Prêmio: %s", this->RoletaStruct[Sortear]._Name);
			}
		}
	}
}

cRoleta Roleta;