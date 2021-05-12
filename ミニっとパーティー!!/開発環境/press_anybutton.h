//-------------------------------------------------------------------
//
// ボタン指示ヘッダー (press_anybutton.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _PRESSANYBUTTON_H_
#define _PRESSANYBUTTON_H_

#include "main.h"

//-------------------------------------------------------------------
// 構造体の定義
//-------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXCOLOR col;			// 色
	float fRemoveAlpha;		// α値減少量
	float fWidth;			// 幅
	float fHeight;			// 高さ
	int nTexType;			// テクスチャタイプ
	bool bUse;				// 使用しているかどうか
	bool bPressAnyButton;	// ボタンを押したかどうか
}PressAnyButton;

//-------------------------------------------------------------------
// プロトタイプ宣言
//-------------------------------------------------------------------
HRESULT InitPressAnyButton(void);			// ボタン指示の初期化処理
void UninitPressAnyButton(void);			// ボタン指示の終了処理
void UpdatePressAnyButton(void);			// ボタン指示の更新処理
void DrawPressAnyButton(void);				// ボタン指示の描画処理

void SetPressAnyButton(D3DXVECTOR3 pos, D3DXCOLOR col, float fRemoveAlpha,
	float fWidth, float fHeight, int nTextype);
void SetVertexPressAnyButton(void);			// 頂点座標の設定
PressAnyButton *GetPressAnyButton(void);		// ボタン指示情報の取得

#endif