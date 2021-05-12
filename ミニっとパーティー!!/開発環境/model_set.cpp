//-----------------------------------------------------------------
//
// モデルセット (model_set.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#include "model_set.h"
#include "shadow.h"
#include "player.h"
#include "camera.h"
#include "light.h"
#include "wall.h"
#include "meshfield.h"

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
ModelSet g_ModelSet;												// モデル情報

//-----------------------------------------------------------------
// モデルセットの初期化処理
//-----------------------------------------------------------------
HRESULT InitModelSet(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し、初期化
	pDevice = GetDevice();

	for (int nCntModel = 0; nCntModel < g_ModelSet.nNumModel; nCntModel++)
	{
		// Xファイルの読み込み
		if (FAILED(D3DXLoadMeshFromX(&g_ModelSet.modelInfo[nCntModel].aFileName[0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_ModelSet.modelInfo[nCntModel].pBuffMatModel,
			NULL,
			&g_ModelSet.modelInfo[nCntModel].nNumMatModel,
			&g_ModelSet.modelInfo[nCntModel].pMeshModel)))
		{
			return E_FAIL;
		}

		// モデルのテクスチャ
		TexModel(nCntModel);

		// モデルの頂点
		VecModel(nCntModel);
	}

	return S_OK;
}

//-----------------------------------------------------------------
// モデルセットの終了処理
//-----------------------------------------------------------------
void UninitModelSet(void)
{
	for (int nCnt = 0; nCnt < g_ModelSet.nNumModel; nCnt++)
	{
		g_ModelSet.modelInfo[nCnt].aFileName[0] = {};

		// メッシュ情報の開放
		if (g_ModelSet.modelInfo[nCnt].pBuffMatModel != NULL)
		{
			g_ModelSet.modelInfo[nCnt].pBuffMatModel->Release();
			g_ModelSet.modelInfo[nCnt].pBuffMatModel = NULL;
		}

		// マテリアル情報の開放
		if (g_ModelSet.modelInfo[nCnt].pMeshModel != NULL)
		{
			g_ModelSet.modelInfo[nCnt].pMeshModel->Release();
			g_ModelSet.modelInfo[nCnt].pMeshModel = NULL;
		}
	}

	for (int nCntModelSet = 0; nCntModelSet < MAX_MODEL; nCntModelSet++)
	{
		if (g_ModelSet.modelSet[nCntModelSet].bUse == true)
		{
			g_ModelSet.modelSet[nCntModelSet].bUse = false;
		}
	}
	g_ModelSet.nNumModel = 0;
}

//-----------------------------------------------------------------
// モデルセットの更新処理
//-----------------------------------------------------------------
void UpdateModelSet(void)
{

}

//-----------------------------------------------------------------
// モデルセットの描画処理
//-----------------------------------------------------------------
void DrawModelSet(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;		// デバイスへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス
	D3DMATERIAL9 matDef;			// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;				// マテリアルデータへのポインタ

	// 変数の受け渡し
	pDevice = GetDevice();

	for (int nModelSet = 0; nModelSet < MAX_MODEL; nModelSet++)
	{
		if (g_ModelSet.modelSet[nModelSet].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_ModelSet.modelSet[nModelSet].mtxWorld);

			// 向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ModelSet.modelSet[nModelSet].rot.y, g_ModelSet.modelSet[nModelSet].rot.x, g_ModelSet.modelSet[nModelSet].rot.z);
			D3DXMatrixMultiply(&g_ModelSet.modelSet[nModelSet].mtxWorld, &g_ModelSet.modelSet[nModelSet].mtxWorld, &mtxRot);

			// 頂点座標の補正
			D3DXVec3TransformCoord(&g_ModelSet.modelSet[nModelSet].vtxMaxModel, &g_ModelSet.modelInfo[g_ModelSet.modelSet[nModelSet].nIdx].vtxMaxModel, &g_ModelSet.modelSet[nModelSet].mtxWorld);
			D3DXVec3TransformCoord(&g_ModelSet.modelSet[nModelSet].vtxMinModel, &g_ModelSet.modelInfo[g_ModelSet.modelSet[nModelSet].nIdx].vtxMinModel, &g_ModelSet.modelSet[nModelSet].mtxWorld);

			// 最大値最小値の補正
			VecModelSet(nModelSet);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_ModelSet.modelSet[nModelSet].pos.x, g_ModelSet.modelSet[nModelSet].pos.y, g_ModelSet.modelSet[nModelSet].pos.z);
			D3DXMatrixMultiply(&g_ModelSet.modelSet[nModelSet].mtxWorld, &g_ModelSet.modelSet[nModelSet].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_ModelSet.modelSet[nModelSet].mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_ModelSet.modelInfo[g_ModelSet.modelSet[nModelSet].nIdx].pBuffMatModel->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_ModelSet.modelInfo[g_ModelSet.modelSet[nModelSet].nIdx].nNumMatModel; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, g_ModelSet.modelInfo[g_ModelSet.modelSet[nModelSet].nIdx].apTextureModelSet[nCntMat]);

				// モデル(パーツ)の描画
				g_ModelSet.modelInfo[g_ModelSet.modelSet[nModelSet].nIdx].pMeshModel->DrawSubset(nCntMat);
			}
			// 保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//-----------------------------------------------------------------
// モデルのテクスチャ
//-----------------------------------------------------------------
void TexModel(int nModelSet)
{
	// 変数宣言
	D3DXMATERIAL *pMat;		// マテリアルデータへのポインタ
	LPDIRECT3DDEVICE9 pDevice;		// デバイスへのポインタ

	// 変数の受け渡し
	pDevice = GetDevice();

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_ModelSet.modelInfo[nModelSet].pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_ModelSet.modelInfo[nModelSet].nNumMatModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_ModelSet.modelInfo[nModelSet].apTextureModelSet[nCntMat]);
		}
	}
}

//-----------------------------------------------------------------
// モデルの頂点座標
//-----------------------------------------------------------------
void VecModel(int nModelSet)
{
	// 変数宣言
	int nNumVtx;			// 頂点数
	DWORD sizeFVF;			// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;			// 頂点バッファへのポインタ

	// 頂点数の取得
	nNumVtx = g_ModelSet.modelInfo[nModelSet].pMeshModel->GetNumVertices();

	// 頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_ModelSet.modelInfo[nModelSet].pMeshModel->GetFVF());

	// 頂点バッファのロック
	g_ModelSet.modelInfo[nModelSet].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		// 頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		// 頂点を比較してモデルの最小値最大値を抜き出す
		if (g_ModelSet.modelInfo[nModelSet].vtxMinModel.x > vtx.x)
		{// X座標の最小値
			g_ModelSet.modelInfo[nModelSet].vtxMinModel.x = vtx.x;
		}
		else if (g_ModelSet.modelInfo[nModelSet].vtxMaxModel.x < vtx.x)
		{// X座標の最大値
			g_ModelSet.modelInfo[nModelSet].vtxMaxModel.x = vtx.x;
		}

		if (g_ModelSet.modelInfo[nModelSet].vtxMinModel.y > vtx.y)
		{// Y座標の最小値
			g_ModelSet.modelInfo[nModelSet].vtxMinModel.y = vtx.y;
		}
		else if (g_ModelSet.modelInfo[nModelSet].vtxMaxModel.y < vtx.y)
		{// Y座標の最大値
			g_ModelSet.modelInfo[nModelSet].vtxMaxModel.y = vtx.y;
		}

		if (g_ModelSet.modelInfo[nModelSet].vtxMinModel.z > vtx.z)
		{// Z座標の最小値
			g_ModelSet.modelInfo[nModelSet].vtxMinModel.z = vtx.z;
		}
		else if (g_ModelSet.modelInfo[nModelSet].vtxMaxModel.z < vtx.z)
		{// Z座標の最大値
			g_ModelSet.modelInfo[nModelSet].vtxMaxModel.z = vtx.z;
		}
		// 頂点フォーマットのサイズ文ポインタを進める
		pVtxBuff += sizeFVF;
	}
	// 頂点バッファのアンロック
	g_ModelSet.modelInfo[nModelSet].pMeshModel->UnlockVertexBuffer();
}

//-----------------------------------------------------------------
// モデルの頂点座標の補正
//-----------------------------------------------------------------
void VecModelSet(int nNumModelSet)
{
	// 最大値と最小値の入れ替え
	if (g_ModelSet.modelSet[nNumModelSet].vtxMaxModel.x < g_ModelSet.modelSet[nNumModelSet].vtxMinModel.x)
	{
		// 変数宣言
		float fVecX;		// 保存用

		// 最大値と最小値を入れ替える
		fVecX = g_ModelSet.modelSet[nNumModelSet].vtxMaxModel.x;
		g_ModelSet.modelSet[nNumModelSet].vtxMaxModel.x = g_ModelSet.modelSet[nNumModelSet].vtxMinModel.x;
		g_ModelSet.modelSet[nNumModelSet].vtxMinModel.x = fVecX;
	}
	if (g_ModelSet.modelSet[nNumModelSet].vtxMaxModel.y < g_ModelSet.modelSet[nNumModelSet].vtxMinModel.y)
	{
		// 変数宣言
		float fVecY;		// 保存用

		// 最大値と最小値を入れ替える
		fVecY = g_ModelSet.modelSet[nNumModelSet].vtxMaxModel.y;
		g_ModelSet.modelSet[nNumModelSet].vtxMaxModel.y = g_ModelSet.modelSet[nNumModelSet].vtxMinModel.y;
		g_ModelSet.modelSet[nNumModelSet].vtxMinModel.y = fVecY;
	}
	if (g_ModelSet.modelSet[nNumModelSet].vtxMaxModel.z < g_ModelSet.modelSet[nNumModelSet].vtxMinModel.z)
	{
		// 変数宣言
		float fVecZ;		// 保存用

		// 最大値と最小値を入れ替え
		fVecZ = g_ModelSet.modelSet[nNumModelSet].vtxMaxModel.z;
		g_ModelSet.modelSet[nNumModelSet].vtxMaxModel.z = g_ModelSet.modelSet[nNumModelSet].vtxMinModel.z;
		g_ModelSet.modelSet[nNumModelSet].vtxMinModel.z = fVecZ;
	}
}

//-----------------------------------------------------------------
// モデルの当たり判定
//-----------------------------------------------------------------
bool CollisionModelSet(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pvtxMin, D3DXVECTOR3 *pvtxMax, int nIdxShadow, D3DXVECTOR3 *PosShadow)
{
	// 構造体のポインタ変数
	ModelSet *pModel = &g_ModelSet;

	// 変数宣言
	bool bCollisionModel = false;		// コインを獲得したかどうか

	for (int nModelSet = 0; nModelSet < MAX_MODEL; nModelSet++)
	{
		if (pModel->modelSet[nModelSet].bUse == true)
		{
			if (pModel->modelSet[nModelSet].bCollision == true)
			{
				// 敵がプレイヤーを見るようにする
				// 敵とプレイヤーの方向ベクトル
				D3DXVECTOR3 ObjectVecCurrent = D3DXVECTOR3(pPos->x - pModel->modelSet[nModelSet].pos.x,
					pPos->y - pModel->modelSet[nModelSet].pos.y,
					pPos->z - pModel->modelSet[nModelSet].pos.z);

				D3DXVECTOR3 ObjectVecOld = D3DXVECTOR3(pPosOld->x - pModel->modelSet[nModelSet].pos.x,
					pPosOld->y - pModel->modelSet[nModelSet].pos.y,
					pPosOld->z - pModel->modelSet[nModelSet].pos.z);

				// 自機と中心点の対角線の長さ
				float fLengthCurrent = sqrtf((ObjectVecCurrent.x * ObjectVecCurrent.x) + (ObjectVecCurrent.z * ObjectVecCurrent.z));
				float fLengthOld = sqrtf((ObjectVecOld.x * ObjectVecOld.x) + (ObjectVecOld.z * ObjectVecOld.z));

				if (fLengthCurrent <= 300.0f + 10.0f && fLengthOld > 300.0f)
				{
					if ((pPos->y <= pModel->modelSet[nModelSet].pos.y + pModel->modelSet[nModelSet].vtxMaxModel.y) &&
						(pPos->y >= pModel->modelSet[nModelSet].pos.y + pModel->modelSet[nModelSet].vtxMinModel.y))
					{
						float fAngle = atan2f(pPos->x - pModel->modelSet[nModelSet].pos.x, pPos->z - pModel->modelSet[nModelSet].pos.z);

						// 座標の設定
						pPos->x = (300.0f + 10.0f) * sinf(fAngle) + pModel->modelSet[nModelSet].pos.x;
						pPos->z = (300.0f + 10.0f) * cosf(fAngle) + pModel->modelSet[nModelSet].pos.z;
					}
				}
				else if (fLengthCurrent < 300.0f)
				{
					if ((pPosOld->y >= pModel->modelSet[nModelSet].pos.y + pModel->modelSet[nModelSet].vtxMaxModel.y) &&
						(pPos->y < pModel->modelSet[nModelSet].pos.y + pModel->modelSet[nModelSet].vtxMaxModel.y))
					{
						pPos->y = pModel->modelSet[nModelSet].pos.y + pModel->modelSet[nModelSet].vtxMaxModel.y;

						// 乗ってることを伝える
						bCollisionModel = true;
					}
					if (pPos->y >= pModel->modelSet[nModelSet].pos.y + pModel->modelSet[nModelSet].vtxMaxModel.y)
					{
						// 影の位置を固定
						PosShadow->y = pModel->modelSet[nModelSet].pos.y + pModel->modelSet[nModelSet].vtxMaxModel.y;
					}
				}
			}
		}
	}
	return bCollisionModel;
}

//-----------------------------------------------------------------
// モデルの設置
//-----------------------------------------------------------------
void SetModel(int type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nCollition)
{
	// 構造体のポインタ変数
	ModelSetInfo *pModelSetInfo = &g_ModelSet.modelSet[0];

	for (int nCntSetModel = 0; nCntSetModel < MAX_MODEL; nCntSetModel++, pModelSetInfo++)
	{
		if (pModelSetInfo->bUse == false)
		{
			// タイプの代入
			pModelSetInfo->nIdx = type;

			// 位置情報の代入
			pModelSetInfo->pos = pos;

			// 向き情報の代入
			pModelSetInfo->rot = rot;

			// 当たり判定するかどうか代入
			if (nCollition == 0)
			{
				pModelSetInfo->bCollision = true;
			}
			else
			{
				pModelSetInfo->bCollision = false;
			}
			// 使用状態をtrueにする
			pModelSetInfo->bUse = true;

			break;
		}
	}
}

//-----------------------------------------------------------------
// モデル情報の取得
//-----------------------------------------------------------------
ModelSet *GetModelSet(void)
{
	return &g_ModelSet;
}