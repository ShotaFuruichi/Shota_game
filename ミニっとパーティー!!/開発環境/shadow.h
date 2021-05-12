//-------------------------------------------------------------------
//
// 影ヘッダー (shadow.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//-----------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------
#define SHADOW_SIZE		(20.0f)		// 影のサイズ

//-------------------------------------------------------------------
// 構造体の定義
//-------------------------------------------------------------------
typedef struct
{
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 向き
	float fWidth;			// 幅
	float fDepth;			// 奥行
	bool bUse;				// 使用しているかどうか
}Shadow;

//-------------------------------------------------------------------
// プロトタイプ宣言
//-------------------------------------------------------------------
HRESULT InitShadow(void);										// 影の初期化処理
void UninitShadow(void);										// 影の終了処理
void UpdateShadow(void);										// 影の更新処理
void DrawShadow(void);											// 影の描画処理

int SetShadow(D3DXVECTOR3 pos, float fWidth, float fDepth);		// 影の配置
void SetPositionShadow(int nIdx, D3DXVECTOR3 pos);				// 影の位置
void DeleteShadow(int nIdx);									// 影の消去
Shadow *GetShadow(void);

void MatrixShadow(int nNumMat, D3DXMATRIX mtxWorld, D3DXVECTOR3 PosShadow,LPD3DXMESH pMesh);		// マトリックスを使用した影の描画

#endif