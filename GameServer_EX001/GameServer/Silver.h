#pragma once

struct sSilver
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

class cSilver
{
public:
	bool Load();
	bool Item(int aIndex);

public:
	int  				_Count;

private:
	sSteel 				SilverStruct[255];
};

extern cSilver Silver;