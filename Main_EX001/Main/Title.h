#pragma once

class cTitle
{
public:
	static void Load();

private:
	int   _Item;
	int   _TextColor;

private:
	enum TextColor
	{
		White         =  0x00,
		Blue          =  0x01,
		Red           =  0x02,
		Gold          =  0x03,
		Green         =  0x04,
		WhiteRed      =  0x05,
		Violet        =  0x06,
		WhiteBlue     =  0x07,
		WhiteBeige    =  0x08,
		GreenBlue     =  0x09,
		Gray          =  0x0A,
		DarkViolet    =  0x0B,
	};
};

extern cTitle Title;