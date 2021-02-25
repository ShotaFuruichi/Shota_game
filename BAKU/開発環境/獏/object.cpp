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

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPD3DXMESH  g_pMeshObject = NULL;				//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatObject = NULL;			//マテリアル(材質情報)へのポインタ
DWORD g_nNumMatObject;							//マテリアルの数
D3DXVECTOR3 g_posObject;						//位置
D3DXVECTOR3 g_rotObject;						//向き
D3DXMATRIX g_mtxWorldObject;					//ワールドマトリックス
D3DXVECTOR3 g_vtxMinObject, g_vtxMaxObject;		//モデルの最小値、最大値
LPDIRECT3DTEXTURE9 g_pTextureObject[256] = {};	//テクスチャへのポインタ

////////////////////////////////////////////////////////////////////////////////
//オブジェクトの初期化処理
////////////////////////////////////////////////////////////////////////////////
void InitObject(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();
	
	g_posObject = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
	g_rotObject = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data/model/iwa.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject, NULL, &g_nNumMatObject, &g_pMeshObject);

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

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldObject);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotObject.y, g_rotObject.x, g_rotObject.z);
	D3DXMatrixMultiply(&g_mtxWorldObject, &g_mtxWorldObject, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posObject.x, g_posObject.y, g_posObject.z);
	D3DXMatrixMultiply(&g_mtxWorldObject, &g_mtxWorldObject, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldObject);

	//現在のマテリアルの取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL *)g_pBuffMatObject->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatObject; nCntMat++)
	{
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

////////////////////////////////////////////////////////////////////////////////
//当たり判定
////////////////////////////////////////////////////////////////////////////////
bool CollisionObject(D3DXVECTOR3 pos, D3DXVECTOR3 oldpos)
{

	D3DXVECTOR3 max;
	D3DXVECTOR3 min;
	D3DXVECTOR3 *pPosPlayer = GetPosPlayer();
	D3DXVECTOR3 *pPosOldPlayer = GetPosOld();

	
	max = g_vtxMaxObject + g_posObject;
	min = g_vtxMinObject + g_posObject;

	if (pos.x + PLAYER_SIZEXZ > min.x && pos.x - PLAYER_SIZEXZ < max.x)
	{
		if (pos.z + PLAYER_SIZEXZ > min.z && pos.z - PLAYER_SIZEXZ < max.z)
		{
			if (oldpos.y > max.y)
			{
				if (pos.y < max.y)
				{
					return true;
				}
			}
			else if (oldpos.y + PLAYER_SIZEY < min.y)
			{
				if (pos.y + PLAYER_SIZEY > min.y)
				{
					pPosPlayer->y = pPosOldPlayer->y;
				}
			}
		}

		for (int nCnt = 0; nCnt < (int)PLAYER_SIZEY; nCnt++)
		{
			if (pos.y + nCnt > min.y && pos.y + nCnt < max.y)
			{
				if (oldpos.z + PLAYER_SIZEXZ < min.z || oldpos.z - PLAYER_SIZEXZ > max.z)
				{
					if (pos.z + PLAYER_SIZEXZ > min.z && pos.z - PLAYER_SIZEXZ < max.z)
					{
						pPosPlayer->z = pPosOldPlayer->z;
					}
				}
			}
		}
	}
	if (pos.z + PLAYER_SIZEXZ > min.z && pos.z - PLAYER_SIZEXZ < max.z)
	{
		for (int nCnt = 0; nCnt < (int)PLAYER_SIZEY; nCnt++)
		{
			if (pos.y + nCnt > min.y && pos.y + nCnt < max.y)
			{
				if (oldpos.x + PLAYER_SIZEXZ < min.x || oldpos.x - PLAYER_SIZEXZ > max.x)
				{
					if (pos.x + PLAYER_SIZEXZ > min.x && pos.x - PLAYER_SIZEXZ < max.x)
					{
						pPosPlayer->x = pPosOldPlayer->x;
					}
				}
			}
		}
	}
	return false;
}