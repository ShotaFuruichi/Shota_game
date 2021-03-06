////////////////////////////////////////////////////////////////////////////////
//
//Contents	: UIÌ [UI.h]
//Author	: ShotaFuruichi
//Since		: 2021/02/17
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _UI_H_
#define _UI_H_
#include "main.h"

////////////////////////////////////////////////////////////////////////////////
//UIÌñ^
////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	UI_HP = 0,			//ÌÍ
	UI_MP,				//mp
	UI_ENEMYHP,			//GÌÌÍ
	UI_HPGAUGE,			//Og
	UI_MPGAUGE,			//Og
	UI_ENEMYHPGAUGE,	//Og
	UI_SKILLACTION,		//ANVXL
	UI_SKILLBALL,		//@XL
	UI_SKILLHEAL,		//ñ@XL
	UI_CHANTMAGIC,		//U@Ìr¥Og
	UI_CHANTHEAL,		//ñ@Ìr¥Og
	UI_CHANTGAUGE,		//r¥ÌQ[W
	UI_MAX
} UI;

////////////////////////////////////////////////////////////////////////////////
//vg^Cvé¾
////////////////////////////////////////////////////////////////////////////////
HRESULT InitUI(void);
void UninitUI(void);
void UpdateUI(void);
void DrawUI(void);

void SetVertexHPGauge(void);
void SetVertexMPGauge(void);
void SetVertexEnemyHPGauge(void);
void SetVertexHP(void);
void SetVertexMP(void);
void SetVertexENEMYHP(void);
void SetVertexAction(void);
void SetVertexMagic(void);
void SetVertexHeal(void);
void SetVertexCooldown(int nIdx);
void SetVertexChantMagic(void);
void SetVertexChantHeal(void);
void SetVertexChant(void);

#endif