#include "StdAfx.h"

bool cBalancer::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Customs\\Balancer.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		this->_Active = Section.Rows[0].GetInt(0) > 0 ? true : false;
	}

	if (Group.GetSection(1, Section))
	{
		this->WizardAttack[0] = Section.Rows[0].GetInt(0);
		this->WizardAttack[1] = Section.Rows[0].GetInt(1);
		this->WizardAttack[2] = Section.Rows[0].GetInt(2);
		this->WizardAttack[3] = Section.Rows[0].GetInt(3);
		this->WizardAttack[4] = Section.Rows[0].GetInt(4);
	}

	if (Group.GetSection(2, Section))
	{
		this->KnightAttack[0] = Section.Rows[0].GetInt(0);
		this->KnightAttack[1] = Section.Rows[0].GetInt(1);
		this->KnightAttack[2] = Section.Rows[0].GetInt(2);
		this->KnightAttack[3] = Section.Rows[0].GetInt(3);
		this->KnightAttack[4] = Section.Rows[0].GetInt(4);
	}

	if (Group.GetSection(3, Section))
	{
		this->ElfAttack[0] = Section.Rows[0].GetInt(0);
		this->ElfAttack[1] = Section.Rows[0].GetInt(1);
		this->ElfAttack[2] = Section.Rows[0].GetInt(2);
		this->ElfAttack[3] = Section.Rows[0].GetInt(3);
		this->ElfAttack[4] = Section.Rows[0].GetInt(4);
	}

	if (Group.GetSection(4, Section))
	{
		this->GladiatorAttack[0] = Section.Rows[0].GetInt(0);
		this->GladiatorAttack[1] = Section.Rows[0].GetInt(1);
		this->GladiatorAttack[2] = Section.Rows[0].GetInt(2);
		this->GladiatorAttack[3] = Section.Rows[0].GetInt(3);
		this->GladiatorAttack[4] = Section.Rows[0].GetInt(4);
	}

	if (Group.GetSection(5, Section))
	{
		this->LordAttack[0] = Section.Rows[0].GetInt(0);
		this->LordAttack[1] = Section.Rows[0].GetInt(1);
		this->LordAttack[2] = Section.Rows[0].GetInt(2);
		this->LordAttack[3] = Section.Rows[0].GetInt(3);
		this->LordAttack[4] = Section.Rows[0].GetInt(4);
	}

	if (Group.GetSection(6, Section))
	{
		this->Combo[0] = Section.Rows[0].GetInt(0);
		this->Combo[1] = Section.Rows[0].GetInt(1);
		this->Combo[2] = Section.Rows[0].GetInt(2);
		this->Combo[3] = Section.Rows[0].GetInt(3);
		this->Combo[4] = Section.Rows[0].GetInt(4);
	}

	return true;
}

void cBalancer::Attack(LPOBJ lpObj, LPOBJ lpTarget, CMagicInf* lpMagic, int &AttackDamage)
{
	if (lpObj->Type != OBJ_USER || lpTarget->Type != OBJ_USER || AttackDamage <= 0)
	{
		return;
	}
	else if (lpObj->Class == WIZARD)
	{
		switch (lpTarget->Class)
		{
		case WIZARD:
			AttackDamage = (AttackDamage * this->WizardAttack[0]) / 100; break;
		case KNIGHT:
			AttackDamage = (AttackDamage * this->WizardAttack[1]) / 100; break;
		case ELF:
			AttackDamage = (AttackDamage * this->WizardAttack[2]) / 100; break;
		case GLADIATOR:
			AttackDamage = (AttackDamage * this->WizardAttack[3]) / 100; break;
		case LORD:
			AttackDamage = (AttackDamage * this->WizardAttack[4]) / 100; break;
		default:
			break;
		}
	}
	else if (lpObj->Class == KNIGHT)
	{
		switch (lpTarget->Class)
		{
		case KNIGHT:
			AttackDamage = (AttackDamage * this->KnightAttack[0]) / 100; break;
		case WIZARD:
			AttackDamage = (AttackDamage * this->KnightAttack[1]) / 100; break;
		case ELF:
			AttackDamage = (AttackDamage * this->KnightAttack[2]) / 100; break;
		case GLADIATOR:
			AttackDamage = (AttackDamage * this->KnightAttack[3]) / 100; break;
		case LORD:
			AttackDamage = (AttackDamage * this->KnightAttack[4]) / 100; break;
		default:
			break;
		}
	}
	else if (lpObj->Class == ELF)
	{
		switch (lpTarget->Class)
		{
		case ELF:
			AttackDamage = (AttackDamage * this->ElfAttack[0]) / 100; break;
		case KNIGHT:
			AttackDamage = (AttackDamage * this->ElfAttack[1]) / 100; break;
		case WIZARD:
			AttackDamage = (AttackDamage * this->ElfAttack[2]) / 100; break;
		case GLADIATOR:
			AttackDamage = (AttackDamage * this->ElfAttack[3]) / 100; break;
		case LORD:
			AttackDamage = (AttackDamage * this->ElfAttack[4]) / 100; break;
		default:
			break;
		}
	}
	else if (lpObj->Class == GLADIATOR)
	{
		switch (lpTarget->Class)
		{
		case GLADIATOR:
			AttackDamage = (AttackDamage * this->GladiatorAttack[0]) / 100; break;
		case KNIGHT:
			AttackDamage = (AttackDamage * this->GladiatorAttack[1]) / 100; break;
		case WIZARD:
			AttackDamage = (AttackDamage * this->GladiatorAttack[2]) / 100; break;
		case ELF:
			AttackDamage = (AttackDamage * this->GladiatorAttack[3]) / 100; break;
		case LORD:
			AttackDamage = (AttackDamage * this->GladiatorAttack[4]) / 100; break;
		default:
			break;
		}
	}
	else if (lpObj->Class == LORD)
	{
		switch (lpTarget->Class)
		{
		case LORD:
			AttackDamage = (AttackDamage * this->LordAttack[0]) / 100; break;
		case KNIGHT:
			AttackDamage = (AttackDamage * this->LordAttack[1]) / 100; break;
		case WIZARD:
			AttackDamage = (AttackDamage * this->LordAttack[2]) / 100; break;
		case ELF:
			AttackDamage = (AttackDamage * this->LordAttack[3]) / 100; break;
		case GLADIATOR:
			AttackDamage = (AttackDamage * this->LordAttack[4]) / 100; break;
		default:
			break;
		}
	}
}

cBalancer Balancer;