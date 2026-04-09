#pragma once

class cProtocol
{
public:
	static BOOL ProtocolCoreEx(int unk1, LPBYTE lpRecv, int unk2, int unk3);;
	static void UpdateCharacterNoEffect();
	static void UpdateCharacterEffect();
	static void LevelUpPoints();
	static bool Skills(int Id);
	void Agility();

public:
	bool Update;
	WORD Level;
	WORD LevelUpPoint;
	WORD Class;
	DWORD Experience;
	DWORD NextExperience;
	WORD Strength;
	WORD Dexterity;
	WORD Vitality;
	WORD Energy;
	WORD Leadership;
	WORD Life;
	WORD MaxLife;
	WORD Mana;
	WORD MaxMana;
	WORD BP;
	WORD MaxBP;
	int RealLevelUpPoint;
	bool InEvent;
};

extern cProtocol Protocol;