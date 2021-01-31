////////////////////////////////////////////////////////////////////////////////
//
//Contents	: 弾の処理 [bullet.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/10/26
//
////////////////////////////////////////////////////////////////////////////////
#include "bullet.h"
#include "enemy.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define BULLET_SIZEX (50.0f)	//弾の横の大きさ
#define BULLET_SIZEY (30.0f)	//弾の縦の大きさ
#define BULLET_DAMAGE (1)		//弾のダメージ量

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		//頂点バッファへの設定
BULLET g_aBullet[MAX_BULLET];							//弾の情報
int g_nCntAnim;											//アニメーション

////////////////////////////////////////////////////////////////////////////////
//弾の初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT InitBullet(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//変数の初期化
	g_pTextureBullet = NULL;
	g_pVtxBuffBullet = NULL;

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{	
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0, 0, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].bUse = false;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\冷気01.png", &g_pTextureBullet);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBullet, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点座標の設定
		SetVertexBullet(nCntBullet);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f,1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f,0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f,1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f,0.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//弾の終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitBullet(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();	//開放
		g_pVtxBuffBullet = NULL;		//初期化
	}

	//テクスチャの開放
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();	//開放
		g_pTextureBullet = NULL;		//初期化
	}
}

////////////////////////////////////////////////////////////////////////////////
//弾の更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateBullet(void)
{
	//変数宣言
	BULLET *pBullet;
	ENEMY *pEnemy;

	//敵の情報を取得
	pBullet = &g_aBullet[0];

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == true)
		{	//弾が使用されているとき
#if 0
			g_nCntAnim++;
			if (g_nCntAnim % 50 == 0)
			{
				//頂点バッファをロックし、頂点情報へのポインタを取得
				g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(g_nCntAnim * 0.25f, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(g_nCntAnim * 0.25f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2((g_nCntAnim + 1)* 0.25f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2((g_nCntAnim + 1)* 0.25f, 0.0f);

				//頂点バッファをアンロックする
				g_pVtxBuffBullet->Unlock();
			}
#endif

			// 位置更新
			pBullet->pos.x += pBullet->move.x;
			pBullet->pos.y += pBullet->move.y;

			//寿命減少
			pBullet->nLife--;
			if (pBullet->nLife == 0)
			{
				pBullet->bUse = false;
			}

			//頂点座標の設定
			SetVertexBullet(nCntBullet);

			pEnemy = GetEnemy();

			//敵との当たり判定
			for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
			{
				//画面外チェック
				if (pBullet->pos.y < 0 || pBullet->pos.y > 1080 || pBullet->pos.x < 0 || pBullet->pos.x > 1920)
				{
					pBullet->bUse = false;
				}

				if (pEnemy->bUse == true)
				{	//敵を使用している場合
					if (pBullet->pos.y < pEnemy->pos.y && pBullet->pos.y >(pEnemy->pos.y - ENEMY_SIZEY) &&
						pBullet->pos.x > (pEnemy->pos.x - ENEMY_SIZEX) && pBullet->pos.x < (pEnemy->pos.x + ENEMY_SIZEX))
					{	//当たり判定

						//敵の被弾処理
						HitEnemy(nCntEnemy, BULLET_DAMAGE);
					}
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//弾の描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawBullet(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{	//弾が使用されている場合
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBullet);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//弾のセット処理
////////////////////////////////////////////////////////////////////////////////
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife)
{
	//変数宣言
	BULLET *pBullet;

	pBullet = &g_aBullet[0];

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == false)
		{	//弾が使用されていないとき

			//位置の設定
			pBullet->pos = pos;

			//頂点座標の設定
			SetVertexBullet(nCntBullet);

			//移動量の設定
			pBullet->move = move;

			//寿命の設定
			pBullet->nLife = nLife;
			
			//弾を使用する
			pBullet->bUse = true;
			
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//弾の頂点座標の設定
////////////////////////////////////////////////////////////////////////////////
void SetVertexBullet(int nIdx)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	//pVtxのポインタ調節
	pVtx += nIdx * 4;

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_SIZEX, g_aBullet[nIdx].pos.y + BULLET_SIZEY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_SIZEX, g_aBullet[nIdx].pos.y - BULLET_SIZEY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_SIZEX, g_aBullet[nIdx].pos.y + BULLET_SIZEY, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_SIZEX, g_aBullet[nIdx].pos.y - BULLET_SIZEY, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}