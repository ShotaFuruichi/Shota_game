//-----------------------------------------------------------------
//
// キャラ決定 (dicision_chara.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "dicision_chara.h"
#include "chara_select_frame.h"
#include "chara_select_image.h"
#include "chara.h"
#include "gamepad.h"
#include "player.h"
#include "fade.h"
#include "sound.h"

//-------------------------------------------------------------------
// マクロ定義
//-------------------------------------------------------------------
#define MAX_TEXTURE		(2)						// テクスチャ枚数
#define MAX_DICISION	(5)
#define SCORE_X			(970.0f)				// 中心座標(X)
#define SCORE_Y			(50.0f)					// 中心座標(Y)

#define SCORE_WIDTH		(45.0f)					// スコアの幅
#define SCORE_HEIGHT	(80.0f)					// スコアの高さ
#define WIDTH_X			(40.0f)					// スコアを配置する間隔

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffDicisionChara = NULL;			// キャラ決定のテクスチャのポインタ
LPDIRECT3DTEXTURE9 g_pTextureDicisionChara[MAX_TEXTURE] = {};	// キャラ決定の頂点バッファのポインタ
DicisionChara g_aDicisionChara[MAX_DICISION];					// キャラ決定の情報
int g_nNumDicision;

//-----------------------------------------------------------------
// キャラセレクト枠の初期化処理
//-----------------------------------------------------------------
HRESULT InitDicisionChara(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// キャラセレクトイメージ情報の取得
	CharaSelectImage *pCharaSelectImage = GetCharaSelectImage();

	g_nNumDicision = 0;

	// テクスチャの読み込み	
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ok.png", &g_pTextureDicisionChara[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/press_start00.jpg", &g_pTextureDicisionChara[1]);

	// 変数の初期化
	for (int nCntDicisionChara = 0; nCntDicisionChara < MAX_DICISION; nCntDicisionChara++, pCharaSelectImage++)
	{
		if (nCntDicisionChara == 4)
		{
			g_aDicisionChara[nCntDicisionChara].pos = D3DXVECTOR3(640.0f, 500.0f, 0.0f);
			g_aDicisionChara[nCntDicisionChara].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_aDicisionChara[nCntDicisionChara].fWidth = 1280.0f;
			g_aDicisionChara[nCntDicisionChara].fHeight = 60.0f;
			g_aDicisionChara[nCntDicisionChara].nTxType = 1;
		}
		else
		{
			g_aDicisionChara[nCntDicisionChara].pos = D3DXVECTOR3(160.0f + 320.0f * nCntDicisionChara, 500.0f, 0.0f);
			g_aDicisionChara[nCntDicisionChara].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_aDicisionChara[nCntDicisionChara].fWidth = 320.0f;
			g_aDicisionChara[nCntDicisionChara].fHeight = 60.0f;
			g_aDicisionChara[nCntDicisionChara].nTxType = 0;
		}
		g_aDicisionChara[nCntDicisionChara].bDicision = false;
	}

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX * MAX_DICISION, // 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffDicisionChara,
		NULL)))
	{
		return E_FAIL;
	}

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffDicisionChara->Lock(0, 0, (void**)&pVtx, 0);

	// 初期化
	for (int nCntDicisionChara = 0; nCntDicisionChara < MAX_DICISION; nCntDicisionChara++)
	{
		// 頂点座標の設定
		SetVertexDicisionChara(nCntDicisionChara);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = g_aDicisionChara[nCntDicisionChara].col;
		pVtx[1].col = g_aDicisionChara[nCntDicisionChara].col;
		pVtx[2].col = g_aDicisionChara[nCntDicisionChara].col;
		pVtx[3].col = g_aDicisionChara[nCntDicisionChara].col;

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// スコアの情報を次にうつす
		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffDicisionChara->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// キャラセレクト枠の終了処理
//-----------------------------------------------------------------
void UninitDicisionChara(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffDicisionChara != NULL)
	{
		g_pVtxBuffDicisionChara->Release();
		g_pVtxBuffDicisionChara = NULL;
	}

	// テクスチャの開放
	for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE; nCntTexture++)
	{
		if (g_pTextureDicisionChara[nCntTexture] != NULL)
		{
			g_pTextureDicisionChara[nCntTexture]->Release();
			g_pTextureDicisionChara[nCntTexture] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// キャラセレクト枠の更新処理
//-----------------------------------------------------------------
void UpdateDicisionChara(void)
{
	// フレーム数を取得
	int nNumFrame = GetFrame();

	// 全員選んだ時
	if (g_nNumDicision == nNumFrame)
	{
		g_aDicisionChara[4].bDicision = true;

		for (int nCntPlayer = 0; nCntPlayer < nNumFrame; nCntPlayer++)
		{
			if (GetJoypadTrigger(nCntPlayer,JPINFO_PAUSE) == true)
			{// ミニゲーム選択画面に遷移
				SetFade(FADE_OUT, MODE_GAME);
				PlaySound(SOUND_LABEL_SE_BOMB);
			}
		}
	}
	else
	{
		g_aDicisionChara[4].bDicision = false;
	}

	for (int nCntDicisionChara = 0; nCntDicisionChara < MAX_DICISION; nCntDicisionChara++)
	{
		if (g_aDicisionChara[nCntDicisionChara].bDicision == true)
		{
			// 頂点座標の更新
			SetVertexDicisionChara(nCntDicisionChara);
		}
	}
}

//-----------------------------------------------------------------
// キャラセレクト枠の描画処理
//-----------------------------------------------------------------
void DrawDicisionChara(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffDicisionChara, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// 選択されたモードに応じて描画
	for (int nCntDicisionChara = 0; nCntDicisionChara < MAX_DICISION; nCntDicisionChara++)
	{
		if (g_aDicisionChara[nCntDicisionChara].bDicision == true)
		{
			pDevice->SetTexture(0, g_pTextureDicisionChara[g_aDicisionChara[nCntDicisionChara].nTxType]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntDicisionChara * 4, 2);
		}
	}
}

//-----------------------------------------------------------------
// キャラセレクトフレームの頂点座標の設定
//-----------------------------------------------------------------
void SetVertexDicisionChara(int nIdx)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffDicisionChara->Lock(0, 0, (void**)&pVtx, 0);

	// 何番目か
	pVtx += nIdx * 4;

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_aDicisionChara[nIdx].pos.x - g_aDicisionChara[nIdx].fWidth / 2.0f, g_aDicisionChara[nIdx].pos.y + g_aDicisionChara[nIdx].fHeight / 2.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aDicisionChara[nIdx].pos.x - g_aDicisionChara[nIdx].fWidth / 2.0f, g_aDicisionChara[nIdx].pos.y - g_aDicisionChara[nIdx].fHeight / 2.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aDicisionChara[nIdx].pos.x + g_aDicisionChara[nIdx].fWidth / 2.0f, g_aDicisionChara[nIdx].pos.y + g_aDicisionChara[nIdx].fHeight / 2.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aDicisionChara[nIdx].pos.x + g_aDicisionChara[nIdx].fWidth / 2.0f, g_aDicisionChara[nIdx].pos.y - g_aDicisionChara[nIdx].fHeight / 2.0f, 0.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffDicisionChara->Unlock();
}

//-----------------------------------------------------------------
// キャラセレクトフレーム情報の取得
//-----------------------------------------------------------------
DicisionChara *GetDicisionChara(void)
{
	return &g_aDicisionChara[0];
}

//-----------------------------------------------------------------
// セットするかどうか
//-----------------------------------------------------------------
void SetDicisionChara(bool bDicision,int nCntPlayer)
{
	g_aDicisionChara[nCntPlayer].bDicision = bDicision;

	if (bDicision == true)
	{
		g_nNumDicision++;
	}
	else
	{
		g_nNumDicision--;
	}
}