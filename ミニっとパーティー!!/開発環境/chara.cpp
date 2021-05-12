//-----------------------------------------------------------------
//
// プレイヤー (player.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "chara.h"
#include "motion.h"
#include "camera.h"
#include "input.h"
#include "gamepad.h"
#include "sound.h"
#include "chara_select_frame.h"
#include "player.h"

//-----------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------
#define MOVE_MODEL			(2.0f)
#define JUMP_PLAYER			(11.0f)
#define PI_QUARTER			(D3DX_PI / 4.0f)
#define GRAVITY				(0.5f)		// 重力

#define LENGTH				(8.0f)
#define MAX_DISPLAY_CHARA	(4)				// プレイヤーの総数

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
Character g_chara;						// キャラ情報

//-----------------------------------------------------------------
// キャラの初期化処理
//-----------------------------------------------------------------
HRESULT InitCharacter(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntChara = 0; nCntChara < MAX_CHARA; nCntChara++)
	{
		// プレイヤー情報の初期化
		g_chara.characterInfo[nCntChara].pos = D3DXVECTOR3(0.0, 0.0f, 0.0f);
		g_chara.characterInfo[nCntChara].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_chara.characterInfo[nCntChara].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_chara.characterInfo[nCntChara].MotionType = MOTIONTYPE_NEUTRAL;
		g_chara.characterInfo[nCntChara].nCounterMotion = 1;
		g_chara.characterInfo[nCntChara].nKey = 0;
		g_chara.characterInfo[nCntChara].bLoopMotion = g_chara.characterInfo[nCntChara].aMotionInfo[g_chara.characterInfo[nCntChara].MotionType].bLoop;
		g_chara.characterInfo[nCntChara].nNumKey = g_chara.characterInfo[nCntChara].aMotionInfo[g_chara.characterInfo[nCntChara].MotionType].nNumKey;

		// プレイヤーのパーツ設定
		for (int nCntModel = 0; nCntModel < g_chara.characterInfo[nCntChara].nNumModel; nCntModel++)
		{
			// Xファイルの読み込み
			if (FAILED(D3DXLoadMeshFromX(g_chara.characterInfo[nCntChara].aModel[nCntModel].aFileName,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_chara.characterInfo[nCntChara].aModel[nCntModel].pBuffMat,
				NULL,
				&g_chara.characterInfo[nCntChara].aModel[nCntModel].nNumMat,
				&g_chara.characterInfo[nCntChara].aModel[nCntModel].pMesh)))
			{
				return E_FAIL;
			}

			// 変数宣言
			D3DXMATERIAL *pMat;		// マテリアルデータへのポインタ
			LPDIRECT3DDEVICE9 pDevice;		// デバイスへのポインタ

			// 変数の受け渡し
			pDevice = GetDevice();

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_chara.characterInfo[nCntChara].aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_chara.characterInfo[nCntChara].aModel[nCntModel].nNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					// テクスチャの読み込み
					D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_chara.characterInfo[nCntChara].aModel[nCntModel].pTexture[nCntMat]);
				}
			}
		}
	}

	return S_OK;
}

//-----------------------------------------------------------------
// キャラの終了処理
//-----------------------------------------------------------------
void UninitCharacter(void)
{
	for (int nCntChara = 0; nCntChara < MAX_CHARA; nCntChara++)
	{
		for (int nCntModel = 0; nCntModel < g_chara.characterInfo[nCntChara].nNumModel; nCntModel++)
		{
			// マテリアル情報の開放
			if (g_chara.characterInfo[nCntChara].aModel[nCntModel].pBuffMat != NULL)
			{
				g_chara.characterInfo[nCntChara].aModel[nCntModel].pBuffMat->Release();
				g_chara.characterInfo[nCntChara].aModel[nCntModel].pBuffMat = NULL;
			}

			// メッシュ情報の開放
			if (g_chara.characterInfo[nCntChara].aModel[nCntModel].pMesh != NULL)
			{
				g_chara.characterInfo[nCntChara].aModel[nCntModel].pMesh->Release();
				g_chara.characterInfo[nCntChara].aModel[nCntModel].pMesh = NULL;
			}
		}
	}
}

//-----------------------------------------------------------------
// キャラの更新処理
//-----------------------------------------------------------------
void UpdateCharacter(void)
{
	for (int nCntChara = 0; nCntChara < MAX_CHARA; nCntChara++)
	{
		// プレイヤーモーション
		CharacterMotion(nCntChara);
	}
}

//-----------------------------------------------------------------
// キャラの描画処理
//-----------------------------------------------------------------
void DrawCharacter(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;		// デバイスへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス
	D3DMATERIAL9 matDef;			// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;				// マテリアルデータへのポインタ

	// 変数の受け渡し
	pDevice = GetDevice();
	Camera *pCamera = GetCamera();

	// キャラセレクトイメージ情報の取得
	CharaSelectFrame *pCharaSelectFrame = GetCharaSelectFrame();

	for (int nCntChara = 0; nCntChara < MAX_DISPLAY_CHARA; nCntChara++,pCharaSelectFrame++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_chara.characterInfo[pCharaSelectFrame->nNumChara].mtxWorld);

		// 向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_chara.characterInfo[pCharaSelectFrame->nNumChara].rot.y, g_chara.characterInfo[pCharaSelectFrame->nNumChara].rot.x, g_chara.characterInfo[pCharaSelectFrame->nNumChara].rot.z);
		D3DXMatrixMultiply(&g_chara.characterInfo[pCharaSelectFrame->nNumChara].mtxWorld, &g_chara.characterInfo[pCharaSelectFrame->nNumChara].mtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, pCamera->CameraInfo[nCntChara].posV.x, g_chara.characterInfo[pCharaSelectFrame->nNumChara].pos.y, g_chara.characterInfo[pCharaSelectFrame->nNumChara].pos.z);
		D3DXMatrixMultiply(&g_chara.characterInfo[pCharaSelectFrame->nNumChara].mtxWorld, &g_chara.characterInfo[pCharaSelectFrame->nNumChara].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_chara.characterInfo[pCharaSelectFrame->nNumChara].mtxWorld);

		for (int nCntModel = 0; nCntModel < g_chara.characterInfo[pCharaSelectFrame->nNumChara].nNumModel; nCntModel++)
		{
			// 変数宣言
			D3DXMATRIX mtxRotModel, mtxTransModel;		// 計算用マトリックス
			D3DXMATRIX mtxParent;						// 親のマトリックス

			// 各パーツのワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].mtxWorld);

			// 各パーツの向き
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].rot.y, g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].rot.x, g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].mtxWorld, &g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].mtxWorld, &mtxRotModel);

			// 各パーツの位置
			D3DXMatrixTranslation(&mtxTransModel, g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].pos.x, g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].pos.y, g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].mtxWorld, &g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].mtxWorld, &mtxTransModel);

			// 各パーツの親のマトリックスを設定
			if (g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].nIdxModelParent != -1)
			{
				mtxParent = g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].nIdxModelParent].mtxWorld;
			}
			else
			{
				mtxParent = g_chara.characterInfo[pCharaSelectFrame->nNumChara].mtxWorld;
			}
			// 算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
			D3DXMatrixMultiply(&g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].mtxWorld,
				&g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].mtxWorld,
				&mtxParent);

			// 各パーツのマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].nNumMat; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].pTexture[nCntMat]);

				// モデル(パーツ)の描画
				g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].pMesh->DrawSubset(nCntMat);
			}
			// 保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//-----------------------------------------------------------------
// キャラ情報の取得
//-----------------------------------------------------------------
Character *GetCharacter(void)
{
	return &g_chara;
}

//-----------------------------------------------------------------
// キャラモーションの設定
//-----------------------------------------------------------------
void CharacterMotion(int nCntCharacter)
{
	// 変数宣言
	CharacterInfo *pCharacterInfo = &g_chara.characterInfo[0];
	pCharacterInfo += nCntCharacter;	// 何番目のプレイヤーか
	KEY *pKey;				// キー情報
	KEY *pKeyNext;			// 次のキー情報
	float fPosX;
	float fPosY;
	float fPosZ;
	float fRotX;
	float fRotY;
	float fRotZ;

	for (int nCntModel = 0; nCntModel < pCharacterInfo->nNumModel; nCntModel++)
	{
		// キーの確定
		pKey = &pCharacterInfo->aMotionInfo[pCharacterInfo->MotionType].aKeyInfo[pCharacterInfo->nKey].aKey[nCntModel];
		pKeyNext = &pCharacterInfo->aMotionInfo[pCharacterInfo->MotionType].aKeyInfo[(pCharacterInfo->nKey + 1) % pCharacterInfo->nNumKey].aKey[nCntModel];

		// 差分の確定
		float fDiffMoitonPosX = pKeyNext->fPosX - pKey->fPosX;
		float fDiffMoitonPosY = pKeyNext->fPosY - pKey->fPosY;
		float fDiffMoitonPosZ = pKeyNext->fPosZ - pKey->fPosZ;
		float fDiffMoitonRotX = pKeyNext->fRotX - pKey->fRotX;
		float fDiffMoitonRotY = pKeyNext->fRotY - pKey->fRotY;
		float fDiffMoitonRotZ = pKeyNext->fRotZ - pKey->fRotZ;

		// 角度の制限
		D3DXVECTOR3(fDiffMoitonRotX, fDiffMoitonRotY, fDiffMoitonRotZ) = AngleCorrection(fDiffMoitonRotX, fDiffMoitonRotY, fDiffMoitonRotZ);

		// 相対値の確定
		float fRateMotion = (float)pCharacterInfo->nCounterMotion / (float)pCharacterInfo->aMotionInfo[pCharacterInfo->MotionType].aKeyInfo[pCharacterInfo->nKey].nFrame;

		// モーションの位置と向きの確定
		fPosX = pKey->fPosX + (fDiffMoitonPosX * fRateMotion);
		fPosY = pKey->fPosY + (fDiffMoitonPosY * fRateMotion);
		fPosZ = pKey->fPosZ + (fDiffMoitonPosZ * fRateMotion);
		fRotX = pKey->fRotX + (fDiffMoitonRotX * fRateMotion);
		fRotY = pKey->fRotY + (fDiffMoitonRotY * fRateMotion);
		fRotZ = pKey->fRotZ + (fDiffMoitonRotZ * fRateMotion);

		// 角度の制限
		D3DXVECTOR3(fRotX, fRotY, fRotZ) = AngleCorrection(fRotX, fRotY, fRotZ);

		if ((pCharacterInfo->nKey) == (pCharacterInfo->nNumKey - 1) && pCharacterInfo->bLoopMotion == false)
		{
			break;
		}

		// 位置と向きの設定
		pCharacterInfo->aModel[nCntModel].pos.x = fPosX;
		pCharacterInfo->aModel[nCntModel].pos.y = fPosY;
		pCharacterInfo->aModel[nCntModel].pos.z = fPosZ;
		pCharacterInfo->aModel[nCntModel].rot.x = fRotX;
		pCharacterInfo->aModel[nCntModel].rot.y = fRotY;
		pCharacterInfo->aModel[nCntModel].rot.z = fRotZ;
	}

	if (pCharacterInfo->nCounterMotion > pCharacterInfo->aMotionInfo[pCharacterInfo->MotionType].aKeyInfo[pCharacterInfo->nKey].nFrame)
	{
		// モーションカウンタの初期化
		pCharacterInfo->nCounterMotion = 0;

		// キーの更新
		pCharacterInfo->nKey++;

		// キーの確定
		pCharacterInfo->nKey = pCharacterInfo->nKey % pCharacterInfo->nNumKey;
	}
	// モーションカウンタの更新
	pCharacterInfo->nCounterMotion++;
}

//-----------------------------------------------------------------
// モーションの設定
//-----------------------------------------------------------------
void SetCharaMotion(int nCntCharacter, MOTIONTYPE motiontype, bool bBlend, int nFrameBlend)
{
	if (bBlend == false && g_chara.characterInfo[nCntCharacter].MotionType != motiontype)
	{
		// モーションの確定
		g_chara.characterInfo[nCntCharacter].MotionType = motiontype;

		// モーションカウンタを初期化
		g_chara.characterInfo[nCntCharacter].nCounterMotion = 0;

		// 現在のキーを初期化
		g_chara.characterInfo[nCntCharacter].nKey = 0;

		// ループするかどうか
		g_chara.characterInfo[nCntCharacter].bLoopMotion = g_chara.characterInfo[nCntCharacter].aMotionInfo[g_chara.characterInfo[nCntCharacter].MotionType].bLoop;

		// キー数の確定
		g_chara.characterInfo[nCntCharacter].nNumKey = g_chara.characterInfo[nCntCharacter].aMotionInfo[g_chara.characterInfo[nCntCharacter].MotionType].nNumKey;
	}
}