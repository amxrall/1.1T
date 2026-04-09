#include "StdAfx.h"
#include "BloodCastle.h"
#include "ChaosCastle.h"
#include "ObjUseSkill.h"
#include "GameMain.h"

cAttack::cAttack() : _Active(false)
{
}

bool cAttack::Load()
{
	this->_Count[0] = 0; this->_Count[1] = 0;

	memset(this->AttackStruct, 0, sizeof(this->AttackStruct));

	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Customs\\Attack.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
		this->_Level = Section.Rows[0].GetInt(1);
		this->_Zen = Section.Rows[0].GetInt(2);
		this->_Time[0] = Section.Rows[0].GetInt(3);
		this->_Time[1] = Section.Rows[0].GetInt(4);

		strcpy_s(this->_Syntax, sizeof(this->_Syntax), (Section.Rows[0].GetStringPtr(5)));
	}

	if (Group.GetSection(1, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->AttackStruct[this->_Count[0]]._MapNumber = Section.Rows[i].GetInt(0);
			this->_Count[0]++;
		}
	}

	if (Group.GetSection(2, Section))
	{
		for (int i = 0; i < Section.RowCount; i++)
		{
			this->AttackStruct[this->_Count[1]]._Magic = Section.Rows[i].GetInt(0);
			this->_Count[1]++;
		}
	}

	return true;
}

void cAttack::Connect(int aIndex)
{
	this->PlayerStruct[aIndex]._Attack = false;

	this->PlayerStruct[aIndex]._OffAttack = false;

	this->PlayerStruct[aIndex]._Skill = -1;

	this->PlayerStruct[aIndex]._Time[0] = 0;

	this->PlayerStruct[aIndex]._Time[1] = 0;
}

int cAttack::Inventory(LPOBJ lpObj, int aIndex)
{
	for (int i = 12; i < 76; i++)
	{
		if (lpObj->pInventory[i].m_Type == aIndex)
		{
			return i;
		}
	}

	return FALSE;
}

bool cAttack::MapCheck(LPOBJ lpObj)
{
	if (this->_Count[0] > 0)
	{
		if (BC_MAP_RANGE(lpObj->MapNumber) || CC_MAP_RANGE(lpObj->MapNumber))
		{
			return false;
		}

		for (int i = 0; i < this->_Count[0]; i++)
		{
			if (lpObj->MapNumber == this->AttackStruct[i]._MapNumber)
			{
				return false;
			}
		}
	}

	return true;
}

bool cAttack::SkillCheck(LPOBJ lpObj, int Magic)
{
	if (this->_Count[1] > 0)
	{
		lpObj->Magic->Set(Magic, 0);

		if (lpObj->Magic != NULL)
		{
			for (int i = 0; i < this->_Count[1]; i++)
			{
				if (Magic == this->AttackStruct[i]._Magic)
				{
					return true;
				}
			}
		}
	}

	return false;
}

bool cAttack::Start(int aIndex, int Attack)
{
	if (Attack == 0)
	{
		this->PlayerStruct[aIndex]._Attack = true;

		this->PlayerStruct[aIndex]._Time[0] = GetTickCount();
	}
	else if (Attack == 1)
	{
		this->PlayerStruct[aIndex]._OffAttack = true;

		this->PlayerStruct[aIndex]._Time[1] = GetTickCount();
	}

	this->PlayerStruct[aIndex]._Skill = gObj[aIndex].UseMagicNumber;

	Function.MsgOutput(aIndex, 1, "O sistema foi iniciado.");

	if (Attack == 1)
	{
		CloseClient(aIndex);
	}

	return true;
}

void cAttack::Run(LPOBJ lpObj)
{
	if (lpObj->Connected == 3 && lpObj->Type == OBJ_USER && this->PlayerStruct[lpObj->m_Index]._Skill > 0)
	{
		if (this->PlayerStruct[lpObj->m_Index]._Attack == true)
		{
			if ((GetTickCount() - this->PlayerStruct[lpObj->m_Index]._Time[0]) > (this->_Time[0] * (1000 * 60)))
			{
				this->Finish(lpObj->m_Index, "Sistema finalizado.");
			}
		}
		else if (this->PlayerStruct[lpObj->m_Index]._OffAttack == true)
		{
			if ((GetTickCount() - this->PlayerStruct[lpObj->m_Index]._Time[1]) > (this->_Time[1] * (1000 * 60)))
			{
				this->PlayerStruct[lpObj->m_Index]._OffAttack = false;

				CloseClient(lpObj->m_Index);

				gObjDel(lpObj->m_Index);
			}
		}

		if (lpObj->HaveWeaponInHand == false)
		{
			this->Finish(lpObj->m_Index, "Utilize uma arma válida.");
			return;
		}
		else if (this->MapCheck(lpObj) == false)
		{
			this->Finish(lpObj->m_Index, "Sistema proibido nesse mapa.");
			return;
		}
		else if ((MapC[lpObj->MapNumber].GetAttr(lpObj->X, lpObj->Y) & 1) == 1)
		{
			this->Finish(lpObj->m_Index, "Sistema proibido em área segura.");
			return;
		}

		if (this->PlayerStruct[lpObj->m_Index]._Attack == true || this->PlayerStruct[lpObj->m_Index]._OffAttack == true)
		{
			if (((lpObj->Life * 100) / (lpObj->MaxLife + lpObj->AddLife)) < 50)
			{
				PMSG_USEITEM Result;
				Result.inventoryPos = this->Inventory(lpObj, ITEMGET(14, 3));
				Result.invenrotyTarget = 0;

				if (Result.inventoryPos != 0x0)
				{
					CGUseItemRecv(&Result, lpObj->m_Index);
				}
			}
			else if (((lpObj->Mana * 100) / (lpObj->MaxMana + lpObj->AddMana)) < 50)
			{
				PMSG_USEITEM Result;
				Result.inventoryPos = this->Inventory(lpObj, ITEMGET(14, 6));
				Result.invenrotyTarget = 0;

				if (Result.inventoryPos != 0x0)
				{
					CGUseItemRecv(&Result, lpObj->m_Index);
				}
			}

			this->PlayerStruct[lpObj->m_Index]._Skill = lpObj->UseMagicNumber;

			lpObj->Magic->Set(this->PlayerStruct[lpObj->m_Index]._Skill, 0);

			if (lpObj->Magic != NULL)
			{
				this->Check(lpObj, lpObj->Magic, lpObj->Class == KNIGHT ? 3 : 6);
			}
		}
	}
}

void cAttack::Finish(int aIndex, char* msg)
{
	this->PlayerStruct[aIndex]._Attack = false;

	this->PlayerStruct[aIndex]._OffAttack = false;

	this->PlayerStruct[aIndex]._Skill = -1;

	this->PlayerStruct[aIndex]._Time[0] = 0;

	this->PlayerStruct[aIndex]._Time[1] = 0;

	Function.MsgOutput(aIndex, 1, msg);
}

void cAttack::Command(int aIndex, char* msg)
{
	if (this->_Active)
	{
		if (gObj[aIndex].Level < this->_Level)
		{
			Function.MsgOutput(aIndex, 1, "É necessário %d de level.", this->_Level);
			return;
		}
		else if (gObj[aIndex].Money < this->_Zen)
		{
			Function.MsgOutput(aIndex, 1, "É necessário %d de zen.", this->_Zen);
			return;
		}
		else if (gObj[aIndex].UseMagicNumber == 0)
		{
			Function.MsgOutput(aIndex, 1, "Utilize uma skill válida.");
			return;
		}
		else if (this->MapCheck(&gObj[aIndex]) == false)
		{
			Function.MsgOutput(aIndex, 1, "Sistema proibido nesse mapa.");
			return;
		}
		else if (this->SkillCheck(&gObj[aIndex], gObj[aIndex].UseMagicNumber) == false)
		{
			Function.MsgOutput(aIndex, 1, "Skill não permitida no sistema.");
			return;
		}

		memset(this->_Name, 0, sizeof(this->_Name));

		sscanf(msg, "%s", &this->_Name);

		if (strlen(msg) < 2 || this->_Name[0] == 0 || strcmpi(this->_Name, "on") && strcmpi(this->_Name, "off") && strcmpi(this->_Name, "offline"))
		{
			Function.MsgOutput(aIndex, 1, "Erro de sintaxe!");
			Function.MsgOutput(aIndex, 1, "Digite: %s offline ou on/off.", this->_Syntax);
			return;
		}

		if (!strcmpi(this->_Name, "off"))
		{
			this->Finish(aIndex, "Sistema finalizado.");
			return;
		}
		else if (!strcmpi(this->_Name, "on"))
		{
			if (this->PlayerStruct[aIndex]._Attack == true)
			{
				Function.MsgOutput(aIndex, 1, "O sistema já está ativo.");
				return;
			}

			if (!this->Start(aIndex, 0))
			{
				GCMoneySend(aIndex, gObj[aIndex].Money -= this->_Zen);
			}
		}
		else if (!strcmpi(this->_Name, "offline"))
		{
			if (this->PlayerStruct[aIndex]._Attack == true)
			{
				this->Finish(aIndex, "");
			}

			if (!this->Start(aIndex, 1))
			{
				GCMoneySend(aIndex, gObj[aIndex].Money -= this->_Zen);
			}
		}
	}
}

void cAttack::Check(LPOBJ lpObj, CMagicInf * lpMagic, short Max)
{
	for (int i = 0; i < 75; i++)
	{
		if (lpObj->VpPlayer2[i].state)
		{
			LPOBJ lpTarget = &gObj[lpObj->VpPlayer2[i].number];

			if (lpTarget >= 0)
			{
				if (lpTarget->Live && lpTarget->Type == OBJ_MONSTER)
				{
					if (gObjCalDistance(lpObj, lpTarget) < Max)
					{
						gObjUseSkill.UseSkill(lpObj->m_Index, lpMagic, lpTarget->X, lpTarget->Y, lpTarget->Dir, 0, lpTarget->m_Index);

						if (gObjAttack(lpObj, lpTarget, lpMagic, 1, 1, 0, FALSE) == TRUE)
						{
							GCMagicAttackNumberSend(lpObj, lpMagic->m_Skill, lpTarget->m_Index, 1);
						}
					}
				}
			}
		}
	}
}

cAttack Attack;