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
#include "player.h"
#include "result.h"
#include "sound.h"

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
	g_Enemy.nAttackCounter = 0;												//攻撃の間隔
	g_Enemy.nLife = LIFE_ENEMY;												//敵の体力
	g_Enemy.nowMotion = ENEMYMOTION_MAX;									//現在のモーション
	g_Enemy.bDrop = false;													//落ちるか	
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
	PLAYER *player = GetPlayer();

	if (g_Enemy.nLife <= 0)
	{
		SetFade(FADE_OUT, MODE_RESULT);
	}
	
	AttackEnemy();

	if (g_Enemy.rot.y < -D3DX_PI)
	{// -3.14fより小さくなったとき値に3.14fにする
		g_Enemy.rot.y += D3DX_PI * 2.0f;
	}
	else if (g_Enemy.rot.y > D3DX_PI)
	{// 3.14fより大きくなったとき値を-3.14fにする
		g_Enemy.rot.y -= D3DX_PI * 2.0f;
	}

	D3DXVECTOR3 vector = player->pos - g_Enemy.pos;
	float fAngle = atan2f(vector.x, vector.z);

	if (g_Enemy.nowMotion != ENEMYMOTION_DROP)
	{
		g_Enemy.rot.y = fAngle;
	}

	if (g_Enemy.bDamage == true)
	{
		static int nCntDamage = 0;
		nCntDamage++;
		if (nCntDamage > 30)
		{
			nCntDamage = 0;
			g_Enemy.bDamage = false;;
		}
	}

	g_Enemy.aModel[1].rot.x -= 0.01f;
	g_Enemy.aModel[1].rot.y -= 0.01f;
	g_Enemy.aModel[1].rot.z -= 0.01f;

	MotionEnemy();
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
	D3DXCOLOR col;								//モデルの色保存用

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
			if (g_Enemy.bDamage == true)
			{
				//マテリアルの拡散光の色を保存
				col = pMat[nCntMat].MatD3D.Diffuse;

				//マテリアルの拡散光の色を変更
				pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			}

			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			if (g_Enemy.bDamage == true)
			{
				//マテリアルの拡散光の色を元に戻す
				pMat[nCntMat].MatD3D.Diffuse = col;
			}

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
	int nType = GetRandom(ENEMYATTACKTYPE_1, ENEMYATTACKTYPE_2);

	g_Enemy.nAttackCounter++;
	if (g_Enemy.nAttackCounter % ATTACK_INTERVAL == 0)
	{
		switch (nType)
		{
		case ENEMYATTACKTYPE_1:
			SetEnemyAttack();
			break;
		case ENEMYATTACKTYPE_2:
			SetEnemyAttack2();
			g_Enemy.nowMotion = ENEMYMOTION_DROP;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//敵のモーション
////////////////////////////////////////////////////////////////////////////////
void MotionEnemy(void)
{
	switch (g_Enemy.nowMotion)
	{
	case ENEMYMOTION_DROP:
		if (g_Enemy.bDrop == false)
		{
			g_Enemy.rot.y += 0.1f;
			g_Enemy.pos.y += 5.0f;
		}

		if (g_Enemy.pos.y > 800)
		{
			g_Enemy.bDrop = true;
		}

		if (g_Enemy.bDrop == true)
		{
			g_Enemy.pos.y -= 35.0f;

			if (g_Enemy.pos.y < ENEMY_APPEARY)
			{
				g_Enemy.pos.y = ENEMY_APPEARY;
				g_Enemy.nowMotion = ENEMYMOTION_MAX;
				g_Enemy.bDrop = false;
			}
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