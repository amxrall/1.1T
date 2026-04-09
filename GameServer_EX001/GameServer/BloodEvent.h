#pragma once

struct sBlood
{
	BYTE                     _Type[7];
	BYTE                     _Index[7];
	BYTE                     _Level[7];
	BYTE                     _Skill[7];
	BYTE                     _Luck[7];
	BYTE                     _Option[7];
	BYTE                     _Excelente[7];
};

class cBloodEvent
{
public:
	bool Load();
	void Item(int aIndex, char Vector);

public:
	int                      _Resets[7];
	int                      _Count[7];

private:
	sBlood			         BloodStruct[255];
};

extern cBloodEvent BloodEvent;