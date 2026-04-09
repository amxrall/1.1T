#pragma once

#define ITEM_ATTRIBUTE_ADDR									0x203
//--------
#define MIN_WING_INDEX										0x24 // 36
#define MAX_WING_INDEX										0x64 // 100
//--------
#define MIN_WING_ITEMID										0x1824 // 35 Wings
#define MAX_WING_ITEMID										0x1864 //0x192C 300 Wings
//--------
#define MIN_WING_ITEMID2									0x1824+ITEM_ATTRIBUTE_ADDR
#define MAX_WING_ITEMID2									0x1864+ITEM_ATTRIBUTE_ADDR
//--------
#define ITEMGET2(x, y) (x * 512 + y) + WING_ID
#define ITEMGET(x, y) (x * 512 + y)
//--------
#define GET_ITEMTYPE(x)				((x)/512)
#define GET_ITEMINDEX(x)			((x)%512)
//--------
#define ITEMGET2(x, y) (x * 512 + y) + WING_ID
#define WING_CHARSET 17
#define ITEM_BASE_MODEL	515
#define ITEM_ATTRIBUTE_ADDR 0x203
#define MAX_ITEM_TYPE 512
#define ITEM(x,y)				((x*512)+y)
#define GET_ITEM(x,y)			(((x)*512)+(y))
#define MIN_WING_INDEX										0x24
#define ITEM_ID(x,y)			((x*512)+y+515)
#define pInitModelData			((void(__cdecl*)()) 0x005FD0E0)
#define pInitTextureData		((void(__cdecl*)()) 0x005FE910)
#define pMakePreviewCharSet     ((void(*)(int aIndex, BYTE * CharSet, int PreviewObject, int Mode, int Agr5, int Agr6, int Agr7)) 0x0050A590)
#define _MakePreviewCharSet		((void(__cdecl*)(int aIndex,BYTE *CharSet,int Struct,int Mode))0x50A590)
#define pItemSetOptionAdd ((void(*)(LPVOID, unsigned __int8, unsigned __int8, BYTE))0x540A50)//005493F0  /$ 55             PUSH EBP
// ---

#define gObjItemGlow		((void(__cdecl*)(int ObjectId, float Arg2, float Arg3, vec3_t Color, bool Mode)) 0x005F6220)
#define gObjItemShine		((void(__cdecl*)(int ObjectId, float Arg2, float Arg3, vec3_t Color, bool Mode)) 0x005F67F0)

#define GET_ITEM_MODEL(x,y) ((((x)*MAX_ITEM_TYPE)+(y))+ITEM_ATTRIBUTE_ADDR)

void InitItem();
void InitJewel();
void ItemModelLoad();
void ItemTextureLoad();
void LoadItemModel(int index, char* folder, char* name, int value);
void LoadItemTexture(int index, char* folder, char* name, int value);
void GetItemColor(DWORD a, DWORD b, DWORD c, DWORD d, DWORD e);
void LoadJewelUpgrade();
void LoadJewelApply();
void FixBoxTexture();

