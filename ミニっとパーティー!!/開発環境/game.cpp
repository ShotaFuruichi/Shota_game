//-----------------------------------------------------------------
//
// ゲームメイン (game.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "game.h"
#include "meshfield.h"
#include "player.h"
#include "wall.h"
#include "ui.h"
#include "shadow.h"
#include "model_set.h"
#include "effect.h"
#include "setparticle.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"
#include "timer.h"
#include "Bomb.h"
#include "pause.h"
#include "finish_game.h"
#include "sound.h"

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
bool g_bPause = false;
int g_ResultCount;

//-----------------------------------------------------------------
// ベースの初期化処理
//-----------------------------------------------------------------
HRESULT InitGame(void)
{
	g_ResultCount = 0;

	// 影の初期化処理
	InitShadow();

	// プレイヤーの初期化処理
	InitPlayer();

	// メッシュフィールドの初期化処理
	InitMeshField();

	// 壁の初期化処理
	InitWall();

	// ボムの初期化処理
	InitBomb();

	// エフェクトの初期化処理
	InitEffect();

	// UIの初期化処理
	InitUi();

	// ポーズ画面の初期化処理
	InitPause();

	PlaySound(SOUND_LABEL_GAME);

	return S_OK;
}

//-----------------------------------------------------------------
// ベースの終了処理
//-----------------------------------------------------------------
void UninitGame(void)
{
	StopSound();
	// ポーズ画面の終了処理
	UninitPause();

	// UIの終了処理
	UninitUi();

	// エフェクトの終了処理
	UninitEffect();

	// ボムの終了処理
	UninitBomb();

	// 壁の終了処理
	UninitWall();

	// メッシュフィールドの終了処理
	UninitMeshField();

	// モデル配置の終了処理
	UninitModelSet();

	// 影の終了処理
	UninitShadow();

	// プレイヤーの終了処理
	UninitPlayer();
}

//-----------------------------------------------------------------
// ベースの更新処理
//-----------------------------------------------------------------
void UpdateGame(void)
{
	// 変数宣言
	int nTimer = GetTimer();
	bool bFinish = GetFinishGame();

	if ((GetKeyboardTrigger(KEYINFO_PAUSE) == true || GetJoypadTrigger(PLAYER_1,JPINFO_PAUSE)) && nTimer < 60)
	{
		g_bPause = g_bPause ? false : true;
	}
	if (g_bPause == false)
	{
		// メッシュフィールドの更新処理
		UpdateMeshField();

		// モデル配置の更新処理
		UpdateModelSet();

		// 壁の更新処理
		UpdateWall();

		// プレイヤーの更新処理
		UpdatePlayer();

		// 影の更新処理
		UpdateShadow();

		// エフェクトの更新処理
		UpdateEffect();

		if (bFinish != true)
		{
			// ボムの更新処理
			UpdateBomb();
		}
	} 
	else
	{
		// ポーズ画面の更新処理
		UpdatePause();
	}
	if (g_bPause == false)
	{
		// UIの更新処理
		UpdateUi();
	}

	if (bFinish == true)
	{
		if (g_ResultCount == 60)
		{
			// 画面モードの初期化処理
			SetFade(FADE_OUT, MODE_RESULT);
		}
		g_ResultCount++;
	}
}

//-----------------------------------------------------------------
// ベースの描画処理
//-----------------------------------------------------------------
void DrawGame(void)
{
	// メッシュフィールドの描画処理
	DrawMeshField();

	// モデル配置の描画処理
	DrawModelSet();

	// プレイヤーの描画処理
	DrawPlayer();

	// 壁の描画処理
	DrawWall();

	// ボムの描画処理
	DrawBomb();
	DrawBombWarnMark();

	// エフェクトの描画処理
	DrawEffect();

	// 影の描画処理
	DrawShadow();

	// UIの描画処理
	DrawUi();

	if (g_bPause == true)
	{
		// ポーズ画面の描画処理
		DrawPause();
	}
}

//-------------------------------------------------------------------
// ポーズの移り替わり
//-------------------------------------------------------------------
void SetPause(bool bPause)
{
	g_bPause = bPause;
}