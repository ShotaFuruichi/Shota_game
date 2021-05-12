//-----------------------------------------------------------------
//
//	テクスチャの読み込み (texture.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "LoadData.h"
#include "LoadCharacterData.h"
#include "LoadSceneData.h"
#include "LoadUIData.h"
#include "texture.h"
#include "texture_set.h"
#include "chara.h"

//-----------------------------------------------------------------
// 情報の読み込み
//-----------------------------------------------------------------
void InitLoadData(void)
{
	// シーン情報の読み込み
	LoadSceneInfoText();

	// キャラ情報の読み込み
	LoadCharacterData();

	// キャラの初期化処理
	InitCharacter();
}

//-----------------------------------------------------------------
// シーン情報の更新
//-----------------------------------------------------------------
void UpdateData(void)
{
	// 各シーンのでーた読み込み
	LoadSceneData();

	// UIデータの読み込み
	LoadUISetData();

	// テクスチャの読み込み
	LoadTexture();
}

//-----------------------------------------------------------------
// データの解放
//-----------------------------------------------------------------
void ReleaseData(void)
{
	// テクスチャの解放
	ReleaseTexture();
}