#include "StdAfx.h"
#include "WingManager.h"

//CWingManager gWingManager;
//
//// ---
//WORD	WingsAdd28Option_Pointer;
//DWORD	WingsAdd28Option_Buff;
//// ---
//void CWingManager::Load()
//{
//
//	SetRange((LPVOID)0x00541703,6,ASM::NOP);
//	SetJmp((LPVOID)0x00541703,this->Add28Option);
//
//}
//
//void Naked CWingManager::Add28Option()
//{
//	_asm
//	{
//		MOV WingsAdd28Option_Pointer,AX
//	}
//	// ---
//	if( WingsAdd28Option_Pointer == ITEM(12,4) || WingsAdd28Option_Pointer >= ITEM(12,36) && WingsAdd28Option_Pointer <= ITEM(12,100))
//	{
//		_asm
//		{
//			MOV WingsAdd28Option_Buff,0x00541709
//			JMP WingsAdd28Option_Buff
//		}
//	}
//	else
//	{
//		_asm
//		{
//			MOV WingsAdd28Option_Buff,0x00541726
//			JMP WingsAdd28Option_Buff
//		}
//	}
//}




/*void ItemSetOptions(LPVOID ItemStruct, unsigned __int8 Option, unsigned __int8 Special, BYTE Value)
{
	ObjectItem * lpItem = (ObjectItem*)&(*(int*)ItemStruct);

	int ItemType = GET_ITEMTYPE(lpItem->Index);
	int ItemIndex = GET_ITEMINDEX(lpItem->Index);
	int OldIndex = lpItem->Index;

	if (ItemType == 12 && (ItemIndex >= MIN_WING_INDEX && ItemIndex <= MAX_WING_INDEX))
	{
		lpItem->Index = ITEMGET(12, 4);
	}
	pItemSetOptionAdd((LPVOID)lpItem, Option, Special, Value);

	if (lpItem->Index != OldIndex)
	{
		lpItem->Index = OldIndex;
	}
}

void __declspec(naked) CustomWingFunction01()
{
	static DWORD CustomWingFunction01_Offset01 = 0x005A5361;//005B392B  |> 66:81F9 031A   CMP CX,1A03
	static DWORD CustomWingFunction01_Offset02 = 0x005A531E;//005B3885  |. 8D0480         LEA EAX,DWORD PTR DS:[EAX+EAX*4]

	_asm
	{
		CMP CX, MIN_WING_ITEMID
		JL NEXT_CHECK
		CMP CX, MAX_WING_ITEMID
		JG NEXT_CHECK
		JMP[CustomWingFunction01_Offset02]

		NEXT_CHECK:
		CMP CX, 0x1803
			JL NEXT_CHECK2
			CMP CX, 0x1806
			JG NEXT_CHECK2
			JMP[CustomWingFunction01_Offset02]

			NEXT_CHECK2 :
			JMP[CustomWingFunction01_Offset01]
	}
}

void __declspec(naked) CustomWingFunction02()
{
	static DWORD CustomWingFunction02_Offset01 = 0x005A770E;//005B5DC3  |> 66:3D 1E1A     CMP AX,1A1E
	static DWORD CustomWingFunction02_Offset02 = 0x005A7714;//005B5DC9  |> 83FE 07        CMP ESI,7

	_asm
	{
		CMP AX, MIN_WING_ITEMID
		JL NEXT_CHECK
		CMP AX, MAX_WING_ITEMID
		JLE ALLOW_CHECK

		NEXT_CHECK :
		CMP AX, 0x1803
			JL NEXT_CHECK1
			CMP AX, 0x1806
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[CustomWingFunction02_Offset01]

			ALLOW_CHECK :
			JMP[CustomWingFunction02_Offset02]
	}

}

void __declspec(naked) CustomWingFunction03()
{
	static DWORD CustomWingFunction03_Offset01 = 0x005A7D7E;//005B6433  |> 66:81F9 1E1A   CMP CX,1A1E
	static DWORD CustomWingFunction03_Offset02 = 0x005A7D85;//005B643A  |> 85F6           TEST ESI,ESI

	_asm
	{
		CMP CX, MIN_WING_ITEMID
		JL NEXT_CHECK
		CMP CX, MAX_WING_ITEMID
		JLE ALLOW_CHECK

		NEXT_CHECK :
		CMP CX, 0x1803
			JL NEXT_CHECK1
			CMP CX, 0x1806
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[CustomWingFunction03_Offset01]

			ALLOW_CHECK :
			JMP[CustomWingFunction03_Offset02]
	}
}

void __declspec(naked) CustomWingFunction04()
{
	static DWORD CustomWingFunction04_Offset01 = 0x005EBE0A;//005FB8C6  |> 8B45 84        MOV EAX,DWORD PTR SS:[EBP-7C]
	static DWORD CustomWingFunction04_Offset02 = 0x005EBE02;//005FB8BE  |. FF45 88        INC DWORD PTR SS:[EBP-78]

	_asm
	{
		CMP AX, MIN_WING_ITEMID
		JL NEXT_CHECK
		CMP AX, MAX_WING_ITEMID
		JG NEXT_CHECK
		JMP[CustomWingFunction04_Offset02]

		NEXT_CHECK:
		CMP AX, 0x1803
			JL NEXT_CHECK2
			CMP AX, 0x1806
			JG NEXT_CHECK2
			JMP[CustomWingFunction04_Offset02]

			NEXT_CHECK2 :
			JMP[CustomWingFunction04_Offset01]
	}
}

void __declspec(naked) CustomWingFunction05()
{
	static DWORD CustomWingFunction05_Offset01 = 0x005AA347;//005B918B  |> 66:3D 301C     CMP AX,1C30
	static DWORD CustomWingFunction05_Offset02 = 0x005AA361;//005B91A5  |> 66:3D 2B1A     CMP AX,1A2B

	_asm
	{
		CMP AX, MIN_WING_ITEMID2
		JL NEXT_CHECK
		CMP AX, MAX_WING_ITEMID2
		JLE ALLOW_CHECK

		NEXT_CHECK :
		CMP AX, 0x1A03//0x1A12
			JL NEXT_CHECK1
			CMP AX, 0x1A09//1A18
			JLE ALLOW_CHECK


			NEXT_CHECK1 :
		JMP[CustomWingFunction05_Offset01]

			ALLOW_CHECK :
			JMP[CustomWingFunction05_Offset02]
	}
}

void __declspec(naked) CustomWingFunction06()
{
	static DWORD CustomWingFunction06_Offset01 = 0x005F9DE7;//0060AD50  |> 66:3D 301C     CMP AX,1C30
	static DWORD CustomWingFunction06_Offset02 = 0x005F9E4A;//0060ADB3  |> 8B45 20        MOV EAX,DWORD PTR SS:[EBP+20]

	_asm
	{
		CMP AX, MIN_WING_ITEMID2
		JL NEXT_CHECK
		CMP AX, MAX_WING_ITEMID2
		JLE ALLOW_CHECK

		NEXT_CHECK :
		CMP AX, 0x1A03//1A12
			JL NEXT_CHECK1
			CMP AX, 0x1A09//1A18
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[CustomWingFunction06_Offset01]

			ALLOW_CHECK :
			JMP[CustomWingFunction06_Offset02]
	}
}

void __declspec(naked) CustomWingFunction07()
{
	static DWORD CustomWingFunction07_Offset01 = 0x005414CF;//00549E8E  |> 66:813E 1E1A   CMP WORD PTR DS:[ESI],1A1E
	static DWORD CustomWingFunction07_Offset02 = 0x005414BE;//00549E7D  |. 33D2           XOR EDX,EDX

	_asm
	{
		CMP AX, MIN_WING_ITEMID
		JL NEXT_CHECK
		CMP AX, MAX_WING_ITEMID
		JG NEXT_CHECK
		JMP[CustomWingFunction07_Offset02]

		NEXT_CHECK:
		CMP AX, 0x1800
			JL NEXT_CHECK2
			CMP AX, 0x1806
			JG NEXT_CHECK2
			JMP[CustomWingFunction07_Offset02]

			NEXT_CHECK2 :
			JMP[CustomWingFunction07_Offset01]
	}
}

void __declspec(naked) CustomWingFunction08()
{
	static DWORD CustomWingFunction08_Offset01 = 0x00542D9B;//0054B853  |> 66:3D 1D1A     CMP AX,1A1D
	static DWORD CustomWingFunction08_Offset02 = 0x00542DFC;//0054B8B4  |> 81FE E8030000  CMP ESI,3E8

	_asm
	{
		CMP AX, MIN_WING_ITEMID
		JL NEXT_CHECK
		CMP AX, MAX_WING_ITEMID
		JLE ALLOW_CHECK

		NEXT_CHECK :
		CMP AX, 0x1800
			JL NEXT_CHECK1
			CMP AX, 0x1806
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[CustomWingFunction08_Offset01]

			ALLOW_CHECK :
			JMP[CustomWingFunction08_Offset02]
	}
}

void __declspec(naked) CustomWingFunction09()
{
	static DWORD CustomWingFunction09_Offset01 = 0x0058A071;//00597873  |> 66:8B82 AC0D00>|MOV AX,WORD PTR DS:[EDX+DAC]
	static DWORD CustomWingFunction09_Offset02 = 0x0058A0E1;//005978E8  |> 83FB 41        |CMP EBX,41



	_asm
	{
		CMP AX, MIN_WING_ITEMID
		JL NEXT_CHECK
		CMP AX, MAX_WING_ITEMID
		JLE ALLOW_CHECK

		NEXT_CHECK :
		CMP AX, 0x1800
			JL NEXT_CHECK1
			CMP AX, 0x1806
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[CustomWingFunction09_Offset01]

			ALLOW_CHECK :
			JMP[CustomWingFunction09_Offset02]
	}
}

void __declspec(naked) CustomWingFunction10()
{
	static DWORD CustomWingFunction10_Offset01 = 0x005A1388;//005AF178  |> 66:83FA 13     CMP DX,13
	static DWORD CustomWingFunction10_Offset02 = 0x005A13B3;//005AF1A3  |> 5F             POP EDI



	_asm
	{
		CMP DX, MIN_WING_ITEMID
		JL NEXT_CHECK
		CMP DX, MAX_WING_ITEMID
		JLE ALLOW_CHECK

		NEXT_CHECK :
		CMP DX, 0x1803
			JL NEXT_CHECK1
			CMP DX, 0x1806
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[CustomWingFunction10_Offset01]

			ALLOW_CHECK :
			JMP[CustomWingFunction10_Offset02]
	}
}

void __declspec(naked) CustomWingFunction11()
{
	static DWORD CustomWingFunction11_Offset01 = 0x005A1950;//005AF8A4  |> 83F8 13        CMP EAX,13
	static DWORD CustomWingFunction11_Offset02 = 0x005A191E;//005AF870  |. 8B45 0C        MOV EAX,DWORD PTR SS:[EBP+C]

	_asm
	{
		CMP EAX, MIN_WING_ITEMID
		JL NEXT_CHECK
		CMP EAX, MAX_WING_ITEMID
		JG NEXT_CHECK
		JMP[CustomWingFunction11_Offset02]

		NEXT_CHECK:
		CMP EAX, 0x1800
			JL NEXT_CHECK2
			CMP EAX, 0x1806
			JG NEXT_CHECK2
			JMP[CustomWingFunction11_Offset02]

			NEXT_CHECK2 :
			JMP[CustomWingFunction11_Offset01]
	}
}

void __declspec(naked) CustomWingFunction12()
{
	static DWORD CustomWingFunction12_Offset01 = 0x005A2389;//005B0310  |> 66:81F9 1E1A   CMP CX,1A1E
	static DWORD CustomWingFunction12_Offset02 = 0x005A2390;//005B0317  |> 83FE 07        CMP ESI,7

	_asm
	{
		CMP CX, MIN_WING_ITEMID
		JL NEXT_CHECK
		CMP CX, MAX_WING_ITEMID
		JLE ALLOW_CHECK

		NEXT_CHECK :
		CMP CX, 0x1800
			JL NEXT_CHECK1
			CMP CX, 0x1806
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[CustomWingFunction12_Offset01]

			ALLOW_CHECK :
			JMP[CustomWingFunction12_Offset02]
	}
}

void __declspec(naked) CustomWingFunction13()
{
	static DWORD CustomWingFunction13_Offset01 = 0x005A3970;//005B1A1A  |> 66:81F9 1F1A   CMP CX,1A1F
	static DWORD CustomWingFunction13_Offset02 = 0x005A394C;//005B19FD  |. 8B4D F0        MOV ECX,DWORD PTR SS:[EBP-10] ??? verificar



	_asm
	{
		CMP CX, MIN_WING_ITEMID
		JL NEXT_CHECK
		CMP CX, MAX_WING_ITEMID
		JG NEXT_CHECK
		JMP[CustomWingFunction13_Offset02]

		NEXT_CHECK:
		CMP CX, 0x1800
			JL NEXT_CHECK2
			CMP CX, 0x1806
			JG NEXT_CHECK2
			JMP[CustomWingFunction13_Offset02]

			NEXT_CHECK2 :
			JMP[CustomWingFunction13_Offset01]
	}
}

void __declspec(naked) CustomWingFunction14()
{
	static DWORD CustomWingFunction14_Offset01 = 0x005A6006;//função não bate 
	static DWORD CustomWingFunction14_Offset02 = 0x005A5FFF;//005B45C2  |> BA 01000000    MOV EDX,1

	_asm
	{
		CMP CX, MIN_WING_ITEMID
		JL NEXT_CHECK
		CMP CX, MAX_WING_ITEMID
		JG NEXT_CHECK
		JMP[CustomWingFunction14_Offset02]

		NEXT_CHECK:
		CMP CX, 0x1800
			JL NEXT_CHECK2
			CMP CX, 0x1806
			JG NEXT_CHECK2
			JMP[CustomWingFunction14_Offset02]

			NEXT_CHECK2 :
			JMP[CustomWingFunction14_Offset01]
	}
}

void __declspec(naked) CustomWingFunction15()
{
	static DWORD CustomWingFunction15_Offset01 = 0x005AB4B0;//005BA350  |> 66:3D 1E1A     CMP AX,1A1E
	static DWORD CustomWingFunction15_Offset02 = 0x005AB4D7;//005BA377  |> C645 0B 00     MOV BYTE PTR SS:[EBP+B],0

	_asm
	{
		CMP AX, MIN_WING_ITEMID
		JL NEXT_CHECK
		CMP AX, MAX_WING_ITEMID
		JLE ALLOW_CHECK

		NEXT_CHECK :
		CMP AX, 0x1800
			JL NEXT_CHECK1
			CMP AX, 0x1806
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[CustomWingFunction15_Offset01]

			ALLOW_CHECK :
			JMP[CustomWingFunction15_Offset02]
	}
}

void __declspec(naked) CustomWingFunction16()
{
	static DWORD CustomWingFunction16_Offset01 = 0x005B1849;//005C09BB  |> 66:3D 1E1A     CMP AX,1A1E
	static DWORD CustomWingFunction16_Offset02 = 0x005B184F;//005C09C1  |> BE 01000000    MOV ESI,1

	_asm
	{
		CMP AX, MIN_WING_ITEMID
		JL NEXT_CHECK
		CMP AX, MAX_WING_ITEMID
		JLE ALLOW_CHECK

		NEXT_CHECK :
		CMP AX, 0x1800
			JL NEXT_CHECK1
			CMP AX, 0x1806
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[CustomWingFunction16_Offset01]

			ALLOW_CHECK :
			JMP[CustomWingFunction16_Offset02]
	}
}

void __declspec(naked) CustomWingFunction17()
{
	static DWORD CustomWingFunction17_Offset01 = 0x005B188B;//005C09FD  |> 66:81F9 1E1A   CMP CX,1A1E
	static DWORD CustomWingFunction17_Offset02 = 0x005B2688;//005C17FF  |> A1 A4036707    MOV EAX,DWORD PTR DS:[76703A4]



	_asm
	{
		CMP CX, MIN_WING_ITEMID
		JL NEXT_CHECK
		CMP CX, MAX_WING_ITEMID
		JLE ALLOW_CHECK

		NEXT_CHECK :
		CMP CX, 0x1800
			JL NEXT_CHECK1
			CMP CX, 0x1806
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[CustomWingFunction17_Offset01]

			ALLOW_CHECK :
			JMP[CustomWingFunction17_Offset02]
	}
}

void __declspec(naked) CustomWingFunction18()
{
	static DWORD CustomWingFunction18_Offset01 = 0x005CD788;//005DC252  |> 66:81F9 041A   CMP CX,1A04
	static DWORD CustomWingFunction18_Offset02 = 0x005CDE0D;//005DC8D7  |> 68 98000000    PUSH 98                                  ; /Arg3 = 00000098

	_asm
	{
		CMP CX, MIN_WING_ITEMID
		JL NEXT_CHECK
		CMP CX, MAX_WING_ITEMID
		JLE ALLOW_CHECK

		NEXT_CHECK :
		CMP CX, 0x1800
			JL NEXT_CHECK1
			CMP CX, 0x1806
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[CustomWingFunction18_Offset01]

			ALLOW_CHECK :
			JMP[CustomWingFunction18_Offset02]
	}
}

void __declspec(naked) CustomWingFunction19()
{
	static DWORD CustomWingFunction19_Offset01 = 0x005CDE95;//005DC956  |> 66:3D 041A     CMP AX,1A04
	static DWORD CustomWingFunction19_Offset02 = 0x005CF0DE;//005DDBB5  |> 6A 02          PUSH 2                                   ; /Arg3 = 00000002



	_asm
	{
		CMP CX, MIN_WING_ITEMID
		JL NEXT_CHECK
		CMP CX, MAX_WING_ITEMID
		JLE ALLOW_CHECK

		NEXT_CHECK :
		CMP CX, 0x1800
			JL NEXT_CHECK1
			CMP CX, 0x1806
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[CustomWingFunction19_Offset01]

			ALLOW_CHECK :
			JMP[CustomWingFunction19_Offset02]
	}
}

void __declspec(naked) CustomWingFunction20()
{
	static DWORD CustomWingFunction20_Offset01 = 0x005EBB7D;//005FB502  |> 8D43 F7        LEA EAX,DWORD PTR DS:[EBX-9]
	static DWORD CustomWingFunction20_Offset02 = 0x005EBB77;//005FB4FC  |. 66:3D 1E1A     CMP AX,1A1E



	_asm
	{
		CMP AX, MIN_WING_ITEMID
		JL ALLOW_CHECK
		CMP AX, MAX_WING_ITEMID
		JLE ALLOW_CHECK

		NEXT_CHECK :
		CMP AX, 0x1800
			JL ALLOW_CHECK
			CMP AX, 0x1806
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[CustomWingFunction20_Offset02]

			ALLOW_CHECK :
			JMP[CustomWingFunction20_Offset01]
	}
}

void __declspec(naked) CustomWingFunction21()
{
	static DWORD CustomWingFunction21_Offset01 = 0x005EBE0A;//005FB8C6  |> 8B45 84        MOV EAX,DWORD PTR SS:[EBP-7C]
	static DWORD CustomWingFunction21_Offset02 = 0x005EBE02;//005FB8BE  |. FF45 88        INC DWORD PTR SS:[EBP-78]

	_asm
	{
		CMP AX, MIN_WING_ITEMID
		JL NEXT_CHECK
		CMP AX, MAX_WING_ITEMID
		JG NEXT_CHECK
		JMP[CustomWingFunction21_Offset02]

		NEXT_CHECK:
		CMP AX, 0x1800
			JL NEXT_CHECK2
			CMP AX, 0x1806
			JG NEXT_CHECK2
			JMP[CustomWingFunction21_Offset02]

			NEXT_CHECK2 :
			JMP[CustomWingFunction21_Offset01]
	}
}

void __declspec(naked) CustomWingFunction22()
{
	static DWORD CustomWingFunction22_ItemIndex;
	static DWORD CustomWingFunction22_Offset01 = 0x005F892C;//0060971A
	//---
	static DWORD CustomWingFunction22_Offset02 = 0x005F878E;//006095E0  |> 8D81 E2E5FFFF  LEA EAX,DWORD PTR DS:[ECX-1A1E]
	static DWORD CustomWingFunction22_Offset03 = 0x005F8748;//0060958C  |. 0F84 88010000  JE main.0060971A



	_asm
	{
		MOV CustomWingFunction22_ItemIndex, ECX
	}

	if (CustomWingFunction22_ItemIndex >= MIN_WING_ITEMID2 && CustomWingFunction22_ItemIndex <= MAX_WING_ITEMID2)
	{
		__asm { JMP[CustomWingFunction22_Offset01] }
	}
	else
	{
		_asm
		{
			CMP ECX, 0x1A0E
			JG Next_Check
			JMP[CustomWingFunction22_Offset03]
			Next_Check:
			JMP[CustomWingFunction22_Offset02]
		}
	}

}

void __declspec(naked) CustomWingFunction23()
{
	static DWORD CustomWingFunction23_Offset01 = 0x0005F9DE7;//0060AD50
	static DWORD CustomWingFunction23_Offset02 = 0x005F9E4A;//0060ADB3

	_asm
	{
		CMP CX, MIN_WING_ITEMID2
		JL NEXT_CHECK
		CMP CX, MAX_WING_ITEMID2
		JLE ALLOW_CHECK

		NEXT_CHECK :
		CMP CX, 0x1A03//1A12

			JL NEXT_CHECK1
			CMP CX, 0x1A09//1A18
			JLE ALLOW_CHECK

			NEXT_CHECK1 :
		JMP[CustomWingFunction23_Offset01]

			ALLOW_CHECK :
			JMP[CustomWingFunction23_Offset02]
	}
}

void ReadyNewWings()
{
	SetCompleteHook(0xFF, 0x00540934, &ItemSetOptions);//005492D9  |. E8 12010000    ||CALL main.005493F0
	SetCompleteHook(0xFF, 0x005AB0AB, &ItemSetOptions);//005B9F33  |. E8 B8F4F8FF    ||CALL main.005493F0                     ; \main.005493F0
	SetCompleteHook(0xFF, 0x005AB6EA, &ItemSetOptions);//005BA58A  |. E8 61EEF8FF    CALL main.005493F0
	SetCompleteHook(0xFF, 0x005ABA7B, &ItemSetOptions);//005BA9EF  |. E8 FCE9F8FF    ||CALL main.005493F0                     ; \main.005493F0
	SetCompleteHook(0xFF, 0x005ABE11, &ItemSetOptions);//005BAD6F  |. E8 7CE6F8FF    ||CALL main.005493F0                     ; \main.005493F0
	SetCompleteHook(0xFF, 0x005AC110, &ItemSetOptions);//005BB0D7  |. E8 14E3F8FF    ||CALL main.005493F0                     ; \main.005493F0



	SetOp((LPVOID)0x005A5310, (LPVOID)CustomWingFunction01, 0xE9);//005B386F  |> 66:81F9 0318   CMP CX,1803
	SetOp((LPVOID)0x005F9DDB, (LPVOID)CustomWingFunction06, 0xE9);//0060AD44  |. 66:3D 121A     CMP AX,1A12
	SetOp((LPVOID)0x005A237B, (LPVOID)CustomWingFunction12, 0xE9);//005B0302  |. 66:81F9 0318   CMP CX,1803
	SetOp((LPVOID)0x005A393E, (LPVOID)CustomWingFunction13, 0xE9);//005B19E6  |> 66:81F9 0318   CMP CX,1803
	SetOp((LPVOID)0x005A5FF1, (LPVOID)CustomWingFunction14, 0xE9);//005B45B4  |. 66:81F9 0018   CMP CX,1800
	SetOp((LPVOID)0x005A7702, (LPVOID)CustomWingFunction02, 0xE9);//005B5DB7  |. 66:3D 0318     CMP AX,1803
	SetOp((LPVOID)0x005A7D70, (LPVOID)CustomWingFunction03, 0xE9);//005B6425  |> 66:81F9 0318   CMP CX,1803
	SetOp((LPVOID)0x005EBDF6, (LPVOID)CustomWingFunction04, 0xE9);//005FB8B2  |. 66:3D 0318     CMP AX,1803
	SetOp((LPVOID)0x005AA33B, (LPVOID)CustomWingFunction05, 0xE9);//005B917F  |. 66:3D 151A     CMP AX,1A15
	SetOp((LPVOID)0x005414B2, (LPVOID)CustomWingFunction07, 0xE9);//00549E71  |. 66:3D 0018     CMP AX,1800 
	SetOp((LPVOID)0x00542D8F, (LPVOID)CustomWingFunction08, 0xE9);//0054B847  |. 66:3D 0018     CMP AX,1800
	SetOp((LPVOID)0x0058A065, (LPVOID)CustomWingFunction09, 0xE9);//00597865  |. 66:81F9 0018   |CMP CX,1800
	SetOp((LPVOID)0x005A137A, (LPVOID)CustomWingFunction10, 0xE9);//005AF16A  |. 66:81FA 0318   CMP DX,1803
	SetOp((LPVOID)0x005A1910, (LPVOID)CustomWingFunction11, 0xE9);//005AF862  |> 3D 03180000    CMP EAX,1803
	//---
	SetOp((LPVOID)0x005AB4A4, (LPVOID)CustomWingFunction15, 0xE9);//005BA344  |. 66:3D 0018     CMP AX,1800
	SetOp((LPVOID)0x005B183D, (LPVOID)CustomWingFunction16, 0xE9);//005C09AF  |. 66:3D 0018     CMP AX,1800
	//---
	SetOp((LPVOID)0x005B1879, (LPVOID)CustomWingFunction17, 0xE9);//005C09EB  |. 66:81F9 0018   CMP CX,1800
	SetOp((LPVOID)0x005CD776, (LPVOID)CustomWingFunction18, 0xE9);//005DC240  |. 66:81F9 0018   CMP CX,1800
	SetOp((LPVOID)0x005CDE83, (LPVOID)CustomWingFunction19, 0xE9);//005DC946  |. 66:3D 0018     CMP AX,1800
	//---
	SetOp((LPVOID)0x005EBB6B, (LPVOID)CustomWingFunction20, 0xE9);//005FB4F0  |. 66:3D 0018     CMP AX,1800
	SetOp((LPVOID)0x005EBDF6, (LPVOID)CustomWingFunction21, 0xE9);//005FB8B2  |. 66:3D 0318     CMP AX,1803
	//---
	SetOp((LPVOID)0x005F8740, (LPVOID)CustomWingFunction22, 0xE9);//00609584  |. 81F9 1D1A0000  CMP ECX,1A1D
	SetByte((LPVOID)0x005F872E, 0x40);//0060956E  |. 81F9 311A0000  CMP ECX,1A31
	SetByte((LPVOID)0x005F8736, 0x3F);//0060957A     301B           XOR BYTE PTR DS:[EBX],BL
}*/
