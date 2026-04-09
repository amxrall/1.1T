#pragma once

void ItemView();

#define OBJ_OFFS (0x203)

const int WeaponViewCheck_Hook = 0x005048CA; //OK
const int WeaponViewCheck_Ret = 0x00504962; //OK

#define RightHandFixup 0x2A8 //OK
#define LeftHandFixup 0x2C8 //OK

#define WeaponViewFlagFixup +0x13 //OK

#define SafeZoneFlagFixup -0x1C // OK


const int SecondWeaponViewCheckReplacedCode_Hook = 0x00504A4F; //00504A4F  |> A1 488D6B00    MOV EAX,DWORD PTR DS:[6B8D48]

const int SecondWeaponViewCheck_Hook1 = 0x005049BB + 1; //005049BB  |. 0F84 8E000000  JE main.00504A4F

const int SecondWeaponViewCheck_Hook2 = 0x005049C4 + 1; //005049C4  |. 0F84 85000000  JE main.00504A4F

const int SecondWeaponViewCheck_Ret = 0x00504A54; // OK  |. 83F8 0B        CMP EAX,0B

const int SecondWeaponViewFix_Hook = 0x005002E8; //005002E8  |. 68 FC198B06    PUSH main.068B19FC                       ; /Arg3 = 068B19FC
const int SecondWeaponViewFix_Ret = 0x005002ED; //005002ED  |. 50             PUSH EAX                                 ; |Arg2

#define SomeVal4 0x68B19FC //OK

const int RotateFunc = 0x005EAE50; //005001CA  |. E8 81AC0E00    CALL main.005EAE50                       ; \main.005EAE50
const int TransFunc = 0x005EAFF0; // OK

#define RotFixup (-0x30)
#define TransFixup (-0x64)

#define OLD_MAIN

#define STACK_PTR EBP
#define CHAR_REG ESI
#define WEAPON_ID_CONTAINER EDI

#ifdef OLD_MAIN
#define MAX_ITEM2 (512)
#else
#define MAX_ITEM (512)
#define STACK_PTR EBP
#define WEAPON_ID_CONTAINER DWORD PTR SS:[EBP+0x1C]
#endif


#define MAKE_ITEM(type, index) (type*MAX_ITEM2 + index)