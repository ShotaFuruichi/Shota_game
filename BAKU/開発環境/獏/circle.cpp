////////////////////////////////////////////////////////////////////////////////
//
//Contents	: 魔法陣 [circle.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/02/25
//
////////////////////////////////////////////////////////////////////////////////
#include "circle.h"
#include "player.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define MAX_CIRCLE (2)				//攻撃の最大数
#define CIRCLE_SIZE (300)			//円の大きさ

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCircle = NULL;	//頂点情報
LPDIRECT3DTEXTURE9 g_pTextureCircle = NULL;			//テクスチャ情報
MAGICCIRCLE g_aCircle[MAX_CIRCLE];					//敵の攻撃

////////////////////////////////////////////////////////////////////////////////
//初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT InitCircle(void)
{
	//変数宣言
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\mahojin2.png", &g_pTextureCircle);

	for (int nCntCircle = 0; nCntCircle < MAX_CIRCLE; nCntCircle++)
	{
		g_aCircle[nCntCircle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCircle[nCntCircle].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCircle[nCntCircle].bUse = false;
	}

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_CIRCLE, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffCircle, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffCircle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntCircle = 0; nCntCircle < MAX_CIRCLE; nCntCircle++)
	{
		SetVertexCircle(nCntCircle);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

		//頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffCircle->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitCircle(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffCircle != NULL)
	{
		g_pVtxBuffCircle->Release();	//開放
		g_pVtxBuffCircle = NULL;		//初期化
	}

	//テクスチャの開放
	if (g_pTextureCircle != NULL)
	{
		g_pTextureCircle->Release();	//開放
		g_pTextureCircle = NULL;		//初期化
	}
}

////////////////////////////////////////////////////////////////////////////////
//更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateCircle(void)
{
	PLAYER *player = GetPlayer();

	for (int nCntCircle = 0; nCntCircle < MAX_CIRCLE; nCntCircle++)
	{
		if (g_aCircle[nCntCircle].bUse == true)
		{
			if (player->bChant == false)
			{
				g_aCircle[nCntCircle].bUse = false;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawCircle(void)
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

	for (int nCntCircle = 0; nCntCircle < MAX_CIRCLE; nCntCircle++)
	{
		if (g_aCircle[nCntCircle].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aCircle[nCntCircle].mtxworld);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aCircle[nCntCircle].pos.x, g_aCircle[nCntCircle].pos.y, g_aCircle[nCntCircle].pos.z);
			D3DXMatrixMultiply(&g_aCircle[nCntCircle].mtxworld, &g_aCircle[nCntCircle].mtxworld, &mtxTrans);

			//ワールドマトリックス
			pDevice->SetTransform(D3DTS_WORLD, &g_aCircle[nCntCircle].mtxworld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffCircle, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureCircle);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntCircle * 4, 2);
		}
	}

	//αテストを無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	//ライティングを有効
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

////////////////////////////////////////////////////////////////////////////////
//敵の攻撃のセット処理
////////////////////////////////////////////////////////////////////////////////
void SetCircle(int nSkill)
{
	PLAYER *player = GetPlayer();
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffCircle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntCircle = 0; nCntCircle < MAX_CIRCLE; nCntCircle++)
	{
		if (g_aCircle[nCntCircle].bUse == false)
		{
			switch (nSkill)
			{
			case SKILL_MAGICBALL:

				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(1.0f, 0.6f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.6f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.6f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.6f, 0.0f, 1.0f);
				break; 

			case SKILL_HEAL:

				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.6f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.6f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.6f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.6f, 1.0f);
				break;
			}

			g_aCircle[nCntCircle].pos = D3DXVECTOR3(player->pos.x, 1.0f, player->pos.z);
			g_aCircle[nCntCircle].bUse = true;
			break;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffCircle->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//頂点座標の設定
////////////////////////////////////////////////////////////////////////////////
void SetVertexCircle(int nIdx)
{
	//変数宣言
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffCircle->Lock(0, 0, (void**)&pVtx, 0);

	//pVtxのポインタ調節
	pVtx += nIdx * 4;

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_aCircle[nIdx].pos.x - CIRCLE_SIZE, 1, g_aCircle[nIdx].pos.z - CIRCLE_SIZE);
	pVtx[1].pos = D3DXVECTOR3(g_aCircle[nIdx].pos.x - CIRCLE_SIZE, 1, g_aCircle[nIdx].pos.z + CIRCLE_SIZE);
	pVtx[2].pos = D3DXVECTOR3(g_aCircle[nIdx].pos.x + CIRCLE_SIZE, 1, g_aCircle[nIdx].pos.z - CIRCLE_SIZE);
	pVtx[3].pos = D3DXVECTOR3(g_aCircle[nIdx].pos.x + CIRCLE_SIZE, 1, g_aCircle[nIdx].pos.z + CIRCLE_SIZE);

	//頂点バッファをアンロックする
	g_pVtxBuffCircle->Unlock();
}