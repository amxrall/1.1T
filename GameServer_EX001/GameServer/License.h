#pragma once

class cLicense
{
public:
	bool Load();
	bool Check(LPCSTR ID);

private:
	BYTE  _Data[6];
	DWORD _Serial;
	char  _Buffer[60];
};

extern cLicense License;