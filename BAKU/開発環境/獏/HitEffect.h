////////////////////////////////////////////////////////////////////////////////
//
//Contents	: ヒットエフェクト処理 [HitEffect.h]
//Author	: ShotaFuruichi
//Since		: 2021/02/24
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _HITEFFECT_H_
#define _HITEFFECT_H_
#include "main.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define MAX_HITEFFECT (4096)			//ヒットエフェクトの最大数

////////////////////////////////////////////////////////////////////////////////
//エフェクトの構造体
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXMATRIX mtxworld;	//ワールドマトリックス
	bool bUse;			//使用しているかどうか
	D3DXCOLOR col;		//色
} HITEFFECT;

////////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
////////////////////////////////////////////////////////////////////////////////
HRESULT InitHitEffect(void);
void UninitHitEffect(void);
void UpdateHitEffect(void);
void DrawHitEffect(void);
void SetHitEffect(D3DXVECTOR3 pos, D3DXCOLOR col);
void SetVertexHitEffect(int nIdx);
void SetColorHitEffect(int nIdx);

#endif

