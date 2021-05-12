//-----------------------------------------------------------------
//
// フィニッシュゲーム (finish_game.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "finish_game.h"
#include "timer.h"
#include "sound.h"

//-------------------------------------------------------------------
// マクロ定義
//-------------------------------------------------------------------
#define FINISHGAME_X		(SCREEN_WIDTH / 2.0f)		// フィニッシュゲームの中心座標(X)
#define FINISHGAME_Y		(SCREEN_HEIGHT / 2.0f)		// フィニッシュゲームの中心座標(Y)
#define FINISHGAME_WIDTH	(320.0f)					// フィニッシュゲームの幅
#define FINISHGAME_HEIGHT	(90.0f)						// フィニッシュゲームの高さ

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFinishGame = NULL;	// フィニッシュゲームのテクスチャのポインタ
LPDIRECT3DTEXTURE9 g_pTextureFinishGame = NULL;			// フィニッシュゲームの頂点バッファのポインタ
FinishGame g_FinishGame;								// フィニッシュゲームの情報

//-----------------------------------------------------------------
// フィニッシュゲームの初期化処理
//-----------------------------------------------------------------
HRESULT InitFinishGame(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// テクスチャの読み込み	
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/timeup_logo.png", &g_pTextureFinishGame);

	// 変数の初期化
	g_FinishGame.pos = D3DXVECTOR3(FINISHGAME_X, FINISHGAME_Y, 0.0f);
	g_FinishGame.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_FinishGame.nCntAlufa = 50;
	g_FinishGame.fCntSize = 1.0f;
	g_FinishGame.nTExType = 0;
	g_FinishGame.bUse = true;
	g_FinishGame.bFinish = false;

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX, // 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffFinishGame,
		NULL)))
	{
		return E_FAIL;
	}

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffFinishGame->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の更新
	SetVertexFinishGame();

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// テクスチャの更新
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffFinishGame->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// フィニッシュゲームの終了処理
//-----------------------------------------------------------------
void UninitFinishGame(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffFinishGame != NULL)
	{
		g_pVtxBuffFinishGame->Release();
		g_pVtxBuffFinishGame = NULL;
	}

	// テクスチャの開放
	if (g_pTextureFinishGame != NULL)
	{
		g_pTextureFinishGame->Release();
		g_pTextureFinishGame = NULL;
	}
	
}

//-----------------------------------------------------------------
// フィニッシュゲームの更新処理
//-----------------------------------------------------------------
void UpdateFinishGame(void)
{
	// 頂点座標の更新
	SetVertexFinishGame();
}

//-----------------------------------------------------------------
// フィニッシュゲームの描画処理
//-----------------------------------------------------------------
void DrawFinishGame(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFinishGame, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定と描画
	if (g_FinishGame.bFinish == true)
	{
		pDevice->SetTexture(0, g_pTextureFinishGame);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//-----------------------------------------------------------------
// 頂点座標の設定
//-----------------------------------------------------------------
void SetVertexFinishGame(void)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffFinishGame->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の更新
	pVtx[0].pos = D3DXVECTOR3(g_FinishGame.pos.x - (FINISHGAME_WIDTH / 2) * g_FinishGame.fCntSize, g_FinishGame.pos.y + (FINISHGAME_HEIGHT / 2) * g_FinishGame.fCntSize, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_FinishGame.pos.x - (FINISHGAME_WIDTH / 2) * g_FinishGame.fCntSize, g_FinishGame.pos.y - (FINISHGAME_HEIGHT / 2) * g_FinishGame.fCntSize, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_FinishGame.pos.x + (FINISHGAME_WIDTH / 2) * g_FinishGame.fCntSize, g_FinishGame.pos.y + (FINISHGAME_HEIGHT / 2) * g_FinishGame.fCntSize, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_FinishGame.pos.x + (FINISHGAME_WIDTH / 2) * g_FinishGame.fCntSize, g_FinishGame.pos.y - (FINISHGAME_HEIGHT / 2) * g_FinishGame.fCntSize, 0.0f);	

	// 頂点カラーの更新
	pVtx[0].col = g_FinishGame.col;
	pVtx[1].col = g_FinishGame.col;
	pVtx[2].col = g_FinishGame.col;
	pVtx[3].col = g_FinishGame.col;

	// 頂点バッファをアンロックする
	g_pVtxBuffFinishGame->Unlock();
}

//-----------------------------------------------------------------
// ゲームが終わったかどうか取得
//-----------------------------------------------------------------
void SetFinishGame(bool bFinish)
{
	if (g_FinishGame.bFinish == false)
	{
		PlaySound(SOUND_LABEL_SE_FINISH);
	}
	g_FinishGame.bFinish = bFinish;
}

//-----------------------------------------------------------------
// ゲームが終わったかどうか取得
//-----------------------------------------------------------------
bool GetFinishGame(void)
{
	return g_FinishGame.bFinish;
}