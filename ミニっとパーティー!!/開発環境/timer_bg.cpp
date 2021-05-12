//-----------------------------------------------------------------
//
// タイマー背景 (timer_bg.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "timer_bg.h"
#include "sound.h"

//-------------------------------------------------------------------
// マクロ定義
//-------------------------------------------------------------------
#define TIMERBG_X				(SCREEN_WIDTH / 2.0f)	// マルチモードのタイマーの中心座標(X)
#define TIMERBG_Y				(60.0f)					// マルチモードのタイマーの中心座標(Y)

#define TIMERBG_WIDTH			(200.0f)					// タイマーの幅
#define TIMERBG_HEIGHT			(80.0f)					// タイマーの高さ

#define MAX_PATTERN				(1)						// アニメーションパターンNo.の最大数

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimerBg = NULL;	// タイマーのテクスチャのポインタ
LPDIRECT3DTEXTURE9 g_pTextureTimerBg = NULL;		// タイマーの頂点バッファのポインタ
D3DXVECTOR3 g_posTimerBg;							// タイマーの中心座標

//-----------------------------------------------------------------
// タイマー背景の初期化処理
//-----------------------------------------------------------------
HRESULT InitTimerBg(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// テクスチャの読み込み	
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/time.png", &g_pTextureTimerBg);

	// 変数の初期化
	g_posTimerBg = D3DXVECTOR3(TIMERBG_X, TIMERBG_Y, 0.0f);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX * MAX_PATTERN, // 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimerBg,
		NULL)))
	{
		return E_FAIL;
	}

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTimerBg->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_posTimerBg.x - (TIMERBG_WIDTH / 2), g_posTimerBg.y + (TIMERBG_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posTimerBg.x - (TIMERBG_WIDTH / 2), g_posTimerBg.y - (TIMERBG_HEIGHT / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posTimerBg.x + (TIMERBG_WIDTH / 2), g_posTimerBg.y + (TIMERBG_HEIGHT / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posTimerBg.x + (TIMERBG_WIDTH / 2), g_posTimerBg.y - (TIMERBG_HEIGHT / 2), 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	// テクスチャの更新
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	
	// 頂点バッファをアンロックする
	g_pVtxBuffTimerBg->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// タイマー背景の終了処理
//-----------------------------------------------------------------
void UninitTimerBg(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffTimerBg != NULL)
	{
		g_pVtxBuffTimerBg->Release();
		g_pVtxBuffTimerBg = NULL;
	}

	// テクスチャの開放
	if (g_pTextureTimerBg != NULL)
	{
		g_pTextureTimerBg->Release();
		g_pTextureTimerBg = NULL;
	}
}

//-----------------------------------------------------------------
// タイマー背景の更新処理
//-----------------------------------------------------------------
void UpdateTimerBg(void)
{

}

//-----------------------------------------------------------------
// タイマー背景の描画処理
//-----------------------------------------------------------------
void DrawTimerBg(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTimerBg, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定と描画
	for (int nCntTimer = 0; nCntTimer < MAX_PATTERN; nCntTimer++)
	{// スコアの表示
		pDevice->SetTexture(0, g_pTextureTimerBg);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTimer * 4, 2);
	}
}