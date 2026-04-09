#include "stdafx.h"
#include "../../Util/CCRC32.H"
#include "ThemidaSDK.h"
#include "ItemDescription.h"
#include "SmokeEffect.h"
#include "CustomItem.h"
#include "CustomJewel.h"
#include "CustomWing.h"
#include "CustomBow.h"
struct MAIN_FILE_INFO
{
	char WindowName[32];
	char IP[16];
	char Version[8];
	char Serial[17];
	char ScreenShotPath[50];
	WORD IpAddressPort;

	char ClientName[32];
	char PluginName1[32];
	char PluginName2[32];
	DWORD ClientCRC32;
	DWORD Plugin1CRC32;
	DWORD Plugin2CRC32;
	// ----
	DWORD MiniMapCheck;
	DWORD SelectCharAnime;
	DWORD RemoveDraggingSkill;
	DWORD ItemLevel15;
	DWORD Transparencia;
	DWORD PlayerInfoGuildLogo;
	DWORD InterfaceType;
	DWORD LoadingWhite;
	DWORD Transparencia12;
	DWORD Transparencia14;
	DWORD Recuo;
	// ----
	DWORD COMANDOS_D;
	DWORD COMANDOS_M;
	DWORD COMANDOS_F;
	DWORD COMANDOS_S;
	DWORD COMANDOS_T;
	DWORD COMANDOS_PET;
	DWORD COMANDOS_SETOPTION;
	DWORD CSSkillCheck;
	// ---
	DWORD BALAOGM;
	DWORD Relogio;
	// ----
	CUSTOM_ITEM_INFO CustomItemInfo[MAX_CUSTOM_ITEM];
	CUSTOM_WING_INFO CustomWingInfo[MAX_CUSTOM_WING];
	CUSTOM_JEWEL_INFO CustomJewelInfo[MAX_CUSTOM_JEWEL];
	CUSTOM_ITEM_BOW_INFO CustomItemBowInfo[MAX_CUSTOM_ITEM_BOW];
	CUSTOM_DESCRIPTION_INFO CustomDescriptionInfo[MAX_CUSTOM_DESCRIPTION];
};

int _tmain(int argc, _TCHAR* argv[]) // OK
{
	CLEAR_START

	ENCODE_START

	MAIN_FILE_INFO info;

	memset(&info, 0, sizeof(info));


	GetPrivateProfileString("MainInfo", "IpAddress", "", info.IP, sizeof(info.IP), ".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo", "ClientVersion", "", info.Version, sizeof(info.Version), ".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo", "ClientSerial", "", info.Serial, sizeof(info.Serial), ".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo", "WindowName", "", info.WindowName, sizeof(info.WindowName), ".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo", "ScreenShotPath", "", info.ScreenShotPath, sizeof(info.ScreenShotPath), ".\\MainInfo.ini");

	info.IpAddressPort = GetPrivateProfileInt("MainInfo", "IpAddressPort", 44405, ".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo", "ClientName", "", info.ClientName, sizeof(info.ClientName), ".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo", "PluginName1", "", info.PluginName1, sizeof(info.PluginName1), ".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo", "PluginName2", "", info.PluginName2, sizeof(info.PluginName2), ".\\MainInfo.ini");

	info.MiniMapCheck = GetPrivateProfileInt("Custom", "MiniMapCheck", 0, ".\\MainInfo.ini");
	
	info.SelectCharAnime = GetPrivateProfileInt("Custom", "SelectCharAnimation", 0, ".\\MainInfo.ini");

	info.RemoveDraggingSkill = GetPrivateProfileInt("Custom", "RemoveDraggingSkill", 0, ".\\MainInfo.ini");

	info.ItemLevel15 = GetPrivateProfileInt("Custom", "ItemLevel15", 0, ".\\MainInfo.ini");
	info.Transparencia = GetPrivateProfileInt("Custom", "Transparencia", 0, ".\\MainInfo.ini");
	info.Transparencia12 = GetPrivateProfileInt("Custom", "Transparencia12", 0, ".\\MainInfo.ini");
	info.Transparencia14 = GetPrivateProfileInt("Custom", "Transparencia14", 0, ".\\MainInfo.ini");

	info.PlayerInfoGuildLogo = GetPrivateProfileInt("Custom", "PlayerInfoGuildLogo", 0, ".\\MainInfo.ini");

	info.InterfaceType = GetPrivateProfileInt("Custom", "InterfaceType", 0, ".\\MainInfo.ini");

	info.LoadingWhite = GetPrivateProfileInt("Custom", "LoadingWhite", 0, ".\\MainInfo.ini");

	info.Recuo = GetPrivateProfileInt("Custom", "RecuoSystem", 0, ".\\MainInfo.ini");

	info.BALAOGM = GetPrivateProfileInt("Custom", "BalaoGM", 0, ".\\MainInfo.ini");

	info.Relogio = GetPrivateProfileInt("Custom", "Relogio", 0, ".\\MainInfo.ini");





	info.COMANDOS_M = GetPrivateProfileInt("Custom", "RemoveKeyM", 0, ".\\MainInfo.ini");
	info.COMANDOS_D = GetPrivateProfileInt("Custom", "RemoveKeyD", 0, ".\\MainInfo.ini");
	info.COMANDOS_F = GetPrivateProfileInt("Custom", "RemoveKeyF", 0, ".\\MainInfo.ini");
	info.COMANDOS_T = GetPrivateProfileInt("Custom", "RemoveKeyT", 0, ".\\MainInfo.ini");
	info.COMANDOS_S = GetPrivateProfileInt("Custom", "RemoveKeyS", 0, ".\\MainInfo.ini");
	info.COMANDOS_PET = GetPrivateProfileInt("Custom", "RemovePetDisplay", 0, ".\\MainInfo.ini");
	info.COMANDOS_SETOPTION = GetPrivateProfileInt("Custom", "RemoveSetItemOption", 0, ".\\MainInfo.ini");
	// ---
	info.CSSkillCheck = GetPrivateProfileInt("Custom", "EnableCsSkillsAllMaps", 0, ".\\MainInfo.ini"); // Adcionar no GS AINDA.

	gCustomItem.Load("ItemManager/CustomItem.txt");

	gCustomJewel.Load("ItemManager/CustomJewel.txt");

	gCustomItemBow.Load("ItemManager/CustomItemBow.txt");

	gCustomWing.Load("ItemManager/CustomWing.txt");

	gCustomItemDescription.Load("ItemManager/CustomItemDescription.txt");

	memcpy(info.CustomItemInfo, gCustomItem.m_CustomItemInfo, sizeof(info.CustomItemInfo));

	memcpy(info.CustomWingInfo, gCustomWing.m_CustomWingInfo, sizeof(info.CustomWingInfo));

	memcpy(info.CustomJewelInfo, gCustomJewel.m_CustomJewelInfo, sizeof(info.CustomJewelInfo));

	memcpy(info.CustomItemBowInfo, gCustomItemBow.m_CustomItemBowInfo, sizeof(info.CustomItemBowInfo));

	memcpy(info.CustomDescriptionInfo, gCustomItemDescription.m_Info, sizeof(info.CustomDescriptionInfo));



	CCRC32 CRC32;
	if (CRC32.FileCRC(info.ClientName, &info.ClientCRC32, 1024) == 0)
	{
		info.ClientCRC32 = 0;
	}

	if (CRC32.FileCRC(info.PluginName1, &info.Plugin1CRC32, 1024) == 0)
	{
		info.Plugin1CRC32 = 0;
	}

	if (CRC32.FileCRC(info.PluginName2, &info.Plugin2CRC32, 1024) == 0)
	{
		info.Plugin2CRC32 = 0;
	}

	for (int n = 0; n < sizeof(MAIN_FILE_INFO); n++)
	{
		((BYTE*)&info)[n] ^= (BYTE)(0xCA ^ LOBYTE(n));
		((BYTE*)&info)[n] -= (BYTE)(0x95 ^ HIBYTE(n));
	}
	//system("mkdir \"Data\\Local\\\"");
	HANDLE file = CreateFile("Main.amx", GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, 0);

	if (file == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	DWORD OutSize = 0;

	if (WriteFile(file, &info, sizeof(MAIN_FILE_INFO), &OutSize, 0) == 0)
	{
		CloseHandle(file);
		return 0;
	}

	CloseHandle(file);

	ENCODE_END

		CLEAR_END

		return 0;
}
