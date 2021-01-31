////////////////////////////////////////////////////////////////////////////////
//
//Contents	: パーティクルの処理 [perticle.cpp]
//Author	: Shota Furuichi
//Since		: 2020/10/26
//
////////////////////////////////////////////////////////////////////////////////
#include "perticle.h"
#include <time.h>

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define MAX_PERTICLE (4096)	//パーティクル最大数
#define PERT_SIZE (10.0f)	//パーティクルサイズ

////////////////////////////////////////////////////////////////////////////////
//構造体の定義
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	D3DXVECTOR3 pos; 
	D3DXVECTOR3 move;
	D3DXCOLOR color;;
	float fRadius;
	int nLife;
	bool bUse;

} PERTICLE;

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
PERTICLE g_Perticle[MAX_PERTICLE];
D3DXVECTOR3 g_posBase;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPerticle = NULL;	//頂点情報
LPDIRECT3DTEXTURE9 g_pTexturePerticle = NULL;		//テクスチャ情報


////////////////////////////////////////////////////////////////////////////////
//初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT InitPerticle(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &g_pTexturePerticle);


	for (int nCntPert = 0; nCntPert < MAX_PERTICLE; nCntPert++)
	{
		g_Perticle[MAX_PERTICLE].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_Perticle[MAX_PERTICLE].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Perticle[MAX_PERTICLE].color = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		g_Perticle[MAX_PERTICLE].fRadius = 0.0f;
		g_Perticle[MAX_PERTICLE].nLife = 0;
		g_Perticle[MAX_PERTICLE].bUse = false;
	}

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PERTICLE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPerticle, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPerticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPert = 0; nCntPert < MAX_PERTICLE; nCntPert++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_Perticle[MAX_PERTICLE].pos.x - g_Perticle[MAX_PERTICLE].fRadius, g_Perticle[MAX_PERTICLE].pos.y + g_Perticle[MAX_PERTICLE].fRadius, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Perticle[MAX_PERTICLE].pos.x - g_Perticle[MAX_PERTICLE].fRadius, g_Perticle[MAX_PERTICLE].pos.y - g_Perticle[MAX_PERTICLE].fRadius, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Perticle[MAX_PERTICLE].pos.x + g_Perticle[MAX_PERTICLE].fRadius, g_Perticle[MAX_PERTICLE].pos.y + g_Perticle[MAX_PERTICLE].fRadius, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Perticle[MAX_PERTICLE].pos.x + g_Perticle[MAX_PERTICLE].fRadius, g_Perticle[MAX_PERTICLE].pos.y - g_Perticle[MAX_PERTICLE].fRadius, 0.0f);

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

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPerticle->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitPerticle(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffPerticle != NULL)
	{
		g_pVtxBuffPerticle->Release();	//開放
		g_pVtxBuffPerticle = NULL;		//初期化
	}

	//テクスチャの開放
	if (g_pTexturePerticle != NULL)
	{
		g_pTexturePerticle->Release();	//開放
		g_pTexturePerticle = NULL;		//初期化
	}
}

////////////////////////////////////////////////////////////////////////////////
//更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdatePerticle(void)
{
	PERTICLE *pPerticle;
	pPerticle = &g_Perticle[0];

	for (int nCntPert = 0; nCntPert < MAX_PERTICLE; nCntPert++, pPerticle++)
	{
		if (pPerticle->bUse == true)
		{

		}
	}
	pPerticle = &g_Perticle[0];

	for (int nCntAppear = 0; nCntAppear < 128; nCntAppear++)
	{
		for (int nCntPert = 0; nCntPert < MAX_PERTICLE; nCntPert++, pPerticle++)
		{
			if (pPerticle->bUse == false)
			{
				pPerticle->pos = g_posBase;
				pPerticle->fRadius = GetRandom(5.0f, 10.0f);
				pPerticle->color = D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f);
				pPerticle->nLife = (int)GetRandom(10.0f, 15.0f);

			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawPerticle(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPerticle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntPert = 0; nCntPert < MAX_PERTICLE; nCntPert++)
	{
		if (g_Perticle[nCntPert].bUse == true)
		{	//弾が使用されている場合
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTexturePerticle);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPert * 4, 2);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//ランダムな数値を取得
////////////////////////////////////////////////////////////////////////////////
float GetRandom(float min, float max)
{
	static int nNum;

	if (nNum == 0)
	{
		srand((unsigned int)time(NULL));
		nNum = 1;
	}

	return min + (int)(rand() * (max - min + 1.0f) / (1.0f + RAND_MAX));
}