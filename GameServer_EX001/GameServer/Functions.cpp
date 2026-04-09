#include "StdAfx.h"
#include "GameServer.h"
#include "ObjCalCharacter.h"
#include "DSProtocol.h"
#include "EDSProtocol.h"
#include "GameMain.h"
#include "ChaosCastle.h"
#include "MapServerManager.h"
#include "winutil.h"

void cFunctions::MsgOutput(int aIndex, int Type, char* Msg, ...)
{
	char Buffer[250];
	va_list pArguments;

	va_start(pArguments, Msg);
	vsprintf(Buffer, Msg, pArguments);
	va_end(pArguments);

	GCServerMsgStringSend(Buffer, aIndex, Type);
}

void cFunctions::AllServerAnnounce(char* message, ...)
{
	char Buffer[512] = "";
	va_list pArguments;

	va_start(pArguments, message);
	vsprintf(&Buffer[0], message, pArguments);
	va_end(pArguments);

	for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
	{
		if (gObj[i].Connected == 3)
		{
			GCServerMsgStringSend(&Buffer[0], i, 0);
		}
	}
}

void cFunctions::SendMapServerGroupMsg(char* message)
{
	GS_GDReqMapSvrMsgMultiCast(g_MapServerManager.GetMapSvrGroup(), message);
}

void cFunctions::UpdateCharacter(int aIndex, bool Effect)
{
	PMSG_UPDATECHARACTER Result;

	Result.h.c = 0xC1;
	Result.h.size = sizeof(PMSG_UPDATECHARACTER);
	Result.h.headcode = 0xFE;
	Result.Code = (Effect == true) ? 1 : 2;

	if (Effect == true)
	{
		Result.Experience = gObj[aIndex].Experience;
		Result.NextExperience = gObj[aIndex].NextExp;
		Result.Level = (WORD)(gObj[aIndex].Level);
	}

	Result.LevelUpPoint = gObj[aIndex].LevelUpPoint;
	Result.Strength = (WORD)(gObj[aIndex].Strength);
	Result.Dexterity = (WORD)(gObj[aIndex].Dexterity);
	Result.Vitality = (WORD)(gObj[aIndex].Vitality);
	Result.Energy = (WORD)(gObj[aIndex].Energy);
	Result.Leadership = (WORD)(gObj[aIndex].Leadership);
	Result.Life = (WORD)(gObj[aIndex].Life);
	Result.MaxLife = (WORD)(gObj[aIndex].MaxLife);
	Result.Mana = (WORD)(gObj[aIndex].Mana);
	Result.MaxMana = (WORD)(gObj[aIndex].MaxMana);
	Result.BP = (WORD)(gObj[aIndex].BP);
	Result.MaxBP = (WORD)(gObj[aIndex].MaxBP);

	DataSend(aIndex, (LPBYTE)(&Result), Result.h.size);

	gObjCalCharacter(aIndex);
	gObjCalcMaxLifePower(aIndex);
}

int cFunctions::GetPlayerIndex(char* Name)
{
	for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
	{
		if (gObj[i].Connected > 2)
		{
			if (!strcmp(gObj[i].Name, Name))
			{
				return i;
			}
		}
	}

	return -1;
}

int cFunctions::MonsterAdd(int MobID, int MapID, int CoordX, int CoordY)
{
	int Index = gObjAddMonster(MapID);

	if (Index >= 0)
	{
		gObj[Index].Class = MobID;
		gObj[Index].MapNumber = MapID;
		gObj[Index].X = CoordX;
		gObj[Index].Y = CoordY;
		gObjSetMonster(Index, MobID);
	}

	return Index;
}

void cFunctions::SendLevelUp(int aIndex)
{
	PMSG_UPDATEPOINTS Result;

	Result.h.c = 0xC1;
	Result.h.size = sizeof(Result);
	Result.h.headcode = 0xFE;
	Result.subcode = 0x08;
	Result.LevelUpPoint = gObj[aIndex].LevelUpPoint;

	DataSend(aIndex, (LPBYTE)&Result, Result.h.size);
}

void cFunctions::SendMain(int aIndex)
{
	PMSG_CHARINFOMAIN Result;

	Result.h.c = 0xC1;
	Result.h.size = sizeof(Result);
	Result.h.headcode = 0xFE;
	Result.Code = 0x07;
	Result.Class = gObj[aIndex].Class;
	Result.LevelUpPoint = gObj[aIndex].LevelUpPoint;

	DataSend(aIndex, (LPBYTE)(&Result), Result.h.size);
}

void cFunctions::Blue(LPCSTR Nome, LPSTR Mensagem, int aIndex)
{
	BYTE Buffer[0xFF] = { 0 };
	BYTE Len = strlen(Mensagem);
	Buffer[0] = 0xC1;
	Buffer[1] = Len + 15;
	Buffer[2] = 0x00;
	strncpy((char*)&Buffer[3], Nome, 10);
	Buffer[13] = 0x7E;
	strncpy((char*)&Buffer[14], Mensagem, Len);

	for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
	{
		if (gObj[i].Connected == 3)
		{
			DataSend(i, (unsigned char*)Buffer, Buffer[1]);
		}
	}
}

void cFunctions::Green(LPCSTR Nome, LPSTR Mensagem, int aIndex)
{
	BYTE Buffer[0xFF] = { 0 };
	BYTE Len = strlen(Mensagem);
	Buffer[0] = 0xC1;
	Buffer[1] = Len + 15;
	Buffer[2] = 0x00;
	Buffer[13] = 0x40;
	strncpy((char*)&Buffer[3], Nome, 10);
	strncpy((char*)&Buffer[14], Mensagem, Len);

	for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
	{
		if (gObj[i].Connected == 3)
		{
			DataSend(i, (unsigned char*)Buffer, Buffer[1]);
		}
	}
}

void cFunctions::Yellow(LPCSTR Nome, LPSTR Mensagem, int aIndex)
{
	BYTE Buffer[0xFF] = { 0 };
	BYTE Len = strlen(Mensagem);
	Buffer[0] = 0xC1;
	Buffer[1] = Len + 14;
	Buffer[2] = 0x02;
	strncpy((char*)&Buffer[3], Nome, 10);
	strncpy((char*)&Buffer[13], Mensagem, Len);

	for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
	{
		if (gObj[i].Connected == 3)
		{
			DataSend(i, (unsigned char*)Buffer, Buffer[1]);
		}
	}
}

void cFunctions::Golden(int aIndex, const char* Format, ...)
{
	char Buffer[512] = "";
	va_list pArguments;

	va_start(pArguments, Format);
	vsprintf(&Buffer[0], Format, pArguments);
	va_end(pArguments);

	BYTE *Packet = (BYTE*)malloc(200);
	memset(Packet, 0x00, 200);
	*Packet = 0xC1;
	*(Packet + 2) = 0x02;
	memcpy((Packet + 13), Buffer, strlen(Buffer));
	int Len = (strlen(Buffer) + 0x13);
	*(Packet + 1) = Len;
	
	DataSend(aIndex, Packet, Len);

	free(Packet);
}

bool cFunctions::CheckItem(int aIndex)
{
	for (int i = 0; i < 11; i++)
	{
		if (gObj[aIndex].pInventory[i].IsItem())
		{
			return false;
		}
	}

	return true;
}

float cFunctions::GetStatus(int aIndex, BYTE Class, BYTE Type)
{
	int Vit, Energy;

	float Life, Mana, LevelLife, LevelMana, VitalityToLife, EnergyToMana, Return = 0;

	switch (Class)
	{
	case 0:
		Vit = 15;
		Energy = 30;
		Life = 60; Mana = 60;
		LevelLife = 1; LevelMana = 2;
		VitalityToLife = 1; EnergyToMana = 2;
		break;
	case 1:
		Vit = 25;
		Energy = 10;
		Life = 110; Mana = 20;
		LevelLife = 2; LevelMana = 0.5;
		VitalityToLife = 3; EnergyToMana = 1;
		break;
	case 2:
		Vit = 20;
		Energy = 15;
		Life = 80; Mana = 30;
		LevelLife = 1; LevelMana = 1.5;
		VitalityToLife = 2; EnergyToMana = 1.5;
		break;
	case 3:
		Vit = 26;
		Energy = 26;
		Life = 110; Mana = 60;
		LevelLife = 1; LevelMana = 1;
		VitalityToLife = 2; EnergyToMana = 2;
		break;
	case 4:
		Vit = 20;
		Energy = 15;
		Life = 90; Mana = 40;
		LevelLife = 1.5; LevelMana = 1;
		VitalityToLife = 2; EnergyToMana = 2;
		break;
	}

	if (Type == 0)
	{
		Return = Life + ((gObj[aIndex].Level - 1) * LevelLife) + ((gObj[aIndex].Vitality - Vit) * VitalityToLife);
	}

	if (Type == 1)
	{
		Return = Mana + ((gObj[aIndex].Level - 1) * LevelMana) + ((gObj[aIndex].Vitality - Vit) * EnergyToMana);
	}

	return Return;
}

void cFunctions::FireWork(int aIndex)
{
	if (gObj[aIndex].X <= 5 || gObj[aIndex].X >= 250 || gObj[aIndex].Y <= 5 || gObj[aIndex].Y >= 250)
	{
		return;
	}

	char Packet[5] = { -2, -1, 0, 1, 2 };

	BYTE FireWork[10][7];

	for (int i = 0; i < 10; i++)
	{
		BYTE X = (rand() % 5);
		BYTE Y = (rand() % 5);

		FireWork[i][0] = 0xC1;
		FireWork[i][1] = 0x07;
		FireWork[i][2] = 0xF3;
		FireWork[i][3] = 0x40;
		FireWork[i][4] = 0x00;
		FireWork[i][5] = (BYTE)(gObj[aIndex].X + Packet[X]);
		FireWork[i][6] = (BYTE)(gObj[aIndex].Y + Packet[Y]);
	}

	for (int i = OBJ_STARTUSERINDEX; i < OBJMAX; ++i)
	{
		if (gObj[i].Connected == 3)
		{
			if (gObj[i].MapNumber == gObj[aIndex].MapNumber)
			{
				for (int Count = 0; Count < 10; Count++)
				{
					DataSend(i, (LPBYTE)(&FireWork[Count]), FireWork[Count][1]);
				}
			}
		}
	}
}

void cFunctions::PlayerOut(LPOBJ lpObj)
{
	if (lpObj->Custom->Move == true)
	{
		if (lpObj->Live == TRUE)
		{
			if (lpObj->Class == ELF)
			{
				int X = 171 + rand() % 6;
				int Y = 108 + rand() % 8;

				gObjTeleport(lpObj->m_Index, 3, X, Y);

				lpObj->Custom->Move = false;
			}
			else
			{
				int X = 133 + rand() % 15;
				int Y = 118 + rand() % 15;

				gObjTeleport(lpObj->m_Index, 0, X, Y);

				lpObj->Custom->Move = false;
			}
		}
	}
	else if (Duel.DuelStruct[lpObj->m_Index]._Move == true)
	{
		if (lpObj->Live == TRUE)
		{
			gObjTeleport(lpObj->m_Index, 2, 210, 41);

			lpObj->m_PK_Level = 3;
			GCPkLevelSend(lpObj->m_Index, 3);

			Duel.DuelStruct[lpObj->m_Index]._Move = false;
		}
	}
	else if (lpObj->Custom->Dead == true)
	{
		if (lpObj->Live == TRUE)
		{
			lpObj->m_PK_Level = 3;
			GCPkLevelSend(lpObj->m_Index, 3);

			lpObj->Custom->Dead = false;
		}
	}
}

int cFunctions::CheckInventory(int aIndex, int Type, int Level)
{
	int Count = 0;

	for (int i = 12; i < 76; i++)
	{
		if (gObj[aIndex].pInventory[i].m_Type == Type && gObj[aIndex].pInventory[i].m_Level >= Level)
		{
			Count++;
		}
	}

	return Count;
}

int cFunctions::DeleteInventory(int aIndex, int Type, int Level, int Quantity)
{
	int Count = 0;

	for (int i = 12; i < 76; i++)
	{
		if (gObj[aIndex].pInventory[i].m_Type == Type && gObj[aIndex].pInventory[i].m_Level >= Level)
		{
			gObjInventoryDeleteItem(aIndex, i);

			GCInventoryItemDeleteSend(aIndex, i, 1);

			Count++;

			if (Quantity == Count)
				break;
		}
	}

	return Count;
}

int cFunctions::InventoryFullCheck(int aIndex, short Item)
{
	int W, H, Width, Height, Result = 0;

	BYTE Blank = 0;

	ItemGetSize(Item, Width, Height);

	if (Width == 0 || Height == 0)
	{
		return Result;
	}

	for (H = 0; H < 8; H++)
	{
		for (W = 0; W < 8; W++)
		{
			if (*(BYTE*)(gObj[aIndex].pInventoryMap + (H * 8) + W) == 255)
			{
				Blank = gObjOnlyInventoryRectCheck(aIndex, W, H, Width, Height);

				if (Blank == 254)
				{
					return Result;
				}

				if (Blank != 255)
				{
					Result++;
				}
			}
		}
	}

	return Result;
}

void cFunctions::HealthBarSend(LPOBJ lpObj)
{
	BYTE Buffer[1500];
	PMSG_HEALTHBAR Result;
	PMSG_HEALTHBAR_INFO Info;

	Result.h.c = 0xC2;
	Result.h.headcode = 0xF3;
	Result.Code = 0xE2;
	Result.Count = 0;

	int Size = sizeof(Result);

	for (int i = 0; i < MAX_VIEWPORT; i++)
	{
		if (lpObj->VpPlayer[i].state != 1 && lpObj->VpPlayer[i].state != 2)
		{
			continue;
		}

		if (lpObj->VpPlayer[i].type != OBJ_MONSTER)
		{
			continue;
		}

		if (OBJMAX_RANGE(lpObj->VpPlayer[i].number) == 0)
		{
			continue;
		}

		LPOBJ lpTargetObj = &gObj[lpObj->VpPlayer[i].number];

		if (lpTargetObj->Class == 200 || lpTargetObj->Live == 0 || lpTargetObj->m_State != 2 || CC_MAP_RANGE(lpTargetObj->MapNumber) != 0)
		{
			continue;
		}

		Info.Index = lpObj->VpPlayer[i].number;
		Info.Rate = (BYTE)((lpTargetObj->Life * 100) / (lpTargetObj->MaxLife + lpTargetObj->AddLife));

		memcpy(&Buffer[Size], &Info, sizeof(Info));
		Size += sizeof(Info);
		Result.Count++;
	}

	Result.h.sizeH = HIBYTE(Size);
	Result.h.sizeL = LOBYTE(Size);

	memcpy(Buffer, &Result, sizeof(Result));

	DataSend(lpObj->m_Index, Buffer, Size);
}

void cFunctions::UseItem(PMSG_USEITEM* lpMsg, int aIndex)
{
	CItem* Item = &gObj[aIndex].pInventory[lpMsg->inventoryPos];
	CItem* Add = &gObj[aIndex].pInventory[lpMsg->invenrotyTarget];

	if (Item->m_Type == ITEMGET(15, 19))
	{
		if (DeathEvent._Portal == true)
		{
			if (gObj[aIndex].Level < DeathEvent._Level)
			{
				Function.MsgOutput(aIndex, 1, "É necessário %d de level.", DeathEvent._Level);
				return;
			}
			else if (gObj[aIndex].Money < DeathEvent._Zen)
			{
				Function.MsgOutput(aIndex, 1, "É necessário %d de zen.", DeathEvent._Zen);
				return;
			}
			else if (gObj[aIndex].Custom->InDuel == true)
			{
				Function.MsgOutput(aIndex, 1, "Saia do duelo para participar.");
				return;
			}
			else if (DeathEvent.PlayerStruct[aIndex]._InEvent == true)
			{
				Function.MsgOutput(aIndex, 1, "Você já está registrado no evento. Aguarde.");
				return;
			}

			DeathEvent.PlayerStruct[aIndex]._InEvent = true;
			DeathEvent.PlayerStruct[aIndex]._AttackBlock = true;

			GCMoneySend(aIndex, gObj[aIndex].Money -= DeathEvent._Zen);

			gObj[aIndex].m_PK_Level = 6;
			GCPkLevelSend(aIndex, gObj[aIndex].m_PK_Level);

			gObjTeleport(aIndex, DeathEvent._MapNumber, DeathEvent._X, DeathEvent._Y);

			DeathEvent._Players++;

			gObjInventoryItemSet(aIndex, lpMsg->inventoryPos, -1);
			gObj[aIndex].pInventory[lpMsg->inventoryPos].Clear();
			GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);

			Function.MsgOutput(aIndex, 1, "Você foi registrado no evento. Aguarde...");
		}
		else if (TheftEvent._Portal == true)
		{
			if (gObj[aIndex].Level < TheftEvent._Level)
			{
				Function.MsgOutput(aIndex, 1, "É necessário %d de level.", TheftEvent._Level);
				return;
			}
			else if (gObj[aIndex].Money < TheftEvent._Zen)
			{
				Function.MsgOutput(aIndex, 1, "É necessário %d de zen.", TheftEvent._Zen);
				return;
			}
			else if (gObj[aIndex].Custom->InDuel == true)
			{
				Function.MsgOutput(aIndex, 1, "Saia do duelo para participar.");
				return;
			}
			else if (TheftEvent.PlayerStruct[aIndex]._InEvent == true)
			{
				Function.MsgOutput(aIndex, 1, "Você já está registrado no evento. Aguarde.");
				return;
			}

			TheftEvent.PlayerStruct[aIndex]._InEvent = true;
			TheftEvent.PlayerStruct[aIndex]._AttackBlock = true;

			GCMoneySend(aIndex, gObj[aIndex].Money -= TheftEvent._Zen);

			gObj[aIndex].m_PK_Level = 6;
			GCPkLevelSend(aIndex, gObj[aIndex].m_PK_Level);

			gObjTeleport(aIndex, TheftEvent._MapNumber, TheftEvent._X, TheftEvent._Y);

			TheftEvent._Players++;

			BYTE SendEvent[4] = { 0xC1, 0x04, 0xFE, 0x09 };
			DataSend(aIndex, SendEvent, 4);

			gObjInventoryItemSet(aIndex, lpMsg->inventoryPos, -1);
			gObj[aIndex].pInventory[lpMsg->inventoryPos].Clear();
			GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);

			Function.MsgOutput(aIndex, 1, "Você foi registrado no evento. Aguarde...");
		}
		else
		{
			Function.MsgOutput(aIndex, 1, "Nenhum evento inicializado.");
		}
	}
}

int	cFunctions::Rand(int Min, int Max)
{
	if (Min == Max)
	{
		return Min;
	}

	int Rand = rand();

	int Result = Min + Rand / (RAND_MAX / (Max - Min) + 1);

	return Result;
}

void cFunctions::UpdateRank(int aIndex)
{
	if (gObj[aIndex].Type == OBJ_USER)
	{
		if (gObj[aIndex].Custom->Hero > 0)
		{
			Manager.ExecFormat("UPDATE Character Set Hero = Hero + %d Where Name = '%s'", gObj[aIndex].Custom->Hero, gObj[aIndex].Name);

			gObj[aIndex].Custom->Hero = 0;
		}

		if (gObj[aIndex].Custom->Killer > 0)
		{
			Manager.ExecFormat("UPDATE Character Set Killer = Killer + %d Where Name = '%s'", gObj[aIndex].Custom->Killer, gObj[aIndex].Name);

			gObj[aIndex].Custom->Killer = 0;
		}
	}
}

BYTE cFunctions::gObjInventoryInsertItemEx(int aIndex, CItem Item)
{
	int W, H, Width, Height;

	BYTE Blank = 0;

	ItemGetSize(Item.m_Type, Width, Height);

	if (Width == 0 || Height == 0)
	{
		return FALSE;
	}

	for (H = 0; H < 8; H++)
	{
		for (W = 0; W < 8; W++)
		{
			if (*(BYTE*)(gObj[aIndex].pInventoryMap + H * 8 + W) == 255)
			{
				Blank = gObjOnlyInventoryRectCheck(aIndex, W, H, Width, Height);

				if (Blank == 254)
				{
					return -1;
				}

				if (Blank != 255)
				{
					gObj[aIndex].pInventory[Blank] = Item;

					gObjInventoryItemSet(aIndex, Blank, gObj[aIndex].pInventory[Blank].m_Type);
					return Blank;
				}
			}
		}
	}

	return -1;
}

BOOL cFunctions::Position(int aIndex, int MapNumber, int X, int Y, int View)
{
	if (gObj[aIndex].MapNumber != MapNumber)
	{
		return FALSE;
	}

	if (gObj[aIndex].X < (X - View) || gObj[aIndex].X >(X + View) || gObj[aIndex].Y < (Y - View) || gObj[aIndex].Y >(Y + View))
	{
		return FALSE;
	}

	return TRUE;
}

void cFunctions::Thread(void* lpParam)
{
	while (true)
	{
#if(GS_CASTLE == 0)
		BossEvent.Run();
		DeathEvent.Run();
		TheftEvent.Run();
		RaffleEvent.Run();
#endif
		HappyEvent.Run();
		News.Run();

		Sleep(1000);
	}

	_endthread();
}

cFunctions Function;
