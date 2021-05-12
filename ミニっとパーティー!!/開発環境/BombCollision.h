#pragma once
#include "main.h"

#define BOMB_COL_SLICES 16 //���̂�
#define BOMB_COL_STACKS 8 //���̂�

#define BOMB_PLAYER_BLOW_RANGE_1 50 //�������S
#define BOMB_PLAYER_BLOW_RANGE_2 100 //�����͈�(�߂�)
#define BOMB_PLAYER_BLOW_RANGE_3 150 //�����͈�(����)
#define BOMB_SELF_BLOW_UP 5 //����
#define BLOW_UP_FORCE_DEFAULT 70 //������
#define BLOW_UP_FORCE_Y1_OFFSET 1.f //�Ռ��g�W��(���S)
#define BLOW_UP_FORCE_Y2_OFFSET 0.5f //�Ռ��g�W��(�߂�)
#define BLOW_UP_FORCE_Y3_OFFSET 0.25f //�Ռ��g�W��(����)
void InitBombCollision();
void UninitBombCollision();
void DrawBombCollision();
BOOL BombCollision(D3DXVECTOR3 TargetPos, int nBombID);
D3DXVECTOR3 BombBlow_Col(D3DXVECTOR3 TargetPos, int BombID);
bool BombBlow_Col_Bool(D3DXVECTOR3 TargetPos, int nBombID);