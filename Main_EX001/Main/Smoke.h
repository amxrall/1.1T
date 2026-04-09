#pragma once

#define MAX_SMOKE_ITEMS 500

struct CUSTOM_SMOKEEFFECT
{
	WORD			    _Index;
	float			    _ColorR;
	float			    _ColorG;
	float			    _ColorB;
};

class cSmoke
{
public:
	bool Load();
	int Get(DWORD Type);
	static void Effect();

private:
	WORD			    _Index;
	int                 _Item;
	int			        _Count;
	float               _ColorR;
	float               _ColorG;
	float               _ColorB;

private:
	CUSTOM_SMOKEEFFECT			    SmokeStruct[255];
};

extern cSmoke Smoke;