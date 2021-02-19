////////////////////////////////////////////////////////////////////////////////
//
//Contents	: モデルの処理 [model.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/11/16
//
////////////////////////////////////////////////////////////////////////////////
#include "model.h"
#include "input.h"
#include "camera.h"
#include "bullet.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define MOVE_SPEED (1.0f)

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPD3DXMESH  g_pMeshModel = NULL;		//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatModel = NULL;	//マテリアル(材質情報)へのポインタ
DWORD g_nNumMatModel;					//マテリアルの数
D3DXVECTOR3 g_posModel;					//位置
D3DXVECTOR3 g_rotModel;					//向き
D3DXMATRIX g_mtxWorldModel;				//ワールドマトリックス

////////////////////////////////////////////////////////////////////////////////
//モデルの初期化処理
////////////////////////////////////////////////////////////////////////////////
void InitModel(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data/model/3Dgame_head.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatModel, NULL, &g_nNumMatModel, &g_pMeshModel);

	g_posModel = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
	g_rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

////////////////////////////////////////////////////////////////////////////////
//モデルの終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitModel(void)
{
	//メッシュの破棄
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();	//破棄
		g_pMeshModel = NULL;		//初期化
	}

	//マテリアルの開放
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();	//開放
		g_pBuffMatModel = NULL;		//初期化
	}
}

////////////////////////////////////////////////////////////////////////////////
//モデルの更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateModel(void)
{
	CAMERA *camera = GetCamera();

	#if 0
	//回転
	if (GetKeyboardPress(DIK_M) == TRUE)
	{
		g_rotModel.y += 0.025f;
	}
	if (GetKeyboardPress(DIK_N) == TRUE)
	{
		g_rotModel.y -= 0.025f;
	}

	if (g_rotModel.x < D3DXToRadian(90) && GetKeyboardPress(DIK_B) == TRUE)
	{
		g_rotModel.x += 0.025f;
	}
	if (g_rotModel.x > -D3DXToRadian(90) && GetKeyboardPress(DIK_V) == TRUE)
	{
		g_rotModel.x -= 0.025f;
	}
	#endif

#if 1
	//移動
	if (GetKeyboardPress(DIK_W) == TRUE)
	{
		g_posModel.x += sinf(camera->rot.y) * MOVE_SPEED;
		g_posModel.z += cosf(camera->rot.y) * MOVE_SPEED;
		if (g_rotModel.y <= camera->rot.y + (D3DX_PI - camera->rot.y) && g_rotModel.y >= 0)
		{
			g_rotModel.y = g_rotModel.y += ((camera->rot.y + D3DX_PI) - g_rotModel.y) * 0.1f;
		}
		else if (g_rotModel.y >= camera->rot.y - (D3DX_PI + camera->rot.y) && g_rotModel.y <= 0)
		{
			g_rotModel.y = g_rotModel.y += ((camera->rot.y - D3DX_PI) - g_rotModel.y) * 0.1f;
		}
	}
	if (GetKeyboardPress(DIK_S) == TRUE)
	{
		g_posModel.x -= sinf(camera->rot.y) * MOVE_SPEED;
		g_posModel.z -= cosf(camera->rot.y) * MOVE_SPEED;
		if (g_rotModel.y > camera->rot.y)
		{
			g_rotModel.y = g_rotModel.y += (camera->rot.y - g_rotModel.y) * 0.1f;
		}
		else if (g_rotModel.y <= camera->rot.y)
		{
			g_rotModel.y = g_rotModel.y += (camera->rot.y - g_rotModel.y) * 0.1f;
		}
	}
	if (GetKeyboardPress(DIK_A) == TRUE)
	{
		g_posModel.x -= sinf(camera->rot.y + D3DXToRadian(90)) * MOVE_SPEED;
		g_posModel.z += cosf(camera->rot.y - D3DXToRadian(90)) * MOVE_SPEED;
		if (g_rotModel.y <= camera->rot.y + ((D3DX_PI / 2) + camera->rot.y) && g_rotModel.y >= ((-D3DX_PI / 2) - camera->rot.y))
		{
			g_rotModel.y = g_rotModel.y += ((camera->rot.y + (D3DX_PI / 2)) - g_rotModel.y) * 0.1f;
		}
		else if (g_rotModel.y >= camera->rot.y + ((D3DX_PI / 2) + camera->rot.y) && g_rotModel.y <= ((-D3DX_PI / 2) + camera->rot.y))
		{
			g_rotModel.y = g_rotModel.y += ((camera->rot.y + (D3DX_PI / 2)) - g_rotModel.y) * 0.1f;
		}
	}
	if (GetKeyboardPress(DIK_D) == TRUE)
	{
		g_posModel.x += sinf(camera->rot.y + D3DXToRadian(90)) * MOVE_SPEED;
		g_posModel.z -= cosf(camera->rot.y - D3DXToRadian(90)) * MOVE_SPEED;
		g_rotModel.y = camera->rot.y - D3DXToRadian(90);
	}
	if (GetKeyboardPress(DIK_O) == TRUE)
	{
		g_posModel.y += MOVE_SPEED;
	}
	if (GetKeyboardPress(DIK_L) == TRUE)
	{
		g_posModel.y -= MOVE_SPEED;
	}
#endif

	if (g_rotModel.y < -D3DX_PI)
	{
		g_rotModel.y += D3DX_PI * 2.0f;
	}
	else if (g_rotModel.y > D3DX_PI)
	{
		g_rotModel.y -= D3DX_PI * 2.0f;
	}
}

////////////////////////////////////////////////////////////////////////////////
//モデルの描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawModel(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアル保存用
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldModel);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y, g_rotModel.x, g_rotModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posModel.x, g_posModel.y, g_posModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

	//現在のマテリアルの取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL *)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, NULL);

		//モデル(パーツ)の描画
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//////////////////////////////////////////////////////////////////////////////////
////モデルの射撃処理
//////////////////////////////////////////////////////////////////////////////////
//void ShotModel(void)
//{
//	if (GetKeyboardTrigger(DIK_RETURN) == TRUE)
//	{
//		SetBullet(g_posModel, D3DXVECTOR3(sinf(g_rotModel.y) * -5.0f, 0.0f, cosf(g_rotModel.y) * -5.0f), 40);
//	}
//}

////////////////////////////////////////////////////////////////////////////////
//モデルの位置を取得
////////////////////////////////////////////////////////////////////////////////
D3DXVECTOR3 *GetPosModel(void)
{
	return &g_posModel;
}

////////////////////////////////////////////////////////////////////////////////
//モデルの位置を取得
////////////////////////////////////////////////////////////////////////////////
D3DXVECTOR3 *GetRotModel(void)
{
	return &g_rotModel;
}