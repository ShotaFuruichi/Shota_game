////////////////////////////////////////////////////////////////////////////////
//
//Contents	: 敵の処理 [enemy.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/08/05
//
////////////////////////////////////////////////////////////////////////////////
#include "enemy.h"
#include "score.h"
#include "game.h"
#include "explosion.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define MAX_TYPE (3)	//タイプの最大数
#define MAX_LIFE (1)	//敵のライフの最大値

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9 g_pTextureEnemy[MAX_TYPE] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;		//頂点バッファへの設定
ENEMY g_aEnemy[MAX_ENEMY];							//敵の情報
int g_nEnemyNumber[MAX_ENEMY];						//敵の数字情報

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

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy.png", &g_pTextureEnemy[ENEMYTYPE_NORMAL]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy2.png", &g_pTextureEnemy[ENEMYTYPE_BIG]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy002.png", &g_pTextureEnemy[ENEMYTYPE_SHOT]);

	//変数の初期化
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{	
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = NULL;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].nCounterState = NULL;
		g_aEnemy[nCntEnemy].nLife = MAX_LIFE;
		g_aEnemy[nCntEnemy].bSwitch = false;
		g_aEnemy[nCntEnemy].bDisp = false;
	}

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
	for (int nCntEnemy = 0; nCntEnemy < MAX_TYPE; nCntEnemy++)
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
	VERTEX_2D *pVtx;

	pEnemy = &g_aEnemy[0];

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{	//敵が使用されているとき

			//位置の更新
			pEnemy->pos.x += pEnemy->move.x;

			switch (pEnemy->nType)
			{
			case ENEMYTYPE_BIG:
				//でかい敵の頂点情報の設定
				SetVertexBigEnemy(nCntEnemy);
				break;

			default:
				//敵の頂点座標の設定
				SetVertexEnemy(nCntEnemy);
				break;
			}

			//進む方向
			if (pEnemy->bSwitch == false)
			{	
				if (pEnemy->pos.x < (SCREEN_WIDTH / 2))
				{	//敵が画面中央より左側にいるとき
					if (pEnemy->nType == ENEMYTYPE_SHOT)
					{	//速い敵
						pEnemy->move.x = SHOTENEMY_SPEED;
					}
					else
					{	//通常敵
						pEnemy->move.x = ENEMY_SPEED;
					}
				}
				else if (pEnemy->pos.x >(SCREEN_WIDTH / 2))
				{	//敵が中央よりも右側にいるとき
					if (pEnemy->nType == ENEMYTYPE_SHOT)
					{	//速い敵
						pEnemy->move.x = -SHOTENEMY_SPEED;
					}
					else
					{	//通常敵
						pEnemy->move.x = -ENEMY_SPEED;
					}
				}

				if (pEnemy->pos.x > 0 + ENEMY_SIZE && pEnemy->pos.x < SCREEN_WIDTH - ENEMY_SIZE)
				{	//画面内に入ったら次に画面外に出た時に消えるようにする
					pEnemy->bSwitch = true;
				}
				pEnemy->bDisp = true;
			}

			if (pEnemy->bSwitch == true)
			{
				if (pEnemy->pos.x < 0 - ENEMY_SIZE || pEnemy->pos.x > SCREEN_WIDTH + ENEMY_SIZE)
				{	//画面外に出たら消去
					pEnemy->bUse = false;
					pEnemy->bDisp = false;
					pEnemy->bSwitch = false;
				}
			}

			switch (g_aEnemy[g_nEnemyNumber[nCntEnemy]].state)
			{
			case ENEMYSTATE_DAMAGE:	//ダメージを受けた時
				g_aEnemy[g_nEnemyNumber[nCntEnemy]].nCounterState--;

				if (g_aEnemy[g_nEnemyNumber[nCntEnemy]].nCounterState <= 0)
				{	//状態カウンタが0以下になった時に元に戻す
					g_aEnemy[g_nEnemyNumber[nCntEnemy]].state = ENEMYSTATE_NORMAL;

					//頂点バッファをロックし、頂点情報へのポインタを取得
					g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

					pVtx += g_nEnemyNumber[nCntEnemy] * 4;

					//頂点カラーの設定
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

					//頂点バッファをアンロックする
					g_pVtxBuffEnemy->Unlock();
				}
				break;

			default:
				break;
			}
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
		if (g_aEnemy[nCntEnemy].bDisp == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEnemy[g_aEnemy[nCntEnemy].nType]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//敵のセット処理
////////////////////////////////////////////////////////////////////////////////
void SetEnemy(void)
{
	//変数宣言
	ENEMY *pEnemy;
	int nPos;
	pEnemy = &g_aEnemy[0];

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == false)
		{	//敵が使用されていないとき
			nPos = (int)GetRandom(0, 1);

			switch (nPos)
			{
			case 0:
				pEnemy->pos.x = SCREEN_WIDTH + BIGENEMY_SIZE;
				break;
			case 1:
				pEnemy->pos.x = SCREEN_LEFT - BIGENEMY_SIZE;
				break;
			}
			pEnemy->pos.y = GetRandom(100.0f + BIGENEMY_SIZE, SCREEN_HEIGHT - BIGENEMY_SIZE);

			pEnemy->nType = (int)GetRandom(0, 2);

			//敵を使用する
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
	pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x - ENEMY_SIZE, g_aEnemy[nIdx].pos.y + ENEMY_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x - ENEMY_SIZE, g_aEnemy[nIdx].pos.y - ENEMY_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x + ENEMY_SIZE, g_aEnemy[nIdx].pos.y + ENEMY_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x + ENEMY_SIZE, g_aEnemy[nIdx].pos.y - ENEMY_SIZE, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//大きい敵の頂点座標の設定
////////////////////////////////////////////////////////////////////////////////
void SetVertexBigEnemy(int nIdx)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x - BIGENEMY_SIZE, g_aEnemy[nIdx].pos.y + BIGENEMY_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x - BIGENEMY_SIZE, g_aEnemy[nIdx].pos.y - BIGENEMY_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x + BIGENEMY_SIZE, g_aEnemy[nIdx].pos.y + BIGENEMY_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x + BIGENEMY_SIZE, g_aEnemy[nIdx].pos.y - BIGENEMY_SIZE, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//敵のステート処理
////////////////////////////////////////////////////////////////////////////////
bool HitEnemy(int nIdx, int nDamage)
{
	//ライフをダメージ分減少
	g_aEnemy[nIdx].nLife -= nDamage;

	if (g_aEnemy[nIdx].nLife <= 0)
	{	//ライフが0以下になった時
		if(g_aEnemy[nIdx].nType == ENEMYTYPE_BIG)
		{
			for (int nCntEnemy = 0; nCntEnemy < 2; nCntEnemy++)
			{	//大きいタイプの敵を倒したときは敵を二体セット
				SetEnemy();
			}
		}

		//敵を破棄
		g_aEnemy[nIdx].bUse = false;
		g_aEnemy[nIdx].bDisp = false;
		g_aEnemy[nIdx].bSwitch = false;

		//爆発再生
		SetExplosion(g_aEnemy[nIdx].pos);

		//タイプごとにスコアを加算
		switch (g_aEnemy[nIdx].nType)
		{
		case ENEMYTYPE_NORMAL:
			AddScore(1000);
		case ENEMYTYPE_SHOT:
			AddScore(3000);
		case ENEMYTYPE_BIG:
			AddScore(5000);
		}
		
		return true;
	}
	else
	{
		g_nEnemyNumber[nIdx] = nIdx;
		g_aEnemy[nIdx].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nIdx].nCounterState = 6;

		//変数宣言
		VERTEX_2D *pVtx;

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += nIdx * 4;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 150);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 150);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 150);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 150);

		//頂点バッファをアンロックする
		g_pVtxBuffEnemy->Unlock();

		return false;
	}
}
