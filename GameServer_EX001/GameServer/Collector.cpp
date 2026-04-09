#include "StdAfx.h"

cCollector::cCollector() : _Active(false)
{
}

bool cCollector::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Customs\\Collector.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_Section = Section.Rows[0].GetInt(1);
	}

	if (Group.GetSection(1, Section))
	{
		this->_Type[0] = Section.Rows[0].GetInt(0);
		this->_Index[0] = Section.Rows[0].GetInt(1);
		this->_Level[0] = Section.Rows[0].GetInt(2);
		this->_Quantity[0] = Section.Rows[0].GetInt(3);
		this->_Value[0] = Section.Rows[0].GetInt(4);
		strcpy_s(this->_Name[0], sizeof(this->_Name[0]), (Section.Rows[0].GetStringPtr(5)));
		strcpy_s(this->_Coin[0], sizeof(this->_Coin[0]), (Section.Rows[0].GetStringPtr(6)));
	}

	if (Group.GetSection(2, Section))
	{
		this->_Type[1] = Section.Rows[0].GetInt(0);
		this->_Index[1] = Section.Rows[0].GetInt(1);
		this->_Level[1] = Section.Rows[0].GetInt(2);
		this->_Quantity[1] = Section.Rows[0].GetInt(3);
		this->_Value[1] = Section.Rows[0].GetInt(4);
		strcpy_s(this->_Name[1], sizeof(this->_Name[1]), (Section.Rows[0].GetStringPtr(5)));
		strcpy_s(this->_Coin[1], sizeof(this->_Coin[1]), (Section.Rows[0].GetStringPtr(6)));
	}

	if (Group.GetSection(3, Section))
	{
		this->_Type[2] = Section.Rows[0].GetInt(0);
		this->_Index[2] = Section.Rows[0].GetInt(1);
		this->_Level[2] = Section.Rows[0].GetInt(2);
		this->_Quantity[2] = Section.Rows[0].GetInt(3);
		this->_Value[2] = Section.Rows[0].GetInt(4);
		strcpy_s(this->_Name[2], sizeof(this->_Name[2]), (Section.Rows[0].GetStringPtr(5)));
		strcpy_s(this->_Coin[2], sizeof(this->_Coin[2]), (Section.Rows[0].GetStringPtr(6)));
	}

	if (Group.GetSection(4, Section))
	{
		this->_Type[3] = Section.Rows[0].GetInt(0);
		this->_Index[3] = Section.Rows[0].GetInt(1);
		this->_Level[3] = Section.Rows[0].GetInt(2);
		this->_Quantity[3] = Section.Rows[0].GetInt(3);
		this->_Value[3] = Section.Rows[0].GetInt(4);
		strcpy_s(this->_Name[3], sizeof(this->_Name[3]), (Section.Rows[0].GetStringPtr(5)));
		strcpy_s(this->_Coin[3], sizeof(this->_Coin[3]), (Section.Rows[0].GetStringPtr(6)));
	}

	if (Group.GetSection(5, Section))
	{
		this->_Type[4] = Section.Rows[0].GetInt(0);
		this->_Index[4] = Section.Rows[0].GetInt(1);
		this->_Level[4] = Section.Rows[0].GetInt(2);
		this->_Quantity[4] = Section.Rows[0].GetInt(3);
		this->_Value[4] = Section.Rows[0].GetInt(4);
		strcpy_s(this->_Name[4], sizeof(this->_Name[4]), (Section.Rows[0].GetStringPtr(5)));
		strcpy_s(this->m_Gold, sizeof(this->m_Gold), (Section.Rows[0].GetStringPtr(6)));
	}

	return true;
}

cCollector Collector;