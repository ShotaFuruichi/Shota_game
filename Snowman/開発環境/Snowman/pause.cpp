////////////////////////////////////////////////////////////////////////////////
//
//Contents	: ポーズ画面の処理 [pause.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/11/06
//
////////////////////////////////////////////////////////////////////////////////
#include "pause.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "sound.h"
#include "xinput_pad.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define BG_ALPHA (150)			//背景のα値
#define BUTTON_ALPHA (1.0f)		//ボタンのα値初期
#define BUTTON_COLOR (0.5f)		//ボタン色初期値

#define MENU_POSX (250)			//メニュー画面中心からの距離X
#define MENU_POSY (350)			//メニュー画面中心からの距離Y
#define BUTTON_X (200)			//メニュー画面中心からのボタン距離X

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseBg = NULL;			//背景頂点情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseMenu = NULL;			//メニュー頂点情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;				//ポーズ頂点情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseContinue = NULL;		//コンティニューボタン頂点情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseRetry = NULL;		//リトライボタン頂点情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseQuit = NULL;			//終了ボタン頂点情報
LPDIRECT3DTEXTURE9 g_pTexturePause = NULL;					//ポーズテクスチャ
LPDIRECT3DTEXTURE9 g_pTexturePauseMenu = NULL;				//メニューテクスチャ
LPDIRECT3DTEXTURE9 g_pTexturePauseContinue = NULL;			//コンティニューボタンテクスチャ
LPDIRECT3DTEXTURE9 g_pTexturePauseRetry = NULL;				//リトライボタンテクスチャ
LPDIRECT3DTEXTURE9 g_pTexturePauseQuit = NULL;				//終了ボタンテクスチャ

D3DXVECTOR3 g_posMenu;										//メニュー中心座標
D3DXCOLOR g_colContinue;									//コンティニューボタン色
D3DXCOLOR g_colRetry;										//リトライボタン色
D3DXCOLOR g_colQuitP;										//終了ボタン色

int g_MenuP = PAUSE_MENU_CONTINUE;							//選択中のボタン

////////////////////////////////////////////////////////////////////////////////
//ポーズ画面の初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT InitPause(void)
{
	//変数宣言
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\menu.jpg", &g_pTexturePauseMenu);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\pause.png", &g_pTexturePause);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\continue.png", &g_pTexturePauseContinue);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\retry.png", &g_pTexturePauseRetry);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\quit.png", &g_pTexturePauseQuit);

	//背景
	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPauseBg, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseBg->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, BG_ALPHA);
	pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, BG_ALPHA);
	pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, BG_ALPHA);
	pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, BG_ALPHA);

	//頂点バッファをアンロックする
	g_pVtxBuffPauseBg->Unlock();

	//メニュー画面
	//代入
	g_posMenu = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPauseMenu, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_posMenu.x - MENU_POSX, g_posMenu.y + MENU_POSY, 0);
	pVtx[1].pos = D3DXVECTOR3(g_posMenu.x - MENU_POSX, g_posMenu.y - MENU_POSY, 0);
	pVtx[2].pos = D3DXVECTOR3(g_posMenu.x + MENU_POSX, g_posMenu.y + MENU_POSY, 0);
	pVtx[3].pos = D3DXVECTOR3(g_posMenu.x + MENU_POSX, g_posMenu.y - MENU_POSY, 0);

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

	//テクスチャ頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPauseBg->Unlock();

	//ポーズ
	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPause, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_posMenu.x - BUTTON_X, g_posMenu.y - 200, 0);
	pVtx[1].pos = D3DXVECTOR3(g_posMenu.x - BUTTON_X, g_posMenu.y - 300, 0);
	pVtx[2].pos = D3DXVECTOR3(g_posMenu.x + BUTTON_X, g_posMenu.y - 200, 0);
	pVtx[3].pos = D3DXVECTOR3(g_posMenu.x + BUTTON_X, g_posMenu.y - 300, 0);

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

	//テクスチャ頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();

	//コンティニューボタン
	//代入
	g_colContinue = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPauseContinue, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseContinue->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_posMenu.x - BUTTON_X, g_posMenu.y - 50, 0);
	pVtx[1].pos = D3DXVECTOR3(g_posMenu.x - BUTTON_X, g_posMenu.y - 150, 0);
	pVtx[2].pos = D3DXVECTOR3(g_posMenu.x + BUTTON_X, g_posMenu.y - 50, 0);
	pVtx[3].pos = D3DXVECTOR3(g_posMenu.x + BUTTON_X, g_posMenu.y - 150, 0);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//テクスチャ頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPauseContinue->Unlock();

	//リトライボタン
	//代入
	g_colRetry = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPauseRetry, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseRetry->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_posMenu.x - BUTTON_X, g_posMenu.y + 125, 0);
	pVtx[1].pos = D3DXVECTOR3(g_posMenu.x - BUTTON_X, g_posMenu.y + 25, 0);
	pVtx[2].pos = D3DXVECTOR3(g_posMenu.x + BUTTON_X, g_posMenu.y + 125, 0);
	pVtx[3].pos = D3DXVECTOR3(g_posMenu.x + BUTTON_X, g_posMenu.y + 25, 0);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//テクスチャ頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPauseRetry->Unlock();

	//終了ボタン
	//代入
	g_colQuitP = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPauseQuit, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseQuit->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_posMenu.x - BUTTON_X, g_posMenu.y + 300, 0);
	pVtx[1].pos = D3DXVECTOR3(g_posMenu.x - BUTTON_X, g_posMenu.y + 200, 0);
	pVtx[2].pos = D3DXVECTOR3(g_posMenu.x + BUTTON_X, g_posMenu.y + 300, 0);
	pVtx[3].pos = D3DXVECTOR3(g_posMenu.x + BUTTON_X, g_posMenu.y + 200, 0);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	SetColor();

	//テクスチャ頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPauseQuit->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//ポーズ画面の終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitPause(void)
{
	//背景頂点バッファの開放
	if (g_pVtxBuffPauseBg != NULL)
	{
		g_pVtxBuffPauseBg->Release();	//開放
		g_pVtxBuffPauseBg = NULL;		//初期化
	}

	//メニュー画面頂点バッファの開放
	if (g_pVtxBuffPauseMenu != NULL)
	{
		g_pVtxBuffPauseMenu->Release();	//開放
		g_pVtxBuffPauseMenu = NULL;		//初期化
	}

	//ポーズ頂点バッファの開放
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();	//開放
		g_pVtxBuffPause = NULL;		//初期化
	}

	//コンティニューボタン頂点バッファの開放
	if (g_pVtxBuffPauseContinue != NULL)
	{
		g_pVtxBuffPauseContinue->Release();	//開放
		g_pVtxBuffPauseContinue = NULL;		//初期化
	}

	//リトライボタン頂点バッファの開放
	if (g_pVtxBuffPauseRetry != NULL)
	{
		g_pVtxBuffPauseRetry->Release();	//開放
		g_pVtxBuffPauseRetry = NULL;		//初期化
	}

	//終了ボタン頂点バッファの開放
	if (g_pVtxBuffPauseQuit != NULL)
	{
		g_pVtxBuffPauseQuit->Release();	//開放
		g_pVtxBuffPauseQuit = NULL;		//初期化
	}
}

////////////////////////////////////////////////////////////////////////////////
//ポーズ画面の更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdatePause(void)
{
	//変数宣言
	FADE fade = GetFade();
	XinputGamepad *pXinput = GetXinputGamepad();

	if (GetKeyboardTrigger(DIK_UP) == true || pXinput->bPressUP == true)
	{
		g_MenuP += 2;
		PlaySound(SOUND_LABEL_SE_SELECT);
	}
	if (GetKeyboardTrigger(DIK_DOWN) == true || pXinput->bPressDOWN == true)
	{
		g_MenuP += 1;
		PlaySound(SOUND_LABEL_SE_SELECT);
	}
	g_MenuP %= 3;

	switch (g_MenuP)
	{
	case PAUSE_MENU_CONTINUE:
		//他を初期化
		g_colQuitP = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, 1.0f);
		g_colRetry = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, 1.0f);
		SetColor();

		g_colContinue = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//ゲームに戻る
		if (GetKeyboardTrigger(DIK_RETURN) == true || pXinput->bPressA == true)
		{
			SetPause(false);
			PlaySound(SOUND_LABEL_SE_DESICION);
		}
		break;

	case PAUSE_MENU_RETRY:

		//他を初期化
		g_colContinue = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, 1.0f);
		g_colQuitP = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, 1.0f);
		SetColor();

		//光る
		g_colRetry = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//ゲーム画面からリトライ
		if (GetKeyboardTrigger(DIK_RETURN) == true || pXinput->bPressA == true)
		{
			//画面遷移
			if (fade == FADE_NONE)
			{
				SetFade(FADE_OUT, MODE_GAME);
				PlaySound(SOUND_LABEL_SE_DESICION);
			}
			SetPause(false);
			g_MenuP = PAUSE_MENU_CONTINUE;
		}
		break;

	case PAUSE_MENU_QUIT:
		//他を初期化
		g_colContinue = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, 1.0f);
		g_colRetry = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, 1.0f);
		SetColor();

		//光る
		g_colQuitP = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//タイトルに戻る
		if (GetKeyboardTrigger(DIK_RETURN) == true || pXinput->bPressA == true)
		{
			//画面遷移
			if (fade == FADE_NONE)
			{
				SetFade(FADE_OUT, MODE_TITLE);
				PlaySound(SOUND_LABEL_SE_DESICION);
				SetStageMode(STAGE_MAX);
			}
			SetPause(false);
			g_MenuP = PAUSE_MENU_CONTINUE;
		}
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////
//ポーズ画面の描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawPause(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//背景
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseBg, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//メニュー画面
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseMenu, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePauseMenu);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//ポーズ
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePause);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//コンティニューボタン
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseContinue, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePauseContinue);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//リトライボタン
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseRetry, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePauseRetry);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//終了ボタン
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseQuit, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePauseQuit);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

////////////////////////////////////////////////////////////////////////////////
//色設定
////////////////////////////////////////////////////////////////////////////////
void SetColor(void)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseContinue->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = g_colContinue;
	pVtx[1].col = g_colContinue;
	pVtx[2].col = g_colContinue;
	pVtx[3].col = g_colContinue;

	//頂点バッファをアンロックする
	g_pVtxBuffPauseContinue->Unlock();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseRetry->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = g_colRetry;
	pVtx[1].col = g_colRetry;
	pVtx[2].col = g_colRetry;
	pVtx[3].col = g_colRetry;

	//頂点バッファをアンロックする
	g_pVtxBuffPauseRetry->Unlock();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseQuit->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = g_colQuitP;
	pVtx[1].col = g_colQuitP;
	pVtx[2].col = g_colQuitP;
	pVtx[3].col = g_colQuitP;

	//頂点バッファをアンロックする
	g_pVtxBuffPauseQuit->Unlock();
}