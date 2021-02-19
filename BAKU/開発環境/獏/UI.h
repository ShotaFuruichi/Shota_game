////////////////////////////////////////////////////////////////////////////////
//
//Contents	: UIの処理 [UI.h]
//Author	: ShotaFuruichi
//Since		: 2021/02/17
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _UI_H_
#define _UI_H_
#include "main.h"

////////////////////////////////////////////////////////////////////////////////
//UIの列挙型
////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	UI_HP = 0,			//体力
	UI_MP,				//mp
	UI_ENEMYHP,			//敵の体力
	UI_HPGAUGE,			//外枠
	UI_MPGAUGE,			//外枠
	UI_ENEMYHPGAUGE,	//外枠
	UI_SKILLACTION,		//アクションスキル
	UI_SKILLBALL,		//魔法スキル
	UI_SKILLHEAL,		//回復魔法スキル
	UI_CHANTMAGIC,		//攻撃魔法の詠唱時外枠
	UI_CHANTHEAL,		//回復魔法の詠唱時外枠
	UI_CHANTGAUGE,		//詠唱時のゲージ
	UI_MAX
} UI;

////////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
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