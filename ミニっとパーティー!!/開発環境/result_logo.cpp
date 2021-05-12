//-----------------------------------------------------------------
//
// リザルト背景 (result_bg.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "result_logo.h"
#include "player.h"
#include "chara_select_frame.h"

//-----------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------
#define MAX_PATTERN			(4)							// 背景の種類
#define MAX_TEXTURE			(6)							// 背景の種類

#define RESULT_BG_X			(SCREEN_WIDTH / 2)			// タイトル背景の位置(X座標)
#define RESULT_BG_Y			(SCREEN_HEIGHT / 2)			// タイトル背景の位置(Y座標)
#define RESULT_BG_WIDTH		(300.0f)				// タイトル背景の幅
#define RESULT_BG_HEIGHT	(130.0f)				// タイトル背景の高さ

#define RESULT_PLAYER_SIZE		(150.0f)				// タイトル背景の幅

//-----------------------------------------------------------------
// 構造体の定義
//-----------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	float fWidth;		// 幅
	float fHeight;		// 高さ
	int nTexType;		// 貼るテクスチャの種類
}ResultLogo;

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultLogo = NULL;				// 背景の頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureresultLogo[MAX_TEXTURE] = {};			// 背景のテクスチャのポインタ
ResultLogo g_ResultLogo[MAX_PATTERN];
int g_nNumLogo;

//-----------------------------------------------------------------
// リザルトロゴの初期化処理
//-----------------------------------------------------------------
HRESULT InitResultLogo(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し、初期化
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_1.png", &g_pTextureresultLogo[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_2.png", &g_pTextureresultLogo[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_3.png", &g_pTextureresultLogo[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_4.png", &g_pTextureresultLogo[3]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/win_logo.png", &g_pTextureresultLogo[4]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/draw_logo.png", &g_pTextureresultLogo[5]);

	// プレイヤー情報の取得
	Player *pPlayer = GetPlayer();
	int nNumFrame = GetFrame();
	g_nNumLogo = 1;

	for (int nCntPlayer = 0; nCntPlayer < nNumFrame; nCntPlayer++, pPlayer++)
	{
		if (pPlayer->bFall == false)
		{
			g_nNumLogo++;
			g_ResultLogo[g_nNumLogo - 2].nTexType = nCntPlayer;
		}
	}
	if (g_nNumLogo == 1 || g_nNumLogo == (nNumFrame + 1))
	{
		g_ResultLogo[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 500.0f, 0.0f);
		g_ResultLogo[0].fWidth = RESULT_BG_WIDTH;
		g_ResultLogo[0].fHeight = RESULT_BG_HEIGHT;
		g_ResultLogo[0].nTexType = 5;
		g_nNumLogo = 1;
	}
	else
	{
		for (int nCntLogo = 0; nCntLogo < g_nNumLogo - 1; nCntLogo++)
		{
			g_ResultLogo[nCntLogo].pos = D3DXVECTOR3(SCREEN_WIDTH / 2.0f + (nCntLogo * 150.0f) - (100.0f * g_nNumLogo), 500.0f, 0.0f);
			g_ResultLogo[nCntLogo].fWidth = RESULT_PLAYER_SIZE;
			g_ResultLogo[nCntLogo].fHeight = RESULT_PLAYER_SIZE;
		}
		g_ResultLogo[g_nNumLogo - 1].pos = D3DXVECTOR3(g_ResultLogo[g_nNumLogo - 2].pos.x + 300.0f, 500.0f, 0.0f);
		g_ResultLogo[g_nNumLogo - 1].fWidth = RESULT_BG_WIDTH;
		g_ResultLogo[g_nNumLogo - 1].fHeight = RESULT_BG_HEIGHT;
		g_ResultLogo[g_nNumLogo - 1].nTexType = 4;
	}

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX * g_nNumLogo,	// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultLogo,
		NULL)))
	{
		return E_FAIL;
	}

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResultLogo->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntResultLogo = 0; nCntResultLogo < g_nNumLogo; nCntResultLogo++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_ResultLogo[nCntResultLogo].pos.x - (g_ResultLogo[nCntResultLogo].fWidth / 2), g_ResultLogo[nCntResultLogo].pos.y + (g_ResultLogo[nCntResultLogo].fHeight / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_ResultLogo[nCntResultLogo].pos.x - (g_ResultLogo[nCntResultLogo].fWidth / 2), g_ResultLogo[nCntResultLogo].pos.y - (g_ResultLogo[nCntResultLogo].fHeight / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_ResultLogo[nCntResultLogo].pos.x + (g_ResultLogo[nCntResultLogo].fWidth / 2), g_ResultLogo[nCntResultLogo].pos.y + (g_ResultLogo[nCntResultLogo].fHeight / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_ResultLogo[nCntResultLogo].pos.x + (g_ResultLogo[nCntResultLogo].fWidth / 2), g_ResultLogo[nCntResultLogo].pos.y - (g_ResultLogo[nCntResultLogo].fHeight / 2), 0.0f);


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
	g_pVtxBuffResultLogo->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// リザルトロゴの終了処理
//-----------------------------------------------------------------
void UninitResultLogo(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffResultLogo != NULL)
	{
		g_pVtxBuffResultLogo->Release();
		g_pVtxBuffResultLogo = NULL;
	}

	// テクスチャの開放
	for (int nCntBg = 0; nCntBg < MAX_TEXTURE; nCntBg++)
	{
		if (g_pTextureresultLogo[nCntBg] != NULL)
		{
			g_pTextureresultLogo[nCntBg]->Release();
			g_pTextureresultLogo[nCntBg] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// リザルトロゴの更新処理
//-----------------------------------------------------------------
void UpdateResultLogo(void)
{

}

//-----------------------------------------------------------------
// リザルトロゴの描画処理
//-----------------------------------------------------------------
void DrawResultLogo(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResultLogo, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for (int nCntBg = 0; nCntBg < g_nNumLogo; nCntBg++)
	{
		pDevice->SetTexture(0, g_pTextureresultLogo[g_ResultLogo[nCntBg].nTexType]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBg * 4, 2);
	}
}