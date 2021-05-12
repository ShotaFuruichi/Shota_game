//-----------------------------------------------------------------
//
//	テキスト読み込み (LoadText.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#include "LoadSceneData.h"
#include "texture_set.h"
#include "texture.h"
#include "model_set.h"
#include "shadow.h"
#include "player.h"
#include "camera.h"
#include "light.h"
#include "wall.h"
#include "meshfield.h"

//-----------------------------------------------------------------
// 構造体の宣言
//-----------------------------------------------------------------
typedef struct
{
	int nCntTexture = 0;		// テクスチャ数
	int nCntModel = 0;			// モデル数
	int nCntCamera = 0;			// カメラ数
	int nCntLight = 0;			// ライト数
	int nCntPlayer = 0;			// プレイヤー数
}Counter;

typedef struct
{
	bool bCameraSet = false;
	bool bLightSet = false;
	bool bFieldSet = false;
	bool bWallSet = false;
	bool bModelSet = false;
	bool bPlayerSet = false;
}Set;

typedef struct
{
	D3DXVECTOR3 pos;	// 位置情報
	D3DXVECTOR3 rot;	// 向き情報
	int nFieldX;		// 壁の数(列)
	int nFieldZ;		// 壁の数(行)
	float fWidth;		// 幅
	float fDepth;		// 奥行
	int nIdxtexture;	// 何番目のテクスチャか
}MeshFieldData;

typedef struct
{
	D3DXVECTOR3 pos;		// 位置情報
	D3DXVECTOR3 rot;		// 向き情報
	D3DXVECTOR3 moveRot;	// 回転量情報
	int nWallX;				// 壁の数(列)
	int nWallY;				// 壁の数(行)
	float fWidth;			// 幅
	float fHieght;			// 奥行
	int nIdxtexture;		// 何番目のテクスチャか
}WallData;

typedef struct
{
	D3DXVECTOR3 pos;	// 位置情報
	D3DXVECTOR3 rot;	// 向き情報
	int nIdxModel;		// 何番目のモデルか
	int nCollition;	// 当たり判定するかどうか	 
}ModelSetData;

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
Counter g_Counter;				// カウンター用
Set g_bSet;						// セット用
MeshFieldData g_MeshFieldInfo;
WallData g_WalInfo;
ModelSetData g_ModelSetInfo;
char aSceneFileName[MODE_MAX][128];		// シーンファイルネーム

//-----------------------------------------------------------------
// シーン情報の読み込み
//-----------------------------------------------------------------
void LoadSceneInfoText(void)
{
	// FILE型のポインタ関数
	FILE *pFile;

	// 構造体のポインタ変数
	Character *pCharacter = GetCharacter();

	// ファイルを開く
	pFile = fopen("data/TEXT/scene.txt", "r");

	// 変数宣言
	bool bGetScript = false;

	char aLine[128];
	char aText[128];
	int nCntScene = 0;

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
			// SCENE_FILENAMEを見つけたらテキストファイル名を格納
			if (strcmp(&aText[0], "SCENE_FILENAME") == 0)
			{
				fscanf(pFile, "%s %s", &aText[0], &aSceneFileName[nCntScene][0]);

				// プレイヤーの総数だけ格納するのでカウントを増やす
				nCntScene++;
			}

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

//-----------------------------------------------------------------
// ステージ情報の読み込み
//-----------------------------------------------------------------
void LoadSceneData(void)
{
	// モードの取得
	MODE mode = GetMode();

	// FILE型のポインタ関数
	FILE *pFile;

	// ファイルを開く
	pFile = fopen(&aSceneFileName[mode][0], "r");

	// 変数宣言
	bool bGetScript = false;
	char aLine[128];
	char aText[128];

	// 変数の初期化
	g_Counter.nCntTexture = 0;		
	g_Counter.nCntModel = 0;		
	g_Counter.nCntCamera = 0;		
	g_Counter.nCntLight = 0;		
	g_Counter.nCntPlayer = 0;		

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
			// UI配置情報の読み込み
			LoadUIsetInfoText(pFile, &aText[0]);

			// テキスト情報の読み込み
			LoadTextureInfo(pFile, &aText[0]);

			// モデル情報の読み込み
			LoadModelInfo(pFile, &aText[0]);

			// カメラ情報の読み込み
			LoadCameraInfo(pFile, &aText[0]);

			// ライト情報の読み込み
			LoadLightInfo(pFile, &aText[0]);

			// フィールド情報の読み込み
			LoadFieldInfo(pFile, &aText[0]);
			
			// 壁情報の読み込み
			LoadWallInfo(pFile, &aText[0]);

			// モデル配置情報の読み込み
			LoadModelSetInfo(pFile, &aText[0]);

			// プレイヤー配置情報の読み込み
			LoadPlayerSetInfo(pFile, &aText[0]);

			// END_SCRIPTを見つけたら読み込みを終える
			if (strcmp(&aText[0], "END_SCRIPT") == 0)
			{
				// モデル情報の初期化
				InitModelSet();

				break;
			}
		}
	}
	// ファイルを閉じる
	fclose(pFile);
}

//-----------------------------------------------------------------
// UIセット情報テキストの読み込み
//-----------------------------------------------------------------
void LoadUIsetInfoText(FILE *pFile, char *aText)
{
	// テクスチャ情報の取得
	TextureSet *pTextureSet = GetTextureSet();

	// UISET_FILENAMEを見つけたらテキストファイル名を格納
	if (strcmp(&aText[0], "UISET_FILENAME") == 0)
	{
		fscanf(pFile, "%s %s", &aText[0], &pTextureSet->aTextName[0]);
	}
}

//-----------------------------------------------------------------
// テクスチャ情報の読み込み
//-----------------------------------------------------------------
void LoadTextureInfo(FILE *pFile,char *aText)
{
	// テクスチャ情報の取得
	Texture *pTexture = GetTexture();

	// NUM_TEXTUREを見つけたらテクスチャの総数を格納
	if (strcmp(&aText[0], "NUM_TEXTURE") == 0)
	{
		fscanf(pFile, "%s %d", &aText[0], &pTexture->nNumTexture);
	}
	// TEXTURE_FILENAMEを見つけたらテクスチャのファイル名を格納
	if (strcmp(&aText[0], "TEXTURE_FILENAME") == 0 && g_Counter.nCntTexture < pTexture->nNumTexture)
	{
		fscanf(pFile, "%s %s", &aText[0], &pTexture->TextureInfo[g_Counter.nCntTexture].aTexcharName[0]);

		// テクスチャの総数だけ格納するのでカウントを増やす
		g_Counter.nCntTexture++;
	}
}

//-----------------------------------------------------------------
// モデル情報の読み込み
//-----------------------------------------------------------------
void LoadModelInfo(FILE *pFile, char *aText)
{
	// モデル情報の取得
	ModelSet *pModelSet = GetModelSet();

	// NUM_MODELを見つけたらモデルの総数を格納
	if (strcmp(&aText[0], "NUM_MODEL") == 0)
	{
		fscanf(pFile, "%s %d", &aText[0], &pModelSet->nNumModel);
	}
	// MODEL_FILENAMEを見つけたらXファイル名を格納
	if (strcmp(&aText[0], "MODEL_FILENAME") == 0 && g_Counter.nCntModel < pModelSet->nNumModel)
	{
		fscanf(pFile, "%s %s", &aText[0], &pModelSet->modelInfo[g_Counter.nCntModel].aFileName[0]);

		// モデルの総数だけ格納するのでカウントを増やす
		g_Counter.nCntModel++;
	}
}

//-----------------------------------------------------------------
// カメラ情報の読み込み
//-----------------------------------------------------------------
void LoadCameraInfo(FILE *pFile, char *aText)
{
	// カメラ情報の取得
	Camera *pCamera = GetCamera();

	// CAMERASETを見つけたらカメラ情報を読み込む許可を与える
	if (strcmp(&aText[0], "CAMERASET") == 0)
	{
		g_bSet.bCameraSet = true;
	}
	if (g_bSet.bCameraSet == true)
	{
		// POSを見つけたら視点位置情報を格納
		if (strcmp(&aText[0], "POS") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pCamera->CameraInfo[g_Counter.nCntCamera].moveV.x,
				&pCamera->CameraInfo[g_Counter.nCntCamera].moveV.y,
				&pCamera->CameraInfo[g_Counter.nCntCamera].moveV.z);
		}
		// REFを見つけたら注視点位置情報を格納
		if (strcmp(&aText[0], "REF") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pCamera->CameraInfo[g_Counter.nCntCamera].moveR.x,
				&pCamera->CameraInfo[g_Counter.nCntCamera].moveR.y,
				&pCamera->CameraInfo[g_Counter.nCntCamera].moveR.z);
		}
		// LENGEを見つけたらどれだけ離した位置に置くか格納
		if (strcmp(&aText[0], "LENGE") == 0)
		{
			fscanf(pFile, "%s %f", &aText[0],&pCamera->CameraInfo[g_Counter.nCntCamera].fLenge);
		}
		// VIEWPORTを見つけたら情報を格納
		if (strcmp(&aText[0], "VIEWPORT") == 0)
		{
			fscanf(pFile, "%s %d %d %d %d", &aText[0],
				&pCamera->CameraInfo[g_Counter.nCntCamera].viewport.X,
				&pCamera->CameraInfo[g_Counter.nCntCamera].viewport.Y,
				&pCamera->CameraInfo[g_Counter.nCntCamera].viewport.Width,
				&pCamera->CameraInfo[g_Counter.nCntCamera].viewport.Height);
		}
		// END_CAMERASETを見つけたらカメラ情報の読み込みを終える
		if (strcmp(&aText[0], "END_CAMERASET") == 0)
		{
			// 変数を加算
			g_Counter.nCntCamera++;

			// 配置するカメラ数を加算
			pCamera->nNumCamera++;

			g_bSet.bCameraSet = false;
		}
	}
}

//-----------------------------------------------------------------
// ライト情報の読み込み
//-----------------------------------------------------------------
void LoadLightInfo(FILE *pFile, char *aText)
{
	// ライト情報の読み込み
	Light *pLight = GetLight();

	// LIGHTSETを見つけたらライト情報を読み込む許可を与える
	if (strcmp(&aText[0], "LIGHTSET") == 0)
	{
		g_bSet.bLightSet = true;
	}
	if (g_bSet.bLightSet == true)
	{
		// DIRECTIONを見つけたら方向情報を格納
		if (strcmp(&aText[0], "DIRECTION") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pLight->vecDir[g_Counter.nCntLight].x,
				&pLight->vecDir[g_Counter.nCntLight].y,
				&pLight->vecDir[g_Counter.nCntLight].z);
		}
		// DIFFUSEを見つけたら明るさ情報を格納
		if (strcmp(&aText[0], "DIFFUSE") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pLight->colDef[g_Counter.nCntLight].r,
				&pLight->colDef[g_Counter.nCntLight].g,
				&pLight->colDef[g_Counter.nCntLight].b);
		}
		// END_LIGHTSETを見つけたらライト情報の読み込みを終える
		if (strcmp(&aText[0], "END_LIGHTSET") == 0)
		{
			// 変数を加算
			g_Counter.nCntLight++;

			// 配置するカメラ数を加算
			pLight->nNumLight++;

			// ライト情報の読み込みを終える
			g_bSet.bLightSet = false;
		}
	}
}

//-----------------------------------------------------------------
// フィールド情報の読み込み
//-----------------------------------------------------------------
void LoadFieldInfo(FILE *pFile, char *aText)
{
	// フィールド情報の取得
	MeshFieldData *pMeshFieldInfo = &g_MeshFieldInfo;

	// FIELDSETを見つけたフィールド情報を読み込む許可を与える
	if (strcmp(&aText[0], "FIELDSET") == 0)
	{
		g_bSet.bFieldSet = true;
	}
	if (g_bSet.bFieldSet == true)
	{
		// TEXTYPEを見つけたらテクスチャ番号を格納
		if (strcmp(&aText[0], "TEXTYPE") == 0)
		{
			fscanf(pFile, "%s %d", &aText[0], &pMeshFieldInfo->nIdxtexture);
		}
		// POSを見つけたら位置情報を格納
		if (strcmp(&aText[0], "POS") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pMeshFieldInfo->pos.x,
				&pMeshFieldInfo->pos.y,
				&pMeshFieldInfo->pos.z);
		}
		// ROTを見つけたら向き情報を格納
		if (strcmp(&aText[0], "ROT") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pMeshFieldInfo->rot.x,
				&pMeshFieldInfo->rot.y,
				&pMeshFieldInfo->rot.z);
		}
		// BLOCKを見つけたらマス情報を格納
		if (strcmp(&aText[0], "BLOCK") == 0)
		{
			fscanf(pFile, "%s %d %d", &aText[0],
				&pMeshFieldInfo->nFieldX,
				&pMeshFieldInfo->nFieldZ);
		}
		// SIZEを見つけたらサイズ情報を格納
		if (strcmp(&aText[0], "SIZE") == 0)
		{
			fscanf(pFile, "%s %f %f", &aText[0],
				&pMeshFieldInfo->fWidth,
				&pMeshFieldInfo->fDepth);
		}
		// END_FIELDSETを見つけたらフィールド情報の読み込みを終える
		if (strcmp(&aText[0], "END_FIELDSET") == 0)
		{
			// メッシュフィールドの設置
			SetMeshField(pMeshFieldInfo->nIdxtexture,
				pMeshFieldInfo->pos,
				pMeshFieldInfo->rot,
				pMeshFieldInfo->nFieldX,
				pMeshFieldInfo->nFieldZ,
				pMeshFieldInfo->fWidth,
				pMeshFieldInfo->fDepth);

			// フィールド情報の読み込みを終える
			g_bSet.bFieldSet = false;
		}
	}
}

//-----------------------------------------------------------------
// 壁情報の読み込み
//-----------------------------------------------------------------
void LoadWallInfo(FILE *pFile, char *aText)
{
	// 壁情報の取得
	WallData *pWallInfo = &g_WalInfo;

	// WALLSETを見つけたら壁情報を読み込む許可を与える
	if (strcmp(&aText[0], "WALLSET") == 0)
	{
		// 初期化
		pWallInfo->nIdxtexture = -1;
		pWallInfo->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pWallInfo->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pWallInfo->moveRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pWallInfo->nWallX = 0;
		pWallInfo->nWallY = 0;
		pWallInfo->fWidth = 0.0f;
		pWallInfo->fHieght = 0.0f;

		g_bSet.bWallSet = true;
	}
	if (g_bSet.bWallSet == true)
	{
		// TEXTYPEを見つけたらテクスチャ番号を格納
		if (strcmp(&aText[0], "TEXTYPE") == 0)
		{
			fscanf(pFile, "%s %d", &aText[0], &pWallInfo->nIdxtexture);
		}
		// POSを見つけたら位置情報を格納
		if (strcmp(&aText[0], "POS") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pWallInfo->pos.x,
				&pWallInfo->pos.y,
				&pWallInfo->pos.z);
		}
		// ROTを見つけたら向き情報を格納
		if (strcmp(&aText[0], "ROT") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pWallInfo->rot.x,
				&pWallInfo->rot.y,
				&pWallInfo->rot.z);
		}
		// MOVEROTを見つけたら回転量情報を格納
		if (strcmp(&aText[0], "MOVEROT") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pWallInfo->moveRot.x,
				&pWallInfo->moveRot.y,
				&pWallInfo->moveRot.z);
		}
		// BLOCKを見つけたらマス情報を格納
		if (strcmp(&aText[0], "BLOCK") == 0)
		{
			fscanf(pFile, "%s %d %d", &aText[0],
				&pWallInfo->nWallX,
				&pWallInfo->nWallY);
		}
		// SIZEを見つけたらサイズ情報を格納
		if (strcmp(&aText[0], "SIZE") == 0)
		{
			fscanf(pFile, "%s %f %f", &aText[0],
				&pWallInfo->fWidth,
				&pWallInfo->fHieght);
		}
		// END_WALLSETを見つけたら壁情報の読み込みを終える
		if (strcmp(&aText[0], "END_WALLSET") == 0)
		{
			// 壁の設置
			SetWall(pWallInfo->nIdxtexture,
				pWallInfo->pos,
				pWallInfo->rot,
				pWallInfo->moveRot,
				pWallInfo->nWallX,
				pWallInfo->nWallY,
				pWallInfo->fWidth,
				pWallInfo->fHieght);

			// 壁情報の読み込みを終える
			g_bSet.bWallSet = false;
		}
	}
}

//-----------------------------------------------------------------
// モデル配置情報の読み込み
//-----------------------------------------------------------------
void LoadModelSetInfo(FILE *pFile, char *aText)
{
	// モデル配置情報の取得
	ModelSetData *pModelSetInfo = &g_ModelSetInfo;

	// 各パーツに情報を読み込む許可があるとき処理
	if (strcmp(&aText[0], "MODELSET") == 0)
	{
		g_bSet.bModelSet = true;
	}
	if (g_bSet.bModelSet == true)
	{
		// TYPEを見つけたら番号を格納
		if (strcmp(&aText[0], "TYPE") == 0)
		{
			fscanf(pFile, "%s %d", &aText[0], &pModelSetInfo->nIdxModel);
		}
		// POSを見つけたら座標情報を格納
		if (strcmp(&aText[0], "POS") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pModelSetInfo->pos.x,
				&pModelSetInfo->pos.y,
				&pModelSetInfo->pos.z);
		}
		// ROTを見つけたら角度情報を格納
		if (strcmp(&aText[0], "ROT") == 0)
		{
			// 変数宣言
			D3DXVECTOR3 rot;			// 角度保存用

			fscanf(pFile, "%s %f %f %f", &aText[0],
				&rot.x,
				&rot.y,
				&rot.z);

			pModelSetInfo->rot.x = (rot.x / 180.0f) * D3DX_PI;
			pModelSetInfo->rot.y = (rot.y / 180.0f) * D3DX_PI;
			pModelSetInfo->rot.z = (rot.z / 180.0f) * D3DX_PI;
		}
		// COLLISIONを見つけたら当たり判定するかどうか格納
		if (strcmp(&aText[0], "COLLISION") == 0)
		{
			int nNumCollition = 1;
			fscanf(pFile, "%s %d", &aText[0], &nNumCollition);

			pModelSetInfo->nCollition = nNumCollition;
		}
		// END_MODELSETKEYを見つけたらモデル配置をする
		if (strcmp(&aText[0], "END_MODELSET") == 0)
		{
			// モデルセット
			SetModel(pModelSetInfo->nIdxModel,
				pModelSetInfo->pos,
				pModelSetInfo->rot,
				pModelSetInfo->nCollition);

			// 初期化
			pModelSetInfo->nCollition = 1;

			// モデル配置情報の取得を終える
			g_bSet.bModelSet = false;
		}
	}
}

//-----------------------------------------------------------------
// プレイヤー配置情報の読み込み
//-----------------------------------------------------------------
void LoadPlayerSetInfo(FILE *pFile, char *aText)
{
	// プレイヤー情報の取得
	Player *pPlayer = GetPlayer();
	
	// 何番目の情報か
	pPlayer += g_Counter.nCntPlayer;

	// 変数宣言
	D3DXVECTOR3 rot;			// 向き保存用

	// PLAYERSETを見つけたらプレイヤー配置情報を格納する許可を与える
	if (strcmp(&aText[0], "PLAYERSET") == 0)
	{
		g_bSet.bPlayerSet = true;
	}
	if (g_bSet.bPlayerSet == true)
	{
		// POSを見つけたら座標情報を格納
		if (strcmp(&aText[0], "POS") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pPlayer->pos.x,
				&pPlayer->pos.y,
				&pPlayer->pos.z);
		}
		// ROTを見つけたら角度情報を格納
		if (strcmp(&aText[0], "ROT") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&rot.x,
				&rot.y,
				&rot.z);

			pPlayer->rot.x = (rot.x / 180.0f) * D3DX_PI;
			pPlayer->rot.y = (rot.y / 180.0f) * D3DX_PI;
			pPlayer->rot.z = (rot.z / 180.0f) * D3DX_PI;
		}
		// END_PLAYERSETを見つけたら許可を取り消す
		if (strcmp(&aText[0], "END_PLAYERSET") == 0)
		{
			// プレイヤー配置情報の取得を終える
			g_bSet.bPlayerSet = false;

			// 情報の更新
			g_Counter.nCntPlayer++;
		}
	}
}