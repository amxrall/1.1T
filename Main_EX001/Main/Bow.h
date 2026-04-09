#pragma once

struct sBows
{
	BYTE Type;
	BYTE Subtype;
};

class cBows
{
public:
	void Load();
	sBows* Get(WORD Index);
	static void NewBows1();
	static void NewBows2();
	static void NewBows3();
	static void NewBows4();
	static void NewBows5();
	static void NewBows6();
	static void NewBows7();
	static void NewBows8();
	static void NewBows9();
	static void NewBows10();
	static void NewBows11();
	static void NewBows12();
	static void NewBows13();
	static void NewBows14();
	static void NewBows15();
	static void NewBows16();
	static void NewCrossbows1();
	static void NewCrossbows2();
	static void NewCrossbows3();
	static void NewCrossbows4();
	static void NewCrossbows5();
	static void NewCrossbows6();
	static void NewCrossbows7();
	static void NewCrossbows8();
	static void NewCrossbows9();
	static void MultipleShotSkillEffect();
	static void SingleShotSkillEffect();

public:
	std::unordered_map<WORD, sBows> Item;
};

extern cBows Bow;