//-------------------------------------------------------------------
//
// プレイヤーヘッダー (player.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "motion.h"
#include "chara.h"

//-------------------------------------------------------------------
// マクロ定義
//-------------------------------------------------------------------
#define MAX_FILENAME (64)		// Xファイルネームの最大文字数

#define MOVE_PLAYER			(1.5f)
#define JUMP_PLAYER			(11.0f)
#define PI_QUARTER			(D3DX_PI / 4.0f)
#define GRAVITY				(0.5f)		// 重力

#define LENGTH				(8.0f)
#define MAX_DISPLAY_CHARA	(4)				// プレイヤーの総数

//-------------------------------------------------------------------
// プレイヤー状態(列挙型)
//-------------------------------------------------------------------
typedef enum
{
	PLAYERSTATE_NORMAL = 0,		// 通常
	PLAYERSTATE_FLOATING,		// 浮遊
	PLAYERSTATE_DAMAGE,			// ダメージ
	PLAYERSTATE_THROW,			// ダメージ
	PLAYERSTATE_MAX,			// 状態の最大数
}PLAYERSTATE;

//-------------------------------------------------------------------
// 構造体の定義
//-------------------------------------------------------------------
typedef struct
{
	int nCharaNumber;							// 何番目のキャラクターか
	D3DXVECTOR3 pos;							// 中心座標
	D3DXVECTOR3 posOld;							// 前の中心座標
	D3DXVECTOR3 rot;							// 現在の向き
	D3DXVECTOR3 rotDest;						// 目的の向き
	D3DXMATRIX mtxWorld;						// ワールドマトリックス
	D3DXVECTOR3 move;							// 移動量
	PLAYERSTATE state;							// プレイヤーの状態
	int nStateCounter;							// 状態カウンタ
	CharacterModel aModel[20];					// モデル
	int nNumModel;								// モデル数
	D3DXVECTOR3 minVecPlayer;					// 頂点の最小値
	D3DXVECTOR3 maxVecPlayer;					// 頂点の最大値
	float fHeight;								// 当たり判定の高さ
	float fRadius;								// 当たり判定の半径
	int nIdx;									// 何番目の影か
	D3DXVECTOR3 PosShadow;							// 影の位置
	bool bJump;									// ジャンプしたかどうか
	bool bFall;									// 落ちたかどうか

	bool bFinishMotion;							// 現在のモーションが終わったかどうか
	bool bBlendMotion;							// ブレンドモーションがあるかどうか
	MOTION_INFO aMotionInfo[MOTYONTYPE_MAX];	// モーション情報
	int nNumMotion;								// モーション数
	MOTIONTYPE MotionType;						// モーションタイプ
	bool bLoopMotion;							// ループするかどうか
	int nNumKey;								// キー数
	int nKey;									// キーNo.
	int nCounterMotion;							// モーションカウンタ

	MOTIONTYPE MotionTypeBlend;					// ブレンドモーションタイプ
	bool bLoopMotionBlend;						// ブレンドモーションがループするかどうか
	int nNumKeyBlend;							// ブレンドモーションのキー数
	int nKeyBlend;								// ブレンドモーションのキーNo.
	int nCounterMotionBlend;					// ブレンドモーションカウンタ
	int nFrameBlend;							// ブレンドフレーム数
	int nCounterBlend;							// ブレンドカウンタ

	int nBombID;
	bool bHaveBomb;
	int nNearPlayer;
	bool bPush;
}Player;

//-------------------------------------------------------------------
// プロトタイプ宣言
//-------------------------------------------------------------------
HRESULT InitPlayer(void);					// プレイヤーの初期化処理
void UninitPlayer(void);					// プレイヤーの終了処理
void UpdatePlayer(void);					// プレイヤーの更新処理
void DrawPlayer(void);						// プレイヤーの描画処理

Player *GetPlayer(void);					// プレイヤー情報の取得

void GamePlayer(void);						// プレイヤーのゲーム処理
void ResultPlayer(void);					// プレイヤーのリザルト処理

void StateManagerPlayer(int nCntPlayer);	// プレイヤー状態の判別
void PlayerStateNormal(int nCntPlayer);		// プレイヤー状態が通常の時
void PlayerStateFloating(int nCntPlayer);	// プレイヤー状態が浮遊の時
void PlayerStateDamage(int nCntPlayer);		// プレイヤーがダメージ状態のとき
void PlayerStateThrow(int nCntPlayer);		// プレイヤーがダメージ状態のとき

void MoveAi(int nCntPlayer);
void ThrowAi(int nCntPlayer);
bool CollisionPlayer(int nCntPlayer);

void MovePlayer(int nCntPlayer);			// プレイヤーの移動処理
void MovePlayerKeyboard(int nCntPlayer);	// プレイヤーの移動処理(キーボード)
void MovePlayerGamepad(int nCntPlayer);		// プレイヤーの移動処理(ゲームパッド)

void PlayerMotion(int nCntPlayer);			// プレイヤモーションの設定
void SetMotion(int nCntPlayer,MOTIONTYPE motiontype, bool bBlend, int nFrameBlend);	// モーションの設定

D3DXVECTOR3 AngleCorrection(float rotX, float rotY, float rotZ);	// 角度の制限

#endif