#ifndef __PETSMANAGER_H__
#define __PETSMANAGER_H__

//void *__cdecl sub_43EDA0(int a1)
typedef void*(__cdecl *Objsub_43EDA0)(int a1);
extern Objsub_43EDA0 sub_43EDA0;

//char __cdecl sub_43EDD0(__int16 a1, int a2, int a3, int a4, int a5)
typedef char(__cdecl *Objsub_43EDD0)(int a1, DWORD a2, DWORD a3, int a4, int a5);
extern Objsub_43EDD0 sub_43EDD0;

//char __cdecl sub_43EFF0(int a1, int a2, int a3, int a4)
typedef char(__cdecl *Objsub_43EFF0)(int a1, DWORD a2, DWORD a3, int a4);
extern Objsub_43EFF0 sub_43EFF0;

//int __cdecl sub_4038D0(int a1)
typedef int(__cdecl *Objsub_4038D0)(int a1);
extern Objsub_4038D0 sub_4038D0;

//int __cdecl sub_5094D0(int a1)
typedef int(__cdecl *Objsub_5094D0)(int a1);
extern Objsub_5094D0 sub_5094D0;

//signed int __cdecl sub_507C70(int a1)
typedef int(__cdecl *Objsub_507C70)(int a1);
extern Objsub_507C70 sub_507C70;

//int __cdecl sub_53FEC0(int a1)
typedef int(__cdecl *Objsub_53FEC0)(int a1);
extern Objsub_53FEC0 sub_53FEC0;

class CPetsManager
{
public:
	CPetsManager();
	// ----
	void Init();
	void Load();
	void Call();
	// ----
	void Initialize();
	void InitPetEffects();
	// ----
	void InitializePets();
	void InitPetMuunSystem();
	// ----
	static DWORD CreatePet(DWORD dwModel, BOOL bType);
	static void RenderPet(short *a1, int a2, int a3, int a4, OBJMODEL *Inventory, char *a6);
	static void RefreshPetASM();
	static void MoveBugHook(int a1, float Velocity);
	static void PetFollowCharacterRun(int a1, float MaxPos);
	static void PetFollowCharacterFly(int a1, float MaxPos);
	static void Draw_RenderObject(int a1, int a2, int a3, int a4);
	static int PreviewCharSetHook(int a1, BYTE*CharSet, int a3, int a4, BYTE a5, int a6, BYTE*Mode);
	// ----
	static int CheckMuun(WORD wItemID);
	static int IsPetMuun(int pObject);
	static int CreateMuun(WORD wItemID);
	// ----
	DWORD PetTickCount;
	int iMuunPetCount;
	CustomPets m_Muun[MAX_CUSTOM_ITEMS];
	// ----
private:
	// ----
	std::vector<pPetSpriteEffect> m_PetSprite;
	std::vector<pPetCreateEffects> m_PetEffect;
	std::vector<pPetParticleEffect> m_PetParticle;
};

extern CPetsManager gPetsManager;

#endif	// __PETSMANAGER_H__