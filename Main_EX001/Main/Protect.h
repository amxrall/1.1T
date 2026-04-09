#ifndef _PROTECT_H
#define _PROTECT_H

#include "ItemDescription.h"
#include "CustomItem.h"
#include "CustomJewel.h"
#include "CustomWing.h"
#include "CustomBow.h"

#pragma once


struct PROTECT_DATA
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

	// ----------
	CUSTOM_ITEM_INFO CustomItemInfo[MAX_CUSTOM_ITEM];
	CUSTOM_WING_INFO CustomWingInfo[MAX_CUSTOM_WING];
	CUSTOM_JEWEL_INFO CustomJewelInfo[MAX_CUSTOM_JEWEL];
	CUSTOM_ITEM_BOW_INFO CustomItemBowInfo[MAX_CUSTOM_ITEM_BOW];
	CUSTOM_DESCRIPTION_INFO CustomDescriptionInfo[MAX_CUSTOM_DESCRIPTION];

};

class CProtect
{
public:
	CProtect();
	virtual ~CProtect();
	bool Load(char* szName);
	void CheckClientFile();
	void CheckPlugin1File();
	void CheckPlugin2File();
public:
	PROTECT_DATA m_Data;
	DWORD m_FileCrc;
};
extern CProtect gProtect;

#endif