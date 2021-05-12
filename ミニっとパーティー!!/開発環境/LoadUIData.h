//-------------------------------------------------------------------
//
// UI���ǂݍ��݃w�b�_�[ (LoadUIData.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _LOADUIDATA_H_
#define _LOADUIDATA_H_

#include "main.h"
#include "stdio.h"

//-------------------------------------------------------------------
// �v���g�^�C�v�錾
//-------------------------------------------------------------------
void LoadUISetData(void);								// UI���̓ǂݍ���
void LoadTextureSetTexInfo(FILE *pFile, char *aText);	// �e�N�X�`�����̓ǂݍ���
void LoadTextureSetData(FILE *pFile, char *aText);		// �e�N�X�`���z�u���̓ǂݍ���
void LoadSelectModeData(FILE *pFile, char *aText);		// �Z���N�g���[�h�z�u���̓ǂݍ���
void LoadPressAnyButtonData(FILE *pFile, char *aText);	// �{�^���w���z�u���̓ǂݍ���

#endif