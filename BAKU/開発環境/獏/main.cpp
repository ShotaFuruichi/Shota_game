////////////////////////////////////////////////////////////////////////////////
//
//Contents	: アクションゲーム [main.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/10/13
//
////////////////////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "polygon.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "input.h"
#include "shadow.h"
#include "wall.h"
#include "Billboard.h"
#include "meshfield.h"
#include "bullet.h"
#include <string.h>
#include <stdio.h>
#include "object.h"
#include "player.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "fade.h"
#include "xinput_pad.h"
#include "enemy.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define CLASS_NAME "windowclass"		//クラスの名前
#define WINDOW_NAME "ウィンドウ表示"	//ウィンドウの名前
#define WINDOW_POS_X (0)				//ウィンドウの左上X座標
#define WINDOW_POS_Y (0)				//ウィンドウの左上Y座標
#define ID_TIMER (121)					//タイマーのID
#define TIMER_INTERVAL (1000/60)		//タイマーの発生感覚

////////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawFPS(void);

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3D9 g_pD3D = NULL;					//Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;		//Direct3Dデバイスへのポインタ
LPD3DXFONT g_pFont = NULL;					//フォントへのポインタ
int g_nCountFPS;							//FPSカウンタ
MODE g_mode = MODE_TITLE;					//モードの種類
HWND hWnd;									//ウィンドウハンドル

////////////////////////////////////////////////////////////////////////////////
//メイン関数
////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//変数宣言
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		"CLASS_NAME",	//ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION),
	};
	MSG msg;				//メッセージを格納する
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	DWORD dwExecLastTime;	//処理終了最終時刻
	DWORD dwFPSLastTime;	//FPS計測最終時刻
	DWORD dwCurrentTime;	//現在時刻
	DWORD dwFrameCount;		//フレームカウント

							//現在の時間を取得
	dwExecLastTime =
		dwFPSLastTime =
		dwCurrentTime = timeGetTime();
	dwFrameCount = 0;

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	//ウィンドウの作成
	hWnd = CreateWindowEx
	(
		0,
		"CLASS_NAME",			//ウィンドウクラスの名前
		"3D",		//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,	//ウィンドウを一番前に出す
		CW_USEDEFAULT,			//X座標
		CW_USEDEFAULT,			//Y座標
		rect.right,				//幅
		rect.bottom,			//高さ
		NULL,					//親のハンドル
		NULL,
		hInstance,
		NULL
	);

	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return-1;
	}

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//メッセージループ
	while (1)
	{
		//メッセージを取得したかの判定
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{	//Windowsの処理
			if (msg.message == WM_QUIT)
			{	//取得したメッセージがWM_QUITだった場合
				break;
			}
			else
			{	//取得したメッセージがWM_QUIT以外だった場合

				//メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{	//DirectXの処理

			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{	//0.5秒経過
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) > (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				//更新処理
				Update();

				//描画処理
				Draw();

				dwFrameCount++;
			}
		}
	}

	//終了処理
	Uninit();

	//ウィンドウクラスの登録解除
	UnregisterClass("CLASS_NAME", wcex.hInstance);

	return(int)msg.wParam;
	return 0;
}

////////////////////////////////////////////////////////////////////////////////
//ウィンドウプロシージャ
////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:	//ウィンドウを破棄する
		PostQuitMessage(0);	//WM_QUIT メッセージを返す
		break;

	case WM_CLOSE:	//×を押したとき
		DestroyWindow(hWnd);	//WM_DESTROY メッセージを返す
		break;

	case WM_KEYDOWN:	//キー入力をしたとき
		switch (wParam)
		{
		case VK_ESCAPE:		//エスケープキー
			DestroyWindow(hWnd);	//WM_DESTROY メッセージを返す
			break;

		default:
			break;
		}

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

////////////////////////////////////////////////////////////////////////////////
//初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//変数宣言
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//ディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//Direct3Dデバイスの生成
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
	{	//描画処理：ハードウェア　頂点処理：ハードウェア　で実行できなかった場合
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
		{	//描画処理：ハードウェア　頂点処理：ソフトウェア　で実行できなかった場合
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
			{	//描画処理：ソフトウェア　頂点処理：ソフトウェア　で実行できなかった場合
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				//カリングの設定
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//αブレンド(α値の合成)の設定
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//ソース(描画元：絵、画像)の合成方法の設定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//デスティネーション(描画先：下地)の合成方法の設定

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//縮小時補間
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//拡大時補間
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//U値繰り返し
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	//V値繰り返し

	// テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE); // α値の合成
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//文字表示
	D3DXCreateFont(g_pD3DDevice, 30, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);

	//入力の初期化
	InitKeyboard(hInstance, hWnd);

	//タイトルの初期化
	InitTitle();

	//チュートリアルの初期化
	InitTutorial();

	//フェードの初期化
	InitFade(MODE_GAME);

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//終了処理
////////////////////////////////////////////////////////////////////////////////
void Uninit(void)
{	
	//入力の終了
	UninitKeyboard();

	//フェードの終了
	UninitFade();

	//フォントの開放
	if (g_pFont != NULL)
	{
		g_pFont->Release();			//開放
		g_pFont = NULL;				//初期化
	}

	//Direct3Dデバイスの開放
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();	//開放
		g_pD3DDevice = NULL;		//初期化
	}

	//Direct3Dオブジェクトの開放
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();			//開放
		g_pD3D = NULL;				//初期化
	}
}

////////////////////////////////////////////////////////////////////////////////
//更新処理
////////////////////////////////////////////////////////////////////////////////
void Update(void)
{
	//入力の更新
	UpdateKeyboard();

	//コントローラーの更新
	LoadGamepad();

	//フェードの更新
	UpdateFade();

	//各種更新
	switch (g_mode)
	{
	case MODE_TITLE:
		//タイトルの更新処理
		UpdateTitle();
		break;

	case MODE_TUTORIAL:
		//チュートリアルの更新処理
		UpdateTutorial();
		break;

	case MODE_GAME:
		//ゲーム画面の更新処理
		UpdateGame();
		break;

	case MODE_RESULT:
		//リザルト画面の更新処理
		UpdateResult();
		break;
	case MODE_RANKING:
		//ランキング更新処理
		UpdateRanking();
		break;
	}

}

////////////////////////////////////////////////////////////////////////////////
//描画処理
////////////////////////////////////////////////////////////////////////////////
void Draw(void)
{
	//バックバッファ&Zバッファのクリア(画面のクリア)
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//各種更新
		switch (g_mode)
		{
		case MODE_TITLE:
			//タイトルの描画処理
			DrawTitle();
			break;

		case MODE_TUTORIAL:
			//チュートリアルの描画処理
			DrawTutorial();
			break;

		case MODE_GAME:
			//ゲーム画面の描画処理
			DrawGame();
			break;

		case MODE_RESULT:
			//リザルト画面の描画処理
			DrawResult();
			break;
		case MODE_RANKING:
			//ランキング描画処理
			DrawRanking();
			break;
		}

		//FPSの描画処理
#ifdef _DEBUG
		DrawFPS();
		DrawText();
#endif

		DrawFade();

		//描画の終了
		g_pD3DDevice->EndScene();
	}
	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

////////////////////////////////////////////////////////////////////////////////
//FPS表示
////////////////////////////////////////////////////////////////////////////////
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	//テキストの描画
	g_pFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

////////////////////////////////////////////////////////////////////////////////
//テキスト表示
////////////////////////////////////////////////////////////////////////////////
void DrawText(void)
{
	RECT rect = { 0,50,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[512];
	CAMERA *camera = GetCamera();
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();
	float Gaiseki = *GetGaiseki();
	int nNum = sprintf(&aStr[0], "カメラ視点座標:%f|%f|%f\n", camera->posV.x, camera->posV.y, camera->posV.z);
	nNum += sprintf(&aStr[nNum], "カメラ注視点座標:%f|%f|%f\n", camera->posR.x, camera->posR.y, camera->posR.z);
	nNum += sprintf(&aStr[nNum], "カメラ回転情報:%f|%f|%f\n", camera->rot.x, camera->rot.y, camera->rot.z);
	nNum += sprintf(&aStr[nNum], "プレイヤー座標:%f|%f|%f\n", player->pos.x, player->pos.y, player->pos.z);
	nNum += sprintf(&aStr[nNum], "プレイヤー回転:%f|%f|%f\n", player->rot.x, player->rot.y, player->rot.z);
	nNum += sprintf(&aStr[nNum], "プレイヤーの体力:%d\n", player->nLife);
	nNum += sprintf(&aStr[nNum], "プレイヤーのMP:%d\n", player->nMP);
	nNum += sprintf(&aStr[nNum], "プレイヤークールダウン:%f\n", player->nCooldown / 60.0f);
	nNum += sprintf(&aStr[nNum], "プレイヤー詠唱:%f\n", player->nChantCounter / 60.0f);
	nNum += sprintf(&aStr[nNum], "プレイヤースキルを使えるか:%d\n", player->bUseSkill);
	nNum += sprintf(&aStr[nNum], "gaiseki:%f\n", Gaiseki);
	nNum += sprintf(&aStr[nNum], "敵の体力:%d\n", enemy->nLife);

	//テキストの描画
	g_pFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

////////////////////////////////////////////////////////////////////////////////
//モードの設定
////////////////////////////////////////////////////////////////////////////////
void SetMode(MODE mode)
{
	//現在の画面の終了処理
	switch (g_mode)
	{
	case MODE_TITLE:
		//タイトルの終了処理
		UninitTitle();
		break;

	case MODE_TUTORIAL:
		//チュートリアルの終了処理
		UninitTutorial();
		break;

	case MODE_GAME:
		//ゲーム画面の終了処理
		UninitGame();
		break;

	case MODE_RESULT:
		//リザルト画面の終了処理
		UninitResult();
		break;
	case MODE_RANKING:
		//ランキング終了処理
		UninitRanking();
		break;
	}

	//画面遷移後の画面の初期化処理
	switch (mode)
	{
	case MODE_TITLE:
		//タイトルの初期化処理
		InitTitle();
		break;

	case MODE_TUTORIAL:
		//チュートリアルの初期化処理
		InitTutorial();
		break;

	case MODE_GAME:
		//ゲーム画面の初期化処理
		InitGame();
		break;

	case MODE_RESULT:
		//リザルト画面の初期化処理
		InitResult();
		break;

	case MODE_RANKING:
		//ランキング初期化
		InitRanking();
	}

	g_mode = mode;
}

////////////////////////////////////////////////////////////////////////////////
//デバイスの取得
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

HWND GethWnd(void)
{
	return hWnd;
}
