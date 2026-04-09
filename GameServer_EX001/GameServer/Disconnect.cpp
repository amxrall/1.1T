#include "StdAfx.h"

bool cDisconnect::Check(int aIndex)
{
	if (!Disconnect.DisconnectStruct[aIndex]._Send)
	{
		return false;
	}

	if (Disconnect.DisconnectStruct[aIndex]._Timer <= 0)
	{
		Disconnect.DisconnectStruct[aIndex]._Timer = GetTickCount();
	}

	if (Disconnect.DisconnectStruct[aIndex]._Count >= 500)
	{
		DWORD Timer = (GetTickCount() - Disconnect.DisconnectStruct[aIndex]._Timer) / 1000;

		if (Timer <= 1)
		{
			Disconnect.DisconnectStruct[aIndex]._Send = false;

			gObjCloseSet(aIndex, 0);
		}
		else
		{
			Disconnect.DisconnectStruct[aIndex]._Count = 0;
			Disconnect.DisconnectStruct[aIndex]._Timer = GetTickCount();
		}
	}

	Disconnect.DisconnectStruct[aIndex]._Count++;

	return true;
}

cDisconnect Disconnect;