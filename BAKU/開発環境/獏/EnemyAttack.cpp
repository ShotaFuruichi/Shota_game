////////////////////////////////////////////////////////////////////////////////
//
//Contents	: 敵の攻撃処理 [EnemyAttack.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/02/15
//
////////////////////////////////////////////////////////////////////////////////
#include "EnemyAttack.h"
#include "enemy.h"
#include "player.h"

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define MAX_ENEMYATTACK (64)		//攻撃の最大数
#define ATTACK_TIME (120)			//円が現れてから攻撃が行われるまでの長さ
#define ATTACK_SIZE (450)			//円の大きさ
#define ENEMYATTACK_DAMAGE (1500)	//敵の攻撃力


////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemyAttack = NULL;	//頂点情報
LPDIRECT3DTEXTURE9 g_pTextureEnemyAttack = NULL;		//テクスチャ情報
ENEMYATTACK g_aEnemyAttack[MAX_ENEMYATTACK];			//敵の攻撃

////////////////////////////////////////////////////////////////////////////////
//初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT InitEnemyAttack(void)
{
	//変数宣言
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\AttackSign.png", &g_pTextureEnemyAttack);

	for (int nCntAttack = 0; nCntAttack < MAX_ENEMYATTACK; nCntAttack++)
	{
		g_aEnemyAttack[nCntAttack].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemyAttack[nCntAttack].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemyAttack[nCntAttack].bUse = false;
	}

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_ENEMYATTACK, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffEnemyAttack, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemyAttack->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntAttack = 0; nCntAttack < MAX_ENEMYATTACK; nCntAttack++)
	{
		SetVertexAttack(nCntAttack);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemyAttack->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitEnemyAttack(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffEnemyAttack != NULL)
	{
		g_pVtxBuffEnemyAttack->Release();	//開放
		g_pVtxBuffEnemyAttack = NULL;		//初期化
	}

	//テクスチャの開放
	if (g_pTextureEnemyAttack != NULL)
	{
		g_pTextureEnemyAttack->Release();	//開放
		g_pTextureEnemyAttack = NULL;		//初期化
	}
}

////////////////////////////////////////////////////////////////////////////////
//更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateEnemyAttack(void)
{
	PLAYER *player = GetPlayer();
	D3DXVECTOR3 Distance[MAX_ENEMYATTACK];
	float fDis[MAX_ENEMYATTACK];
	float fSize = powf(ATTACK_SIZE, 2.0f);

	for (int nCntAttack = 0; nCntAttack < MAX_ENEMYATTACK; nCntAttack++)
	{
		if (g_aEnemyAttack[nCntAttack].bUse == true)
		{
			Distance[nCntAttack].x = (player->pos.x - g_aEnemyAttack[nCntAttack].pos.x);
			Distance[nCntAttack].z = (player->pos.z - g_aEnemyAttack[nCntAttack].pos.z);
			
			Distance[nCntAttack].x = powf(Distance[nCntAttack].x, 2.0f);
			Distance[nCntAttack].z = powf(Distance[nCntAttack].z, 2.0f);
			
			Distance[nCntAttack].x -= powf(PLAYER_SIZEXZ, 2.0f);
			Distance[nCntAttack].z -= powf(PLAYER_SIZEXZ, 2.0f);
			
			fDis[nCntAttack] = Distance[nCntAttack].x + Distance[nCntAttack].z;

			g_aEnemyAttack[nCntAttack].nTime--;
			if (g_aEnemyAttack[nCntAttack].nTime <= 0)
			{
				if (fDis[nCntAttack] <= fSize)
				{
					player->nLife -= ENEMYATTACK_DAMAGE;
				}
				g_aEnemyAttack[nCntAttack].bUse = false;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawEnemyAttack(void)
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

	for (int nCntAttack = 0; nCntAttack < MAX_ENEMYATTACK; nCntAttack++)
	{
		if (g_aEnemyAttack[nCntAttack].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aEnemyAttack[nCntAttack].mtxworld);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aEnemyAttack[nCntAttack].pos.x, g_aEnemyAttack[nCntAttack].pos.y, g_aEnemyAttack[nCntAttack].pos.z);
			D3DXMatrixMultiply(&g_aEnemyAttack[nCntAttack].mtxworld, &g_aEnemyAttack[nCntAttack].mtxworld, &mtxTrans);

			//ワールドマトリックス
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemyAttack[nCntAttack].mtxworld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffEnemyAttack, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEnemyAttack);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntAttack * 4, 2);
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
void SetEnemyAttack(void)
{
	//変数宣言
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();
	int nType = GetRandom(ENEMYATTACKTYPE_1, ENEMYATTACKTYPE_2);

	for (int nCntAttack = 0; nCntAttack < MAX_ENEMYATTACK; nCntAttack++)
	{
		if (g_aEnemyAttack[nCntAttack].bUse == false)
		{
			switch (nType)
			{
			case ENEMYATTACKTYPE_1:
				g_aEnemyAttack[nCntAttack].pos = D3DXVECTOR3(player->pos.x + GetRandom(-500, 500), 1.0f, player->pos.z + GetRandom(-500, 500));
				g_aEnemyAttack[nCntAttack].bUse = true;
				g_aEnemyAttack[nCntAttack].nTime = ATTACK_TIME;
				break;
			case ENEMYATTACKTYPE_2:
				g_aEnemyAttack[nCntAttack].pos = D3DXVECTOR3(enemy->pos.x, 1.0f, enemy->pos.z);
				g_aEnemyAttack[nCntAttack].bUse = true;
				g_aEnemyAttack[nCntAttack].nTime = ATTACK_TIME;
			}
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//頂点座標の設定
////////////////////////////////////////////////////////////////////////////////
void SetVertexAttack(int nIdx)
{
	//変数宣言
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemyAttack->Lock(0, 0, (void**)&pVtx, 0);

	//pVtxのポインタ調節
	pVtx += nIdx * 4;

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_aEnemyAttack[nIdx].pos.x - ATTACK_SIZE, 1, g_aEnemyAttack[nIdx].pos.z - ATTACK_SIZE);
	pVtx[1].pos = D3DXVECTOR3(g_aEnemyAttack[nIdx].pos.x - ATTACK_SIZE, 1, g_aEnemyAttack[nIdx].pos.z + ATTACK_SIZE);
	pVtx[2].pos = D3DXVECTOR3(g_aEnemyAttack[nIdx].pos.x + ATTACK_SIZE, 1, g_aEnemyAttack[nIdx].pos.z - ATTACK_SIZE);
	pVtx[3].pos = D3DXVECTOR3(g_aEnemyAttack[nIdx].pos.x + ATTACK_SIZE, 1, g_aEnemyAttack[nIdx].pos.z + ATTACK_SIZE);

	//頂点バッファをアンロックする
	g_pVtxBuffEnemyAttack->Unlock();
}