////////////////////////////////////////////////////////////////////////////////
//
//Contents	: リザルト画面の処理 [result.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/08/31
//
////////////////////////////////////////////////////////////////////////////////
#include "result.h"
#include "input.h"
#include "fade.h"
#include "player.h"
#include "score.h"
#include "highscore.h"
#include "sound.h"
#include "xinput_pad.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define HIGHSCORE_POSX (585.0f)	//ハイスコアの中心からの距離X
#define HIGHSCORE_POSY (135.0f)	//ハイスコアの中心からの距離Y
#define EXPAND_RESULTX (8.6f)	//リザルトの中心からの広がりの速さX
#define EXPAND_RESULTY (2.0f)	//リザルトの中心からの広がりの速さY

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultBg = NULL;			//リザルト背景頂点情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultHighscore = NULL;	//リザルトクリア頂点情報
LPDIRECT3DTEXTURE9 g_pTextureResultBg = NULL;				//リザルト背景テクスチャ情報
LPDIRECT3DTEXTURE9 g_pTextureResultHighscore = NULL;		//リザルトクリアテクスチャ情報
D3DXVECTOR3 g_posHighscore;									//ハイスコアの位置
float g_fLengthX;											//中心からの長さx
float g_fLengthY;											//中心からの長さy

////////////////////////////////////////////////////////////////////////////////
//初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT InitResult(void)
{
	//変数宣言
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bg.jpg", &g_pTextureResultBg);				//リザルト背景テクスチャ
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\highscore.png", &g_pTextureResultHighscore);		//リザルトハイスコアテクスチャ

	//背景
	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffResultBg, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResultBg->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);

	//頂点バッファをアンロックする
	g_pVtxBuffResultBg->Unlock();

	//ハイスコア
	g_posHighscore = D3DXVECTOR3(SCREEN_WIDTH / 2, 400.0f, 0.0f);
	g_fLengthX = 0.0f;
	g_fLengthY = 0.0f;

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffResultHighscore, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResultHighscore->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	SetVertexHighscore();

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
	pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);

	//頂点バッファをアンロックする
	g_pVtxBuffResultHighscore->Unlock();

	PlaySound(SOUND_LABEL_BGM000);

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitResult(void)
{
	UninitScore();

	StopSound();

	//背景
	//頂点バッファの開放
	if (g_pVtxBuffResultBg != NULL)
	{
		g_pVtxBuffResultBg->Release();	//開放
		g_pVtxBuffResultBg = NULL;		//初期化
	}
	//テクスチャの開放
	if (g_pTextureResultBg != NULL)
	{
		g_pTextureResultBg->Release();	//開放
		g_pTextureResultBg = NULL;		//初期化
	}
	
	//ハイスコア
	//頂点バッファの開放
	if (g_pVtxBuffResultHighscore != NULL)
	{
		g_pVtxBuffResultHighscore->Release();	//開放
		g_pVtxBuffResultHighscore = NULL;		//初期化
	}
	//テクスチャの開放
	if (g_pTextureResultHighscore != NULL)
	{
		g_pTextureResultHighscore->Release();	//開放
		g_pTextureResultHighscore = NULL;		//初期化
	}
}

////////////////////////////////////////////////////////////////////////////////
//更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateResult(void)
{
	//変数宣言
	FADE fade = GetFade();
	PLAYER *pPlayer = GetPlayer();
	XinputGamepad *pXinput = GetXinputGamepad();

	if (g_fLengthX < HIGHSCORE_POSX)
	{
		g_fLengthX += EXPAND_RESULTX;
	}
	if (g_fLengthY < HIGHSCORE_POSY)
	{
		g_fLengthY += EXPAND_RESULTY;
	}

	UpdateHighScore();
	AddHighScore();

	//頂点座標の設定
	SetVertexHighscore();

	//画面遷移
	if (fade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true || pXinput->bPressStart == true || pXinput->bPressA)
		{
			SetFade(FADE_OUT, MODE_TITLE);
		}
	}
	UpdateScore();
	AddScore(0);
}

////////////////////////////////////////////////////////////////////////////////
//描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawResult(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//背景
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResultBg, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResultBg);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//ハイスコア
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResultHighscore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResultHighscore);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	DrawScore();

	DrawHighScore();
}

////////////////////////////////////////////////////////////////////////////////
//ハイスコアの頂点座標の設定
////////////////////////////////////////////////////////////////////////////////
void SetVertexHighscore(void)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResultHighscore->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_posHighscore.x - g_fLengthX, g_posHighscore.y + g_fLengthY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posHighscore.x - g_fLengthX, g_posHighscore.y - g_fLengthY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posHighscore.x + g_fLengthX, g_posHighscore.y + g_fLengthY, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posHighscore.x + g_fLengthX, g_posHighscore.y - g_fLengthY, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffResultHighscore->Unlock();
}