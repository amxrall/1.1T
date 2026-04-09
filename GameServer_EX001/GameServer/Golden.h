#pragma once

struct sGolden
{
	BYTE				_Type;
	BYTE				_Index;
	BYTE				_Level;
	BYTE				_Skill;
	BYTE				_Luck;
	BYTE				_Option;
	BYTE				_Excelente;
	BYTE				_Ancient;
};

class cGolden
{
public:
	bool Load();
	bool Item(int aIndex);

public:
	int  				_Count;

private:
	sGolden 			GoldenStruct[255];
};

extern cGolden Golden;