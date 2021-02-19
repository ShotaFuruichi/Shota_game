////////////////////////////////////////////////////////////////////////////////
//
//Contents	: 敵の処理 [enemy.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/02/15
//
////////////////////////////////////////////////////////////////////////////////
#include "enemy.h"
#include "EnemyAttack.h"
#include "fade.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
ENEMY g_Enemy;	//敵	

////////////////////////////////////////////////////////////////////////////////
//初期化処理
////////////////////////////////////////////////////////////////////////////////
void InitEnemy(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data/model/enemy_body.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Enemy.aModel[0].pBufferMat, NULL, &g_Enemy.aModel[0].nNumMat, &g_Enemy.aModel[0].pMesh);
	D3DXLoadMeshFromX("data/model/enemy_head.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Enemy.aModel[1].pBufferMat, NULL, &g_Enemy.aModel[1].nNumMat, &g_Enemy.aModel[1].pMesh);
	D3DXLoadMeshFromX("data/model/enemy_armR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Enemy.aModel[2].pBufferMat, NULL, &g_Enemy.aModel[2].nNumMat, &g_Enemy.aModel[2].pMesh);
	D3DXLoadMeshFromX("data/model/enemy_handR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Enemy.aModel[3].pBufferMat, NULL, &g_Enemy.aModel[3].nNumMat, &g_Enemy.aModel[3].pMesh);
	D3DXLoadMeshFromX("data/model/enemy_armL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Enemy.aModel[4].pBufferMat, NULL, &g_Enemy.aModel[4].nNumMat, &g_Enemy.aModel[4].pMesh);
	D3DXLoadMeshFromX("data/model/enemy_handL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Enemy.aModel[5].pBufferMat, NULL, &g_Enemy.aModel[5].nNumMat, &g_Enemy.aModel[5].pMesh);

	g_Enemy.nNumModel = MAX_MODEL_ENEMY;

	//各パーツの階層構造設定
	g_Enemy.aModel[0].nIdxModelParent = -1;									//親モデルのインデックスを設定
	g_Enemy.aModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, .0f);					//位置(オフセット)の初期設定
	g_Enemy.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//向きの初期設定
	g_Enemy.aModel[1].nIdxModelParent = 0;									//親モデルのインデックスを設定
	g_Enemy.aModel[1].pos = D3DXVECTOR3(0.0f, 275.0f, 0.0f);				//位置(オフセット)の初期設定
	g_Enemy.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//向きの初期設定
	g_Enemy.aModel[2].nIdxModelParent = 0;									//親モデルのインデックスを設定
	g_Enemy.aModel[2].pos = D3DXVECTOR3(-75.0f, 200.0f, 0.0f);				//位置(オフセット)の初期設定
	g_Enemy.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 45.0f);					//向きの初期設定
	g_Enemy.aModel[3].nIdxModelParent = 2;									//親モデルのインデックスを設定
	g_Enemy.aModel[3].pos = D3DXVECTOR3(-150.0f, 0.0f, 0.0f);				//位置(オフセット)の初期設定
	g_Enemy.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//向きの初期設定
	g_Enemy.aModel[4].nIdxModelParent = 0;									//親モデルのインデックスを設定
	g_Enemy.aModel[4].pos = D3DXVECTOR3(75.0f, 200.0f, 0.0f);				//位置(オフセット)の初期設定
	g_Enemy.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, -45.0f);				//向きの初期設定
	g_Enemy.aModel[5].nIdxModelParent = 4;									//親モデルのインデックスを設定
	g_Enemy.aModel[5].pos = D3DXVECTOR3(150.0f, 0.0f, 0.0f);				//位置(オフセット)の初期設定
	g_Enemy.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//向きの初期設定
	
	g_Enemy.pos = D3DXVECTOR3(ENEMY_APPEARX, ENEMY_APPEARY, ENEMY_APPEARZ);	//プレイヤーの位置の初期設定
	g_Enemy.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//プレイヤーの前回更新時の位置の初期設定
	g_Enemy.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//プレイヤーの向きの初期設定
	g_Enemy.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//プレイヤーの目標の向きの初期設定
	g_Enemy.nowMotion = MOTION_NEUTRAL;										//現在のモーション
	g_Enemy.nLife = LIFE_ENEMY;												//敵の体力
}

////////////////////////////////////////////////////////////////////////////////
//終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitEnemy(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL_ENEMY; nCntModel++)
	{
		if (g_Enemy.aModel[nCntModel].pMesh != NULL)
		{
			g_Enemy.aModel[nCntModel].pMesh->Release();	//破棄
			g_Enemy.aModel[nCntModel].pMesh = NULL;		//初期化
		}

		if (g_Enemy.aModel[nCntModel].pBufferMat != NULL)
		{
			g_Enemy.aModel[nCntModel].pBufferMat->Release();	//破棄
			g_Enemy.aModel[nCntModel].pBufferMat = NULL;		//初期化
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateEnemy(void)
{
	if (g_Enemy.nowMotion != MOTION_JUMP && g_Enemy.nowMotion != MOTION_ACTION)
	{
		g_Enemy.nowMotion = MOTION_NEUTRAL;
	}

	if (g_Enemy.nLife <= 0)
	{
		SetFade(FADE_OUT, MODE_RESULT);
	}
	
	AttackEnemy();

	g_Enemy.aModel[1].rot.x -= 0.01f;
	g_Enemy.aModel[1].rot.y -= 0.01f;
	g_Enemy.aModel[1].rot.z -= 0.01f;

	//MotionEnemy();
}

////////////////////////////////////////////////////////////////////////////////
//描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアル保存用
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

												//プレイヤーのワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Enemy.mtxWorld);

	//プレイヤーの向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy.rot.y, g_Enemy.rot.x, g_Enemy.rot.z);
	D3DXMatrixMultiply(&g_Enemy.mtxWorld, &g_Enemy.mtxWorld, &mtxRot);

	//プレイヤーの位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Enemy.pos.x, g_Enemy.pos.y, g_Enemy.pos.z);
	D3DXMatrixMultiply(&g_Enemy.mtxWorld, &g_Enemy.mtxWorld, &mtxTrans);

	//プレイヤーのワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Enemy.mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < g_Enemy.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;	//計算用マトリックス
		D3DXMATRIX mtxParent;					//親のマトリックス

												//各パーツのワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Enemy.aModel[nCntModel].mtxWorld);

		//各パーツの向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy.aModel[nCntModel].rot.y, g_Enemy.aModel[nCntModel].rot.x, g_Enemy.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_Enemy.aModel[nCntModel].mtxWorld, &g_Enemy.aModel[nCntModel].mtxWorld, &mtxRot);

		//各パーツの位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Enemy.aModel[nCntModel].pos.x, g_Enemy.aModel[nCntModel].pos.y, g_Enemy.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_Enemy.aModel[nCntModel].mtxWorld, &g_Enemy.aModel[nCntModel].mtxWorld, &mtxTrans);

		//各パーツの親のマトリックスを設定
		if (g_Enemy.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_Enemy.aModel[g_Enemy.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_Enemy.mtxWorld;	//プレイヤーのマトリックスを設定
		}

		//算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
		D3DXMatrixMultiply(&g_Enemy.aModel[nCntModel].mtxWorld, &g_Enemy.aModel[nCntModel].mtxWorld, &mtxParent);

		//各パーツのワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Enemy.aModel[nCntModel].mtxWorld);

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL *)g_Enemy.aModel[nCntModel].pBufferMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Enemy.aModel[nCntModel].nNumMat; nCntMat++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, NULL);

			//モデル(パーツ)の描画
			g_Enemy.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

////////////////////////////////////////////////////////////////////////////////
//敵の攻撃
////////////////////////////////////////////////////////////////////////////////
void AttackEnemy(void)
{
	g_Enemy.AttackCounter++;
	if (g_Enemy.AttackCounter % ATTACK_INTERVAL == 0)
	{
		for (int nAttack = 0; nAttack < 4; nAttack++)
		{
			SetEnemyAttack();
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//敵の情報を取得
////////////////////////////////////////////////////////////////////////////////
ENEMY *GetEnemy(void)
{
	return &g_Enemy;
}