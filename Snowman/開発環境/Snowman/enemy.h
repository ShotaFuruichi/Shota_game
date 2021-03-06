////////////////////////////////////////////////////////////////////////////////
//
//Contents	: 敵の処理 [enemy.h]
//Author	: ShotaFuruichi
//Since		: 2020/10/23
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define MAX_ENEMY (512)					//敵の最大数
#define ENEMY_SIZEY (80.0f)				//敵のサイズY
#define ENEMY_SIZEX (60.0f)				//敵のサイズX
#define ENEMY_SPEED (2.0f)				//敵の移動量

////////////////////////////////////////////////////////////////////////////////
//敵の状態
////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	ENEMYSTATE_NORMAL = 0,	//通常状態
	ENEMYSTATE_FREEZE,		//凍結状態
	ENEMYSTATE_MAX
} ENEMYSTATE;

////////////////////////////////////////////////////////////////////////////////
//敵の種類
////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	ENEMYTYPE_SPRING = 0,
	ENEMYTYPE_SPRINGFREEZE,
	ENEMYTYPE_SUMMER,
	ENEMYTYPE_SUMMERFREEZE,
	ENEMYTYPE_AUTUMN,
	ENEMYTYPE_MAX
} ENEMYTYPE;

////////////////////////////////////////////////////////////////////////////////
//敵の構造体
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 posold;	//前回の位置
	D3DXVECTOR3 move;	//移動量
	ENEMYTYPE type;		//種類
	int nJumpCounter;	//ジャンプカウント
	int nJumpTiming;	//ジャンプのタイミング
	bool bUse;			//使用しているかどうか
	ENEMYSTATE state;	//状態
	int nCounterState;	//状態カウンター
	int nLife;			//体力
} ENEMY;

////////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
////////////////////////////////////////////////////////////////////////////////
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMYTYPE type);
ENEMY *GetEnemy(void);
void SetVertexEnemy(int nIdx);
void SetTextureEnemy(int nIdx);
bool HitEnemy(int nIdx, int nDamage);
int GetRandom(int min, int max);

#endif