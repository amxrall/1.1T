#include "StdAfx.h"

void cTexture::Load()
{
	memset(&this->Textures, 0, sizeof(Textures));

	*(DWORD*)(0x4A982D) = TEXTURE_MAX;
	*(DWORD*)(0x6086EF) = (DWORD)(&this->Textures);
	*(DWORD*)(0x534410) = (DWORD)(&this->Textures);
	*(DWORD*)(0x534A39) = (DWORD)(&this->Textures);
	*(DWORD*)(0x534A48) = (DWORD)(&this->Textures);
	*(DWORD*)(0x5E000D) = (DWORD)(&this->Textures);
	*(DWORD*)(0x5E9780) = (DWORD)(&this->Textures);
	*(DWORD*)(0x5FA7E9) = (DWORD)(&this->Textures);
	*(DWORD*)(0x5FA844) = (DWORD)(&this->Textures);
	*(DWORD*)(0x5FA9BC) = (DWORD)(&this->Textures);
	*(DWORD*)(0x62C4E6) = (DWORD)(&this->Textures);
	*(DWORD*)(0x62C93B) = (DWORD)(&this->Textures);
	*(DWORD*)(0x62CADD) = (DWORD)(&this->Textures);
	*(DWORD*)(0x62CB5C) = (DWORD)(&this->Textures);
	*(DWORD*)(0x44D909) = (DWORD)(&this->Textures->Width);
	*(DWORD*)(0x44D9CA) = (DWORD)(&this->Textures->Width);
	*(DWORD*)(0x44DA8A) = (DWORD)(&this->Textures->Width);
	*(DWORD*)(0x460BB8) = (DWORD)(&this->Textures->Width);
	*(DWORD*)(0x461570) = (DWORD)(&this->Textures->Width);
	*(DWORD*)(0x53D284) = (DWORD)(&this->Textures->Width);
	*(DWORD*)(0x53DF56) = (DWORD)(&this->Textures->Width);
	*(DWORD*)(0x5484E4) = (DWORD)(&this->Textures->Width);
	*(DWORD*)(0x5485F6) = (DWORD)(&this->Textures->Width);
	*(DWORD*)(0x636CA2) = (DWORD)(&this->Textures->Width);
	*(DWORD*)(0x636CC0) = (DWORD)(&this->Textures->Width);
	*(DWORD*)(0x636CE9) = (DWORD)(&this->Textures->Width);
	*(DWORD*)(0x636CFE) = (DWORD)(&this->Textures->Width);
	*(DWORD*)(0x5E0006) = (DWORD)(&this->Textures->Width);
	*(DWORD*)(0x5E9779) = (DWORD)(&this->Textures->Width);
	*(DWORD*)(0x630A78) = (DWORD)(&this->Textures->Width);
	*(DWORD*)(0x636D4F) = (DWORD)(&this->Textures->Width);
	*(DWORD*)(0x636F6D) = (DWORD)(&this->Textures->Width);
	*(DWORD*)(0x636FA0) = (DWORD)(&this->Textures->Width);
	*(DWORD*)(0x44D923) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x44D9B2) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x44DA74) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x460BA0) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x46142D) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x46155A) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x461B06) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x53D290) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x53DF5F) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x548403) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x5484CC) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x5485E0) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x5E90D9) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x636CB1) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x636CD4) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x636CF2) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x636D0D) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x53BACE) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x636D72) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x636FE5) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x63701A) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x6598D0) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x6599B5) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x659B2F) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x659B69) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x659BA2) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x659BEC) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x659C28) = (DWORD)(&this->Textures->Height);
	*(DWORD*)(0x44D9D7) = (DWORD)(&this->Textures->UnkDword28);
	*(DWORD*)(0x451F6B) = (DWORD)(&this->Textures->UnkDword28);
	*(DWORD*)(0x451FF3) = (DWORD)(&this->Textures->UnkDword28);
	*(DWORD*)(0x4529AA) = (DWORD)(&this->Textures->UnkDword28);
	*(DWORD*)(0x4529FE) = (DWORD)(&this->Textures->UnkDword28);
	*(DWORD*)(0x460BC5) = (DWORD)(&this->Textures->UnkDword28);
	*(DWORD*)(0x4E5487) = (DWORD)(&this->Textures->UnkDword28);
	*(DWORD*)(0x4E54D4) = (DWORD)(&this->Textures->UnkDword28);
	*(DWORD*)(0x4E606B) = (DWORD)(&this->Textures->UnkDword28);
	*(DWORD*)(0x4E60B8) = (DWORD)(&this->Textures->UnkDword28);
	*(DWORD*)(0x4E7ACD) = (DWORD)(&this->Textures->UnkDword28);
	*(DWORD*)(0x4E7B03) = (DWORD)(&this->Textures->UnkDword28);
	*(DWORD*)(0x53D2A5) = (DWORD)(&this->Textures->UnkDword28);
	*(DWORD*)(0x53DD95) = (DWORD)(&this->Textures->UnkDword28);
	*(DWORD*)(0x5484F1) = (DWORD)(&this->Textures->UnkDword28);
	*(DWORD*)(0x60D718) = (DWORD)(&this->Textures->UnkDword28);
	*(DWORD*)(0x44D997) = (DWORD)(&this->Textures->Texture);
	*(DWORD*)(0x5484B4) = (DWORD)(&this->Textures->Texture);
	*(DWORD*)(0x60C935) = (DWORD)(&this->Textures->Texture);
	*(DWORD*)(0x60C991) = (DWORD)(&this->Textures->Texture);
	*(DWORD*)(0x637259) = (DWORD)(&this->Textures->Texture);
	*(DWORD*)(0x460B0D) = (DWORD)(&this->Textures->UnkPByte34);
	*(DWORD*)(0x4631D9) = (DWORD)(&this->Textures->UnkPByte34);
	*(DWORD*)(0x463209) = (DWORD)(&this->Textures->UnkPByte34);
	*(DWORD*)(0x60EF87) = (DWORD)(&this->Textures->UnkPByte34);
	*(DWORD*)(0x44D95F) = (DWORD)(&this->Textures->UnkPByte34);
	*(DWORD*)(0x44D9AC) = (DWORD)(&this->Textures->UnkPByte34);
	*(DWORD*)(0x4603BA) = (DWORD)(&this->Textures->UnkPByte34);
	*(DWORD*)(0x460B9A) = (DWORD)(&this->Textures->UnkPByte34);
	*(DWORD*)(0x46321E) = (DWORD)(&this->Textures->UnkPByte34);
	*(DWORD*)(0x548422) = (DWORD)(&this->Textures->UnkPByte34);
	*(DWORD*)(0x5484C6) = (DWORD)(&this->Textures->UnkPByte34);
	*(DWORD*)(0x5E90C5) = (DWORD)(&this->Textures->UnkPByte34);
	*(DWORD*)(0x534407) = (DWORD)(&this->Textures->UnkPByte34);
	*(DWORD*)(0x62CAD4) = (DWORD)(&this->Textures->UnkPByte34);
	*(DWORD*)(0x62CB53) = (DWORD)(&this->Textures->UnkPByte34);
	*(DWORD*)(0x5DFDF8) = (DWORD)(&this->Textures) + 0x790;
	*(DWORD*)(0x5E0375) = (DWORD)(&this->Textures) + 0x790;
	*(DWORD*)(0x5DFE06) = (DWORD)(&this->Textures) + 0x794;
	*(DWORD*)(0x5E0383) = (DWORD)(&this->Textures) + 0x794;
	*(DWORD*)(0x5DFF72) = (DWORD)(&this->Textures) + 0x798;
	*(DWORD*)(0x5E0432) = (DWORD)(&this->Textures) + 0x798;
	*(DWORD*)(0x5DFF56) = (DWORD)(&this->Textures) + 0x79C;
	*(DWORD*)(0x5E0419) = (DWORD)(&this->Textures) + 0x79C;
	*(DWORD*)(0x5DFE16) = (DWORD)(&this->Textures) + 0x7A4;
	*(DWORD*)(0x5DFF68) = (DWORD)(&this->Textures) + 0x7A4;
	*(DWORD*)(0x5E0393) = (DWORD)(&this->Textures) + 0x7A4;
	*(DWORD*)(0x5E03CB) = (DWORD)(&this->Textures) + 0x7A4;
	*(DWORD*)(0x5E042B) = (DWORD)(&this->Textures) + 0x7A4;
	*(DWORD*)(0x5E8C12) = (DWORD)(&this->Textures) + 0x7A8;
	*(DWORD*)(0x59CD95) = (DWORD)(&this->Textures) + 0x7D0;
	*(DWORD*)(0x6044AA) = (DWORD)(&this->Textures) + 0xE38;
	*(DWORD*)(0x6044B3) = (DWORD)(&this->Textures) + 0x1068;
	*(DWORD*)(0x6044FF) = (DWORD)(&this->Textures) + 0x1068;
	*(DWORD*)(0x604552) = (DWORD)(&this->Textures) + 0x1538;

	MemorySet(0x5FA7B0, 0x90, 5);
	TextureMax = 15000;

	MemorySet(0x5FE283, 0x90, 22);
	SetCompleteHook(0xE9, 0x5FE283, cTexture::gObjTexture);
}

__declspec(naked) void cTexture::gObjTexture()
{
	for (int n = 0; n < MAX_CUSTOM_ITEM; n++)
	{
		if (gCustomItem.m_CustomItemInfo[n].Index != -1)
		{
			LoadItemModel((gCustomItem.m_CustomItemInfo[n].ItemIndex + ITEM_BASE_MODEL), ((gCustomItem.m_CustomItemInfo[n].ItemIndex >= GET_ITEM(7, 0) && gCustomItem.m_CustomItemInfo[n].ItemIndex < GET_ITEM(12, 0)) ? "Player\\" : "Item\\"), gCustomItem.m_CustomItemInfo[n].ModelName, -1);
			LoadItemTexture((gCustomItem.m_CustomItemInfo[n].ItemIndex + ITEM_BASE_MODEL), ((gCustomItem.m_CustomItemInfo[n].ItemIndex >= GET_ITEM(7, 0) && gCustomItem.m_CustomItemInfo[n].ItemIndex < GET_ITEM(12, 0)) ? "Player\\" : "Item\\"), gCustomItem.m_CustomItemInfo[n].ModelName, -1);
		}
	}

	for (int n = 0; n < MAX_CUSTOM_JEWEL; n++)
	{
		if (gCustomJewel.m_CustomJewelInfo[n].Index != -1)
		{
			LoadItemModel((gCustomJewel.m_CustomJewelInfo[n].ItemIndex + ITEM_BASE_MODEL), "Item\\", gCustomJewel.m_CustomJewelInfo[n].ModelName, -1);
			LoadItemTexture((gCustomJewel.m_CustomJewelInfo[n].ItemIndex + ITEM_BASE_MODEL), "Item\\", gCustomJewel.m_CustomJewelInfo[n].ModelName, -1);
		}
	}

	for (int n = 0; n < MAX_CUSTOM_WING; n++)
	{
		if (gCustomWing.m_CustomWingInfo[n].Index != -1)
		{
			LoadItemModel((gCustomWing.m_CustomWingInfo[n].ItemIndex + ITEM_BASE_MODEL), "Item\\", gCustomWing.m_CustomWingInfo[n].ModelName, -1);
			LoadItemTexture((gCustomWing.m_CustomWingInfo[n].ItemIndex + ITEM_BASE_MODEL), "Item\\", gCustomWing.m_CustomWingInfo[n].ModelName, -1);
		}
	}

	_asm
	{
		PUSH - 1;
		PUSH 0x6BA85C;
		PUSH 0x6BAA90;
		PUSH 0x1E22;
		MOV EAX, 0x5FACA0;
		CALL EAX;

		MOV EAX, 0x5FE299;
		JMP EAX;
	}
}

cTexture Texture;