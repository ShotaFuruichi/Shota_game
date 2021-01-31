////////////////////////////////////////////////////////////////////////////////
//
//Contents	: アイテム(目標)の処理 [Item.h]
//Author	: ShotaFuruichi
//Since		: 2020/10/16
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _ITEM_H_
#define _ITEM_H_
#include "main.h"

////////////////////////////////////////////////////////////////////////////////
//構造体
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	D3DXVECTOR3 pos;
	float fWidth;
	float fHeight;
	bool bUse;
} ITEM;

////////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
////////////////////////////////////////////////////////////////////////////////
HRESULT InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, float fWidth, float fHeight);
void SetVertexItem(void);
ITEM *GetItem(void);

#endif

