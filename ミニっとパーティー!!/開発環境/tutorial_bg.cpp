//-----------------------------------------------------------------
//
// チュートリアル画面の背景 (tutorial_bg.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "tutorial_bg.h"

//-----------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------
#define MAX_IMAGE				(1)							// 背景の種類

#define TUTORIAL_BG_X			(SCREEN_WIDTH / 2)			// チュートリアル画面背景の位置(X座標)
#define TUTORIAL_BG_Y			(SCREEN_HEIGHT / 2)			// チュートリアル画面背景の位置(Y座標)
#define TUTORIAL_BG_WIDTH		(SCREEN_WIDTH)				// チュートリアル画面背景の幅
#define TUTORIAL_BG_HEIGHT		(SCREEN_HEIGHT)				// チュートリアル画面背景の高さ

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorialBg = NULL;		// チュートリアル画面背景の頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureTutorialBg[MAX_IMAGE] = {};	// チュートリアル画面背景のテクスチャのポインタ
D3DXVECTOR3 g_posTutorialBg;

//-----------------------------------------------------------------
// チュートリアル画面背景の初期化処理
//-----------------------------------------------------------------
HRESULT InitTutorialBg(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し、初期化
	pDevice = GetDevice();
	g_posTutorialBg = D3DXVECTOR3(TUTORIAL_BG_X, TUTORIAL_BG_Y, 0.0f);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/tutorial_bg.jpg", &g_pTextureTutorialBg[0]);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX * MAX_IMAGE,	// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorialBg,
		NULL)))
	{
		return E_FAIL;
	}

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTutorialBg->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBg = 0; nCntBg < MAX_IMAGE; nCntBg++)
	{
		// 頂点座標の設定
		SetVertexTutorialBg(nCntBg);

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
	g_pVtxBuffTutorialBg->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// チュートリアルセレクト画面背景の終了処理
//-----------------------------------------------------------------
void UninitTutorialBg(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffTutorialBg != NULL)
	{
		g_pVtxBuffTutorialBg->Release();
		g_pVtxBuffTutorialBg = NULL;
	}

	// テクスチャの開放
	for (int nCntBg = 0; nCntBg < MAX_IMAGE; nCntBg++)
	{
		if (g_pTextureTutorialBg[nCntBg] != NULL)
		{
			g_pTextureTutorialBg[nCntBg]->Release();
			g_pTextureTutorialBg[nCntBg] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// チュートリアル画面背景の更新処理
//-----------------------------------------------------------------
void UpdateTutorialBg(void)
{

}

//-----------------------------------------------------------------
// チュートリアル画面の描画処理
//-----------------------------------------------------------------
void DrawTutorialBg(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorialBg, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for (int nCntBg = 0; nCntBg < MAX_IMAGE; nCntBg++)
	{
		pDevice->SetTexture(0, g_pTextureTutorialBg[nCntBg]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBg * 4, 2);
	}
}

//-----------------------------------------------------------------
// チュートリアル画面の頂点座標の設定
//-----------------------------------------------------------------
void SetVertexTutorialBg(int nCnt)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTutorialBg->Lock(0, 0, (void**)&pVtx, 0);

	// 何番目か
	pVtx += nCnt * 4;

	// 頂点座標の更新
	pVtx[0].pos = D3DXVECTOR3(g_posTutorialBg.x - (TUTORIAL_BG_WIDTH / 2), g_posTutorialBg.y + (TUTORIAL_BG_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posTutorialBg.x - (TUTORIAL_BG_WIDTH / 2), g_posTutorialBg.y - (TUTORIAL_BG_HEIGHT / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posTutorialBg.x + (TUTORIAL_BG_WIDTH / 2), g_posTutorialBg.y + (TUTORIAL_BG_HEIGHT / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posTutorialBg.x + (TUTORIAL_BG_WIDTH / 2), g_posTutorialBg.y - (TUTORIAL_BG_HEIGHT / 2), 0.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffTutorialBg->Unlock();
}