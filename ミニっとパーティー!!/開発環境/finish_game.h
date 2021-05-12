//-------------------------------------------------------------------
//
// フィニッシュゲームヘッダー (finish_game.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _FINISHGAME_H_
#define _FINISHGAME_H_

#include "main.h"

//-------------------------------------------------------------------
// 構造体の定義
//-------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXCOLOR col;		// 色
	int nTExType;		// テクスチャの種類
	int nCntAlufa;		// α値の移動値
	float fCntSize;		// サイズの移動値
	bool bUse;			// 使用しているかどうか
	bool bFinish;		// ゲームが終わったかどうか
}FinishGame;

//-------------------------------------------------------------------
// プロトタイプ宣言
//-------------------------------------------------------------------
HRESULT InitFinishGame(void);		// フィニッシュゲームの初期化処理
void UninitFinishGame(void);		// フィニッシュゲームの終了処理
void UpdateFinishGame(void);		// フィニッシュゲームの更新処理
void DrawFinishGame(void);			// フィニッシュゲームの描画処理
void SetVertexFinishGame(void);		// フィニッシュゲームの頂点座標の設定
void SetFinishGame(bool bFinish);	// フィニッシュゲームの設定
bool GetFinishGame(void);

#endif