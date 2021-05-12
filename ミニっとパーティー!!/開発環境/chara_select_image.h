//-------------------------------------------------------------------
//
// キャラセレクトイメージヘッダー (chara_select_image.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _CHARASELECTIMAGE_H_
#define _CHARASELECTIMAGE_H_

#include "main.h"

//-------------------------------------------------------------------
// マクロ定義
//-------------------------------------------------------------------
#define MAX_CHARAIMAGE		(5)						// テクスチャ枚数

//-----------------------------------------------------------------
// 構造体の定義
//-----------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXCOLOR col;			// 色
	float fWidth;			// 幅
	float fHeight;			// 高さ
	bool bSelect;			// 選択されたかどうか
}CharaSelectImage;

//-------------------------------------------------------------------
// プロトタイプ宣言
//-------------------------------------------------------------------
HRESULT InitCharaSelectImage(void);			// キャラセレクトイメージの初期化処理
void UninitCharaSelectImage(void);			// キャラセレクトイメージの終了処理
void UpdateCharaSelectImage(void);			// キャラセレクトイメージの更新処理
void DrawCharaSelectImage(void);			// キャラセレクトイメージの描画処理

CharaSelectImage *GetCharaSelectImage(void);	// キャラセレクトイメージ情報の取得

#endif