////////////////////////////////////////////////////////////////////////////////
//
//Contents	: 敵の処理 [enemy.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/10/23
//
////////////////////////////////////////////////////////////////////////////////
#include "enemy.h"
#include "block.h"
#include "time.h"
#include <time.h>

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define MAX_LIFE (100)	//敵のライフの最大値

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9 g_pTextureEnemy[ENEMYTYPE_MAX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;			//頂点バッファへの設定
ENEMY g_aEnemy[MAX_ENEMY];								//敵の情報

////////////////////////////////////////////////////////////////////////////////
//敵の初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT InitEnemy(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//変数の初期化
	for (int nCntEnemy = 0; nCntEnemy < ENEMYTYPE_MAX; nCntEnemy++)
	{
		g_pTextureEnemy[nCntEnemy] = NULL;	//テクスチャへのポインタ
	}
	g_pVtxBuffEnemy = NULL;

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{	
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(10000.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nJumpCounter = 0;
		g_aEnemy[nCntEnemy].nJumpTiming = GetRandom(30, 60);
		g_aEnemy[nCntEnemy].type = ENEMYTYPE_SPRING;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].nCounterState = NULL;
		g_aEnemy[nCntEnemy].nLife = MAX_LIFE;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy00.png", &g_pTextureEnemy[ENEMYTYPE_SPRING]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy00Freeze.png", &g_pTextureEnemy[ENEMYTYPE_SPRINGFREEZE]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy01.png", &g_pTextureEnemy[ENEMYTYPE_SUMMER]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy01Freeze.png", &g_pTextureEnemy[ENEMYTYPE_SUMMERFREEZE]);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffEnemy, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//頂点情報の設定
		SetVertexEnemy(nCntEnemy);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(225, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//敵の終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitEnemy(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();	//開放
		g_pVtxBuffEnemy = NULL;		//初期化
	}

	//テクスチャの開放
	for (int nCntEnemy = 0; nCntEnemy < ENEMYTYPE_MAX; nCntEnemy++)
	{
		if (g_pTextureEnemy[nCntEnemy] != NULL)
		{
			g_pTextureEnemy[nCntEnemy]->Release();	//開放
			g_pTextureEnemy[nCntEnemy] = NULL;		//初期化
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//敵の更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateEnemy(void)
{
	//変数宣言
	ENEMY *pEnemy;

	pEnemy = &g_aEnemy[0];

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{	//敵が使用されているとき
			
			pEnemy->posold = pEnemy->pos;
			switch (pEnemy->state)
			{
			case ENEMYSTATE_NORMAL:
				pEnemy->nCounterState = 0;
				pEnemy->move.y += 1.5f;

				pEnemy->pos.x += pEnemy->move.x;
				pEnemy->pos.y += pEnemy->move.y;

				if (pEnemy->pos.y > SCREEN_HEIGHT)
				{
					pEnemy->move.y = 0.0f;
					pEnemy->pos.y = SCREEN_HEIGHT;
				}
				
				if ((pEnemy->pos.x - DIAGONAL_X - 20) <= 0)
				{
					pEnemy->pos.x = DIAGONAL_X + 20;
					pEnemy->move.x *= -1;
				}
				if ((pEnemy->pos.x + DIAGONAL_X + 20) >= SCREEN_WIDTH)
				{
					pEnemy->pos.x = SCREEN_WIDTH - DIAGONAL_X - 20;
					pEnemy->move.x *= -1;
				}


				if (pEnemy->nLife <= 0)
				{
					pEnemy->state = ENEMYSTATE_FREEZE;
					pEnemy->move.x = 0.0f;
					pEnemy->move.y += 5.0f;
				}

				if (ColisionBlock(&pEnemy->pos, &pEnemy->posold, &pEnemy->move, ENEMY_SIZEX, ENEMY_SIZEY) == true)
				{
					pEnemy->move.x *= -1;
				}
				SetTextureEnemy(nCntEnemy);

				switch (pEnemy->type)
				{
				case ENEMYTYPE_SUMMER:
					pEnemy->nJumpCounter++;
					if (pEnemy->nJumpCounter % pEnemy->nJumpTiming == 0)
					{
						pEnemy->move.y -= 20.0f;
					}
					break;
				}

				break;
				
			case ENEMYSTATE_FREEZE:
				pEnemy->move.y += 1.5f;

				pEnemy->pos.x += pEnemy->move.x;
				pEnemy->pos.y += pEnemy->move.y;

				if ((pEnemy->pos.x - DIAGONAL_X - 20) <= 0)
				{
					pEnemy->pos.x = DIAGONAL_X + 20;
					pEnemy->move.x *= -1;
				}
				if ((pEnemy->pos.x + DIAGONAL_X + 20) >= SCREEN_WIDTH)
				{
					pEnemy->pos.x = SCREEN_WIDTH - DIAGONAL_X - 20;
					pEnemy->move.x *= -1;
				}

				if (pEnemy->pos.y > SCREEN_HEIGHT)
				{
					pEnemy->move.y = 0.0f;
					pEnemy->pos.y = SCREEN_HEIGHT;
				}
				if (ColisionBlock(&pEnemy->pos, &pEnemy->posold, &pEnemy->move, ENEMY_SIZEX, ENEMY_SIZEY) == true)
				{
					pEnemy->move.x = 0;
					
				}

				pEnemy->nCounterState++;
				if (pEnemy->nCounterState > 500)
				{
					pEnemy->state = ENEMYSTATE_NORMAL;
					pEnemy->nLife = MAX_LIFE;
					pEnemy->move.x = 2.5f;
				}

				break;
			}

			SetVertexEnemy(nCntEnemy);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//敵の描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawEnemy(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//テクスチャの設定
			switch (g_aEnemy[nCntEnemy].type)
			{
			case ENEMYTYPE_SPRING:
				switch (g_aEnemy[nCntEnemy].state)
				{
				case ENEMYSTATE_NORMAL:
					pDevice->SetTexture(0, g_pTextureEnemy[ENEMYTYPE_SPRING]);
					break;
				case ENEMYSTATE_FREEZE:
					pDevice->SetTexture(0, g_pTextureEnemy[ENEMYTYPE_SPRINGFREEZE]);
					break;
				}
				break;

			case ENEMYTYPE_SUMMER:
				switch (g_aEnemy[nCntEnemy].state)
				{
				case ENEMYSTATE_NORMAL:
					pDevice->SetTexture(0, g_pTextureEnemy[ENEMYTYPE_SUMMER]);
					break;
				case ENEMYSTATE_FREEZE:
					pDevice->SetTexture(0, g_pTextureEnemy[ENEMYTYPE_SUMMERFREEZE]);
					break;
				}
				break;
			}
			

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//敵のセット処理
////////////////////////////////////////////////////////////////////////////////
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMYTYPE type)
{
	//変数宣言
	ENEMY *pEnemy;
	pEnemy = &g_aEnemy[0];

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == false)
		{	//敵が使用されていないとき
			pEnemy->pos = pos;
			pEnemy->move = move;
			pEnemy->type = type;
			pEnemy->state = ENEMYSTATE_NORMAL;
			pEnemy->nLife = MAX_LIFE;
			pEnemy->bUse = true;
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//ポインタの取得
////////////////////////////////////////////////////////////////////////////////
ENEMY *GetEnemy(void)
{
	return &g_aEnemy[0];
}

////////////////////////////////////////////////////////////////////////////////
//通常敵の頂点座標の設定
////////////////////////////////////////////////////////////////////////////////
void SetVertexEnemy(int nIdx)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x - ENEMY_SIZEX, g_aEnemy[nIdx].pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x - ENEMY_SIZEX, g_aEnemy[nIdx].pos.y - ENEMY_SIZEY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x + ENEMY_SIZEX, g_aEnemy[nIdx].pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x + ENEMY_SIZEX, g_aEnemy[nIdx].pos.y - ENEMY_SIZEY, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//テクスチャ座標
////////////////////////////////////////////////////////////////////////////////
void SetTextureEnemy(int nIdx)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	if (g_aEnemy[nIdx].move.x < 0)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	}
	else
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//敵のステート処理
////////////////////////////////////////////////////////////////////////////////
bool HitEnemy(int nIdx, int nDamage)
{
	g_aEnemy[nIdx].nLife -= nDamage;
	
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//ランダムな数値を取得
////////////////////////////////////////////////////////////////////////////////
int GetRandom(int min, int max)
{
	static int nNum;

	if (nNum == 0)
	{
		srand((unsigned int)time(NULL));
		nNum = 1;
	}

	return min + (rand() * (max - min + 1) / (1 + RAND_MAX));
}
