//-----------------------------------------------------------------
//
//	テクスチャの読み込み (texture.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "texture.h"

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
Texture g_Texture;			// テクスチャ情報
Texture g_UITexture;			// UIテクスチャ情報

//-----------------------------------------------------------------
//テクスチャの読み込み
//-----------------------------------------------------------------
void LoadTexture(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し、初期化
	pDevice = GetDevice();

	for (int nCntTexture = 0; nCntTexture < g_Texture.nNumTexture; nCntTexture++)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, &g_Texture.TextureInfo[nCntTexture].aTexcharName[0], &g_Texture.TextureInfo[nCntTexture].pTexture);
	}

	for (int nCntUITexture = 0; nCntUITexture < g_UITexture.nNumTexture; nCntUITexture++)
	{
		// UIテクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, &g_UITexture.TextureInfo[nCntUITexture].aTexcharName[0], &g_UITexture.TextureInfo[nCntUITexture].pTexture);
	}
}

//-----------------------------------------------------------------
//テクスチャの解放
//-----------------------------------------------------------------
void ReleaseTexture(void)
{
	// テクスチャの解放
	for (int nCntTexture = 0; nCntTexture < g_Texture.nNumTexture; nCntTexture++)
	{
		if (g_Texture.TextureInfo[nCntTexture].pTexture != NULL)
		{
			g_Texture.TextureInfo[nCntTexture].pTexture->Release();
			g_Texture.TextureInfo[nCntTexture].pTexture = NULL;
		}
	}

	// UIテクスチャの解放
	for (int nCntUITexture = 0; nCntUITexture < g_UITexture.nNumTexture; nCntUITexture++)
	{
		if (g_UITexture.TextureInfo[nCntUITexture].pTexture != NULL)
		{
			g_UITexture.TextureInfo[nCntUITexture].pTexture->Release();
			g_UITexture.TextureInfo[nCntUITexture].pTexture = NULL;
		}
	}
}

//-----------------------------------------------------------------
// テクスチャ情報の取得
//-----------------------------------------------------------------
Texture *GetTexture(void)
{
	return &g_Texture;
}

//-----------------------------------------------------------------
// テクスチャ情報の取得
//-----------------------------------------------------------------
Texture *GetUITexture(void)
{
	return &g_UITexture;
}