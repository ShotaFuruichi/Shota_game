#pragma once
#pragma once
#include "main.h"

#define CANNON_NUM 2
#define CANNON_TEX 100
#define CANNON_POS_X 380.f
#define CANNON_POS_Y 30.f
#define INIT_ROT_ANGLE_Y (D3DX_PI / 2.f)
#define INIT_ROT_ANGLE_X (D3DX_PI / 8.f)
#define MAX_ROT_ANGLE (D3DX_PI * 7.f / 10.f)
#define MIN_ROT_ANGLE (D3DX_PI * 3.f / 10.f)
#define ROT_SPEED 0.002f
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	float fRotSpeed;
	LPD3DXMESH Xfile_Mesh; //mesh
	LPD3DXBUFFER Xfile_Materials; //çﬁéø
	DWORD Xfile_MaterialNum; //çﬁéøÇÃêî
	LPDIRECT3DTEXTURE9 Xfile_Textures[CANNON_TEX] = {}; //çﬁéøópÇÃtexture
}CANNON;
void InitCannon();
void UninitCannon();
void UpdateCannon();
void DrawCannon();
CANNON *GetCannon();