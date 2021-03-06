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
#include "HitEffect.h"
#include "object.h"
#include "sound.h"

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define MAX_ENEMYATTACK (64)		//攻撃の最大数
#define ATTACK_TIME (150)			//円が現れてから攻撃が行われるまでの長さ
#define ATTACK_TIME2 (180)			//円が現れてから攻撃が行われるまでの長さ
#define ATTACK_SIZE (400)			//円の大きさ
#define ATTACK_SIZE2 (1000)			//円の大きさ
#define ENEMYATTACK_DAMAGE (1500)	//敵の攻撃1のダメージ
#define ENEMYATTACK_DAMAGE2 (2000)	//敵の攻撃2のダメージ


////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemyAttack[ENEMYATTACKTYPE_MAX];		//頂点情報
LPDIRECT3DTEXTURE9 g_pTextureEnemyAttack = NULL;						//テクスチャ情報
ENEMYATTACK g_aEnemyAttack[MAX_ENEMYATTACK][ENEMYATTACKTYPE_MAX];		//敵の攻撃

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

	//変数の初期化
	for (int nCntAttack = 0; nCntAttack < MAX_ENEMYATTACK; nCntAttack++)
	{
		for (int nCntAttack2 = 0; nCntAttack2 < ENEMYATTACKTYPE_MAX; nCntAttack2++)
		{
			g_aEnemyAttack[nCntAttack][nCntAttack2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemyAttack[nCntAttack][nCntAttack2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemyAttack[nCntAttack][nCntAttack2].bUse = false;
		}
	}

	for (int nCntAttack2 = 0; nCntAttack2 < ENEMYATTACKTYPE_MAX; nCntAttack2++)
	{
		//頂点バッファの生成
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_ENEMYATTACK, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffEnemyAttack[nCntAttack2], NULL)))
		{
			return E_FAIL;
		}

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffEnemyAttack[nCntAttack2]->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntAttack = 0; nCntAttack < MAX_ENEMYATTACK; nCntAttack++)
		{	
			//頂点座標の設定
			switch (nCntAttack2)
			{
			case ENEMYATTACKTYPE_1:
				SetVertexAttack(nCntAttack);
				break;

			case ENEMYATTACKTYPE_2:
				SetVertexAttack2(nCntAttack);
			}

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
		g_pVtxBuffEnemyAttack[nCntAttack2]->Unlock();
	}

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitEnemyAttack(void)
{
	//頂点バッファの開放
	for (int nCntAttack = 0; nCntAttack < ENEMYATTACKTYPE_MAX; nCntAttack++)
	{
		if (g_pVtxBuffEnemyAttack[nCntAttack] != NULL)
		{
			g_pVtxBuffEnemyAttack[nCntAttack]->Release();	//開放
			g_pVtxBuffEnemyAttack[nCntAttack] = NULL;		//初期化
		}
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
	//敵の攻撃の処理
	EnemyAttack();
	EnemyAttack2();
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
		for(int nCntAttack2 = 0; nCntAttack2 < ENEMYATTACKTYPE_MAX; nCntAttack2++)
		if (g_aEnemyAttack[nCntAttack][nCntAttack2].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aEnemyAttack[nCntAttack][nCntAttack2].mtxworld);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aEnemyAttack[nCntAttack][nCntAttack2].pos.x, g_aEnemyAttack[nCntAttack][nCntAttack2].pos.y, g_aEnemyAttack[nCntAttack][nCntAttack2].pos.z);
			D3DXMatrixMultiply(&g_aEnemyAttack[nCntAttack][nCntAttack2].mtxworld, &g_aEnemyAttack[nCntAttack][nCntAttack2].mtxworld, &mtxTrans);

			//ワールドマトリックス
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemyAttack[nCntAttack][nCntAttack2].mtxworld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffEnemyAttack[nCntAttack2], 0, sizeof(VERTEX_3D));

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
//敵の攻撃のセット処理�@
////////////////////////////////////////////////////////////////////////////////
void SetEnemyAttack(void)
{
	//変数宣言
	PLAYER *player = GetPlayer();

	for (int nCntAttack2 = 0; nCntAttack2 < 5; nCntAttack2++)
	{
		for (int nCntAttack = 0; nCntAttack < MAX_ENEMYATTACK; nCntAttack++)
		{
			if (g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_1].bUse == false)
			{
				if (nCntAttack2 == 0)
				{	//1つはプレイヤーの足元に
					g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_1].pos = D3DXVECTOR3(player->pos.x, 1.0f, player->pos.z);
				}
				else
				{	//他はフィールド上にランダムで
					g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_1].pos = D3DXVECTOR3((float)GetRandom(-2000, 2000), 1.0f, (float)GetRandom(-2000, 2000));
				}
				g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_1].bUse = true;
				g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_1].nTime = ATTACK_TIME;
				break;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//敵の攻撃をセット�A
////////////////////////////////////////////////////////////////////////////////
void SetEnemyAttack2(void)
{
	ENEMY *enemy = GetEnemy();

	for (int nCntAttack = 0; nCntAttack < MAX_ENEMYATTACK; nCntAttack++)
	{
		if (g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_2].bUse == false)
		{	//敵の足元に大きめの攻撃
			g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_2].pos = D3DXVECTOR3(enemy->pos.x, 1.0f, enemy->pos.z);
			g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_2].bUse = true;
			g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_2].nTime = ATTACK_TIME2;
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//敵の攻撃�@
////////////////////////////////////////////////////////////////////////////////
void EnemyAttack(void)
{
	PLAYER *player = GetPlayer();
	D3DXVECTOR3 Distance[MAX_ENEMYATTACK];
	float fDis[MAX_ENEMYATTACK];
	float fSize = powf(ATTACK_SIZE, 2.0f);
	int nAttack = ENEMYATTACK_DAMAGE;

	for (int nCntAttack = 0; nCntAttack < MAX_ENEMYATTACK; nCntAttack++)
	{
		if (g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_1].bUse == true)
		{
			//プレイヤーと攻撃範囲の距離を変数に代入
			Distance[nCntAttack].x = (player->pos.x - g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_1].pos.x);
			Distance[nCntAttack].z = (player->pos.z - g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_1].pos.z);

			//プレイヤーと攻撃範囲の距離を2乗
			Distance[nCntAttack].x = powf(Distance[nCntAttack].x, 2.0f);
			Distance[nCntAttack].z = powf(Distance[nCntAttack].z, 2.0f);

			//プレイヤーの大きさの分をマイナス
			Distance[nCntAttack].x -= powf(PLAYER_SIZEXZ, 2.0f);
			Distance[nCntAttack].z -= powf(PLAYER_SIZEXZ, 2.0f);

			//x座標とz座標の距離を合わせる
			fDis[nCntAttack] = Distance[nCntAttack].x + Distance[nCntAttack].z;
			
			//攻撃を実際に行うまでの時間経過
			g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_1].nTime--;

			if (g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_1].nTime <= 0)
			{	//nTimeが0以下になった時
				if (fDis[nCntAttack] <= fSize)
				{	//プレイヤーと攻撃との距離が攻撃範囲以下になっているとき
					if (player->nLife - nAttack < 0)
					{	//攻撃が敵の残りHPを超えたとき0までのダメージに変換
						nAttack = player->nLife;
					}
					
					//ダメージの処理
					player->nLife -= nAttack;
					SetHitEffect(player->pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
				//攻撃範囲の破棄と攻撃演出
				g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_1].bUse = false;
				SetObject(g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_1].pos);
				PlaySound(SOUND_LABEL_SE_ENEATTACK);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//敵の攻撃�A
////////////////////////////////////////////////////////////////////////////////
void EnemyAttack2(void)
{
	PLAYER *player = GetPlayer();
	D3DXVECTOR3 Distance[MAX_ENEMYATTACK];
	float fDis[MAX_ENEMYATTACK];
	float fSize = powf(ATTACK_SIZE2, 2.0f);
	int nAttack = ENEMYATTACK_DAMAGE2;

	for (int nCntAttack = 0; nCntAttack < MAX_ENEMYATTACK; nCntAttack++)
	{
		if (g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_2].bUse == true)
		{
			//プレイヤーと攻撃範囲の距離を変数に代入
			Distance[nCntAttack].x = (player->pos.x - g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_2].pos.x);
			Distance[nCntAttack].z = (player->pos.z - g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_2].pos.z);

			//プレイヤーと攻撃範囲の距離を2乗
			Distance[nCntAttack].x = powf(Distance[nCntAttack].x, 2.0f);
			Distance[nCntAttack].z = powf(Distance[nCntAttack].z, 2.0f);

			//プレイヤーの大きさの分をマイナス
			Distance[nCntAttack].x -= powf(PLAYER_SIZEXZ, 2.0f);
			Distance[nCntAttack].z -= powf(PLAYER_SIZEXZ, 2.0f);

			//x座標とz座標の距離を合わせる
			fDis[nCntAttack] = Distance[nCntAttack].x + Distance[nCntAttack].z;

			//攻撃を実際に行うまでの時間経過
			g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_2].nTime--;

			if (g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_2].nTime <= 0)
			{	//nTimeが0以下になった時
				if (fDis[nCntAttack] <= fSize)
				{	//プレイヤーと攻撃との距離が攻撃範囲以下になっているとき
					if (player->nLife - nAttack < 0)
					{	//攻撃が敵の残りHPを超えたとき0までのダメージに変換
						nAttack = player->nLife;
					}

					//ダメージの処理
					player->nLife -= nAttack;
					SetHitEffect(player->pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}

				//SE再生
				PlaySound(SOUND_LABEL_SE_ENEATTACK2);

				//攻撃範囲の破棄
				g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_2].bUse = false;

				/*D3DXVECTOR3 vector = g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_2].pos - player->pos;
				float fAngle = atan2f(vector.x, vector.z);

				player->posDest.x += sinf(fAngle) * -500;
				player->posDest.z += cosf(fAngle) * -500;*/
			}
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
	g_pVtxBuffEnemyAttack[ENEMYATTACKTYPE_1]->Lock(0, 0, (void**)&pVtx, 0);

	//pVtxのポインタ調節
	pVtx += nIdx * 4;

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_1].pos.x - ATTACK_SIZE, 1, g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_1].pos.z - ATTACK_SIZE);
	pVtx[1].pos = D3DXVECTOR3(g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_1].pos.x - ATTACK_SIZE, 1, g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_1].pos.z + ATTACK_SIZE);
	pVtx[2].pos = D3DXVECTOR3(g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_1].pos.x + ATTACK_SIZE, 1, g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_1].pos.z - ATTACK_SIZE);
	pVtx[3].pos = D3DXVECTOR3(g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_1].pos.x + ATTACK_SIZE, 1, g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_1].pos.z + ATTACK_SIZE);

	//頂点バッファをアンロックする
	g_pVtxBuffEnemyAttack[ENEMYATTACKTYPE_1]->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//頂点座標の設定
////////////////////////////////////////////////////////////////////////////////
void SetVertexAttack2(int nIdx)
{
	//変数宣言
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemyAttack[ENEMYATTACKTYPE_2]->Lock(0, 0, (void**)&pVtx, 0);

	//pVtxのポインタ調節
	pVtx += nIdx * 4;

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_2].pos.x - ATTACK_SIZE2, 1, g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_2].pos.z - ATTACK_SIZE2);
	pVtx[1].pos = D3DXVECTOR3(g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_2].pos.x - ATTACK_SIZE2, 1, g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_2].pos.z + ATTACK_SIZE2);
	pVtx[2].pos = D3DXVECTOR3(g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_2].pos.x + ATTACK_SIZE2, 1, g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_2].pos.z - ATTACK_SIZE2);
	pVtx[3].pos = D3DXVECTOR3(g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_2].pos.x + ATTACK_SIZE2, 1, g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_2].pos.z + ATTACK_SIZE2);

	//頂点バッファをアンロックする
	g_pVtxBuffEnemyAttack[ENEMYATTACKTYPE_2]->Unlock();
}