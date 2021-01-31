////////////////////////////////////////////////////////////////////////////////
//
//Contents	: スコア表示 [score.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/08/24
//
////////////////////////////////////////////////////////////////////////////////
#include "score.h"
#include "input.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define POS_X (750.0f)		//スコアのX座標
#define SCORE_WIDTH (45.0f)	//スコアの大きさX
#define SCORE_HEIGHT (50.0f)//スコアの大きさY

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;			//頂点バッファへの設定
int g_nScore;

////////////////////////////////////////////////////////////////////////////////
//スコアの初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT InitScore(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number001.png", &g_pTextureScore);

	//初期化
	g_nScore = NULL;

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffScore, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(POS_X + (nCntScore * SCORE_WIDTH), SCORE_HEIGHT,0);
		pVtx[1].pos = D3DXVECTOR3(POS_X + (nCntScore * SCORE_WIDTH), 0, 0);
		pVtx[2].pos = D3DXVECTOR3(POS_X + ((nCntScore + 1) * SCORE_WIDTH), SCORE_HEIGHT, 0);
		pVtx[3].pos = D3DXVECTOR3(POS_X + ((nCntScore + 1) * SCORE_WIDTH), 0, 0);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 225, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);

		pVtx += 4;

		
	}
	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//スコアの終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitScore(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();	//開放
		g_pVtxBuffScore = NULL;		//初期化
	}

	//テクスチャの開放
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();	//開放
		g_pTextureScore = NULL;		//初期化
	}

}

////////////////////////////////////////////////////////////////////////////////
//スコアの更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateScore(void)
{
	
}

////////////////////////////////////////////////////////////////////////////////
//スコアの描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawScore(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureScore);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);	//四角形を作る場合プリミティブの数を2にする
	}

}

////////////////////////////////////////////////////////////////////////////////
//スコア変換
////////////////////////////////////////////////////////////////////////////////
void AddScore(int nValue)
{
	int nDigit = 10000000;	//スコアが8桁だから
	int nScore;
	int nScore2;
	float fPosition;
	VERTEX_2D *pVtx;

	g_nScore += nValue;

	nScore = g_nScore;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < 8; nCntScore++, nDigit /= 10)
	{
		//現在のスコアを10の桁数＋１乗で割った余りを代入
		nScore2 = nScore % (nDigit * 10);

		//上で出した値を10の桁数乗で割った商を代入
		nScore2 /= nDigit;

		//テクスチャのポジションを決定
		fPosition = (float)nScore2 / 10;

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(fPosition, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(fPosition, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(fPosition + 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(fPosition + 0.1f, 0.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//スコアの取得
////////////////////////////////////////////////////////////////////////////////p
int GetScore(void)
{
	return g_nScore;
}