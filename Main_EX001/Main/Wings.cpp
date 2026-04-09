#include "StdAfx.h"
#include "Offsets.h"

void cWings::Load()
{
	Hook(0xFF, 0x491F31, this->MakePreviewCharSetEx);
	Hook(0xFF, 0x4BC6D7, this->MakePreviewCharSetEx);
	Hook(0xFF, 0x4C1F87, this->MakePreviewCharSetEx);
	Hook(0xFF, 0x4C2D98, this->MakePreviewCharSetEx);
	Hook(0xFF, 0x4DA13F, this->MakePreviewCharSetEx);
	Hook(0xFF, 0x4DBE44, this->MakePreviewCharSetEx);

	Hook(0xFF, 0x540934, this->ItemSetOptionEx);
	Hook(0xFF, 0x5AB0AB, this->ItemSetOptionEx);
	Hook(0xFF, 0x5AB6EA, this->ItemSetOptionEx);
	Hook(0xFF, 0x5ABA7B, this->ItemSetOptionEx);
	Hook(0xFF, 0x5ABE11, this->ItemSetOptionEx);
	Hook(0xFF, 0x5AC110, this->ItemSetOptionEx);

	HookJump(0x5A5310, this->Function1);
	HookJump(0x5A7702, this->Function2);
	HookJump(0x5A7D70, this->Function3);
	HookJump(0x5EBDF6, this->Function4);
	HookJump(0x5AA33B, this->Function5);
	HookJump(0x5F9DDB, this->Function6);
	HookJump(0x5414B2, this->Function7);
	HookJump(0x542D8F, this->Function8);
	HookJump(0x58A065, this->Function9);
	HookJump(0x5A137A, this->Function10);
	HookJump(0x5A1910, this->Function11);
	HookJump(0x5A237B, this->Function12);
	HookJump(0x5A393E, this->Function13);
	HookJump(0x5A5FF1, this->Function14);
	HookJump(0x5AB4A4, this->Function15);
	HookJump(0x5B183D, this->Function16);
	HookJump(0x5B1879, this->Function17);
	HookJump(0x5CD776, this->Function18);
	HookJump(0x5CDE83, this->Function19);
	HookJump(0x5EBB6B, this->Function20);
	HookJump(0x5EBDF6, this->Function21);
	HookJump(0x5F8740, this->Function22);

	SetNop(0x5F87BB, 18);
	HookJump(0x5F87BB, this->Shine);

	*(BYTE*)(0x5F872E) = 0x40;
	*(BYTE*)(0x5F8736) = 0x3F;
	*(BYTE*)(0x5C6D27 + 2) = 0xC8;
}

void cWings::ItemSetOptionEx(LPVOID ItemStruct, unsigned __int8 Option, unsigned __int8 Special, BYTE Value)
{
	ObjectItem* Result = (ObjectItem*)&(*(int*)ItemStruct);

	int Type = ITEMTYPE(Result->ItemID);

	int Index = ITEMINDEX(Result->ItemID);

	int Old = Result->ItemID;

	if (Type == 12 && Index >= 0x64 && Index <= 0xC8 || Type == 12 && Index >= 0x00 && Index <= 0x02)
	{
		Result->ItemID = ITEMGET(12, 3);
	}

	ItemSetOptionAdd((LPVOID)Result, Option, Special, Value);

	if (Result->ItemID != Old)
	{
		Result->ItemID = Old;
	}
}

void cWings::MakePreviewCharSetEx(int aIndex, BYTE* CharSet, int Struct, int Mode)
{
	MakePreviewCharSet(aIndex, CharSet, Struct, Mode);

	BYTE Wings = CharSet[16] >> 2;

	if (Wings > 0)
	{
		*(WORD*)(*(int*)0x07424644 + (1060 * aIndex) + 0x2E8) = ITEM_ID(12, 100) + (Wings - 1);
	}
}

void __declspec(naked) cWings::Function1()
{
	static DWORD Offset1 = 0x5A5361;
	static DWORD Offset2 = 0x5A531E;

	_asm
	{
		CMP CX, ITEMGET(12, 100);
		JL NEXT_CHECK
			CMP CX, ITEMGET(12, 200);
		JG NEXT_CHECK
			JMP[Offset2]

			NEXT_CHECK:
		CMP CX, 0x1803
			JL NEXT_CHECK2
			CMP CX, 0x1806
			JG NEXT_CHECK2
			JMP[Offset2]

			NEXT_CHECK2 :
			JMP[Offset1]
	}
}

void __declspec(naked) cWings::Function2()
{
	static DWORD Offset1 = 0x5A770E;
	static DWORD Offset2 = 0x5A7714;

	_asm
	{
		CMP AX, ITEMGET(12, 100);
		JL NEXT_CHECK
			CMP AX, ITEMGET(12, 200);
		JLE ALLOW_CHECK

			NEXT_CHECK :
		CMP AX, 0x1803
			JL NEXT_CHECK1
			CMP AX, 0x1806
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[Offset1]

			ALLOW_CHECK :
			JMP[Offset2]
	}

}

void __declspec(naked) cWings::Function3()
{
	static DWORD Offset1 = 0x5A7D7E;
	static DWORD Offset2 = 0x5A7D85;

	_asm
	{
		CMP CX, ITEMGET(12, 100);
		JL NEXT_CHECK
			CMP CX, ITEMGET(12, 200);
		JLE ALLOW_CHECK

			NEXT_CHECK :
		CMP CX, 0x1803
			JL NEXT_CHECK1
			CMP CX, 0x1806
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[Offset1]

			ALLOW_CHECK :
			JMP[Offset2]
	}
}

void __declspec(naked) cWings::Function4()
{
	static DWORD Offset1 = 0x5EBE0A;
	static DWORD Offset2 = 0x5EBE02;

	_asm
	{
		CMP AX, ITEMGET(12, 100);
		JL NEXT_CHECK
			CMP AX, ITEMGET(12, 200);
		JG NEXT_CHECK
			JMP[Offset2]

			NEXT_CHECK:
		CMP AX, 0x1803
			JL NEXT_CHECK2
			CMP AX, 0x1806
			JG NEXT_CHECK2
			JMP[Offset2]

			NEXT_CHECK2 :
			JMP[Offset1]
	}
}

void __declspec(naked) cWings::Function5()
{
	static DWORD Offset1 = 0x5AA347;
	static DWORD Offset2 = 0x5AA361;

	_asm
	{
		CMP AX, ITEM_ID(12, 100);
		JL NEXT_CHECK
			CMP AX, ITEM_ID(12, 200);
		JLE ALLOW_CHECK

			NEXT_CHECK :
		CMP AX, 0x1A03
			JL NEXT_CHECK1
			CMP AX, 0x1A09
			JLE ALLOW_CHECK


			NEXT_CHECK1 :
		JMP[Offset1]

			ALLOW_CHECK :
			JMP[Offset2]
	}
}

void __declspec(naked) cWings::Function6()
{
	static DWORD Offset1 = 0x5F9DE7;
	static DWORD Offset2 = 0x5F9E4A;

	_asm
	{
		CMP AX, ITEM_ID(12, 100);
		JL NEXT_CHECK
			CMP AX, ITEM_ID(12, 200);
		JLE ALLOW_CHECK

			NEXT_CHECK :
		CMP AX, 0x1A03
			JL NEXT_CHECK1
			CMP AX, 0x1A09
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[Offset1]

			ALLOW_CHECK :
			JMP[Offset2]
	}
}


void __declspec(naked) cWings::Function7()
{
	static DWORD Offset1 = 0x5414CF;
	static DWORD Offset2 = 0x5414BE;

	_asm
	{
		CMP AX, ITEMGET(12, 100);
		JL NEXT_CHECK
			CMP AX, ITEMGET(12, 200);
		JG NEXT_CHECK
			JMP[Offset2]

			NEXT_CHECK:
		CMP AX, 0x1800
			JL NEXT_CHECK2
			CMP AX, 0x1806
			JG NEXT_CHECK2
			JMP[Offset2]

			NEXT_CHECK2 :
			JMP[Offset1]
	}
}

void __declspec(naked) cWings::Function8()
{
	static DWORD Offset1 = 0x542D9B;
	static DWORD Offset2 = 0x542DFC;

	_asm
	{
		CMP AX, ITEMGET(12, 100);
		JL NEXT_CHECK
			CMP AX, ITEMGET(12, 200);
		JLE ALLOW_CHECK

			NEXT_CHECK :
		CMP AX, 0x1800
			JL NEXT_CHECK1
			CMP AX, 0x1806
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[Offset1]

			ALLOW_CHECK :
			JMP[Offset2]
	}
}

void __declspec(naked) cWings::Function9()
{
	static DWORD Offset1 = 0x58A071;
	static DWORD Offset2 = 0x58A0E1;

	_asm
	{
		CMP AX, ITEMGET(12, 100);
		JL NEXT_CHECK
			CMP AX, ITEMGET(12, 200);
		JLE ALLOW_CHECK

			NEXT_CHECK :
		CMP AX, 0x1800
			JL NEXT_CHECK1
			CMP AX, 0x1806
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[Offset1]

			ALLOW_CHECK :
			JMP[Offset2]
	}
}

void __declspec(naked) cWings::Function10()
{
	static DWORD Offset1 = 0x5A1388;
	static DWORD Offset2 = 0x5A13B3;



	_asm
	{
		CMP DX, ITEMGET(12, 100);
		JL NEXT_CHECK
			CMP DX, ITEMGET(12, 200);
		JLE ALLOW_CHECK

			NEXT_CHECK :
		CMP DX, 0x1803
			JL NEXT_CHECK1
			CMP DX, 0x1806
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[Offset1]

			ALLOW_CHECK :
			JMP[Offset2]
	}
}

void __declspec(naked) cWings::Function11()
{
	static DWORD Offset1 = 0x5A1950;
	static DWORD Offset2 = 0x5A191E;

	_asm
	{
		CMP EAX, ITEMGET(12, 100);
		JL NEXT_CHECK
			CMP EAX, ITEMGET(12, 200);
		JG NEXT_CHECK
			JMP[Offset2]

			NEXT_CHECK:
		CMP EAX, 0x1800
			JL NEXT_CHECK2
			CMP EAX, 0x1806
			JG NEXT_CHECK2
			JMP[Offset2]

			NEXT_CHECK2 :
			JMP[Offset1]
	}
}

void __declspec(naked) cWings::Function12()
{
	static DWORD Offset1 = 0x5A2389;
	static DWORD Offset2 = 0x5A2390;

	_asm
	{
		CMP CX, ITEMGET(12, 100);
		JL NEXT_CHECK
			CMP CX, ITEMGET(12, 200);
		JLE ALLOW_CHECK

			NEXT_CHECK :
		CMP CX, 0x1800
			JL NEXT_CHECK1
			CMP CX, 0x1806
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[Offset1]

			ALLOW_CHECK :
			JMP[Offset2]
	}
}

void __declspec(naked) cWings::Function13()
{
	static DWORD Offset1 = 0x5A3970;
	static DWORD Offset2 = 0x5A394C;



	_asm
	{
		CMP CX, ITEMGET(12, 100);
		JL NEXT_CHECK
			CMP CX, ITEMGET(12, 200);
		JG NEXT_CHECK
			JMP[Offset2]

			NEXT_CHECK:
		CMP CX, 0x1800
			JL NEXT_CHECK2
			CMP CX, 0x1806
			JG NEXT_CHECK2
			JMP[Offset2]

			NEXT_CHECK2 :
			JMP[Offset1]
	}
}

void __declspec(naked) cWings::Function14()
{
	static DWORD Offset1 = 0x5A6006;
	static DWORD Offset2 = 0x5A5FFF;

	_asm
	{
		CMP CX, ITEMGET(12, 100);
		JL NEXT_CHECK
			CMP CX, ITEMGET(12, 200);
		JG NEXT_CHECK
			JMP[Offset2]

			NEXT_CHECK:
		CMP CX, 0x1800
			JL NEXT_CHECK2
			CMP CX, 0x1806
			JG NEXT_CHECK2
			JMP[Offset2]

			NEXT_CHECK2 :
			JMP[Offset1]
	}
}

void __declspec(naked) cWings::Function15()
{
	static DWORD Offset1 = 0x5AB4B0;
	static DWORD Offset2 = 0x5AB4D7;

	_asm
	{
		CMP AX, ITEMGET(12, 100);
		JL NEXT_CHECK
			CMP AX, ITEMGET(12, 200);
		JLE ALLOW_CHECK

			NEXT_CHECK :
		CMP AX, 0x1800
			JL NEXT_CHECK1
			CMP AX, 0x1806
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[Offset1]

			ALLOW_CHECK :
			JMP[Offset2]
	}
}


void __declspec(naked) cWings::Function16()
{
	static DWORD Offset1 = 0x5B1849;
	static DWORD Offset2 = 0x5B184F;

	_asm
	{
		CMP AX, ITEMGET(12, 100);
		JL NEXT_CHECK
			CMP AX, ITEMGET(12, 200);
		JLE ALLOW_CHECK

			NEXT_CHECK :
		CMP AX, 0x1800
			JL NEXT_CHECK1
			CMP AX, 0x1806
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[Offset1]

			ALLOW_CHECK :
			JMP[Offset2]
	}
}

void __declspec(naked) cWings::Function17()
{
	static DWORD Offset1 = 0x5B188B;
	static DWORD Offset2 = 0x5B2688;

	_asm
	{
		CMP CX, ITEMGET(12, 100);
		JL NEXT_CHECK
			CMP CX, ITEMGET(12, 200);
		JLE ALLOW_CHECK

			NEXT_CHECK :
		CMP CX, 0x1800
			JL NEXT_CHECK1
			CMP CX, 0x1806
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[Offset1]

			ALLOW_CHECK :
			JMP[Offset2]
	}
}

void __declspec(naked) cWings::Function18()
{
	static DWORD Offset1 = 0x5CD788;
	static DWORD Offset2 = 0x5CDE0D;

	_asm
	{
		CMP CX, ITEMGET(12, 100);
		JL NEXT_CHECK
			CMP CX, ITEMGET(12, 200);
		JLE ALLOW_CHECK

			NEXT_CHECK :
		CMP CX, 0x1800
			JL NEXT_CHECK1
			CMP CX, 0x1806
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[Offset1]

			ALLOW_CHECK :
			JMP[Offset2]
	}
}

void __declspec(naked) cWings::Function19()
{
	static DWORD Offset1 = 0x5CDE95;
	static DWORD Offset2 = 0x5CF0DE;

	_asm
	{
		CMP CX, ITEMGET(12, 100);
		JL NEXT_CHECK
			CMP CX, ITEMGET(12, 200);
		JLE ALLOW_CHECK

			NEXT_CHECK :
		CMP CX, 0x1800
			JL NEXT_CHECK1
			CMP CX, 0x1806
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[Offset1]

			ALLOW_CHECK :
			JMP[Offset2]
	}
}

void __declspec(naked) cWings::Function20()
{
	static DWORD Offset1 = 0x5EBB7D;
	static DWORD Offset2 = 0x5EBB77;

	_asm
	{
		CMP AX, ITEMGET(12, 100);
		JL ALLOW_CHECK
			CMP AX, ITEMGET(12, 200);
		JLE ALLOW_CHECK

			NEXT_CHECK :
		CMP AX, 0x1800
			JL ALLOW_CHECK
			CMP AX, 0x1806
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[Offset2]

			ALLOW_CHECK :
			JMP[Offset1]
	}
}

void __declspec(naked) cWings::Function21()
{
	static DWORD Offset1 = 0x5EBE0A;
	static DWORD Offset2 = 0x5EBE02;

	_asm
	{
		CMP AX, ITEMGET(12, 100);
		JL NEXT_CHECK
			CMP AX, ITEMGET(12, 200);
		JG NEXT_CHECK
			JMP[Offset2]

			NEXT_CHECK:
		CMP AX, 0x1800
			JL NEXT_CHECK2
			CMP AX, 0x1806
			JG NEXT_CHECK2
			JMP[Offset2]

			NEXT_CHECK2 :
			JMP[Offset1]
	}
}

void __declspec(naked) cWings::Function22()
{
	static DWORD ItemIndex;
	static DWORD Offset1 = 0x5F892C;
	static DWORD Offset2 = 0x5F878E;
	static DWORD Offset3 = 0x5F8748;

	_asm
	{
		MOV ItemIndex, ECX
	}

	if (ItemIndex >= ITEM_ID(12, 0) && ItemIndex <= ITEM_ID(12, 2) || ItemIndex >= ITEM_ID(12, 100) && ItemIndex <= ITEM_ID(12, 200))
	{
		__asm
		{
			JMP[Offset1]
		}
	}
	else
	{
		_asm
		{
			CMP ECX, 0x1A0E
			JG Next_Check
			JMP[Offset3]
			Next_Check:
			JMP[Offset2]
		}
	}

}

void __declspec(naked) cWings::Shine()
{
	static DWORD Glow = 0x5F892C;
	static DWORD Continue = 0x5F885A;
	static DWORD Return = 0x5F87CD;

	_asm
	{
		CMP ECX, ITEM_ID(13, 30)
		JG NOES
		JE ESITEM
		CMP ECX, ITEM_ID(12, 100)
		JG NOES
		JE ESITEM
		CMP ECX, ITEM_ID(12, 200)
		JG NOES
		JE ESITEM
		JMP Return

		NOES :
		JMP Continue

			ESITEM :
		JMP Glow
	}
}

cWings Wing;