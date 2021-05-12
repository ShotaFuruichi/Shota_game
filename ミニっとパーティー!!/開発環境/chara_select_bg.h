//-------------------------------------------------------------------
//
// キャラセレクト画面背景ヘッダー (chara_select_bg.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _CHARASELECTBG_H_
#define _CHARASELECTBG_H_

#include "main.h"

//-------------------------------------------------------------------
// プロトタイプ宣言
//-------------------------------------------------------------------
HRESULT InitCharaSelectBg(void);		// キャラセレク画面背景の初期化処理
void UninitCharaSelectBg(void);			// キャラセレク画面背景の終了処理
void UpdateCharaSelectBg(void);			// キャラセレク画面背景の更新処理
void DrawCharaSelectBg(void);			// キャラセレク画面背景の描画処理
void SetVertexCharaSelectBg(int nCnt);	// キャラセレク画面背景の頂点座標の設定

#endif