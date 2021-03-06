////////////////////////////////////////////////////////////////////////////////
//
//Contents	:	オブジェクトの処理 [object.h]
//Author	: ShotaFuruichi
//Since		: 2020/12/10
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "main.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define MAX_OBJECT (256)

////////////////////////////////////////////////////////////////////////////////
//オブジェクトの構造体
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 rot;						//向き
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
	bool bUse;								//使用状況
	int nCount;								//消えるまでのカウント
} OBJECT;

////////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
////////////////////////////////////////////////////////////////////////////////
void InitObject(void);
void UninitObject(void);
void UpdateObject(void);
void DrawObject(void);

void SetObject(D3DXVECTOR3 pos);
bool CollisionObject(D3DXVECTOR3 pos, D3DXVECTOR3 oldpos);

#endif
