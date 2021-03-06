//-----------------------------------------------------------------
//
// タイトル画面の背景 (title_bg.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "title_bg.h"

//-----------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------
#define MAX_PATTERN			(1)							// 背景の種類

#define TITLE_BG_X			(SCREEN_WIDTH / 2)			// タイトル背景の位置(X座標)
#define TITLE_BG_Y			(SCREEN_HEIGHT / 2)			// タイトル背景の位置(Y座標)
#define TITLE_BG_WIDTH		(SCREEN_WIDTH)				// タイトル背景の幅
#define TITLE_BG_HEIGHT		(SCREEN_HEIGHT)				// タイトル背景の高さ

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleBg = NULL;				// 背景の頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureTitleBg[MAX_PATTERN] = {};			// 背景のテクスチャのポインタ
D3DXVECTOR3 g_posTitleBg;

//-----------------------------------------------------------------
// 背景の初期化処理
//-----------------------------------------------------------------
HRESULT InitTitleBg(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し、初期化
	pDevice = GetDevice();
	g_posTitleBg = D3DXVECTOR3(TITLE_BG_X, TITLE_BG_Y, 0.0f);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title_bg.png", &g_pTextureTitleBg[0]);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX * MAX_PATTERN,	// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitleBg,
		NULL)))
	{
		return E_FAIL;
	}

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitleBg->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBg = 0; nCntBg < MAX_PATTERN; nCntBg++)
	{
		// 頂点座標の設定
		SetVertexTitleBg(nCntBg);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// 情報の更新
		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffTitleBg->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// 背景の終了処理
//-----------------------------------------------------------------
void UninitTitleBg(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffTitleBg != NULL)
	{
		g_pVtxBuffTitleBg->Release();
		g_pVtxBuffTitleBg = NULL;
	}

	// テクスチャの開放
	for (int nCntBg = 0; nCntBg < MAX_PATTERN; nCntBg++)
	{
		if (g_pTextureTitleBg[nCntBg] != NULL)
		{
			g_pTextureTitleBg[nCntBg]->Release();
			g_pTextureTitleBg[nCntBg] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// 背景の更新処理
//-----------------------------------------------------------------
void UpdateTitleBg(void)
{

}

//-----------------------------------------------------------------
// 背景の描画処理
//-----------------------------------------------------------------
void DrawTitleBg(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitleBg, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for (int nCntBg = 0; nCntBg < MAX_PATTERN; nCntBg++)
	{
		pDevice->SetTexture(0, g_pTextureTitleBg[nCntBg]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBg * 4, 2);
	}
}

//-----------------------------------------------------------------
// 頂点座標の設定
//-----------------------------------------------------------------
void SetVertexTitleBg(int nCnt)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitleBg->Lock(0, 0, (void**)&pVtx, 0);

	// 何番目か
	pVtx += nCnt * 4;

	// 頂点座標の更新
	pVtx[0].pos = D3DXVECTOR3(g_posTitleBg.x - (TITLE_BG_WIDTH / 2), g_posTitleBg.y + (TITLE_BG_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posTitleBg.x - (TITLE_BG_WIDTH / 2), g_posTitleBg.y - (TITLE_BG_HEIGHT / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posTitleBg.x + (TITLE_BG_WIDTH / 2), g_posTitleBg.y + (TITLE_BG_HEIGHT / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posTitleBg.x + (TITLE_BG_WIDTH / 2), g_posTitleBg.y - (TITLE_BG_HEIGHT / 2), 0.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffTitleBg->Unlock();
}