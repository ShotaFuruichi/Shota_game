////////////////////////////////////////////////////////////////////////////////
//
//Contents	: プレイヤーの処理 [player.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/07/21
//
////////////////////////////////////////////////////////////////////////////////
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "enemy.h"
#include "fade.h"
#include "effect.h"
#include "explosion.h"
#include "item.h"
#include "sound.h"
#include "xinput_pad.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define POS_X (SCREEN_WIDTH / 2)	//中心X座標
#define POS_Y (780)					//中心Y座標
#define POS_Z (0)					//中心Z座標

#define DIAGONAL_X (40)				//X方向1辺の長さ
#define DIAGONAL_Y (40)				//Y方向1辺の長さ

#define SHOT_INTERVAL (50)			//射撃の間隔
#define STOP_SHOT (50)				//弾を止められる時間

#define MOVE_SPEED (4.0f)			//移動速度
#define DOWN_SPEED (0.6f)			//移動速度 * DOWN_SPEED で減速

#define PLAYER_LIFE (2)				//プレイヤーのライフ
#define DAMAGE_FLASH (10)			//ダメージを受けた時の点滅速度
#define DAMAGE_END (60)				//ダメージを受ける処理の終了速度
#define DEATH_TIME (30)				//死亡からフェードまでの速度

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTexturePlayer2 = NULL;		//テクスチャへのポインタ
PLAYER g_Player;									//プレイヤーの情報
int g_nCounterShot = 0;								///射撃カウンター
int g_nStopShot = 0;								//射撃を止めるカウンター
bool g_bStopShot = false;							//射撃中かどうか

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

	g_Player.pos = D3DXVECTOR3(POS_X, POS_Y, POS_Z);								//中心座標の設定
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//回転角の設定
	g_Player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								//回転角の設定
	g_Player.fLength = sqrtf(DIAGONAL_X * DIAGONAL_X + DIAGONAL_Y * DIAGONAL_Y);	//対角線の長さの設定
	g_Player.fAngle = atan2f(DIAGONAL_X, DIAGONAL_Y);								//対角線の角度の設定
	g_Player.nLife = 2;																//体力の設定
	g_Player.state = PLAYERSTATE_APPER;												//状態の設定
	g_Player.nCounterState = 0;														//状態カウンタの設定
	g_Player.nCounterDisp = 0;														//表示カウンタの設定
	g_Player.bDisp = true;															//表示ON/OFFの設定
	g_Player.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);								//色の設定
	g_Player.BulletType = 0;														//弾のタイプ
	g_Player.BulletResidue = 0;														//特殊弾の残弾数

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\player.png", &g_pTexturePlayer);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\player2.png", &g_pTexturePlayer2);

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
	SetColor();

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
	//変数宣言
	FADE fade= GetFade();

	//通常の頂点情報の設定
	SetVertexPlayer();

	switch (g_Player.state)
	{
	case PLAYERSTATE_APPER:
		if (fade == FADE_NONE)
		{
			g_Player.state = PLAYERSTATE_NORMAL;
		}	
		break;
	case PLAYERSTATE_NORMAL:

		//色
		SetColor();

		//移動処理
		MovePlayer();

		//射撃処理
		ShotPlayer();

		//敵との当たり判定
		HitPlayer();

		//アイテムとの当たり判定
		HitItem();

		break;

	case PLAYERSTATE_DAMAGE:

		//移動処理
		MovePlayer();

		//射撃処理
		ShotPlayer();

		g_Player.nCounterState++;
		if (g_Player.nLife > 1)
		{	//ライフが2以上残っているとき
			if (g_Player.nCounterState % DAMAGE_FLASH == 0)
			{
				if (g_Player.col.g == 1.0f && g_Player.col.b == 1.0f)
				{
					g_Player.col.g = 0.0f;
					g_Player.col.b = 0.0f;
				}
				else if (g_Player.col.g == 0.0f && g_Player.col.b == 0.0f)
				{
					g_Player.col.g = 1.0f;
					g_Player.col.b = 1.0f;
				}
				SetColor();
			}

			if (g_Player.nCounterState == DAMAGE_END)
			{	
				g_Player.col.g = 1.0f;
				g_Player.col.b = 1.0f;
				g_Player.nLife--;
				g_Player.nCounterState = 0;
				g_Player.state = PLAYERSTATE_NORMAL;
			}
		}
		else if (g_Player.nLife == 1)
		{	//ライフが残り1の時
			g_Player.state = PLAYERSTATE_DEATH;
			PlaySound(SOUND_LABEL_SE_DEATH);
		}
		break;

	case PLAYERSTATE_DEATH:
		g_Player.bDisp = false;
		g_Player.nCounterDisp++;
		if (g_Player.nCounterDisp == 0)
		{
			SetExplosion(g_Player.pos);
		}
		
		if (g_Player.nCounterDisp == DEATH_TIME)
		{
			//画面遷移
			if (fade == FADE_NONE)
			{
				SetFade(FADE_OUT, MODE_RESULT);
			}
			break;
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

	//テクスチャの設定
	if (g_Player.nLife == 1 && g_Player.state == PLAYERSTATE_NORMAL)
	{
		pDevice->SetTexture(0, g_pTexturePlayer2);
	}
	else
	{
		pDevice->SetTexture(0, g_pTexturePlayer);
	}

	if(g_Player.bDisp == true)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
	
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
	pVtx[0].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI * 0.00f - g_Player.fAngle)) * g_Player.fLength;
	pVtx[0].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI * 0.00f - g_Player.fAngle)) * g_Player.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI * 1.00f + g_Player.fAngle)) * g_Player.fLength;
	pVtx[1].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI * 1.00f + g_Player.fAngle)) * g_Player.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI * 0.00f + g_Player.fAngle)) * g_Player.fLength;
	pVtx[2].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI * 0.00f + g_Player.fAngle)) * g_Player.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI * 1.00f - g_Player.fAngle)) * g_Player.fLength;
	pVtx[3].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI * 1.00f - g_Player.fAngle)) * g_Player.fLength;
	pVtx[3].pos.z = 0.0f;

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//プレイヤーの射撃処理
////////////////////////////////////////////////////////////////////////////////
void ShotPlayer(void)
{

	//シフトを押した
	if (g_nStopShot <= STOP_SHOT)
	{
		if (GetKeyboardPress(DIK_SPACE) == true)
		{
			g_bStopShot = true;
		}
	}
	
	if (g_bStopShot == false)
	{	
		if (g_nStopShot > 0)
		{
			g_nStopShot--;
		}

		g_nCounterShot++;
		if (g_nCounterShot % SHOT_INTERVAL == 0)
		{
			SetBullet(g_Player.pos, D3DXVECTOR3(sinf(D3DX_PI - g_Player.rot.z) * -10.0f, cosf(D3DX_PI - g_Player.rot.z) * 10.0f, 0.0f), 40, g_Player.BulletType);

			if (g_Player.BulletType == 1)
			{
				g_Player.BulletResidue++;
				if (g_Player.BulletResidue == 30)
				{
					g_Player.BulletType = 0;
					g_Player.BulletResidue = 0;
				}
			}
		}
	}
	else if (g_bStopShot == true)
	{
		g_nStopShot++;
		if (g_nStopShot >= STOP_SHOT)
		{
			g_nStopShot += STOP_SHOT;
		}
		g_bStopShot = false;
	}
}

////////////////////////////////////////////////////////////////////////////////
//プレイヤーの移動処理
////////////////////////////////////////////////////////////////////////////////
void MovePlayer(void)
{
	//変数宣言
	XinputGamepad *pXinput = GetXinputGamepad();

	//向いている方向へ移動
	if (GetKeyboardPress(DIK_LSHIFT) == true || GetKeyboardPress(DIK_RSHIFT) == true || pXinput->bPressB == true)
	{	//左シフトを押している時は減速する
		g_Player.pos += D3DXVECTOR3(sinf(D3DX_PI - g_Player.rot.z) * -(MOVE_SPEED * DOWN_SPEED), cosf(D3DX_PI - g_Player.rot.z) * (MOVE_SPEED * DOWN_SPEED), 0.0f);
	}
	else
	{	//通常移動
		g_Player.pos += D3DXVECTOR3(sinf(D3DX_PI - g_Player.rot.z) * -MOVE_SPEED, cosf(D3DX_PI - g_Player.rot.z) * MOVE_SPEED, 0.0f);
	}

	//画面外に出ないようにする
	if (g_Player.pos.x < (0 + DIAGONAL_X))
	{
		g_Player.pos.x = (0 + DIAGONAL_X);
		g_Player.state = PLAYERSTATE_DEATH;
		PlaySound(SOUND_LABEL_SE_DEATH);
		SetExplosion(g_Player.pos);
	}
	else if (g_Player.pos.x > (SCREEN_WIDTH - DIAGONAL_X))
	{
		g_Player.pos.x = (SCREEN_WIDTH - DIAGONAL_X);
		g_Player.state = PLAYERSTATE_DEATH;
		PlaySound(SOUND_LABEL_SE_DEATH);
		SetExplosion(g_Player.pos);
	}

	if (g_Player.pos.y < (0 + DIAGONAL_Y))
	{
		g_Player.pos.y = (0 + DIAGONAL_Y);
		g_Player.state = PLAYERSTATE_DEATH;
		PlaySound(SOUND_LABEL_SE_DEATH);
		SetExplosion(g_Player.pos);
	}
	else if (g_Player.pos.y > (SCREEN_HEIGHT - DIAGONAL_Y))
	{
		g_Player.pos.y = (SCREEN_HEIGHT - DIAGONAL_Y);
		g_Player.state = PLAYERSTATE_DEATH;
		PlaySound(SOUND_LABEL_SE_DEATH);
		SetExplosion(g_Player.pos);
	}

	if (g_Player.rotDest.z - g_Player.rot.z < -D3DX_PI)
	{// -3.14fより小さくなったとき値を3.14fにする
		g_Player.rotDest.z += D3DX_PI * 2.0f;
	}
	else if (g_Player.rotDest.z - g_Player.rot.z > D3DX_PI)
	{// 3.14fより大きくなったとき値を-3.14fにする
		g_Player.rotDest.z -= D3DX_PI * 2.0f;
	}
	// 向きの更新
	g_Player.rot.z += (g_Player.rotDest.z - g_Player.rot.z) * 0.08f;

	if (g_Player.rot.z < -D3DX_PI)
	{// -3.14fより小さくなったとき値に3.14fにする
		g_Player.rot.z += D3DX_PI * 2.0f;
	}
	else if (g_Player.rot.z > D3DX_PI)
	{// 3.14fより大きくなったとき値を-3.14fにする
		g_Player.rot.z -= D3DX_PI * 2.0f;
	}

	//回転
	if (pXinput->bPressLStick == true)
	{
		g_Player.rotDest.z = pXinput->fAngle;
	}

	if (GetKeyboardPress(DIK_W) == TRUE || pXinput->bPressUP == true)
	{
		if (GetKeyboardPress(DIK_A) == TRUE || pXinput->bPressLEFT == true)
		{
			g_Player.rotDest.z = D3DXToRadian(45);
		}
		else if (GetKeyboardPress(DIK_D) == TRUE || pXinput->bPressRIGHT == true)
		{
			g_Player.rotDest.z = D3DXToRadian(-45);
		}
		else
		{
			g_Player.rotDest.z = 0.0f;
		}
	}
	else if (GetKeyboardPress(DIK_S) == TRUE || pXinput->bPressDOWN == true)
	{
		if (GetKeyboardPress(DIK_A) == TRUE || pXinput->bPressLEFT == true)
		{
			g_Player.rotDest.z = D3DXToRadian(135);
		}
		else if (GetKeyboardPress(DIK_D) == TRUE || pXinput->bPressRIGHT == true)
		{
			g_Player.rotDest.z = D3DXToRadian(-135);
		}
		else
		{
			g_Player.rotDest.z = D3DX_PI;
		}
	}
	else if (GetKeyboardPress(DIK_A) == TRUE || pXinput->bPressLEFT == true)
	{
		g_Player.rotDest.z = (D3DX_PI / 2);
	}
	else if (GetKeyboardPress(DIK_D) == TRUE || pXinput->bPressRIGHT == true)
	{
		g_Player.rotDest.z = (-D3DX_PI / 2);
	}
}

////////////////////////////////////////////////////////////////////////////////
//色の設定
////////////////////////////////////////////////////////////////////////////////
void SetColor(void)
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
	float fRangeX2;
	float fRangeY2;
	ENEMY *pEnemy;
	pEnemy = GetEnemy();
	fRangeX = DIAGONAL_X + ENEMY_SIZE;
	fRangeY = DIAGONAL_Y + ENEMY_SIZE;
	fRangeX2 = DIAGONAL_X + BIGENEMY_SIZE;
	fRangeY2 = DIAGONAL_Y + BIGENEMY_SIZE;

	//敵との当たり判定
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{	//敵を使用している場合

			if (g_Player.pos.x >= pEnemy->pos.x)
			{
				fDisX = g_Player.pos.x - pEnemy->pos.x;
			}
			else if (g_Player.pos.x <= pEnemy->pos.x)
			{
				fDisX = pEnemy->pos.x - g_Player.pos.x;
			}

			if (g_Player.pos.y >= pEnemy->pos.y)
			{
				fDisY = g_Player.pos.y - pEnemy->pos.y;
			}
			else if (g_Player.pos.y <= pEnemy->pos.y)
			{
				fDisY = pEnemy->pos.y - g_Player.pos.y;
			}

			switch (pEnemy->nType)
			{
			case ENEMYTYPE_BIG:
				if (0 > (fDisX - fRangeX2) && 0 > (fDisY - fRangeY2))
				{
					g_Player.state = PLAYERSTATE_DAMAGE;
					pEnemy->bUse = false;
					pEnemy->bDisp = false;
					//爆発再生
					SetExplosion(pEnemy->pos);
					PlaySound(SOUND_LABEL_SE_HIT);
				}
				break;

			default:
				if (0 > (fDisX - fRangeX) && 0 > (fDisY - fRangeY))
				{
					g_Player.state = PLAYERSTATE_DAMAGE;
					pEnemy->bUse = false;
					pEnemy->bDisp = false;
					//爆発再生
					SetExplosion(pEnemy->pos);
					PlaySound(SOUND_LABEL_SE_HIT);
				}
				break;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//アイテムとの当たり判定
////////////////////////////////////////////////////////////////////////////////
void HitItem(void)
{
	//変数宣言
	float fDisX;
	float fDisY;
	float fRangeX;
	float fRangeY;
	ITEM *pItem;
	pItem = GetItem();
	fRangeX = DIAGONAL_X + ITEM_SIZEX;
	fRangeY = DIAGONAL_Y + ITEM_SIZEY;

	//アイテムとの当たり判定
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
	{
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

			if (g_Player.pos.y >= pItem->pos.y)
			{
				fDisY = g_Player.pos.y - pItem->pos.y;
			}
			else if (g_Player.pos.y <= pItem->pos.y)
			{
				fDisY = pItem->pos.y - g_Player.pos.y;
			}

			if (0 > (fDisX - fRangeX) && 0 > (fDisY - fRangeY))
			{
				g_Player.BulletType = pItem->nType;
				g_Player.BulletResidue = 0;
				pItem->bUse = false;
				pItem->bDisp = false;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//プレイヤーの情報の取得
////////////////////////////////////////////////////////////////////////////////
PLAYER *GetPlayer(void)
{
	return &g_Player;
}