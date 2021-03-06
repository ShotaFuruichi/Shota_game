////////////////////////////////////////////////////////////////////////////////
//
//Contents	: 弾の処理	[bullet.h]
//Author	: ShotaFuruichi
//Since		: 2020/08/03
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define BULLET_SPEED (10.0f)	//弾の速度

////////////////////////////////////////////////////////////////////////////////
//構造体の定義
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	D3DXMATRIX mtxworld;	//ワールドマトリックス
	bool bUse;				//使用状況
	int nLife;				//寿命
} BULLET;

////////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
////////////////////////////////////////////////////////////////////////////////
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos);
void SetVertexBullet(int nIdx);

#endif