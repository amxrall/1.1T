#include "StdAfx.h"

cSpeed::cSpeed() : _Active(false)
{
}

bool cSpeed::Load()
{
	this->_Count = 0;

	memset(this->SkillStruct, 0, sizeof(this->SkillStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Customs\\Speed.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_Attack = Section.Rows[0].GetInt(1);
		this->_Moviment = Section.Rows[0].GetInt(2);

		this->_Display[0] = Section.Rows[1].GetInt(0);
		this->_Display[1] = Section.Rows[1].GetInt(1);
		this->_Display[2] = Section.Rows[1].GetInt(2);
	}

	if (Group.GetSection(1, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->SkillStruct[this->_Count]._Magic = Section.Rows[i].GetInt(0);
			this->SkillStruct[this->_Count]._Velocity = Section.Rows[i].GetInt(1);
			this->_Count++;
		}
	}

	return true;
}

void cSpeed::Connect(int aIndex)
{
	if (this->_Active)
	{
		this->SpeedStruct[aIndex]._Sended = false;

		this->SpeedStruct[aIndex]._Attack = 0;

		this->SpeedStruct[aIndex]._Skill = 0;

		this->SpeedStruct[aIndex]._Moviment = 0;
	}
}

void cSpeed::Run(LPOBJ lpObj)
{
	if (this->_Active)
	{
		if (this->SpeedStruct[lpObj->m_Index]._Attack > this->_Attack && this->SpeedStruct[lpObj->m_Index]._Sended == false)
		{
			this->SpeedStruct[lpObj->m_Index]._Sended = true;

			Function.MsgOutput(lpObj->m_Index, 0, "Detectado alteração de velocidade: %s!", lpObj->Name);
			Function.MsgOutput(lpObj->m_Index, 0, "Desconectado por uso de speed hacker.");

			gObjCloseSet(lpObj->m_Index, 0);
		}

		if (this->SpeedStruct[lpObj->m_Index]._Moviment > this->_Moviment && this->SpeedStruct[lpObj->m_Index]._Sended == false)
		{
			this->SpeedStruct[lpObj->m_Index]._Sended = true;

			Function.MsgOutput(lpObj->m_Index, 0, "Detectado alteração de velocidade: %s!", lpObj->Name);
			Function.MsgOutput(lpObj->m_Index, 0, "Desconectado por uso de speed hacker.");

			gObjCloseSet(lpObj->m_Index, 0);
		}

		this->SpeedStruct[lpObj->m_Index]._Attack = 0;
		this->SpeedStruct[lpObj->m_Index]._Skill = 0;
		this->SpeedStruct[lpObj->m_Index]._Moviment = 0;
	}
}

bool cSpeed::Attack(LPOBJ lpObj, LPOBJ Target, class CMagicInf* lpMagic)
{
	if (this->_Active)
	{
		if (lpObj->Type == OBJ_USER && Target->Type == OBJ_USER)
		{
			if (lpObj->m_Index != Target->m_Index && lpMagic == NULL)
			{
				if (this->SpeedStruct[lpObj->m_Index]._Attack > 0 && this->_Display[0] == 1)
				{
					Function.MsgOutput(lpObj->m_Index, 0, "Attack: %d", this->SpeedStruct[lpObj->m_Index]._Attack);
				}

				this->SpeedStruct[lpObj->m_Index]._Attack++;
			}
		}
	}

	return true;
}

void cSpeed::Skill(LPOBJ lpObj, int Magic)
{
	if (this->_Active)
	{
		lpObj->Magic->Set(Magic, 0);

		if (lpObj->Magic != NULL)
		{
			for (int i = 0; i < this->_Count; i++)
			{
				if (Magic == this->SkillStruct[i]._Magic)
				{
					this->SpeedStruct[lpObj->m_Index]._Skill++;

					if (this->SpeedStruct[lpObj->m_Index]._Skill > 0 && this->_Display[1] == 1)
					{
						Function.MsgOutput(lpObj->m_Index, 0, "Skill: %d", this->SpeedStruct[lpObj->m_Index]._Skill);
					}

					if (this->SpeedStruct[lpObj->m_Index]._Skill > this->SkillStruct[i]._Velocity && this->SpeedStruct[lpObj->m_Index]._Sended == false)
					{
						this->SpeedStruct[lpObj->m_Index]._Sended = true;

						Function.MsgOutput(lpObj->m_Index, 0, "Detectado alteração de velocidade: %s!", lpObj->Name);
						Function.MsgOutput(lpObj->m_Index, 0, "Desconectado por uso de speed hacker.");

						gObjCloseSet(lpObj->m_Index, 0);
					}
				}
			}
		}
	}
}

cSpeed Speed;