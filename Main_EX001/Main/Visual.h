#pragma once

class VisualState
{
public:
	void Load();
	void Index(PMSG_JOINRESULT* Data);
	void RecvDamage(PMSG_ATTACKRESULT * Data);
	void RecvHP(PMSG_REFILL* Data);
	void RecvMP(PMSG_MANASEND* Data);
	void Respawn();
	void Killed(PMSG_DIEPLAYER* Data);
	static void DrawDamageHP(int a1, int a2, int a3, float a4, char a5, char a6);
	static void DrawHP(float a1, float a2, int Value, float a4, float a5);
	static void DrawMP(float a1, float a2, int Value, float a4, float a5);
	static void DrawAG(float a1, float a2, int Value, float a4, float a5);
	static void DrawTabHP(int PosX, int PosY, LPCSTR lpString);
	static void DrawTabMP(int PosX, int PosY, LPCSTR lpString);
	static void DrawTabAG(int PosX, int PosY, LPCSTR lpString);
	static void InfoHP(int a1, int a2, LPCSTR a3, int a4, char a5, int a6);
	static void InfoMP(int a1, int a2, LPCSTR a3, int a4, char a5, int a6);
	static void CheckMP1();
	static void CheckMP2();
	static void CheckMP3();
	static void CheckMP4();
	static void CheckBP1();
	static void CheckBP2();
	static void CheckBP3();
	static void CheckBP4();

public:
	bool Kill;
	short aIndex;
	int Attack;
	int Life;
	int MaxLife;
	int Mana;
	int MaxMana;
	int BP;
	int MaxBP;
	char Buffer[6][50];
};

extern VisualState Visual;