#include "stdafx.h"


DWORD SecondWeaponFixVal = 0;
DWORD IsShield = 0;

__declspec(naked) void WeaponViewCheck()
{
	__asm
	{

		MOV BYTE PTR SS : [STACK_PTR + WeaponViewFlagFixup], 0

		CMP DWORD PTR SS : [STACK_PTR + SafeZoneFlagFixup], 0
		JE WEAPON_CHECK
		MOV BYTE PTR SS : [STACK_PTR + WeaponViewFlagFixup], 1

		WEAPON_CHECK :

					 CMP EAX, 0
					 JNZ LEFT_HAND

					 CMP WORD PTR DS : [CHAR_REG + RightHandFixup], MAKE_ITEM(7, 0) + OBJ_OFFS
					 JGE NO_DISPLAY

					 CMP WORD PTR DS : [CHAR_REG + RightHandFixup], MAKE_ITEM(4, 15) + OBJ_OFFS
					 JE DISPLAY_WEAPON
					 JMP END_CHECK

					 LEFT_HAND :


		CMP WORD PTR DS : [CHAR_REG + LeftHandFixup], MAKE_ITEM(7, 0) + OBJ_OFFS
			JGE NO_DISPLAY

			CMP WORD PTR DS : [CHAR_REG + LeftHandFixup], MAKE_ITEM(4, 7) + OBJ_OFFS
			JE DISPLAY_WEAPON
			JMP END_CHECK


			DISPLAY_WEAPON :
		MOV BYTE PTR SS : [STACK_PTR + WeaponViewFlagFixup], 1
			JMP END_CHECK

			NO_DISPLAY :
		MOV BYTE PTR SS : [STACK_PTR + WeaponViewFlagFixup], 0


			END_CHECK :

			jmp WeaponViewCheck_Ret
	}
}

__declspec(naked) void SecondWeaponViewCheck()
{
	__asm
	{
		CMP SecondWeaponFixVal, 0
		JNZ END_CHECK

		MOV EAX, 1
		MOV SecondWeaponFixVal, 1


		JMP WeaponViewCheck

		END_CHECK :
		MOV SecondWeaponFixVal, 0
			jmp SecondWeaponViewCheck_Ret
	}
}

__declspec(naked) void SecondWeaponViewCheckReplacedCode()
{
	__asm
	{
		MOV EAX, DWORD PTR DS : [0x6B8D48]

		JMP SecondWeaponViewCheck
	}
}

DWORD s_eax, s_ecx, s_edx;

__declspec(naked) void SecondWeaponViewFix()
{
	__asm
	{


		MOV s_eax, EAX
		MOV s_ecx, ECX
		MOV s_edx, EDX


		MOV IsShield, 0

		// check for shield
		CMP WEAPON_ID_CONTAINER, MAKE_ITEM(6, 0) + OBJ_OFFS
		JL FLIP_CHECK
		CMP WEAPON_ID_CONTAINER, MAKE_ITEM(7, 0) + OBJ_OFFS
		JGE FLIP_CHECK

		MOV IsShield, 1

		CMP WEAPON_ID_CONTAINER, MAKE_ITEM(6, 16) + OBJ_OFFS
		JNZ CHECK_SHIELD_14_15


		MOV DWORD PTR SS : [STACK_PTR + RotFixup], 0x41F00000
		MOV DWORD PTR SS : [STACK_PTR + RotFixup + 4], 0
		MOV DWORD PTR SS : [STACK_PTR + RotFixup + 8], 0x42B40000
		LEA EDX, DWORD PTR SS : [STACK_PTR + TransFixup]
		LEA EAX, DWORD PTR SS : [STACK_PTR + RotFixup]
		PUSH EDX
		PUSH EAX
		CALL RotateFunc
		ADD ESP, 0x8
		MOV DWORD PTR SS : [STACK_PTR + TransFixup + 0x0C], 0xC1A00000
		MOV DWORD PTR SS : [STACK_PTR + TransFixup + 0x1C], 0
		MOV DWORD PTR SS : [STACK_PTR + TransFixup + 0x2C], 0xC1A00000

		JMP FLIP_CHECK


		CHECK_SHIELD_14_15 :

		CMP WEAPON_ID_CONTAINER, MAKE_ITEM(6, 15) + OBJ_OFFS
			JE SHIELD_14_15
			CMP WEAPON_ID_CONTAINER, MAKE_ITEM(6, 14) + OBJ_OFFS
			JNZ CHECK_SHIELD_6

			SHIELD_14_15 :

		MOV DWORD PTR SS : [STACK_PTR + RotFixup], 0x42480000
			MOV DWORD PTR SS : [STACK_PTR + RotFixup + 4], 0
			MOV DWORD PTR SS : [STACK_PTR + RotFixup + 8], 0x42B40000
			LEA EDX, DWORD PTR SS : [STACK_PTR + TransFixup]
			LEA EAX, DWORD PTR SS : [STACK_PTR + RotFixup]
			PUSH EDX
			PUSH EAX
			CALL RotateFunc
			ADD ESP, 8
			MOV DWORD PTR SS : [STACK_PTR + TransFixup + 0x0C], 0xC1E00000
			MOV DWORD PTR SS : [STACK_PTR + TransFixup + 0x1C], 0
			MOV DWORD PTR SS : [STACK_PTR + TransFixup + 0x2C], 0xC1C80000

			JMP FLIP_CHECK


			CHECK_SHIELD_6 :

		CMP WEAPON_ID_CONTAINER, MAKE_ITEM(6, 6) + OBJ_OFFS
			JNZ SET_SHIELD

			MOV DWORD PTR SS : [STACK_PTR + RotFixup], 0x41F00000
			MOV DWORD PTR SS : [STACK_PTR + RotFixup + 4], 0
			MOV DWORD PTR SS : [STACK_PTR + RotFixup + 8], 0x42B40000
			LEA EDX, DWORD PTR SS : [STACK_PTR + TransFixup]
			LEA EAX, DWORD PTR SS : [STACK_PTR + RotFixup]
			PUSH EDX
			PUSH EAX
			CALL RotateFunc
			ADD ESP, 8
			MOV DWORD PTR SS : [STACK_PTR + TransFixup + 0x0C], 0xC1700000
			MOV DWORD PTR SS : [STACK_PTR + TransFixup + 0x1C], 0
			MOV DWORD PTR SS : [STACK_PTR + TransFixup + 0x2C], 0xC1C80000

			JMP FLIP_CHECK

			SET_SHIELD :

		MOV DWORD PTR SS : [STACK_PTR + TransFixup + 0x0C], 0xC1200000
			MOV DWORD PTR SS : [STACK_PTR + TransFixup + 0x1C], 0
			MOV DWORD PTR SS : [STACK_PTR + TransFixup + 0x2C], 0

			FLIP_CHECK :

			CMP IsShield, 1
			JE EXIT

			CMP SecondWeaponFixVal, 0
			JE EXIT

			SUB ESP, 0x3C

			MOV DWORD PTR SS : [ESP + 0x30], 0x43110000
			MOV DWORD PTR SS : [ESP + 0x34], 0
			MOV DWORD PTR SS : [ESP + 0x38], 0x43898000
			LEA EAX, DWORD PTR SS : [ESP]
			LEA ECX, DWORD PTR SS : [ESP + 0x30]
			PUSH EAX
			PUSH ECX
			CALL RotateFunc
			ADD ESP, 8

			MOV DWORD PTR SS : [ESP + 0x0C], 0
			MOV DWORD PTR SS : [ESP + 0x1C], 0x41200000
			MOV DWORD PTR SS : [ESP + 0x2C], 0xC1F00000
			LEA EDX, DWORD PTR SS : [STACK_PTR + TransFixup]
			LEA EAX, DWORD PTR SS : [ESP]
			LEA ECX, DWORD PTR SS : [STACK_PTR + TransFixup]
			PUSH EDX
			PUSH EAX
			PUSH ECX
			CALL TransFunc

			ADD ESP, 0x48

			EXIT:

		MOV EAX, s_eax
			MOV ECX, s_ecx
			MOV EDX, s_edx

			PUSH SomeVal4
			JMP SecondWeaponViewFix_Ret
	}
}

void ItemView()
{
	SetCompleteHook(0xE9, WeaponViewCheck_Hook, &WeaponViewCheck);
	SetCompleteHook(0xE9, SecondWeaponViewCheckReplacedCode_Hook, &SecondWeaponViewCheckReplacedCode);
	SetCompleteHook(0xFF, SecondWeaponViewCheck_Hook1, &SecondWeaponViewCheck);
	SetCompleteHook(0xFF, SecondWeaponViewCheck_Hook2, &SecondWeaponViewCheck);
	SetCompleteHook(0xE9, SecondWeaponViewFix_Hook, &SecondWeaponViewFix);
}
