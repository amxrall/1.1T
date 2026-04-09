// Protect.cpp: implementation of the CProtect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CRC.h"

CProtect gProtect;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProtect::CProtect() // OK
{

}

CProtect::~CProtect() // OK
{

}

bool CProtect::Load(char* szName)
{
	CCRC32 CRC32;
	// ---
	if (CRC32.FileCRC(szName, &this->m_FileCrc, 1024) == 0)
	{
		return 0;
	}
	// ---
	HANDLE szFile = CreateFile(szName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, 0);
	// ---
	if (szFile == INVALID_HANDLE_VALUE)
	{
		return 0;
	}
	// ---
	if (GetFileSize(szFile, NULL) != sizeof(PROTECT_DATA))
	{
		CloseHandle(szFile);
		return 0;
	}
	// ---
	DWORD OutSize = 0;
	// ---
	if (ReadFile(szFile, &this->m_Data, sizeof(PROTECT_DATA), &OutSize, NULL) == NULL)
	{
		CloseHandle(szFile);
		return 0;
	}
	// ---
	for (int n = 0; n < sizeof(PROTECT_DATA); n++)
	{
		((BYTE*)&this->m_Data)[n] += (BYTE)(0x95 ^ HIBYTE(n));
		((BYTE*)&this->m_Data)[n] ^= (BYTE)(0xCA ^ LOBYTE(n));
	}
	// ---
	CloseHandle(szFile);
	return 1;
}
void CProtect::CheckClientFile() // OK
{
	if (this->m_Data.ClientCRC32 == 0)
	{
		return;
	}

	char name[MAX_PATH] = { 0 };

	if (GetModuleFileName(0, name, sizeof(name)) == 0)
	{
		ExitProcess(0);
	}

	if (_stricmp(ConvertModuleFileName(name), this->m_Data.ClientName) != 0)
	{
		ExitProcess(0);
	}

	CCRC32 CRC32;

	DWORD ClientCRC32;

	if (CRC32.FileCRC(this->m_Data.ClientName, &ClientCRC32, 1024) == 0)
	{
		MessageBox(0, "Main.exe CRC error!", "Error", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}

	if (this->m_Data.ClientCRC32 != ClientCRC32)
	{
		MessageBox(0, "Main.exe CRC error!", "Error", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}
}

void CProtect::CheckPlugin1File() // OK
{
	if (this->m_Data.Plugin1CRC32 == 0)
	{
		return;
	}

	CCRC32 CRC32;

	DWORD Plugin1CRC32;

	if (CRC32.FileCRC(this->m_Data.PluginName1, &Plugin1CRC32, 1024) == 0)
	{
		MessageBox(0, "Plugin 1 CRC error!", "Error", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}

	if (this->m_Data.Plugin1CRC32 != Plugin1CRC32)
	{
		ExitProcess(0);
	}

	HMODULE module = LoadLibrary(this->m_Data.PluginName1);

	if (module == 0)
	{
		ExitProcess(0);
	}

	void(*EntryProc)() = (void(*)())GetProcAddress(module, "EntryProc");

	if (EntryProc != 0)
	{
		EntryProc();
	}
}

void CProtect::CheckPlugin2File() // OK
{
	if (this->m_Data.Plugin2CRC32 == 0)
	{
		return;
	}

	CCRC32 CRC32;

	DWORD Plugin2CRC32;

	if (CRC32.FileCRC(this->m_Data.PluginName2, &Plugin2CRC32, 1024) == 0)
	{
		MessageBox(0, "Plugin 2 CRC error!", "Error", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}

	if (this->m_Data.Plugin2CRC32 != Plugin2CRC32)
	{
		ExitProcess(0);
	}

	HMODULE module = LoadLibrary(this->m_Data.PluginName2);

	if (module == 0)
	{
		ExitProcess(0);
	}

	void(*EntryProc)() = (void(*)())GetProcAddress(module, "EntryProc");

	if (EntryProc != 0)
	{
		EntryProc();
	}
}