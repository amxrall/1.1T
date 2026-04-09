#include "StdAfx.h"

__declspec(naked) void cDescription::Load()
{
	static WORD TEXT;
	static WORD ITEM;
	static DWORD RETURN;

	_asm
	{
		MOV TEXT, AX
		MOV AX, WORD PTR SS : [ESI]
		MOV ITEM, AX
	}

	if (ITEM == ITEMGET(12, 15))
	{
		Text("É usado para combinar item chaos", TextColor::White, 0);
	}
	else if (ITEM == ITEMGET(14, 38))
	{
		Text("Jogue-o e você pode receber itens.", TextColor::Blue, 0);
	}
	else if (ITEM == ITEMGET(14, 39))
	{
		Text("Jogue-o e você pode receber itens.", TextColor::Blue, 0);
	}
	else if (ITEM == ITEMGET(14, 40))
	{
		Text("Jogue-o e você pode receber itens.", TextColor::Blue, 0);
	}
	else if (ITEM == ITEMGET(14, 41))
	{
		Text("Jogue-o e você pode receber itens.", TextColor::Blue, 0);
	}
	else if (ITEM == ITEMGET(14, 42))
	{
		Text("Jogue-o e você pode receber itens.", TextColor::Blue, 0);
	}
	else if (ITEM == ITEMGET(15, 19))
	{
		Text("É usado para participar do Death/Theft.", TextColor::Blue, 0);

		Text(" ", NULL, 0);

		Text("Atenção!", TextColor::WhiteRed, 0);
		Text("Para consumir o convite utilize o botão direito.", TextColor::Blue, 0);

	}

	_asm
	{
		MOV AX, TEXT
		MOV RETURN, 0x5A5131
		JMP RETURN
	}
}

void cDescription::Text(char * Text, int Color, int Weight, ...)
{
	char Buffer[1024] = { 0 };

	va_list Arguments;
	va_start(Arguments, Text);
	vsprintf(Buffer, Text, Arguments);
	va_end(Arguments);

	*(&*(DWORD*)0x785B2A8 + *(DWORD*)0x788C850) = Color;
	*(&*(DWORD*)0x7889F60 + *(DWORD*)0x788C850) = Weight;

	ItemText(100 * (*(DWORD*)0x788C850) + 0x0785A110, Buffer);

	*(DWORD*)0x788C850 += 1;
}

cDescription Description;