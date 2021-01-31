////////////////////////////////////////////////////////////////////////////////
//
//Contents	: ゲーム画面の処理 [game.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/08/28
//
////////////////////////////////////////////////////////////////////////////////
#include "game.h"
#include "bg.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "player.h"
#include "score.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "effect.h"
#include "Pause.h"
#include "item.h"
#include "stdlib.h"
#include "time.h"
#include "xinput_pad.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define ENEMY_NUM (12)			//敵のfor文で使うやつ
#define ENEMY_TYPE (3)			//敵の種類数
#define ENEMY_FREQUENCY (75)	//敵の出現頻度
#define HIGH_FREQUENCY (25)		//敵の最速出現頻度
#define CHANGE_FREQUENCY (5)	//何体ごとに出現頻度を早くするか
#define ITEM_FREQUENCY (500)	//アイテムの出現頻度

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
bool g_bPause = false;			//ポーズ中かどうか	
int g_EnemyCounter;				//敵のカウンター
int g_ItemCounter;				//アイテムのカウンター
int g_EnemyFrequency;			//敵が出る感覚
int g_EnemyCount;				//敵が出る感覚を早めるためのカウンタ

////////////////////////////////////////////////////////////////////////////////
//ゲーム画面の初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT InitGame(void)
{
	g_EnemyCounter = 0;
	g_ItemCounter = 0;
	g_EnemyFrequency = ENEMY_FREQUENCY;

	//背景の初期化処理
	InitBg();

	//弾の初期化処理
	InitBullet();

	//エフェクトの初期化
	InitEffect();

	//アイテムの初期化
	InitItem();

	//プレイヤーの初期化処理
	InitPlayer();

	//敵の初期化処理
	InitEnemy();

	//爆発の初期化処理
	InitExplosion();

	//スコアの初期化
	InitScore();

	//ポーズ画面の初期化
	InitPause();

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM002);

	/*for (int nCount = 0; nCount < 10; nCount++)
	{
		SetEnemy();
	}*/

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitGame(void)
{	
	//サウンドの停止
	StopSound();

	//ポーズ画面の終了処理
	UninitPause();

	//爆発の終了処理
	UninitExplosion();

	//敵の終了処理
	UninitEnemy();

	//プレイヤーの終了処理
	UninitPlayer();

	//アイテムの終了処理
	UninitItem();

	//エフェクトの終了処理
	UninitEffect();

	//弾の終了処理
	UninitBullet();

	//背景の終了処理
	UninitBg();
}

////////////////////////////////////////////////////////////////////////////////
//更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateGame(void)
{
	FADE fade = GetFade();
	XinputGamepad *pXinput = GetXinputGamepad();

	//ポーズ処理
	if (GetKeyboardTrigger(DIK_P) == true || pXinput->bPressStart == true)
	{
		g_bPause = g_bPause ? false : true;
	}

	//各更新
	if (g_bPause == true)
	{
		UpdatePause();
	}
	else
	{
		//背景の更新処理
		UpdateBg();

		//弾の更新処理
		UpdateBullet();

		//エフェクトの更新処理
		UpdateEffect();

		//アイテムの更新処理
		UpdateItem();

		//プレイヤーの更新処理
		UpdatePlayer();

		//敵の更新処理
		UpdateEnemy();

		//爆発の更新処理
		UpdateExplosion();

		//スコアの更新処理
		UpdateScore();

		//敵出現
		g_EnemyCounter++;
		if (g_EnemyCounter % g_EnemyFrequency == 0)
		{
			SetEnemy();
			if (g_EnemyFrequency > HIGH_FREQUENCY)
			{
				g_EnemyCount++;
				if (g_EnemyCount % CHANGE_FREQUENCY == 0)
				{
					g_EnemyFrequency--;
				}
			}
		}

		//アイテム出現
		g_ItemCounter++;
		if (g_ItemCounter % ITEM_FREQUENCY == 0)
		{
			SetItem();
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawGame(void)
{
	//背景の描画処理
	DrawBg();

	//弾の描画処理
	DrawBullet();

	//エフェクトの描画処理
	DrawEffect();

	//アイテムの描画処理
	DrawItem();

	//プレイヤーの描画処理
	DrawPlayer();

	//敵の描画処理
	DrawEnemy();

	//爆発の描画処理
	DrawExplosion();

	//スコアの描画処理
	DrawScore();

	if (g_bPause == true)
	{
		DrawPause();
	}
}

////////////////////////////////////////////////////////////////////////////////
//ポーズ状態取得
////////////////////////////////////////////////////////////////////////////////
void SetPause(bool bPause)
{
	g_bPause = bPause;
}

////////////////////////////////////////////////////////////////////////////////
//ランダムな数値を取得
////////////////////////////////////////////////////////////////////////////////
float GetRandom(float min, float max)
{
	static int nNum;

	if (nNum == 0)
	{
		srand((unsigned int)time(NULL));
		nNum = 1;
	}

	return min + (int)(rand() * (max - min + 1.0f) / (1.0f + RAND_MAX));
}
