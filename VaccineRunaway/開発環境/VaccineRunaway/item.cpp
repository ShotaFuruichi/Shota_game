////////////////////////////////////////////////////////////////////////////////
//
//Contents	: アイテムの処理 [item.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/09/12
//
////////////////////////////////////////////////////////////////////////////////
#include "item.h"
#include "game.h"
////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define ITEM_SPEED (2.0f)	//アイテムの移動量
#define ITEM_TOP (200)		//アイテム生成の上範囲
#define ITEM_BOTTOM (880)	//アイテム生成の下範囲

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;			//頂点情報
LPDIRECT3DTEXTURE9 g_pTextureItem[MAX_ITEMTYPE] = {};	//テクスチャ情報
ITEM g_aItem[MAX_ITEM];									//アイテムの情報

////////////////////////////////////////////////////////////////////////////////
//アイテムの初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT InitItem(void)
{
	//変数宣言
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Item002.png", &g_pTextureItem[ITEM_THROUGH]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Item000.png", &g_pTextureItem[ITEM_REFLECTIVE]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Item003.png", &g_pTextureItem[ITEM_DIFFUSION]);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].bUse = false;
		g_aItem[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].nType = NULL;
		g_aItem[nCntItem].pos = D3DXVECTOR3(30000.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].bSwitch = false;
		g_aItem[nCntItem].bDisp = false;
	}

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffItem, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		SetVertexItem(nCntItem);

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

		//テクスチャ頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}
	
	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//アイテムの終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitItem(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();	//開放
		g_pVtxBuffItem = NULL;		//初期化
	}

	//テクスチャの開放
	for (int nCntItem = 0; nCntItem < MAX_ITEMTYPE; nCntItem++)
	{
		if (g_pTextureItem[nCntItem] != NULL)
		{
			g_pTextureItem[nCntItem]->Release();	//開放
			g_pTextureItem[nCntItem] = NULL;		//初期化
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//アイテムの更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateItem(void)
{
	//変数宣言
	ITEM *pItem;
	pItem = &g_aItem[0];

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
	{
		if (pItem->bUse == true)
		{	
			//位置の更新
			pItem->pos.x += pItem->move.x;

			SetVertexItem(nCntItem);
		
			//進む方向
			if (pItem->bSwitch == false)
			{
				if (pItem->pos.x < (SCREEN_WIDTH / 2))
				{	//画面中央よりも左側にいるとき
					pItem->move.x = ITEM_SPEED;

				}
				else if (pItem->pos.x >(SCREEN_WIDTH / 2))
				{	//画面中央よりも右側にいるとき
					pItem->move.x = -ITEM_SPEED;
				}

				if (pItem->pos.x > SCREEN_LEFT + ITEM_SIZEX && pItem->pos.x < SCREEN_WIDTH - ITEM_SIZEX)
				{	//初めて画面内に入った時に画面外に出ると消えるようにする
					pItem->bSwitch = true;
				}

				pItem->bDisp = true;
			}
			if (pItem->bSwitch == true)
			{
				if (pItem->pos.x < SCREEN_LEFT - ITEM_SIZEX)
				{
					pItem->bUse = false;
					pItem->bDisp = false;
					pItem->bSwitch = false;
				}
				else if (pItem->pos.x > SCREEN_WIDTH + ITEM_SIZEX)
				{
					pItem->bUse = false;
					pItem->bDisp = false;
					pItem->bSwitch = false;
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//アイテムの描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawItem(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bDisp == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureItem[g_aItem[nCntItem].nType]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//アイテムのセット処理
////////////////////////////////////////////////////////////////////////////////
void SetItem(void)
{
	//変数宣言
	ITEM *pItem;
	int nPos;

	pItem = &g_aItem[0];

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
	{
		if (pItem->bUse == false)
		{	//敵が使用されていないとき

			pItem->nType = (int)GetRandom(1, 3);
			nPos = (int)GetRandom(0, 1);

			switch (nPos)
			{
			case 0:
				pItem->pos.x = SCREEN_WIDTH + ITEM_SIZEX;
				break;
			case 1:
				pItem->pos.x = 0.0f - ITEM_SIZEX;
				break;
			}
			pItem->pos.y = GetRandom(ITEM_TOP, ITEM_BOTTOM);

			//アイテムを使用する
			pItem->bUse = true;

			break;
		}	
	}
}

////////////////////////////////////////////////////////////////////////////////
//頂点座標の設定
////////////////////////////////////////////////////////////////////////////////
void SetVertexItem(int nIdx)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x - ITEM_SIZEX, g_aItem[nIdx].pos.y + ITEM_SIZEY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x - ITEM_SIZEX, g_aItem[nIdx].pos.y - ITEM_SIZEY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x + ITEM_SIZEX, g_aItem[nIdx].pos.y + ITEM_SIZEY, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x + ITEM_SIZEX, g_aItem[nIdx].pos.y - ITEM_SIZEY, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//アイテムのポインタ取得
////////////////////////////////////////////////////////////////////////////////
ITEM *GetItem(void)
{
	return &g_aItem[0];
}
