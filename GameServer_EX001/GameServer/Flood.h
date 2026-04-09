#pragma once

struct sFlood
{
	char IP[16];
	DWORD LastConnect;
};

class cFlood
{
public:
	cFlood();

public:
	int Get(char* IP);

public:
	int			    _List;

public:
	sFlood			FloodStruct[2000];
};

extern cFlood Flood;