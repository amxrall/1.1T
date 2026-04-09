#pragma once

class cMessage
{
public:
	bool Load();

public:
	char _Buffer[6][255];
};

extern cMessage Message;