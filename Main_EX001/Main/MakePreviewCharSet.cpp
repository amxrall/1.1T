#include "StdAfx.h"

void MakePreviewCharSets(int aIndex, BYTE *CharSet, int Struct, int Mode) // OK
{
	_MakePreviewCharSets(aIndex, CharSet, Struct, Mode);

	_WingsCharSet(aIndex, CharSet, Struct, Mode);
}


void _WingsCharSet(int aIndex, BYTE *CharSet, int Struct, int Mode)
{
	BYTE CustomWings = CharSet[16] >> 2;

	if (CustomWings > 0)
	{
		*(WORD*)(*(int*)0x07424644 + (1060 * aIndex) + 0x2E8) = ITEMGET(12, MIN_WING_INDEX) + (CustomWings - 1); // Wing
	}

}

void ReadMakePreviewCharSet() // OK
{
	SetCompleteHook(0xFF, 0x00491F31, &MakePreviewCharSets);
	SetCompleteHook(0xFF, 0x004BC6D7, &MakePreviewCharSets);
	SetCompleteHook(0xFF, 0x004C1F87, &MakePreviewCharSets);
	SetCompleteHook(0xFF, 0x004C2D98, &MakePreviewCharSets);
	SetCompleteHook(0xFF, 0x004DA13F, &MakePreviewCharSets);
	SetCompleteHook(0xFF, 0x004DBE44, &MakePreviewCharSets);
}

