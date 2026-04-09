#include "StdAfx.h"

void cInterface2::Load()
{
	//this->COMANDOS_D = GetPrivateProfileInt("INTERFACE", "Desativar_Interface_COMANDOS_D", 0, "./Data/Customs/Settings.txt");
	if (gProtect.m_Data.COMANDOS_D != 0)
	{
		*(BYTE*)(0x594B18 + 1) = 0x2F;

		// - COMMAND FUNCTION

		*(BYTE*)(0x59028D) = 0x90;
		*(BYTE*)(0x59028D + 1) = 0x90;
		*(BYTE*)(0x59028D + 2) = 0x90;
		*(BYTE*)(0x59028D + 3) = 0x90;
		*(BYTE*)(0x59028D + 4) = 0x90;

		// - COMMAND TEXT

		*(BYTE*)(0x408ADF) = 0x90;
		*(BYTE*)(0x408ADF + 1) = 0x90;
		*(BYTE*)(0x408ADF + 2) = 0x90;
		*(BYTE*)(0x408ADF + 3) = 0x90;
		*(BYTE*)(0x408ADF + 4) = 0x90;
	}
	//this->COMANDOS_M = GetPrivateProfileInt("INTERFACE", "Desativar_Interface_Moves_M", 0, "./Data/Customs/Settings.txt");
	if (gProtect.m_Data.COMANDOS_M != 0)
	{
		// letra M
		SetNop(0x5A08D9, 5);
	}

	//this->COMANDOS_F = GetPrivateProfileInt("INTERFACE", "Desativar_Interface_Friend", 0, "./Data/Customs/Settings.txt");
	if (gProtect.m_Data.COMANDOS_F != 0)
	{ 
	// - Remove F

	*(BYTE*)(0x594AA6 + 1) = 0x2F;

	// - FRIEND FUNCTION

	*(BYTE*)(0x590237) = 0x90;
	*(BYTE*)(0x590237 + 1) = 0x90;
	*(BYTE*)(0x590237 + 2) = 0x90;
	*(BYTE*)(0x590237 + 3) = 0x90;
	*(BYTE*)(0x590237 + 4) = 0x90;

	// - FRIEND TEXT

	*(BYTE*)(0x599764) = 0x90;
	*(BYTE*)(0x599764 + 1) = 0x90;
	*(BYTE*)(0x599764 + 2) = 0x90;
	*(BYTE*)(0x599764 + 3) = 0x90;
	*(BYTE*)(0x599764 + 4) = 0x90;
	}

	//this->COMANDOS_S = GetPrivateProfileInt("INTERFACE", "Desativar_Interface_PShop", 0, "./Data/Customs/Settings.txt");
	if (gProtect.m_Data.COMANDOS_S != 0)
	{
		// - Remove S

		*(BYTE*)(0x5D3DF6 + 1) = 0x2F;
		
		// - PSHOP FUNCTION

		*(BYTE*)(0x5D3DB6) = 0x90;
		*(BYTE*)(0x5D3DB6 + 1) = 0x90;
		*(BYTE*)(0x5D3DB6 + 2) = 0x90;
		*(BYTE*)(0x5D3DB6 + 3) = 0x90;
		*(BYTE*)(0x5D3DB6 + 4) = 0x90;

		// - PSHOP GRAPHICAL

		*(BYTE*)(0x5E14A2) = 0xE9;
		*(BYTE*)(0x5E14A2 + 1) = 0x28;
		*(BYTE*)(0x5E14A2 + 2) = 0x02;
		*(BYTE*)(0x5E14A2 + 3) = 0x00;
		*(BYTE*)(0x5E14A2 + 4) = 0x00;
		*(BYTE*)(0x5E14A2 + 5) = 0x90;
	}



	//this->COMANDOS_T = GetPrivateProfileInt("INTERFACE", "Desativar_Interface_Quest", 0, "./Data/Customs/Settings.txt");
	if (gProtect.m_Data.COMANDOS_T != 0)
	{
		// - Remove T

		*(BYTE*)(0x5949BF + 1) = 0x2F;
		
		// - QUEST GRAPHICAL

		SetNop(0x41AFDB, 5);
		SetNop(0x41B019, 5);
		SetNop(0x41B01E, 5);
		SetNop(0x41B052, 5);
		SetNop(0x419B62, 2);
		SetNop(0x419B6B, 5);

	}

	//this->COMANDOS_PET = GetPrivateProfileInt("INTERFACE", "Desativar_Interface_Mascote", 0, "./Data/Customs/Settings.txt");
	if (gProtect.m_Data.COMANDOS_PET != 0)
	{
		// - PET GRAPHICAL

		SetNop(0x5E5C55, 5);
		SetNop(0x422CD2, 5);
	}
	//this->COMANDOS_SETOPTION = GetPrivateProfileInt("INTERFACE", "Desativar_Interface_SetOption", 0, "./Data/Customs/Settings.txt");
	if (gProtect.m_Data.COMANDOS_SETOPTION != 0)
	{
		// - SET OPTION

		*(BYTE*)(0x40CBE0) = 0xC3;
		SetNop(0x40CC28, 5);
		SetNop(0x40CCEA, 5);
	}

};
cInterface2 Interface2;