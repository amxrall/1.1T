#include "StdAfx.h"

__declspec(naked) void cTitle::Load()
{
	_asm
	{
		MOV DX, WORD PTR DS : [EBX]
		MOV Title._Item, EDX
	}

	if (Title._Item == ITEMGET(14, 16))
	{
		Title._TextColor = TextColor::Gold;
	}
	else if (Title._Item == ITEMGET(5, 10))
	{
		Title._TextColor = TextColor::Violet;
	}
	else if (Title._Item == ITEMGET(0, 19))
	{
		Title._TextColor = TextColor::Violet;
	}
	else if (Title._Item == ITEMGET(4, 18))
	{
		Title._TextColor = TextColor::Violet;
	}
	else if (Title._Item == ITEMGET(2, 13))
	{
		Title._TextColor = TextColor::Violet;
	}
	else if (Title._Item == ITEMGET(14, 38))
	{
		Title._TextColor = TextColor::WhiteBeige;
	}
	else if (Title._Item == ITEMGET(14, 39))
	{
		Title._TextColor = TextColor::GreenBlue;
	}
	else if (Title._Item == ITEMGET(14, 40))
	{
		Title._TextColor = TextColor::WhiteRed;
	}
	else if (Title._Item == ITEMGET(14, 41))
	{
		Title._TextColor = TextColor::GreenBlue;
	}
	else if (Title._Item == ITEMGET(14, 42))
	{
		Title._TextColor = TextColor::WhiteBeige;
	}
	else if (Title._Item == ITEMGET(15, 19))
	{
		Title._TextColor = TextColor::WhiteBlue;
	}
	// ------
	// Wings
	// ------
	else if (Title._Item == ITEMGET(12, 100)) // Wing of War
	{
		Title._TextColor = TextColor::Gold;
	}
	else if (Title._Item == ITEMGET(12, 101)) // Wing of Warlock
	{
		Title._TextColor = TextColor::Gold;
	}
	else if (Title._Item == ITEMGET(12, 102)) // Wing of New 2.0
	{
		Title._TextColor = TextColor::Gold;
	}
	else if (Title._Item == ITEMGET(12, 103)) // Wing of Christmas
	{
		Title._TextColor = TextColor::Gold;
	}
	else if (Title._Item == ITEMGET(12, 104)) // Wing of love
	{
		Title._TextColor = TextColor::Gold;
	}
	else if (Title._Item == ITEMGET(12, 105)) // Wing of santa
	{
		Title._TextColor = TextColor::Gold;
	}
	else if (Title._Item == ITEMGET(12, 106)) // Wing of ilussion lvl3 elfa
	{
		Title._TextColor = TextColor::Gold;
	}
	else if (Title._Item == ITEMGET(12, 107)) // Wing of ethernal lvl 3 sm
	{
		Title._TextColor = TextColor::Gold;
	}
	else if (Title._Item == ITEMGET(12, 108)) // Wing of Hurricane lvl 3 mg
	{
		Title._TextColor = TextColor::Gold;
	}
	else if (Title._Item == ITEMGET(12, 109)) // Wing of blade lvl3 bk
	{
		Title._TextColor = TextColor::Gold;
	}
	else if (Title._Item == ITEMGET(12, 110)) // Wing of apocalipse
	{
		Title._TextColor = TextColor::Gold;
	}
	else if (Title._Item == ITEMGET(12, 111)) // Wing of Chronus
	{
		Title._TextColor = TextColor::Gold;
	}
	else if (Title._Item == ITEMGET(12, 112)) // Wing of Eros
	{
		Title._TextColor = TextColor::Gold;
	}
	else if (Title._Item == ITEMGET(12, 113)) // Wing of Poseidon
	{
		Title._TextColor = TextColor::Gold;
	}
	// --------------------
	// Kit Anel
	// --------------------
	else if (Title._Item == ITEMGET(13, 50)) // Ring WAR
	{
	Title._TextColor = TextColor::Green;
	}
	else if (Title._Item == ITEMGET(13, 51)) // Pendant War
	{
	Title._TextColor = TextColor::Green;
	}
	else
	{
		_asm
		{
			MOV EAX, 0x5A22AD
			JMP EAX
		}
	}

	_asm
	{
		MOV EDI, Title._TextColor;
		MOV EAX, DWORD PTR DS : [0x788C850]
		MOV DWORD PTR SS : [EBP - 0x1C], EDI
		MOV ECX, 0x5A2378
		JMP ECX
	}
}

cTitle Title;