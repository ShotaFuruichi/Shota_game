////////////////////////////////////////////////////////////////////////////////
//
//Contents	: アイテムの処理 [item.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/10/16
//
////////////////////////////////////////////////////////////////////////////////
#include "item.h"

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;	//頂点情報
LPDIRECT3DTEXTURE9 g_pTextureItem = NULL;		//テクスチャ情報
ITEM g_Item;

////////////////////////////////////////////////////////////////////////////////
//背景の初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT InitItem(void)
{
	//変数宣言
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//変数の初期化
	g_Item.pos = D3DXVECTOR3(18000.0f, 0.0f, 0.0f);
	g_Item.fWidth = 25.0f;
	g_Item.fHeight = 25.0f;
	g_Item.bUse = false;
	g_pVtxBuffItem = NULL;
	g_pTextureItem = NULL;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\right.png", &g_pTextureItem);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffItem, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	SetVertexItem();

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

	//頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//背景の終了処理
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
	if (g_pTextureItem != NULL)
	{
		g_pTextureItem->Release();	//開放
		g_pTextureItem = NULL;		//初期化
	}
}

////////////////////////////////////////////////////////////////////////////////
//背景の更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateItem(void)
{
	if (g_Item.bUse == true)
	{
		SetVertexItem();
	}
}

////////////////////////////////////////////////////////////////////////////////
//背景の描画処理
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

	if (g_Item.bUse == true)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureItem);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

////////////////////////////////////////////////////////////////////////////////
//セット
////////////////////////////////////////////////////////////////////////////////
void SetItem(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//変数宣言
	ITEM *pItem;
	pItem = &g_Item;

	//for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
	//{
		if (pItem->bUse == false)
		{	//敵が使用されていないとき

			//アイテムの基本情報
			pItem->pos = pos;
			pItem->fWidth = fWidth;
			pItem->fHeight = fHeight;

			//アイテムを使用する
			pItem->bUse = true;

		}
	/*}*/
}

////////////////////////////////////////////////////////////////////////////////
//頂点座標の設定
////////////////////////////////////////////////////////////////////////////////
void SetVertexItem(void)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_Item.pos.x - g_Item.fWidth, g_Item.pos.y + g_Item.fHeight, 0);
	pVtx[1].pos = D3DXVECTOR3(g_Item.pos.x - g_Item.fWidth, g_Item.pos.y - g_Item.fHeight, 0);
	pVtx[2].pos = D3DXVECTOR3(g_Item.pos.x + g_Item.fWidth, g_Item.pos.y + g_Item.fHeight, 0);
	pVtx[3].pos = D3DXVECTOR3(g_Item.pos.x + g_Item.fWidth, g_Item.pos.y - g_Item.fHeight, 0);

	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

ITEM *GetItem(void)
{
	return &g_Item;
}