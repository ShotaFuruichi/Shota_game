//-----------------------------------------------------------------
//
// チュートリアル (tutorial.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "tutorial.h"
#include "tutorial_bg.h"
#include "loadscreen.h"
#include "sound.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"
#include "wall.h"
#include "model_set.h"
#include "meshfield.h"

//-----------------------------------------------------------------
// チュートリアルの初期化処理
//-----------------------------------------------------------------
HRESULT InitTutorial(void)
{
	// チュートリアル画面背景の初期化処理
	InitTutorialBg();

	// メッシュフィールドの初期化処理
	InitMeshField();

	// 壁の初期化処理
	InitWall();

	InitLoadScreen();

	return S_OK;
}

//-----------------------------------------------------------------
// チュートリアルの終了処理
//-----------------------------------------------------------------
void UninitTutorial(void)
{
	UninitLoadScreen();

	// 壁の終了処理
	UninitWall();

	// メッシュフィールドの終了処理
	UninitMeshField();

	// モデル配置の終了処理
	UninitModelSet();

	// チュートリアル画面背景の終了処理
	UninitTutorialBg();
}

//-----------------------------------------------------------------
// チュートリアルの更新処理
//-----------------------------------------------------------------
void UpdateTutorial(void)
{
	// チュートリアル画面背景の更新処理
	UpdateTutorialBg();

	// メッシュフィールドの更新処理
	UpdateMeshField();

	// モデル配置の更新処理
	UpdateModelSet();

	// 壁の更新処理
	UpdateWall();

	UpdateLoadScreen();

	if (GetKeyboardTrigger(KEYINFO_OK) == true)
	{// ゲーム画面に遷移
		SetFade(FADE_OUT, MODE_GAME);
	}
}

//-----------------------------------------------------------------
// チュートリアルの描画処理
//-----------------------------------------------------------------
void DrawTutorial(void)
{
	// チュートリアル画面背景の描画処理
	DrawTutorialBg();

	// メッシュフィールドの描画処理
	DrawMeshField();

	// モデル配置の描画処理
	DrawModelSet();

	// 壁の描画処理
	DrawWall();

	DrawLoadScreen();
}