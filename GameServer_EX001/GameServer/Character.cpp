#include "StdAfx.h"

bool cCharacter::Load()
{
	Tokenizer          Token;
	TokenizerGroup     Group;
	TokenizerSection   Section;

	Token.ParseFile(std::string(".\\Data\\Character\\Character.txt"), Group);

	if (Group.GetSection(0, Section))
	{
		Character.WizardAttack[0] = Section.Rows[0].GetInt(0);
		Character.WizardAttack[1] = Section.Rows[0].GetInt(1);
		Character.WizardAttack[2] = Section.Rows[0].GetInt(2);
		Character.WizardAttack[3] = Section.Rows[0].GetInt(3);

		Character.AttackSpeed[0] = Section.Rows[1].GetInt(0);
		Character.MagicSpeed[0] = Section.Rows[1].GetInt(1);
		Character.Defense[0] = Section.Rows[1].GetInt(2);
		Character.SuccessfulBlocking[0] = Section.Rows[1].GetInt(3);
		Character.MagicDamageMin[0] = Section.Rows[1].GetInt(4);
		Character.MagicDamageMax[0] = Section.Rows[1].GetInt(5);
	}

	if (Group.GetSection(1, Section))
	{
		Character.KnightAttack[0] = Section.Rows[0].GetInt(0);
		Character.KnightAttack[1] = Section.Rows[0].GetInt(1);
		Character.KnightAttack[2] = Section.Rows[0].GetInt(2);
		Character.KnightAttack[3] = Section.Rows[0].GetInt(3);

		Character.AttackSpeed[1] = Section.Rows[1].GetInt(0);
		Character.MagicSpeed[1] = Section.Rows[1].GetInt(1);
		Character.Defense[1] = Section.Rows[1].GetInt(2);
		Character.SuccessfulBlocking[1] = Section.Rows[1].GetInt(3);
		Character.MagicDamageMin[1] = Section.Rows[1].GetInt(4);
		Character.MagicDamageMax[1] = Section.Rows[1].GetInt(5);
	}

	if (Group.GetSection(2, Section))
	{
		Character.ElfAttack[0] = Section.Rows[0].GetInt(0);
		Character.ElfAttack[1] = Section.Rows[0].GetInt(1);
		Character.ElfAttack[2] = Section.Rows[0].GetInt(2);
		Character.ElfAttack[3] = Section.Rows[0].GetInt(3);

		Character.ElfAttack[4] = Section.Rows[1].GetInt(0);
		Character.ElfAttack[5] = Section.Rows[1].GetInt(1);
		Character.ElfAttack[6] = Section.Rows[1].GetInt(2);
		Character.ElfAttack[7] = Section.Rows[1].GetInt(3);
		Character.ElfAttack[8] = Section.Rows[1].GetInt(4);
		Character.ElfAttack[9] = Section.Rows[1].GetInt(5);
		Character.ElfAttack[10] = Section.Rows[1].GetInt(6);
		Character.ElfAttack[11] = Section.Rows[1].GetInt(7);

		Character.ElfAttack[12] = Section.Rows[2].GetInt(0);
		Character.ElfAttack[13] = Section.Rows[2].GetInt(1);
		Character.ElfAttack[14] = Section.Rows[2].GetInt(2);
		Character.ElfAttack[15] = Section.Rows[2].GetInt(3);

		Character.AttackSpeed[2] = Section.Rows[3].GetInt(0);
		Character.MagicSpeed[2] = Section.Rows[3].GetInt(1);
		Character.Defense[2] = Section.Rows[3].GetInt(2);
		Character.SuccessfulBlocking[2] = Section.Rows[3].GetInt(3);
		Character.MagicDamageMin[2] = Section.Rows[3].GetInt(4);
		Character.MagicDamageMax[2] = Section.Rows[3].GetInt(5);
	}

	if (Group.GetSection(3, Section))
	{
		Character.GladiatorAttack[0] = Section.Rows[0].GetInt(0);
		Character.GladiatorAttack[1] = Section.Rows[0].GetInt(1);
		Character.GladiatorAttack[2] = Section.Rows[0].GetInt(2);
		Character.GladiatorAttack[3] = Section.Rows[0].GetInt(3);
		Character.GladiatorAttack[4] = Section.Rows[0].GetInt(4);
		Character.GladiatorAttack[5] = Section.Rows[0].GetInt(5);
		Character.GladiatorAttack[6] = Section.Rows[0].GetInt(6);
		Character.GladiatorAttack[7] = Section.Rows[0].GetInt(7);

		Character.AttackSpeed[3] = Section.Rows[1].GetInt(0);
		Character.MagicSpeed[3] = Section.Rows[1].GetInt(1);
		Character.Defense[3] = Section.Rows[1].GetInt(2);
		Character.SuccessfulBlocking[3] = Section.Rows[1].GetInt(3);
		Character.MagicDamageMin[3] = Section.Rows[1].GetInt(4);
		Character.MagicDamageMax[3] = Section.Rows[1].GetInt(5);
	}

	if (Group.GetSection(4, Section))
	{
		Character.LordAttack[0] = Section.Rows[0].GetInt(0);
		Character.LordAttack[1] = Section.Rows[0].GetInt(1);
		Character.LordAttack[2] = Section.Rows[0].GetInt(2);
		Character.LordAttack[3] = Section.Rows[0].GetInt(3);
		Character.LordAttack[4] = Section.Rows[0].GetInt(4);
		Character.LordAttack[5] = Section.Rows[0].GetInt(5);
		Character.LordAttack[6] = Section.Rows[0].GetInt(6);
		Character.LordAttack[7] = Section.Rows[0].GetInt(7);

		Character.AttackSpeed[4] = Section.Rows[1].GetInt(0);
		Character.MagicSpeed[4] = Section.Rows[1].GetInt(1);
		Character.Defense[4] = Section.Rows[1].GetInt(2);
		Character.SuccessfulBlocking[4] = Section.Rows[1].GetInt(3);
		Character.MagicDamageMin[4] = Section.Rows[1].GetInt(4);
		Character.MagicDamageMax[4] = Section.Rows[1].GetInt(5);
	}

	return true;
}

cCharacter Character;