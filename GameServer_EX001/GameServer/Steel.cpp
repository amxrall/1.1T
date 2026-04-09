#include "StdAfx.h"
#include "DSProtocol.h"

bool cSteel::Load()
{
	this->_Count = 0;

	memset(this->SteelStruct, 0, sizeof(this->SteelStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Box's\\02 - Steel Box.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->SteelStruct[this->_Count]._Type = Section.Rows[i].GetInt(0);
			this->SteelStruct[this->_Count]._Index = Section.Rows[i].GetInt(1);
			this->SteelStruct[this->_Count]._Level = Section.Rows[i].GetInt(2);
			this->SteelStruct[this->_Count]._Luck = Section.Rows[i].GetInt(3);
			this->SteelStruct[this->_Count]._Skill = Section.Rows[i].GetInt(4);
			this->SteelStruct[this->_Count]._Option = Section.Rows[i].GetInt(5);
			this->SteelStruct[this->_Count]._Excelente = Section.Rows[i].GetInt(6);
			this->SteelStruct[this->_Count]._Ancient = Section.Rows[i].GetInt(7);
			this->_Count++;
		}
	}

	return true;
}

bool cSteel::Item(int aIndex)
{
	if (this->_Count == 0)
	{
		return false;
	}

	srand(time(NULL));

	int Sortear = rand() % this->_Count;

	int Item = ITEMGET(this->SteelStruct[Sortear]._Type, this->SteelStruct[Sortear]._Index);
	
	if (!Function.InventoryFullCheck(aIndex, Item))
	{
		Function.MsgOutput(aIndex, 1, "O inventário está cheio!");
		return 236;
	}

	int Check = Function.InventoryFullCheck(aIndex, Item);

	if (this->_Count > Check)
	{
		this->_Count = Check;
	}
	ItemSerialCreateSend(aIndex, 236, gObj[aIndex].X, gObj[aIndex].Y, Item, this->SteelStruct[Sortear]._Level, 0, this->SteelStruct[Sortear]._Skill, this->SteelStruct[Sortear]._Luck, this->SteelStruct[Sortear]._Option, aIndex, this->SteelStruct[Sortear]._Excelente, this->SteelStruct[Sortear]._Ancient);
	//ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, Item, this->SteelStruct[Sortear]._Level, 0, this->SteelStruct[Sortear]._Skill, this->SteelStruct[Sortear]._Luck, this->SteelStruct[Sortear]._Option, aIndex, this->SteelStruct[Sortear]._Excelente, this->SteelStruct[Sortear]._Ancient);
	return true;
}

cSteel Steel;