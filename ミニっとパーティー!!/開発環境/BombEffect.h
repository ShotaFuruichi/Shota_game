#pragma once
#include "main.h"
#include "Bomb.h"

#define BOMB_PARTICLE_TEX 1
#define BOMB_PARTICLE_NUM 1000
#define BOMB_PARTICLE_TRACK_LENGTH 150
#define BLOW_EFFECT_SIZE_X 80
#define BLOW_EFFECT_SIZE_Y 80
#define BLOW_EFFECT_PART 9.0f
#define BLOW_EFFECT_Y_OFFSET 40.f
typedef enum
{
	LEVEL_1 = 0,
	LEVEL_2,
	LEVEL_MAX,
}PARTCILE_LEVEL;

typedef struct
{
	D3DXVECTOR3 pos; //à íu
	D3DXVECTOR3 move; //à⁄ìÆ
	D3DXVECTOR3 nor; //ñ@ê¸å¸Ç´Å@normal vector
	bool bUse;
	int nPatternAnime, nTextureID, nID;
}BLOW_EFFECT;

HRESULT InitBlowEffect();
void UninitBlowEffect();
void UpdateBlowEffect();
void DrawBlowEffect();
void SetBlowEffect(BOMB *pBomb);