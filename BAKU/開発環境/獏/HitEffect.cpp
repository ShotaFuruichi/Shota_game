////////////////////////////////////////////////////////////////////////////////
//
//Contents	: エフェクト [effect.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/09/07
//
////////////////////////////////////////////////////////////////////////////////
#include "HitEffect.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define HITEFFECT_SIZE (50.0f)			//エフェクトのサイズ
#define ALPHA_DOWN (0.03f)				//α値減少量

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9 g_pTextureHitEffect = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHitEffect = NULL;			//頂点バッファへの設定
HITEFFECT g_aHitEffect[MAX_HITEFFECT];							//エフェクトの情報

////////////////////////////////////////////////////////////////////////////////
//エフェクトの初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT InitHitEffect(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_3D *pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\HitEffect.png", &g_pTextureHitEffect);

	//初期化
	for (int nCntEffect = 0; nCntEffect < MAX_HITEFFECT; nCntEffect++)
	{
		g_aHitEffect[nCntEffect].pos = D3DXVECTOR3(0, 0, 0.0f);
		g_aHitEffect[nCntEffect].bUse = false;
		g_aHitEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_HITEFFECT, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffHitEffect, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffHitEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_HITEFFECT; nCntEffect++)
	{
		//頂点座標の設定
		SetVertexHitEffect(nCntEffect);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーの設定
		SetColorHitEffect(nCntEffect);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.143f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.143f, 0.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffHitEffect->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//エフェクトの終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitHitEffect(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffHitEffect != NULL)
	{
		g_pVtxBuffHitEffect->Release();	//開放
		g_pVtxBuffHitEffect = NULL;		//初期化
	}
	//テクスチャの開放

	if (g_pTextureHitEffect != NULL)
	{
		g_pTextureHitEffect->Release();	//開放
		g_pTextureHitEffect = NULL;		//初期化
	}
}

////////////////////////////////////////////////////////////////////////////////
//エフェクトの更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateHitEffect(void)
{
	//変数宣言
	HITEFFECT *pEffect;
	VERTEX_3D *pVtx;
	static int nCntAnim[MAX_HITEFFECT] = {};
	static int nCnt = 0;
	static float f[MAX_HITEFFECT] = {0.5f};

	pEffect = &g_aHitEffect[0];

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffHitEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_HITEFFECT; nCntEffect++, pEffect++)
	{
		if (pEffect->bUse == true)
		{	//エフェクトが使用されているとき

			//色の設定
			SetColorHitEffect(nCntEffect);


			if (nCntAnim[nCntEffect] < 6)
			{
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(nCntAnim[nCntEffect] * (1.0f / 7), f[nCntEffect]);
				pVtx[1].tex = D3DXVECTOR2(nCntAnim[nCntEffect] * (1.0f / 7), (f[nCntEffect] - 0.5f));
				pVtx[2].tex = D3DXVECTOR2((nCntAnim[nCntEffect] + 1) * (1.0f / 7), f[nCntEffect]);
				pVtx[3].tex = D3DXVECTOR2((nCntAnim[nCntEffect] + 1) * (1.0f / 7), (f[nCntEffect] - 0.5f));
			}
			else if (nCntAnim[nCntEffect] >= 6)
			{
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2((nCntAnim[nCntEffect] / 2) * (1.0f / 7), f[nCntEffect]);
				pVtx[1].tex = D3DXVECTOR2((nCntAnim[nCntEffect] / 2) * (1.0f / 7), (f[nCntEffect] - 0.5f));
				pVtx[2].tex = D3DXVECTOR2(((nCntAnim[nCntEffect] / 2) + 1) * (1.0f / 7), f[nCntEffect]);
				pVtx[3].tex = D3DXVECTOR2(((nCntAnim[nCntEffect] / 2) + 1) * (1.0f / 7), (f[nCntEffect] - 0.5f));
			}

			nCntAnim[nCntEffect]++;

			if (nCntAnim[nCntEffect] == 6)
			{
				f[nCntEffect] = 1.0f;
			}

			if (nCntAnim[nCntEffect] == 13)
			{
				pEffect->bUse = false;
				f[nCntEffect] = 0.5f;
				nCntAnim[nCntEffect] = 0;
			}
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffHitEffect->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//エフェクトの描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawHitEffect(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxTrans;

	//デバイスの取得
	pDevice = GetDevice();

	// Zバッファを適用
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//加算合成を適用
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//ライティングの無効
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntEffect = 0; nCntEffect < MAX_HITEFFECT; nCntEffect++)
	{
		if (g_aHitEffect[nCntEffect].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aHitEffect[nCntEffect].mtxworld);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);
#if 0
			//ポリゴンをカメラに対して正面に向ける
			//逆行列を求める
			D3DXMatrixInverse(&g_aEffect[nCntEffect].mtxworld, NULL, &mtxView);

			//平行移動の部分は無視する
			g_aEffect[nCntEffect].mtxworld._41 = 0.0f;
			g_aEffect[nCntEffect].mtxworld._42 = 0.0f;
			g_aEffect[nCntEffect].mtxworld._43 = 0.0f;
#endif

#if 1
			g_aHitEffect[nCntEffect].mtxworld._11 = mtxView._11;
			g_aHitEffect[nCntEffect].mtxworld._12 = mtxView._21;
			g_aHitEffect[nCntEffect].mtxworld._13 = mtxView._31;
			g_aHitEffect[nCntEffect].mtxworld._21 = mtxView._12;
			g_aHitEffect[nCntEffect].mtxworld._22 = mtxView._22;
			g_aHitEffect[nCntEffect].mtxworld._23 = mtxView._32;
			g_aHitEffect[nCntEffect].mtxworld._31 = mtxView._13;
			g_aHitEffect[nCntEffect].mtxworld._32 = mtxView._23;
			g_aHitEffect[nCntEffect].mtxworld._33 = mtxView._33;
#endif

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aHitEffect[nCntEffect].pos.x, g_aHitEffect[nCntEffect].pos.y, g_aHitEffect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_aHitEffect[nCntEffect].mtxworld, &g_aHitEffect[nCntEffect].mtxworld, &mtxTrans);

			//ワールドマトリックス
			pDevice->SetTransform(D3DTS_WORLD, &g_aHitEffect[nCntEffect].mtxworld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffHitEffect, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureHitEffect);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
		}
	}

	//加算合成を戻す
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// デスティネーションの合成方法の説明

																	// Zバッファを無効
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//ライティングを有効
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

////////////////////////////////////////////////////////////////////////////////
//エフェクトのセット処理
////////////////////////////////////////////////////////////////////////////////
void SetHitEffect(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	//変数宣言
	HITEFFECT *pEffect;

	pEffect = &g_aHitEffect[0];

	for (int nCntEffect = 0; nCntEffect < MAX_HITEFFECT; nCntEffect++, pEffect++)
	{
		if (pEffect->bUse == false)
		{	//エフェクトが使用されていないとき

			pEffect->pos = pos;

			pEffect->col = col;

			//弾を使用する
			pEffect->bUse = true;

			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//エフェクトの頂点座標の設定
////////////////////////////////////////////////////////////////////////////////
void SetVertexHitEffect(int nIdx)
{
	//変数宣言
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffHitEffect->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_aHitEffect[nIdx].pos.x - HITEFFECT_SIZE, g_aHitEffect[nIdx].pos.y - HITEFFECT_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aHitEffect[nIdx].pos.x - HITEFFECT_SIZE, g_aHitEffect[nIdx].pos.y + HITEFFECT_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aHitEffect[nIdx].pos.x + HITEFFECT_SIZE, g_aHitEffect[nIdx].pos.y - HITEFFECT_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aHitEffect[nIdx].pos.x + HITEFFECT_SIZE, g_aHitEffect[nIdx].pos.y + HITEFFECT_SIZE, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffHitEffect->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//色の設定
////////////////////////////////////////////////////////////////////////////////
void SetColorHitEffect(int nIdx)
{
	//変数宣言
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffHitEffect->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//頂点カラーの設定
	pVtx[0].col = g_aHitEffect[nIdx].col;
	pVtx[1].col = g_aHitEffect[nIdx].col;
	pVtx[2].col = g_aHitEffect[nIdx].col;
	pVtx[3].col = g_aHitEffect[nIdx].col;

	//頂点バッファをアンロックする
	g_pVtxBuffHitEffect->Unlock();
}