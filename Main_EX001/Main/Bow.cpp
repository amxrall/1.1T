#include "StdAfx.h"

void cBows::Load()
{
	HookJump(0x5CF247, this->NewBows1);
	HookJump(0x4EB652, this->NewBows2);
	HookJump(0x4EA96C, this->NewBows3);
	HookJump(0x5048F3, this->NewBows4);
	HookJump(0x4EC5CA, this->NewBows5);
	HookJump(0x4EC837, this->NewBows6);
	HookJump(0x555F62, this->NewBows7);
	HookJump(0x54C3F0, this->NewBows8);
	HookJump(0x543AE8, this->NewBows9);
	HookJump(0x5A811A, this->NewBows10);
	HookJump(0x55930B, this->NewBows11);
	HookJump(0x58D58F, this->NewBows12);
	HookJump(0x555BF5, this->NewBows13);
	HookJump(0x54C052, this->NewBows14);
	HookJump(0x572594, this->NewBows15);
	HookJump(0x570D2B, this->NewBows16);
	HookJump(0x4EC5E9, this->NewCrossbows1);
	HookJump(0x4EC861, this->NewCrossbows2);
	HookJump(0x53382A, this->NewCrossbows3);
	HookJump(0x4EB671, this->NewCrossbows4);
	HookJump(0x4C58D4, this->NewCrossbows5);
	HookJump(0x5F54C0, this->NewCrossbows6);
	HookJump(0x50491D, this->NewCrossbows7);
	HookJump(0x5001A1, this->NewCrossbows8);
	HookJump(0x4EA98B, this->NewCrossbows9);
	HookJump(0x53347F, this->MultipleShotSkillEffect);
	HookJump(0x53362F, this->SingleShotSkillEffect);
}

sBows* cBows::Get(WORD Index)
{
	if (this->Item.count(Index) > 0)
	{
		return &this->Item.at(Index);
	}

	return NULL;
}

__declspec(naked) void cBows::NewBows1()
{
	static DWORD Local[2] = { 0x5CF24F, 0x5CF274 };
	static DWORD Id;
	static sBows* Value;

	__asm
	{
		MOV Id, ESI;
		PUSHAD;
	}

	Value = Bow.Get((WORD)(Id - 515));

	if (Value && Value->Type == 4)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP ESI, 0xA18;
		JNZ NotZero;
		JMP Local[0];

	NotZero:
		JMP Local[4];
	}
}

__declspec(naked) void cBows::NewBows2()
{
	static DWORD Local[2] = { 0x4EB659, 0x4EB6A0 };
	static WORD Id;
	static sBows* Value;

	__asm
	{
		MOV Id, CX;
		PUSHAD;
	}

	Value = Bow.Get(Id - 515);

	if (Value && Value->Type == 4)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		CMP CX, 0xA18;
		JE Equal;
		JMP Local[0];

	Equal:
		JMP Local[4];
	}
}

__declspec(naked) void cBows::NewBows3()
{
	static DWORD Local[2] = { 0x4EA973, 0x4EA9BB };
	static WORD Id;
	static sBows* Value;

	__asm
	{
		MOV Id, CX;
		PUSHAD;
	}

	Value = Bow.Get(Id - 515);

	if (Value && Value->Type == 4)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		CMP CX, 0xA18;
		JE Equal;
		JMP Local[0];

	Equal:
		JMP Local[4];
	}
}

__declspec(naked) void cBows::NewBows4()
{
	static DWORD Local[2] = { 0x5048FA, 0x504936 };
	static WORD Id;
	static sBows* Value;

	__asm
	{
		MOV Id, DI;
		PUSHAD;
	}

	Value = Bow.Get(Id - 515);

	if (Value && Value->Type == 4)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		CMP DI, 0xA18;
		JE Equal;
		JMP Local[0];

	Equal:
		JMP Local[4];
	}
}

__declspec(naked) void cBows::NewBows5()
{
	static DWORD Local[2] = { 0x4EC5D1, 0x4EC626 };
	static WORD Id;
	static sBows* Value;

	__asm
	{
		MOV Id, CX;
		PUSHAD;
	}

	Value = Bow.Get(Id - 515);

	if (Value && Value->Type == 4)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		CMP CX, 0xA18;
		JE Equal;
		JMP Local[0];

	Equal:
		JMP Local[4];
	}
}

__declspec(naked) void cBows::NewBows6()
{
	static DWORD Local[2] = { 0x4EC842, 0x4EC8CE };
	static WORD Id;
	static sBows* Value;

	__asm
	{
		MOV Id, CX;
		PUSHAD;
	}

	Value = Bow.Get(Id - 515);

	if (Value && Value->Type == 4)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		CMP CX, 0xA18;
		JE Equal;
		JMP Local[0];

	Equal:
		JMP Local[4];
	}
}

__declspec(naked) void cBows::NewBows7()
{
	static DWORD Local[2] = { 0x555F6E, 0x555FF4 };
	static DWORD Id;
	static sBows* Value;

	__asm
	{
		MOV Id, EBX;
		PUSHAD;
	}

	Value = Bow.Get((WORD)(Id));

	if (Value && Value->Type == 4)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP EBX, 0x815;
		JNZ NotZero;
		JMP Local[0];

	NotZero:
		JMP Local[4];
	}
}

__declspec(naked) void cBows::NewBows8()
{
	static DWORD Local[2] = { 0x54C3F8, 0x54C41F };
	static DWORD Id;
	static sBows* Value;

	__asm
	{
		MOV Id, ESI;
		PUSHAD;
	}

	Value = Bow.Get((WORD)(Id));

	if (Value && Value->Type == 4)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		CMP ESI, 0x815;
		JE Equal;
		JMP Local[0];

	Equal:
		JMP Local[4];
	}
}

__declspec(naked) void cBows::NewBows9()
{
	static DWORD Local[2] = { 0x543AEF, 0x543AFC };
	static WORD Id;
	static sBows* Value;

	__asm
	{
		MOV Id, BX;
		PUSHAD;
	}

	Value = Bow.Get(Id);

	if (Value && Value->Type == 4)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP BX, 0x815;
		JNZ NotZero;
		JMP Local[0];

	NotZero:
		JMP Local[4];
	}
}

__declspec(naked) void cBows::NewBows10()
{
	static DWORD Local[2] = { 0x5A8120, 0x5A8148 };
	static WORD Id;
	static sBows* Value;

	__asm
	{
		MOV Id, AX;
		PUSHAD;
	}

	Value = Bow.Get(Id);

	if (Value && Value->Type == 4)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		CMP AX, 0x815;
		JE Equal;
		JMP Local[0];

	Equal:
		JMP Local[4];
	}
}

__declspec(naked) void cBows::NewBows11()
{
	static DWORD Local[2] = { 0x559312, 0x559319 };
	static DWORD Id;
	static sBows* Value;

	__asm
	{
		MOV Id, EAX;
		PUSHAD;
	}

	Value = Bow.Get((WORD)(Id));

	if (Value && Value->Type == 4)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP EAX, 0x815;
		JNZ NotZero;
		JMP Local[0];

	NotZero:
		JMP Local[4];
	}
}

__declspec(naked) void cBows::NewBows12()
{
	static DWORD Local[2] = { 0x58D596, 0x58D5B2 };
	static DWORD Id;
	static sBows* Value;

	__asm
	{
		MOV Id, EAX;
		PUSHAD;
	}

	Value = Bow.Get((WORD)(Id));

	if (Value && Value->Type == 4)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		CMP EAX, 0x815;
		JE Equal;
		JMP Local[0];

	Equal:
		JMP Local[4];
	}
}

__declspec(naked) void cBows::NewBows13()
{
	static DWORD Local[2] = { 0x555BFC, 0x555C67 };
	static WORD Id;
	static sBows* Value;

	__asm
	{
		MOV Id, CX;
		PUSHAD;
	}

	Value = Bow.Get(Id);

	if (Value && Value->Type == 4)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP CX, 0x815;
		JNZ NotZero;
		JMP Local[0];

	NotZero:
		JMP Local[4];
	}
}

__declspec(naked) void cBows::NewBows14()
{
	static DWORD Local[2] = { 0x54C05A, 0x54C083 };
	static DWORD Id;
	static sBows* Value;

	__asm
	{
		MOV Id, ESI;
		PUSHAD;
	}

	Value = Bow.Get((WORD)(Id));

	if (Value && Value->Type == 4)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		CMP ESI, 0x815;
		JE Equal;
		JMP Local[0];

	Equal:
		JMP Local[4];
	}
}

__declspec(naked) void cBows::NewBows15()
{
	static DWORD Local[2] = { 0x57259A, 0x5725A8 };
	static WORD Id;
	static sBows* Value;

	__asm
	{
		MOV Id, AX;
		PUSHAD;
	}

	Value = Bow.Get(Id - 515);

	if (Value && Value->Type == 4)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		CMP AX, 0xA18;
		JE Equal;
		JMP Local[0];

	Equal:
		JMP Local[4];
	}
}

__declspec(naked) void cBows::NewBows16()
{
	static DWORD Local[2] = { 0x570D31, 0x570D47 };
	static WORD Id;
	static sBows* Value;

	__asm
	{
		MOV Id, AX;
		PUSHAD;
	}

	Value = Bow.Get(Id - 515);

	if (Value && Value->Type == 4)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		CMP AX, 0xA18;
		JE Equal;
		JMP Local[0];

	Equal:
		JMP Local[4];
	}
}

__declspec(naked) void cBows::NewCrossbows1()
{
	static DWORD Local[2] = { 0x4EC5F3, 0x4EC3A5 };
	static WORD Id;
	static sBows* Value;

	__asm
	{
		MOV Id, AX;
		PUSHAD;
	}

	Value = Bow.Get(Id - 515);

	if (Value && Value->Type == 16)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP AX, 0xA15;
		JL Less;
		JMP Local[0];

	Less:
		JMP Local[4];
	}
}

__declspec(naked) void cBows::NewCrossbows2()
{
	static DWORD Local[2] = { 0x4EC867, 0x4EC877 };
	static WORD Id;
	static sBows* Value;

	__asm
	{
		MOV Id, AX;
		PUSHAD;
	}

	Value = Bow.Get(Id - 515);

	if (Value && Value->Type == 16)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP AX, 0xA15;
		JL Less;
		JMP Local[0];

	Less:
		JMP Local[4];
	}
}

__declspec(naked) void cBows::NewCrossbows3()
{
	static DWORD Local[2] = { 0x533835, 0x533985 };
	static WORD Id;
	static sBows* Value;

	__asm
	{
		MOV Id, DX;
		PUSHAD;
	}

	Value = Bow.Get(Id - 515);

	if (Value && Value->Type == 16)
	{
		__asm
		{
			POPAD;
			JMP Equal;
		}
	}

	__asm
	{
		POPAD;
		CMP DX, 0xA15;
		JE Equal;
		JMP Local[0];

	Equal:
		JMP Local[4];
	}
}

__declspec(naked) void cBows::NewCrossbows4()
{
	static DWORD Local[2] = { 0x4EB677, 0x4EB684 };
	static WORD Id;
	static sBows* Value;

	__asm
	{
		MOV Id, AX;
		PUSHAD;
	}

	Value = Bow.Get(Id - 515);

	if (Value && Value->Type == 16)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP AX, 0xA15;
		JL Less;
		JMP Local[0];

	Less:
		JMP Local[4];
	}
}

__declspec(naked) void cBows::NewCrossbows5()
{
	static DWORD Local[2] = { 0x4C58DA, 0x4C5940 };
	static WORD Id;
	static sBows* Value;

	__asm
	{
		MOV Id, AX;
		PUSHAD;
	}

	Value = Bow.Get(Id - 515);

	if (Value && Value->Type == 16)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP AX, 0xA15;
		JL Less;
		JMP Local[0];

	Less:
		JMP Local[4];
	}
}

__declspec(naked) void cBows::NewCrossbows6()
{
	static DWORD Local[2] = { 0x5F54C7, 0x5F54DA };
	static WORD Id;
	static sBows* Value;

	__asm
	{
		MOV Id, CX;
		PUSHAD;
	}

	Value = Bow.Get(Id - 515);

	if (Value && Value->Type == 16)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP CX, 0xA15;
		JL Less;
		JMP Local[0];

	Less:
		JMP Local[4];
	}
}

__declspec(naked) void cBows::NewCrossbows7()
{
	static DWORD Local[2] = { 0x504924, 0x50492F };
	static WORD Id;
	static sBows* Value;

	__asm
	{
		MOV Id, CX;
		PUSHAD;
	}

	Value = Bow.Get(Id - 515);

	if (Value && Value->Type == 16)
	{
		__asm
		{
			POPAD;
			JMP Local[0];
		}
	}

	__asm
	{
		POPAD;
		CMP CX, 0xA15;
		JL Less;
		JMP Local[0];

	Less:
		JMP Local[4];
	}
}

__declspec(naked) void cBows::NewCrossbows8()
{
	static DWORD Local[2] = { 0x5001A7, 0x5001B1 };
	static DWORD Id;
	static sBows* Value;

	__asm
	{
		MOV Id, EDI;
		PUSHAD;
	}

	Value = Bow.Get((WORD)(Id - 515));

	if (Value && Value->Type == 16)
	{
		__asm
		{
			POPAD;
			JMP Local[4];
		}
	}

	__asm
	{
		POPAD;
		CMP EDI, 0xA15;
		JMP Local[0];
	}
}

__declspec(naked) void cBows::NewCrossbows9()
{
	static DWORD Local[2] = { 0x4EA99F, 0x4EA991 };
	static WORD Id;
	static sBows* Value;

	__asm
	{
		MOV Id, AX;
		PUSHAD;
	}

	Value = Bow.Get(Id - 515);

	if (Value && Value->Type == 16)
	{
		__asm
		{
			POPAD;
			JMP Local[4];
		}
	}

	__asm
	{
		POPAD;
		CMP AX, 0xA15;
		JL Less;
		JMP Local[4];

	Less:
		JMP Local[0];
	}
}

__declspec(naked) void cBows::MultipleShotSkillEffect()
{
	static DWORD Local[11] = { 0x533495, 0x5334BE, 0x5334E7, 0x533510, 0x533539, 0x533562, 0x53358B, 0x5335B1, 0x5335D7, 0x5335FD, 0x533485 };
	static DWORD Item1;
	static DWORD Item2;
	static sBows* Value;
	static bool Effect = false;

	__asm
	{
		MOV Effect, 0;
		MOV Item1, EDX;
		MOV Item2, ECX;
		ADD ECX, -0xA0B;
		PUSHAD;
	}

	Value = Bow.Get((WORD)(Item1));

	if (Value && Value->Type == 4)
	{
		Effect = true;
	}

	if (!Effect)
	{
		Value = Bow.Get((WORD)(Item2 - 515));

		if (Value && Value->Type == 16)
		{
			Effect = true;
		}
	}

	if (Effect)
	{
		if (Value->Subtype == 0)
		{
			__asm
			{
				POPAD;
				JMP Local[0];
			}
		}
		else if (Value->Subtype == 1)
		{
			__asm
			{
				POPAD;
				JMP Local[4];
			}
		}
		else if (Value->Subtype == 2)
		{
			__asm
			{
				POPAD;
				JMP Local[8];
			}
		}
		else if (Value->Subtype == 3)
		{
			__asm
			{
				POPAD;
				JMP Local[12];
			}
		}
		else if (Value->Subtype == 4)
		{
			__asm
			{
				POPAD;
				JMP Local[16];
			}
		}
		else if (Value->Subtype == 5)
		{
			__asm
			{
				POPAD;
				JMP Local[20];
			}
		}
		else if (Value->Subtype == 6)
		{
			__asm
			{
				POPAD;
				JMP Local[24];
			}
		}
		else if (Value->Subtype == 7)
		{
			__asm
			{
				POPAD;
				JMP Local[28];
			}
		}
		else if (Value->Subtype == 8)
		{
			__asm
			{
				POPAD;
				JMP Local[32];
			}
		}
		else if (Value->Subtype == 9)
		{
			__asm
			{
				POPAD;
				JMP Local[36];
			}
		}
	}

	__asm
	{
		POPAD;
		JMP Local[40];
	}
}

__declspec(naked) void cBows::SingleShotSkillEffect()
{
	static DWORD Local[7] = { 0x53364D, 0x533680, 0x5336B3, 0x5336E6, 0x533719, 0x53374C, 0x533635 };
	static DWORD Item1;
	static DWORD Item2;
	static sBows* Value;
	static bool Effect = false;

	__asm
	{
		MOV Effect, 0;
		MOV ECX, DWORD PTR SS : [EBP + 0x8];
		MOV Item2, ECX;
		LEA ECX, DWORD PTR DS : [EDX - 0xA03];
		MOV Item1, EDX;
		PUSHAD;
	}

	Value = Bow.Get((WORD)(Item1 - 515));

	if (Value && Value->Type == 4)
	{
		Effect = true;
	}

	if (!Effect)
	{
		Value = Bow.Get((WORD)(Item2 - 515));

		if (Value && Value->Type == 16)
		{
			Effect = true;
		}
	}

	if (Effect)
	{
		if (Value->Subtype >= 0 && Value->Subtype <= 4)
		{
			__asm
			{
				POPAD;
				JMP Local[0];
			}
		}
		else if (Value->Subtype == 5)
		{
			__asm
			{
				POPAD;
				JMP Local[4];
			}
		}
		else if (Value->Subtype == 6)
		{
			__asm
			{
				POPAD;
				JMP Local[8];
			}
		}
		else if (Value->Subtype == 7)
		{
			__asm
			{
				POPAD;
				JMP Local[12];
			}
		}
		else if (Value->Subtype == 8)
		{
			__asm
			{
				POPAD;
				JMP Local[16];
			}
		}
		else if (Value->Subtype == 9)
		{
			__asm
			{
				POPAD;
				JMP Local[20];
			}
		}
	}

	__asm
	{
		POPAD;
		JMP Local[24];
	}
}

cBows Bow;