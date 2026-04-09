#pragma once

struct sBronze
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

class cBronze
{
public:
	bool Load();
	bool Item(int aIndex);

public:
	int  				_Count;

private:
	sBronze 			BronzeStruct[255];
};

extern cBronze Bronze;