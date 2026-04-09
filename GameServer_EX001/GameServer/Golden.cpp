#include "StdAfx.h"
#include "DSProtocol.h"

bool cGolden::Load()
{
	this->_Count = 0;

	memset(this->GoldenStruct, 0, sizeof(this->GoldenStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Box's\\05 - Golden Box.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->GoldenStruct[this->_Count]._Type = Section.Rows[i].GetInt(0);
			this->GoldenStruct[this->_Count]._Index = Section.Rows[i].GetInt(1);
			this->GoldenStruct[this->_Count]._Level = Section.Rows[i].GetInt(2);
			this->GoldenStruct[this->_Count]._Luck = Section.Rows[i].GetInt(3);
			this->GoldenStruct[this->_Count]._Skill = Section.Rows[i].GetInt(4);
			this->GoldenStruct[this->_Count]._Option = Section.Rows[i].GetInt(5);
			this->GoldenStruct[this->_Count]._Excelente = Section.Rows[i].GetInt(6);
			this->GoldenStruct[this->_Count]._Ancient = Section.Rows[i].GetInt(7);
			this->_Count++;
		}
	}

	return true;
}

bool cGolden::Item(int aIndex)
{
	if (this->_Count == 0)
	{
		return false;
	}

	srand(time(NULL));

	int Sortear = rand() % this->_Count;

	int Item = ITEMGET(this->GoldenStruct[Sortear]._Type, this->GoldenStruct[Sortear]._Index);

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

	ItemSerialCreateSend(aIndex, 236, gObj[aIndex].X, gObj[aIndex].Y, Item, this->GoldenStruct[Sortear]._Level, 0, this->GoldenStruct[Sortear]._Skill, this->GoldenStruct[Sortear]._Luck, this->GoldenStruct[Sortear]._Option, aIndex, this->GoldenStruct[Sortear]._Excelente, this->GoldenStruct[Sortear]._Ancient);

	return true;
}

cGolden Golden;