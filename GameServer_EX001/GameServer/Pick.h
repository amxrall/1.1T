#pragma once

class cPick
{
public:
	bool Load();
	void Run(LPOBJ lpObj);

public:
	bool                _Active;
	int                 _VipCount;
};

extern cPick Pick;