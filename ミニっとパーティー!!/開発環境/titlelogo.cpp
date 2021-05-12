//-----------------------------------------------------------------
//
// タイトルロゴ (titlelogo.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "titlelogo.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"

//-----------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------
#define MAX_PATTERN				(2)							// アニメーションパターンNo.の最大数

#define TITLELOGO_POS_Y			(200.0f)					// 配置するY座標
#define TITLELOGO_X				(800.0f)					// タイトルロゴ幅
#define TITLELOGO_Y				(300.0f)					// タイトルロゴの高さ
#define HEIGHT_Y				(300.0f)					// タイトルロゴの初期中心Y座標

#define TITLELOGO_ROT_COUNTER	(100)						// 一周するカウント
#define TITLELOGO_ROT_Z			(0.002f)					// タイトルロゴの回転量

#define MOVE_TITLELOGO			(5.0f)						// タイトルロゴの移動量

#define RATE					(0.05f)						// 割合レートの増減量
#define MOVE_RATE				(0.001f)					// 割合レートの増減量

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleLogo = NULL;		// タイトルロゴの頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureTitleLogo = NULL;			// タイトルロゴのテクスチャのポインタ
TITLELOGO g_TitleLogo;									// タイトルロゴの情報
D3DXCOLOR g_color;										// 色
bool g_bFall;											// タイトルロゴが完全に落ちたか判別
int g_TLCnt;											// タイトルロゴの回転カウント

//-----------------------------------------------------------------
// タイトルロゴの初期化処理
//-----------------------------------------------------------------
HRESULT InitTitlelogo(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// 変数の初期化
	g_TitleLogo.pos = D3DXVECTOR3(SCREEN_WIDTH / 2, HEIGHT_Y, 0.0f);
	g_TitleLogo.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_TitleLogo.fRateWidth = RATE;
	g_TitleLogo.fRateHeight = RATE;
	g_TitleLogo.fMoveRateWidth = g_TitleLogo.fRateWidth;
	g_TitleLogo.fMoveRateHeight = g_TitleLogo.fRateHeight;
	g_TitleLogo.fWidth = TITLELOGO_X * g_TitleLogo.fRateWidth;
	g_TitleLogo.fHeight =TITLELOGO_Y * g_TitleLogo.fRateHeight;
	g_TitleLogo.fAngle = atan2f(g_TitleLogo.fWidth, g_TitleLogo.fHeight);
	g_TitleLogo.fLength = sqrtf(g_TitleLogo.fWidth * g_TitleLogo.fWidth + g_TitleLogo.fHeight * g_TitleLogo.fHeight);
	g_TitleLogo.bMaxSize = false;
	g_TitleLogo.bNormalSize = false;
	g_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_bFall = false;
	g_TLCnt = 0;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title_logo.png", &g_pTextureTitleLogo);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX, // 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitleLogo,
		NULL)))
	{
		return E_FAIL;
	}

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	SetVerTexTitleLogo(0);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = g_color;
	pVtx[1].col = g_color;
	pVtx[2].col = g_color;
	pVtx[3].col = g_color;

	// テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffTitleLogo->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// タイトルロゴの終了処理
//-----------------------------------------------------------------
void UninitTitlelogo(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffTitleLogo != NULL)
	{
		g_pVtxBuffTitleLogo->Release();
		g_pVtxBuffTitleLogo = NULL;
	}

	// テクスチャの開放
	if (g_pTextureTitleLogo != NULL)
	{
		g_pTextureTitleLogo->Release();
		g_pTextureTitleLogo = NULL;
	}
}

//-----------------------------------------------------------------
// タイトルロゴの更新処理
//-----------------------------------------------------------------
void UpdateTitlelogo(void)
{
	// フェード情報の取得
	int nFade = GetFade();

	if (g_TitleLogo.bNormalSize == false)
	{
#if 1
		if (g_TitleLogo.bMaxSize == false)
		{
			// サイズ増減の割合更新
			g_TitleLogo.fRateWidth -= MOVE_RATE;
			g_TitleLogo.fRateHeight -= MOVE_RATE;

			// サイズ増減量更新
			g_TitleLogo.fMoveRateWidth += g_TitleLogo.fRateWidth;
			g_TitleLogo.fMoveRateHeight += g_TitleLogo.fRateHeight;

			// サイズ更新
			g_TitleLogo.fWidth = TITLELOGO_X * g_TitleLogo.fMoveRateWidth;
			g_TitleLogo.fHeight = TITLELOGO_Y * g_TitleLogo.fMoveRateHeight;

			// 
			if ((g_TitleLogo.fWidth >= TITLELOGO_X) && (g_TitleLogo.fHeight >= TITLELOGO_Y))
			{
				g_TitleLogo.bMaxSize = true;
			}
		}
		else
		{
			// サイズ増減の割合更新
			g_TitleLogo.fRateWidth -= RATE / 30.0f;
			g_TitleLogo.fRateHeight -= RATE / 30.0f;

			// サイズ増減量更新
			g_TitleLogo.fMoveRateWidth += g_TitleLogo.fRateWidth;
			g_TitleLogo.fMoveRateHeight += g_TitleLogo.fRateHeight;

			// サイズ更新
			g_TitleLogo.fWidth = TITLELOGO_X * g_TitleLogo.fMoveRateWidth;
			g_TitleLogo.fHeight = TITLELOGO_Y * g_TitleLogo.fMoveRateHeight;

			if ((g_TitleLogo.fWidth <= TITLELOGO_X) && (g_TitleLogo.fHeight <= TITLELOGO_Y))
			{
				g_TitleLogo.bNormalSize = true;
			}
		}
#else
		if (g_TitleLogo.bMaxSize == false)
		{
			// サイズ増減の割合更新
			g_TitleLogo.fRateWidth -= MOVE_RATE;
			g_TitleLogo.fRateHeight -= MOVE_RATE;

			// サイズ増減量更新
			g_TitleLogo.fMoveRateWidth += g_TitleLogo.fRateWidth;
			g_TitleLogo.fMoveRateHeight += g_TitleLogo.fRateHeight;

			// サイズ更新
			g_TitleLogo.fWidth = TITLELOGO_X * g_TitleLogo.fMoveRateWidth;
			g_TitleLogo.fHeight = TITLELOGO_Y * g_TitleLogo.fMoveRateHeight;

			// 
			if ((g_TitleLogo.fMoveRateWidth >= 1.0f) && (g_TitleLogo.fMoveRateHeight >= 1.0f))
			{
				g_TitleLogo.bMaxSize = true;
			}
		}
		else
		{
			// サイズ増減の割合更新
			g_TitleLogo.fRateWidth -= RATE / 30.0f;
			g_TitleLogo.fRateHeight -= RATE / 30.0f;

			// サイズ増減量更新
			g_TitleLogo.fMoveRateWidth += g_TitleLogo.fRateWidth;
			g_TitleLogo.fMoveRateHeight += g_TitleLogo.fRateHeight;

			// サイズ更新
			g_TitleLogo.fWidth = TITLELOGO_X * g_TitleLogo.fMoveRateWidth;
			g_TitleLogo.fHeight = TITLELOGO_Y * g_TitleLogo.fMoveRateHeight;

			if ((g_TitleLogo.fMoveRateWidth <= 1.0f) && (g_TitleLogo.fMoveRateHeight <= 1.0f))
			{
				g_TitleLogo.bNormalSize = true;
			}
		}
#endif 
	}
	// 頂点座標の更新
	SetVerTexTitleLogo(0);
}

//-----------------------------------------------------------------
// タイトルロゴの描画処理
//-----------------------------------------------------------------
void DrawTitlelogo(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitleLogo, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	pDevice->SetTexture(0, g_pTextureTitleLogo);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//-----------------------------------------------------------------
// 頂点座標の設定
//-----------------------------------------------------------------
void SetVerTexTitleLogo(int nIdx)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

	// 何番目の情報か
	pVtx += 4 * nIdx;

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_TitleLogo.pos.x - (g_TitleLogo.fWidth / 2.0f), g_TitleLogo.pos.y - (g_TitleLogo.fHeight / 2.0f), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_TitleLogo.pos.x + (g_TitleLogo.fWidth / 2.0f), g_TitleLogo.pos.y - (g_TitleLogo.fHeight / 2.0f), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_TitleLogo.pos.x - (g_TitleLogo.fWidth / 2.0f), g_TitleLogo.pos.y + (g_TitleLogo.fHeight / 2.0f), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_TitleLogo.pos.x + (g_TitleLogo.fWidth / 2.0f), g_TitleLogo.pos.y + (g_TitleLogo.fHeight / 2.0f), 0.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffTitleLogo->Unlock();
}

//-----------------------------------------------------------------
// タイトルロゴ情報の取得
//-----------------------------------------------------------------
bool GetFall(void)
{
	return g_bFall;
}