////////////////////////////////////////////////////////////////////////////////
//
//Contents	: オブジェクトの処理 [object.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/12/10
//
////////////////////////////////////////////////////////////////////////////////
#include "object.h"
#include "player.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define DELETE_OBJECT (120)

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPD3DXMESH  g_pMeshObject = NULL;				//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatObject = NULL;			//マテリアル(材質情報)へのポインタ
DWORD g_nNumMatObject;							//マテリアルの数
D3DXVECTOR3 g_vtxMinObject, g_vtxMaxObject;		//モデルの最小値、最大値
LPDIRECT3DTEXTURE9 g_pTextureObject[256] = {};	//テクスチャへのポインタ
OBJECT g_aObject[MAX_OBJECT];					//オブジェクトの情報

////////////////////////////////////////////////////////////////////////////////
//オブジェクトの初期化処理
////////////////////////////////////////////////////////////////////////////////
void InitObject(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();
	
	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		g_aObject[nCntObj].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aObject[nCntObj].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aObject[nCntObj].bUse = false;
		g_aObject[nCntObj].nCount = 0;
	}

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data/model/Rock.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject, NULL, &g_nNumMatObject, &g_pMeshObject);

	int nNumVtx;		//頂点数
	DWORD sizeFVF;		//頂点フォーマットのサイズ
	BYTE *pVtxBuff;		//頂点バッファへのポインタ
	D3DXMATERIAL *pMat;	//マテリアルのポインタ

	//マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatObject->GetBufferPointer();

	//テクスチャの読み込み
	for (int nCntMat = 0; nCntMat < (int)g_nNumMatObject; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, g_pTextureObject);
		}
	}

	//頂点数を取得
	nNumVtx = g_pMeshObject->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshObject->GetFVF());

	//頂点バッファをロック
	g_pMeshObject->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

		//全ての頂点を比較してモデルの最小値、最大値を抜き出す
		if (vtx.x < g_vtxMinObject.x)
		{
			g_vtxMinObject.x = vtx.x;
		}
		if (vtx.x > g_vtxMaxObject.x)
		{
			g_vtxMaxObject.x = vtx.x;
		}
		if (vtx.y < g_vtxMinObject.y)
		{
			g_vtxMinObject.y = vtx.y;
		}
		if (vtx.y > g_vtxMaxObject.y)
		{
			g_vtxMaxObject.y = vtx.y;
		}
		if (vtx.z < g_vtxMinObject.z)
		{
			g_vtxMinObject.z = vtx.z;
		}
		if (vtx.z > g_vtxMaxObject.z)
		{
			g_vtxMaxObject.z = vtx.z;
		}

		pVtxBuff += sizeFVF;	//頂点フォーマットのサイズ分ポインタを進める
	}

	//頂点バッファをアンロック
	g_pMeshObject->UnlockVertexBuffer();
}

////////////////////////////////////////////////////////////////////////////////
//オブジェクトの終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitObject(void)
{
	//メッシュの破棄
	if (g_pMeshObject != NULL)
	{
		g_pMeshObject->Release();	//破棄
		g_pMeshObject = NULL;		//初期化
	}

	//マテリアルの開放
	if (g_pBuffMatObject != NULL)
	{
		g_pBuffMatObject->Release();	//開放
		g_pBuffMatObject = NULL;		//初期化
	}
}

////////////////////////////////////////////////////////////////////////////////
//オブジェクトの更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateObject(void)
{
	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		if (g_aObject[nCntObj].bUse == true)
		{
			g_aObject[nCntObj].nCount++;

			if (g_aObject[nCntObj].nCount == DELETE_OBJECT)
			{
				g_aObject[nCntObj].nCount = 0;
				g_aObject[nCntObj].bUse = false;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//オブジェクトの描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawObject(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアル保存用
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		if (g_aObject[nCntObj].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aObject[nCntObj].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aObject[nCntObj].rot.y, g_aObject[nCntObj].rot.x, g_aObject[nCntObj].rot.z);
			D3DXMatrixMultiply(&g_aObject[nCntObj].mtxWorld, &g_aObject[nCntObj].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aObject[nCntObj].pos.x, g_aObject[nCntObj].pos.y, g_aObject[nCntObj].pos.z);
			D3DXMatrixMultiply(&g_aObject[nCntObj].mtxWorld, &g_aObject[nCntObj].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aObject[nCntObj].mtxWorld);

			//現在のマテリアルの取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL *)g_pBuffMatObject->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatObject; nCntMat++)
			{
				if (g_aObject[nCntObj].nCount == 0)
				{
					pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;
				}
				else
				{
					pMat[nCntMat].MatD3D.Diffuse.a -= 0.001f;
				}

				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureObject[nCntMat]);

				//モデル(パーツ)の描画
				g_pMeshObject->DrawSubset(nCntMat);
			}

			//保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//セット処理
////////////////////////////////////////////////////////////////////////////////
void SetObject(D3DXVECTOR3 pos)
{
	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		if (g_aObject[nCntObj].bUse == false)
		{
			g_aObject[nCntObj].pos = pos;
			g_aObject[nCntObj].bUse = true;
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//当たり判定
////////////////////////////////////////////////////////////////////////////////
bool CollisionObject(D3DXVECTOR3 pos, D3DXVECTOR3 oldpos)
{

	//D3DXVECTOR3 max;
	//D3DXVECTOR3 min;
	//D3DXVECTOR3 *pPosPlayer = GetPosPlayer();
	//D3DXVECTOR3 *pPosOldPlayer = GetPosOld();

	//
	//max = g_vtxMaxObject + g_posObject;
	//min = g_vtxMinObject + g_posObject;

	//if (pos.x + PLAYER_SIZEXZ > min.x && pos.x - PLAYER_SIZEXZ < max.x)
	//{
	//	if (pos.z + PLAYER_SIZEXZ > min.z && pos.z - PLAYER_SIZEXZ < max.z)
	//	{
	//		if (oldpos.y > max.y)
	//		{
	//			if (pos.y < max.y)
	//			{
	//				return true;
	//			}
	//		}
	//		else if (oldpos.y + PLAYER_SIZEY < min.y)
	//		{
	//			if (pos.y + PLAYER_SIZEY > min.y)
	//			{
	//				pPosPlayer->y = pPosOldPlayer->y;
	//			}
	//		}
	//	}

	//	for (int nCnt = 0; nCnt < (int)PLAYER_SIZEY; nCnt++)
	//	{
	//		if (pos.y + nCnt > min.y && pos.y + nCnt < max.y)
	//		{
	//			if (oldpos.z + PLAYER_SIZEXZ < min.z || oldpos.z - PLAYER_SIZEXZ > max.z)
	//			{
	//				if (pos.z + PLAYER_SIZEXZ > min.z && pos.z - PLAYER_SIZEXZ < max.z)
	//				{
	//					pPosPlayer->z = pPosOldPlayer->z;
	//				}
	//			}
	//		}
	//	}
	//}
	//if (pos.z + PLAYER_SIZEXZ > min.z && pos.z - PLAYER_SIZEXZ < max.z)
	//{
	//	for (int nCnt = 0; nCnt < (int)PLAYER_SIZEY; nCnt++)
	//	{
	//		if (pos.y + nCnt > min.y && pos.y + nCnt < max.y)
	//		{
	//			if (oldpos.x + PLAYER_SIZEXZ < min.x || oldpos.x - PLAYER_SIZEXZ > max.x)
	//			{
	//				if (pos.x + PLAYER_SIZEXZ > min.x && pos.x - PLAYER_SIZEXZ < max.x)
	//				{
	//					pPosPlayer->x = pPosOldPlayer->x;
	//				}
	//			}
	//		}
	//	}
	//}
	return false;
}