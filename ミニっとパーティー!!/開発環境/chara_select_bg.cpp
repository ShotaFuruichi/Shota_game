//-----------------------------------------------------------------
//
// キャラセレクト画面の背景 (chara_select_bg.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "chara_select_bg.h"

//-----------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------
#define MAX_PATTERN					(1)							// 背景の種類

#define CHARASELECT_BG_X			(SCREEN_WIDTH / 2)			// キャラセレクト画面背景の位置(X座標)
#define CHARASELECT_BG_Y			(SCREEN_HEIGHT / 2)			// キャラセレクト画面背景の位置(Y座標)
#define CHARASELECT_BG_WIDTH		(SCREEN_WIDTH)				// キャラセレクト画面背景の幅
#define CHARASELECT_BG_HEIGHT		(SCREEN_HEIGHT)				// キャラセレクト画面背景の高さ

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCharaSelectBg = NULL;			// キャラセレクト画面背景の頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureCharaSelectBg[MAX_PATTERN] = {};	// キャラセレクト画面背景のテクスチャのポインタ
D3DXVECTOR3 g_posCharaSelectBg;

//-----------------------------------------------------------------
// キャラセレクト画面背景の初期化処理
//-----------------------------------------------------------------
HRESULT InitCharaSelectBg(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し、初期化
	pDevice = GetDevice();
	g_posCharaSelectBg = D3DXVECTOR3(CHARASELECT_BG_X, CHARASELECT_BG_Y, 0.0f);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/chara_select_bg.png", &g_pTextureCharaSelectBg[0]);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX * MAX_PATTERN,	// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffCharaSelectBg,
		NULL)))
	{
		return E_FAIL;
	}

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffCharaSelectBg->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBg = 0; nCntBg < MAX_PATTERN; nCntBg++)
	{
		// 頂点座標の設定
		SetVertexCharaSelectBg(nCntBg);

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
	g_pVtxBuffCharaSelectBg->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// キャラセレクト画面背景の終了処理
//-----------------------------------------------------------------
void UninitCharaSelectBg(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffCharaSelectBg != NULL)
	{
		g_pVtxBuffCharaSelectBg->Release();
		g_pVtxBuffCharaSelectBg = NULL;
	}

	// テクスチャの開放
	for (int nCntBg = 0; nCntBg < MAX_PATTERN; nCntBg++)
	{
		if (g_pTextureCharaSelectBg[nCntBg] != NULL)
		{
			g_pTextureCharaSelectBg[nCntBg]->Release();
			g_pTextureCharaSelectBg[nCntBg] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// キャラセレクト画面背景の更新処理
//-----------------------------------------------------------------
void UpdateCharaSelectBg(void)
{

}

//-----------------------------------------------------------------
// キャラセレクト画面の描画処理
//-----------------------------------------------------------------
void DrawCharaSelectBg(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffCharaSelectBg, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for (int nCntBg = 0; nCntBg < MAX_PATTERN; nCntBg++)
	{
		pDevice->SetTexture(0, g_pTextureCharaSelectBg[nCntBg]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBg * 4, 2);
	}
}

//-----------------------------------------------------------------
// キャラセレクト画面の頂点座標の設定
//-----------------------------------------------------------------
void SetVertexCharaSelectBg(int nCnt)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffCharaSelectBg->Lock(0, 0, (void**)&pVtx, 0);

	// 何番目か
	pVtx += nCnt * 4;

	// 頂点座標の更新
	pVtx[0].pos = D3DXVECTOR3(g_posCharaSelectBg.x - (CHARASELECT_BG_WIDTH / 2), g_posCharaSelectBg.y + (CHARASELECT_BG_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posCharaSelectBg.x - (CHARASELECT_BG_WIDTH / 2), g_posCharaSelectBg.y - (CHARASELECT_BG_HEIGHT / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posCharaSelectBg.x + (CHARASELECT_BG_WIDTH / 2), g_posCharaSelectBg.y + (CHARASELECT_BG_HEIGHT / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posCharaSelectBg.x + (CHARASELECT_BG_WIDTH / 2), g_posCharaSelectBg.y - (CHARASELECT_BG_HEIGHT / 2), 0.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffCharaSelectBg->Unlock();
}