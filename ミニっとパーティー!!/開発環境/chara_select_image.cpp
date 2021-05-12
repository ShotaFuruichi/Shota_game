//-----------------------------------------------------------------
//
// キャラセレクトイメージ (chara_select_image.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "chara_select_image.h"

//-------------------------------------------------------------------
// マクロ定義
//-------------------------------------------------------------------
#define SCORE_X			(970.0f)				// 中心座標(X)
#define SCORE_Y			(50.0f)					// 中心座標(Y)

#define SCORE_WIDTH		(45.0f)					// スコアの幅
#define SCORE_HEIGHT	(80.0f)					// スコアの高さ
#define WIDTH_X			(40.0f)					// スコアを配置する間隔

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCharaSelectImage = NULL;				// キャラセレクトイメージのテクスチャのポインタ
LPDIRECT3DTEXTURE9 g_pTextureCharaSelectImage[MAX_CHARAIMAGE] = {};		// キャラセレクトイメージの頂点バッファのポインタ
CharaSelectImage g_aCharaSelectImage[MAX_CHARAIMAGE];						// キャラセレクトイメージの情報

//-----------------------------------------------------------------
// キャラセレクトイメージの初期化処理
//-----------------------------------------------------------------
HRESULT InitCharaSelectImage(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// テクスチャの読み込み	
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/chara_image1.jpg", &g_pTextureCharaSelectImage[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/chara_image2.jpg", &g_pTextureCharaSelectImage[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/chara_image3.jpg", &g_pTextureCharaSelectImage[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/chara_image4.jpg", &g_pTextureCharaSelectImage[3]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/chara_image_random.jpg", &g_pTextureCharaSelectImage[4]);

	// 変数の初期化
	for (int nCntImage = 0; nCntImage < MAX_CHARAIMAGE; nCntImage++)
	{
		g_aCharaSelectImage[nCntImage].pos = D3DXVECTOR3(340.0f + nCntImage * 150.0f, 620.0f, 0.0f);
		g_aCharaSelectImage[nCntImage].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aCharaSelectImage[nCntImage].fWidth = 120.0f;
		g_aCharaSelectImage[nCntImage].fHeight = 120.0f;
		g_aCharaSelectImage[nCntImage].bSelect = false;
	}

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX * MAX_CHARAIMAGE, // 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffCharaSelectImage,
		NULL)))
	{
		return E_FAIL;
	}

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffCharaSelectImage->Lock(0, 0, (void**)&pVtx, 0);

	// 初期化
	for (int nCntImage = 0; nCntImage < MAX_CHARAIMAGE; nCntImage++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aCharaSelectImage[nCntImage].pos.x - (g_aCharaSelectImage[nCntImage].fWidth / 2), g_aCharaSelectImage[nCntImage].pos.y + (g_aCharaSelectImage[nCntImage].fHeight / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aCharaSelectImage[nCntImage].pos.x - (g_aCharaSelectImage[nCntImage].fWidth / 2), g_aCharaSelectImage[nCntImage].pos.y - (g_aCharaSelectImage[nCntImage].fHeight / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aCharaSelectImage[nCntImage].pos.x + (g_aCharaSelectImage[nCntImage].fWidth / 2), g_aCharaSelectImage[nCntImage].pos.y + (g_aCharaSelectImage[nCntImage].fHeight / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aCharaSelectImage[nCntImage].pos.x + (g_aCharaSelectImage[nCntImage].fWidth / 2), g_aCharaSelectImage[nCntImage].pos.y - (g_aCharaSelectImage[nCntImage].fHeight / 2), 0.0f);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = g_aCharaSelectImage[nCntImage].col;
		pVtx[1].col = g_aCharaSelectImage[nCntImage].col;
		pVtx[2].col = g_aCharaSelectImage[nCntImage].col;
		pVtx[3].col = g_aCharaSelectImage[nCntImage].col;

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// スコアの情報を次にうつす
		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffCharaSelectImage->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// キャラセレクトイメージの終了処理
//-----------------------------------------------------------------
void UninitCharaSelectImage(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffCharaSelectImage != NULL)
	{
		g_pVtxBuffCharaSelectImage->Release();
		g_pVtxBuffCharaSelectImage = NULL;
	}

	// テクスチャの開放
	for (int nCntTexture = 0; nCntTexture < MAX_CHARAIMAGE; nCntTexture++)
	{
		if (g_pTextureCharaSelectImage[nCntTexture] != NULL)
		{
			g_pTextureCharaSelectImage[nCntTexture]->Release();
			g_pTextureCharaSelectImage[nCntTexture] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// キャラセレクト枠の更新処理
//-----------------------------------------------------------------
void UpdateCharaSelectImage(void)
{

}

//-----------------------------------------------------------------
// キャラセレクトイメージの描画処理
//-----------------------------------------------------------------
void DrawCharaSelectImage(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffCharaSelectImage, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定と描画
	for (int nCntTexture = 0; nCntTexture < MAX_CHARAIMAGE; nCntTexture++)
	{
		pDevice->SetTexture(0, g_pTextureCharaSelectImage[nCntTexture]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTexture * 4, 2);
	}
}

//-----------------------------------------------------------------
// キャラセレクトイメージ情報の取得
//-----------------------------------------------------------------
CharaSelectImage *GetCharaSelectImage(void)
{
	return &g_aCharaSelectImage[0];
}