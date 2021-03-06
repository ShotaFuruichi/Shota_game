//-----------------------------------------------------------------
//
// ポーズ (pause.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "pause.h"
#include "loadscreen.h"
#include "game.h"
#include "fade.h"
#include "input.h"
#include "gamepad.h"
#include "sound.h"

//-----------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------
#define MAX_PATTERN				(6)					// アニメーションパターンNo.の最大数

#define PAUSE_MENU_BG_X			(SCREEN_WIDTH / 2)	// ポーズメニューの中心座標X
#define PAUSE_MENU_BG_Y			(370.0f)			// ポーズメニューの中心座標Y
#define PAUSE_MENU_BG_WIDTH		(400.0f)			// ポーズメニューの幅
#define PAUSE_MENU_BG_HEIGHT	(480.0f)			// ポーズメニューの高さ

#define LOGO_X					(SCREEN_WIDTH / 2)	// ロゴの中心座標X(すべて共通)
#define LOGO_Y					(270.0f)			// ロゴの中心座標Y(すべて共通)
#define LOGO_WIDTH				(280.0f)			// ロゴの幅(すべて共通)
#define LOGO_HEIGHT				(70.0f)				// ロゴの高さ(すべて共通)

#define ALUFA_INTERBAL			(10)				// 点滅のインターバル

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;			// ポーズ画面の頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTexturePause[MAX_PATTERN] = {};	// ポーズ画面のテクスチャのポインタ
D3DXCOLOR g_Pausecol;									// ポーズ画面の色
int g_nPauseCnt;										// どのモードを選んでいるか
int g_nMoveAlufaCnt;

//-----------------------------------------------------------------
// ポーズの初期化処理
//-----------------------------------------------------------------
HRESULT InitPause(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// 変数の初期化
	g_nPauseCnt = PAUSE_MENU_CONTINUE;
	g_Pausecol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_nMoveAlufaCnt = 0;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause_menu_bg.png", &g_pTexturePause[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/continue_logo.png", &g_pTexturePause[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/retry_logo.png", &g_pTexturePause[3]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/chara_select_logo.png", &g_pTexturePause[4]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/quit_logo.png", &g_pTexturePause[5]);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX * MAX_PATTERN, // 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL)))
	{
		return E_FAIL;
	}

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPause = 0; nCntPause < MAX_PATTERN; nCntPause++)
	{
		// 頂点座標の設定
		SetVertexPause(nCntPause);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// 情報の更新
		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// ポーズの終了処理
//-----------------------------------------------------------------
void UninitPause(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}

	// テクスチャの開放
	for (int nCntPause = 0; nCntPause < MAX_PATTERN; nCntPause++)
	{
		if (g_pTexturePause[nCntPause] != NULL)
		{
			g_pTexturePause[nCntPause]->Release();
			g_pTexturePause[nCntPause] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// ポーズの更新処理
//-----------------------------------------------------------------
void UpdatePause(void)
{
	// 変数宣言
	bool *pStick = GetStickTrigger(PLAYER_1);
	bool *pCrossKey = GetCrossKeyTrigger(PLAYER_1);

	// JOYPAD の処理
	if (pStick[STICKTRIGGER_UP] == true ||
		pCrossKey[CROSSKEYPRESS_UP] == true ||
		GetKeyboardTrigger(KEYINFO_UP) == true)
	{// 次の情報の確定
		g_nPauseCnt--;

		if (g_nPauseCnt < PAUSE_MENU_CONTINUE)
		{// 0より小さくなったとき更新
			g_nPauseCnt = PAUSE_MENU_QUIT;
		}
		// SE
		PlaySound(SOUND_LABEL_SE_CURSOR);
	}
	if (pStick[STICKTRIGGER_DOWN] == true ||
		pCrossKey[CROSSKEYPRESS_DOWN] == true ||
		GetKeyboardTrigger(KEYINFO_DOWN) == true)
	{// 次の情報の確定
		g_nPauseCnt++;

		if (g_nPauseCnt > PAUSE_MENU_QUIT)
		{// 2より大きくなったとき更新
			g_nPauseCnt = PAUSE_MENU_CONTINUE;
		}
		// SE
		PlaySound(SOUND_LABEL_SE_CURSOR);
	}
	// どの情報で押したか
	if (GetJoypadTrigger(PLAYER_1, JPINFO_OKorJUMP) == true ||
		GetKeyboardTrigger(KEYINFO_OK) == true)
	{
		if (g_nPauseCnt == PAUSE_MENU_CONTINUE)
		{// コンティニュー
			SetPause(false);
			// SE
			PlaySound(SOUND_LABEL_SE_CANSEL);
		}
		else if (g_nPauseCnt == PAUSE_MENU_RETRY)
		{// リトライ
			SetFade(FADE_OUT, MODE_GAME);
			// SE
			PlaySound(SOUND_LABEL_SE_DICIDE);
		}
		else if (g_nPauseCnt == PAUSE_MENU_CHARASELECT)
		{// クイット
			SetFade(FADE_OUT, MODE_CHARASELECT);
			// SE
			PlaySound(SOUND_LABEL_SE_DICIDE);
		}
		else if (g_nPauseCnt == PAUSE_MENU_QUIT)
		{// クイット
			SetFade(FADE_OUT, MODE_TITLE);
			// SE
			PlaySound(SOUND_LABEL_SE_DICIDE);
		}
	}
	else if (GetJoypadTrigger(PLAYER_1, JPINFO_PAUSE) == true)
	{// コンティニューに初期化
		g_nPauseCnt = PAUSE_MENU_CONTINUE;
	}
	// 頂点座標の更新
	for (int nCnt = 0; nCnt < MAX_PATTERN; nCnt++)
	{
		SetVertexPause(nCnt);
	}
}

//-----------------------------------------------------------------
// ポーズの描画処理
//-----------------------------------------------------------------
void DrawPause(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for (int nCntPause = 0; nCntPause < MAX_PATTERN; nCntPause++)
	{
		pDevice->SetTexture(0, g_pTexturePause[nCntPause]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPause * 4, 2);
	}
}

//-----------------------------------------------------------------
// ポーズの頂点座標の設定
//-----------------------------------------------------------------
void SetVertexPause(int nCntPause)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	// 何番目か
	pVtx += nCntPause * 4;
	if (nCntPause == 0)
	{// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	}
	else if (nCntPause == 1)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(PAUSE_MENU_BG_X - PAUSE_MENU_BG_WIDTH / 2, PAUSE_MENU_BG_Y + PAUSE_MENU_BG_HEIGHT / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(PAUSE_MENU_BG_X - PAUSE_MENU_BG_WIDTH / 2, PAUSE_MENU_BG_Y - PAUSE_MENU_BG_HEIGHT / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(PAUSE_MENU_BG_X + PAUSE_MENU_BG_WIDTH / 2, PAUSE_MENU_BG_Y + PAUSE_MENU_BG_HEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(PAUSE_MENU_BG_X + PAUSE_MENU_BG_WIDTH / 2, PAUSE_MENU_BG_Y - PAUSE_MENU_BG_HEIGHT / 2, 0.0f);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else if (nCntPause >= 2 && nCntPause < 6)
	{
		PauseMenu(nCntPause);
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();
}

//-----------------------------------------------------------------
// ポーズメニュー
//-----------------------------------------------------------------
void PauseMenu(int nCnt)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	// 変数宣言
	float fPosY = 80;

	pVtx += 4 * nCnt;
	fPosY *= nCnt - 2;

	// 頂点座標の更新
	pVtx[0].pos = D3DXVECTOR3(LOGO_X - (LOGO_WIDTH / 2), LOGO_Y + fPosY + (LOGO_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(LOGO_X - (LOGO_WIDTH / 2), LOGO_Y + fPosY - (LOGO_HEIGHT / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(LOGO_X + (LOGO_WIDTH / 2), LOGO_Y + fPosY + (LOGO_HEIGHT / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(LOGO_X + (LOGO_WIDTH / 2), LOGO_Y + fPosY - (LOGO_HEIGHT / 2), 0.0f);

	if (g_nPauseCnt == (nCnt - 2) % PAUSE_MENU_MAX)
	{// 選ばれているとき点滅にする
		g_Pausecol.a = 1.0f;
	}
	else
	{// 選ばれていないとき半透明にする
		g_Pausecol.a = 0.2f;
	}
	// 頂点カラーの設定
	pVtx[0].col = g_Pausecol;
	pVtx[1].col = g_Pausecol;
	pVtx[2].col = g_Pausecol;
	pVtx[3].col = g_Pausecol;

	// 頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();
}