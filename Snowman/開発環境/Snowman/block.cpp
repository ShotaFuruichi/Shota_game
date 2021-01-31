////////////////////////////////////////////////////////////////////////////////
//
//Contents	: ブロックの処理 [block.cpp]
//Author	: Shota Furuichi
//Since		: 2020/10/13
//
////////////////////////////////////////////////////////////////////////////////
#include "block.h"
#include "player.h"
#include "input.h"
#include "enemy.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;				//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBlock[BLOCKTYPE_MAX] = {};		//テクスチャへのポインタ
BLOCK g_aBlock[MAX_BLOCK];									//ブロック
int g_aMove[MAX_BLOCK];

////////////////////////////////////////////////////////////////////////////////
//初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT InitBlock(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//変数の初期化
	g_pVtxBuffBlock = NULL;
	for (int nCntBlock = 0; nCntBlock < BLOCKTYPE_MAX; nCntBlock++)
	{
		g_pTextureBlock[nCntBlock] = NULL;
	}

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].PosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].fWidth = 0.0f;
		g_aBlock[nCntBlock].fHeight = 0.0f;
		g_aBlock[nCntBlock].bUse = false;
		g_aBlock[nCntBlock].bMove = false;
		g_aBlock[nCntBlock].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].nTexX = 0;
		g_aBlock[nCntBlock].nTexY = 0;
		g_aBlock[nCntBlock].type = BLOCKTYPE_NORMAL;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\block000.jpg", &g_pTextureBlock[BLOCKTYPE_NORMAL]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\soil.jpg", &g_pTextureBlock[BLOCKTYPE_GROUND]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\snowsoil.png", &g_pTextureBlock[BLOCKTYPE_SNOWGROUND]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\GrassSoil.jpg", &g_pTextureBlock[BLOCKTYPE_GRASSGROUND]);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBlock, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//頂点座標の設定
		SetVertexBlock(nCntBlock);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		SetColorBlock(nCntBlock);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitBlock(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();	//開放
		g_pVtxBuffBlock = NULL;		//初期化
	}

	//テクスチャの開放
	for (int nCntBlock = 0; nCntBlock < BLOCKTYPE_MAX; nCntBlock++)
	{
		if (g_pTextureBlock[nCntBlock] != NULL)
		{
			g_pTextureBlock[nCntBlock]->Release();	//開放
			g_pTextureBlock[nCntBlock] = NULL;		//初期化
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateBlock(void)
{
	BLOCK *pBlock;
	pBlock = &g_aBlock[0];

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pBlock++)
	{	
		if (pBlock->bUse == true)
		{
			//頂点座標の設定
			SetVertexBlock(nCntBlock);

			//色の設定
			SetColorBlock(nCntBlock);

			//テクスチャ座標の設定
			SetTextureBlock(nCntBlock);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawBlock(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	BLOCK *pBlock;
	pBlock = &g_aBlock[0];

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{	//弾が使用されている場合

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBlock[pBlock->type]);

			//ポリゴンの描画
			if (pBlock->bDisp == true)
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//セット
////////////////////////////////////////////////////////////////////////////////
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight, bool bDisp, bool bMove, D3DXCOLOR col, int texX, int texY, BLOCKTYPE type)
{
	//変数宣言
	BLOCK *pBlock;

	pBlock = &g_aBlock[0];

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pBlock++)
	{
		if (pBlock->bUse == false)
		{	//弾が使用されていないとき

			//位置の設定
			pBlock->pos = pos;

			//幅・高さの設定
			pBlock->fWidth = fWidth;
			pBlock->fHeight = fHeight;

			//透明・不透明の設定
			pBlock->bDisp = bDisp;

			//テクスチャの枚数
			pBlock->nTexX = texX;
			pBlock->nTexY = texY;

			//動くか
			pBlock->bMove = bMove;

			//色
			pBlock->col = col;

			//タイプ
			pBlock->type = type;

			//頂点座標の設定
			SetVertexBlock(nCntBlock);

			//弾を使用する
			pBlock->bUse = true;

			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//頂点座標の設定
////////////////////////////////////////////////////////////////////////////////
void SetVertexBlock(int nIdx)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//pVtxのポインタ調節
	pVtx += nIdx * 4;

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x, g_aBlock[nIdx].pos.y + g_aBlock[nIdx].fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x, g_aBlock[nIdx].pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x + g_aBlock[nIdx].fWidth, g_aBlock[nIdx].pos.y + g_aBlock[nIdx].fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x + g_aBlock[nIdx].fWidth, g_aBlock[nIdx].pos.y, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//色の設定
////////////////////////////////////////////////////////////////////////////////
void SetColorBlock(int nIdx)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//pVtxのポインタ調節
	pVtx += nIdx * 4;

	//色の設定
	//頂点カラーの設定
	pVtx[0].col = g_aBlock[nIdx].col;
	pVtx[1].col = g_aBlock[nIdx].col;
	pVtx[2].col = g_aBlock[nIdx].col;
	pVtx[3].col = g_aBlock[nIdx].col;

	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//テクスチャ座標の設定
////////////////////////////////////////////////////////////////////////////////
void SetTextureBlock(int nIdx)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//pVtxのポインタ調節
	pVtx += nIdx * 4;

	//色の設定
	//頂点カラーの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f * g_aBlock[nIdx].nTexY);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f * g_aBlock[nIdx].nTexX, 1.0f * g_aBlock[nIdx].nTexY);
	pVtx[3].tex = D3DXVECTOR2(1.0f * g_aBlock[nIdx].nTexX, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//ブロックの当たり判定
////////////////////////////////////////////////////////////////////////////////
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight)
{
	//変数宣言
	BLOCK *pBlock;
	PLAYER *pPlayer;
	bool bLand = false;
	pBlock = &g_aBlock[0];
	pPlayer = GetPlayer();
	
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pBlock++)
	{
		if (pBlock->bUse == true)
		{
			if (pBlock->bMove == true)
			{
				g_aMove[nCntBlock]++;
				g_aMove[nCntBlock] = g_aMove[nCntBlock] % 1000;
				if (g_aMove[nCntBlock] <= 500)
				{
					pBlock->pos.x += 1;
				}
				else if (g_aMove[nCntBlock] > 500)
				{
					pBlock->pos.x -= 1;
				}
			}
			if ((pPlayer->pos.x + DIAGONAL_X) > pBlock->pos.x && (pPlayer->pos.x - DIAGONAL_X) < (pBlock->pos.x + pBlock->fWidth))
			{
				if (pPlayer->oldpos.y <= pBlock->pos.y)
				{
					if (pPlayer->pos.y > pBlock->pos.y)
					{
						pPlayer->bJump = false;
					}
				}
			}
			if ((pPos->x + fWidth) > pBlock->pos.x && (pPos->x - fWidth) < (pBlock->pos.x + pBlock->fWidth))
			{
				if (pPosOld->y <= pBlock->pos.y)
				{
					if (pPos->y > pBlock->pos.y)
					{
						pMove->y = 0.0f;
						pPos->y = pBlock->pos.y;
					}
				}
				
				if ((pPosOld->y - fHeight) > (pBlock->pos.y + pBlock->fHeight))
				{
					if ((pPos->y - fHeight) < (pBlock->pos.y + pBlock->fHeight))
					{
						pMove->y = 0.0f;
						pPos->y = pPosOld->y;
					}
				}
			}

			for (int nCnt = 0; nCnt < fHeight; nCnt++)
			{
				if ((pPos->y - nCnt) > pBlock->pos.y && (pPos->y - nCnt) < (pBlock->pos.y + pBlock->fHeight))
				{
					if ((pPosOld->x + fWidth) <= pBlock->pos.x)
					{
						if ((pPos->x + fWidth) > pBlock->pos.x)
						{
							pPos->x = pPosOld->x;
							bLand = true;
						}
					}
					else if ((pPosOld->x - fWidth) >= (pBlock->pos.x + pBlock->fWidth))
					{
						if ((pPos->x - fWidth) < (pBlock->pos.x + pBlock->fWidth))
						{
							pPos->x = pPosOld->x;
							bLand = true;
						}
					}
				}
			}

#if 0
			pBlock->PosOld = pBlock->pos;
			if (pPlayer->bMove == true)
			{
				if (GetKeyboardPress(DIK_D) == true)
				{
					if (GetKeyboardPress(DIK_A) == true)
					{
					}
					else
					{
						pBlock->pos.x -= 2.0f;
					}
				}
				else if (GetKeyboardPress(DIK_A) == true)
				{
					if (GetKeyboardPress(DIK_D) == true)
					{
					}
					else
					{
						pBlock->pos.x += 2.0f;
					}
				}
			}
#endif
		}
	}
	return bLand;
}
