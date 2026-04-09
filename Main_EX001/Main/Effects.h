#pragma once
#ifndef __EFFECTS_H__
#define __EFFECTS_H__

#include "Structs.h"
class cEffects
{
public:
	cEffects();
	virtual ~cEffects();
	// ----
	void Load();
	void Init();
	// ----
	static void Draw(LPOBJMODEL Owner, int ObjectId, vec3_t Light, float Alpha, int ItemLevel, int NewOption, int SetOption, int Select, int RenderType);
	// ----
private:
	// ----
	std::vector<pSpriteEffect> m_Sprite;
	std::vector<pCreateEffects> m_Effect;
	std::vector<pParticleEffect> m_Particle;
};

extern cEffects		*&RenderEffect;
extern cEffects		gEffects;

#endif	// __EFFECTS_H__