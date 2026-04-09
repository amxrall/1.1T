//#ifndef _WING_MANAGER_H
//#define _WING_MANAGER_H

#pragma once
#define ITEM_ATTRIBUTE_ADDR									0x203
//--------
#define MIN_WING_INDEX										0x24
#define MAX_WING_INDEX										0x64
//--------
#define MIN_WING_ITEMID										0x1824
#define MAX_WING_ITEMID										0x1864
//--------
#define MIN_WING_ITEMID2									0x1824+ITEM_ATTRIBUTE_ADDR
#define MAX_WING_ITEMID2									0x1864+ITEM_ATTRIBUTE_ADDR
//--------
const int WING_ID = 0x203;
//--------
#define ITEMGET2(x, y) (x * 512 + y) + WING_ID
#define ITEMGET(x, y) (x * 512 + y)
//--------
#define GET_ITEMTYPE(x)				((x)/512)
#define GET_ITEMINDEX(x)			((x)%512)
//--------
#define pItemSetOptionAdd ((void(*)(LPVOID, unsigned __int8, unsigned __int8, BYTE))0x00540A50)//005493F0  /$ 55             PUSH EBP


//class CWingManager
//{
//public:
//	void Load();
//	// ---
//
//	static void Add28Option();
//};
//
//extern CWingManager gWingManager;

//#endif
void ReadyNewWings();
void ItemSetOptions(LPVOID ItemStruct, unsigned __int8 Option, unsigned __int8 Special, BYTE Value);
