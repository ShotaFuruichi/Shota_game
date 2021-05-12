//-------------------------------------------------------------------
//
// チュートリアル画面背景ヘッダー (tutorial_bg.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _TUTORIALBG_H_
#define _TUTORIALBG_H_

#include "main.h"

//-------------------------------------------------------------------
// プロトタイプ宣言
//-------------------------------------------------------------------
HRESULT InitTutorialBg(void);			// チュートリアル画面背景の初期化処理
void UninitTutorialBg(void);			// チュートリアル画面背景の終了処理
void UpdateTutorialBg(void);			// チュートリアル画面背景の更新処理
void DrawTutorialBg(void);				// チュートリアル画面背景の描画処理
void SetVertexTutorialBg(int nCnt);		// チュートリアル画面背景の頂点座標の設定

#endif