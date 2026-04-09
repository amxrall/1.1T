#include "StdAfx.h"
#include "GlowManager.h"

DWORD dwJewelUpgradeAllow_Buff;
DWORD dwJewelApplyAllow_Buff;

void InitItem() // OK
{
	Hook(0xE9, 0x005F58AB, &FixBoxTexture);

	//Hook(0xFF, 0x0060ABBB, &ItemModelLoad); //s1

	//Hook(0xFF, 0x0060ABC0, &ItemTextureLoad); //s1

	//SetCompleteHook(0xFF, 0x005069A2, &GetItemColor); //s1

	//SetCompleteHook(0xFF, 0x005F8445, &GetItemColor); //s1

}

void InitJewel() // OK
{
	SetRange((LPVOID)0x005B8E6D, 7, ASM::NOP);
	SetJmp((LPVOID)0x005B8E6D, LoadJewelUpgrade); // 006318D2
	// ---
	SetRange((LPVOID)0x005C6CF2, 7, ASM::NOP);
	SetJmp((LPVOID)0x005C6CF2, LoadJewelApply); // 00644F73
}
__declspec(naked) void Teste()
{
	static float b6A7A04 = 1.0f;
	static DWORD Address = 0x005F9D01;

	_asm
	{
		FMUL DWORD PTR DS : [b6A7A04]
		FSTP DWORD PTR DS : [EBX]
		FLD DWORD PTR DS : [EAX + 0x4]
		FMUL DWORD PTR DS : [b6A7A04]
		FSTP DWORD PTR DS : [EDI + 0x4C]
		FLD DWORD PTR DS : [EAX + 0x8]
		MOV EAX, DWORD PTR SS : [EBP + 0x28]
		FMUL DWORD PTR DS : [b6A7A04]
		JMP[Address]
	}

}

void __declspec(naked) FixBoxTexture()
{
	static DWORD BoxTextureAddress1 = 0x005F58B7;
	_asm
	{
		MOV WORD PTR DS : [ESI + 2], 0x2231
		MOV WORD PTR DS : [ESI + 2], 0x2231
		JMP[BoxTextureAddress1]
	}
}

void ItemModelLoad() // OK
{
	pInitModelData();

	for (int n = 0; n < MAX_CUSTOM_JEWEL; n++)
	{
		if (gCustomJewel.m_CustomJewelInfo[n].Index != -1)
		{
			LoadItemModel((gCustomJewel.m_CustomJewelInfo[n].ItemIndex + ITEM_BASE_MODEL), "Item\\", gCustomJewel.m_CustomJewelInfo[n].ModelName, -1);
		}
	}

	for (int n = 0; n < MAX_CUSTOM_ITEM_BOW; n++)
	{
		if (gCustomItemBow.m_CustomItemBowInfo[n].Index != -1)
		{
			LoadItemTexture((gCustomItemBow.m_CustomItemBowInfo[n].ItemIndex + ITEM_BASE_MODEL), "Item\\", gCustomItemBow.m_CustomItemBowInfo[n].ModelName, -1);

		}
	}

	for (int n = 0; n < MAX_CUSTOM_WING; n++)
	{
		if (gCustomWing.m_CustomWingInfo[n].Index != -1)
		{
			LoadItemModel((gCustomWing.m_CustomWingInfo[n].ItemIndex + ITEM_BASE_MODEL), "Item\\", gCustomWing.m_CustomWingInfo[n].ModelName, -1);
		}
	}

	for (int n = 0; n < MAX_CUSTOM_ITEM; n++)
	{
		WORD Item = (gCustomItem.m_CustomItemInfo[n].Index);

		if (gCustomItem.m_CustomItemInfo[n].Index != -1)
		{
			LoadItemModel((gCustomItem.m_CustomItemInfo[n].ItemIndex + ITEM_BASE_MODEL), ((gCustomItem.m_CustomItemInfo[n].ItemIndex >= GET_ITEM(7, 0) && gCustomItem.m_CustomItemInfo[n].ItemIndex < GET_ITEM(12, 0)) ? "Player\\" : "Item\\"), gCustomItem.m_CustomItemInfo[n].ModelName, -1);
		}
		//else if (n == 22)
		//{
		//	Bow.Item[Item] = { (int)4, (int)7 };
		//}
		//else if (n == 23)
		//{
		//	Bow.Item[Item] = { (int)4, (int)9 };
		//}
	}
}

void ItemTextureLoad() // OK
{
	for (int n = 0; n < MAX_CUSTOM_JEWEL; n++)
	{
		if (gCustomJewel.m_CustomJewelInfo[n].Index != -1)
		{
			LoadItemTexture((gCustomJewel.m_CustomJewelInfo[n].ItemIndex + ITEM_BASE_MODEL), "Item\\", gCustomJewel.m_CustomJewelInfo[n].ModelName, -1);
		}
	}
	for (int n = 0; n < MAX_CUSTOM_ITEM_BOW; n++)
	{
		if (gCustomItemBow.m_CustomItemBowInfo[n].Index != -1)
		{
			LoadItemTexture((gCustomItemBow.m_CustomItemBowInfo[n].ItemIndex + ITEM_BASE_MODEL), "Item\\", gCustomItemBow.m_CustomItemBowInfo[n].ModelName, -1);

		}
	}
	for (int n = 0; n < MAX_CUSTOM_WING; n++)
	{
		if (gCustomWing.m_CustomWingInfo[n].Index != -1)
		{
			LoadItemTexture((gCustomWing.m_CustomWingInfo[n].ItemIndex + ITEM_BASE_MODEL), "Item\\", gCustomWing.m_CustomWingInfo[n].ModelName, -1);
		}
	}

	for (int n = 0; n < MAX_CUSTOM_ITEM; n++)
	{
		WORD Item = ITEMGET(4, n);
		if (gCustomItem.m_CustomItemInfo[n].Index != -1)
		{
			LoadItemTexture((gCustomItem.m_CustomItemInfo[n].ItemIndex + ITEM_BASE_MODEL), ((gCustomItem.m_CustomItemInfo[n].ItemIndex >= GET_ITEM(7, 0) && gCustomItem.m_CustomItemInfo[n].ItemIndex < GET_ITEM(12, 0)) ? "Player\\" : "Item\\"), gCustomItem.m_CustomItemInfo[n].ModelName, -1);
		}
		/*else if (n == 22)
		{
			Bow.Item[Item] = { (int)4, (int)7 };
		}
		else if (n == 23)
		{
			Bow.Item[Item] = { (int)4, (int)9 };
		}*/
	}

	pInitTextureData();
}

void LoadItemModel(int index, char* folder, char* name, int value)
{
	if (name[0] == 0)
	{
		return;
	}

	char path[MAX_PATH] = { 0 };

	wsprintf(path, "Data\\%s", folder);

	((void(*)(int, char*, char*, int))0x005FACA0)(index, path, name, value);
}

void LoadItemTexture(int index, char* folder, char* name, int value)
{
	if (name[0] == 0)
	{
		return;
	}

	char path[MAX_PATH] = { 0 };

	wsprintf(path, "Data\\%s", folder);

	((void(*)(int, char*, int, int, int))0x005FA860)(index, folder, 0x2901, 0x2600, 0x01);
}

void GetItemColor(DWORD a, DWORD b, DWORD c, DWORD d, DWORD e)
{
	if (gCustomItem.GetCustomItemColor((a - ITEM_BASE_MODEL), (float*)d) == 0)
	{
		((void(*)(DWORD, DWORD, DWORD, DWORD, DWORD))0x005F6220)(a, b, c, d, e);
	}
}


__declspec(naked) void LoadJewelUpgrade()
{
	_asm
	{
		CMP SI, ITEM(14, 14)
		JE Exit
		// ---
		CMP SI, ITEM(14, 200)
		JE Exit
		// ---
		CMP SI, ITEM(14, 201)
		JE Exit
		// ---
		CMP SI, ITEM(14, 202)
		JE Exit
		// ---
		CMP SI, ITEM(14, 203)
		JE Exit
		// ---
		CMP SI, ITEM(14, 204)
		JE Exit
		// ---
		CMP SI, ITEM(14, 205)
		JE Exit
		// ---
		CMP SI, ITEM(14, 206)
		JE Exit
		// ---
		CMP SI, ITEM(14, 207)
		JE Exit
		// ---
		CMP SI, ITEM(14, 208)
		JE Exit
		// ---
		CMP SI, ITEM(14, 209)
		JE Exit
		// ---
		CMP SI, ITEM(14, 210)
		JE Exit
		// ---
		CMP SI, ITEM(14, 211)
		JE Exit
		// ---
		CMP SI, ITEM(14, 212)
		JE Exit
		// ---
		CMP SI, ITEM(14, 213)
		JE Exit
		// ---
		CMP SI, ITEM(14, 214)
		JE Exit
		// ---
		MOV dwJewelUpgradeAllow_Buff, 0x005B8E74 // 006318D9
		JMP dwJewelUpgradeAllow_Buff
		// ---
		Exit :
		MOV dwJewelUpgradeAllow_Buff, 0x005B8E92 // 00631913
			JMP dwJewelUpgradeAllow_Buff
	}
}

__declspec(naked) void LoadJewelApply()
{
	_asm
	{
		CMP DX, ITEM(14, 14)
		JE Exit
		// ---
		CMP DX, ITEM(14, 200)
		JE Exit
		// ---
		CMP DX, ITEM(14, 201)
		JE Exit
		// ---
		CMP DX, ITEM(14, 202)
		JE Exit
		// ---
		CMP DX, ITEM(14, 203)
		JE Exit
		// ---
		CMP DX, ITEM(14, 204)
		JE Exit
		// ---
		CMP DX, ITEM(14, 205)
		JE Exit
		// ---
		CMP DX, ITEM(14, 206)
		JE Exit
		// ---
		CMP DX, ITEM(14, 207)
		JE Exit
		// ---
		CMP DX, ITEM(14, 208)
		JE Exit
		// ---
		CMP DX, ITEM(14, 209)
		JE Exit
		// ---
		CMP DX, ITEM(14, 210)
		JE Exit
		// ---
		CMP DX, ITEM(14, 211)
		JE Exit
		// ---
		CMP DX, ITEM(14, 212)
		JE Exit
		// ---
		CMP DX, ITEM(14, 213)
		JE Exit
		// ---
		CMP DX, ITEM(14, 214)
		JE Exit
		// ---
		MOV dwJewelApplyAllow_Buff, 0x005C6CF9 // 00644F7A
		JMP dwJewelApplyAllow_Buff
		// ---
		Exit :
		MOV dwJewelApplyAllow_Buff, 0x005C6D04 // 00644F9A
			JMP dwJewelApplyAllow_Buff
	}
}