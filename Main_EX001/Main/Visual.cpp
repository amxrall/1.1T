#include "StdAfx.h"

void VisualState::Load()
{
	this->Kill = TRUE;
	this->Attack = 0;
	this->aIndex = 0;
	this->Life = 0;
	this->MaxLife = 0;
	this->Mana = 0;
	this->MaxMana = 0;
	this->BP = 0;
	this->MaxBP = 0;

	HookCall(0x59A086, DrawHP);
	HookCall(0x59A0AD, DrawMP);
	HookCall(0x598978, DrawAG);
	HookCall(0x599382, DrawTabHP);
	HookCall(0x59944A, DrawTabMP);
	HookCall(0x5989D3, DrawTabAG);
	HookCall(0x5DEA6F, InfoHP);
	HookCall(0x5DEB82, InfoMP);
	HookJump(0x5703B1, CheckMP1);
	HookJump(0x573723, CheckMP2);
	HookJump(0x57A4E1, CheckMP3);
	HookJump(0x5834AA, CheckMP4);
	HookJump(0x54E3A8, CheckBP1);
	HookJump(0x556983, CheckBP2);
	HookJump(0x573E76, CheckBP3);
	HookJump(0x583C87, CheckBP4);
}

void VisualState::Index(PMSG_JOINRESULT* Data)
{
	this->aIndex = MAKE_NUMBERW(Data->NumberH, Data->NumberL);
	this->Kill = FALSE;
}

void VisualState::RecvDamage(PMSG_ATTACKRESULT * Data)
{
	this->Attack = Data->AttackDamage;

	if (this->aIndex == MAKE_NUMBERW(Data->NumberH, Data->NumberL))
	{
		this->Life -= this->Attack;

		if (this->Life < 0)
		{
			this->Life = 0;
		}
	}
}

void VisualState::RecvHP(PMSG_REFILL* Data)
{
	if (Data->IPos == 0xFF)
	{
		this->Life = Data->Life;
	}
	else if (Data->IPos == 0xFE)
	{
		this->MaxLife = Data->Life;
	}

	if (this->Life > this->MaxLife)
	{
		this->Life = this->MaxLife;
	}

	if (this->Kill == TRUE)
	{
		this->Life = 0;
	}
}

void VisualState::RecvMP(PMSG_MANASEND* Data)
{
	if (Data->IPos == 0xFF)
	{
		this->Mana = Data->Mana;
		this->BP = Data->BP;
	}

	else if (Data->IPos == 0xFE)
	{
		this->MaxMana = Data->Mana;
		this->MaxBP = Data->BP;
	}

	if (this->Mana > this->MaxMana)
	{
		this->Mana = this->MaxMana;
	}
}

void VisualState::Respawn()
{
	this->Kill = FALSE;

	this->Life = this->MaxLife;
	this->Mana = this->MaxMana;
	this->BP = this->MaxBP;
}

void VisualState::Killed(PMSG_DIEPLAYER* Data)
{
	short tIndex = MAKE_NUMBERW(Data->NumberH, Data->NumberL);

	if (this->aIndex == tIndex)
	{
		this->Life = 0;
		this->Kill = TRUE;
	}
}

void VisualState::DrawDamageHP(int a1, int a2, int a3, float a4, char a5, char a6)
{
	DrawDamage(a1, Visual.Attack, a3, a4, a5, a6);
}

void VisualState::DrawHP(float PosX, float PosY, int Value, float ScaleX, float ScaleY)
{
	DrawBar(PosX + 24.0f, PosY, Visual.Life, ScaleX, ScaleY);
}

void VisualState::DrawMP(float PosX, float PosY, int Value, float ScaleX, float ScaleY)
{
	DrawBar(PosX - 15.0f, PosY, Visual.Mana, ScaleX, ScaleY);
}

void VisualState::DrawAG(float PosX, float PosY, int Value, float ScaleX, float ScaleY)
{
	DrawBar(PosX - 6.0f, PosY, Visual.BP, ScaleX, ScaleY);
}

void VisualState::DrawTabHP(int PosX, int PosY, LPCSTR lpString)
{
	sprintf_s(Visual.Buffer[0], "Life: %d/%d", Visual.Life, Visual.MaxLife);

	DrawTab(PosX, PosY, Visual.Buffer[0]);
}

void VisualState::DrawTabMP(int PosX, int PosY, LPCSTR lpString)
{
	sprintf_s(Visual.Buffer[1], "Mana: %d/%d", Visual.Mana, Visual.MaxMana);

	DrawTab(PosX, PosY, Visual.Buffer[1]);
}

void VisualState::DrawTabAG(int PosX, int PosY, LPCSTR lpString)
{
	sprintf_s(Visual.Buffer[2], "AG: %d/%d", Visual.BP, Visual.MaxBP);

	DrawTab(PosX, PosY, Visual.Buffer[2]);
}

void VisualState::InfoHP(int a1, int a2, LPCSTR a3, int a4, char a5, int a6)
{
	sprintf_s(Visual.Buffer[4], "Life: %d/%d", Visual.Life, Visual.MaxLife);

	DrawInfo(a1, a2, Visual.Buffer[4], a4, a5, a6);
}

void VisualState::InfoMP(int a1, int a2, LPCSTR a3, int a4, char a5, int a6)
{
	sprintf_s(Visual.Buffer[5], "Mana: %d/%d", Visual.Mana, Visual.MaxMana);

	DrawInfo(a1, a2, Visual.Buffer[5], a4, a5, a6);
}

__declspec(naked) void VisualState::CheckMP1()
{
	static DWORD Local = 0x5703B7;

	__asm
	{
		MOV EDX, Visual.Mana;
		CMP ECX, EDX;
		JMP Local;
	}
}

__declspec(naked) void VisualState::CheckMP2()
{
	static DWORD Local = 0x573729;

	__asm
	{
		MOV EDX, Visual.Mana;
		CMP ECX, EDX;
		JMP Local;
	}
}

__declspec(naked) void VisualState::CheckMP3()
{
	static DWORD Local = 0x57A4E7;

	__asm
	{
		MOV EDX, Visual.Mana;
		CMP ECX, EDX;
		JMP Local;
	}
}

__declspec(naked) void VisualState::CheckMP4()
{
	static DWORD Local = 0x5834B0;

	__asm
	{
		MOV ECX, Visual.Mana;
		CMP EDX, ECX;
		JMP Local;
	}
}

__declspec(naked) void VisualState::CheckBP1()
{
	static DWORD Local = 0x54E3AE;

	__asm
	{
		XOR EDX, EDX;
		MOV EDX, Visual.BP;
		JMP Local;
	}
}

__declspec(naked) void VisualState::CheckBP2()
{
	static DWORD Local = 0x556989;

	__asm
	{
		XOR ECX, ECX;
		MOV ECX, Visual.BP;
		JMP Local;
	}
}

__declspec(naked) void VisualState::CheckBP3()
{
	static DWORD Local = 0x573E7C;

	__asm
	{
		XOR ECX, ECX;
		MOV ECX, Visual.BP;
		JMP Local;
	}
}

__declspec(naked) void VisualState::CheckBP4()
{
	static DWORD Local = 0x583C8D;

	__asm
	{
		XOR ECX, ECX;
		MOV ECX, Visual.BP;
		JMP Local;
	}
}

VisualState Visual;