#pragma once
#include "main.h"

#define POS_MARK_OFFSET_X_1 -15
#define POS_MARK_OFFSET_X_2 0
#define POS_MARK_OFFSET_X_3 15
#define POS_MARK_OFFSET_Y_1 -50
#define POS_MARK_OFFSET_Y_2 -50
#define POS_MARK_OFFSET_Y_3 -50
#define MARK_SIZE_X 20
#define MARK_SIZE_Y 20
#define WARNING_MARK_NUMBER 3 //àÍÇ¬BOMBÇÃåxçêMarkÇÕ3Ç¡Ç¬Ç™Ç†ÇË
typedef struct
{
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	float frot;
	bool bUse;
}WARNING_MARK;

void InitBombWarnMark();
void UninitBombWarnMark();
void UpdateBombWarnMark();
void DrawBombWarnMark();
D3DXVECTOR2 Switch_Pos(D3DXVECTOR3 pos); //worldç¿ïWÇ©ÇÁscreenç¿ïWÇ…ïœä∑Ç∑ÇÈ
void SetBombMark(int nCntBomb);
void ResetBombMark(int nCntBomb);
void ResetBombMarkALL(int nCntBomb);