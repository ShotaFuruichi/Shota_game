//-----------------------------------------------------------------
//
//	�e�L�X�g�ǂݍ��� (LoadText.cpp)
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
// �L�����f�[�^�̓ǂݍ���
//-----------------------------------------------------------------
void LoadCharacterData(void)
{
	// FILE�^�̃|�C���^�֐�
	FILE *pFile;

	// �\���̂̃|�C���^�ϐ�
	Character *pCharacter = GetCharacter();

	// �L��������ǂݍ��ރe�L�X�g�����擾
	LoadCharacterInfo();

	for (int nCntCharacter = 0; nCntCharacter < pCharacter->nNumCharacter; nCntCharacter++)
	{
		// �t�@�C�����J��
		pFile = fopen(&pCharacter->aTextName[nCntCharacter][0], "r");

		if (pFile != NULL)
		{
			// �ϐ��錾
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

			// SCRIPT��T��
			while (fgets(aLine, 128, pFile) != NULL)
			{
				fscanf(pFile, "%s", &aText[0]);

				// SCRIPT���������炻��ȍ~��ǂݍ���
				if (strcmp(&aText[0], "SCRIPT") == 0)
				{
					bGetScript = true;
				}

				if (bGetScript == true)
				{
					// �v���C���[�̃��f�����̓ǂݍ���
					// NUM_MODEL���������烂�f���̑������i�[
					if (strcmp(&aText[0], "NUM_MODEL") == 0)
					{
						fscanf(pFile, "%s %d", &aText[0], &pCharacter->characterInfo[nCntCharacter].nNumModel);
					}
					// MODEL_FILENAME����������X�t�@�C�������i�[
					if (strcmp(&aText[0], "MODEL_FILENAME") == 0 && nCntModel < pCharacter->characterInfo[nCntCharacter].nNumModel)
					{
						fscanf(pFile, "%s %s", &aText[0], &pCharacter->characterInfo[nCntCharacter].aModel[nCntModel].aFileName[0]);

						// ���f���̑��������i�[����̂ŃJ�E���g�𑝂₷
						nCntModel++;
					}
					// CHARACTERSET����������L�����N�^�[����ǂݍ��ދ���^����
					if (strcmp(&aText[0], "CHARACTERSET") == 0)
					{
						bPlayerSet = true;
					}
					// PARTSSET����������e�p�[�c�̏����i�[���鋖��^����
					if (strcmp(&aText[0], "PARTSSET") == 0 && bPlayerSet == true)
					{
						bPartsSet = true;
					}
					// �e�p�[�c�̏����i�[���鋖������Ƃ�����
					if (bPartsSet == true)
					{
						// PARENT����������X�t�@�C�������i�[
						if (strcmp(&aText[0], "PARENT") == 0)
						{
							fscanf(pFile, "%s %d", &aText[0], &pCharacter->characterInfo[nCntCharacter].aModel[nCntParts].nIdxModelParent);
						}
						// POS������������W�����i�[
						if (strcmp(&aText[0], "POS") == 0)
						{
							fscanf(pFile, "%s %f %f %f", &aText[0],
								&pCharacter->characterInfo[nCntCharacter].aModel[nCntParts].pos.x,
								&pCharacter->characterInfo[nCntCharacter].aModel[nCntParts].pos.y,
								&pCharacter->characterInfo[nCntCharacter].aModel[nCntParts].pos.z);
						}
						// ROT����������p�x�����i�[
						if (strcmp(&aText[0], "ROT") == 0)
						{
							fscanf(pFile, "%s %f %f %f", &aText[0],
								&pCharacter->characterInfo[nCntCharacter].aModel[nCntParts].rot.x,
								&pCharacter->characterInfo[nCntCharacter].aModel[nCntParts].rot.y,
								&pCharacter->characterInfo[nCntCharacter].aModel[nCntParts].rot.z);
						}
						// END_PARTSSET����������e�p�[�c�̏����i�[���I����
						if (strcmp(&aText[0], "END_PARTSSET") == 0 && bPlayerSet == true)
						{
							bPartsSet = false;

							if (nCntParts < pCharacter->characterInfo[nCntCharacter].nNumModel)
							{
								// �p�[�c�̑��������i�[����̂ŃJ�E���g�𑝂₷
								nCntParts++;
							}
						}
					}
					// END_CHARACTERSET����������L�����N�^�[����ǂݍ��ނ��I����
					if (strcmp(&aText[0], "END_CHARACTERSET") == 0)
					{
						bPlayerSet = false;
					}

					// ���[�V�������̓ǂݍ���
					// MOTIONSET���������烂�[�V��������ǂݍ��ދ���^����
					if (strcmp(&aText[0], "MOTIONSET") == 0)
					{
						bMotionSet = true;

						// ���[�V�������������邩������Ȃ��̂ŃJ�E���g
						nCntMotion++;
					}
					// ���[�V��������ǂݍ��ދ�������Ƃ�����
					if (bMotionSet == true)
					{
						// LOOP���������烂�[�V���������[�v�����邩�ǂ������߂�
						if (strcmp(&aText[0], "LOOP") == 0)
						{
							fscanf(pFile, "%s %d", &aText[0], &nNumLoop);

							// �����Ń��[�v���邩�ǂ������f
							if (nNumLoop == 1)
							{
								pCharacter->characterInfo[nCntCharacter].aMotionInfo[nCntMotion].bLoop = true;
							}
							else
							{
								pCharacter->characterInfo[nCntCharacter].aMotionInfo[nCntMotion].bLoop = false;
							}
						}
						// NUM_KEY����������L�[�����i�[
						if (strcmp(&aText[0], "NUM_KEY") == 0)
						{
							fscanf(pFile, "%s %d", &aText[0], &pCharacter->characterInfo[nCntCharacter].aMotionInfo[nCntMotion].nNumKey);
						}
						// KEYSET����������e�L�[����ǂݍ��ދ���^����
						if (strcmp(&aText[0], "KEYSET") == 0)
						{
							bKeySet = true;

							// �L�[�͕�������̂ŃJ�E���g
							nCntKey++;
						}
						// �e�L�[����ǂݍ��ދ�������Ƃ�����
						if (bKeySet == true)
						{
							// FRAME����������t���[�������i�[
							if (strcmp(&aText[0], "FRAME") == 0)
							{
								fscanf(pFile, "%s %d", &aText[0], &pCharacter->characterInfo[nCntCharacter].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);
							}
							// KEY����������e�p�[�c�ɏ���ǂݍ��ދ���^����
							if (strcmp(&aText[0], "KEY") == 0)
							{
								bKey = true;

								// �p�[�c����������̂ŃJ�E���g
								nCntKeyParts++;
							}
							// �e�p�[�c�ɏ���ǂݍ��ދ�������Ƃ�����
							if (bKey == true)
							{
								// POS������������W�����i�[
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
								// ROT����������p�x�����i�[
								if (strcmp(&aText[0], "ROT") == 0)
								{
									fscanf(pFile, "%s %f %f %f", &aText[0],
										&pCharacter->characterInfo[nCntCharacter].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntKeyParts].fRotX,
										&pCharacter->characterInfo[nCntCharacter].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntKeyParts].fRotY,
										&pCharacter->characterInfo[nCntCharacter].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntKeyParts].fRotZ);
								}
								// END_KEY����������e�p�[�c�ɏ��̓ǂݍ��݂��I����
								if (strcmp(&aText[0], "END_KEY") == 0)
								{
									bKey = false;
								}
							}
							// END_KEYSET����������e�L�[���̓ǂݍ��݂��I����
							if (strcmp(&aText[0], "END_KEYSET") == 0)
							{
								bKeySet = false;

								// �p�[�c�J�E���g�p�̕ϐ���������
								nCntKeyParts = -1;
							}
						}
						// END_MOTIONSET���������烂�[�V�������̓ǂݍ��݂��I����
						if (strcmp(&aText[0], "END_MOTIONSET") == 0)
						{
							bMotionSet = false;

							// �L�[�J�E���g�p�̕ϐ���������
							nCntKey = -1;
						}
					}

					// END_SCRIPT����������ǂݍ��݂��I����
					if (strcmp(&aText[0], "END_SCRIPT") == 0)
					{
						bGetScript = false;
					}
				}
			}
			// �t�@�C�������
			fclose(pFile);
		}
		else
		{
		}
	}
}

//-----------------------------------------------------------------
// �L��������ǂݍ���
//-----------------------------------------------------------------
void LoadCharacterInfo(void)
{
	// FILE�^�̃|�C���^�֐�
	FILE *pFile;

	// �\���̂̃|�C���^�ϐ�
	Character *pCharacter = GetCharacter();

	// �t�@�C�����J��
	pFile = fopen("data/TEXT/character.txt", "r");

	// �ϐ��錾
	bool bGetScript = false;

	char aLine[128];
	char aText[128];
	int nCntCharacter = -1;

	if (pFile != NULL)
	{
		// SCRIPT��T��
		while (fgets(aLine, 128, pFile) != NULL)
		{
			fscanf(pFile, "%s", &aText[0]);

			// SCRIPT���������炻��ȍ~��ǂݍ���
			if (strcmp(&aText[0], "SCRIPT") == 0)
			{
				bGetScript = true;
			}

			if (bGetScript == true)
			{
				// �v���C���[�̃��f�����̓ǂݍ���
				// NUM_PLAYER����������v���C���[�̑������i�[
				if (strcmp(&aText[0], "NUM_CHARACTER") == 0)
				{
					fscanf(pFile, "%s %d", &aText[0], &pCharacter->nNumCharacter);
				}
				// CHARACTER_FILENAME����������X�t�@�C�������i�[
				if (strcmp(&aText[0], "CHARACTER_FILENAME") == 0)
				{
					fscanf(pFile, "%s %s", &aText[0], &pCharacter->aTextName[nCntCharacter][256]);

					// �v���C���[�̑��������i�[����̂ŃJ�E���g�𑝂₷
					nCntCharacter++;
				}

				// END_SCRIPT����������ǂݍ��݂��I����
				if (strcmp(&aText[0], "END_SCRIPT") == 0)
				{
					break;
				}
			}
		}
		// �t�@�C�������
		fclose(pFile);
	}
	else
	{
	}
}