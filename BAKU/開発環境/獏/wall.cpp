////////////////////////////////////////////////////////////////////////////////
//
//Contents	: 壁の処理 [wall.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/11/17
//
////////////////////////////////////////////////////////////////////////////////
#include "wall.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define MAX_WALL (4)

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall= NULL;	//頂点情報
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;		//テクスチャ情報
WALL g_aWall[MAX_WALL];
VERTEX_3D *pVtx;

////////////////////////////////////////////////////////////////////////////////
//壁の初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT InitWall(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\", &g_pTextureWall);

	g_aWall[0].pos = D3DXVECTOR3(0.0f, 100.0f, 500.0f);
	g_aWall[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aWall[1].pos = D3DXVECTOR3(0.0f, 100.0f, -500.0f);
	g_aWall[1].rot = D3DXVECTOR3(0.0f, D3DXToRadian(180), 0.0f);
	g_aWall[2].pos = D3DXVECTOR3(500.0f, 100.0f, 0.0f);
	g_aWall[2].rot = D3DXVECTOR3(0.0f, D3DXToRadian(90), 0.0f);
	g_aWall[3].pos = D3DXVECTOR3(-500.0f, 100.0f, 0.0f);
	g_aWall[3].rot = D3DXVECTOR3(0.0f, -D3DXToRadian(90), 0.0f);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffWall, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);
	
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-500, -100, 0);
		pVtx[1].pos = D3DXVECTOR3(-500, 100, 0);
		pVtx[2].pos = D3DXVECTOR3(500, -100, 0);
		pVtx[3].pos = D3DXVECTOR3(500, 100, 0);

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
	g_pVtxBuffWall->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//壁の終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitWall(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();	//開放
		g_pVtxBuffWall = NULL;		//初期化
	}

	//テクスチャの開放
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();	//開放
		g_pTextureWall = NULL;		//初期化
	}
}

////////////////////////////////////////////////////////////////////////////////
//壁の更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateWall(void)
{

}

////////////////////////////////////////////////////////////////////////////////
//壁の描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawWall(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aWall[nCntWall].mtxworld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
		D3DXMatrixMultiply(&g_aWall[nCntWall].mtxworld, &g_aWall[nCntWall].mtxworld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
		D3DXMatrixMultiply(&g_aWall[nCntWall].mtxworld, &g_aWall[nCntWall].mtxworld, &mtxTrans);

		//ワールドマトリックス
		pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxworld);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, NULL);

		////ポリゴンの描画
		//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWall * 4, 2);
	}
}

WALL *GetWall(void)
{
	return &g_aWall[0];
}

VERTEX_3D *GetVtx(void)
{
	return pVtx;
}