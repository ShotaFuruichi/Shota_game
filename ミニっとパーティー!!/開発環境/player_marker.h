//-------------------------------------------------------------------
//
// プレイヤーマーカーヘッダー (player_marker.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _PLAYERMARKER_H_
#define _PLAYERMARKER_H_

#include "main.h"

//-------------------------------------------------------------------
// 列挙型
//-------------------------------------------------------------------
typedef enum
{
	PLAYER_MARKER_TYPE_ONE = 0,		// 1P
	PLAYER_MARKER_TYPE_TWO,			// 2P
	PLAYER_MARKER_TYPE_MAX,			// 獲得ポイントロゴの最大数
}PLAYER_MARKER_TYPE;				// プレイヤーマーカーの最大値

//-------------------------------------------------------------------
// 構造体の定義
//-------------------------------------------------------------------
typedef struct
{
	D3DXMATRIX mtxWorld;		// ワールドマトリックス
	D3DXVECTOR3 pos;			// 位置
	D3DXVECTOR3 move;			// 移動量
	PLAYER_MARKER_TYPE type;	// プレイヤーマーカーのタイプ
	float fWidth;				// 幅
	float fHeight;				// 高さ
}PLAYER_MARKER;					// プレイヤーマーカーの構造体

//-------------------------------------------------------------------
// プロトタイプ宣言
//-------------------------------------------------------------------
HRESULT InitPlayerMarker(void);															// ポイントの初期化処理
void UninitPlayerMarker(void);															// ポイントの終了処理
void UpdatePlayerMarker(void);															// ポイントの更新処理
void DrawPlayerMarker(void);															// ポイントの描画処理

#endif
