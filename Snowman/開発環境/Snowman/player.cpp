////////////////////////////////////////////////////////////////////////////////
//
//Contents	: プレイヤーの処理 [player.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/10/13
//
////////////////////////////////////////////////////////////////////////////////
#include "game.h"
#include "player.h"
#include "input.h"
#include "Item.h"
#include "block.h"
#include "enemy.h"
#include "bullet.h"
#include "fade.h"
#include "time.h"
#include "sound.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define POS_X (DIAGONAL_X)					//中心X座標
#define POS_Y (SCREEN_HEIGHT - BLOCK_SIZE)	//中心Y座標
#define POS_Z (0)							//中心Z座標

#define SHOT_INTERVAL (50)					//射撃の間隔
#define STOP_SHOT (50)						//弾を止められる時間

#define MOVE_SPEED (3.0f)					//移動速度
#define DOWN_SPEED (0.7f)					//移動速度 * DOWN_SPEED で減速
#define ROTATE_SPEED (0.04f)				//回転の速度

#define DAMAGE_FLASH (10)					//ダメージを受けた時の点滅速度
#define DAMAGE_END (60)						//ダメージを受ける処理の終了速度
#define DEATH_TIME (30)						//死亡からフェードまでの速度

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer;		//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTexturePlayer;			//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTexturePlayer2;			//テクスチャへのポインタ
PLAYER g_Player;									//プレイヤーの情報
int g_nCounterShot = 0;								///射撃カウンター
int g_AnimCounter;
int g_AnimNum;	
int g_stage;

////////////////////////////////////////////////////////////////////////////////
//プレイヤーの初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT InitPlayer(void)
{
	//変数宣言
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	g_pVtxBuffPlayer = NULL;														//頂点バッファへのポインタ
	g_pTexturePlayer = NULL;														//テクスチャへのポインタ
	g_pTexturePlayer2 = NULL;														//テクスチャへのポインタ
	g_Player.pos = D3DXVECTOR3(POS_X, POS_Y, POS_Z);								//中心座標の設定
	g_Player.oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								//前の位置
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//回転角の設定
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//移動量
	g_Player.bJump = false;															//ジャンプしているか
	g_Player.fLength = sqrtf(DIAGONAL_X * DIAGONAL_X + DIAGONAL_Y * DIAGONAL_Y);	//対角線の長さの設定
	g_Player.fAngle = atan2f(DIAGONAL_X, DIAGONAL_Y);								//対角線の角度の設定
	g_Player.nLife = 2;																//体力の設定
	g_Player.state = PLAYERSTATE_APPER;												//状態の設定
	g_Player.nCounterState = 0;														//状態カウンタの設定
	g_Player.nCounterDisp = 0;														//表示カウンタの設定
	g_Player.bDisp = true;															//表示ON/OFFの設定
	g_Player.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);								//色の設定
	g_Player.Direction = false;														//向き
	g_AnimCounter = 0;
	g_AnimNum;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\snowman0.png", &g_pTexturePlayer);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPlayer, NULL)))
	{
		return E_FAIL;
	}
	
	//頂点情報の設定
	SetVertexPlayer();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//色の設定
	SetColorPlayer();

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//プレイヤーの終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitPlayer(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();	//開放
		g_pVtxBuffPlayer = NULL;		//初期化
	}

	//テクスチャの開放
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();	//開放
		g_pTexturePlayer = NULL;		//初期化
	}
}

////////////////////////////////////////////////////////////////////////////////
//プレイヤーの更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdatePlayer(void)
{
	STAGE stage;
	bool bClear;
	bClear = GetClear();
	stage = GetStage();

	//前回の位置の保存
	g_Player.oldpos = g_Player.pos;

	//移動処理
	MovePlayer();
	
	//敵との当たり判定
	HitPlayer();

	//射撃処理
	ShotPlayer();
	
	//ブロックの当たり判定
	ColisionBlock(&g_Player.pos, &g_Player.oldpos, &g_Player.move, DIAGONAL_X, DIAGONAL_Y);

	//通常の頂点情報の設定
	SetVertexPlayer();
	
	//アイテムとの当たり判定
	if (HitItem() == true)
	{
		switch (stage)
		{
		case STAGE_0:
			SetStageMode(STAGE_1);
			break;

		case STAGE_1:
			/*SetStageMode(STAGE_2);*/
			bClear = true;
			SetFade(FADE_OUT, MODE_RESULT);
			SetStageMode(STAGE_MAX);
			break;

		/*case STAGE_2:
			SetStageMode(STAGE_3);
			break;

		case STAGE_3:
			SetFade(FADE_OUT, MODE_RESULT);
			SetStageMode(STAGE_MAX);
			break;*/
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//プレイヤーの描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawPlayer(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ
	pDevice->SetTexture(0, g_pTexturePlayer);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

////////////////////////////////////////////////////////////////////////////////
//プレイヤーの頂点情報の設定
////////////////////////////////////////////////////////////////////////////////
void SetVertexPlayer(void)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの位置を設定
	pVtx[0].pos.x = g_Player.pos.x - DIAGONAL_X;
	pVtx[0].pos.y = g_Player.pos.y;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_Player.pos.x - DIAGONAL_X;
	pVtx[1].pos.y = g_Player.pos.y - (DIAGONAL_Y);
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_Player.pos.x + DIAGONAL_X;
	pVtx[2].pos.y = g_Player.pos.y;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_Player.pos.x + DIAGONAL_X;
	pVtx[3].pos.y = g_Player.pos.y - (DIAGONAL_Y);
	pVtx[3].pos.z = 0.0f;

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//プレイヤーの射撃処理
////////////////////////////////////////////////////////////////////////////////
void ShotPlayer(void)
{
	if (GetKeyboardPress(DIK_RETURN) == true)
	{
		g_nCounterShot++;
		if (g_nCounterShot % 2 == 0)
		{
			if (g_Player.Direction == false)
			{
				SetBullet(D3DXVECTOR3(g_Player.pos.x + DIAGONAL_X + 25.0f, g_Player.pos.y - 40, 0.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f), 10);
				PlaySoundN(SOUND_LABEL_SE_SHOT);
			}
			else if (g_Player.Direction == true)
			{
				SetBullet(D3DXVECTOR3(g_Player.pos.x - DIAGONAL_X - 25.0f, g_Player.pos.y - 40, 0.0f), D3DXVECTOR3(-10.0f, 0.0f, 0.0f), 10);
				PlaySoundN(SOUND_LABEL_SE_SHOT);
			}
		}
	}
	else
	{
		StopSound(SOUND_LABEL_SE_SHOT);
	}
}

////////////////////////////////////////////////////////////////////////////////
//プレイヤーの移動処理
////////////////////////////////////////////////////////////////////////////////
void MovePlayer(void)
{	
	//変数宣言
	VERTEX_2D *pVtx;

	g_Player.oldpos = g_Player.pos;

	if (GetKeyboardPress(DIK_D) == true)
	{
		if (GetKeyboardPress(DIK_A) == true)
		{
		}
		else
		{
			g_Player.move.x += 0.425f;

			g_Player.Direction = false;

			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

			//頂点バッファをアンロックする
			g_pVtxBuffPlayer->Unlock();
		}	
	}
	else if(GetKeyboardPress(DIK_A) == true)
	{
		if (GetKeyboardPress(DIK_D) == true)
		{
		}
		else
		{
			g_Player.move.x -= 0.425f;

			g_Player.Direction = true;

			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);

			//頂点バッファをアンロックする
			g_pVtxBuffPlayer->Unlock();
		}
	}

	if (g_Player.bJump == false)
	{
		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{
			g_Player.move.y -= 20.0f;
			g_Player.bJump = true;
			PlaySound(SOUND_LABEL_SE_JUMP);
		}
	}
	if (g_Player.state == PLAYERSTATE_DAMAGE)
	{
		g_Player.move.y -= 3.0f;
		g_Player.state = PLAYERSTATE_NORMAL;
	}

	g_Player.move.y += 1.5f;

	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y += g_Player.move.y;
	g_Player.move.x += (0.0f - g_Player.move.x) * 0.1f;

	if (g_Player.pos.y > SCREEN_HEIGHT)
	{
		g_Player.move.y = 0.0f;
		g_Player.pos.y = SCREEN_HEIGHT;
		g_Player.bJump = false;
	}

	if ((g_Player.pos.x - DIAGONAL_X) <= 0)
	{
		g_Player.pos.x = DIAGONAL_X;
	}
	if ((g_Player.pos.x + DIAGONAL_X) >= SCREEN_WIDTH)
	{
		g_Player.pos.x = (SCREEN_WIDTH - DIAGONAL_X);
	}
}

////////////////////////////////////////////////////////////////////////////////
//色の設定
////////////////////////////////////////////////////////////////////////////////
void SetColorPlayer(void)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = g_Player.col;
	pVtx[1].col = g_Player.col;
	pVtx[2].col = g_Player.col;
	pVtx[3].col = g_Player.col;

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//当たり判定
////////////////////////////////////////////////////////////////////////////////
void HitPlayer(void)
{
	//変数宣言
	float fDisX;
	float fDisY;
	float fRangeX;
	float fRangeY;
	ENEMY *pEnemy;
	pEnemy = GetEnemy();
	fRangeX = DIAGONAL_X + ENEMY_SIZEX;
	fRangeY = DIAGONAL_Y + ENEMY_SIZEY;

	//敵との当たり判定
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{	//敵を使用している場合
			switch (pEnemy->state)
			{
			case ENEMYSTATE_NORMAL:
				if (g_Player.pos.x >= pEnemy->pos.x)
				{
					fDisX = g_Player.pos.x - pEnemy->pos.x + 20;
				}
				else if (g_Player.pos.x <= pEnemy->pos.x)
				{
					fDisX = pEnemy->pos.x - g_Player.pos.x + 20;
				}

				if ((g_Player.pos.y - (DIAGONAL_Y / 2)) >= (pEnemy->pos.y - (ENEMY_SIZEY / 2)))
				{
					fDisY = (g_Player.pos.y - (DIAGONAL_Y / 2)) - (pEnemy->pos.y - (ENEMY_SIZEY / 2));
				}
				else if ((g_Player.pos.y - (DIAGONAL_Y / 2)) <= (pEnemy->pos.y - (ENEMY_SIZEY / 2)))
				{
					fDisY = (pEnemy->pos.y - (ENEMY_SIZEY / 2)) - (g_Player.pos.y - (DIAGONAL_Y / 2));
				}

				if (0 > (fDisX - fRangeX) && -60 > (fDisY - fRangeY))
				{
					g_Player.state = PLAYERSTATE_DAMAGE;
					if (pEnemy->pos.x < g_Player.pos.x)
					{
						g_Player.move.x += 8.0f;
						g_Player.bDisp = false;
					}
					else
					{
						g_Player.move.x -= 8.0f;
						g_Player.bDisp = false;
					}
				}
				break;

			case ENEMYSTATE_FREEZE:
				if ((g_Player.pos.x + DIAGONAL_X) > (pEnemy->pos.x - ENEMY_SIZEX) && (g_Player.pos.x - DIAGONAL_X) < (pEnemy->pos.x + ENEMY_SIZEX))
				{
					if (g_Player.oldpos.y <= (pEnemy->pos.y - ENEMY_SIZEY))
					{
						if (g_Player.pos.y > (pEnemy->pos.y - ENEMY_SIZEY))
						{
							g_Player.move.y = 0.0f;
							g_Player.pos.y = (pEnemy->pos.y - ENEMY_SIZEY);
							g_Player.bJump = false;
							g_Player.move.x += pEnemy->move.x / 10;
						}
					}
					if ((g_Player.oldpos.y - DIAGONAL_Y) >= pEnemy->pos.y)
					{
						if ((g_Player.pos.y - DIAGONAL_Y) < pEnemy->pos.y)
						{
							g_Player.move.y = 0.0f;
							g_Player.pos.y = g_Player.oldpos.y;
						}
					}
				}

				for (int nCnt = 0; nCnt < DIAGONAL_Y; nCnt++)
				{
					if ((g_Player.pos.y - nCnt) > (pEnemy->pos.y - ENEMY_SIZEY) && (g_Player.pos.y - nCnt) < pEnemy->pos.y)
					{
						if ((g_Player.oldpos.x + DIAGONAL_X) <= (pEnemy->pos.x - ENEMY_SIZEX))
						{
							if ((g_Player.pos.x + DIAGONAL_X) > (pEnemy->pos.x - ENEMY_SIZEX))
							{
									g_Player.pos.x = g_Player.oldpos.x;
									pEnemy->move.x += 2.0f;
							}
						}
						else if ((g_Player.oldpos.x - DIAGONAL_X) >= (pEnemy->pos.x + ENEMY_SIZEX))
						{
							if ((g_Player.pos.x - DIAGONAL_X) < (pEnemy->pos.x + ENEMY_SIZEX))
							{
									g_Player.pos.x = g_Player.oldpos.x;
									pEnemy->move.x -= 2.0f;
							}
						}
					}
				}
				break;
			}
		}
	}
}


////////////////////////////////////////////////////////////////////////////////
//アイテムとの当たり判定
////////////////////////////////////////////////////////////////////////////////
bool HitItem(void)
{
	//変数宣言
	float fDisX;
	float fDisY;
	float fRangeX;
	float fRangeY;
	ITEM *pItem;
	pItem = GetItem();
	fRangeX = DIAGONAL_X + pItem->fWidth;
	fRangeY = DIAGONAL_Y + pItem->fHeight;

	////アイテムとの当たり判定
	//for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
	//{
		if (pItem->bUse == true)
		{	//アイテムを使用している場合

			if (g_Player.pos.x >= pItem->pos.x)
			{
				fDisX = g_Player.pos.x - pItem->pos.x;
			}
			else if (g_Player.pos.x <= pItem->pos.x)
			{
				fDisX = pItem->pos.x - g_Player.pos.x;
			}

			if ((g_Player.pos.y - 80) >= pItem->pos.y)
			{
				fDisY = (g_Player.pos.y - 80) - pItem->pos.y;
			}
			else if ((g_Player.pos.y - 80) <= pItem->pos.y)
			{
				fDisY = (pItem->pos.y - 80) - g_Player.pos.y;
			}

			if (0 > (fDisX - fRangeX) && 0 > (fDisY - fRangeY))
			{	
				pItem->bUse = false;
				return true;
			}
		}
		return false;
	/*}*/
}

////////////////////////////////////////////////////////////////////////////////
//プレイヤーの情報の取得
////////////////////////////////////////////////////////////////////////////////
PLAYER *GetPlayer(void)
{
	return &g_Player;
}