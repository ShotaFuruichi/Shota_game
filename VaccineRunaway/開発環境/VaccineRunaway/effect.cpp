////////////////////////////////////////////////////////////////////////////////
//
//Contents	: エフェクト [effect.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/09/07
//
////////////////////////////////////////////////////////////////////////////////
#include "effect.h"
#include "sound.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define EFFECT_SIZE (25.0f)			//エフェクトのサイズ
#define ALPHA_DOWN (0.04f)			//α値減少量

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
	VERTEX_2D *pVtx;

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
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffEffect, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//頂点座標の設定
		SetVertexEffect(nCntEffect);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		SetColorEffect(nCntEffect);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;

		//頂点バッファをアンロックする
		g_pVtxBuffEffect->Unlock();
	}
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
			if (pEffect->col.a >= 0)
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

	//デバイスの取得
	pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			//ソース(描画元：絵、画像)の合成方法の設定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);				//デスティネーション(描画先：下地)の合成方法の設定

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureEffect);

		if (g_aEffect[nCntEffect].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
		}
	}

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			//ソース(描画元：絵、画像)の合成方法の設定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		//デスティネーション(描画先：下地)の合成方法の設定
}

////////////////////////////////////////////////////////////////////////////////
//エフェクトのセット処理
////////////////////////////////////////////////////////////////////////////////
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	//変数宣言
	EFFECT *pEffect;

	pEffect = &g_aEffect[0];

	for (int nCntExplosion = 0; nCntExplosion < MAX_EFFECT; nCntExplosion++, pEffect++)
	{
		if (pEffect->bUse == false)
		{	//エフェクトが使用されていないとき

			pEffect->pos = pos;

			pEffect->col = col;

			//頂点座標の設定
			SetVertexEffect(nCntExplosion);

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
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_aEffect[nIdx].pos.x - EFFECT_SIZE, g_aEffect[nIdx].pos.y + EFFECT_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aEffect[nIdx].pos.x - EFFECT_SIZE, g_aEffect[nIdx].pos.y - EFFECT_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aEffect[nIdx].pos.x + EFFECT_SIZE, g_aEffect[nIdx].pos.y + EFFECT_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aEffect[nIdx].pos.x + EFFECT_SIZE, g_aEffect[nIdx].pos.y - EFFECT_SIZE, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//色の設定
////////////////////////////////////////////////////////////////////////////////
void SetColorEffect(int nIdx)
{
	//変数宣言
	VERTEX_2D *pVtx;

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