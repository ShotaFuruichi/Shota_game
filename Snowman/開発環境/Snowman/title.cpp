////////////////////////////////////////////////////////////////////////////////
//
//Contents	: タイトルの処理 [title.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/10/30
//
////////////////////////////////////////////////////////////////////////////////
#include "title.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "sound.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define BUTTON_ALPHA (1.0f)		//ボタンのα値初期
#define BUTTON_COLOR (0.5f)		//ボタン色初期値

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				//頂点情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleGame = NULL;			//ゲーム開始ボタン頂点情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleTuto = NULL;			//チュートリアルボタン頂点情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleQuit = NULL;			//終了ボタン頂点情報

LPDIRECT3DTEXTURE9 g_pTextureTitle = NULL;					//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureTitleGame = NULL;				//ゲーム開始ボタンテクスチャ
LPDIRECT3DTEXTURE9 g_pTextureTitleTuto = NULL;				//チュートリアルボタンテクスチャ
LPDIRECT3DTEXTURE9 g_pTextureTitleQuit = NULL;				//終了ボタンテクスチャ

D3DXCOLOR g_colGame;										//ゲーム開始ボタン色
D3DXCOLOR g_colTuto;										//チュートリアルボタン色
D3DXCOLOR g_colQuit;										//終了ボタン色

int g_Menu = TITLE_MENU_GAME;								//選択中のボタン

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

	//変数の初期化
	g_pVtxBuffTitle = NULL;
	g_pTextureTitle = NULL;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\title.jpg", &g_pTextureTitle);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\start.png", &g_pTextureTitleGame);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial.png", &g_pTextureTitleTuto);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\quit.png", &g_pTextureTitleQuit);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitle, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffTitle->Unlock();

	//ゲーム開始ボタン
	//代入
	g_colGame = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitleGame, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitleGame->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 1.75f, SCREEN_HEIGHT - 400, 0);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 1.75f, SCREEN_HEIGHT - 500, 0);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 1.25f, SCREEN_HEIGHT - 400, 0);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 1.25f, SCREEN_HEIGHT - 500, 0);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	ColorGame();

	//テクスチャ頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffTitleGame->Unlock();

	//チューとリアルボタン
	//代入
	g_colTuto = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitleTuto, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitleTuto->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 1.75f, SCREEN_HEIGHT - 250, 0);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 1.75f, SCREEN_HEIGHT - 350, 0);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 1.25f, SCREEN_HEIGHT - 250, 0);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 1.25f, SCREEN_HEIGHT - 350, 0);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	ColorTuto();

	//テクスチャ頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffTitleTuto->Unlock();

	//ゲーム終了ボタン
	//代入
	g_colQuit = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitleQuit, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitleQuit->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 1.75f, SCREEN_HEIGHT - 100, 0);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 1.75f, SCREEN_HEIGHT - 200, 0);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 1.25f, SCREEN_HEIGHT - 100, 0);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 1.25f, SCREEN_HEIGHT - 200, 0);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	ColorQuit();

	//テクスチャ頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffTitleQuit->Unlock();

	//bgmの再生
	StopSound();
	PlaySound(SOUND_LABEL_BGM000);

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitTitle(void)
{
	//タイトル
	//頂点バッファの開放
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();	//開放
		g_pVtxBuffTitle = NULL;		//初期化
	}

	//テクスチャの開放
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();	//開放
		g_pTextureTitle = NULL;		//初期化
	}

	//ゲーム開始ボタン
	//頂点バッファの開放
	if (g_pVtxBuffTitleGame != NULL)
	{
		g_pVtxBuffTitleGame->Release();	//開放
		g_pVtxBuffTitleGame = NULL;		//初期化
	}

	//テクスチャの開放
	if (g_pTextureTitleGame != NULL)
	{
		g_pTextureTitleGame->Release();	//開放
		g_pTextureTitleGame = NULL;		//初期化
	}

	//チュートリアルボタン
	//頂点バッファの開放
	if (g_pVtxBuffTitleTuto != NULL)
	{
		g_pVtxBuffTitleTuto->Release();	//開放
		g_pVtxBuffTitleTuto = NULL;		//初期化
	}

	//テクスチャの開放
	if (g_pTextureTitleTuto != NULL)
	{
		g_pTextureTitleTuto->Release();	//開放
		g_pTextureTitleTuto = NULL;		//初期化
	}

	//終了ボタン
	//頂点バッファの開放
	if (g_pVtxBuffTitleQuit != NULL)
	{
		g_pVtxBuffTitleQuit->Release();	//開放
		g_pVtxBuffTitleQuit = NULL;		//初期化
	}

	//テクスチャの開放
	if (g_pTextureTitleQuit != NULL)
	{
		g_pTextureTitleQuit->Release();	//開放
		g_pTextureTitleQuit = NULL;		//初期化
	}
}

////////////////////////////////////////////////////////////////////////////////
//更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateTitle(void)
{
	//変数宣言
	FADE fade;
	HWND hWnd;
	fade = GetFade();
	hWnd = GethWnd();

	if (GetKeyboardTrigger(DIK_UP) == true)
	{
		g_Menu += 2;
		PlaySound(SOUND_LABEL_SE_SELECT);
	}
	if (GetKeyboardTrigger(DIK_DOWN) == true)
	{
		g_Menu += 1;
		PlaySound(SOUND_LABEL_SE_SELECT);
	}
	g_Menu %= 3;

	switch (g_Menu)
	{
	case TITLE_MENU_GAME:
		//他を初期化
		g_colQuit = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);
		g_colTuto = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);;
		ColorGame();
		ColorTuto();
		ColorQuit();

		//光る
		g_colGame = D3DXCOLOR(1.0f, 1.0f, 1.0f, BUTTON_ALPHA);
		//if (g_colContinue.r > 1.0f || g_colContinue.r < 0.01f)
		//{
		//	g_fFlashR *= -1;
		//}

		//ゲーム画面にすすむ
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			//画面遷移
			if (fade == FADE_NONE)
			{
				SetFade(FADE_OUT, MODE_GAME);
				PlaySound(SOUND_LABEL_SE_DESICION);
			}
		}
		break;

	case TITLE_MENU_TUTORIAL:

		//他を初期化
		g_colGame = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);;
		g_colQuit = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);;
		ColorGame();
		ColorTuto();
		ColorQuit();

		//光る
		g_colTuto = D3DXCOLOR(1.0f, 1.0f, 1.0f, BUTTON_ALPHA);;

		//チュートリアル画面にすすむ
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			//画面遷移
			if (fade == FADE_NONE)
			{
				SetFade(FADE_OUT, MODE_TUTORIAL);
				PlaySound(SOUND_LABEL_SE_DESICION);
			}
		}
		break;

	case TITLE_MENU_QUIT:
		//他を初期化
		g_colGame = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);;
		g_colTuto = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);;
		ColorGame();
		ColorTuto();
		ColorQuit();

		//光る
		g_colQuit = D3DXCOLOR(1.0f, 1.0f, 1.0f, BUTTON_ALPHA);;

		//タイトルに戻る
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if (GetKeyboardTrigger(DIK_RETURN) == true)
			{
				DestroyWindow(hWnd);
				PlaySound(SOUND_LABEL_SE_DESICION);
			}
		}
		break;
	}
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

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitle);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//コンティニューボタン
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitleGame, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitleGame);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//チュートリアルボタン
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitleTuto, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitleTuto);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//終了ボタン
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitleQuit, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitleQuit);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

////////////////////////////////////////////////////////////////////////////////
//ゲーム開始ボタン頂点カラーの設定
////////////////////////////////////////////////////////////////////////////////
void ColorGame(void)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitleGame->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = g_colGame;
	pVtx[1].col = g_colGame;
	pVtx[2].col = g_colGame;
	pVtx[3].col = g_colGame;

	//頂点バッファをアンロックする
	g_pVtxBuffTitleGame->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//チュートリアルボタン頂点カラーの設定
////////////////////////////////////////////////////////////////////////////////
void ColorTuto(void)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitleTuto->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = g_colTuto;
	pVtx[1].col = g_colTuto;
	pVtx[2].col = g_colTuto;
	pVtx[3].col = g_colTuto;

	//頂点バッファをアンロックする
	g_pVtxBuffTitleTuto->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//終了ボタン頂点カラーの設定
////////////////////////////////////////////////////////////////////////////////
void ColorQuit(void)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitleQuit->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = g_colQuit;
	pVtx[1].col = g_colQuit;
	pVtx[2].col = g_colQuit;
	pVtx[3].col = g_colQuit;

	//頂点バッファをアンロックする
	g_pVtxBuffTitleQuit->Unlock();
}