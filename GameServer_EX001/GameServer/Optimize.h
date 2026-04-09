#pragma once

class cOptimize
{
public:
	bool Load();
	bool Memory();

private:
	DWORD  _Id;
	HANDLE _Thread;
};

extern cOptimize Optimize;