//-------------------------------------------------------------------
//
// タイトルロゴヘッダー (titlelogo.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

#include "main.h"

//-------------------------------------------------------------------
// 構造体の定義
//-------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 回転
	float fRateWidth;		// 幅の割合
	float fRateHeight;		// 高さの割合
	float fMoveRateWidth;	// 割合の増減量
	float fMoveRateHeight;	// 割合の増減量
	float fWidth;			// 幅
	float fHeight;			// 高さ
	float fAngle;			// 角度
	float fLength;			// 対角線の長さ
	bool bMaxSize;			// 最大サイズになったかどうか
	bool bNormalSize;		// 普通のサイズになったかどうか
}TITLELOGO;

//-------------------------------------------------------------------
// プロトタイプ宣言
//-------------------------------------------------------------------
HRESULT InitTitlelogo(void);				// タイトルロゴの初期化処理
void UninitTitlelogo(void);					// タイトルロゴの終了処理
void UpdateTitlelogo(void);					// タイトルロゴの更新処理
void DrawTitlelogo(void);					// タイトルロゴの描画処理

void SetVerTexTitleLogo(int nIdx);			// 頂点座標の設定
bool GetFall(void);							// タイトルロゴの情報の取得

#endif