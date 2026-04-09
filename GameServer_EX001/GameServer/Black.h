#pragma once

struct sBlack
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

class cBlack
{
public:
	bool Load();
	bool Item(int aIndex);

public:
	int  				_Count;

private:
	sBlack 				BlackStruct[255];
};

extern cBlack Black;