//-------------------------------------------------------------------
//
// キャラセレクトフレームヘッダー (chara_select_frame.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _CHARASELECTFRAME_H_
#define _CHARASELECTFRAME_H_

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
	int nIdxChara;					// 何番目のキャラにフレームがいるか
	int nNumChara;					// 何番目のキャラを選んだか
	int nCounterLandam;				// ランダム選択時のカウント
	bool bSelect;					// 選択されたかどうか
	int nSaveCommand[MAX_COMMAND];	// コマンド保存用
	bool bSecrec;					// 隠しキャラのするかどうか
}CharaSelectFrame;

//-------------------------------------------------------------------
// プロトタイプ宣言
//-------------------------------------------------------------------
HRESULT InitCharaSelectFrame(void);					// キャラセレクトフレームの初期化処理
void UninitCharaSelectFrame(void);					// キャラセレクトフレームの終了処理
void UpdateCharaSelectFrame(void);					// キャラセレクトフレームの更新処理
void DrawCharaSelectFrame(void);					// キャラセレクトフレームの描画処理

bool SecretChara(int nCntPlayer, int nNumChara);	// シークレットキャラを出すか処理
void SetVertexCharaSelectFrame(int nIdx);			// キャラセレクトフレームの頂点座標の設定
CharaSelectFrame *GetCharaSelectFrame(void);		// キャラセレクトフレーム情報の取得

int GetFrame(void);

#endif