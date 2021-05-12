//-------------------------------------------------------------------
//
// テクスチャヘッダー (texture.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "main.h"

//-------------------------------------------------------------------
// 構造体の定義
//-------------------------------------------------------------------
typedef struct
{
	LPDIRECT3DTEXTURE9 pTexture;	// テクスチャへのポインタ
	char aTexcharName[128];			// テクスチャの名前
}Texture_Info;

typedef struct
{
	Texture_Info TextureInfo[20];	// テクスチャ情報
	int nNumTexture;				// テクスチャの数
}Texture;

//-------------------------------------------------------------------
// プロトタイプ宣言
//-------------------------------------------------------------------
void LoadTexture(void);		// テクスチャの読み込み
void ReleaseTexture(void);	// テクスチャの解放

Texture *GetTexture(void);	// テクスチャ情報の取得
Texture *GetUITexture(void);	// テクスチャ情報の取得

#endif