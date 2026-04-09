#include "StdAfx.h"

bool Buffs::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Customs\\Buffs.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_ManaShield[0] = Section.Rows[0].GetInt(0);
		this->_ManaShield[1] = Section.Rows[0].GetInt(1);
		this->_ManaShield[2] = Section.Rows[0].GetInt(2);
	}

	if (Group.GetSection(1, Section))
	{
		this->_GreaterFortitude[0] = Section.Rows[0].GetInt(0);
		this->_GreaterFortitude[1] = Section.Rows[0].GetInt(1);
		this->_GreaterFortitude[2] = Section.Rows[0].GetInt(2);
	}

	if (Group.GetSection(2, Section))
	{
		this->_GreaterDamage[0] = Section.Rows[0].GetInt(0);
		this->_GreaterDamage[1] = Section.Rows[0].GetInt(1);
	}

	if (Group.GetSection(3, Section))
	{
		this->_GreaterDefense[0] = Section.Rows[0].GetInt(0);
		this->_GreaterDefense[1] = Section.Rows[0].GetInt(1);
	}

	if (Group.GetSection(4, Section))
	{
		this->_GreaterCritical[0] = Section.Rows[0].GetInt(0);
		this->_GreaterCritical[1] = Section.Rows[0].GetInt(1);
		this->_GreaterCritical[2] = Section.Rows[0].GetInt(2);
	}

	return true;
}

Buffs Buff;