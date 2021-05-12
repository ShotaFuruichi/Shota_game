//-------------------------------------------------------------------
//
// テクスチャ配置ヘッダー (texture_set.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _TEXTURESET_H_
#define _TEXTURESET_H_

#include "main.h"
#include "texture.h"

//-----------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------
#define MAX_TEXTURE_SET	(64)							// 背景の種類

//-------------------------------------------------------------------
// 構造体の定義
//-------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 回転
	D3DXVECTOR3 move;		// 移動
	D3DXCOLOR col;			// 色
	float fRemoveAlpha;		// α値の減少量
	float fWidthDest;		// 目的の幅
	float fHeightDest;		// 目的の高さ
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
	int nType;				// 移動タイプ
	int nTexType;			// テクスチャタイプ
	bool bUse;				// 使用しているかどうか
}TextureSetInfo;

typedef struct
{
	TextureSetInfo textureSetInfo[MAX_TEXTURE_SET];		// テクスチャ配置情報
	int nNumTextureSet;									// 置くテクスチャの数
	char aTextName[128];								// 読み込むテキスト
}TextureSet;

//-------------------------------------------------------------------
// プロトタイプ宣言
//-------------------------------------------------------------------
HRESULT InitTextureSet(void);		// テクスチャ設置の初期化処理
void UninitTextureSet(void);		// テクスチャ設置の終了処理
void UpdateTextureSet(void);		// テクスチャ設置の更新処理
void DrawTextureSet(void);			// テクスチャ設置の描画処理

void SetVertexTextureSet(int nCnt); // 頂点座標の設定
void SetTexture(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXCOLOR col,
	float fRemoveAlpha,float fWidth, float fHeight,float fWidthDest, float fHeightDest,
	int type, int textype);

TextureSet *GetTextureSet(void);	// テクスチャ配置情報の取得

#endif