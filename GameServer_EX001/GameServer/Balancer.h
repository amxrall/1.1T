#pragma once

class cBalancer
{
public:
	bool Load();
	void Attack(LPOBJ lpObj, LPOBJ lpTarget, CMagicInf* lpMagic, int &AttackDamage);

public:
	bool _Active;
	WORD WizardAttack[5];
	WORD KnightAttack[5];
	WORD ElfAttack[5];
	WORD GladiatorAttack[5];
	WORD LordAttack[5];
	WORD Combo[5];
};

extern cBalancer Balancer;