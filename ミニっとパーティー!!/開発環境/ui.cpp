//-----------------------------------------------------------------
//
// UI背景 (ui.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "ui.h"
#include "timer.h"
#include "timer_bg.h"
#include "player_marker.h"
#include "count_down.h"
#include "finish_game.h"

//-----------------------------------------------------------------
// UIの初期化処理
//-----------------------------------------------------------------
void InitUi(void)
{
	// タイマーの初期化処理
	InitTimer();

	// タイマー背景の初期化処理
	InitTimerBg();

	// プレイヤーマーカーの初期化処理
	InitPlayerMarker();

	// カウントダウンの初期化処理
	InitCountDown();

	// フィニッシュゲームの初期化処理
	InitFinishGame();
}

//-----------------------------------------------------------------
// UIの終了処理
//-----------------------------------------------------------------
void UninitUi(void)
{
	// フィニッシュゲームの終了処理
	UninitFinishGame();

	// カウントダウンの終了処理
	UninitCountDown();

	// プレイヤーマーカーの終了処理
	UninitPlayerMarker();

	// タイマー背景の終了処理
	UninitTimerBg();

	// タイマーの終了処理
	UninitTimer();
}

//-----------------------------------------------------------------
// UIの更新処理
//-----------------------------------------------------------------
void UpdateUi(void)
{
	// 変数宣言
	int nCountDown = GetCountDown();
	bool bFinish = GetFinishGame();

	if (nCountDown == 0 && bFinish == false)
	{
		// タイマーの更新処理
		UpdateTimer();
	}

	// タイマー背景の更新処理
	UpdateTimerBg();

	// プレイヤーマーカーの更新処理
	UpdatePlayerMarker();

	// カウントダウンの更新処理
	UpdateCountDown();

	// フィニッシュゲームの更新処理
	UpdateFinishGame();
}


//-----------------------------------------------------------------
// UIの描画処理
//-----------------------------------------------------------------
void DrawUi(void)
{
	// プレイヤーマーカーの描画処理
	DrawPlayerMarker();

	// タイマー背景の描画処理
	DrawTimerBg();

	// タイマーの描画処理
	DrawTimer();

	// カウントダウンの描画処理
	DrawCountDown();

	// フィニッシュゲームの描画処理
	DrawFinishGame();
}