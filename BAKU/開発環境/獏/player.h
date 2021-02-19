////////////////////////////////////////////////////////////////////////////////
//
//Contents	: プレイヤーの処理 [player.h]
//Author	: ShotaFuruichi
//Since		: 2020/12/17
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define SEC_ONE (60)							//1秒
	
#define MAX_MODEL_PLAYER (10)					//モデルの最大数
#define PLAYER_SIZEXZ (10.0f)					//プレイヤーのサイズXZ軸
#define PLAYER_SIZEY (35.0f)					//プレイヤーのサイズY軸
#define LIFE_PLAYER (10000)						//プレイヤーの体力
#define MP_PLAYER (8000)						//mpの最大値
#define MAX_COOLDOWN (SEC_ONE * 2)				//クールダウン
#define CHANT_TIMEMAGIC ((float)SEC_ONE * 1.5f)	//攻撃魔法の詠唱時間
#define CHANT_TIMEHEAL (SEC_ONE)				//回復魔法の詠唱時間

////////////////////////////////////////////////////////////////////////////////
//現在のモーション
////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	MOTION_NEUTRAL = 0,	//ニュートラルモーション
	MOTION_MOVE,		//移動モーション
	MOTION_JUMP,		//ジャンプモーション
	MOTION_ACTION,		//アクションモーション
	MOTION_MAX
} MOTION;

////////////////////////////////////////////////////////////////////////////////
//現在詠唱中の魔法
////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	SKILL_NONE = 0,		//何も詠唱していない状態
	SKILL_ATTACK,		//物理攻撃
	SKILL_MAGICBALL, 	//攻撃魔法
	SKILL_HEAL,			//回復魔法
	SKILL_MAX
} SKILL;

////////////////////////////////////////////////////////////////////////////////
//モデルの構造体
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	LPD3DXMESH pMesh;			//メッシュへのポインタ
	LPD3DXBUFFER pBufferMat;	//マテリアルへのポインタ
	DWORD nNumMat;				//マテリアルの数
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 rot;			//向き
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
	int nIdxModelParent;		//親モデルのインデックス
} MODEL;

////////////////////////////////////////////////////////////////////////////////
//プレイヤーの構造体
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	D3DXVECTOR3 pos;				//位置
	D3DXVECTOR3 posOld;				//前回更新時の位置
	D3DXVECTOR3 rot;				//向き
	D3DXVECTOR3 rotDest;			//目標の向き
	D3DXMATRIX mtxWorld;			//ワールドマトリックス
	MOTION nowMotion;				//現在のモーション
	bool bA;						//当たったか
	bool bMove;						//動いているか
	bool bChant;					//詠唱中かどうか
	bool bUseSkill;					//スキルを使えるか
	int nChantCounter;				//詠唱時間
	int nCooldown;					//スキル共通クールダウン
	SKILL skill;					//現在詠唱中の魔法
	int nLife;						//体力
	int nMP;						//マジックポイント
	int nMpRec;						//mp回復のためのカウンタ
	float fGravity;					//重力
	bool bJump;						//ジャンプの可不可
	MODEL aModel[MAX_MODEL_PLAYER];	//モデル(パーツ)
	int nNumModel;					//モデル(パーツ)数

} PLAYER;

////////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
////////////////////////////////////////////////////////////////////////////////
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

void SkillPlayer(void);
void MovePlayer(void);

void MotionPlayer(void);
void MotionPlayerNeutral(void);
void MotionPlayerMove(void);
void MotionPlayerJump(void);
void MotionPlayerAction(void);

D3DXVECTOR3 *GetPosPlayer(void);
D3DXVECTOR3 *GetPosOld(void);
D3DXVECTOR3 *GetRotPlayer(void);
PLAYER *GetPlayer(void);
float *GetGaiseki(void);
int GetRandom(int min, int max);

#endif