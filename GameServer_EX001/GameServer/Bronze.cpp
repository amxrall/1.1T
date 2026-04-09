#include "StdAfx.h"
#include "DSProtocol.h"

bool cBronze::Load()
{
	this->_Count = 0;

	memset(this->BronzeStruct, 0, sizeof(this->BronzeStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Box's\\01 - Bronze Box.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->BronzeStruct[this->_Count]._Type = Section.Rows[i].GetInt(0);
			this->BronzeStruct[this->_Count]._Index = Section.Rows[i].GetInt(1);
			this->BronzeStruct[this->_Count]._Level = Section.Rows[i].GetInt(2);
			this->BronzeStruct[this->_Count]._Luck = Section.Rows[i].GetInt(3);
			this->BronzeStruct[this->_Count]._Skill = Section.Rows[i].GetInt(4);
			this->BronzeStruct[this->_Count]._Option = Section.Rows[i].GetInt(5);
			this->BronzeStruct[this->_Count]._Excelente = Section.Rows[i].GetInt(6);
			this->BronzeStruct[this->_Count]._Ancient = Section.Rows[i].GetInt(7);
			this->_Count++;
		}
	}

	return true;
}

bool cBronze::Item(int aIndex)
{
	if (this->_Count == 0)
	{
		return false;
	}

	srand(time(NULL));

	int Sortear = rand() % this->_Count;

	int Item = ITEMGET(this->BronzeStruct[Sortear]._Type, this->BronzeStruct[Sortear]._Index);

	if (!Function.InventoryFullCheck(aIndex, Item))
	{
		Function.MsgOutput(aIndex, 1, "O inventário está cheio!");
		return ItemSerialCreateSend;
	}

	int Check = Function.InventoryFullCheck(aIndex, Item);

	if (this->_Count > Check)
	{
		this->_Count = Check;
	}

	ItemSerialCreateSend(aIndex, 236, gObj[aIndex].X, gObj[aIndex].Y, Item, this->BronzeStruct[Sortear]._Level, 0, this->BronzeStruct[Sortear]._Skill, this->BronzeStruct[Sortear]._Luck, this->BronzeStruct[Sortear]._Option, aIndex, this->BronzeStruct[Sortear]._Excelente, this->BronzeStruct[Sortear]._Ancient);

	return true;
}

cBronze Bronze;