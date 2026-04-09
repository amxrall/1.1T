#include "StdAfx.h"

CPetsManager gPetsManager;

CPetsManager::CPetsManager()
{
	this->PetTickCount = 0;
}

#define PreviewCharSet						((void(*)(int a1, LPBYTE a2, int a3, int a4, int a5, int a6, BYTE * a7)) 0x0050A590)
#define oPreviewStructInit					*(int*)0x7424644
#define oPreviewStruct						*(int*)0x742464C

#define oRenderObjectPetPreview_Call01		0x00445908
#define oRenderObjectPetPreview_Call02		0x004BFE5C
#define oRenderObjectPetPreview_Call03		0x004BFFF9
#define oRenderObjectPetPreview_Call04		0x004CA345
#define oRenderObjectPetPreview_Call05		0x004CB023
#define oRenderObjectPetPreview_Call06		0x004CB050
#define oRenderObjectPetPreview_Call07		0x004CB07A
#define oRenderObjectPetPreview_Call08		0x004CB0A4
#define oRenderObjectPetPreview_Call09		0x004CB155
#define oRenderObjectPetPreview_Call10		0x004CBCE2
#define oRenderObjectPetPreview_Call11		0x004CEA7B
#define oRenderObjectPetPreview_Call12		0x004D3630
#define oRenderObjectPetPreview_Call13		0x004D4D31
#define oRenderObjectPetPreview_Call14		0x004D4F45
#define oRenderObjectPetPreview_Call15		0x004D505E
#define oRenderObjectPetPreview_Call16		0x004D510A
#define oRenderObjectPetPreview_Call17		0x004DBE77
#define oRenderObjectPetPreview_Call18		0x004DC962
#define oRenderObjectPetPreview_Call19		0x004DCACE

#define pRenderObjectPetPreview				((void(__cdecl*)(short *a1,int a2,int a3,int a4,OBJMODEL *Inventory,char *a6))0x005AB5B0)
#define pCreateObjectPetGuardianType		((bool(__cdecl*)(int ResourceID,vec3_t ObjectPos,vec3_t RelativePos,int Arg4,int Arg5))0x0043EFF0)
#define pCreateObjectPetMauntType			((void(__cdecl*)(int ResourceID,vec3_t ObjectPos,vec3_t WorldPos,BYTE Maunt,int Arg5))0x0043EDD0)
#define pCreateObjectPetMovement			((bool(__cdecl*)(int pObjModel,float Velocity))0x0043F060)		// HERE: pObjModel = LPOBJMODEL but struct must be tested and re-compiled, modified members etc T_T only: int pObject Pointer and link struct later :)
#define pCreateObjectPetEffect				((bool(__cdecl*)(LPOBJMODEL lpObjModel,char Switch))0x0043FE50)
#define pCreateObjectPetRefresh				((int(__cdecl*)(int Inventory))0x004C1FA0)
#define pResetObjectPetPreview				((PLONG(__cdecl*)(vec3_t WorldPos))0x0043EDA0)

#define Joint(x)	((0x30 * x) + oBoneTransformPointer)
#define Object(x)	*(WORD*)(x+2)

enum eCustomPetType
{
	eGuardian = 0,
	eMaunt = 1,
};

Objsub_43EDA0		sub_43EDA0 = (Objsub_43EDA0)0x43EDA0;
Objsub_43EDD0		sub_43EDD0 = (Objsub_43EDD0)0x43EDD0;
Objsub_43EFF0		sub_43EFF0 = (Objsub_43EFF0)0x43EFF0;
Objsub_4038D0		sub_4038D0 = (Objsub_4038D0)0x4038D0;
Objsub_5094D0		sub_5094D0 = (Objsub_5094D0)0x5094D0;
Objsub_507C70		sub_507C70 = (Objsub_507C70)0x507C70;
Objsub_53FEC0		sub_53FEC0 = (Objsub_53FEC0)0x53FEC0;

DWORD CPetsManager::CreatePet(DWORD dwModel, BOOL bType)
{
	int ObjectStruct;
	ObjectStruct = *(DWORD*)0x7424644 + 1060 * bType;
	// ----
	if (bType == eCustomPetType::eGuardian)
	{
		sub_43EFF0(dwModel, (DWORD)&ObjectStruct + 16, (DWORD)&ObjectStruct, NULL);
	}
	else if (bType == eCustomPetType::eMaunt)
	{
		sub_43EDD0(dwModel, (DWORD)&ObjectStruct + 16, (DWORD)&ObjectStruct, (int)&bType + 3, NULL);
	}
	// ----
	return 0;
}

#pragma optimize("t",on)
void CPetsManager::RefreshPetASM()
{
	static DWORD dwRefreshPet_Pointer;
	// ----
	static DWORD dwRefreshPet_Buffer = 0x4C2351;
	static DWORD dwRefreshPet_Jump = 0x4C23A7;
	// ----
	_asm
	{
		LEA ECX, [EAX + 0x203]
		MOV dwRefreshPet_Pointer, ECX
	}
	// ----
	if (dwRefreshPet_Pointer >= ITEM_ID(13, 100)
		&& dwRefreshPet_Pointer <= ITEM_ID(13, 150))
	{
		_asm
		{
			PUSH ECX
			PUSH ECX
			LEA EDX, [ESI + 0x10]
			PUSH ESI
			PUSH EDX
			MOV dwRefreshPet_Pointer, EAX
			PUSH EAX
			JMP dwRefreshPet_Jump
		}
	}
	else
	{
		_asm
		{
			JMP dwRefreshPet_Buffer
		}
	}
}
#pragma optimize("t",off)

void CPetsManager::RenderPet(short *a1, int a2, int a3, int a4, OBJMODEL *Inventory, char *a6)
{
	gPetsManager.CreateMuun(Inventory->dwObjectID);
	// ----
	pRenderObjectPetPreview(a1, a2, a3, a4, Inventory, a6);
}

void CPetsManager::Call()
{
	//SetRange((LPVOID)0x004C234B, 6, ASM::NOP);
	//SetJmp((LPVOID)0x004C234B, this->RefreshPetASM);
	// ----
	SetOp((LPVOID)oRenderObjectPetPreview_Call01, this->RenderPet, ASM::CALL);
	SetOp((LPVOID)oRenderObjectPetPreview_Call02, this->RenderPet, ASM::CALL);
	SetOp((LPVOID)oRenderObjectPetPreview_Call03, this->RenderPet, ASM::CALL);
	SetOp((LPVOID)oRenderObjectPetPreview_Call04, this->RenderPet, ASM::CALL);
	SetOp((LPVOID)oRenderObjectPetPreview_Call05, this->RenderPet, ASM::CALL);
	SetOp((LPVOID)oRenderObjectPetPreview_Call06, this->RenderPet, ASM::CALL);
	SetOp((LPVOID)oRenderObjectPetPreview_Call07, this->RenderPet, ASM::CALL);
	SetOp((LPVOID)oRenderObjectPetPreview_Call08, this->RenderPet, ASM::CALL);
	SetOp((LPVOID)oRenderObjectPetPreview_Call09, this->RenderPet, ASM::CALL);
	SetOp((LPVOID)oRenderObjectPetPreview_Call10, this->RenderPet, ASM::CALL);
	SetOp((LPVOID)oRenderObjectPetPreview_Call11, this->RenderPet, ASM::CALL);
	SetOp((LPVOID)oRenderObjectPetPreview_Call12, this->RenderPet, ASM::CALL);
	SetOp((LPVOID)oRenderObjectPetPreview_Call13, this->RenderPet, ASM::CALL);
	SetOp((LPVOID)oRenderObjectPetPreview_Call14, this->RenderPet, ASM::CALL);
	SetOp((LPVOID)oRenderObjectPetPreview_Call15, this->RenderPet, ASM::CALL);
	SetOp((LPVOID)oRenderObjectPetPreview_Call16, this->RenderPet, ASM::CALL);
	SetOp((LPVOID)oRenderObjectPetPreview_Call17, this->RenderPet, ASM::CALL);
	SetOp((LPVOID)oRenderObjectPetPreview_Call18, this->RenderPet, ASM::CALL);
	SetOp((LPVOID)oRenderObjectPetPreview_Call19, this->RenderPet, ASM::CALL);
	// ----
	SetOp((LPVOID)0x00491F31, this->PreviewCharSetHook, ASM::CALL);
	SetOp((LPVOID)0x004BC6D7, this->PreviewCharSetHook, ASM::CALL);
	SetOp((LPVOID)0x004C1F87, this->PreviewCharSetHook, ASM::CALL);
	SetOp((LPVOID)0x004C2D98, this->PreviewCharSetHook, ASM::CALL);
	SetOp((LPVOID)0x004DA13F, this->PreviewCharSetHook, ASM::CALL);
	SetOp((LPVOID)0x004DBE44, this->PreviewCharSetHook, ASM::CALL);
}

#define sub_41F180						((void(*)(DWORD a1)) 0x0041F180)
#define ReturnPetSlot					((LPVOID(__cdecl*)(int a1)) 0x0043EDA0)
#define gCheckPetStatus					((int(*)(DWORD a1)) 0x004127C0)

#define oUserPreviewStruct  *(DWORD*)0x7424644

#define CS_GET_WEAPON(x, y)		( y | (16 * (x & 0xF0)) )
#define CS_EMPTY_WEAPON			4095 // ITEM(7, 511)
#define ITEM_INTER				515
#define CS_EMPTY_ITEM			511
#define	CS_SET_1(x)				( x >> 2)
#define CS_GET_HELM(x, y, z)	( (32 * (z & 0xF)) + 16 * ((x >> 7) & 1) + (y >> 4) )
#define CS_GET_ARMOR(x, y, z)	( (32 * ((z >> 4) & 0xF)) + 16 * ((x >> 6) & 1) + (y & 0xF) )
#define CS_GET_PANTS(x, y, z)	( (32 * (z & 0xF)) + 16 * ((x >> 5) & 1) + (y >> 4) )
#define CS_GET_GLOVES(x, y, z)	( (32 * ((z >> 4) & 0xF)) + 16 * ((x >> 4) & 1) + (y & 0xF) )
#define CS_GET_BOOTS(x, y, z)	( (32 * (z & 0xF)) + 16 * ((x >> 3) & 1) + (y >> 4) )

BYTE gLevelSmallConvert(int SmallValue)
{
	BYTE ResultValue;
	// ----
	switch (SmallValue)
	{
	case 0:
		ResultValue = 0;
		break;
	case 1:
		ResultValue = 3;
		break;
	case 2:
		ResultValue = 5;
		break;
	case 3:
		ResultValue = 7;
		break;
	case 4:
		ResultValue = 9;
		break;
	case 5:
		ResultValue = 11;
		break;
	case 6:
		ResultValue = 13;
		break;
	case 7:
		ResultValue = 15;
		break;
	default:
		ResultValue = 0;
		break;
	}
	// ----
	return ResultValue;
}

int CPetsManager::PreviewCharSetHook(int a1, BYTE * CharSet, int a3, int a4, BYTE a5, int a6, BYTE * Mode)
{
	int ObjectStruct;

	ObjectStruct = *(DWORD*)0x7424644 + 1060 * a1;

	if (*(WORD*)(ObjectStruct + 2) == 507)
	{
		short WeaponFirstType = CS_GET_WEAPON(CharSet[11], CharSet[0]);
		if (WeaponFirstType == CS_EMPTY_WEAPON)
		{
			*(BYTE*)(ObjectStruct + 683) = 0;
			*(WORD*)(ObjectStruct + 680) = -1;
			*(BYTE*)(ObjectStruct + 684) = 0;
		}
		else
		{
			*(WORD*)(ObjectStruct + 680) = WeaponFirstType + ITEM_INTER;
		}

		short WeaponSecondType = CS_GET_WEAPON(CharSet[12], CharSet[1]);
		if (WeaponSecondType == CS_EMPTY_WEAPON)
		{
			*(WORD*)(ObjectStruct + 712) = -1;
			*(BYTE*)(ObjectStruct + 715) = 0;
			*(BYTE*)(ObjectStruct + 716) = 0;
		}
		else if ((*(BYTE*)(ObjectStruct + 452) & 7) != 4 || (WORD)WeaponSecondType != 2565)
		{
			*(WORD*)(ObjectStruct + 712) = WeaponSecondType + ITEM_INTER;
		}
		else
		{
			*(WORD*)(ObjectStruct + 712) = 7176;
			sub_41F180(ObjectStruct);
		}

		if ((CS_SET_1(CharSet[4]) & 3) == 3)
		{
			BYTE SecondWingsType = CharSet[8] & 7;
			if (SecondWingsType)
			{
				switch (SecondWingsType)
				{
				case 5: // Cape Of Lord
					*(WORD*)(ObjectStruct + 744) = ITEM_ID(13, 30);
					break;
				default: // Other Wings
					*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 2) + SecondWingsType;
					break;
				}
			}
			else
			{
				*(WORD *)(ObjectStruct + 744) = -1;
				*(BYTE *)(ObjectStruct + 747) = 0;
				*(BYTE *)(ObjectStruct + 748) = 0;
			}
		}
		else
		{
			*(WORD *)(ObjectStruct + 744) = ITEM_ID(12, 0) + (CS_SET_1(CharSet[4]) & 3);
		}
		// ----
		BYTE CustomWings = CharSet[16] >> 2;
		// ----
		if (CustomWings > 0)
		{
			switch (CustomWings)
			{
			case 1:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 100);
				break;
			}
			case 2:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 101);
				break;
			}
			case 3:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 102);
				break;
			}
			case 4:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 103);
				break;
			}
			case 5:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 104);
				break;
			}
			case 6:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 105);
				break;
			}
			case 7:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 106);
				break;
			}
			case 8:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 107);
				break;
			}
			case 9:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 108);
				break;
			}
			case 10:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 109);
				break;
			}
			case 11:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 110);
				break;
			}
			case 12:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 111);
				break;
			}
			case 13:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 112);
				break;
			}
			case 14:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 113);
				break;
			}
			case 15:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 114);
				break;
			}
			case 16:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 115);
				break;
			}
			case 17:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 116);
				break;
			}
			case 18:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 117);
				break;
			}
			case 19:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 118);
				break;
			}
			case 20:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 119);
				break;
			}
			case 21:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 120);
				break;
			}
			case 22:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 121);
				break;
			}
			case 23:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 122);
				break;
			}
			case 24:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 123);
				break;
			}
			case 25:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 124);
				break;
			}
			case 26:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 125);
				break;
			}
			case 27:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 126);
				break;
			}
			case 28:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 127);
				break;
			}
			case 29:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 128);
				break;
			}
			case 30:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 129);
				break;
			}
			case 31:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 130);
				break;
			}
			case 32:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 131);
				break;
			}
			case 33:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 132);
				break;
			}
			case 34:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 133);
				break;
			}
			case 35:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 134);
				break;
			}
			case 36:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 135);
				break;
			}
			case 37:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 136);
				break;
			}
			case 38:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 137);
				break;
			}
			case 39:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 138);
				break;
			}
			case 40:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 139);
				break;
			}
			case 41:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 140);
				break;
			}
			case 42:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 141);
				break;
			}
			case 43:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 142);
				break;
			}
			case 44:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 143);
				break;
			}
			case 45:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 144);
				break;
			}
			case 46:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 145);
				break;
			}
			case 47:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 146);
				break;
			}
			case 48:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 147);
				break;
			}
			case 49:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 148);
				break;
			}
			case 50:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 149);
				break;
			}
			case 51:
			{
				*(WORD*)(ObjectStruct + 744) = ITEM_ID(12, 150);
				break;
			}
			}
		}
		// ----
		if (Mode)
		{
			Mode = 0;
		}
		else
		{
			ReturnPetSlot(ObjectStruct);
		}
		// ----
		BYTE NormalPetType = CharSet[4] & 3;
		// ----
		if (NormalPetType == 3)
		{
			if ((CharSet[9] & 1) == 1)
			{
				*(WORD*)(ObjectStruct + 776) = ITEM_ID(13, 3);
				// ----
				if (Mode)
				{
					sub_43EDD0(270, ObjectStruct + 16, ObjectStruct, (int)Mode, 0);
				}
				else
				{
					sub_43EFF0(270, ObjectStruct + 16, ObjectStruct, 0);
				}
			}
			else
			{
				*(WORD*)(ObjectStruct + 776) = -1;
				*(BYTE*)(ObjectStruct + 779) = 0;
				*(BYTE*)(ObjectStruct + 780) = 0;
			}
		}
		else
		{
			*(WORD*)(ObjectStruct + 776) = ITEM_ID(13, 0) + NormalPetType;
			int MauntCode = NULL;
			bool Check = true;
			// ----
			if (NormalPetType)
			{
				if (NormalPetType == 2)
				{
					MauntCode = 198;
				}
				else
				{
					if (NormalPetType == 3)
					{
						MauntCode = 270;
					}
					else
					{
						Check = false;
					}
				}
			}
			else
			{
				MauntCode = ITEM_ID(13, 0);
			}
			// ----
			if (Check == true)
			{
				if (Mode)
				{
					sub_43EDD0(MauntCode, ObjectStruct + 16, ObjectStruct, (int)Mode, 0);
				}
				else
				{
					ReturnPetSlot(ObjectStruct);
					sub_43EFF0(MauntCode, ObjectStruct + 16, ObjectStruct, 0);
				}
			}
		}
		// ----
		if ((CharSet[11] & 1) == 1)
		{
			*(WORD*)(ObjectStruct + 776) = ITEM_ID(13, 4);
			// ----
			if (Mode)
			{
				sub_43EDD0(191, ObjectStruct + 16, ObjectStruct, (int)Mode, 0);
			}
			else
			{
				sub_43EFF0(191, ObjectStruct + 16, ObjectStruct, 0);
			}
		}
		// ----
		BYTE NewsPet = CharSet[15] >> 1;
		// ----
		if (NewsPet > 0)
		{
			short ShopPetType = NULL;
			// ----
			switch (NewsPet)
			{
			case 1:
				ShopPetType = 100;
				break;
			case 2:
				ShopPetType = 101;
				break;
			case 3:
				ShopPetType = 102;
				break;
			case 4:
				ShopPetType = 103;
				break;
			case 5:
				ShopPetType = 104;
				break;
			case 6:
				ShopPetType = 105;
				break;
			case 7:
				ShopPetType = 106;
				break;
			case 8:
				ShopPetType = 107;
				break;
			case 9:
				ShopPetType = 108;
				break;
			case 10:
				ShopPetType = 109;
				break;
			case 11:
				ShopPetType = 110;
				break;
			case 12:
				ShopPetType = 111;
				break;
			case 13:
				ShopPetType = 112;
				break;
			case 14:
				ShopPetType = 113;
				break;
			case 15:
				ShopPetType = 114;
				break;
			case 16:
				ShopPetType = 115;
				break;
			case 17:
				ShopPetType = 116;
				break;
			case 18:
				ShopPetType = 117;
				break;
			case 19:
				ShopPetType = 118;
				break;
			case 20:
				ShopPetType = 119;
				break;
			case 21:
				ShopPetType = 120;
				break;
			case 22:
				ShopPetType = 121;
				break;
			case 23:
				ShopPetType = 122;
				break;
			case 24:
				ShopPetType = 123;
				break;
			case 25:
				ShopPetType = 124;
				break;
			case 26:
				ShopPetType = 125;
				break;
			case 27:
				ShopPetType = 126;
				break;
			case 28:
				ShopPetType = 127;
				break;
			case 29:
				ShopPetType = 128;
				break;
			case 30:
				ShopPetType = 129;
				break;
			case 31:
				ShopPetType = 130;
				break;
			case 32:
				ShopPetType = 131;
				break;
			case 33:
				ShopPetType = 132;
				break;
			case 34:
				ShopPetType = 133;
				break;
			case 35:
				ShopPetType = 134;
				break;
			case 36:
				ShopPetType = 135;
				break;
			case 37:
				ShopPetType = 136;
				break;
			case 38:
				ShopPetType = 137;
				break;
			case 39:
				ShopPetType = 138;
				break;
			case 40:
				ShopPetType = 139;
				break;
			case 41:
				ShopPetType = 140;
				break;
			case 42:
				ShopPetType = 141;
				break;
			case 43:
				ShopPetType = 142;
				break;
			case 44:
				ShopPetType = 143;
				break;
			case 45:
				ShopPetType = 144;
				break;
			case 46:
				ShopPetType = 145;
				break;
			case 47:
				ShopPetType = 146;
				break;
			case 48:
				ShopPetType = 147;
				break;
			case 49:
				ShopPetType = 148;
				break;
			case 50:
				ShopPetType = 149;
				break;
			case 51:
				ShopPetType = 150;
				break;
			}
			// ----
			ReturnPetSlot(ObjectStruct);
			// ----
			*(WORD*)(ObjectStruct + 776) = ITEM_ID(13, 0) + ShopPetType;
			// ----
			if (!Mode)
			{
				sub_43EFF0(ITEM_ID(13, 0) + ShopPetType, ObjectStruct + 16, ObjectStruct, 0);
			}
		}
		// ----
		gCheckPetStatus(ObjectStruct);
		// ----
		if ((CharSet[11] & 2) == 2)
		{
			if (!*(BYTE*)(ObjectStruct + 848) || *(BYTE*)(ObjectStruct + 848) > 3)
			{
				*(BYTE *)(ObjectStruct + 848) = 4;
			}
		}
		else if (!*(BYTE*)(ObjectStruct + 848) || *(BYTE*)(ObjectStruct + 848) > 3)
		{
			*(BYTE*)(ObjectStruct + 848) = 0;
		}

		int TempBuff = CharSet[7] + ((CharSet[6] + (CharSet[5] << 8)) << 8);
		*(BYTE*)(ObjectStruct + 682) = gLevelSmallConvert(CharSet[7] & 7);
		*(BYTE*)(ObjectStruct + 714) = gLevelSmallConvert((TempBuff >> 3) & 7);
		*(BYTE *)(ObjectStruct + 746) = 0;
		*(BYTE *)(ObjectStruct + 778) = 0;
		if (!*(BYTE*)(ObjectStruct + 979))
		{
			short HelmType = CS_GET_HELM(CharSet[8], CharSet[2], CharSet[12]);
			if (HelmType == CS_EMPTY_ITEM)
			{
				int Primeiro = (*(BYTE *)(ObjectStruct + 452) >> 3);
				int Segundo = *(BYTE *)(ObjectStruct + 452) & 7;
				int Terceiro = 5 * Primeiro;
				int Quarto = 5 * Primeiro + Segundo + 8707;
				*(WORD*)(ObjectStruct + 520) = Quarto;
			}
			else
			{
				*(WORD*)(ObjectStruct + 520) = ITEM_ID(7, 0) + HelmType;
			}
			// ----
			short ArmorType = CS_GET_ARMOR(CharSet[8], CharSet[2], CharSet[13]);
			// ----
			if (ArmorType == CS_EMPTY_ITEM)
			{
				int AmorPrimeiro = (*(BYTE *)(ObjectStruct + 452) >> 3) + 1743;
				int ArmorSegundo = *(BYTE *)(ObjectStruct + 452) & 7;
				int ArmorTerceiro = ArmorSegundo + 5 * AmorPrimeiro;
				*(WORD*)(ObjectStruct + 552) = ArmorTerceiro;
			}
			else
			{
				*(WORD*)(ObjectStruct + 552) = ITEM_ID(8, 0) + ArmorType;
			}
			// ----
			short PantsType = CS_GET_PANTS(CharSet[8], CharSet[3], CharSet[13]);
			// ----
			if (PantsType == CS_EMPTY_ITEM)
			{
				int PantsPrimeiro = *(BYTE *)(ObjectStruct + 452);
				int PantsSegundo = PantsPrimeiro >> 3;
				int PantsTerceiro = PantsPrimeiro & 7;
				PantsSegundo *= 5;
				int PantsQuarto = PantsSegundo + PantsTerceiro + 8723;

				*(WORD *)(ObjectStruct + 584) = PantsQuarto;
			}
			else
			{
				*(WORD *)(ObjectStruct + 584) = ITEM_ID(9, 0) + PantsType;
			}
			// ----
			short GlovesType = CS_GET_GLOVES(CharSet[8], CharSet[3], CharSet[14]);
			// ----
			if (GlovesType == CS_EMPTY_ITEM)
			{
				int GlovesPrimeiro = *(BYTE *)(ObjectStruct + 452);
				int GlovesSegundo = GlovesPrimeiro >> 3;
				int GlovesTerceiro = GlovesPrimeiro & 7;
				GlovesSegundo *= 5;
				int GlovesQuarto = GlovesSegundo + GlovesTerceiro + 8731;

				*(WORD *)(ObjectStruct + 616) = GlovesQuarto;
			}
			else
			{
				*(WORD *)(ObjectStruct + 616) = ITEM_ID(10, 0) + GlovesType;
			}
			// ----
			short BootsType = CS_GET_BOOTS(CharSet[8], CharSet[4], CharSet[14]);
			// ----
			if (BootsType == CS_EMPTY_ITEM)
			{
				int BootsPrimeiro = *(BYTE *)(ObjectStruct + 452);
				int BootsSegundo = BootsPrimeiro >> 3;
				int BootsTerceiro = BootsPrimeiro & 7;
				int BootsQuarto = 5 * BootsSegundo + BootsTerceiro + 8739;

				*(WORD *)(ObjectStruct + 648) = BootsQuarto;
			}
			else
			{
				*(WORD *)(ObjectStruct + 648) = ITEM_ID(11, 0) + BootsType;
			}

			*(BYTE*)(ObjectStruct + 522) = gLevelSmallConvert((TempBuff >> 6) & 7);
			*(BYTE*)(ObjectStruct + 554) = gLevelSmallConvert((TempBuff >> 9) & 7);
			*(BYTE*)(ObjectStruct + 586) = gLevelSmallConvert((TempBuff >> 12) & 7);
			*(BYTE*)(ObjectStruct + 618) = gLevelSmallConvert((TempBuff >> 15) & 7);
			*(BYTE*)(ObjectStruct + 650) = gLevelSmallConvert((TempBuff >> 18) & 7);

			*(BYTE *)(ObjectStruct + 523) = CharSet[9] >> 7;
			*(BYTE *)(ObjectStruct + 555) = (CharSet[9] >> 6) & 1;
			*(BYTE *)(ObjectStruct + 587) = (CharSet[9] >> 5) & 1;
			*(BYTE *)(ObjectStruct + 619) = (CharSet[9] >> 4) & 1;
			*(BYTE *)(ObjectStruct + 651) = (CharSet[9] >> 3) & 1;
			*(BYTE *)(ObjectStruct + 524) = CharSet[10] >> 7;
			*(BYTE *)(ObjectStruct + 556) = (CharSet[10] >> 6) & 1;
			*(BYTE *)(ObjectStruct + 588) = (CharSet[10] >> 5) & 1;
			*(BYTE *)(ObjectStruct + 620) = (CharSet[10] >> 4) & 1;
			*(BYTE *)(ObjectStruct + 652) = (CharSet[10] >> 3) & 1;
			*(BYTE *)(ObjectStruct + 683) = (CharSet[9] >> 2) & 1;
			*(BYTE *)(ObjectStruct + 715) = (CharSet[9] >> 1) & 1;
			*(BYTE *)(ObjectStruct + 684) = (CharSet[10] >> 2) & 1;
			*(BYTE *)(ObjectStruct + 716) = (CharSet[10] >> 1) & 1;
			*(BYTE *)(ObjectStruct + 840) = CharSet[10] & 1;

			sub_4038D0(ObjectStruct);
			sub_5094D0(ObjectStruct);
		}
	}

	return ObjectStruct;
}

DWORD PetPreview_Pointer;
DWORD PetPreview_Hook;

#pragma optimize("t",on)
__declspec(naked) void PetPreview()
{
	static DWORD dwCreateBug = 0x0043EFF0;
	// ----
	_asm
	{
		MOV EAX, DWORD PTR SS : [EBP + 0x18]
		MOV PetPreview_Pointer, EAX;
	}
	if (PetPreview_Pointer == ITEMGET(13, 0))
	{
		_asm
		{
			MOV PetPreview_Hook, 0x005AB73B
			JMP PetPreview_Hook
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 2))
	{
		_asm
		{
			MOV PetPreview_Hook, 0x005AB7A9;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 3))
	{
		_asm
		{
			MOV PetPreview_Hook, 0x005AB7E9;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 4))
	{
		_asm
		{
			MOV PetPreview_Hook, 0x005AB828;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 100))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 100);

			CALL dwCreateBug

				ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 101))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 101);

			CALL dwCreateBug

				ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 102))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 102);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 103))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 103);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 104))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 104);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 105))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 105);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 106))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 106);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 107))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 107);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 108))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 108);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 109))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 109);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 110))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 110);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 111))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 111);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 112))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 112);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 113))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 113);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 114))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 114);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 115))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 115);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 116))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 116);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 117))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 117);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 118))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 118);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 119))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 119);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 120))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 120);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 121))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 121);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 122))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 122);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 123))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 123);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 124))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 124);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 125))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 125);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 126))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 126);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 127))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 127);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 128))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 128);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 129))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 129);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 130))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 130);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 131))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 131);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 132))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 132);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 133))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 133);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 134))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 134);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 135))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 135);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 136))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 136);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 137))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 137);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 138))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 138);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 139))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 139);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 140))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 140);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 141))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 141);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 142))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 142);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 143))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 143);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 144))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 144);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 145))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 145);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 146))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 146);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 147))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 147);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 148))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 148);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 149))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 149);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else if (PetPreview_Pointer == ITEMGET(13, 150))
	{
		_asm
		{
			PUSH 0;
			PUSH 0;
			PUSH ESI;
			ADD ESI, 0x10;
			PUSH ESI;
			PUSH ITEM_ID(13, 150);

			CALL dwCreateBug;


			ADD ESP, 0x14;

			MOV PetPreview_Hook, 0x005AB751;
			JMP PetPreview_Hook;
		}
	}
	else
	{
		_asm
		{
			MOV PetPreview_Hook, 0x005AB8D8
			JMP PetPreview_Hook
		}
	}
}
#pragma optimize("t",off)

DWORD PetPreview2_Pointer;
DWORD PetPreview2_Hook;

#pragma optimize("t",on)
__declspec(naked) void PetPreview2()
{
	static DWORD dwCreateBug = 0x0043EFF0;
	// ----
	_asm
	{
		MOVSX EAX, WORD PTR DS : [0x785ACC8];
		MOV PetPreview2_Pointer, EAX;
	}
	if (PetPreview2_Pointer == ITEMGET(13, 0))
	{
		_asm
		{
			MOV PetPreview2_Hook, 0x005AD20C;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 2))
	{
		_asm
		{
			MOV PetPreview2_Hook, 0x005AD229;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 3))
	{
		_asm
		{
			MOV PetPreview2_Hook, 0x005AD246;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 4))
	{
		_asm
		{
			MOV PetPreview2_Hook, 0x005AD263;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 100))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 100);

			CALL dwCreateBug;

			ADD ESP, 0x14;

			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 101))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 101);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 102))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 102);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 103))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 103);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 104))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 104);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 105))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 105);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 106))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 106);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 107))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 107);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 108))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 108);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 109))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 109);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 110))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 110);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 111))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 111);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 112))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 112);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 113))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 113);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 114))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 114);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 115))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 115);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 116))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 116);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 117))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 117);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 118))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 118);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 119))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 119);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 120))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 120);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 121))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 121);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 122))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 122);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 123))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 123);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 124))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 124);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 125))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 125);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 126))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 126);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 127))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 127);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 128))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 128);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 129))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 129);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 130))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 130);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 131))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 131);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 132))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 132);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 133))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 133);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 134))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 134);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 135))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 135);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 136))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 136);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 137))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 137);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 138))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 138);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 139))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 139);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 140))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 140);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 141))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 141);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 142))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 142);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 143))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 143);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 144))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 144);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 145))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 145);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 146))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 146);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 147))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 147);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 148))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 148);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 149))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 149);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else if (PetPreview2_Pointer == ITEMGET(13, 150))
	{
		_asm
		{
			MOV EAX, DWORD PTR DS : [0x742464C];
			PUSH 0x0;
			PUSH 0x0;
			PUSH EAX;
			ADD EAX, 0x10;
			PUSH EAX;
			PUSH ITEM_ID(13, 150);

			CALL dwCreateBug;

			ADD ESP, 0x14;


			MOV PetPreview2_Hook, 0x005AD227;
			JMP PetPreview2_Hook;
		}
	}
	else
	{
		_asm
		{
			MOV PetPreview2_Hook, 0x005AD2EF;
			JMP PetPreview2_Hook;
		}
	}
}
#pragma optimize("t"off)

BOOL Barhp_Switcher;
WORD Barhp_Pointer;
DWORD Barhp_Hook;

#pragma optimize("t",on)
__declspec(naked) void BarraHp()
{
	Barhp_Switcher = FALSE;
	// ----
	_asm
	{
		MOV Barhp_Pointer, AX;
	}
	// ----
	if (Barhp_Pointer == ITEM_ID(13, 0))
	{
		Barhp_Switcher = TRUE;
	}
	else if (Barhp_Pointer == ITEM_ID(13, 1))
	{
		Barhp_Switcher = TRUE;
	}
	else if (Barhp_Pointer == ITEM_ID(13, 2))
	{
		Barhp_Switcher = TRUE;
	}
	else if (Barhp_Pointer == ITEM_ID(13, 3))
	{
		Barhp_Switcher = TRUE;
	}
	else if (Barhp_Pointer == ITEM_ID(13, 4))
	{
		Barhp_Switcher = TRUE;
	}
	else if (Barhp_Pointer >= ITEM_ID(13, 100)
		&& Barhp_Pointer <= ITEM_ID(13, 150))
	{
		Barhp_Switcher = FALSE;
		gInterface.ExToolTipShow = true;
		// ---
		_asm
		{
			MOV Barhp_Hook, 0x0059AB5A;
			JMP Barhp_Hook;
		}
	}
	else
	{
		gInterface.ExToolTipShow = false;
		// ----
		_asm
		{
			MOV Barhp_Hook, 0x0059AE9F;
			JMP Barhp_Hook;
		}
	}
	// ----
	if (Barhp_Switcher == TRUE)
	{
		_asm
		{
			MOV Barhp_Hook, 0x0059AB5A;
			JMP Barhp_Hook;
		}
	}
	else
	{
		_asm
		{
			MOV Barhp_Hook, 0x0059AE9F;
			JMP Barhp_Hook;
		}
	}
}
#pragma optimize("t",off)

DWORD Pet_Pointer;
DWORD Pet_Hook;

#define pAngleMatrix		((void(__cdecl*)(int angles,int matrix))0x5EAE50)
#define pVectorRotate		((void(__cdecl*)(int in1,int in2,vec3_t out))0x5EB130)

int CPetsManager::CreateMuun(WORD wItemID)
{
	LPOBJMODEL lpObj = &*(OBJMODEL*)oPreviewStruct;
	// ----
	for (int i = 0; i < gPetsManager.iMuunPetCount; i++)
	{
		while (wItemID == ITEMGET(gPetsManager.m_Muun[i].Type, gPetsManager.m_Muun[i].Index))
		{
			return gPetsManager.CreatePet((DWORD)(ITEM_ID(gPetsManager.m_Muun[i].Type, gPetsManager.m_Muun[i].Index)), eGuardian);
		}
	}
	return 0;
}

int CPetsManager::CheckMuun(WORD wItemID)
{
	for (int i = 0; i < gPetsManager.iMuunPetCount; i++)
	{
		if (wItemID == ITEMGET(gPetsManager.m_Muun[i].Type, gPetsManager.m_Muun[i].Index)
			&& gPetsManager.m_Muun[i].IsFlyer == TRUE)
		{
			return 1;
		}
	}
	return 0;
}

int CPetsManager::IsPetMuun(int pObject)
{
	LPOBJMODEL lpObj = &*(OBJMODEL*)pObject;
	// ----
	if (lpObj->IsRender)
	{
		for (int i = 0; i < gPetsManager.iMuunPetCount; i++)
		{
			if (lpObj->dwObjectID == ITEM_ID(gPetsManager.m_Muun[i].Type, gPetsManager.m_Muun[i].Index))
			{
				return 1;
			}
		}
	}
	return 0;
}

void CPetsManager::MoveBugHook(int a1, float Velocity)
{
	LPOBJMODEL lpObj = &*(OBJMODEL*)a1;
	// ----
	WORD ItemID = *(WORD*)(a1 + 2);
	DWORD Class = *(DWORD*)(0x5756AB8 + 224);
	// ----
	LPVOID BMD = (LPVOID)(Class*ItemID);
	// ----
	if (BMD)
	{
		if (ItemID >= ITEM_ID(13, 100) && ItemID <= ITEM_ID(13, 150))
		{
			if (gPetsManager.CheckMuun(ItemID) == 1)
			{
				if (pPlayerState != 5)
				{
					*(float*)(a1 + 20) = *(float*)(*(DWORD*)(a1 + 260) + 20) - 60.0f;
					*(float*)(a1 + 24) = *(float*)(*(DWORD*)(a1 + 260) + 24) + 60.0f;
				}
				else
				{
					gPetsManager.PetFollowCharacterFly(a1, 150);
				}
			}
			else
			{
				gPetsManager.PetFollowCharacterRun(a1, 150);
			}
		}
		// ----
		/*
		if(ItemID >= ITEM_ID(13,100) && ItemID <= ITEM_ID(13,150))
		{
			gPetsManager.PetFollowCharacter(a1,150);
			// ----
			if(pPlayerState == Select_Char && gPetsManager.m_Muun[ItemID].IsFlyer == TRUE)
			{
				if(ItemID >= ITEM_ID(13,100) && ItemID <= ITEM_ID(13,150))
				{
					*(float*)(a1 + 20) = *(float*)(*(DWORD*)(a1 + 260) + 20) - 60.0f;
					*(float*)(a1 + 24) = *(float*)(*(DWORD*)(a1 + 260) + 24) + 60.0f;
				}
			}
			else if(pPlayerState == Select_Char && gPetsManager.m_Muun[ItemID].IsFlyer == FALSE)
			{
				if(ItemID >= ITEM_ID(13,100) && ItemID <= ITEM_ID(13,150))
				{
					*(float*)(a1 + 24) = *(float*)(*(DWORD*)(a1 + 260) + 24) + 60.0f;
				}
			}
			else if(pPlayerState == Select_Game && gPetsManager.m_Muun[ItemID].IsFlyer == TRUE)
			{
				if(ItemID >= ITEM_ID(13,100) && ItemID <= ITEM_ID(13,150))
				{
					*(float*)(a1 + 24) = *(float*)(*(DWORD*)(a1 + 260) + 24) + 60.0f;
				}
			}
			else if(pPlayerState == Select_Game && gPetsManager.m_Muun[ItemID].IsFlyer == FALSE)
			{
				if(ItemID >= ITEM_ID(13,100) && ItemID <= ITEM_ID(13,150))
				{
					*(float*)(a1 + 20) = *(float*)(*(DWORD*)(a1 + 260) + 20);
				}
			}
		}
		*/
	}
	// ----
	pCreateObjectPetMovement(a1, Velocity);
}

void CPetsManager::PetFollowCharacterFly(int a1, float MaxPos)
{
	float v22;
	vec3_t MUFLOAT;
	vec3_t PetPos;
	vec3_t OwnerPos;
	vec3_t CurrentPos;
	int LootPosition = 1000;

	OwnerPos[0] = *(float *)(*(DWORD *)(a1 + 260) + 16);
	OwnerPos[1] = *(float *)(*(DWORD *)(a1 + 260) + 20);
	OwnerPos[2] = *(float *)(*(DWORD *)(a1 + 260) + 24);

	PetPos[0] = OwnerPos[0] - *(float *)(a1 + 16);
	PetPos[1] = OwnerPos[1] - *(float *)(a1 + 20);
	PetPos[2] = OwnerPos[2] - *(float *)(a1 + 24);

	CurrentPos[0] = *(float *)(a1 + 16);
	CurrentPos[1] = *(float *)(a1 + 20);
	CurrentPos[2] = *(float *)(a1 + 24);

	float PetMapPos = PetPos[0] * PetPos[0] + PetPos[1] * PetPos[1];

	float diff1 = ((OwnerPos[0] > CurrentPos[0]) ? OwnerPos[0] - CurrentPos[0] : CurrentPos[0] - OwnerPos[0]);
	float diff2 = ((OwnerPos[1] > CurrentPos[1]) ? OwnerPos[1] - CurrentPos[1] : CurrentPos[1] - OwnerPos[1]);

	float angle = atan(diff2 / diff1) * 180 / Q_PI;
	float angle2 = atan2(diff1, diff2) * 180 / Q_PI; //

	if (PetMapPos >= MaxPos * MaxPos)
	{
		float speed;
		if (PetMapPos >= (MaxPos * 2) * (MaxPos * 2))
		{
			speed = 14.0f;
			speed += 1.0f;
			*(float *)(a1 + 212) = 0.89000002f;
		}
		else if (PetMapPos >= (MaxPos + (MaxPos / 2)) * (MaxPos + (MaxPos / 2)))
		{
			speed = 13.0f;
			*(float *)(a1 + 212) = 0.69000002f;
		}
		else
		{
			speed = 10.0f;
			*(float *)(a1 + 212) = 0.40000001f;
		}

		double MoveX = speed * (cos(angle * Q_PI / 180));
		double MoveY = speed * (sin(angle * Q_PI / 180));
		// X Y
		if (CurrentPos[0] < OwnerPos[0] && CurrentPos[1] < OwnerPos[1])
		{
			*(float *)(a1 + 16) += (float)MoveX;
			*(float *)(a1 + 20) += (float)MoveY;
			*(float *)(a1 + 36) = 180;
			*(float *)(a1 + 36) -= angle2;
		}
		// X -Y
		else if (CurrentPos[0] < OwnerPos[0] && CurrentPos[1] > OwnerPos[1])
		{
			*(float *)(a1 + 16) += (float)MoveX;
			*(float *)(a1 + 20) -= (float)MoveY;
			*(float *)(a1 + 36) = angle2;
		}
		// -X Y
		else if (CurrentPos[0] > OwnerPos[0] && CurrentPos[1] > OwnerPos[1])
		{
			*(float *)(a1 + 16) -= (float)MoveX;
			*(float *)(a1 + 20) -= (float)MoveY;
			*(float *)(a1 + 36) = 360;
			*(float *)(a1 + 36) -= angle2;
		}
		// -X -Y
		else if (CurrentPos[0] > OwnerPos[0] && CurrentPos[1] < OwnerPos[1])
		{
			*(float *)(a1 + 16) -= (float)MoveX;
			*(float *)(a1 + 20) += (float)MoveY;
			*(float *)(a1 + 36) = 180;
			*(float *)(a1 + 36) += angle2;
		}
		else
		{
			*(float *)(a1 + 16) += abs(MoveX);
			*(float *)(a1 + 20) += abs(MoveY);
			*(float *)(a1 + 36) = *(float *)(*(DWORD *)(a1 + 260) + 36);
		}
		*(WORD*)(a1 + 269) = 0; // 1.01.46
	}
	else if (PetMapPos < 70 * 70)
	{
		if ((*(BYTE *)(*(DWORD *)(a1 + 260) + 269) < 15 || *(BYTE *)(*(DWORD *)(a1 + 260) + 269) > 37))
		{
			*(WORD*)(a1 + 269) = 0; // 1.01.46
			pAngleMatrix(a1 + 28, a1 + 152);				// sub_5EAE50 -> pAngleMatrix
			pVectorRotate(a1 + 200, a1 + 152, MUFLOAT);	// sub_5EB130 -> pVectorRotate
			*(float *)(a1 + 16) = *(float *)(a1 + 16) + MUFLOAT[0];
			*(float *)(a1 + 20) = *(float *)(a1 + 20) + MUFLOAT[1];
		}
	}
	/*
	else
	{
		if(GetTickCount() <= gPetsManager.PetTickCount + 800)
		{
			*(WORD*)(a1 + 269) = 0;
			*(float*)(a1 + 20) = *(float*)(*(DWORD*)(a1 + 260) + 20) + 20.0f;
		}
		else if(GetTickCount() <= gPetsManager.PetTickCount + 12000)
		{
			*(WORD*)(a1 + 269) = 0;	// -> Movement :)
			*(float*)(a1 + 20) = *(float*)(*(DWORD*)(a1 + 260) + 20) - 15.0f;
		}
		else
		{
			gPetsManager.PetTickCount = GetTickCount();
		}
	}
	*/
	if (PetMapPos >= LootPosition * LootPosition)
	{
		if (*(float *)(a1 + 16) < *(float *)(*(DWORD *)(a1 + 260) + 16))
			*(float *)(a1 + 16) = *(float *)(a1 + 16) + PetPos[0] + rand() % 360;
		if (*(float *)(a1 + 16) > *(float *)(*(DWORD *)(a1 + 260) + 16))
			*(float *)(a1 + 16) = *(float *)(a1 + 16) + PetPos[0] - rand() % 360;

		if (*(float *)(a1 + 20) < *(float *)(*(DWORD *)(a1 + 260) + 20))
			*(float *)(a1 + 20) = *(float *)(a1 + 20) + PetPos[1] + rand() % 360;
		if (*(float *)(a1 + 20) > *(float *)(*(DWORD *)(a1 + 260) + 20))
			*(float *)(a1 + 20) = *(float *)(a1 + 20) + PetPos[1] - rand() % 360;
	}

	*(float *)(a1 + 24) = *(float *)(*(DWORD *)(a1 + 260) + 24);

	if (!(rand() % 100))
	{
		if (PetMapPos < MaxPos * MaxPos)
		{
			v22 = -(float)(rand() % 64 + 16) * 0.1000000014901161f;
			*(float *)(a1 + 36) = (float)(rand() % 360);
		}
		else
		{
			v22 = -(float)(rand() % 64 + 128) * 0.1000000014901161f;
		}
		*(float *)(a1 + 200) = 0.0f;
		*(float *)(a1 + 36) = v22;
		*(float *)(a1 + 208) = (float)(rand() % 64 - 32) * 0.1000000014901161f;
	}

	if (*(float *)(a1 + 24) < *(float *)(*(DWORD *)(a1 + 260) + 24) + 100.0f)
		*(float *)(a1 + 208) = *(float *)(a1 + 208) + 1.5f;
	if (*(float *)(a1 + 24) > *(float *)(*(DWORD *)(a1 + 260) + 24) + 200.0f)
		*(float *)(a1 + 208) = *(float *)(a1 + 208) - 1.5f;
}

void CPetsManager::PetFollowCharacterRun(int a1, float MaxPos)
{
	float v22;
	vec3_t MUFLOAT;
	vec3_t PetPos;
	vec3_t OwnerPos;
	vec3_t CurrentPos;
	int LootPosition = 1000;

	OwnerPos[0] = *(float *)(*(DWORD *)(a1 + 260) + 16);
	OwnerPos[1] = *(float *)(*(DWORD *)(a1 + 260) + 20);
	OwnerPos[2] = *(float *)(*(DWORD *)(a1 + 260) + 24);

	PetPos[0] = OwnerPos[0] - *(float *)(a1 + 16);
	PetPos[1] = OwnerPos[1] - *(float *)(a1 + 20);
	PetPos[2] = OwnerPos[2] - *(float *)(a1 + 24);

	CurrentPos[0] = *(float *)(a1 + 16);
	CurrentPos[1] = *(float *)(a1 + 20);
	CurrentPos[2] = *(float *)(a1 + 24);

	float PetMapPos = PetPos[0] * PetPos[0] + PetPos[1] * PetPos[1];

	float diff1 = ((OwnerPos[0] > CurrentPos[0]) ? OwnerPos[0] - CurrentPos[0] : CurrentPos[0] - OwnerPos[0]);
	float diff2 = ((OwnerPos[1] > CurrentPos[1]) ? OwnerPos[1] - CurrentPos[1] : CurrentPos[1] - OwnerPos[1]);

	float angle = atan(diff2 / diff1) * 180 / Q_PI;
	float angle2 = atan2(diff1, diff2) * 180 / Q_PI; //

	if (PetMapPos >= MaxPos * MaxPos)
	{
		float speed;
		if (PetMapPos >= (MaxPos * 2) * (MaxPos * 2))
		{
			speed = 14.0f;
			speed += 1.0f;
			*(float *)(a1 + 212) = 0.89000002f;
		}
		else if (PetMapPos >= (MaxPos + (MaxPos / 2)) * (MaxPos + (MaxPos / 2)))
		{
			speed = 13.0f;
			*(float *)(a1 + 212) = 0.69000002f;
		}
		else
		{
			speed = 10.0f;
			*(float *)(a1 + 212) = 0.40000001f;
		}

		double MoveX = speed * (cos(angle * Q_PI / 180));
		double MoveY = speed * (sin(angle * Q_PI / 180));
		// X Y
		if (CurrentPos[0] < OwnerPos[0] && CurrentPos[1] < OwnerPos[1])
		{
			*(float *)(a1 + 16) += (float)MoveX;
			*(float *)(a1 + 20) += (float)MoveY;
			*(float *)(a1 + 36) = 180;
			*(float *)(a1 + 36) -= angle2;
		}
		// X -Y
		else if (CurrentPos[0] < OwnerPos[0] && CurrentPos[1] > OwnerPos[1])
		{
			*(float *)(a1 + 16) += (float)MoveX;
			*(float *)(a1 + 20) -= (float)MoveY;
			*(float *)(a1 + 36) = angle2;
		}
		// -X Y
		else if (CurrentPos[0] > OwnerPos[0] && CurrentPos[1] > OwnerPos[1])
		{
			*(float *)(a1 + 16) -= (float)MoveX;
			*(float *)(a1 + 20) -= (float)MoveY;
			*(float *)(a1 + 36) = 360;
			*(float *)(a1 + 36) -= angle2;
		}
		// -X -Y
		else if (CurrentPos[0] > OwnerPos[0] && CurrentPos[1] < OwnerPos[1])
		{
			*(float *)(a1 + 16) -= (float)MoveX;
			*(float *)(a1 + 20) += (float)MoveY;
			*(float *)(a1 + 36) = 180;
			*(float *)(a1 + 36) += angle2;
		}
		else
		{
			*(float *)(a1 + 16) += abs(MoveX);
			*(float *)(a1 + 20) += abs(MoveY);
			*(float *)(a1 + 36) = *(float *)(*(DWORD *)(a1 + 260) + 36);
		}
		*(WORD*)(a1 + 269) = 2; // 1.01.46
	}
	else if (PetMapPos < 70 * 70)
	{
		if ((*(BYTE *)(*(DWORD *)(a1 + 260) + 269) < 15 || *(BYTE *)(*(DWORD *)(a1 + 260) + 269) > 37))
		{
			*(WORD*)(a1 + 269) = 0; // 1.01.46
			pAngleMatrix(a1 + 28, a1 + 152);				// sub_5EAE50 -> pAngleMatrix
			pVectorRotate(a1 + 200, a1 + 152, MUFLOAT);	// sub_5EB130 -> pVectorRotate
			*(float *)(a1 + 16) = *(float *)(a1 + 16) + MUFLOAT[0];
			*(float *)(a1 + 20) = *(float *)(a1 + 20) + MUFLOAT[1];
		}
	}
	else
	{
		if (GetTickCount() <= gPetsManager.PetTickCount + 800)
		{
			*(WORD*)(a1 + 269) = 1;
			*(float*)(a1 + 20) = *(float*)(*(DWORD*)(a1 + 260) + 20) + 20.0f;
		}
		else if (GetTickCount() <= gPetsManager.PetTickCount + 12000)
		{
			*(WORD*)(a1 + 269) = 0;
			*(float*)(a1 + 20) = *(float*)(*(DWORD*)(a1 + 260) + 20) - 15.0f;
		}
		else
		{
			gPetsManager.PetTickCount = GetTickCount();
		}
	}
	if (PetMapPos >= LootPosition * LootPosition)
	{
		if (*(float *)(a1 + 16) < *(float *)(*(DWORD *)(a1 + 260) + 16))
			*(float *)(a1 + 16) = *(float *)(a1 + 16) + PetPos[0] + rand() % 360;
		if (*(float *)(a1 + 16) > *(float *)(*(DWORD *)(a1 + 260) + 16))
			*(float *)(a1 + 16) = *(float *)(a1 + 16) + PetPos[0] - rand() % 360;

		if (*(float *)(a1 + 20) < *(float *)(*(DWORD *)(a1 + 260) + 20))
			*(float *)(a1 + 20) = *(float *)(a1 + 20) + PetPos[1] + rand() % 360;
		if (*(float *)(a1 + 20) > *(float *)(*(DWORD *)(a1 + 260) + 20))
			*(float *)(a1 + 20) = *(float *)(a1 + 20) + PetPos[1] - rand() % 360;
	}

	*(float *)(a1 + 24) = *(float *)(*(DWORD *)(a1 + 260) + 24);

	if (!(rand() % 100))
	{
		if (PetMapPos < MaxPos * MaxPos)
		{
			v22 = -(float)(rand() % 64 + 16) * 0.1000000014901161f;
			*(float *)(a1 + 36) = (float)(rand() % 360);
		}
		else
		{
			v22 = -(float)(rand() % 64 + 128) * 0.1000000014901161f;
		}
		*(float *)(a1 + 200) = 0.0f;
		*(float *)(a1 + 36) = v22;
		*(float *)(a1 + 208) = (float)(rand() % 64 - 32) * 0.1000000014901161f;
	}

	if (*(float *)(a1 + 24) < *(float *)(*(DWORD *)(a1 + 260) + 24) + 100.0f)
		*(float *)(a1 + 208) = *(float *)(a1 + 208) + 1.5f;
	if (*(float *)(a1 + 24) > *(float *)(*(DWORD *)(a1 + 260) + 24) + 200.0f)
		*(float *)(a1 + 208) = *(float *)(a1 + 208) - 1.5f;
}

#define oDraw_RenderObject_Call01	0x502887
#define oDraw_RenderObject_Call02	0x5F0699
#define pDraw_RenderObject			((void(__cdecl*)(int a1,int a2,int a3,int a4))0x005EE350)

void CPetsManager::Draw_RenderObject(int a1, int a2, int a3, int a4)
{
	pDraw_RenderObject(a1, a2, a3, a4);
	// ----
	vec3_t Bone = { 0.0f,0.0f,0.0f };
	vec3_t Color = { 0.0f,0.0f,0.0f };
	vec3_t WorldPos;
	// ----
	WORD ItemID = *(WORD*)(a1 + 2);
	DWORD Class = *(DWORD*)(0x5756AB8 + 224);
	// ----
	LPVOID BMD = (LPVOID)(Class*ItemID);
	// ----
	if (BMD)
	{
		for (std::vector<pPetSpriteEffect>::iterator it = gPetsManager.m_PetSprite.begin(); it != gPetsManager.m_PetSprite.end(); it++)
		{
			if (it->ObjectId == ItemID)
			{
				Vector(it->Color[0], it->Color[1], it->Color[2], Color);
				pTransformPositionEx(BMD, Joint(it->BoneId), WorldPos, Bone, NULL);
				pCreateSprite(it->EffectId, Bone, it->Scale, Color, (LPOBJMODEL)a1, it->Position, it->SubType);
			}
		}
		// ----
		for (std::vector<pPetCreateEffects>::iterator it = gPetsManager.m_PetEffect.begin(); it != gPetsManager.m_PetEffect.end(); it++)
		{
			if (it->ObjectId == ItemID)
			{
				Vector(it->Color[0], it->Color[1], it->Color[2], Color);
				pTransformPositionEx(BMD, Joint(it->BoneId), WorldPos, Bone, NULL);
				pCreateEffect(it->EffectId, Bone, (float*)(a1 + 264), Color, it->SubType, (LPOBJMODEL)a1, NONE, NULL, it->Scale, NULL, NULL);
			}
		}
		// ----
		for (std::vector<pPetParticleEffect>::iterator it = gPetsManager.m_PetParticle.begin(); it != gPetsManager.m_PetParticle.end(); it++)
		{
			if (it->ObjectId == ItemID)
			{
				Vector(it->Color[0], it->Color[1], it->Color[2], Color);
				pTransformPositionEx(BMD, Joint(it->BoneId), WorldPos, Bone, NULL);
				pCreateParticle(it->EffectId, Bone, (float*)(a1 + 264), Color, it->SubType, it->Scale, (LPOBJMODEL)a1);
			}
		}
	}
}

void CPetsManager::Initialize()
{
	this->m_PetSprite.clear();
	this->m_PetEffect.clear();
	this->m_PetParticle.clear();
}

void CPetsManager::InitPetEffects()
{
	if (gEncode.Load(EFFECTPET_FILE))
	{
		WZSMDToken Token = gEncode.GetToken();
		// ----
		if ((Token == END) || (gEncode.GetInt() != 0))
		{
			MessageBox(NULL, "PetsEffect.gbt file corrupted (Section: 0)", "Error", MB_OK);
			ExitProcess(NULL);
		}
		// ----
		this->Initialize();
		// ----
		int Group = 0;
		int Index = 0;
		// ----
		pPetSpriteEffect PetSprite;
		// ----
		while (true)
		{
			Token = gEncode.GetToken();
			// ----
			if (Token == END || lstrcmpi(gEncode.GetString(), "end") == 0)
			{
				break;
			}
			// ----
			memset(&PetSprite, NULL, sizeof(PetSprite));
			// ----
			Group = gEncode.GetInt();		Token = gEncode.GetToken();
			Index = gEncode.GetInt();		Token = gEncode.GetToken();
			// ----
			PetSprite.ObjectId = ITEM_ID(Group, Index);
			// ----
			PetSprite.EffectId = gEncode.GetInt();		Token = gEncode.GetToken();
			PetSprite.BoneId = gEncode.GetInt();		Token = gEncode.GetToken();
			PetSprite.Scale = gEncode.GetFloat();	Token = gEncode.GetToken();
			PetSprite.Color[0] = gEncode.GetFloat();	Token = gEncode.GetToken();
			PetSprite.Color[1] = gEncode.GetFloat();	Token = gEncode.GetToken();
			PetSprite.Color[2] = gEncode.GetFloat();	Token = gEncode.GetToken();
			PetSprite.Position = gEncode.GetFloat();	Token = gEncode.GetToken();
			PetSprite.SubType = gEncode.GetInt();
			// ----
			this->m_PetSprite.push_back(PetSprite);
		}
		// ----
		Token = gEncode.GetToken();
		// ----
		if ((Token == END) || (gEncode.GetInt() != 1))
		{
			MessageBox(NULL, "PetsEffect.gbt file corrupted (Section: 1)", "Error", MB_OK);
			ExitProcess(NULL);
		}
		// ----
		pPetCreateEffects PetEffect;
		// ----
		while (true)
		{
			Token = gEncode.GetToken();
			// ----
			if (Token == END || lstrcmpi(gEncode.GetString(), "end") == 0)
			{
				break;
			}
			// ----
			memset(&PetEffect, NULL, sizeof(PetEffect));
			// ----
			Group = gEncode.GetInt();		Token = gEncode.GetToken();
			Index = gEncode.GetInt();		Token = gEncode.GetToken();
			// ----
			PetEffect.ObjectId = ITEM_ID(Group, Index);
			// ----
			PetEffect.EffectId = gEncode.GetInt();		Token = gEncode.GetToken();
			PetEffect.BoneId = gEncode.GetInt();		Token = gEncode.GetToken();
			PetEffect.Color[0] = gEncode.GetFloat();	Token = gEncode.GetToken();
			PetEffect.Color[1] = gEncode.GetFloat();	Token = gEncode.GetToken();
			PetEffect.Color[2] = gEncode.GetFloat();	Token = gEncode.GetToken();
			PetEffect.SubType = gEncode.GetInt();		Token = gEncode.GetToken();
			PetEffect.Scale = gEncode.GetFloat();
			// ----
			this->m_PetEffect.push_back(PetEffect);
		}
		// ----
		Token = gEncode.GetToken();
		// ----
		if ((Token == END) || (gEncode.GetInt() != 2))
		{
			MessageBox(NULL, "PetsEffect.gbt file corrupted (Section:2)", "Error", MB_OK);
			ExitProcess(NULL);
		}
		// ----
		pPetParticleEffect PetParticle;
		// ----
		while (true)
		{
			Token = gEncode.GetToken();
			// ----
			if (Token == END || lstrcmpi(gEncode.GetString(), "end") == 0)
			{
				break;
			}
			// ----
			memset(&PetParticle, NULL, sizeof(PetParticle));
			// ----
			Group = gEncode.GetInt();		Token = gEncode.GetToken();
			Index = gEncode.GetInt();		Token = gEncode.GetToken();
			// ----
			PetParticle.ObjectId = ITEM_ID(Group, Index);
			PetParticle.EffectId = gEncode.GetInt();		Token = gEncode.GetToken();
			PetParticle.BoneId = gEncode.GetInt();		Token = gEncode.GetToken();
			PetParticle.Color[0] = gEncode.GetFloat();	Token = gEncode.GetToken();
			PetParticle.Color[1] = gEncode.GetFloat();	Token = gEncode.GetToken();
			PetParticle.Color[2] = gEncode.GetFloat();	Token = gEncode.GetToken();
			PetParticle.SubType = gEncode.GetInt();		Token = gEncode.GetToken();
			PetParticle.Scale = gEncode.GetFloat();
			// ----
			this->m_PetParticle.push_back(PetParticle);
		}
		// ----
		if (this->m_PetSprite.size() || this->m_PetEffect.size() || this->m_PetParticle.size())
		{
			SetOp((LPVOID)oDraw_RenderObject_Call01, this->Draw_RenderObject, ASM::CALL);
			SetOp((LPVOID)oDraw_RenderObject_Call02, this->Draw_RenderObject, ASM::CALL);
		}
		// ----
		gEncode.Close();
	}
	else
	{
		MessageBox(NULL, "PetsEffect.gbt file not found", "Error", MB_OK);
		ExitProcess(NULL);
	}
}

void EffectsPetsHook()
{
	SetOp((LPVOID)0x0043FE29, gPetsManager.MoveBugHook, ASM::CALL);
	SetOp((LPVOID)0x00490086, gPetsManager.MoveBugHook, ASM::CALL);
}

void FixPreview()
{
	SetRange((LPVOID)0x005AB723, 24, ASM::NOP);
	SetJmp((LPVOID)0x005AB723, &PetPreview);
	SetRange((LPVOID)0x005AD1F0, 28, ASM::NOP);
	SetJmp((LPVOID)0x005AD1F0, &PetPreview2);
	SetRange((LPVOID)0x0059AB46, 20, ASM::NOP);
	SetJmp((LPVOID)0x0059AB46, &BarraHp);
}

void CPetsManager::Init()
{
	this->Call();
}

void CPetsManager::InitializePets()
{
	this->iMuunPetCount = 0;
	memset(this->m_Muun, NULL, sizeof(this->m_Muun));
}

void CPetsManager::InitPetMuunSystem()
{
	if (gEncode.Load(MUUNPET_FILE))
	{
		WZSMDToken Token = gEncode.GetToken();
		// ----
		if ((Token == END) || (gEncode.GetInt() != 0))
		{
			MessageBox(NULL, "PetsLoad.gbt file corrupted", "Error", MB_OK);
			ExitProcess(NULL);
		}
		// ----
		this->InitializePets();
		// ----
		while (true)
		{
			Token = gEncode.GetToken();
			// ----
			if (Token == END || lstrcmpi(gEncode.GetString(), "end") == 0)
			{
				break;
			}
			// ----
			Token = gEncode.GetToken();
			this->m_Muun[this->iMuunPetCount].Type = gEncode.GetInt();
			Token = gEncode.GetToken();
			this->m_Muun[this->iMuunPetCount].Index = gEncode.GetInt();
			Token = gEncode.GetToken();
			this->m_Muun[this->iMuunPetCount].IsFlyer = gEncode.GetInt();
			// ----
			this->iMuunPetCount++;
		}
		if (this->iMuunPetCount > 0)
		{
			FixPreview();
			EffectsPetsHook();
			this->Init();				// TEST : TODO
		}
	}
	else
	{
		MessageBox(NULL, "PetsLoad.gbt file not found", "Error", MB_OK);
		ExitProcess(NULL);
	}
}

void CPetsManager::Load()
{
	this->InitPetMuunSystem();
	this->InitPetEffects();		// Pets Effects Initialization
}