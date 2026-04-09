#pragma once

struct sSteel
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

class cSteel
{
public:
	bool Load();
	bool Item(int aIndex);

public:
	int  				_Count;

private:
	sSteel 				SteelStruct[255];
};

extern cSteel Steel;