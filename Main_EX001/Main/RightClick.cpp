#include "StdAfx.h"

void ItemPosicion(DWORD a1, DWORD a2, int a3, int Columna, int Fila)
{
	if (CheckWindows(0x20))
	{
		a1 = 0x113;
		a2 = 0x10F;
		a3 = 0x7889FD8;
		Fila = 4;
		Columna = 8;
	}

	if (CheckWindows(0x100))
	{
		a1 = 0x113;
		a2 = 0x6E;
		a3 = 0x7D0E088;
		Fila = 4;
		Columna = 8;
	}

	((void(*)(DWORD a1, DWORD a2, int a3, int Fila, int a5))0x005B8890)(a1, a2, a3, Columna, Fila);
}

bool __stdcall CheckClick(int a1)
{
	if (CheckWindows(0x20))
	{
		return true;
	}

	if (CheckWindows(0x100))
	{
		return true;
	}

	return CheckWindows(a1);
}
