////////////////////////////////////////////////////////////////////////////////
//
//Contents	: フェードの処理 [fade.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/08/31
//
////////////////////////////////////////////////////////////////////////////////
#include "fade.h"
#include "game.h"
#include "title.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define FADE_SPEED (0.03f);

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;	//頂点情報
FADE g_fade;									//フェード情報
MODE g_modeNext;								//フェードイン後のモード
D3DXCOLOR g_colorFade;							//フェードの色

////////////////////////////////////////////////////////////////////////////////
//フェードの初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT InitFade(MODE modeNext)
{
	//変数宣言
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//変数の初期化
	g_pVtxBuffFade = NULL;
	g_fade = FADE_IN;
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffFade, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

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

	//色の設定
	ColorFade();

	//頂点バッファをアンロックする
	g_pVtxBuffFade->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//フェードの終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitFade(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();	//開放
		g_pVtxBuffFade = NULL;		//初期化
	}
}

////////////////////////////////////////////////////////////////////////////////
//フェードの更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateFade(void)
{
	//フェードイン・フェードアウト
	switch (g_fade)
	{
	case FADE_IN:
		if (g_colorFade.a >= 0.0f)
		{
			g_colorFade.a -= FADE_SPEED;
		}
		else
		{
			g_fade = FADE_NONE;
			g_colorFade.a = 0.0f;
		}
		break;
	case FADE_OUT:
		if (g_colorFade.a <= 1.0f)
		{
			g_colorFade.a += FADE_SPEED;
		}
		else
		{
			g_fade = FADE_IN;
			SetMode(g_modeNext);
		}
		break;
	default:
		break;
	}

	//色の設定
	ColorFade();
}

////////////////////////////////////////////////////////////////////////////////
//フェードの描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawFade(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

////////////////////////////////////////////////////////////////////////////////
//フェードのセット処理
////////////////////////////////////////////////////////////////////////////////
void SetFade(FADE fade, MODE modeNext)
{
	if (g_fade == FADE_NONE)
	{
		g_modeNext = modeNext;
		g_fade = fade;
	}
}

////////////////////////////////////////////////////////////////////////////////
//フェード強制終了
////////////////////////////////////////////////////////////////////////////////
void EndFade(void)
{
	switch (g_fade)
	{
	case FADE_IN:
		g_colorFade.a = 0.0f;
		break;
	case FADE_OUT:
		g_colorFade.a = 1.0f;
		break;
	default:
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////
//フェードの取得
////////////////////////////////////////////////////////////////////////////////
FADE GetFade(void)
{
	return g_fade;
}

////////////////////////////////////////////////////////////////////////////////
//フェードの色設定
////////////////////////////////////////////////////////////////////////////////
void ColorFade(void)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;

	//頂点バッファをアンロックする
	g_pVtxBuffFade->Unlock();
}