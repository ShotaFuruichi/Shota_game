//-----------------------------------------------------------------
//
//	UI情報読み込み (LoadUIdata.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#include "LoadUIData.h"
#include "texture_set.h"
#include "press_anybutton.h"

//-----------------------------------------------------------------
// 構造体の宣言
//-----------------------------------------------------------------
typedef struct
{
	int nCntTexture = 0;		// テクスチャ数
}UIsetCounter;

typedef struct
{
	bool bTexSet = false;
	bool bSelectModeSet = false;
	bool bPressAnyButtonSet = false;
}UIset;

typedef struct
{
	D3DXVECTOR3 pos;	// 位置情報
	D3DXVECTOR3 rot;	// 向き情報
	D3DXVECTOR3 move;	// 移動量情報
	D3DXCOLOR col;		// 色
	float fRemoveAlpha;	// α値の減少量
	float fWidth;		// 幅
	float fHeight;		// 高さ
	float fWidthDest;	// 目的の幅
	float fHeightDest;	// 目的の高さ
	int nType;			// 移動タイプ
	int nTexType;		// テクスチャタイプ
}TextureSetData;

typedef struct
{
	D3DXVECTOR3 pos;	// 位置情報
	D3DXCOLOR col;		// 色
	float fWidth;		// 幅
	float fHeight;		// 高さ
	int nTexType;		// テクスチャタイプ
}SelectModeSetData;

typedef struct
{
	D3DXVECTOR3 pos;	// 位置情報
	D3DXCOLOR col;		// 色
	float fRemoveAlpha;	// α値減少量
	float fWidth;		// 幅
	float fHeight;		// 高さ
	int nTexType;		// テクスチャタイプ
}PressAnyButtonSetData;

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
UIsetCounter g_UIsetCounter;				// カウンター用
UIset g_bUIset;						// セット用
TextureSetData g_TextureData;
SelectModeSetData g_SelectModeSetData;
PressAnyButtonSetData g_PressAnyButtonSetData;

//-----------------------------------------------------------------
// UI情報の読み込み
//-----------------------------------------------------------------
void LoadUISetData(void)
{
	// テクスチャ配置情報の取得
	TextureSet *pTextureSet = GetTextureSet();

	// モードの取得
	MODE mode = GetMode();

	// FILE型のポインタ関数
	FILE *pFile;

	// ファイルを開く
	pFile = fopen(&pTextureSet->aTextName[0], "r");

	if (pFile != NULL)
	{
		// 変数宣言
		bool bGetScript = false;
		char aLine[128];
		char aText[128];

		// 変数の初期化
		g_UIsetCounter.nCntTexture = 0;

		// SCRIPTを探す
		while (fgets(aLine, 128, pFile) != NULL)
		{
			fscanf(pFile, "%s", &aText[0]);

			// SCRIPTを見つけたらそれ以降を読み込む
			if (strcmp(&aText[0], "SCRIPT") == 0)
			{
				bGetScript = true;
			}

			if (bGetScript == true)
			{
				// テキスト情報の読み込み
				LoadTextureSetTexInfo(pFile, &aText[0]);

				// テクスチャ配置情報の読み込み
				LoadTextureSetData(pFile, &aText[0]);

				// セレクトモードの配置情報の読み込み
				LoadSelectModeData(pFile, &aText[0]);

				// ボタン指示配置情報の読み込み
				LoadPressAnyButtonData(pFile, &aText[0]);

				// END_SCRIPTを見つけたら読み込みを終える
				if (strcmp(&aText[0], "END_SCRIPT") == 0)
				{
					break;
				}
			}
		}
		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{
	}
}

//-----------------------------------------------------------------
// テクスチャ情報の読み込み
//-----------------------------------------------------------------
void LoadTextureSetTexInfo(FILE *pFile, char *aText)
{
	// テクスチャ配置情報の取得
	Texture *pTexture = GetUITexture();

	// NUM_TEXTUREを見つけたらテクスチャの総数を格納
	if (strcmp(&aText[0], "NUM_TEXTURE") == 0)
	{
		fscanf(pFile, "%s %d", &aText[0], &pTexture->nNumTexture);
	}
	// TEXTURE_FILENAMEを見つけたらテクスチャのファイル名を格納
	if (strcmp(&aText[0], "TEXTURE_FILENAME") == 0 && g_UIsetCounter.nCntTexture < pTexture->nNumTexture)
	{
		fscanf(pFile, "%s %s", &aText[0], &pTexture->TextureInfo[g_UIsetCounter.nCntTexture].aTexcharName[0]);

		// テクスチャの総数だけ格納するのでカウントを増やす
		g_UIsetCounter.nCntTexture++;
	}
}

//-----------------------------------------------------------------
// テクスチャ配置情報の読み込み
//-----------------------------------------------------------------
void LoadTextureSetData(FILE *pFile, char *aText)
{
	// テクスチャ配置情報の取得
	TextureSetData *pTextureSetInfo = &g_TextureData;

	// TEXTURESETを見つけたテクスチャ配置情報を読み込む許可を与える
	if (strcmp(&aText[0], "TEXTURESET") == 0)
	{
		// 変数の初期化
		pTextureSetInfo->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pTextureSetInfo->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pTextureSetInfo->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pTextureSetInfo->col = D3DXCOLOR(0.0f, 0.0f, 0.0f,0.0f);
		pTextureSetInfo->fRemoveAlpha = 0.0f;
		pTextureSetInfo->fWidth = 0.0f; 
		pTextureSetInfo->fHeight = 0.0f; 
		pTextureSetInfo->fWidthDest = 0.0f; 
		pTextureSetInfo->fHeightDest = 0.0f; 
		pTextureSetInfo->nType = -1; 
		pTextureSetInfo->nTexType = -1;

		g_bUIset.bTexSet = true;
	}
	if (g_bUIset.bTexSet == true)
	{
		// TEXTYPEを見つけたらテクスチャ番号を格納
		if (strcmp(&aText[0], "TEXTYPE") == 0)
		{
			fscanf(pFile, "%s %d", &aText[0], &pTextureSetInfo->nTexType);
		}
		// EFFECTTYPEを見つけたらエフェクト番号を格納
		if (strcmp(&aText[0], "EFFECTTYPE") == 0)
		{
			fscanf(pFile, "%s %d", &aText[0], &pTextureSetInfo->nType);
		}
		// POSを見つけたら位置情報を格納
		if (strcmp(&aText[0], "POS") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pTextureSetInfo->pos.x,
				&pTextureSetInfo->pos.y,
				&pTextureSetInfo->pos.z);
		}
		// ROTを見つけたら向き情報を格納
		if (strcmp(&aText[0], "ROT") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pTextureSetInfo->rot.x,
				&pTextureSetInfo->rot.y,
				&pTextureSetInfo->rot.z);
		}
		// MOVEを見つけたら移動量情報を格納
		if (strcmp(&aText[0], "MOVE") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pTextureSetInfo->move.x,
				&pTextureSetInfo->move.y,
				&pTextureSetInfo->move.z);
		}
		// COLを見つけたら色情報を格納
		if (strcmp(&aText[0], "COL") == 0)
		{
			fscanf(pFile, "%s %f %f %f %f", &aText[0],
				&pTextureSetInfo->col.r,
				&pTextureSetInfo->col.g,
				&pTextureSetInfo->col.b,
				&pTextureSetInfo->col.a);
		}
		// REMOVEを見つけたらα値減少量情報を格納
		if (strcmp(&aText[0], "REMOVE") == 0)
		{
			fscanf(pFile, "%s %f", &aText[0],
				&pTextureSetInfo->fRemoveAlpha);
		}
		// SIZEを見つけたらサイズ情報を格納
		if (strcmp(&aText[0], "SIZE") == 0)
		{
			fscanf(pFile, "%s %f %f", &aText[0],
				&pTextureSetInfo->fWidth,
				&pTextureSetInfo->fHeight);
		}
		// SIZEDESTを見つけたら目的サイズ情報を格納
		if (strcmp(&aText[0], "SIZEDEST") == 0)
		{
			fscanf(pFile, "%s %f %f", &aText[0],
				&pTextureSetInfo->fWidthDest,
				&pTextureSetInfo->fHeightDest);
		}
		// END_TEXTURESETを見つけたらテクスチャ配置情報の読み込みを終える
		if (strcmp(&aText[0], "END_TEXTURESET") == 0)
		{
			// テクスチャの設置
			SetTexture(pTextureSetInfo->pos,
				pTextureSetInfo->rot,
				pTextureSetInfo->move,
				pTextureSetInfo->col,
				pTextureSetInfo->fRemoveAlpha,
				pTextureSetInfo->fWidth,
				pTextureSetInfo->fHeight,
				pTextureSetInfo->fWidthDest,
				pTextureSetInfo->fHeightDest,
				pTextureSetInfo->nType, 
				pTextureSetInfo->nTexType);

			// テクスチャ情報の読み込みを終える
			g_bUIset.bTexSet = false;
		}
	}
}

//-----------------------------------------------------------------
// セレクトモード配置情報の読み込み
//-----------------------------------------------------------------
void LoadSelectModeData(FILE *pFile, char *aText)
{
	// フィールド情報の取得
	SelectModeSetData *pSelectModeSetData = &g_SelectModeSetData;

	// SELECTMODESETを見つけたセレクトモード配置情報を読み込む許可を与える
	if (strcmp(&aText[0], "SELECTMODESET") == 0)
	{
		// 変数の初期化
		pSelectModeSetData->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pSelectModeSetData->col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pSelectModeSetData->fWidth = 0.0f;
		pSelectModeSetData->fHeight = 0.0f;
		pSelectModeSetData->nTexType = -1;

		g_bUIset.bSelectModeSet = true;
	}
	if (g_bUIset.bSelectModeSet == true)
	{
		// TEXTYPEを見つけたらテクスチャ番号を格納
		if (strcmp(&aText[0], "TEXTYPE") == 0)
		{
			fscanf(pFile, "%s %d", &aText[0], &pSelectModeSetData->nTexType);
		}
		// POSを見つけたら位置情報を格納
		if (strcmp(&aText[0], "POS") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pSelectModeSetData->pos.x,
				&pSelectModeSetData->pos.y,
				&pSelectModeSetData->pos.z);
		}
		// COLを見つけたら色情報を格納
		if (strcmp(&aText[0], "COL") == 0)
		{
			fscanf(pFile, "%s %f %f %f %f", &aText[0],
				&pSelectModeSetData->col.r,
				&pSelectModeSetData->col.g,
				&pSelectModeSetData->col.b,
				&pSelectModeSetData->col.a);
		}
		// SIZEを見つけたらサイズ情報を格納
		if (strcmp(&aText[0], "SIZE") == 0)
		{
			fscanf(pFile, "%s %f %f", &aText[0],
				&pSelectModeSetData->fWidth,
				&pSelectModeSetData->fHeight);
		}
		// END_SELECTMODESETを見つけたらセレクトモード配置情報の読み込みを終える
		if (strcmp(&aText[0], "END_SELECTMODESET") == 0)
		{			// フィールド情報の読み込みを終える
			g_bUIset.bSelectModeSet = false;
		}
	}
}

//-----------------------------------------------------------------
// ボタン指示配置情報の読み込み
//-----------------------------------------------------------------
void LoadPressAnyButtonData(FILE *pFile, char *aText)
{
	// フィールド情報の取得
	PressAnyButtonSetData *pPressAnyButtonSetData = &g_PressAnyButtonSetData;

	// PRESSANYBUTTONSETを見つけたセレクトモード配置情報を読み込む許可を与える
	if (strcmp(&aText[0], "PRESSANYBUTTONSET") == 0)
	{
		// 変数の初期化
		pPressAnyButtonSetData->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pPressAnyButtonSetData->col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pPressAnyButtonSetData->fRemoveAlpha = 0.0f;
		pPressAnyButtonSetData->fWidth = 0.0f;
		pPressAnyButtonSetData->fHeight = 0.0f;
		pPressAnyButtonSetData->nTexType = -1;

		g_bUIset.bPressAnyButtonSet = true;
	}
	if (g_bUIset.bPressAnyButtonSet == true)
	{
		// TEXTYPEを見つけたらテクスチャ番号を格納
		if (strcmp(&aText[0], "TEXTYPE") == 0)
		{
			fscanf(pFile, "%s %d", &aText[0], &pPressAnyButtonSetData->nTexType);
		}
		// POSを見つけたら位置情報を格納
		if (strcmp(&aText[0], "POS") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pPressAnyButtonSetData->pos.x,
				&pPressAnyButtonSetData->pos.y,
				&pPressAnyButtonSetData->pos.z);
		}
		// COLを見つけたら色情報を格納
		if (strcmp(&aText[0], "COL") == 0)
		{
			fscanf(pFile, "%s %f %f %f %f", &aText[0],
				&pPressAnyButtonSetData->col.r,
				&pPressAnyButtonSetData->col.g,
				&pPressAnyButtonSetData->col.b,
				&pPressAnyButtonSetData->col.a);
		}
		// REMOVEを見つけたらα値減少量情報を格納
		if (strcmp(&aText[0], "REMOVE") == 0)
		{
			fscanf(pFile, "%s %f", &aText[0],
				&pPressAnyButtonSetData->fRemoveAlpha);
		}
		// SIZEを見つけたらサイズ情報を格納
		if (strcmp(&aText[0], "SIZE") == 0)
		{
			fscanf(pFile, "%s %f %f", &aText[0],
				&pPressAnyButtonSetData->fWidth,
				&pPressAnyButtonSetData->fHeight);
		}
		// END_PRESSANYBUTTONSETを見つけたらセレクトモード配置情報の読み込みを終える
		if (strcmp(&aText[0], "END_PRESSANYBUTTONSET") == 0)
		{
			// セレクトモードの設置
			SetPressAnyButton(pPressAnyButtonSetData->pos,
				pPressAnyButtonSetData->col,
				pPressAnyButtonSetData->fRemoveAlpha,
				pPressAnyButtonSetData->fWidth,
				pPressAnyButtonSetData->fHeight,
				pPressAnyButtonSetData->nTexType);

			// フィールド情報の読み込みを終える
			g_bUIset.bPressAnyButtonSet = false;
		}
	}
}