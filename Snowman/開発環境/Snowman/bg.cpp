////////////////////////////////////////////////////////////////////////////////
//
//Contents	: 背景の処理 [bg.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/10/13
//
////////////////////////////////////////////////////////////////////////////////
#include "bg.h"
#include "player.h"
#include "input.h"
#include "block.h"
#include "game.h"
#include "fade.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define MAX_BUFF (2) //頂点情報の個数

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg[MAX_BUFF] = {};		//頂点情報
LPDIRECT3DTEXTURE9 g_pTextureBg[STAGE_MAX] = {};	//テクスチャ情報

BGTEX g_Bg;
D3DXCOLOR g_col;

float g_f;
float g_f2;

////////////////////////////////////////////////////////////////////////////////
//背景の初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT InitBg(void)
{
	//変数宣言
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCntTexture = 0; nCntTexture < STAGE_MAX; nCntTexture++)
	{
		g_pTextureBg[nCntTexture] = NULL;
	}
	g_Bg = BG_WINTER;
	g_f = 0.0f;
	g_f2 = 1.0f;
	g_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\winter.jpg", &g_pTextureBg[STAGE_0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\spring.jpg", &g_pTextureBg[STAGE_1]);

	for (int nCntBG = 0; nCntBG < MAX_BUFF; nCntBG++)
	{
		//変数の初期化
		g_pVtxBuffBg[nCntBG] = NULL;

		//頂点バッファの生成
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBg[nCntBG], NULL)))
		{
			return E_FAIL;
		}

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffBg[nCntBG]->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0);
		pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0);

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

		//頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffBg[nCntBG]->Unlock();

	}

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//背景の終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitBg(void)
{
	//頂点バッファの開放
	//テクスチャの開放
	for (int nCntBuff = 0; nCntBuff < MAX_BUFF; nCntBuff++)
	{
		if (g_pVtxBuffBg[nCntBuff] != NULL)
		{
			g_pVtxBuffBg[nCntBuff]->Release();	//開放
			g_pVtxBuffBg[nCntBuff] = NULL;		//初期化
		}
	}

	//テクスチャの開放
	for (int nCntTexture = 0; nCntTexture < STAGE_MAX; nCntTexture++)
	{
		if (g_pTextureBg[nCntTexture] != NULL)
		{
			g_pTextureBg[nCntTexture]->Release();	//開放
			g_pTextureBg[nCntTexture] = NULL;		//初期化
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//背景の更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateBg(void)
{
	PLAYER *pPlayer;
	VERTEX_2D *pVtx;
	pPlayer = GetPlayer();

#if 0
		if (GetKeyboardPress(DIK_D) == true)
		{
			if (GetKeyboardPress(DIK_A) == true)
			{
			}
			else
			{
				g_f -= 0.0005f;
				g_f2 -= 0.0005f;
			}
		}
		else if (GetKeyboardPress(DIK_A) == true)
		{
			if (GetKeyboardPress(DIK_D) == true)
			{
			}
			else
			{
				g_f += 0.0005f;
				g_f2 += 0.0005f;
			}
		}
#endif
		/*if (g_Bg == BG_WINTER)
		{
			if (g_f2 < 1.0f)
			{
				g_f += 0.005f;
				g_f2 += 0.005f;
			}
		}*/

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBg[1]->Lock(0, 0, (void**)&pVtx, 0);
	
	if (g_col.a > 0)
	{
		g_col.a -= 0.01f;
	}

	//頂点カラーの設定
	pVtx[0].col = g_col;
	pVtx[1].col = g_col;
	pVtx[2].col = g_col;
	pVtx[3].col = g_col;

	//頂点バッファをアンロックする
	g_pVtxBuffBg[1]->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//背景の描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawBg(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	FADE fade;
	STAGE stage;
	stage = GetStage();
	fade = GetFade();

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBg[0], 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBg[STAGE_1]);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBg[1], 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_Bg == BG_WINTER)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBg[STAGE_0]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
	
}

////////////////////////////////////////////////////////////////////////////////
//bgの情報取得
////////////////////////////////////////////////////////////////////////////////
void SetBg(BGTEX bg)
{
	g_Bg = bg;
}