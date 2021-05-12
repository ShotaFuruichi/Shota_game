//-------------------------------------------------------------------
//
// UI情報読み込みヘッダー (LoadUIData.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _LOADUIDATA_H_
#define _LOADUIDATA_H_

#include "main.h"
#include "stdio.h"

//-------------------------------------------------------------------
// プロトタイプ宣言
//-------------------------------------------------------------------
void LoadUISetData(void);								// UI情報の読み込み
void LoadTextureSetTexInfo(FILE *pFile, char *aText);	// テクスチャ情報の読み込み
void LoadTextureSetData(FILE *pFile, char *aText);		// テクスチャ配置情報の読み込み
void LoadSelectModeData(FILE *pFile, char *aText);		// セレクトモード配置情報の読み込み
void LoadPressAnyButtonData(FILE *pFile, char *aText);	// ボタン指示配置情報の読み込み

#endif