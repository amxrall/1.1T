#pragma once

class cAuthority
{
public:
	bool Load();
	bool Check(LPOBJ lpObj, unsigned Value);

private:
	struct sAuthority
	{
		char Name[11];
		int  Type[11];
	};

private:
	int  Count;

private:
	sAuthority		AuthorityStruct[255];
};

extern cAuthority Authority;