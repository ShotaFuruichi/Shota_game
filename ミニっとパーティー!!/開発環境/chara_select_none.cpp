//-----------------------------------------------------------------
//
// キャラセレクトノーン (chara_select_none.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "chara_select_none.h"
#include "chara_select_frame.h"

//-------------------------------------------------------------------
// マクロ定義
//-------------------------------------------------------------------
#define SCORE_X			(970.0f)				// 中心座標(X)
#define SCORE_Y			(50.0f)					// 中心座標(Y)

#define SCORE_WIDTH		(45.0f)					// スコアの幅
#define SCORE_HEIGHT	(80.0f)					// スコアの高さ
#define WIDTH_X			(40.0f)					// スコアを配置する間隔

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCharaSelectNone = NULL;				// キャラセレクトイメージのテクスチャのポインタ
LPDIRECT3DTEXTURE9 g_pTextureCharaSelectNone = NULL;				// キャラセレクトイメージの頂点バッファのポインタ
CharaSelectNone g_aCharaSelectNone[MAX_CHARANONE];						// キャラセレクトイメージの情報
int g_nNumNone;															// 描画数

//-----------------------------------------------------------------
// キャラセレクトノーンの初期化処理
//-----------------------------------------------------------------
HRESULT InitCharaSelectNone(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// モード情報の取得
	int nNumPlayer = GetFrame();

	g_nNumNone = MAX_CHARANONE - nNumPlayer;

	// テクスチャの読み込み	
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/chara_select_none.jpg", &g_pTextureCharaSelectNone);

	// 変数の初期化
	for (int nCntNone = 0; nCntNone < MAX_CHARANONE; nCntNone++)
	{
		g_aCharaSelectNone[nCntNone].pos = D3DXVECTOR3(1120.0f - nCntNone * 320.0f, 255.0f, 0.0f);
		g_aCharaSelectNone[nCntNone].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aCharaSelectNone[nCntNone].fWidth = 320.0f;
		g_aCharaSelectNone[nCntNone].fHeight = 520.0f;
		g_aCharaSelectNone[nCntNone].bSelect = false;
	}

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX * MAX_CHARANONE, // 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffCharaSelectNone,
		NULL)))
	{
		return E_FAIL;
	}

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffCharaSelectNone->Lock(0, 0, (void**)&pVtx, 0);

	// 初期化
	for (int nCntImage = 0; nCntImage < MAX_CHARANONE; nCntImage++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aCharaSelectNone[nCntImage].pos.x - (g_aCharaSelectNone[nCntImage].fWidth / 2), g_aCharaSelectNone[nCntImage].pos.y + (g_aCharaSelectNone[nCntImage].fHeight / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aCharaSelectNone[nCntImage].pos.x - (g_aCharaSelectNone[nCntImage].fWidth / 2), g_aCharaSelectNone[nCntImage].pos.y - (g_aCharaSelectNone[nCntImage].fHeight / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aCharaSelectNone[nCntImage].pos.x + (g_aCharaSelectNone[nCntImage].fWidth / 2), g_aCharaSelectNone[nCntImage].pos.y + (g_aCharaSelectNone[nCntImage].fHeight / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aCharaSelectNone[nCntImage].pos.x + (g_aCharaSelectNone[nCntImage].fWidth / 2), g_aCharaSelectNone[nCntImage].pos.y - (g_aCharaSelectNone[nCntImage].fHeight / 2), 0.0f);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = g_aCharaSelectNone[nCntImage].col;
		pVtx[1].col = g_aCharaSelectNone[nCntImage].col;
		pVtx[2].col = g_aCharaSelectNone[nCntImage].col;
		pVtx[3].col = g_aCharaSelectNone[nCntImage].col;

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// スコアの情報を次にうつす
		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffCharaSelectNone->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// キャラセレクトノーンの終了処理
//-----------------------------------------------------------------
void UninitCharaSelectNone(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffCharaSelectNone != NULL)
	{
		g_pVtxBuffCharaSelectNone->Release();
		g_pVtxBuffCharaSelectNone = NULL;
	}

	// テクスチャの開放
	if (g_pTextureCharaSelectNone != NULL)
	{
		g_pTextureCharaSelectNone->Release();
		g_pTextureCharaSelectNone = NULL;
	}
}

//-----------------------------------------------------------------
// キャラセレクトノーンの更新処理
//-----------------------------------------------------------------
void UpdateCharaSelectNone(void)
{

}

//-----------------------------------------------------------------
// キャラセレクトノーンの描画処理
//-----------------------------------------------------------------
void DrawCharaSelectNone(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// モード情報の取得
	int nNumPlayer = GetFrame();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffCharaSelectNone, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定と描画
	for (int nCntTexture = 0; nCntTexture < 4 - nNumPlayer; nCntTexture++)
	{
		pDevice->SetTexture(0, g_pTextureCharaSelectNone);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTexture * 4, 2);
	}
}