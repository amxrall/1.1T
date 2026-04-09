#pragma once

class Buffs
{
public:
	bool Load();

public:
	short _ManaShield[3];
	short _GreaterFortitude[3];
	short _GreaterDamage[2];
	short _GreaterDefense[2];
	short _GreaterCritical[3];
};

extern Buffs Buff;