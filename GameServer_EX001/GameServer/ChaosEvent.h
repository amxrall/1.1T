#pragma once

struct sChaos
{
	BYTE                     _Type[6];
	BYTE                     _Index[6];
	BYTE                     _Level[6];
	BYTE                     _Skill[6];
	BYTE                     _Luck[6];
	BYTE                     _Option[6];
	BYTE                     _Excelente[6];
	BYTE                     _Ancient[6];
};

class cChaosEvent
{
public:
	bool Load();
	void Item(int aIndex, char Vector);

public:
	int                      _Resets[6];
	int                      _Count[6];

private:
	sChaos			         ChaosStruct[255];
};

extern cChaosEvent ChaosEvent;