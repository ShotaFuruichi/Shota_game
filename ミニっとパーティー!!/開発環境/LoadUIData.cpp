//-----------------------------------------------------------------
//
//	UI���ǂݍ��� (LoadUIdata.cpp)
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
// �\���̂̐錾
//-----------------------------------------------------------------
typedef struct
{
	int nCntTexture = 0;		// �e�N�X�`����
}UIsetCounter;

typedef struct
{
	bool bTexSet = false;
	bool bSelectModeSet = false;
	bool bPressAnyButtonSet = false;
}UIset;

typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu���
	D3DXVECTOR3 rot;	// �������
	D3DXVECTOR3 move;	// �ړ��ʏ��
	D3DXCOLOR col;		// �F
	float fRemoveAlpha;	// ���l�̌�����
	float fWidth;		// ��
	float fHeight;		// ����
	float fWidthDest;	// �ړI�̕�
	float fHeightDest;	// �ړI�̍���
	int nType;			// �ړ��^�C�v
	int nTexType;		// �e�N�X�`���^�C�v
}TextureSetData;

typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu���
	D3DXCOLOR col;		// �F
	float fWidth;		// ��
	float fHeight;		// ����
	int nTexType;		// �e�N�X�`���^�C�v
}SelectModeSetData;

typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu���
	D3DXCOLOR col;		// �F
	float fRemoveAlpha;	// ���l������
	float fWidth;		// ��
	float fHeight;		// ����
	int nTexType;		// �e�N�X�`���^�C�v
}PressAnyButtonSetData;

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
UIsetCounter g_UIsetCounter;				// �J�E���^�[�p
UIset g_bUIset;						// �Z�b�g�p
TextureSetData g_TextureData;
SelectModeSetData g_SelectModeSetData;
PressAnyButtonSetData g_PressAnyButtonSetData;

//-----------------------------------------------------------------
// UI���̓ǂݍ���
//-----------------------------------------------------------------
void LoadUISetData(void)
{
	// �e�N�X�`���z�u���̎擾
	TextureSet *pTextureSet = GetTextureSet();

	// ���[�h�̎擾
	MODE mode = GetMode();

	// FILE�^�̃|�C���^�֐�
	FILE *pFile;

	// �t�@�C�����J��
	pFile = fopen(&pTextureSet->aTextName[0], "r");

	if (pFile != NULL)
	{
		// �ϐ��錾
		bool bGetScript = false;
		char aLine[128];
		char aText[128];

		// �ϐ��̏�����
		g_UIsetCounter.nCntTexture = 0;

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
				// �e�L�X�g���̓ǂݍ���
				LoadTextureSetTexInfo(pFile, &aText[0]);

				// �e�N�X�`���z�u���̓ǂݍ���
				LoadTextureSetData(pFile, &aText[0]);

				// �Z���N�g���[�h�̔z�u���̓ǂݍ���
				LoadSelectModeData(pFile, &aText[0]);

				// �{�^���w���z�u���̓ǂݍ���
				LoadPressAnyButtonData(pFile, &aText[0]);

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

//-----------------------------------------------------------------
// �e�N�X�`�����̓ǂݍ���
//-----------------------------------------------------------------
void LoadTextureSetTexInfo(FILE *pFile, char *aText)
{
	// �e�N�X�`���z�u���̎擾
	Texture *pTexture = GetUITexture();

	// NUM_TEXTURE����������e�N�X�`���̑������i�[
	if (strcmp(&aText[0], "NUM_TEXTURE") == 0)
	{
		fscanf(pFile, "%s %d", &aText[0], &pTexture->nNumTexture);
	}
	// TEXTURE_FILENAME����������e�N�X�`���̃t�@�C�������i�[
	if (strcmp(&aText[0], "TEXTURE_FILENAME") == 0 && g_UIsetCounter.nCntTexture < pTexture->nNumTexture)
	{
		fscanf(pFile, "%s %s", &aText[0], &pTexture->TextureInfo[g_UIsetCounter.nCntTexture].aTexcharName[0]);

		// �e�N�X�`���̑��������i�[����̂ŃJ�E���g�𑝂₷
		g_UIsetCounter.nCntTexture++;
	}
}

//-----------------------------------------------------------------
// �e�N�X�`���z�u���̓ǂݍ���
//-----------------------------------------------------------------
void LoadTextureSetData(FILE *pFile, char *aText)
{
	// �e�N�X�`���z�u���̎擾
	TextureSetData *pTextureSetInfo = &g_TextureData;

	// TEXTURESET���������e�N�X�`���z�u����ǂݍ��ދ���^����
	if (strcmp(&aText[0], "TEXTURESET") == 0)
	{
		// �ϐ��̏�����
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
		// TEXTYPE����������e�N�X�`���ԍ����i�[
		if (strcmp(&aText[0], "TEXTYPE") == 0)
		{
			fscanf(pFile, "%s %d", &aText[0], &pTextureSetInfo->nTexType);
		}
		// EFFECTTYPE����������G�t�F�N�g�ԍ����i�[
		if (strcmp(&aText[0], "EFFECTTYPE") == 0)
		{
			fscanf(pFile, "%s %d", &aText[0], &pTextureSetInfo->nType);
		}
		// POS����������ʒu�����i�[
		if (strcmp(&aText[0], "POS") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pTextureSetInfo->pos.x,
				&pTextureSetInfo->pos.y,
				&pTextureSetInfo->pos.z);
		}
		// ROT������������������i�[
		if (strcmp(&aText[0], "ROT") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pTextureSetInfo->rot.x,
				&pTextureSetInfo->rot.y,
				&pTextureSetInfo->rot.z);
		}
		// MOVE����������ړ��ʏ����i�[
		if (strcmp(&aText[0], "MOVE") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pTextureSetInfo->move.x,
				&pTextureSetInfo->move.y,
				&pTextureSetInfo->move.z);
		}
		// COL����������F�����i�[
		if (strcmp(&aText[0], "COL") == 0)
		{
			fscanf(pFile, "%s %f %f %f %f", &aText[0],
				&pTextureSetInfo->col.r,
				&pTextureSetInfo->col.g,
				&pTextureSetInfo->col.b,
				&pTextureSetInfo->col.a);
		}
		// REMOVE���������烿�l�����ʏ����i�[
		if (strcmp(&aText[0], "REMOVE") == 0)
		{
			fscanf(pFile, "%s %f", &aText[0],
				&pTextureSetInfo->fRemoveAlpha);
		}
		// SIZE����������T�C�Y�����i�[
		if (strcmp(&aText[0], "SIZE") == 0)
		{
			fscanf(pFile, "%s %f %f", &aText[0],
				&pTextureSetInfo->fWidth,
				&pTextureSetInfo->fHeight);
		}
		// SIZEDEST����������ړI�T�C�Y�����i�[
		if (strcmp(&aText[0], "SIZEDEST") == 0)
		{
			fscanf(pFile, "%s %f %f", &aText[0],
				&pTextureSetInfo->fWidthDest,
				&pTextureSetInfo->fHeightDest);
		}
		// END_TEXTURESET����������e�N�X�`���z�u���̓ǂݍ��݂��I����
		if (strcmp(&aText[0], "END_TEXTURESET") == 0)
		{
			// �e�N�X�`���̐ݒu
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

			// �e�N�X�`�����̓ǂݍ��݂��I����
			g_bUIset.bTexSet = false;
		}
	}
}

//-----------------------------------------------------------------
// �Z���N�g���[�h�z�u���̓ǂݍ���
//-----------------------------------------------------------------
void LoadSelectModeData(FILE *pFile, char *aText)
{
	// �t�B�[���h���̎擾
	SelectModeSetData *pSelectModeSetData = &g_SelectModeSetData;

	// SELECTMODESET���������Z���N�g���[�h�z�u����ǂݍ��ދ���^����
	if (strcmp(&aText[0], "SELECTMODESET") == 0)
	{
		// �ϐ��̏�����
		pSelectModeSetData->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pSelectModeSetData->col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pSelectModeSetData->fWidth = 0.0f;
		pSelectModeSetData->fHeight = 0.0f;
		pSelectModeSetData->nTexType = -1;

		g_bUIset.bSelectModeSet = true;
	}
	if (g_bUIset.bSelectModeSet == true)
	{
		// TEXTYPE����������e�N�X�`���ԍ����i�[
		if (strcmp(&aText[0], "TEXTYPE") == 0)
		{
			fscanf(pFile, "%s %d", &aText[0], &pSelectModeSetData->nTexType);
		}
		// POS����������ʒu�����i�[
		if (strcmp(&aText[0], "POS") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pSelectModeSetData->pos.x,
				&pSelectModeSetData->pos.y,
				&pSelectModeSetData->pos.z);
		}
		// COL����������F�����i�[
		if (strcmp(&aText[0], "COL") == 0)
		{
			fscanf(pFile, "%s %f %f %f %f", &aText[0],
				&pSelectModeSetData->col.r,
				&pSelectModeSetData->col.g,
				&pSelectModeSetData->col.b,
				&pSelectModeSetData->col.a);
		}
		// SIZE����������T�C�Y�����i�[
		if (strcmp(&aText[0], "SIZE") == 0)
		{
			fscanf(pFile, "%s %f %f", &aText[0],
				&pSelectModeSetData->fWidth,
				&pSelectModeSetData->fHeight);
		}
		// END_SELECTMODESET����������Z���N�g���[�h�z�u���̓ǂݍ��݂��I����
		if (strcmp(&aText[0], "END_SELECTMODESET") == 0)
		{			// �t�B�[���h���̓ǂݍ��݂��I����
			g_bUIset.bSelectModeSet = false;
		}
	}
}

//-----------------------------------------------------------------
// �{�^���w���z�u���̓ǂݍ���
//-----------------------------------------------------------------
void LoadPressAnyButtonData(FILE *pFile, char *aText)
{
	// �t�B�[���h���̎擾
	PressAnyButtonSetData *pPressAnyButtonSetData = &g_PressAnyButtonSetData;

	// PRESSANYBUTTONSET���������Z���N�g���[�h�z�u����ǂݍ��ދ���^����
	if (strcmp(&aText[0], "PRESSANYBUTTONSET") == 0)
	{
		// �ϐ��̏�����
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
		// TEXTYPE����������e�N�X�`���ԍ����i�[
		if (strcmp(&aText[0], "TEXTYPE") == 0)
		{
			fscanf(pFile, "%s %d", &aText[0], &pPressAnyButtonSetData->nTexType);
		}
		// POS����������ʒu�����i�[
		if (strcmp(&aText[0], "POS") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pPressAnyButtonSetData->pos.x,
				&pPressAnyButtonSetData->pos.y,
				&pPressAnyButtonSetData->pos.z);
		}
		// COL����������F�����i�[
		if (strcmp(&aText[0], "COL") == 0)
		{
			fscanf(pFile, "%s %f %f %f %f", &aText[0],
				&pPressAnyButtonSetData->col.r,
				&pPressAnyButtonSetData->col.g,
				&pPressAnyButtonSetData->col.b,
				&pPressAnyButtonSetData->col.a);
		}
		// REMOVE���������烿�l�����ʏ����i�[
		if (strcmp(&aText[0], "REMOVE") == 0)
		{
			fscanf(pFile, "%s %f", &aText[0],
				&pPressAnyButtonSetData->fRemoveAlpha);
		}
		// SIZE����������T�C�Y�����i�[
		if (strcmp(&aText[0], "SIZE") == 0)
		{
			fscanf(pFile, "%s %f %f", &aText[0],
				&pPressAnyButtonSetData->fWidth,
				&pPressAnyButtonSetData->fHeight);
		}
		// END_PRESSANYBUTTONSET����������Z���N�g���[�h�z�u���̓ǂݍ��݂��I����
		if (strcmp(&aText[0], "END_PRESSANYBUTTONSET") == 0)
		{
			// �Z���N�g���[�h�̐ݒu
			SetPressAnyButton(pPressAnyButtonSetData->pos,
				pPressAnyButtonSetData->col,
				pPressAnyButtonSetData->fRemoveAlpha,
				pPressAnyButtonSetData->fWidth,
				pPressAnyButtonSetData->fHeight,
				pPressAnyButtonSetData->nTexType);

			// �t�B�[���h���̓ǂݍ��݂��I����
			g_bUIset.bPressAnyButtonSet = false;
		}
	}
}