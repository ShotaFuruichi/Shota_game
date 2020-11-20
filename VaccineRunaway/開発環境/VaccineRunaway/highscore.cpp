////////////////////////////////////////////////////////////////////////////////
//
//Contents	: ハイスコア表示 [Highscore.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/09/25
//
////////////////////////////////////////////////////////////////////////////////
#include "highscore.h"
#include "input.h"
#include "score.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define POS_X (585.0f)		//ハイスコアのX座標

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9 g_pTextureHighScore = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHighScore = NULL;			//頂点バッファへの設定
int g_nHighScore = 0;

////////////////////////////////////////////////////////////////////////////////
//ハイスコアの初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT InitHighScore(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number001.png", &g_pTextureHighScore);

	//初期化
	g_nHighScore = NULL;

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffHighScore, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffHighScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHighScore = 0; nCntHighScore < MAX_SCORE; nCntHighScore++)
	{
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
	g_pVtxBuffHighScore->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//ハイスコアの終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitHighScore(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffHighScore != NULL)
	{
		g_pVtxBuffHighScore->Release();	//開放
		g_pVtxBuffHighScore = NULL;		//初期化
	}

	//テクスチャの開放
	if (g_pTextureHighScore != NULL)
	{
		g_pTextureHighScore->Release();	//開放
		g_pTextureHighScore = NULL;		//初期化
	}

}

////////////////////////////////////////////////////////////////////////////////
//ハイスコアの更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateHighScore(void)
{
	//変数宣言
	int pScore;
	VERTEX_2D *pVtx;

	pScore = GetScore();

	if (pScore >= g_nHighScore)
	{
		g_nHighScore = pScore;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffHighScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHighScore = 0; nCntHighScore < MAX_SCORE; nCntHighScore++)
	{
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(POS_X + (nCntHighScore * 95.0f), SCREEN_HEIGHT / 2 + 40.0f, 0);
	pVtx[1].pos = D3DXVECTOR3(POS_X + (nCntHighScore * 95.0f), SCREEN_HEIGHT / 2 - 40.0f, 0);
	pVtx[2].pos = D3DXVECTOR3(POS_X + ((nCntHighScore + 1) * 95.0f), SCREEN_HEIGHT / 2 + 40.0f, 0);
	pVtx[3].pos = D3DXVECTOR3(POS_X + ((nCntHighScore + 1) * 95.0f), SCREEN_HEIGHT / 2 - 40.0f, 0);
	pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffHighScore->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//ハイスコアの描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawHighScore(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffHighScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	for (int nCntHighScore = 0; nCntHighScore < MAX_SCORE; nCntHighScore++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureHighScore);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntHighScore * 4, 2);	//四角形を作る場合プリミティブの数を2にする
	}
}

////////////////////////////////////////////////////////////////////////////////
//ハイスコアの表示
////////////////////////////////////////////////////////////////////////////////
void AddHighScore(void)
{
	int nDigit = 10000000;	//スコアが8桁だから
	int nHighScore;
	int nHighScore2;
	float fPosition;
	VERTEX_2D *pVtx;

	nHighScore = g_nHighScore;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffHighScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHighScore = 0; nCntHighScore < 8; nCntHighScore++, nDigit /= 10)
	{
		//現在のスコアを10の桁数＋１乗で割った余りを代入
		nHighScore2 = nHighScore % (nDigit * 10);

		//上で出した値を10の桁数乗で割った商を代入
		nHighScore2 /= nDigit;

		//テクスチャのポジションを決定
		fPosition = (float)nHighScore2 / 10;

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(fPosition, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(fPosition, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(fPosition + 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(fPosition + 0.1f, 0.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffHighScore->Unlock();
}