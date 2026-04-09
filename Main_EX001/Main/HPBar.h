#pragma once

#define MAX_MAIN_VIEWPORT 400
#define UnknownFunc1 ((bool(__cdecl*)()) 0x0060CC20)

struct VAngle
{
	float X;
	float Y;
	float Z;
};

struct HEALTH_BAR
{
	short Index;
	BYTE Rate;
};

class cHPBar
{
public:
	void Clear();
	void Insert(short Index, BYTE Rate);
	HEALTH_BAR* Get(short Index);
	static void Draw();

private:
	char Buffer[80];
};

extern cHPBar HPBar;