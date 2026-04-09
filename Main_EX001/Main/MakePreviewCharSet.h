#pragma once

void     ReadMakePreviewCharSet();

void    _WingsCharSet(int aIndex, BYTE *CharSet, int Struct, int Mode);

#define _MakePreviewCharSets	((void(__cdecl*)(int aIndex,BYTE *CharSet,int Struct,int Mode))0x0050A590)