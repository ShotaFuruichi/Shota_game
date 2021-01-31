////////////////////////////////////////////////////////////////////////////////
//
//Contents	: タイトル画面 [title.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/08/31
//
////////////////////////////////////////////////////////////////////////////////
#include "title.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "xinput_pad.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define LOGO_POSX (780)			//ロゴ中心からの距離X
#define LOGO_POSY (360)			//ロゴ中心からの距離Y
#define LOGO_STOP (400)			//ロゴ止めるY座標
#define LOGO_SPEED (5)			//ロゴの移動速度

#define SIGN_POSX (390)			//サイン中心からの距離X
#define SIGN_POSY (90)			//サイン中心からの距離Y
#define SIGN_FLASH (25)			//サイン点滅スピード

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleBg = NULL;	//背景の頂点情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleLogo = NULL;	//ロゴの頂点情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleSign = NULL;	//サインの頂点情報
LPDIRECT3DTEXTURE9 g_pTextureTitleSign = NULL;		//サインのテクスチャ情報
LPDIRECT3DTEXTURE9 g_pTextureTitleBg = NULL;		//背景のテクスチャ情報
LPDIRECT3DTEXTURE9 g_pTextureTitleLogo = NULL;		//ロゴのテクスチャ情報
D3DXVECTOR3 g_posLogo;								//ロゴの位置情報
D3DXVECTOR3 g_posSign;								//サインの位置情報
int g_SignCounter;									//サインカウンター
bool g_bDisp;										//サイン点滅
int g_FadeCounter;									//フェードまでのカウント
int g_FlashSpeed;									//点滅速度
bool g_bFlash;										//早く点滅しているかどうか

////////////////////////////////////////////////////////////////////////////////
//初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT InitTitle(void)
{
	//変数宣言
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bg00000.jpg", &g_pTextureTitleBg);		//背景
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\title100.png", &g_pTextureTitleLogo);	//ロゴ
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\sign000.png", &g_pTextureTitleSign);		//サイン

	//初期化
	g_SignCounter = 1;
	g_bDisp = false;
	g_FadeCounter = 0;
	g_FlashSpeed = SIGN_FLASH;
	g_bFlash = false;

	//背景
	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitleBg, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitleBg->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffTitleBg->Unlock();

	//ロゴ
	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitleLogo, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

	//ロゴの中心座標の設定
	g_posLogo = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);

	//頂点座標の設定
	SetVertexLogo();

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
	g_pVtxBuffTitleLogo->Unlock();

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitleSign, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitleSign->Lock(0, 0, (void**)&pVtx, 0);

	//ロゴの中心座標の設定
	g_posSign = D3DXVECTOR3(SCREEN_WIDTH / 2, 890.0f, 0.0f);

	//頂点座標の設定
	SetVertexSign();

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
	g_pVtxBuffTitleSign->Unlock();

	PlaySound(SOUND_LABEL_BGM001);

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitTitle(void)
{
	StopSound();
	
	//背景頂点バッファの開放
	if (g_pVtxBuffTitleBg != NULL)
	{
		g_pVtxBuffTitleBg->Release();	//開放
		g_pVtxBuffTitleBg = NULL;		//初期化
	}
	//背景テクスチャの開放
	if (g_pTextureTitleBg != NULL)
	{
		g_pTextureTitleBg->Release();	//開放
		g_pTextureTitleBg = NULL;		//初期化
	}

	//ロゴ頂点バッファの開放
	if (g_pVtxBuffTitleLogo != NULL)
	{
		g_pVtxBuffTitleLogo->Release();	//開放
		g_pVtxBuffTitleLogo = NULL;		//初期化
	}
	//ロゴテクスチャの開放
	if (g_pTextureTitleLogo != NULL)
	{
		g_pTextureTitleLogo->Release();	//開放
		g_pTextureTitleLogo = NULL;		//初期化
	}

	//サイン頂点バッファの開放
	if (g_pVtxBuffTitleSign != NULL)
	{
		g_pVtxBuffTitleSign->Release();	//開放
		g_pVtxBuffTitleSign = NULL;		//初期化
	}
	//サインテクスチャの開放
	if (g_pTextureTitleSign != NULL)
	{
		g_pTextureTitleSign->Release();	//開放
		g_pTextureTitleSign = NULL;		//初期化
	}
}

////////////////////////////////////////////////////////////////////////////////
//更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateTitle(void)
{
	//変数宣言
	FADE fade;
	XinputGamepad *pXinput = GetXinputGamepad();
	fade = GetFade();

	//ロゴ移動
	if (g_posLogo.y < LOGO_STOP)
	{
		g_posLogo.y += LOGO_SPEED;
	}
	else
	{
		//点滅
		g_SignCounter++;
		if (g_SignCounter % g_FlashSpeed == 0)
		{
			g_bDisp = g_bDisp ? false : true;
		}
	}

	//早く点滅し始めからフェードカウンター
	if (g_bFlash == true)
	{
		g_FadeCounter++;
	}

	//エンターキーを押したとき
	if (GetKeyboardTrigger(DIK_RETURN) == true || pXinput->bPressStart == true || pXinput->bPressA)
	{
		if (g_posLogo.y == LOGO_STOP)
		{
			if (g_bFlash == false)
			{
				g_FlashSpeed /= 6;
			}
			g_bFlash = true;
		}
		else
		{
			g_posLogo.y = LOGO_STOP;
		}	
	}

	//早く点滅してから1秒後フェードアウト
	if (g_FadeCounter > 60)
	{
		if (fade == FADE_NONE)
		{
			SetFade(FADE_OUT, MODE_TUTORIAL);
		}
	}

	//ロゴの頂点座標の設定
	SetVertexLogo();

	//サインの頂点座標の設定
	SetVertexSign();
}

////////////////////////////////////////////////////////////////////////////////
//描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawTitle(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();
	
	//背景
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitleBg, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitleBg);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//ロゴ
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitleLogo, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitleLogo);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//サイン
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitleSign, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitleSign);

	if (g_bDisp == true)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

////////////////////////////////////////////////////////////////////////////////
//ロゴの頂点座標の設定
////////////////////////////////////////////////////////////////////////////////
void SetVertexLogo(void)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_posLogo.x - LOGO_POSX, g_posLogo.y + LOGO_POSY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posLogo.x - LOGO_POSX, g_posLogo.y - LOGO_POSY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posLogo.x + LOGO_POSX, g_posLogo.y + LOGO_POSY, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posLogo.x + LOGO_POSX, g_posLogo.y - LOGO_POSY, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffTitleLogo->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//サインの頂点座標の設定
////////////////////////////////////////////////////////////////////////////////
void SetVertexSign(void)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitleSign->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_posSign.x - SIGN_POSX, g_posSign.y + SIGN_POSY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posSign.x - SIGN_POSX, g_posSign.y - SIGN_POSY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posSign.x + SIGN_POSX, g_posSign.y + SIGN_POSY, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posSign.x + SIGN_POSX, g_posSign.y - SIGN_POSY, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffTitleSign->Unlock();
}