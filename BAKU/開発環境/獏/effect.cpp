////////////////////////////////////////////////////////////////////////////////
//
//Contents	: エフェクト [effect.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/09/07
//
////////////////////////////////////////////////////////////////////////////////
#include "effect.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define EFFECT_SIZE (100.0f)			//エフェクトのサイズ
#define ALPHA_DOWN (0.03f)				//α値減少量

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;		//頂点バッファへの設定
EFFECT g_aEffect[MAX_EFFECT];							//エフェクトの情報

////////////////////////////////////////////////////////////////////////////////
//エフェクトの初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT InitEffect(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_3D *pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\effect000.jpg", &g_pTextureEffect);

	//初期化
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0, 0, 0.0f);
		g_aEffect[nCntEffect].bUse = false;
		g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffEffect, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//頂点座標の設定
		SetVertexEffect(nCntEffect);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーの設定
		SetColorEffect(nCntEffect);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}
		//頂点バッファをアンロックする
		g_pVtxBuffEffect->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//エフェクトの終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitEffect(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();	//開放
		g_pVtxBuffEffect = NULL;		//初期化
	}
	//テクスチャの開放

	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();	//開放
		g_pTextureEffect = NULL;		//初期化
	}
}

////////////////////////////////////////////////////////////////////////////////
//エフェクトの更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateEffect(void)
{
	//変数宣言
	EFFECT *pEffect;

	pEffect = &g_aEffect[0];

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		//色の設定
		SetColorEffect(nCntEffect);

		if (pEffect->bUse == true)
		{	//エフェクトが使用されているとき

			//α値減少
			if (pEffect->col.a > 0)
			{
				pEffect->col.a -= ALPHA_DOWN;
			}
			else
			{
				pEffect->bUse = false;
				pEffect->col.a = 1.0f;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//エフェクトの描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawEffect(void)
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

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aEffect[nCntEffect].mtxworld);

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
			g_aEffect[nCntEffect].mtxworld._11 = mtxView._11;
			g_aEffect[nCntEffect].mtxworld._12 = mtxView._21;
			g_aEffect[nCntEffect].mtxworld._13 = mtxView._31;
			g_aEffect[nCntEffect].mtxworld._21 = mtxView._12;
			g_aEffect[nCntEffect].mtxworld._22 = mtxView._22;
			g_aEffect[nCntEffect].mtxworld._23 = mtxView._32;
			g_aEffect[nCntEffect].mtxworld._31 = mtxView._13;
			g_aEffect[nCntEffect].mtxworld._32 = mtxView._23;
			g_aEffect[nCntEffect].mtxworld._33 = mtxView._33;
#endif

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCntEffect].pos.x, g_aEffect[nCntEffect].pos.y, g_aEffect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCntEffect].mtxworld, &g_aEffect[nCntEffect].mtxworld, &mtxTrans);

			//ワールドマトリックス
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntEffect].mtxworld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEffect);

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
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	//変数宣言
	EFFECT *pEffect;

	pEffect = &g_aEffect[0];

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
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
void SetVertexEffect(int nIdx)
{
	//変数宣言
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_aEffect[nIdx].pos.x - EFFECT_SIZE, g_aEffect[nIdx].pos.y - EFFECT_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aEffect[nIdx].pos.x - EFFECT_SIZE, g_aEffect[nIdx].pos.y + EFFECT_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aEffect[nIdx].pos.x + EFFECT_SIZE, g_aEffect[nIdx].pos.y - EFFECT_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aEffect[nIdx].pos.x + EFFECT_SIZE, g_aEffect[nIdx].pos.y + EFFECT_SIZE, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//色の設定
////////////////////////////////////////////////////////////////////////////////
void SetColorEffect(int nIdx)
{
	//変数宣言
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//頂点カラーの設定
	pVtx[0].col = g_aEffect[nIdx].col;
	pVtx[1].col = g_aEffect[nIdx].col;
	pVtx[2].col = g_aEffect[nIdx].col;
	pVtx[3].col = g_aEffect[nIdx].col;

	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}