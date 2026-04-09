#pragma once

class cDisplay
{
public:
	cDisplay();
	~cDisplay();

public:
	void ViewPaint(HWND hWnd);

private:
	HFONT  Font;
	HFONT  Font1;
	HBRUSH Background;
	HBRUSH Background1;
	HBRUSH Background2;
	HBRUSH Background3;
	HBRUSH Background4;
	HBRUSH Background5;
private:
	char Buffer[255];
};

extern cDisplay Display;