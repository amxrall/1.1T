#include "StdAfx.h"
#include "DSProtocol.h"

bool cSilver::Load()
{
	this->_Count = 0;

	memset(this->SilverStruct, 0, sizeof(this->SilverStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Box's\\04 - Silver Box.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->SilverStruct[this->_Count]._Type = Section.Rows[i].GetInt(0);
			this->SilverStruct[this->_Count]._Index = Section.Rows[i].GetInt(1);
			this->SilverStruct[this->_Count]._Level = Section.Rows[i].GetInt(2);
			this->SilverStruct[this->_Count]._Luck = Section.Rows[i].GetInt(3);
			this->SilverStruct[this->_Count]._Skill = Section.Rows[i].GetInt(4);
			this->SilverStruct[this->_Count]._Option = Section.Rows[i].GetInt(5);
			this->SilverStruct[this->_Count]._Excelente = Section.Rows[i].GetInt(6);
			this->SilverStruct[this->_Count]._Ancient = Section.Rows[i].GetInt(7);
			this->_Count++;
		}
	}

	return true;
}

bool cSilver::Item(int aIndex)
{
	if (this->_Count == 0)
	{
		return false;
	}

	srand(time(NULL));

	int Sortear = rand() % this->_Count;

	int Item = ITEMGET(this->SilverStruct[Sortear]._Type, this->SilverStruct[Sortear]._Index);

	if (!Function.InventoryFullCheck(aIndex, Item))
	{
		Function.MsgOutput(aIndex, 1, "O inventário está cheio!");
		return gObj[aIndex].MapNumber;
	}

	int Check = Function.InventoryFullCheck(aIndex, Item);

	if (this->_Count > Check)
	{
		this->_Count = Check;
	}

	ItemSerialCreateSend(aIndex, 236, gObj[aIndex].X, gObj[aIndex].Y, Item, this->SilverStruct[Sortear]._Level, 0, this->SilverStruct[Sortear]._Skill, this->SilverStruct[Sortear]._Luck, this->SilverStruct[Sortear]._Option, aIndex, this->SilverStruct[Sortear]._Excelente, this->SilverStruct[Sortear]._Ancient);

	return true;
}

cSilver Silver;