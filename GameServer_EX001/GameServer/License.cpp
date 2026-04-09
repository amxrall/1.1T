#include "StdAfx.h"

bool cLicense::Load()
{
	GetVolumeInformation("C:\\", NULL, 0, &this->_Serial, NULL, NULL, NULL, 0);

	UUID ID; UuidCreateSequential(&ID);

	for (int i = 2; i < 8; i++)
	{
		this->_Data[i - 2] = ID.Data4[i];
	}

	sprintf(this->_Buffer, "%02X-%02X-%02X-%02X-%02X-%02X", this->_Data[0], this->_Data[1], this->_Data[2], this->_Data[3], this->_Data[4], this->_Data[5]);


    //if (this->Check(this->_Buffer) && this->_Serial == 0x0677D10C) // Local
	//if (this->Check(this->_Buffer) && this->_Serial == 0xA02FF4F0) // MuExcalibur
	if (this->Check(this->_Buffer) && this->_Serial == 0x0C20EE5ED) // Local Wellington

	{
		return true;
	}
	else
	{
		MessageBox(NULL, "Infelizmente sua licença não foi encontrada!\n Por favor, entre em contato.\n\n", "GBTeam Emulador", MB_OK | MB_ICONINFORMATION);
		ExitProcess(0);
	}

	return false;
}

bool cLicense::Check(LPCSTR ID)
{
	char CheckList[13][18] =
	{

		"00-E0-2D-93-DC-C8", //LOCAL
		"60-45-CB-A2-76-F6", //LOCAL2
		"E0-CB-4E-23-57-73", //
		"00-50-56-0A-12-93", // Excalibur
		"E0-D5-5E-45-37-43", // Local Welligton
	};

	for (int i = 0; i < 13; i++)
	{
		if (!strcmp(ID, CheckList[i]))
		{
			return true;
		}
	}

	return false;
}

cLicense License;