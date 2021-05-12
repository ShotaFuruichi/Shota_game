#pragma once
#include "main.h"

#define BOMB_COL_SLICES 16 //‹…‘Ì‚Ì
#define BOMB_COL_STACKS 8 //‹…‘Ì‚Ì

#define BOMB_PLAYER_BLOW_RANGE_1 50 //”š”­’†S
#define BOMB_PLAYER_BLOW_RANGE_2 100 //”š”­”ÍˆÍ(‹ß‚¢)
#define BOMB_PLAYER_BLOW_RANGE_3 150 //”š”­”ÍˆÍ(‰“‚¢)
#define BOMB_SELF_BLOW_UP 5 //©”š
#define BLOW_UP_FORCE_DEFAULT 70 //”š•——Í
#define BLOW_UP_FORCE_Y1_OFFSET 1.f //ÕŒ‚”gŒW”(’†S)
#define BLOW_UP_FORCE_Y2_OFFSET 0.5f //ÕŒ‚”gŒW”(‹ß‚¢)
#define BLOW_UP_FORCE_Y3_OFFSET 0.25f //ÕŒ‚”gŒW”(‰“‚¢)
void InitBombCollision();
void UninitBombCollision();
void DrawBombCollision();
BOOL BombCollision(D3DXVECTOR3 TargetPos, int nBombID);
D3DXVECTOR3 BombBlow_Col(D3DXVECTOR3 TargetPos, int BombID);
bool BombBlow_Col_Bool(D3DXVECTOR3 TargetPos, int nBombID);