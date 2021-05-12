//-----------------------------------------------------------------
//
// テクスチャ配置 (texture_set.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "texture_set.h"

//-----------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------
#define RATE					(0.05f)						// 割合レートの増減量
#define MOVE_RATE				(0.001f)					// 割合レートの増減量

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTextureSet = NULL;				// 背景の頂点バッファのポインタ
TextureSet g_TextureSet;											// テクスチャ配置情報

//-----------------------------------------------------------------
// 背景の初期化処理
//-----------------------------------------------------------------
HRESULT InitTextureSet(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し、初期化
	pDevice = GetDevice();

	// 変数の初期化
	for (int nCntTextureSet = 0; nCntTextureSet < MAX_TEXTURE_SET; nCntTextureSet++)
	{
		g_TextureSet.textureSetInfo[nCntTextureSet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_TextureSet.textureSetInfo[nCntTextureSet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_TextureSet.textureSetInfo[nCntTextureSet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_TextureSet.textureSetInfo[nCntTextureSet].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		g_TextureSet.textureSetInfo[nCntTextureSet].fRemoveAlpha = 0.0f;
		g_TextureSet.textureSetInfo[nCntTextureSet].fWidthDest = 0.0f;
		g_TextureSet.textureSetInfo[nCntTextureSet].fHeightDest = 0.0f;
		g_TextureSet.textureSetInfo[nCntTextureSet].fRateWidth = RATE;
		g_TextureSet.textureSetInfo[nCntTextureSet].fRateHeight = RATE;
		g_TextureSet.textureSetInfo[nCntTextureSet].fMoveRateWidth = RATE;
		g_TextureSet.textureSetInfo[nCntTextureSet].fMoveRateHeight = RATE;
		g_TextureSet.textureSetInfo[nCntTextureSet].fWidth = 0.0f;
		g_TextureSet.textureSetInfo[nCntTextureSet].fHeight = 0.0f;
		g_TextureSet.textureSetInfo[nCntTextureSet].fAngle = 0.0f;
		g_TextureSet.textureSetInfo[nCntTextureSet].fLength = 0.0f;
		g_TextureSet.textureSetInfo[nCntTextureSet].bMaxSize = false;
		g_TextureSet.textureSetInfo[nCntTextureSet].bNormalSize = false;
		g_TextureSet.textureSetInfo[nCntTextureSet].nType = -1;
		g_TextureSet.textureSetInfo[nCntTextureSet].nTexType = -1;
		g_TextureSet.textureSetInfo[nCntTextureSet].bUse = false;
	}

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX * MAX_TEXTURE_SET,	// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffTextureSet,
		NULL)))
	{
		return E_FAIL;
	}

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTextureSet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE_SET; nCntTexture++)
	{
		// 頂点座標の設定
		SetVertexTextureSet(nCntTexture);

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
	g_pVtxBuffTextureSet->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// 背景の終了処理
//-----------------------------------------------------------------
void UninitTextureSet(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffTextureSet != NULL)
	{
		g_pVtxBuffTextureSet->Release();
		g_pVtxBuffTextureSet = NULL;
	}
}

//-----------------------------------------------------------------
// 背景の更新処理
//-----------------------------------------------------------------
void UpdateTextureSet(void)
{
	// テクスチャ設置情報の取得
	TextureSetInfo *pTextureSetInfo = &g_TextureSet.textureSetInfo[0];

	for (int nCntTextureSet = 0; nCntTextureSet < MAX_TEXTURE_SET; nCntTextureSet++, pTextureSetInfo++)
	{
		if (pTextureSetInfo->bUse == true)
		{
			if (pTextureSetInfo->nType == 0)
			{
				if (pTextureSetInfo->bNormalSize == false)
				{
					if (pTextureSetInfo->bMaxSize == false)
					{
						// サイズ増減の割合更新
						pTextureSetInfo->fRateWidth -= MOVE_RATE;
						pTextureSetInfo->fRateHeight -= MOVE_RATE;

						// サイズ増減量更新
						pTextureSetInfo->fMoveRateWidth += pTextureSetInfo->fRateWidth;
						pTextureSetInfo->fMoveRateHeight += pTextureSetInfo->fRateHeight;

						// サイズ更新
						pTextureSetInfo->fWidth = pTextureSetInfo->fWidthDest * pTextureSetInfo->fMoveRateWidth;
						pTextureSetInfo->fHeight = pTextureSetInfo->fHeightDest * pTextureSetInfo->fMoveRateHeight;

						// 
						if ((pTextureSetInfo->fWidth >= pTextureSetInfo->fWidthDest) && (pTextureSetInfo->fHeight >= pTextureSetInfo->fHeightDest))
						{
							pTextureSetInfo->bMaxSize = true;
						}
					}
					else
					{
						// サイズ増減の割合更新
						pTextureSetInfo->fRateWidth -= RATE / 30.0f;
						pTextureSetInfo->fRateHeight -= RATE / 30.0f;

						// サイズ増減量更新
						pTextureSetInfo->fMoveRateWidth += pTextureSetInfo->fRateWidth;
						pTextureSetInfo->fMoveRateHeight += pTextureSetInfo->fRateHeight;

						// サイズ更新
						pTextureSetInfo->fWidth = pTextureSetInfo->fWidthDest * pTextureSetInfo->fMoveRateWidth;
						pTextureSetInfo->fHeight = pTextureSetInfo->fHeightDest * pTextureSetInfo->fMoveRateHeight;

						if ((pTextureSetInfo->fWidth <= pTextureSetInfo->fWidthDest) && (pTextureSetInfo->fHeight <= pTextureSetInfo->fHeightDest))
						{
							pTextureSetInfo->bNormalSize = true;
						}
					}
				}
			}
			// 角度と対角線の長さを計算
			pTextureSetInfo->fAngle = atan2f(pTextureSetInfo->fWidth / 2.0f, pTextureSetInfo->fHeight / 2.0f);
			pTextureSetInfo->fLength = sqrtf((pTextureSetInfo->fWidth / 2.0f) * (pTextureSetInfo->fWidth / 2.0f) + (pTextureSetInfo->fHeight / 2.0f) * (pTextureSetInfo->fHeight / 2.0f));

			// α値の減少
			pTextureSetInfo->col.a -= pTextureSetInfo->fRemoveAlpha;

			// α値が0.0fより小さくなったら使用状態をfalseにしてα値を初期化する
			if (pTextureSetInfo->col.a < 0.0f)
			{
				pTextureSetInfo->bUse = false;
				pTextureSetInfo->col.a = 1.0f;
			}
			// 頂点座標の更新
			SetVertexTextureSet(nCntTextureSet);
		}
	}
}

//-----------------------------------------------------------------
// 背景の描画処理
//-----------------------------------------------------------------
void DrawTextureSet(void)
{
	// テクスチャ設置情報の取得
	Texture *pTexture = GetUITexture();;

	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTextureSet, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE_SET; nCntTexture++)
	{
		if (g_TextureSet.textureSetInfo[nCntTexture].bUse == true)
		{
			pDevice->SetTexture(0, pTexture->TextureInfo[g_TextureSet.textureSetInfo[nCntTexture].nTexType].pTexture);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTexture * 4, 2);
		}
	}
}

//-----------------------------------------------------------------
// 頂点座標の設定
//-----------------------------------------------------------------
void SetVertexTextureSet(int nCnt)
{
	// テクスチャ配置情報の取得
	TextureSetInfo *pTextureSetInfo = &g_TextureSet.textureSetInfo[0];

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTextureSet->Lock(0, 0, (void**)&pVtx, 0);

	// 何番目か
	pVtx += nCnt * 4;
	pTextureSetInfo += nCnt;

	// 頂点座標の更新
	pVtx[0].pos.x = pTextureSetInfo->pos.x + sinf(pTextureSetInfo->rot.z + (D3DX_PI * 0.00f - pTextureSetInfo->fAngle)) * pTextureSetInfo->fLength;
	pVtx[0].pos.y = pTextureSetInfo->pos.y + cosf(pTextureSetInfo->rot.z + (D3DX_PI * 0.00f - pTextureSetInfo->fAngle)) * pTextureSetInfo->fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = pTextureSetInfo->pos.x + sinf(pTextureSetInfo->rot.z + (pTextureSetInfo->fAngle + D3DX_PI * 1.00f)) * pTextureSetInfo->fLength;
	pVtx[1].pos.y = pTextureSetInfo->pos.y + cosf(pTextureSetInfo->rot.z + (pTextureSetInfo->fAngle + D3DX_PI * 1.00f)) * pTextureSetInfo->fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = pTextureSetInfo->pos.x + sinf(pTextureSetInfo->rot.z + (pTextureSetInfo->fAngle + D3DX_PI * 0.00f)) * pTextureSetInfo->fLength;
	pVtx[2].pos.y = pTextureSetInfo->pos.y + cosf(pTextureSetInfo->rot.z + (pTextureSetInfo->fAngle + D3DX_PI * 0.00f)) * pTextureSetInfo->fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = pTextureSetInfo->pos.x + sinf(pTextureSetInfo->rot.z + (D3DX_PI * 1.00f - pTextureSetInfo->fAngle)) * pTextureSetInfo->fLength;
	pVtx[3].pos.y = pTextureSetInfo->pos.y + cosf(pTextureSetInfo->rot.z + (D3DX_PI * 1.00f - pTextureSetInfo->fAngle)) * pTextureSetInfo->fLength;
	pVtx[3].pos.z = 0.0f;

	// 頂点カラーの設定
	pVtx[0].col = pTextureSetInfo->col;
	pVtx[1].col = pTextureSetInfo->col;
	pVtx[2].col = pTextureSetInfo->col;
	pVtx[3].col = pTextureSetInfo->col;

	// 頂点バッファをアンロックする
	g_pVtxBuffTextureSet->Unlock();
}

//-----------------------------------------------------------------
// テクスチャの設置
//-----------------------------------------------------------------
void SetTexture(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXCOLOR col,float fRemoveAlpha, 
	float fWidth, float fHeight, float fWidthDest, float fHeightDest ,int type, int textype)
{
	// テクスチャ配置情報の取得
	TextureSetInfo *pTextureSetInfo = &g_TextureSet.textureSetInfo[0];

	for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE_SET; nCntTexture++,pTextureSetInfo++)
	{
		if (pTextureSetInfo->bUse == false)
		{
			// 位置情報の設定
			pTextureSetInfo->pos = pos;

			// 向きの設定
			pTextureSetInfo->rot = rot;

			// 移動量の設定
			pTextureSetInfo->move = move;

			// 色の設定
			pTextureSetInfo->col = col;

			// α値の減少量の設定
			pTextureSetInfo->fRemoveAlpha = fRemoveAlpha;

			// 目的の幅の設定
			pTextureSetInfo->fWidth = fWidth;

			// 目的の高さの設定
			pTextureSetInfo->fHeight = fHeight;

			// 角度と対角線の長さを計算
			pTextureSetInfo->fAngle = atan2f(pTextureSetInfo->fWidth / 2.0f, pTextureSetInfo->fHeight / 2.0f);
			pTextureSetInfo->fLength = sqrtf((pTextureSetInfo->fWidth / 2.0f) * (pTextureSetInfo->fWidth / 2.0f) + (pTextureSetInfo->fHeight / 2.0f) * (pTextureSetInfo->fHeight / 2.0f));

			// 目的の幅の設定
			pTextureSetInfo->fWidthDest = fWidthDest;

			// 目的の高さの設定
			pTextureSetInfo->fHeightDest = fHeightDest;

			// エフェクトタイプの設定
			pTextureSetInfo->nType = type;

			// テクスチャタイプの設定
			pTextureSetInfo->nTexType = textype;

			// 使用状態をtrueにする
			pTextureSetInfo->bUse = true;

			break;
		}
	}
}

//-----------------------------------------------------------------
// テクスチャ配置情報の取得
//-----------------------------------------------------------------
TextureSet *GetTextureSet(void)
{
	return &g_TextureSet;
}