//-------------------------------------------------------------------
//
// プレイヤーマーカー (player_marker.cpp)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#include "player_marker.h"
#include "player.h"
#include "gamepad.h"
#include "chara_select_frame.h"

//-------------------------------------------------------------------
// マクロ定義
//-------------------------------------------------------------------
#define MAX_PLAYER_MARKER		(4)						// プレイヤーマーカーの最大値

#define PLAYER_MARKER_SIZE_X	(10.0f)					// プレイヤーマーカーのサイズ(幅)
#define PLAYER_MARKER_SIZE_Y	(10.0f)					// プレイヤーマーカーのサイズ(高さ)

#define PLAYER_MARKER_HEIGHT	(100.0f)					// プレイヤーマーカーの位置調整

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayerMarker = NULL;				// プレイヤーマーカーのテクスチャのポインタ
LPDIRECT3DTEXTURE9 g_pTexturePlayerMarker[MAX_PLAYER_MARKER] = {};	// プレイヤーマーカーの頂点バッファのポインタ
PLAYER_MARKER g_aPlayerMarker[MAX_PLAYER_MARKER];					// プレイヤーマーカーの情報
int g_nCntPlayerMarker;												// 配置するプレイヤーマーカーの数

//-----------------------------------------------------------------
// 敵の初期化処理
//-----------------------------------------------------------------
HRESULT InitPlayerMarker(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	Player *pPlayer;

	// 変数の受け渡し
	pDevice = GetDevice();
	pPlayer = GetPlayer();

	// セレクトモード情報の取得
	int nNumPlayer = GetFrame();

	g_nCntPlayerMarker = nNumPlayer;

	// 変数の初期化
	for (int nCnt = 0; nCnt < g_nCntPlayerMarker; nCnt++,pPlayer++)
	{
		g_aPlayerMarker[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayerMarker[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayerMarker[nCnt].fWidth = PLAYER_MARKER_SIZE_X;
		g_aPlayerMarker[nCnt].fHeight = PLAYER_MARKER_SIZE_X;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_1.png", &g_pTexturePlayerMarker[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_2.png", &g_pTexturePlayerMarker[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_3.png", &g_pTexturePlayerMarker[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_4.png", &g_pTexturePlayerMarker[3]);


	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * MAX_VERTEX * g_nCntPlayerMarker, // 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,								// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayerMarker,
		NULL)))
	{
		return E_FAIL;
	}

	// 構造体のポインタ変数
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayerMarker->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPlayerMarker = 0; nCntPlayerMarker < g_nCntPlayerMarker; nCntPlayerMarker++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aPlayerMarker[nCntPlayerMarker].pos.x - g_aPlayerMarker[nCntPlayerMarker].fWidth, g_aPlayerMarker[nCntPlayerMarker].pos.y + g_aPlayerMarker[nCntPlayerMarker].fHeight, g_aPlayerMarker[nCntPlayerMarker].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aPlayerMarker[nCntPlayerMarker].pos.x + g_aPlayerMarker[nCntPlayerMarker].fWidth, g_aPlayerMarker[nCntPlayerMarker].pos.y + g_aPlayerMarker[nCntPlayerMarker].fHeight, g_aPlayerMarker[nCntPlayerMarker].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aPlayerMarker[nCntPlayerMarker].pos.x - g_aPlayerMarker[nCntPlayerMarker].fWidth, g_aPlayerMarker[nCntPlayerMarker].pos.y - g_aPlayerMarker[nCntPlayerMarker].fHeight, g_aPlayerMarker[nCntPlayerMarker].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aPlayerMarker[nCntPlayerMarker].pos.x + g_aPlayerMarker[nCntPlayerMarker].fWidth, g_aPlayerMarker[nCntPlayerMarker].pos.y - g_aPlayerMarker[nCntPlayerMarker].fHeight, g_aPlayerMarker[nCntPlayerMarker].pos.z);

		// 法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 次の情報に更新
		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffPlayerMarker->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// 敵の終了処理
//-----------------------------------------------------------------
void UninitPlayerMarker(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffPlayerMarker != NULL)
	{
		g_pVtxBuffPlayerMarker->Release();
		g_pVtxBuffPlayerMarker = NULL;
	}

	// テクスチャの開放
	for (int nCnt = 0; nCnt < MAX_PLAYER_MARKER; nCnt++)
	{
		if (g_pTexturePlayerMarker[nCnt] != NULL)
		{
			g_pTexturePlayerMarker[nCnt]->Release();
			g_pTexturePlayerMarker[nCnt] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// 敵の更新処理
//-----------------------------------------------------------------
void UpdatePlayerMarker(void)
{
	// 構造体のポインタ変数
	PLAYER_MARKER *pPlayerMarker = &g_aPlayerMarker[0];
	Player *pPlayer = GetPlayer();

	for (int nCntPlayerMarker = 0; nCntPlayerMarker < g_nCntPlayerMarker; nCntPlayerMarker++, pPlayerMarker++,pPlayer++)
	{
		// 位置の更新
		pPlayerMarker->pos.x = pPlayer->pos.x;
		pPlayerMarker->pos.y = pPlayer->pos.y + PLAYER_MARKER_HEIGHT;
		pPlayerMarker->pos.z = pPlayer->pos.z;
	}
}

//-----------------------------------------------------------------
// 敵の描画処理
//-----------------------------------------------------------------
void DrawPlayerMarker(void)
{
	// 変数宣言
	PLAYER_MARKER *pPlayerMarker = &g_aPlayerMarker[0];
	LPDIRECT3DDEVICE9 pDevice;					// デバイスへのポインタ
	D3DXMATRIX mtxView;							// ビューマトリックス取得用
	D3DXMATRIX mtxScaling, mtxTrans;			// 計算用マトリックス

	// 変数の受け渡し
	pDevice = GetDevice();

	// ライトをオフにする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Zバッファを適用
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (int nCntPlayerMarker = 0; nCntPlayerMarker < g_nCntPlayerMarker; nCntPlayerMarker++, pPlayerMarker++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&pPlayerMarker->mtxWorld);

		// ビューマトリックスの取得
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);
#if 0
		// ポリゴンをカメラに対して正面に向ける
		D3DXMatrixInverse(&pBillboard->mtxWorld, NULL, &mtxView);
		pBillboard->mtxWorld._41 = 0.0f;
		pBillboard->mtxWorld._42 = 0.0f;
		pBillboard->mtxWorld._43 = 0.0f;
#else
		pPlayerMarker->mtxWorld._11 = mtxView._11;
		pPlayerMarker->mtxWorld._12 = mtxView._21;
		pPlayerMarker->mtxWorld._13 = mtxView._31;
		pPlayerMarker->mtxWorld._21 = mtxView._12;
		pPlayerMarker->mtxWorld._22 = mtxView._22;
		pPlayerMarker->mtxWorld._23 = mtxView._32;
		pPlayerMarker->mtxWorld._31 = mtxView._13;
		pPlayerMarker->mtxWorld._32 = mtxView._23;
		pPlayerMarker->mtxWorld._33 = mtxView._33;
#endif
		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, pPlayerMarker->pos.x, pPlayerMarker->pos.y, pPlayerMarker->pos.z);
		D3DXMatrixMultiply(&pPlayerMarker->mtxWorld, &pPlayerMarker->mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &pPlayerMarker->mtxWorld);

		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffPlayerMarker, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// ポリゴンの描画
		pDevice->SetTexture(0, g_pTexturePlayerMarker[nCntPlayerMarker]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPlayerMarker * 4, 2);
	}
	// 標準に戻す
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// ライトをオンにする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}