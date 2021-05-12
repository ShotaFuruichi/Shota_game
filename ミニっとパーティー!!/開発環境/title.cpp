//-----------------------------------------------------------------
//
// タイトル (title.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "title.h"
#include "title_bg.h"
#include "titlelogo.h"
#include "texture_set.h"
#include "press_anybutton.h"
#include "sound.h"
#include "setparticle.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"
#include "wall.h"
#include "model_set.h"
#include "meshfield.h"
#include "effect.h"

//-----------------------------------------------------------------
// タイトルの初期化処理
//-----------------------------------------------------------------
HRESULT InitTitle(void)
{
	// エフェクトの初期化処理
	InitEffect();

	// テクスチャ配置の初期化処理
	InitTextureSet();

	// ボタン指示の初期化処理
	InitPressAnyButton();

	// タイトルロゴの初期化処理
	InitTitlelogo();
	 
	// メッシュフィールドの初期化処理
	InitMeshField();

	// 壁の初期化処理
	InitWall();

	PlaySound(SOUND_LABEL_TITLE);

	return S_OK;
}

//-----------------------------------------------------------------
// タイトルの終了処理
//-----------------------------------------------------------------
void UninitTitle(void)
{
	StopSound();
	// 壁の終了処理
	UninitWall();

	// メッシュフィールドの終了処理
	UninitMeshField();

	// モデル配置の終了処理
	UninitModelSet();

	// タイトルロゴの終了処理
	UninitTitlelogo();

	// ボタン指示の終了処理
	UninitPressAnyButton();

	// テクスチャ配置の終了処理
	UninitTextureSet();

	// エフェクトの終了処理
	UninitEffect();
}

//-----------------------------------------------------------------
// タイトルの更新処理
//-----------------------------------------------------------------
void UpdateTitle(void)
{
	// テクスチャ配置の更新処理
	UpdateTextureSet();

	// ボタン指示の更新処理
	UpdatePressAnyButton();

	// タイトルロゴの更新処理
	UpdateTitlelogo();

	// メッシュフィールドの更新処理
	UpdateMeshField();

	// モデル配置の更新処理
	UpdateModelSet();

	// 壁の更新処理
	UpdateWall();

	// エフェクトの更新処理
	UpdateEffect();

	if (GetKeyboardTrigger(KEYINFO_OK) == true)
	{// キャラセレクト画面に遷移
		SetFade(FADE_OUT, MODE_CHARASELECT);
	}

}

//-----------------------------------------------------------------
// タイトルの描画処理
//-----------------------------------------------------------------
void DrawTitle(void)
{
	// メッシュフィールドの描画処理
	DrawMeshField();

	// モデル配置の描画処理
	DrawModelSet();

	// 壁の描画処理
	DrawWall();

	// テクスチャ配置の描画処理
	DrawTextureSet();
	
	// ボタン指示の描画処理
	DrawPressAnyButton();

	// タイトルロゴの描画処理
	DrawTitlelogo();

	// エフェクトの描画処理
	DrawEffect();
}