//-------------------------------------------------------------------
//
// キャラ決定ヘッダー (dicision_chara.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _DICISIONCHARA_H_
#define _DICISIONCHARA_H_

#include "main.h"

//-------------------------------------------------------------------
// マクロ定義
//-------------------------------------------------------------------
#define MAX_COMMAND	(5)						// コマンド数

//-----------------------------------------------------------------
// 構造体の定義
//-----------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;				// 位置
	D3DXCOLOR col;					// 色
	float fWidth;					// 幅
	float fHeight;					// 高さ
	int nTxType;					// テクスチャタイプ
	bool bDicision;					// 決定したかどうか
}DicisionChara;

//-------------------------------------------------------------------
// プロトタイプ宣言
//-------------------------------------------------------------------
HRESULT InitDicisionChara(void);				// キャラ決定の初期化処理
void UninitDicisionChara(void);					// キャラ決定の終了処理
void UpdateDicisionChara(void);					// キャラ決定の更新処理
void DrawDicisionChara(void);					// キャラ決定の描画処理

void SetVertexDicisionChara(int nIdx);			// キャラ決定の頂点座標の設定
DicisionChara *GetDicisionChara(void);			// キャラ決定情報の取得

void SetDicisionChara(bool bDicision, int nCntPlayer);			// 決定したとき

#endif