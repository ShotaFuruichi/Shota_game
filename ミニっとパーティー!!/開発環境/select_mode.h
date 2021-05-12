//-------------------------------------------------------------------
//
// ポーズヘッダー (pause.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _SELECTMODE_H_
#define _SELECTMODE_H_

#include "main.h"

//-------------------------------------------------------------------
// ポーズの状態
//-------------------------------------------------------------------
typedef enum
{
	PAUSE_MENU_CONTINUE = 0,	// コンティニュー
	PAUSE_MENU_RETRY,			// リトライ
	PAUSE_MENU_QUIT,			// 終了
	PAUSE_MENU_MAX,
}SELECT_MENU;

//-------------------------------------------------------------------
// プロトタイプ宣言
//-------------------------------------------------------------------
HRESULT InitSelectMode(void);				// ポーズの初期化処理
void UninitSelectMode(void);					// ポーズの終了処理
void UpdateSelectMode(void);					// ポーズの更新処理
void DrawSelectMode(void);					// ポーズの描画処理

void SetVertexSelectMode(int nCntPause);		// ポーズ画面の頂点座標
void SelectMenu(int nCnt);				// ポーズメニュー

#endif