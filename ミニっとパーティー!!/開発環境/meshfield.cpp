//-----------------------------------------------------------------
//
// メッシュフィールド (meshfield.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "meshfield.h"
#include "input.h"
#include "gamepad.h"
#include "shadow.h"
#include "texture.h"

//-----------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------
#define MAX_MESHFIELD		(16)										// メッシュフィールド最大数
#define MAX_MESHFIELD_VTX	(200)										// メッシュフィールドの頂点最大数
#define MAX_INDEX			(200)										// インデックス最大数

#define WIDTH_NUM			(g_MeshField[nCntMeshField].nCntMeshFieldX)	// 列
#define DEPTH_NUM			(g_MeshField[nCntMeshField].nCntMeshFieldZ)	// 行
#define WIDTH				(g_MeshField[nCntMeshField].fWidth)			// 幅
#define DEPTH				(g_MeshField[nCntMeshField].fDepth)			// 奥行
#define WIDTH_VEC			(WIDTH_NUM + 1)								// 列の頂点数
#define DEPTH_VEC			(DEPTH_NUM + 1)								// 行の頂点数

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
MeshField g_MeshField[MAX_MESHFIELD];							// メッシュフィールド情報

//-----------------------------------------------------------------
// メッシュフィールドの初期化処理
//-----------------------------------------------------------------
HRESULT InitMeshField(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し、初期化
	pDevice = GetDevice();

	// 変数の初期化
	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		g_MeshField[nCntMeshField].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshField[nCntMeshField].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshField[nCntMeshField].nCntMeshFieldX = 0;
		g_MeshField[nCntMeshField].nCntMeshFieldZ = 0;
		g_MeshField[nCntMeshField].nCntVecX = 0;
		g_MeshField[nCntMeshField].nCntVecZ = 0;
		g_MeshField[nCntMeshField].fWidth = 0.0f;
		g_MeshField[nCntMeshField].fDepth = 0.0f;
		g_MeshField[nCntMeshField].fsizeWidth = 0.0f;
		g_MeshField[nCntMeshField].fsizeDepth = 0.0f;
		g_MeshField[nCntMeshField].nIndex = 0;
		g_MeshField[nCntMeshField].nVetex = 0;
		g_MeshField[nCntMeshField].nPrimitive = 0;
		g_MeshField[nCntMeshField].nIdxtexture = -1;
		g_MeshField[nCntMeshField].bUse = false;

		// 頂点バッファの生成
		if (FAILED(pDevice->CreateVertexBuffer(
			sizeof(VERTEX_3D) * MAX_MESHFIELD_VTX,	// 確保するバッファサイズ
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,									// 頂点フォーマット
			D3DPOOL_MANAGED,
			&g_MeshField[nCntMeshField].pVtxBuffMeshField,
			NULL)))
		{
			return E_FAIL;
		}

		// インデックスバッファの生成
		if (FAILED(pDevice->CreateIndexBuffer(
			sizeof(WORD) * MAX_INDEX,	// 確保するバッファサイズ
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,						// フォーマット
			D3DPOOL_MANAGED,
			&g_MeshField[nCntMeshField].pIdxBuffMeshField,
			NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//-----------------------------------------------------------------
// メッシュフィールドの終了処理
//-----------------------------------------------------------------
void UninitMeshField(void)
{
	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		// インデックスの開放
		if (g_MeshField[nCntMeshField].pIdxBuffMeshField != NULL)
		{
			g_MeshField[nCntMeshField].pIdxBuffMeshField->Release();
			g_MeshField[nCntMeshField].pIdxBuffMeshField = NULL;
		}

		// 頂点バッファの開放
		if (g_MeshField[nCntMeshField].pVtxBuffMeshField != NULL)
		{
			g_MeshField[nCntMeshField].pVtxBuffMeshField->Release();
			g_MeshField[nCntMeshField].pVtxBuffMeshField = NULL;
		}
	}
}

//-----------------------------------------------------------------
// メッシュフィールドの更新処理
//-----------------------------------------------------------------
void UpdateMeshField(void)
{

}

//-----------------------------------------------------------------
// メッシュフィールドの描画処理
//-----------------------------------------------------------------
void DrawMeshField(void)
{
	// 変数宣言
	Texture *pTexture = GetTexture();
	LPDIRECT3DDEVICE9 pDevice;		// デバイスへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	// 変数の受け渡し
	pDevice = GetDevice();

	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		if (g_MeshField[nCntMeshField].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_MeshField[nCntMeshField].mtxWorld);

			// 向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshField[nCntMeshField].rot.y, g_MeshField[nCntMeshField].rot.x, g_MeshField[nCntMeshField].rot.z);
			D3DXMatrixMultiply(&g_MeshField[nCntMeshField].mtxWorld, &g_MeshField[nCntMeshField].mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_MeshField[nCntMeshField].pos.x, g_MeshField[nCntMeshField].pos.y, g_MeshField[nCntMeshField].pos.z);
			D3DXMatrixMultiply(&g_MeshField[nCntMeshField].mtxWorld, &g_MeshField[nCntMeshField].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_MeshField[nCntMeshField].mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_MeshField[nCntMeshField].pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

			// インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_MeshField[nCntMeshField].pIdxBuffMeshField);

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// ポリゴンの描画
			pDevice->SetTexture(0, pTexture->TextureInfo[g_MeshField[nCntMeshField].nIdxtexture].pTexture);
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_MeshField[nCntMeshField].nVetex, 0, g_MeshField[nCntMeshField].nPrimitive);
		}
	}
}

//-----------------------------------------------------------------
// メッシュフィールドとの当たり判定
//-----------------------------------------------------------------
bool CollisionMeshField(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld,int nIdxShadow, D3DXVECTOR3 *PosShadow)
{
	// 変数宣言
	bool bLand = false;

	for (int nCntMeshFiled = 0; nCntMeshFiled < MAX_MESHFIELD; nCntMeshFiled++)
	{
		if (g_MeshField[nCntMeshFiled].bUse == true)
		{
			// 当たり判定
			if (pPosOld->x > g_MeshField[nCntMeshFiled].pos.x - g_MeshField[nCntMeshFiled].fsizeWidth / 2.0f && pPosOld->x < g_MeshField[nCntMeshFiled].pos.x + g_MeshField[nCntMeshFiled].fsizeWidth / 2.0f &&
				pPosOld->z > g_MeshField[nCntMeshFiled].pos.z - g_MeshField[nCntMeshFiled].fsizeDepth / 2.0f && pPosOld->z < g_MeshField[nCntMeshFiled].pos.z + g_MeshField[nCntMeshFiled].fsizeDepth / 2.0f)
			{// 範囲内にいるとき処理
				if (pPosOld->y >= g_MeshField[nCntMeshFiled].pos.y)
				{
					if (pPos->y < g_MeshField[nCntMeshFiled].pos.y)
					{
						// 下にめり込んだら座標を合わせる
						pPos->y = g_MeshField[nCntMeshFiled].pos.y;

						// 乗っていることを伝える
						bLand = true;
					}
				}
				// 壁の位置を保存
				PosShadow->y = g_MeshField[nCntMeshFiled].pos.y;
			}
		}
	}
	return bLand;
}

//-----------------------------------------------------------------
// メッシュフィールドセット
//-----------------------------------------------------------------
void SetMeshField(int type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int blockX, int blockZ, float sizeX, float sizeZ)
{
	// 構造体のポインタ変数
	MeshField *pMeshField = &g_MeshField[0];

	// メッシュフィールドセット
	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++,pMeshField++)
	{
		if (pMeshField->bUse == false)
		{
			// テクスチャタイプの設定
			pMeshField->nIdxtexture = type;

			// 位置の設定
			pMeshField->pos = pos;

			// 角度の設定
			pMeshField->rot = rot;

			// 置くブロック数(X)の設定
			pMeshField->nCntMeshFieldX = blockX;

			// 置くブロック数(Z)の設定
			pMeshField->nCntMeshFieldZ = blockZ;

			// サイズ(X)の設定
			pMeshField->fWidth = sizeX;

			// サイズ(Z)の設定
			pMeshField->fDepth = sizeZ;

			// サイズの確定
			g_MeshField[nCntMeshField].fsizeWidth = g_MeshField[nCntMeshField].nCntMeshFieldX * g_MeshField[nCntMeshField].fWidth;
			g_MeshField[nCntMeshField].fsizeDepth = g_MeshField[nCntMeshField].nCntMeshFieldZ * g_MeshField[nCntMeshField].fDepth;

			// 頂点数とインデックス数、プリミティブ数の確定
			pMeshField->nVetex = ((pMeshField->nCntMeshFieldX + 1) * (pMeshField->nCntMeshFieldZ + 1));
			pMeshField->nPrimitive = (pMeshField->nCntMeshFieldX * pMeshField->nCntMeshFieldZ * 2) + (4 * (pMeshField->nCntMeshFieldZ - 1));

			// 使用状態をtrueにする
			pMeshField->bUse = true;

			// 構造体のポインタ変数
			VERTEX_3D *pVtx;

			// インデックス情報へのポインタ
			WORD *pIdx;

			// 頂点バッファをロックし、頂点情報へのポインタを取得
			g_MeshField[nCntMeshField].pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

			// インデックスバッファをロックし、番号データへのポインタを取得
			g_MeshField[nCntMeshField].pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

			for (int nCntZ = 0; nCntZ < DEPTH_VEC; nCntZ++)
			{
				for (int nCntX = 0; nCntX < WIDTH_VEC; nCntX++)
				{
					// 頂点座標の設定
					pVtx[0].pos = D3DXVECTOR3((-g_MeshField[nCntMeshField].fsizeWidth / 2.0f + (float)nCntX * g_MeshField[nCntMeshField].fWidth) + g_MeshField[nCntMeshField].pos.x,
						0.0f,
						((g_MeshField[nCntMeshField].fsizeDepth / 2.0f) - (float)nCntZ * g_MeshField[nCntMeshField].fDepth) + g_MeshField[nCntMeshField].pos.z);

					// 法線ベクトルの設定
					pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

					// 頂点カラーの設定
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					// テクスチャ座標
					pVtx[0].tex = D3DXVECTOR2(1.0f * nCntX, 1.0f * nCntZ);

					// 次の情報
					pVtx++;
				}
			}

			for (int nCntZ = 0; nCntZ < DEPTH_NUM; nCntZ++)
			{
				for (int nCntX = 0; nCntX < WIDTH_VEC + 1; nCntX++)
				{
					if (nCntX != 0 && nCntX == WIDTH_VEC && nCntZ != DEPTH_NUM - 1)
					{// 右端から折り返す時
						pIdx[0] = pIdx[-1];
						pIdx[1] = pIdx[-2] + 1;
					}
					else if (nCntZ == DEPTH_NUM - 1 && nCntX == WIDTH_VEC)
					{// 終了時に無視する
						break;
					}
					else
					{// 通常配置
						pIdx[0] = WIDTH_VEC + (WIDTH_VEC * nCntZ) + nCntX;
						pIdx[1] = pIdx[0] - WIDTH_VEC;
					}
					// 次の情報に移動
					pIdx += 2;
				}
			}
			// 頂点バッファをアンロックする
			g_MeshField[nCntMeshField].pVtxBuffMeshField->Unlock();

			// インデックスバッファをアンロックする
			g_MeshField[nCntMeshField].pIdxBuffMeshField->Unlock();

			break;
		}
	}
}

//-----------------------------------------------------------------
// メッシュフィールド情報の取得
//-----------------------------------------------------------------
MeshField *GetMeshField(void)
{
	return &g_MeshField[0];
}