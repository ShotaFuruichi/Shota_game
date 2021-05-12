//-----------------------------------------------------------------
//
//	テキスト読み込み (LoadText.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#include "LoadCharacterData.h"
#include "chara.h"
#include "motion.h"

//-----------------------------------------------------------------
// キャラデータの読み込み
//-----------------------------------------------------------------
void LoadCharacterData(void)
{
	// FILE型のポインタ関数
	FILE *pFile;

	// 構造体のポインタ変数
	Character *pCharacter = GetCharacter();

	// キャラ情報を読み込むテキスト情報を取得
	LoadCharacterInfo();

	for (int nCntCharacter = 0; nCntCharacter < pCharacter->nNumCharacter; nCntCharacter++)
	{
		// ファイルを開く
		pFile = fopen(&pCharacter->aTextName[nCntCharacter][0], "r");

		if (pFile != NULL)
		{
			// 変数宣言
			bool bGetScript = false;
			bool bPlayerSet = false;
			bool bPartsSet = false;
			bool bMotionSet = false;
			bool bKeySet = false;
			bool bKey = false;

			char aLine[128];
			char aText[128];
			int nCntModel = 0;
			int nCntParts = 0;
			int nCntMotion = -1;
			int nNumLoop = 0;
			int nCntKey = -1;
			int nCntKeyParts = -1;

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
					// プレイヤーのモデル情報の読み込み
					// NUM_MODELを見つけたらモデルの総数を格納
					if (strcmp(&aText[0], "NUM_MODEL") == 0)
					{
						fscanf(pFile, "%s %d", &aText[0], &pCharacter->characterInfo[nCntCharacter].nNumModel);
					}
					// MODEL_FILENAMEを見つけたらXファイル名を格納
					if (strcmp(&aText[0], "MODEL_FILENAME") == 0 && nCntModel < pCharacter->characterInfo[nCntCharacter].nNumModel)
					{
						fscanf(pFile, "%s %s", &aText[0], &pCharacter->characterInfo[nCntCharacter].aModel[nCntModel].aFileName[0]);

						// モデルの総数だけ格納するのでカウントを増やす
						nCntModel++;
					}
					// CHARACTERSETを見つけたらキャラクター情報を読み込む許可を与える
					if (strcmp(&aText[0], "CHARACTERSET") == 0)
					{
						bPlayerSet = true;
					}
					// PARTSSETを見つけたら各パーツの情報を格納する許可を与える
					if (strcmp(&aText[0], "PARTSSET") == 0 && bPlayerSet == true)
					{
						bPartsSet = true;
					}
					// 各パーツの情報を格納する許可があるとき処理
					if (bPartsSet == true)
					{
						// PARENTを見つけたらXファイル名を格納
						if (strcmp(&aText[0], "PARENT") == 0)
						{
							fscanf(pFile, "%s %d", &aText[0], &pCharacter->characterInfo[nCntCharacter].aModel[nCntParts].nIdxModelParent);
						}
						// POSを見つけたら座標情報を格納
						if (strcmp(&aText[0], "POS") == 0)
						{
							fscanf(pFile, "%s %f %f %f", &aText[0],
								&pCharacter->characterInfo[nCntCharacter].aModel[nCntParts].pos.x,
								&pCharacter->characterInfo[nCntCharacter].aModel[nCntParts].pos.y,
								&pCharacter->characterInfo[nCntCharacter].aModel[nCntParts].pos.z);
						}
						// ROTを見つけたら角度情報を格納
						if (strcmp(&aText[0], "ROT") == 0)
						{
							fscanf(pFile, "%s %f %f %f", &aText[0],
								&pCharacter->characterInfo[nCntCharacter].aModel[nCntParts].rot.x,
								&pCharacter->characterInfo[nCntCharacter].aModel[nCntParts].rot.y,
								&pCharacter->characterInfo[nCntCharacter].aModel[nCntParts].rot.z);
						}
						// END_PARTSSETを見つけたら各パーツの情報を格納を終える
						if (strcmp(&aText[0], "END_PARTSSET") == 0 && bPlayerSet == true)
						{
							bPartsSet = false;

							if (nCntParts < pCharacter->characterInfo[nCntCharacter].nNumModel)
							{
								// パーツの総数だけ格納するのでカウントを増やす
								nCntParts++;
							}
						}
					}
					// END_CHARACTERSETを見つけたらキャラクター情報を読み込むを終える
					if (strcmp(&aText[0], "END_CHARACTERSET") == 0)
					{
						bPlayerSet = false;
					}

					// モーション情報の読み込み
					// MOTIONSETを見つけたらモーション情報を読み込む許可を与える
					if (strcmp(&aText[0], "MOTIONSET") == 0)
					{
						bMotionSet = true;

						// モーションが複数あるかもしれないのでカウント
						nCntMotion++;
					}
					// モーション情報を読み込む許可があるとき処理
					if (bMotionSet == true)
					{
						// LOOPを見つけたらモーションをループさせるかどうか決める
						if (strcmp(&aText[0], "LOOP") == 0)
						{
							fscanf(pFile, "%s %d", &aText[0], &nNumLoop);

							// 数字でループするかどうか判断
							if (nNumLoop == 1)
							{
								pCharacter->characterInfo[nCntCharacter].aMotionInfo[nCntMotion].bLoop = true;
							}
							else
							{
								pCharacter->characterInfo[nCntCharacter].aMotionInfo[nCntMotion].bLoop = false;
							}
						}
						// NUM_KEYを見つけたらキー数を格納
						if (strcmp(&aText[0], "NUM_KEY") == 0)
						{
							fscanf(pFile, "%s %d", &aText[0], &pCharacter->characterInfo[nCntCharacter].aMotionInfo[nCntMotion].nNumKey);
						}
						// KEYSETを見つけたら各キー情報を読み込む許可を与える
						if (strcmp(&aText[0], "KEYSET") == 0)
						{
							bKeySet = true;

							// キーは複数あるのでカウント
							nCntKey++;
						}
						// 各キー情報を読み込む許可があるとき処理
						if (bKeySet == true)
						{
							// FRAMEを見つけたらフレーム数を格納
							if (strcmp(&aText[0], "FRAME") == 0)
							{
								fscanf(pFile, "%s %d", &aText[0], &pCharacter->characterInfo[nCntCharacter].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);
							}
							// KEYを見つけたら各パーツに情報を読み込む許可を与える
							if (strcmp(&aText[0], "KEY") == 0)
							{
								bKey = true;

								// パーツも複数あるのでカウント
								nCntKeyParts++;
							}
							// 各パーツに情報を読み込む許可があるとき処理
							if (bKey == true)
							{
								// POSを見つけたら座標情報を格納
								if (strcmp(&aText[0], "POS") == 0)
								{
									fscanf(pFile, "%s %f %f %f", &aText[0],
										&pCharacter->characterInfo[nCntCharacter].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntKeyParts].fPosX,
										&pCharacter->characterInfo[nCntCharacter].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntKeyParts].fPosY,
										&pCharacter->characterInfo[nCntCharacter].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntKeyParts].fPosZ);

									pCharacter->characterInfo[nCntCharacter].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntKeyParts].fPosX += pCharacter->characterInfo[nCntCharacter].aModel[nCntKeyParts].pos.x;
									pCharacter->characterInfo[nCntCharacter].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntKeyParts].fPosY += pCharacter->characterInfo[nCntCharacter].aModel[nCntKeyParts].pos.y;
									pCharacter->characterInfo[nCntCharacter].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntKeyParts].fPosZ += pCharacter->characterInfo[nCntCharacter].aModel[nCntKeyParts].pos.z;
								}
								// ROTを見つけたら角度情報を格納
								if (strcmp(&aText[0], "ROT") == 0)
								{
									fscanf(pFile, "%s %f %f %f", &aText[0],
										&pCharacter->characterInfo[nCntCharacter].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntKeyParts].fRotX,
										&pCharacter->characterInfo[nCntCharacter].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntKeyParts].fRotY,
										&pCharacter->characterInfo[nCntCharacter].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntKeyParts].fRotZ);
								}
								// END_KEYを見つけたら各パーツに情報の読み込みを終える
								if (strcmp(&aText[0], "END_KEY") == 0)
								{
									bKey = false;
								}
							}
							// END_KEYSETを見つけたら各キー情報の読み込みを終える
							if (strcmp(&aText[0], "END_KEYSET") == 0)
							{
								bKeySet = false;

								// パーツカウント用の変数を初期化
								nCntKeyParts = -1;
							}
						}
						// END_MOTIONSETを見つけたらモーション情報の読み込みを終える
						if (strcmp(&aText[0], "END_MOTIONSET") == 0)
						{
							bMotionSet = false;

							// キーカウント用の変数を初期化
							nCntKey = -1;
						}
					}

					// END_SCRIPTを見つけたら読み込みを終える
					if (strcmp(&aText[0], "END_SCRIPT") == 0)
					{
						bGetScript = false;
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
}

//-----------------------------------------------------------------
// キャラ情報を読み込む
//-----------------------------------------------------------------
void LoadCharacterInfo(void)
{
	// FILE型のポインタ関数
	FILE *pFile;

	// 構造体のポインタ変数
	Character *pCharacter = GetCharacter();

	// ファイルを開く
	pFile = fopen("data/TEXT/character.txt", "r");

	// 変数宣言
	bool bGetScript = false;

	char aLine[128];
	char aText[128];
	int nCntCharacter = -1;

	if (pFile != NULL)
	{
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
				// プレイヤーのモデル情報の読み込み
				// NUM_PLAYERを見つけたらプレイヤーの総数を格納
				if (strcmp(&aText[0], "NUM_CHARACTER") == 0)
				{
					fscanf(pFile, "%s %d", &aText[0], &pCharacter->nNumCharacter);
				}
				// CHARACTER_FILENAMEを見つけたらXファイル名を格納
				if (strcmp(&aText[0], "CHARACTER_FILENAME") == 0)
				{
					fscanf(pFile, "%s %s", &aText[0], &pCharacter->aTextName[nCntCharacter][256]);

					// プレイヤーの総数だけ格納するのでカウントを増やす
					nCntCharacter++;
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
	else
	{
	}
}