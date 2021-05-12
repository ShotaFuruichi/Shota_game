//-----------------------------------------------------------------
//
// キャラセレクト (chara_select.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "chara_select.h"
#include "chara_select_frame.h"
#include "chara_select_Image.h"
#include "chara_select_bg.h"
#include "chara_select_none.h"
#include "dicision_chara.h"
#include "chara.h"
#include "player_band.h"
#include "wall.h"
#include "model_set.h"
#include "meshfield.h"
#include "sound.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"
#include "LoadSceneData.h"
#include "texture.h"
#include "texture_set.h"

//-----------------------------------------------------------------
// キャラセレクトの初期化処理
//-----------------------------------------------------------------
HRESULT InitCharaSelect(void)
{	
	// メッシュフィールドの初期化処理
	InitMeshField();

	// 壁の初期化処理
	InitWall();

	// テクスチャ配置の初期化処理
	InitTextureSet();

	// キャラの初期化処理
	InitCharacter();

	// キャラセレクト背景の初期化処理
	InitCharaSelectBg();

	// キャラセレクトノーンの初期化処理
	InitCharaSelectNone();

	// キャラセレクトイメージの初期化処理
	InitCharaSelectImage();

	// キャラセレクト枠の初期化処理
	InitCharaSelectFrame();

	// プレイヤーバンドの初期化処理
	InitPlayerBand();

	// キャラ決定の初期化処理
	InitDicisionChara();

	PlaySound(SOUND_LABEL_CHARASELECT);
	return S_OK;
}

//-----------------------------------------------------------------
// キャラセレクトの終了処理
//-----------------------------------------------------------------
void UninitCharaSelect(void)
{
	StopSound();
	// キャラ決定の終了処理
	UninitDicisionChara();

	// プレイヤーバンドの終了処理
	UninitPlayerBand();

	// キャラセレクト枠の終了処理
	UninitCharaSelectFrame();

	// キャラセレクトマーカーの終了処理
	UninitCharaSelectImage();

	// キャラセレクト背景の終了処理
	UninitCharaSelectNone();

	// キャラセレクトノーンの終了処理
	UninitCharaSelectBg();

	// テクスチャ配置の終了処理
	UninitTextureSet();

	// 壁の終了処理
	UninitWall();

	// メッシュフィールドの終了処理
	UninitMeshField();

	// モデル配置の終了処理
	UninitModelSet();
}

//-----------------------------------------------------------------
// キャラセレクトの更新処理
//-----------------------------------------------------------------
void UpdateCharaSelect(void)
{
	// メッシュフィールドの更新処理
	UpdateMeshField();

	// モデル配置の更新処理
	UpdateModelSet();

	// 壁の更新処理
	UpdateWall();

	// テクスチャ配置の更新処理
	UpdateTextureSet();

	// キャラの更新処理
	UpdateCharacter();

	// キャラセレクト背景の更新処理
	UpdateCharaSelectBg();

	// キャラセレクトノーンの更新処理
	UpdateCharaSelectNone();

	// キャラセレクトマーカーの更新処理
	UpdateCharaSelectImage();

	// キャラセレクト枠の更新処理
	UpdateCharaSelectFrame();

	// プレイヤーバンドの更新処理
	UpdatePlayerBand();

	// キャラ決定の更新処理
	UpdateDicisionChara();
}

//-----------------------------------------------------------------
// キャラセレクトの描画処理
//-----------------------------------------------------------------
void DrawCharaSelect(void)
{
	// メッシュフィールドの描画処理
	DrawMeshField();

	// モデル配置の描画処理
	DrawModelSet();

	// 壁の描画処理
	DrawWall();

	// キャラの描画処理
	DrawCharacter();

	// キャラセレクト背景の描画処理
	DrawCharaSelectBg();

	// プレイヤーバンドの描画処理
	DrawPlayerBand();

	// キャラセレクトノーンの描画処理
	DrawCharaSelectNone();

	// テクスチャ配置の描画処理
	DrawTextureSet();

	// キャラセレクトイメージの描画処理
	DrawCharaSelectImage();

	// キャラセレクト枠の描画処理
	DrawCharaSelectFrame();

	// キャラ決定の描画処理
	DrawDicisionChara();
}