//-------------------------------------------------------------------
//
// プレイヤーバンドヘッダー (player_band.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _PLAYERBAND_H_
#define _PLAYERBAND_H_

#include "main.h"
#include "texture.h"

//-----------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------
#define MAX_PLAYERBAND		(5)							// プレイヤーバンド数
#define DISPLAY_PLAYERBAND	(4)							// 表示する最大数

//-------------------------------------------------------------------
// 列挙型
//-------------------------------------------------------------------
typedef enum
{
	PLAYERBANDTYPE_1P = 0,		// 1P
	PLAYERBANDTYPE_2P,			// 2P
	PLAYERBANDTYPE_3P,			// 3P
	PLAYERBANDTYPE_4P,			// 4P
	PLAYERBANDTYPE_COM,			// COM
	PLAYERBANDTYPE_MAX,			
}PLAYERBANDTYPE;				// プレイヤーバンドの種類

//-------------------------------------------------------------------
// 構造体の定義
//-------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXCOLOR col;			// 色
	float fWidth;			// 幅
	float fHeight;			// 高さ
	int nTexType;			// テクスチャタイプ
	bool bUse;				// 使用しているかどうか
}PlayerBand;

//-------------------------------------------------------------------
// プロトタイプ宣言
//-------------------------------------------------------------------
HRESULT InitPlayerBand(void);		// プレイヤーバンドの初期化処理
void UninitPlayerBand(void);		// プレイヤーバンドの終了処理
void UpdatePlayerBand(void);		// プレイヤーバンドの更新処理
void DrawPlayerBand(void);			// プレイヤーバンドの描画処理

void SetVertexPlayerBand(int nIdx); // 頂点座標の設定

PlayerBand *GetPlayerBand(void);	// プレイヤーバンド情報の取得

void LoadPlayerBandData(void);		// プレイヤーバンド情報の読み込み

#endif