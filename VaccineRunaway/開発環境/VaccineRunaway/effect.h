////////////////////////////////////////////////////////////////////////////////
//
//Contents	: エフェクト処理 [effect.h]
//Author	: ShotaFuruichi
//Since		: 2020/09/07
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _EFFECT_H_
#define _EFFECT_H_
#include "main.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define MAX_EFFECT (8192)			//敵の最大数

////////////////////////////////////////////////////////////////////////////////
//エフェクトの構造体
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	bool bUse;			//使用しているかどうか
	D3DXCOLOR col;		//色
} EFFECT;

////////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
////////////////////////////////////////////////////////////////////////////////
HRESULT InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col);
void SetVertexEffect(int nIdx);
void SetColorEffect(int nIdx);

#endif
