//-----------------------------------------------------------------
//
// 壁 (wall.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "wall.h"
#include "input.h"
#include "gamepad.h"
#include "texture.h"

//-----------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------
#define MAX_WALL		(16)							// メッシュフィールド最大数
#define MAX_WALL_VTX	(200)							// メッシュフィールドの頂点最大数
#define MAX_INDEX		(200)							// インデックス最大数

#define WIDTH_NUM		(g_MeshOrbit[nCntWall].nCntWallX)	// 列
#define HEIGHT_NUM		(g_MeshOrbit[nCntWall].nCntWallY)	// 行
#define WIDTH			(g_MeshOrbit[nCntWall].fWidth)		// 幅
#define HEIGHT			(g_MeshOrbit[nCntWall].fHieght)		// 奥行
#define WIDTH_VEC		(WIDTH_NUM + 1)					// 列の頂点数
#define HEIGHT_VEC		(HEIGHT_NUM + 1)				// 行の頂点数

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
Wall g_MeshOrbit[MAX_WALL];												// 壁の情報

//-----------------------------------------------------------------
// 壁の初期化処理
//-----------------------------------------------------------------
HRESULT InitWall(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し、初期化
	pDevice = GetDevice();

	// 変数の初期化
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_MeshOrbit[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshOrbit[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshOrbit[nCntWall].moveRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshOrbit[nCntWall].nCntWallX = 0;
		g_MeshOrbit[nCntWall].nCntWallY = 0;
		g_MeshOrbit[nCntWall].nCntVecX = 0;
		g_MeshOrbit[nCntWall].nCntVecY = 0;
		g_MeshOrbit[nCntWall].fWidth = 0.0f;
		g_MeshOrbit[nCntWall].fHieght = 0.0f;
		g_MeshOrbit[nCntWall].fsizeWidth = 1.0f;
		g_MeshOrbit[nCntWall].fsizeHieght = 0.0f;
		g_MeshOrbit[nCntWall].nVetex = 0;
		g_MeshOrbit[nCntWall].nIndex = 0;
		g_MeshOrbit[nCntWall].nPrimitive = 0;
		g_MeshOrbit[nCntWall].nIdxtexture = 0;
		g_MeshOrbit[nCntWall].bUse = false;

		// 頂点バッファの生成
		if (FAILED(pDevice->CreateVertexBuffer(
			sizeof(VERTEX_3D) * MAX_WALL_VTX,	// 確保するバッファサイズ
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,									// 頂点フォーマット
			D3DPOOL_MANAGED,
			&g_MeshOrbit[nCntWall].pVtxBuffWall,
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
			&g_MeshOrbit[nCntWall].pIdxBuffWall,
			NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//-----------------------------------------------------------------
// 壁の終了処理
//-----------------------------------------------------------------
void UninitWall(void)
{
	// 変数の初期化
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		// インデックスの開放
		if (g_MeshOrbit[nCntWall].pIdxBuffWall != NULL)
		{
			g_MeshOrbit[nCntWall].pIdxBuffWall->Release();
			g_MeshOrbit[nCntWall].pIdxBuffWall = NULL;
		}

		// 頂点バッファの開放
		if (g_MeshOrbit[nCntWall].pVtxBuffWall != NULL)
		{
			g_MeshOrbit[nCntWall].pVtxBuffWall->Release();
			g_MeshOrbit[nCntWall].pVtxBuffWall = NULL;
		}
	}
}

//-----------------------------------------------------------------
// 壁の更新処理
//-----------------------------------------------------------------
void UpdateWall(void)
{
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_MeshOrbit[nCntWall].bUse == true)
		{
			// 回転量の更新
			g_MeshOrbit[nCntWall].rot += g_MeshOrbit[nCntWall].moveRot;
		}
	}
}

//-----------------------------------------------------------------
// 壁の描画処理
//-----------------------------------------------------------------
void DrawWall(void)
{
	// 変数宣言
	Wall *pWall = &g_MeshOrbit[0];
	Texture *pTexture = GetTexture();
	LPDIRECT3DDEVICE9 pDevice;		// デバイスへのポインタ
	D3DXMATRIX mtxScaling,mtxRot, mtxTrans;	// 計算用マトリックス

	// 変数の受け渡し
	pDevice = GetDevice();

	// アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 120);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, pWall++)
	{
		if (pWall->bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&pWall->mtxWorld);

			// 向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pWall->rot.y, pWall->rot.x, pWall->rot.z);
			D3DXMatrixMultiply(&pWall->mtxWorld, &pWall->mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, pWall->pos.x, pWall->pos.y, pWall->pos.z);
			D3DXMatrixMultiply(&pWall->mtxWorld, &pWall->mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &pWall->mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, pWall->pVtxBuffWall, 0, sizeof(VERTEX_3D));

			// インデックスバッファをデータストリームに設定
			pDevice->SetIndices(pWall->pIdxBuffWall);

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// ポリゴンの描画
			pDevice->SetTexture(0, pTexture->TextureInfo[pWall->nIdxtexture].pTexture);
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, pWall->nVetex, 0, pWall->nPrimitive);
		}
	}

	// アルファテストを元の設定に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
}

//-----------------------------------------------------------------
// 壁の配置
//-----------------------------------------------------------------
void SetWall(int type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 moveRot,int blockX, int blockY, float sizeX, float sizeY)
{
	// 構造体のポインタ変数
	Wall *pWall = &g_MeshOrbit[0];

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, pWall++)
	{
		if (pWall->bUse == false)
		{
			// 位置の設定
			// テクスチャタイプの設定
			pWall->nIdxtexture = type;

			// 位置の設定
			pWall->pos = pos;

			// 角度の設定
			pWall->rot = rot;

			// 回転量の設定
			pWall->moveRot = moveRot;

			// 置くブロック数(X)の設定
			pWall->nCntWallX = blockX;

			// 置くブロック数(Z)の設定
			pWall->nCntWallY = blockY;

			// サイズ(X)の設定
			pWall->fWidth = sizeX;

			// サイズ(Z)の設定
			pWall->fHieght = sizeY;

			// 使用状態をtureにする
			pWall->bUse = true;

			// サイズの確定
			pWall->fsizeWidth = pWall->nCntWallX * pWall->fWidth;
			pWall->fsizeHieght = pWall->nCntWallY * pWall->fHieght;

			// 頂点数とインデックス数、プリミティブ数の確定
			pWall->nVetex = ((pWall->nCntWallX + 1) * (pWall->nCntWallY + 1));
			pWall->nPrimitive = (pWall->nCntWallX * pWall->nCntWallY * 2) + (4 * (pWall->nCntWallY - 1));

			// 構造体のポインタ変数
			VERTEX_3D *pVtx;

			// インデックス情報へのポインタ
			WORD *pIdx;

			// 頂点バッファをロックし、頂点情報へのポインタを取得
			pWall->pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

			// インデックスバッファをロックし、番号データへのポインタを取得
			pWall->pIdxBuffWall->Lock(0, 0, (void**)&pIdx, 0);

			for (int nCntZ = 0; nCntZ < HEIGHT_VEC; nCntZ++)
			{
				for (int nCntX = 0; nCntX < WIDTH_VEC; nCntX++)
				{
					// 頂点座標の設定
					pVtx[0].pos = D3DXVECTOR3((-pWall->fsizeWidth / 2.0f + (float)nCntX * pWall->fWidth) + pWall->pos.x,
						(pWall->fsizeHieght /2.0f - (float)nCntZ * pWall->fHieght) + pWall->pos.y,
						0.0f);

					// 法線ベクトルの設定
					pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

					// 頂点カラーの設定
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					// テクスチャ座標
					pVtx[0].tex = D3DXVECTOR2(1.0f * nCntX, 1.0f * nCntZ);

					// 次の情報
					pVtx++;
				}
			}

			for (int nCntZ = 0; nCntZ < HEIGHT_NUM; nCntZ++)
			{
				for (int nCntX = 0; nCntX < WIDTH_VEC + 1; nCntX++)
				{
					if (nCntX != 0 && nCntX == WIDTH_VEC && nCntZ != HEIGHT_NUM - 1)
					{// 右端から折り返す時
						pIdx[0] = pIdx[-1];
						pIdx[1] = pIdx[-2] + 1;
					}
					else if (nCntZ == HEIGHT_NUM - 1 && nCntX == WIDTH_VEC)
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
			pWall->pVtxBuffWall->Unlock();

			// インデックスバッファをアンロックする
			pWall->pIdxBuffWall->Unlock();

			break;
		}
	}
}

//-----------------------------------------------------------------
// 壁との当たり判定
//-----------------------------------------------------------------
void CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pvtxMin, D3DXVECTOR3 *pvtxMax)
{
	
}

//-----------------------------------------------------------------
// 壁情報の取得
//-----------------------------------------------------------------
Wall *GetWall(void)
{
	return &g_MeshOrbit[0];
}