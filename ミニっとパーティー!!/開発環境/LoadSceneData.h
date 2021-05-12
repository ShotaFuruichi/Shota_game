//-------------------------------------------------------------------
//
// テキスト読み込みヘッダー (LoadSceneData.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _LOADSCENEDATA_H_
#define _LOADSCENEDATA_H_

#include "main.h"
#include "stdio.h"

//-------------------------------------------------------------------
// プロトタイプ宣言
//-------------------------------------------------------------------
void LoadSceneInfoText(void);	// シーン情報テキストの読み込み

void LoadSceneData(void);		// シーンデータの読み込み

void LoadUIsetInfoText(FILE *pFile, char *aText);			// UIセット情報テキストの読み込み
void LoadTextureInfo(FILE *pFile, char *aText);				// テクスチャ情報の読み込み
void LoadModelInfo(FILE *pFile, char *aText);				// モデル情報の読み込み
void LoadCameraInfo(FILE *pFile, char *aText);				// カメラ情報の読み込み
void LoadLightInfo(FILE *pFile, char *aText);				// ライト情報の読み込み
void LoadFieldInfo(FILE *pFile, char *aText);				// フィールド情報の読み込み
void LoadWallInfo(FILE *pFile, char *aText);				// 壁情報の読み込み
void LoadModelSetInfo(FILE *pFile, char *aText);			// モデル配置情報の読み込み
void LoadPlayerSetInfo(FILE *pFile, char *aText);			// プレイヤー配置情報の読み込み

#endif