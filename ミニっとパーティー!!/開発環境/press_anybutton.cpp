//-----------------------------------------------------------------
//
// ボタン指示 (press_anybutton.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "press_anybutton.h"
#include "texture.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"
#include "sound.h"

// マクロ
#define FLASH_INTERBAL_MODELOGO		(10)				// 点滅インターバル
#define CLEAR_NUMBER_MODELOGO		(5)					// 透明
#define LESS_CLEAR_NUMBER_MODELOGO	(0)					// 不透明
#define FLASH_COUNT					(50)				// フラッシュカウント

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPressAnyButton = NULL;			// セレクトモードの頂点バッファのポインタ
PressAnyButton g_PressAnyButton;								// セレクトモードの情報
int g_nCntFlash;												// 点滅カウント

//-----------------------------------------------------------------
// ボタン指示の初期化処理
//-----------------------------------------------------------------
HRESULT InitPressAnyButton(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// 変数の初期化
	g_PressAnyButton.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_PressAnyButton.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	g_PressAnyButton.fRemoveAlpha = 0.0f;
	g_PressAnyButton.fWidth = 0.0f;
	g_PressAnyButton.fHeight = 0.0f;
	g_PressAnyButton.nTexType = -1;
	g_PressAnyButton.bUse = false;
	g_PressAnyButton.bPressAnyButton = false;

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX , // 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffPressAnyButton,
		NULL)))
	{
		return E_FAIL;
	}

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPressAnyButton->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	SetVertexPressAnyButton();

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

	// 頂点バッファをアンロックする
	g_pVtxBuffPressAnyButton->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// ボタン指示の終了処理
//-----------------------------------------------------------------
void UninitPressAnyButton(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffPressAnyButton != NULL)
	{
		g_pVtxBuffPressAnyButton->Release();
		g_pVtxBuffPressAnyButton = NULL;
	}
}

//-----------------------------------------------------------------
// ボタン指示の更新処理
//-----------------------------------------------------------------
void UpdatePressAnyButton(void)
{
	// 頂点座標の更新
	if (g_PressAnyButton.bPressAnyButton == false)
	{
		if (GetJoypadTrigger(PLAYER_1, JPINFO_PAUSE))
		{
			g_PressAnyButton.bPressAnyButton = true;
			PlaySound(SOUND_LABEL_SE_DICIDE);
		}
		if ((g_PressAnyButton.col.a < 0.3f) || (g_PressAnyButton.col.a > 1.0f))
		{// 透明
			g_PressAnyButton.fRemoveAlpha -= g_PressAnyButton.fRemoveAlpha * 2.0f;
		}
		// 色の更新
		g_PressAnyButton.col.a -= g_PressAnyButton.fRemoveAlpha;
	}
	else
	{
		// 点滅させるためにカウントを進める
		g_nCntFlash++;

		if (CLEAR_NUMBER_MODELOGO == g_nCntFlash % FLASH_INTERBAL_MODELOGO)
		{// 透明
			g_PressAnyButton.col.a = 0.0f;
		}
		else if (LESS_CLEAR_NUMBER_MODELOGO == g_nCntFlash % FLASH_INTERBAL_MODELOGO)
		{// 不透明
			g_PressAnyButton.col.a = 1.0f;
		}
		// カウントがある程度進んだら遷移
		if (g_nCntFlash >= FLASH_COUNT)
		{// 次に進んだとき処理
		 // ゲームに遷移
			SetFade(FADE_OUT, MODE_TUTORIAL);
		}
	}
	// 頂点座標の更新
	SetVertexPressAnyButton();
}

//-----------------------------------------------------------------
// ボタン指示の描画処理
//-----------------------------------------------------------------
void DrawPressAnyButton(void)
{
	// UIテクスチャ情報の取得
	Texture *pTexture = GetUITexture();

	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPressAnyButton, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	pDevice->SetTexture(0, pTexture->TextureInfo[g_PressAnyButton.nTexType].pTexture);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, 2);
}

//-----------------------------------------------------------------
// ボタン指示の設置
//-----------------------------------------------------------------
void SetPressAnyButton(D3DXVECTOR3 pos, D3DXCOLOR col,float fRemoveAlpha, float fWidth, float fHeight, int nTextype)
{
	// セレクトモード設置情報の取得
	PressAnyButton *pPressAnyButton = &g_PressAnyButton;

	if (pPressAnyButton->bUse == false)
	{
		// 位置情報の格納
		pPressAnyButton->pos = pos;

		// 色情報の格納
		pPressAnyButton->col = col;

		// α値減少量の格納
		pPressAnyButton->fRemoveAlpha = fRemoveAlpha;

		// 幅の格納
		pPressAnyButton->fWidth = fWidth;

		// 高さの格納
		pPressAnyButton->fHeight = fHeight;

		// テクスチャタイプの格納
		pPressAnyButton->nTexType = nTextype;

		// 使用状態をtrueにする
		pPressAnyButton->bUse = true;
	}
}

//-----------------------------------------------------------------
// 頂点座標の設定
//-----------------------------------------------------------------
void SetVertexPressAnyButton(void)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;
	PressAnyButton *pPressAnyButton = &g_PressAnyButton;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPressAnyButton->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の更新
	pVtx[0].pos = D3DXVECTOR3(pPressAnyButton->pos.x - (pPressAnyButton->fWidth / 2.0f), pPressAnyButton->pos.y + (pPressAnyButton->fHeight / 2.0f), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pPressAnyButton->pos.x - (pPressAnyButton->fWidth / 2.0f), pPressAnyButton->pos.y - (pPressAnyButton->fHeight / 2.0f), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pPressAnyButton->pos.x + (pPressAnyButton->fWidth / 2.0f), pPressAnyButton->pos.y + (pPressAnyButton->fHeight / 2.0f), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pPressAnyButton->pos.x + (pPressAnyButton->fWidth / 2.0f), pPressAnyButton->pos.y - (pPressAnyButton->fHeight / 2.0f), 0.0f);

	// 頂点カラーの設定
	pVtx[0].col = pPressAnyButton->col;
	pVtx[1].col = pPressAnyButton->col;
	pVtx[2].col = pPressAnyButton->col;
	pVtx[3].col = pPressAnyButton->col;

	// 頂点バッファをアンロックする
	g_pVtxBuffPressAnyButton->Unlock();
}

//-----------------------------------------------------------------
// ボタン指示情報の取得
//-----------------------------------------------------------------
PressAnyButton *GetPressAnyButton(void)
{
	return &g_PressAnyButton;
}