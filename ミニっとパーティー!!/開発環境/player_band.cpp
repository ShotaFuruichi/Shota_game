//-----------------------------------------------------------------
//
// プレイヤーバンド (player_band.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#include "player_band.h"

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayerBand = NULL;				// プレイヤーバンドの頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTexturePlayerBand[MAX_PLAYERBAND] = {};		// プレイヤーバンドの頂点バッファのポインタ
PlayerBand g_PlayerBand[DISPLAY_PLAYERBAND];							// プレイヤーバンド情報

//-----------------------------------------------------------------
// プレイヤーバンドの初期化処理
//-----------------------------------------------------------------
HRESULT InitPlayerBand(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し、初期化
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/band_1P.png", &g_pTexturePlayerBand[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/band_2P.png", &g_pTexturePlayerBand[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/band_3P.png", &g_pTexturePlayerBand[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/band_4P.png", &g_pTexturePlayerBand[3]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/band_COM.png", &g_pTexturePlayerBand[4]);

	// 変数の初期化
	for (int nCntPlayerBand = 0; nCntPlayerBand < DISPLAY_PLAYERBAND; nCntPlayerBand++)
	{
		g_PlayerBand[nCntPlayerBand].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);
		g_PlayerBand[nCntPlayerBand].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_PlayerBand[nCntPlayerBand].fWidth = 0.0f;
		g_PlayerBand[nCntPlayerBand].fHeight = 0.0f;
		g_PlayerBand[nCntPlayerBand].nTexType = nCntPlayerBand;
		g_PlayerBand[nCntPlayerBand].bUse = true;
	}

	// プレイヤーバンド情報の読み込み
	LoadPlayerBandData();

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX * DISPLAY_PLAYERBAND,	// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayerBand,
		NULL)))
	{
		return E_FAIL;
	}

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayerBand->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPlayerBand = 0; nCntPlayerBand < DISPLAY_PLAYERBAND; nCntPlayerBand++)
	{
		// 頂点座標の設定
		SetVertexPlayerBand(nCntPlayerBand);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// 情報の更新
		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffPlayerBand->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// プレイヤーバンドの終了処理
//-----------------------------------------------------------------
void UninitPlayerBand(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffPlayerBand != NULL)
	{
		g_pVtxBuffPlayerBand->Release();
		g_pVtxBuffPlayerBand = NULL;
	}

	for (int nCntTexture = 0; nCntTexture < MAX_PLAYERBAND; nCntTexture++)
	{
		if (g_pTexturePlayerBand[nCntTexture] != NULL)
		{
			g_pTexturePlayerBand[nCntTexture]->Release();
			g_pTexturePlayerBand[nCntTexture] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// プレイヤーバンドの更新処理
//-----------------------------------------------------------------
void UpdatePlayerBand(void)
{
	
}

//-----------------------------------------------------------------
// プレイヤーバンドの描画処理
//-----------------------------------------------------------------
void DrawPlayerBand(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayerBand, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for (int nCntTexture = 0; nCntTexture < DISPLAY_PLAYERBAND; nCntTexture++)
	{
		if (g_PlayerBand[nCntTexture].bUse == true)
		{
			pDevice->SetTexture(0, g_pTexturePlayerBand[g_PlayerBand[nCntTexture].nTexType]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTexture * 4, 2);
		}
	}
}

//-----------------------------------------------------------------
// 頂点座標の設定
//-----------------------------------------------------------------
void SetVertexPlayerBand(int nIdx)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayerBand->Lock(0, 0, (void**)&pVtx, 0);

	// 何番目か
	pVtx += nIdx * 4;

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_PlayerBand[nIdx].pos.x - g_PlayerBand[nIdx].fWidth / 2.0f, g_PlayerBand[nIdx].pos.y + g_PlayerBand[nIdx].fHeight / 2.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_PlayerBand[nIdx].pos.x - g_PlayerBand[nIdx].fWidth / 2.0f, g_PlayerBand[nIdx].pos.y - g_PlayerBand[nIdx].fHeight / 2.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_PlayerBand[nIdx].pos.x + g_PlayerBand[nIdx].fWidth / 2.0f, g_PlayerBand[nIdx].pos.y + g_PlayerBand[nIdx].fHeight / 2.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_PlayerBand[nIdx].pos.x + g_PlayerBand[nIdx].fWidth / 2.0f, g_PlayerBand[nIdx].pos.y - g_PlayerBand[nIdx].fHeight / 2.0f, 0.0f);

	// 頂点カラーの設定
	pVtx[0].col = g_PlayerBand[nIdx].col;
	pVtx[1].col = g_PlayerBand[nIdx].col;
	pVtx[2].col = g_PlayerBand[nIdx].col;
	pVtx[3].col = g_PlayerBand[nIdx].col;

	// 頂点バッファをアンロックする
	g_pVtxBuffPlayerBand->Unlock();
}

//-----------------------------------------------------------------
// プレイヤーバンド情報の取得
//-----------------------------------------------------------------
PlayerBand *GetPlayerBand(void)
{
	return &g_PlayerBand[0];
}

//-----------------------------------------------------------------
// プレイヤーバンド情報の読み込み
//-----------------------------------------------------------------
void LoadPlayerBandData(void)
{
	// プレイヤーバンド情報の取得
	PlayerBand *pPlayerBand = &g_PlayerBand[0];

	// FILE型のポインタ関数
	FILE *pFile;

	// ファイルを開く
	pFile = fopen("data/TEXT/player_band.txt", "r");

	// 変数宣言
	bool bGetScript = false;
	bool bPlayerBandSet = false;

	char aLine[128];
	char aText[128];
	int nCntPlayerBand = 0;

	if (pFile != NULL)
	{
		// SCRIPTを探す
		while (fgets(aLine, 128, pFile) != NULL)
		{
			fscanf(pFile, "%s", &aText[0]);

			// SCRIPTを見つけたらそれ以降を読み込む
			if (strcmp(&aText[0], "SCRIPT") == 0)
			{
				bGetScript = true;
			}

			if (bGetScript == true)
			{
				// プレイヤーのモデル情報の読み込み
				// PLAYERBANDSETを見つけたらプレイヤーバンド情報を読み込む許可を与える
				if (strcmp(&aText[0], "PLAYERBANDSET") == 0)
				{
					bPlayerBandSet = true;
				}
				if (bPlayerBandSet == true)
				{
					// POSを見つけたら座標情報を格納
					if (strcmp(&aText[0], "POS") == 0)
					{
						fscanf(pFile, "%s %f %f %f", &aText[0],
							&pPlayerBand->pos.x,
							&pPlayerBand->pos.y,
							&pPlayerBand->pos.z);
					}
					// SIZEを見つけたらサイズ情報を格納
					if (strcmp(&aText[0], "SIZE") == 0)
					{
						fscanf(pFile, "%s %f %f", &aText[0],
							&pPlayerBand->fWidth,
							&pPlayerBand->fHeight);
					}
					// END_PLAYERBANDSETを見つけたらプレイヤーバンド情報の読み込みを終える
					if (strcmp(&aText[0], "END_PLAYERBANDSET") == 0)
					{
						bPlayerBandSet = false;

						// 情報の更新
						pPlayerBand++;
					}
				}
				// END_SCRIPTを見つけたら読み込みを終える
				if (strcmp(&aText[0], "END_SCRIPT") == 0)
				{
					break;
				}
			}
		}
		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{
	}
}