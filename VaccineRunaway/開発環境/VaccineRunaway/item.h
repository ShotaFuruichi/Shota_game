////////////////////////////////////////////////////////////////////////////////
//
//Contents	: アイテムの処理 [item.h]
//Author	: ShotaFuruichi
//Since		: 2020/09/12
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _ITEM_H_
#define _ITEM_H_
#include "main.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define MAX_ITEM (128)	//アイテムの最大数
#define ITEM_THROUGH (1)	//貫通弾
#define ITEM_REFLECTIVE (2)	//反射弾
#define ITEM_DIFFUSION (3)	//拡散弾
#define MAX_ITEMTYPE (4)	//種類数
#define ITEM_SIZEX (25.0f)	//アイテムのXサイズ
#define ITEM_SIZEY (15.0f)	//アイテムのYサイズ


////////////////////////////////////////////////////////////////////////////////
//構造体の定義
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	bool bUse;			//使用しているかどうか
	int nType;			//弾の種類
	bool bSwitch;		//画面外に行くか
} ITEM;


////////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
////////////////////////////////////////////////////////////////////////////////
HRESULT InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(void);
void SetVertexItem(int nIdx);
ITEM *GetItem(void);

#endif

