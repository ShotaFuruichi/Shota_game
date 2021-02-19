////////////////////////////////////////////////////////////////////////////////
//
//Contents	: ビルボードの処理 [Billboard.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/11/20
//
////////////////////////////////////////////////////////////////////////////////
#include "Billboard.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define MAX_BILLBOARD (5)

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;	//頂点情報
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;		//テクスチャ情報
BILLBOARD g_aBillboard[MAX_BILLBOARD];

////////////////////////////////////////////////////////////////////////////////
//初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT InitBillboard(void)
{
	//変数宣言
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\hoshi.png", &g_pTextureBillboard);

	g_aBillboard[0].pos = D3DXVECTOR3(0.0f, 20.0f, 50.0f);
	g_aBillboard[1].pos = D3DXVECTOR3(80.0f, 20.0f, 50.0f);
	g_aBillboard[2].pos = D3DXVECTOR3(-80.0f, 20.0f, 50.0f);
	g_aBillboard[3].pos = D3DXVECTOR3(160.0f, 20.0f, 50.0f);
	g_aBillboard[4].pos = D3DXVECTOR3(-160.0f, 20.0f, 50.0f);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffBillboard, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBoard = 0; nCntBoard < MAX_BILLBOARD; nCntBoard++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-100, -30, 0);
		pVtx[1].pos = D3DXVECTOR3(-100, 30, 0);
		pVtx[2].pos = D3DXVECTOR3(100, -30, 0);
		pVtx[3].pos = D3DXVECTOR3(100, 30, 0);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBillboard->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitBillboard(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();	//開放
		g_pVtxBuffBillboard = NULL;		//初期化
	}

	//テクスチャの開放
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();	//開放
		g_pTextureBillboard = NULL;		//初期化
	}
}

////////////////////////////////////////////////////////////////////////////////
//更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateBillboard(void)
{

}

////////////////////////////////////////////////////////////////////////////////
//描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawBillboard(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxTrans;

	//デバイスの取得
	pDevice = GetDevice();

	//αテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 120);

	//ライティングの無効
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntBoard = 0; nCntBoard < MAX_BILLBOARD; nCntBoard++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aBillboard[nCntBoard].mtxworld);

		//ビューマトリックスを取得
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);
		
		#if 0
		//ポリゴンをカメラに対して正面に向ける
		//逆行列を求める
		D3DXMatrixInverse(&g_aBillboard[nCntBoard].mtxworld, NULL, &mtxView);

		//平行移動の部分は無視する
		g_aBillboard[nCntBoard].mtxworld._41 = 0.0f;
		g_aBillboard[nCntBoard].mtxworld._42 = 0.0f;
		g_aBillboard[nCntBoard].mtxworld._43 = 0.0f;
		#endif

		#if 1
		g_aBillboard[nCntBoard].mtxworld._11 = mtxView._11;
		g_aBillboard[nCntBoard].mtxworld._12 = mtxView._21;
		g_aBillboard[nCntBoard].mtxworld._13 = mtxView._31;
		g_aBillboard[nCntBoard].mtxworld._21 = mtxView._12;
		g_aBillboard[nCntBoard].mtxworld._22 = mtxView._22;
		g_aBillboard[nCntBoard].mtxworld._23 = mtxView._32;
		g_aBillboard[nCntBoard].mtxworld._31 = mtxView._13;
		g_aBillboard[nCntBoard].mtxworld._32 = mtxView._23;
		g_aBillboard[nCntBoard].mtxworld._33 = mtxView._33;
		#endif

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aBillboard[nCntBoard].pos.x, g_aBillboard[nCntBoard].pos.y, g_aBillboard[nCntBoard].pos.z);
		D3DXMatrixMultiply(&g_aBillboard[nCntBoard].mtxworld, &g_aBillboard[nCntBoard].mtxworld, &mtxTrans);

		//ワールドマトリックス
		pDevice->SetTransform(D3DTS_WORLD, &g_aBillboard[nCntBoard].mtxworld);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBillboard);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBoard * 4, 2);
	}

	//αテストを無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	//ライティングを有効
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void SetBillboard(void)
{

}