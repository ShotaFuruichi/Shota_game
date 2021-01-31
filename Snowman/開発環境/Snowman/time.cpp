////////////////////////////////////////////////////////////////////////////////
//
//Contents	: 制限時間の表示 [time.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/11/09
//
////////////////////////////////////////////////////////////////////////////////
#include "time.h"
#include "fade.h"
#include "game.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define POS_X (900.0f)		//制限時間のX座標

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;			//頂点バッファへの設定
int g_nTime;
bool g_bClear;

////////////////////////////////////////////////////////////////////////////////
//制限時間の初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT InitTime(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//デバイスの取得
	pDevice = GetDevice();
	
	//初期化
	g_pTextureTime = NULL;
	g_pVtxBuffTime = NULL;
	g_nTime = 7200;
	g_bClear = false;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number000.png", &g_pTextureTime);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIME, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTime, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(POS_X + (nCntTime *90.0f), 100.0f, 0);
		pVtx[1].pos = D3DXVECTOR3(POS_X + (nCntTime * 90.0f), 0, 0);
		pVtx[2].pos = D3DXVECTOR3(POS_X + ((nCntTime + 1) * 90.0f), 100.0f, 0);
		pVtx[3].pos = D3DXVECTOR3(POS_X + ((nCntTime + 1) * 90.0f), 0, 0);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);

		pVtx += 4;


	}
	//頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//制限時間の終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitTime(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();	//開放
		g_pVtxBuffTime = NULL;		//初期化
	}

	//テクスチャの開放
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();	//開放
		g_pTextureTime = NULL;		//初期化
	}
}

////////////////////////////////////////////////////////////////////////////////
//制限時間の更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateTime(void)
{
	int nTime = 0;
	int nTime2 = 0;
	int nDigit = 100;
	float fPosition;
	VERTEX_2D *pVtx;

	//クリアまたはゲームオーバーしていないとき
	if (g_bClear == false)
	{
		g_nTime--;
		nTime = g_nTime;

		nTime /= 60;

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++, nDigit /= 10)
		{
			//現在の時間を10の桁数＋１乗で割った余りを代入
			nTime2 = nTime % (nDigit * 10);

			//上で出した値を10の桁数乗で割った商を代入
			nTime2 /= nDigit;

			//テクスチャのポジションを決定
			fPosition = (float)nTime2 / 10;

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(fPosition, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(fPosition, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(fPosition + 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(fPosition + 0.1f, 0.0f);

			pVtx += 4;
		}
		//頂点バッファをアンロックする
		g_pVtxBuffTime->Unlock();

		if (g_nTime == 0)
		{
			g_bClear = true;
			SetFade(FADE_OUT, MODE_RESULT);
			SetStageMode(STAGE_MAX);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//制限時間の描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawTime(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTime);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTime * 4, 2);	//四角形を作る場合プリミティブの数を2にする
	}

}

//////////////////////////////////////////////////////////////////////////////////
////スコア変換
//////////////////////////////////////////////////////////////////////////////////
//void AddScore(int nValue)
//{
//	int nDigit = 10000000;	//スコアが8桁だから
//	int nScore;
//	int nScore2;
//	float fPosition;
//	VERTEX_2D *pVtx;
//
//	g_nScore += nValue;
//
//	nScore = g_nScore;
//
//	//頂点バッファをロックし、頂点情報へのポインタを取得
//	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int nCntScore = 0; nCntScore < 8; nCntScore++, nDigit /= 10)
//	{
//		//現在のスコアを10の桁数＋１乗で割った余りを代入
//		nScore2 = nScore % (nDigit * 10);
//
//		//上で出した値を10の桁数乗で割った商を代入
//		nScore2 /= nDigit;
//
//		//テクスチャのポジションを決定
//		fPosition = (float)nScore2 / 10;
//
//		//テクスチャ座標の設定
//		pVtx[0].tex = D3DXVECTOR2(fPosition, 1.0f);
//		pVtx[1].tex = D3DXVECTOR2(fPosition, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(fPosition + 0.1f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(fPosition + 0.1f, 0.0f);
//
//		pVtx += 4;
//	}
//	//頂点バッファをアンロックする
//	g_pVtxBuffScore->Unlock();
//}

////////////////////////////////////////////////////////////////////////////////
//スコアの取得
////////////////////////////////////////////////////////////////////////////////
int GetTime(void)
{
	return g_nTime;
}

////////////////////////////////////////////////////////////////////////////////
//クリア情報の取得
////////////////////////////////////////////////////////////////////////////////
bool GetClear(void)
{
	return g_bClear;
}