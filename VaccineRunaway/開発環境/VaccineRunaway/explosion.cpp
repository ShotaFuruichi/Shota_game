////////////////////////////////////////////////////////////////////////////////
//
//Contents	: 爆発処理 [explosion.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/08/05
//
////////////////////////////////////////////////////////////////////////////////
#include "explosion.h"
#include "sound.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define EXPLOSION_SIZE (30.0f)			//爆発のサイズ

#define MAX_ANIM (8)					//アニメーション枚数
#define ANIM_DIVIDE (1.0f  / MAX_ANIM)	//アニメーション画像区切り

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;			//頂点バッファへの設定
EXPLOSION g_aExplosion[MAX_EXPLOSION];						//爆発の情報
int g_nCounterAnimEx[MAX_EXPLOSION];						//アニメーションカウンター
int g_nPatternAnimEx[MAX_EXPLOSION];						//アニメーションパターンNO.

////////////////////////////////////////////////////////////////////////////////
//爆発の初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT InitExplosion(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\explosion000.png", &g_pTextureExplosion);

	//初期化
	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{	
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0, 0, 0.0f);
		g_aExplosion[nCntExplosion].bUse = false;
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(0.0f, 0.0f, 0.f, 0.0f);
	}

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffExplosion, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//頂点座標の設定
		SetVertexExplosion(nCntExplosion);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;

		//頂点バッファをアンロックする
		g_pVtxBuffExplosion->Unlock();
	}
	

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//爆発の終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitExplosion(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();	//開放
		g_pVtxBuffExplosion = NULL;		//初期化
	}
	//テクスチャの開放
	
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();	//開放
		g_pTextureExplosion = NULL;		//初期化
	}
}

////////////////////////////////////////////////////////////////////////////////
//爆発の更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateExplosion(void)
{
	//変数宣言
	EXPLOSION *pExplosion;
	VERTEX_2D *pVtx;

	pExplosion = &g_aExplosion[0];

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pExplosion++)
	{	
		if (pExplosion->bUse == true)
		{	//爆発が使用されているとき

			//アニメーションカウンターの更新
			g_nCounterAnimEx[nCntExplosion]++;

			if (g_nCounterAnimEx[nCntExplosion] % 5 == 0)
			{
				g_nPatternAnimEx[nCntExplosion]++;

				pVtx[0].tex = D3DXVECTOR2(ANIM_DIVIDE * (float)g_nPatternAnimEx[nCntExplosion], 1.0f);
				pVtx[1].tex = D3DXVECTOR2(ANIM_DIVIDE * (float)g_nPatternAnimEx[nCntExplosion], 0.0f);
				pVtx[2].tex = D3DXVECTOR2(ANIM_DIVIDE * ((float)g_nPatternAnimEx[nCntExplosion] + 1.0f), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(ANIM_DIVIDE * ((float)g_nPatternAnimEx[nCntExplosion] + 1.0f), 0.0f);

				if (g_nPatternAnimEx[nCntExplosion] >= MAX_ANIM)
				{
					pExplosion->bUse = false;
					g_nPatternAnimEx[nCntExplosion] = NULL;
				}
			}
		}
		pVtx+= 4;
	}
		//頂点バッファをアンロックする
		g_pVtxBuffExplosion->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//爆発の描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawExplosion(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureExplosion);

		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
		}
	}

}

////////////////////////////////////////////////////////////////////////////////
//爆発のセット処理
////////////////////////////////////////////////////////////////////////////////
void SetExplosion(D3DXVECTOR3 pos)
{
	//変数宣言
	EXPLOSION *pExplosion;

	pExplosion = &g_aExplosion[0];

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pExplosion++)
	{
		if (pExplosion->bUse == false)
		{	//爆発が使用されていないとき

			pExplosion->pos = pos;
			
			//頂点座標の設定
			SetVertexExplosion(nCntExplosion);

			//弾を使用する
			pExplosion->bUse = true;

			break;
		}
	}
	
}

////////////////////////////////////////////////////////////////////////////////
//爆発の頂点座標の設定
////////////////////////////////////////////////////////////////////////////////
void SetVertexExplosion(int nIdx)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nIdx].pos.x - EXPLOSION_SIZE, g_aExplosion[nIdx].pos.y + EXPLOSION_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nIdx].pos.x - EXPLOSION_SIZE, g_aExplosion[nIdx].pos.y - EXPLOSION_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nIdx].pos.x + EXPLOSION_SIZE, g_aExplosion[nIdx].pos.y + EXPLOSION_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nIdx].pos.x + EXPLOSION_SIZE, g_aExplosion[nIdx].pos.y - EXPLOSION_SIZE, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}