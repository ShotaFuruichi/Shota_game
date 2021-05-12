//-------------------------------------------------------------------
//
// キャラセレクトヘッダー (chara_select.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _CHARASELECT_H_
#define _CHARASELECT_H_

#include "main.h"

//-------------------------------------------------------------------
// プロトタイプ宣言
//-------------------------------------------------------------------
HRESULT InitCharaSelect(void);				// キャラセレクトの初期化処理
void UninitCharaSelect(void);				// キャラセレクトの終了処理
void UpdateCharaSelect(void);				// キャラセレクトの更新処理
void DrawCharaSelect(void);					// キャラセレクトの描画処理

#endif