#include "StdAfx.h"
#include "DSProtocol.h"

bool cChaosEvent::Load()
{
	for (int i = 0; i < 6; i++)
	{
		this->_Resets[i] = 0, this->_Count[i] = 0;
	}

	memset(this->ChaosStruct, 0, sizeof(this->ChaosStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Eventos\\ChaosEvent.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Resets[0] = Section.Rows[0].GetInt(0);
		this->_Resets[1] = Section.Rows[0].GetInt(1);
		this->_Resets[2] = Section.Rows[0].GetInt(2);
		this->_Resets[3] = Section.Rows[0].GetInt(3);
		this->_Resets[4] = Section.Rows[0].GetInt(4);
		this->_Resets[5] = Section.Rows[0].GetInt(5);
	}

	if (Group.GetSection(1, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->ChaosStruct[this->_Count[0]]._Type[0] = Section.Rows[i].GetInt(0);
			this->ChaosStruct[this->_Count[0]]._Index[0] = Section.Rows[i].GetInt(1);
			this->ChaosStruct[this->_Count[0]]._Level[0] = Section.Rows[i].GetInt(2);
			this->ChaosStruct[this->_Count[0]]._Luck[0] = Section.Rows[i].GetInt(3);
			this->ChaosStruct[this->_Count[0]]._Skill[0] = Section.Rows[i].GetInt(4);
			this->ChaosStruct[this->_Count[0]]._Option[0] = Section.Rows[i].GetInt(5);
			this->ChaosStruct[this->_Count[0]]._Excelente[0] = Section.Rows[i].GetInt(6);
			this->ChaosStruct[this->_Count[0]]._Ancient[0] = Section.Rows[i].GetInt(7);
			this->_Count[0]++;
		}
	}

	if (Group.GetSection(2, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->ChaosStruct[this->_Count[1]]._Type[1] = Section.Rows[i].GetInt(0);
			this->ChaosStruct[this->_Count[1]]._Index[1] = Section.Rows[i].GetInt(1);
			this->ChaosStruct[this->_Count[1]]._Level[1] = Section.Rows[i].GetInt(2);
			this->ChaosStruct[this->_Count[1]]._Luck[1] = Section.Rows[i].GetInt(3);
			this->ChaosStruct[this->_Count[1]]._Skill[1] = Section.Rows[i].GetInt(4);
			this->ChaosStruct[this->_Count[1]]._Option[1] = Section.Rows[i].GetInt(5);
			this->ChaosStruct[this->_Count[1]]._Excelente[1] = Section.Rows[i].GetInt(6);
			this->ChaosStruct[this->_Count[1]]._Ancient[1] = Section.Rows[i].GetInt(7);
			this->_Count[1]++;
		}
	}

	if (Group.GetSection(3, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->ChaosStruct[this->_Count[2]]._Type[2] = Section.Rows[i].GetInt(0);
			this->ChaosStruct[this->_Count[2]]._Index[2] = Section.Rows[i].GetInt(1);
			this->ChaosStruct[this->_Count[2]]._Level[2] = Section.Rows[i].GetInt(2);
			this->ChaosStruct[this->_Count[2]]._Luck[2] = Section.Rows[i].GetInt(3);
			this->ChaosStruct[this->_Count[2]]._Skill[2] = Section.Rows[i].GetInt(4);
			this->ChaosStruct[this->_Count[2]]._Option[2] = Section.Rows[i].GetInt(5);
			this->ChaosStruct[this->_Count[2]]._Excelente[2] = Section.Rows[i].GetInt(6);
			this->ChaosStruct[this->_Count[2]]._Ancient[2] = Section.Rows[i].GetInt(7);
			this->_Count[2]++;
		}
	}

	if (Group.GetSection(4, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->ChaosStruct[this->_Count[3]]._Type[3] = Section.Rows[i].GetInt(0);
			this->ChaosStruct[this->_Count[3]]._Index[3] = Section.Rows[i].GetInt(1);
			this->ChaosStruct[this->_Count[3]]._Level[3] = Section.Rows[i].GetInt(2);
			this->ChaosStruct[this->_Count[3]]._Luck[3] = Section.Rows[i].GetInt(3);
			this->ChaosStruct[this->_Count[3]]._Skill[3] = Section.Rows[i].GetInt(4);
			this->ChaosStruct[this->_Count[3]]._Option[3] = Section.Rows[i].GetInt(5);
			this->ChaosStruct[this->_Count[3]]._Excelente[3] = Section.Rows[i].GetInt(6);
			this->ChaosStruct[this->_Count[3]]._Ancient[3] = Section.Rows[i].GetInt(7);
			this->_Count[3]++;
		}
	}

	if (Group.GetSection(5, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->ChaosStruct[this->_Count[4]]._Type[4] = Section.Rows[i].GetInt(0);
			this->ChaosStruct[this->_Count[4]]._Index[4] = Section.Rows[i].GetInt(1);
			this->ChaosStruct[this->_Count[4]]._Level[4] = Section.Rows[i].GetInt(2);
			this->ChaosStruct[this->_Count[4]]._Luck[4] = Section.Rows[i].GetInt(3);
			this->ChaosStruct[this->_Count[4]]._Skill[4] = Section.Rows[i].GetInt(4);
			this->ChaosStruct[this->_Count[4]]._Option[4] = Section.Rows[i].GetInt(5);
			this->ChaosStruct[this->_Count[4]]._Excelente[4] = Section.Rows[i].GetInt(6);
			this->ChaosStruct[this->_Count[4]]._Ancient[4] = Section.Rows[i].GetInt(7);
			this->_Count[4]++;
		}
	}

	if (Group.GetSection(6, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->ChaosStruct[this->_Count[5]]._Type[5] = Section.Rows[i].GetInt(0);
			this->ChaosStruct[this->_Count[5]]._Index[5] = Section.Rows[i].GetInt(1);
			this->ChaosStruct[this->_Count[5]]._Level[5] = Section.Rows[i].GetInt(2);
			this->ChaosStruct[this->_Count[5]]._Luck[5] = Section.Rows[i].GetInt(3);
			this->ChaosStruct[this->_Count[5]]._Skill[5] = Section.Rows[i].GetInt(4);
			this->ChaosStruct[this->_Count[5]]._Option[5] = Section.Rows[i].GetInt(5);
			this->ChaosStruct[this->_Count[5]]._Excelente[5] = Section.Rows[i].GetInt(6);
			this->ChaosStruct[this->_Count[5]]._Ancient[5] = Section.Rows[i].GetInt(7);
			this->_Count[5]++;
		}
	}

	return true;
}

void cChaosEvent::Item(int aIndex, char Vector)
{
	for (int i = 0; i < this->_Count[Vector]; i++)
	{
		int Item = ITEMGET(this->ChaosStruct[i]._Type[Vector], this->ChaosStruct[i]._Index[Vector]);
		ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, Item, this->ChaosStruct[i]._Level[Vector], 0, this->ChaosStruct[i]._Skill[Vector], this->ChaosStruct[i]._Luck[Vector], this->ChaosStruct[i]._Option[Vector], aIndex, this->ChaosStruct[i]._Excelente[Vector], this->ChaosStruct[i]._Ancient[Vector]);
	}
}

cChaosEvent ChaosEvent;