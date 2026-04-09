#include "StdAfx.h"

BOOL cProtocol::ProtocolCoreEx(int unk1, LPBYTE lpRecv, int unk2, int unk3)
{
	BYTE Head = lpRecv[(lpRecv[0] == 0xC2 || lpRecv[0] == 0xC4) ? 3 : 2];
	BYTE SubCode = lpRecv[(lpRecv[0] == 0xC2 || lpRecv[0] == 0xC4) ? 4 : 3];

	switch (Head)
	{
	case 0xD7:
	{
		Visual.RecvDamage((PMSG_ATTACKRESULT*)lpRecv);
	}
	break;
	case 0x17:
	{
		Visual.Killed((PMSG_DIEPLAYER*)lpRecv);
	}
	break;
	case 0x26:
	{
		Visual.RecvHP((PMSG_REFILL*)lpRecv);
	}
	break;
	case 0x27:
	{
		Visual.RecvMP((PMSG_MANASEND*)lpRecv);
	}
	break;
	case 0xF1:
	{
		switch (SubCode)
		{
		case 0x00:
		{
			Visual.Index((PMSG_JOINRESULT*)lpRecv);
		}
		break;
		}
	}
	break;
	case 0xF3:
	{
		switch (SubCode)
		{
		case 0x03:
		{
			Visual.Respawn();

			Protocol.Agility();

			Protocol.InEvent = false;
		}
		break;
		case 0x04:
		{
			Visual.Respawn();
		}
		break;
		case 0x05:
		{
			Protocol.Update = false;
		}
		break;
		case 0x06:
		{
			Protocol.Update = false;
			Protocol.RealLevelUpPoint--;
		}
		break;
		case 0xE2:
		{
			HPBar.Clear();

			PMSG_HEALTHBAR* lpMsg = (PMSG_HEALTHBAR*)(lpRecv);

			for (int i = 0; i < lpMsg->Count; i++)
			{
				PMSG_HEALTHBAR_INFO* Info = (PMSG_HEALTHBAR_INFO*)(&lpRecv[sizeof(PMSG_HEALTHBAR) + (sizeof(PMSG_HEALTHBAR_INFO) * i)]);
				HPBar.Insert(Info->Index, Info->Rate);
			}
		}
		break;
		}
	}
	break;
	case 0xFE:
	{
		switch (SubCode)
		{
		case 0x01:
		{
			PMSG_LEVELUP Result;
			PMSG_UPDATECHARACTER* Info = (PMSG_UPDATECHARACTER*)(lpRecv);

			Protocol.Update = true;
			Protocol.Level = Info->Level;
			Protocol.LevelUpPoint = Info->LevelUpPoint;
			Protocol.RealLevelUpPoint = Info->LevelUpPoint;
			Protocol.Experience = Info->Experience;
			Protocol.NextExperience = Info->NextExperience;
			Protocol.Strength = Info->Strength;
			Protocol.Dexterity = Info->Dexterity;
			Protocol.Vitality = Info->Vitality;
			Protocol.Energy = Info->Energy;
			Protocol.Leadership = Info->Leadership;
			Protocol.Life = Info->Life;
			Protocol.MaxLife = Info->MaxLife;
			Protocol.Mana = Info->Mana;
			Protocol.MaxMana = Info->MaxMana;
			Protocol.BP = Info->BP;
			Protocol.MaxBP = Info->MaxBP;
			Visual.Life = Info->MaxLife;
			Visual.Mana = Info->MaxMana;
			Visual.BP = Info->MaxBP;

			Result.h.c = 0xC1;
			Result.h.size = sizeof(Result);
			Result.h.headcode = 0xF3;
			Result.subcode = 0x05;

			LevelUpRecv(&Result);
		}
		break;
		case 0x02:
		{
			PMSG_LVPOINTADDRESULT Result;
			PMSG_UPDATECHARACTER* Info = (PMSG_UPDATECHARACTER*)(lpRecv);

			Protocol.Update = true;
			Protocol.LevelUpPoint = Info->LevelUpPoint + 1;
			Protocol.RealLevelUpPoint = Info->LevelUpPoint;
			Protocol.Strength = Info->Strength - 1;
			Protocol.Dexterity = Info->Dexterity;
			Protocol.Vitality = Info->Vitality;
			Protocol.Energy = Info->Energy;
			Protocol.Leadership = Info->Leadership;
			Protocol.Life = Info->Life;
			Protocol.MaxLife = Info->MaxLife;
			Protocol.Mana = Info->Mana;
			Protocol.MaxMana = Info->MaxMana;
			Protocol.BP = Info->BP;
			Protocol.MaxBP = Info->MaxBP;
			Visual.Life = Info->MaxLife;
			Visual.Mana = Info->MaxMana;
			Visual.BP = Info->MaxBP;

			Result.h.c = 0xC1;
			Result.h.size = sizeof(Result);
			Result.h.headcode = 0xF3;
			Result.subcode = 0x06;
			Result.ResultType = 0x10;
			Result.MaxLifeAndMana = Info->MaxLife;
			Result.MaxBP = Info->MaxBP;

			LevelUpAddPoint(&Result);
		}
		break;
		case 0x07:
		{
			PMSG_CHARINFOMAIN* Info = (PMSG_CHARINFOMAIN*)(lpRecv);

			Protocol.Class = Info->Class;
			Protocol.RealLevelUpPoint = Info->LevelUpPoint;
		}
		break;
		case 0x08:
		{
			PMSG_UPDATEPOINTS* Info = (PMSG_UPDATEPOINTS*)(lpRecv);

			Protocol.RealLevelUpPoint = Info->LevelUpPoint;
		}
		break;
		case 0x09:
			Protocol.InEvent = true;
			break;
		case 0x0A:
			Protocol.InEvent = false;
			break;
		}
	}
	break;
	}

	return ProtocolCore(unk1, lpRecv, unk2, unk3);
}

DWORD UpdateCharacterNoEffectBack = 0x4CC645;
__declspec(naked) void cProtocol::UpdateCharacterNoEffect()
{
	__asm PUSHAD;

	if (Protocol.Update == true)
	{
		__asm
		{
			POPAD;

			MOV EAX, DWORD PTR DS : [0x7666A78];

			MOV CX, Protocol.Strength;
			MOV WORD PTR DS : [EAX + 0x18], CX;

			MOV CX, Protocol.Dexterity;
			MOV WORD PTR DS : [EAX + 0x1A], CX;

			MOV CX, Protocol.Vitality;
			MOV WORD PTR DS : [EAX + 0x1C], CX;

			MOV CX, Protocol.Energy;
			MOV WORD PTR DS : [EAX + 0x1E], CX;

			MOV CX, Protocol.Leadership;
			MOV WORD PTR DS : [EAX + 0x20], CX;

			MOV CX, Protocol.Life;
			MOV WORD PTR DS : [EAX + 0x22], CX;

			MOV CX, Protocol.MaxLife;
			MOV WORD PTR DS : [EAX + 0x26], CX;

			MOV CX, Protocol.Mana;
			MOV WORD PTR DS : [EAX + 0x24], CX;

			MOV CX, Protocol.MaxMana;
			MOV WORD PTR DS : [EAX + 0x28], CX;

			MOV CX, Protocol.BP;
			MOV WORD PTR DS : [EAX + 0x38], CX;

			MOV CX, Protocol.MaxBP;
			MOV WORD PTR DS : [EAX + 0x3A], CX;

			MOV WORD PTR DS : [EAX + 0x44], 0;		// StatPoint
			MOV WORD PTR DS : [EAX + 0x46], 0;		// MaxStatPoint

			MOV CX, Protocol.LevelUpPoint;
			MOV WORD PTR DS : [EAX + 0x68], CX;

			JMP UpdateCharacterNoEffectBack;
		}
	}

	__asm
	{
		POPAD;
		MOV EAX, DWORD PTR DS : [0x7666A78];
		JMP UpdateCharacterNoEffectBack;
	}
}

DWORD UpdateCharacterEffectBack[2] = { 0x4CC416, 0x4CC3C6 };
__declspec(naked) void cProtocol::UpdateCharacterEffect()
{
	__asm PUSHAD;

	if (Protocol.Update == true)
	{
		__asm
		{
			POPAD;
			MOV EAX, DWORD PTR DS : [0x7666A78];

			MOV CX, Protocol.Level;
			MOV WORD PTR DS : [EAX + 0x0E], CX;

			MOV EDX, Protocol.Experience;
			MOV DWORD PTR DS : [EAX + 0x10], EDX;

			MOV EDX, Protocol.NextExperience;
			MOV DWORD PTR DS : [EAX + 0x14], EDX;

			MOV CX, Protocol.Strength;
			MOV WORD PTR DS : [EAX + 0x18], CX;

			MOV CX, Protocol.Dexterity;
			MOV WORD PTR DS : [EAX + 0x1A], CX;

			MOV CX, Protocol.Vitality;
			MOV WORD PTR DS : [EAX + 0x1C], CX;

			MOV CX, Protocol.Energy;
			MOV WORD PTR DS : [EAX + 0x1E], CX;

			MOV CX, Protocol.Leadership;
			MOV WORD PTR DS : [EAX + 0x20], CX;

			MOV CX, Protocol.Life;
			MOV WORD PTR DS : [EAX + 0x22], CX;

			MOV CX, Protocol.MaxLife;
			MOV WORD PTR DS : [EAX + 0x26], CX;

			MOV CX, Protocol.Mana;
			MOV WORD PTR DS : [EAX + 0x24], CX;

			MOV CX, Protocol.MaxMana;
			MOV WORD PTR DS : [EAX + 0x28], CX;

			MOV CX, Protocol.BP;
			MOV WORD PTR DS : [EAX + 0x38], CX;

			MOV CX, Protocol.MaxBP;
			MOV WORD PTR DS : [EAX + 0x3A], CX;

			MOV WORD PTR DS : [EAX + 0x44], 0;  // StatPoint
			MOV WORD PTR DS : [EAX + 0x46], 0;  // MaxStatPoint

			MOV CX, Protocol.LevelUpPoint;
			MOV WORD PTR DS : [EAX + 0x68], CX;

			JMP UpdateCharacterEffectBack[0];
		}
	}

	__asm
	{
		POPAD;
		MOV EAX, DWORD PTR DS : [0x7666A78];
		JMP UpdateCharacterEffectBack[4];
	}
}

__declspec(naked) void cProtocol::LevelUpPoints()
{
	static DWORD Local = 0x5DEE8E;

	__asm
	{
		MOV EAX, Protocol.RealLevelUpPoint;
		PUSH EAX;
		JMP Local;
	}
}

bool cProtocol::Skills(int Id)
{
	if (Id == 6 || Id == 15)
	{
		if (Protocol.InEvent)
		{
			return false;
		}
	}

	return ((bool(*)(int))(0x5951F0))(Id);
}

void cProtocol::Agility()
{
	switch (Protocol.Class)
	{
	case 0:
		*(BYTE*)(0x4F0B7D + 6) = 0x02;
		break;
	case 1:
		*(BYTE*)(0x4F0B7D + 6) = 0x0F;
		break;
	case 2:
		*(BYTE*)(0x4F11E1 + 6) = 0x02;
		break;
	case 3:
		*(BYTE*)(0x4F0B7D + 6) = 0x02;
		break;
	case 4:
		*(BYTE*)(0x4F0B7D + 6) = 0x02;
		break;
	}
}

cProtocol Protocol;