#pragma once

class cBank
{
public:
	bool Load();
	void Command(int aIndex, char* msg);

public:
	bool					_Active;
	int					    _Level;
	int					    _Zen;
	int                     _Max;
	int                     _Count;
	char                    _Syntax[25];
	char                    _Jewel[10];
	char                    _Trans[10];

public:
	enum
	{
		Bless, Soul, Life, Chaos, Creation, Guardian
	};
};

extern cBank Bank;