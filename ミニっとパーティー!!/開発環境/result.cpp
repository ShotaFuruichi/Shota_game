//-----------------------------------------------------------------
//
// リザルト (result.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "result.h"
#include "result_logo.h"
#include "meshfield.h"
#include "player.h"
#include "wall.h"
#include "shadow.h"
#include "model_set.h"
#include "setparticle.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"
#include "sound.h"
#include "select_mode.h"

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
int g_nSkipCnt;					// リザルトからタイトルに遷移できるまでのカウント

//-----------------------------------------------------------------
// リザルトの初期化処理
//-----------------------------------------------------------------
HRESULT InitResult(void)
{
	// メッシュフィールドの初期化処理
	InitMeshField();

	// 壁の初期化処理
	InitWall();

	// プレイヤーの初期化処理
	InitPlayer();

	// リザルトロゴの初期化処理
	InitResultLogo();

	// セレクトモードの初期化処理
	InitSelectMode();

	PlaySound(SOUND_LABEL_RESULT);
	return S_OK;
}

//-----------------------------------------------------------------
// リザルトの終了処理
//-----------------------------------------------------------------
void UninitResult(void)
{
	StopSound();
	// セレクトモードの終了処理
	UninitSelectMode();

	// リザルトロゴの終了処理
	UninitResultLogo();

	// プレイヤーの終了処理
	UninitPlayer();

	// 壁の終了処理
	UninitWall();

	// メッシュフィールドの終了処理
	UninitMeshField();

	// モデル配置の終了処理
	UninitModelSet();
}

//-----------------------------------------------------------------
// リザルトの更新処理
//-----------------------------------------------------------------
void UpdateResult(void)
{
	// メッシュフィールドの更新処理
	UpdateMeshField();

	// モデル配置の更新処理
	UpdateModelSet();

	// 壁の更新処理
	UpdateWall();

	// プレイヤーの更新処理
	UpdatePlayer();

	// リザルトロゴの更新処理
	UpdateResultLogo();

	// セレクトモードの更新処理
	UpdateSelectMode();
}

//-----------------------------------------------------------------
// リザルトの描画処理
//-----------------------------------------------------------------
void DrawResult(void)
{
	// メッシュフィールドの描画処理
	DrawMeshField();

	// モデル配置の描画処理
	DrawModelSet();

	// 壁の描画処理
	DrawWall();

	// プレイヤーの描画処理
	DrawPlayer();

	// リザルトロゴの描画処理
	DrawResultLogo();

	// セレクトモードの描画処理
	DrawSelectMode();
}