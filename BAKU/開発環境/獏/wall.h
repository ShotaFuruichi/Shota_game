////////////////////////////////////////////////////////////////////////////////
//
//Contents	: 壁の処理 [wall.h]
//Author	: ShotaFuruichi
//Since		: 2020/11/17
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _WALL_H_
#define _WALL_H_
#include "main.h"

////////////////////////////////////////////////////////////////////////////////
//壁の構造体
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//向き
	D3DXMATRIX mtxworld;	//ワールドマトリックス
} WALL;

////////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
////////////////////////////////////////////////////////////////////////////////
HRESULT InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
WALL *GetWall(void);
VERTEX_3D *GetVtx(void);

#endif