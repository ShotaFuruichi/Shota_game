//-------------------------------------------------------------------
//
// リザルトロゴヘッダー (title.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _RESULTLOGO_H_
#define _RESuLTLOGO_H_

#include "main.h"

//-------------------------------------------------------------------
// プロトタイプ宣言
//-------------------------------------------------------------------
HRESULT InitResultLogo(void);				// リザルトロゴの初期化処理
void UninitResultLogo(void);				// リザルトロゴの終了処理
void UpdateResultLogo(void);				// リザルトロゴの更新処理
void DrawResultLogo(void);					// リザルトロゴの描画処理

#endif
