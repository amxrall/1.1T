#pragma once

class cCharacter
{
public:
	bool Load();

public:
	WORD WizardAttack[4];
	WORD KnightAttack[4];
	WORD ElfAttack[16];
	WORD GladiatorAttack[8];
	WORD LordAttack[8];
	WORD AttackSpeed[5];
	WORD MagicSpeed[5];
	WORD SuccessfulBlocking[5];
	WORD Defense[5];
	WORD MagicDamageMin[5];
	WORD MagicDamageMax[5];
};

extern cCharacter Character;