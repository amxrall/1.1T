#pragma once

struct sReset
{
	int                     _VipCount;
	int					    _ResetsMin;
	int					    _ResetsMax;
	int					    _Points;
	int                     _Level;
	int                     _Money;
	int                     _Experience;
	int                     _NpcIndex;
	int					    _MapNPC;
	int					    _CordX;
	int                     _CordY;
};

class cReset
{
public:
	bool Load();
	void Run(int aIndex);
	void GetNpcReset(int aIndex, LPOBJ lpNpc);

public:
	bool					_Active;
	BYTE					_Type;
	int                     _Teleport[4];
	int                     _Remove[4];
	int                     _Comando[4];
	int                     _Count;
	char					_Syntax[25];
	int                     _Level[4];
	int                     _Experience[4];

	sReset                  ResetStruct[255];
};

extern cReset Reset;