#pragma once
#include "main.h"
#include "BombWarningMark.h"

#define BOMB_NUMBER 30 //爆弾数
#define BOMB_CREATE_TIME 100 //爆弾生成時間間隔
#define BOMB_BLOW_UP_TIME 5 //爆発時間限り
#define BOMB_BLOW_UP_FRAME 60 //爆発を持続時間Frame
#define BOMB_TEXTURE 100 //材質用Textute最大値
#define BOMB_SHOOT_SPEED_Y 2.5f //bomb発射の初速度(高さ)
#define BOMB_SHOOT_POWER ((rand () % 15 / 10.f) + 2.f) 
#define BOMB_THROW_SPEED 1.5f
#define BOMB_THROW_SPEED_Y 4.0f
#define BOMB_THROW_POWER 2.5f
#define BOMB_GRAVITY 0.2f //重力
#define BOMB_ELASTIC 0.75f //弾力係数
#define BOMB_AIR_FRICTION 0.02f //空気摩擦力
#define BOMB_GROUND_FRICTION 0.05f //地面摩擦力
#define STAGE_HEIGHT 70//ステージの高さ
#define BOMB_RADIUS 30.f //Bomb当たり判定球の半径
#define BOMB_PLAYER_CATCH_Y 30.f //プレイアの頭の上にbombを掲げて高さ
#define STAGE_RADIUS 300.f //stageの半径
#define BOMB_SHADOW 20.f
#define BOMB_SPIN_Y 10.f
typedef enum
{
	BOMB_MOVE = 0, //移動中
	BOMB_STOP, //stageにいる
	BOMB_CATCH, //playerの手にいる
	BOMB_BLOW, //爆発
	BOMB_SHOOT_OUT, //大砲から発射するまだstageに入ってない時
	BOMB_NOTCREATE, //未生成
}BOMB_STATE;

typedef	struct
{
	bool bUse; //有効判断
	int nID; //番号
	int nCntTime; //爆発時間カウントダウン
	int nIdexShadow;
	bool bCatch;
	D3DXVECTOR3 pos; //位置
	D3DXVECTOR3 move; //移動量
	D3DXVECTOR3 rot; //角度
	D3DXVECTOR3 rotMove; //回転量
	BOMB_STATE BombState; //状態管理

	LPD3DXMESH Xfile_Mesh; //mesh
	LPD3DXBUFFER Xfile_Materials; //材質
	DWORD Xfile_MaterialNum; //材質の数
	LPDIRECT3DTEXTURE9 Xfile_Textures[BOMB_TEXTURE] = {}; //材質用のtexture
	D3DXMATRIX Xfile_MtxWorld; //

	WARNING_MARK aWarning_Mark[WARNING_MARK_NUMBER];
}BOMB;

HRESULT InitBomb(); //BOMB定義
void UninitBomb(); //メモリの
void UpdateBomb(); //BOMB更新処理
void DrawBomb(); //BOMB描画

void SetBomb(int nCannonID); //BOMB生成
void BombStateControl(); //BOMB状態管理
void BombThrow(int nID, D3DXVECTOR3 pos, D3DXVECTOR3 rot); //BOMB投げる
void BombSpin();
BOMB *GetBomb();
void BombAndPlayer(int nCntPlayer);
void SetBombBlow(int nCntBomb);