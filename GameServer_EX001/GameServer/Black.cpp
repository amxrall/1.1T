#include "StdAfx.h"
#include "DSProtocol.h"

bool cBlack::Load()
{
	this->_Count = 0;

	memset(this->BlackStruct, 0, sizeof(this->BlackStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Box's\\03 - Black Box.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->BlackStruct[this->_Count]._Type = Section.Rows[i].GetInt(0);
			this->BlackStruct[this->_Count]._Index = Section.Rows[i].GetInt(1);
			this->BlackStruct[this->_Count]._Level = Section.Rows[i].GetInt(2);
			this->BlackStruct[this->_Count]._Luck = Section.Rows[i].GetInt(3);
			this->BlackStruct[this->_Count]._Skill = Section.Rows[i].GetInt(4);
			this->BlackStruct[this->_Count]._Option = Section.Rows[i].GetInt(5);
			this->BlackStruct[this->_Count]._Excelente = Section.Rows[i].GetInt(6);
			this->BlackStruct[this->_Count]._Ancient = Section.Rows[i].GetInt(7);
			this->_Count++;
		}
	}

	return true;
}

bool cBlack::Item(int aIndex)
{
	if (this->_Count == 0)
	{
		return false;
	}

	srand(time(NULL));

	int Sortear = rand() % this->_Count;

	int Item = ITEMGET(this->BlackStruct[Sortear]._Type, this->BlackStruct[Sortear]._Index);
	
	if (!Function.InventoryFullCheck(aIndex, Item))
	{
		Function.MsgOutput(aIndex, 1, "O inventário está cheio!");
		return true;
	}

	int Check = Function.InventoryFullCheck(aIndex, Item);

	if (this->_Count > Check)
	{
		this->_Count = Check;
	}

	ItemSerialCreateSend(aIndex, 236, gObj[aIndex].X, gObj[aIndex].Y, Item, this->BlackStruct[Sortear]._Level, 0, this->BlackStruct[Sortear]._Skill, this->BlackStruct[Sortear]._Luck, this->BlackStruct[Sortear]._Option, aIndex, this->BlackStruct[Sortear]._Excelente, this->BlackStruct[Sortear]._Ancient);
}

cBlack Black;