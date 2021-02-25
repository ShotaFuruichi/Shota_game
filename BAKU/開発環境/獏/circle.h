////////////////////////////////////////////////////////////////////////////////
//
//Contents	: 魔法陣 [circle.h]
//Author	: ShotaFuruichi
//Since		: 2021/02/25
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _CIRCLE_H_
#define _CIRCLE_H_
#include "main.h"

////////////////////////////////////////////////////////////////////////////////
//敵の攻撃の構造体
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//向き
	D3DXMATRIX mtxworld;	//ワールドマトリックス
	bool bUse;				//使用状況
} MAGICCIRCLE;

////////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
////////////////////////////////////////////////////////////////////////////////
HRESULT InitCircle(void);
void UninitCircle(void);
void UpdateCircle(void);
void DrawCircle(void);
void SetCircle(int nSkill);
void SetVertexCircle(int nIdx);

#endif