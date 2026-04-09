#include "StdAfx.h"

void cConnect::PlayerConnect(int aIndex)
{
	gObj[aIndex].Custom->VipCount = Manager.VipCount(gObj[aIndex].AccountID);

	gObj[aIndex].Custom->ResetCount = Manager.ResetCount(gObj[aIndex].Name);

	Manager.JewelsCount(aIndex, gObj[aIndex].AccountID);

	Manager.CheckBonus(aIndex, gObj[aIndex].AccountID);

	gObj[aIndex].m_Gold = Manager.MoneyGold(gObj[aIndex].AccountID);
	gObj[aIndex].m_Cash = Manager.MoneyCash(gObj[aIndex].AccountID);

	//Manager.CoinCount(aIndex, gObj[aIndex].AccountID);

#if(GS_CASTLE == 0)
	if (gObj[aIndex].Custom->VipCount == 0)
	{
		Function.MsgOutput(aIndex, 0, Message._Buffer[0]);
	}
	else if (gObj[aIndex].Custom->VipCount == 1)
	{
		Function.MsgOutput(aIndex, 0, Message._Buffer[1]);
	}
	else if (gObj[aIndex].Custom->VipCount == 2)
	{
		Function.MsgOutput(aIndex, 0, Message._Buffer[2]);
	}
	else if (gObj[aIndex].Custom->VipCount == 3)
	{
		Function.MsgOutput(aIndex, 0, Message._Buffer[3]);
	}

	if (gObj[aIndex].Authority > 1)
	{
		Function.AllServerAnnounce(Message._Buffer[4], gObj[aIndex].Name);
	}

#else
	Function.MsgOutput(aIndex, 0, Message._Buffer[5]);
#endif
}

cConnect Connect;