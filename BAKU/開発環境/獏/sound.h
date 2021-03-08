//=============================================================================
//
// Contents	: サウンド処理 [sound.h]
// Author	: ShotaFuruichi
// Since	: 2021/02/26
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_SE_MAGIC,		// 攻撃魔法
	SOUND_LABEL_SE_HEAL,		// 回復魔法
	SOUND_LABEL_SE_CHANT,		// 詠唱音
	SOUND_LABEL_SE_HIT,			// ヒット音
	SOUND_LABEL_SE_ENEATTACK,	// 敵攻撃音
	SOUND_LABEL_SE_ENEATTACK2,	// 敵攻撃音2
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif

