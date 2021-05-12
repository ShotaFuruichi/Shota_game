//-------------------------------------------------------------------
//
// �e�L�X�g�ǂݍ��݃w�b�_�[ (LoadSceneData.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _LOADSCENEDATA_H_
#define _LOADSCENEDATA_H_

#include "main.h"
#include "stdio.h"

//-------------------------------------------------------------------
// �v���g�^�C�v�錾
//-------------------------------------------------------------------
void LoadSceneInfoText(void);	// �V�[�����e�L�X�g�̓ǂݍ���

void LoadSceneData(void);		// �V�[���f�[�^�̓ǂݍ���

void LoadUIsetInfoText(FILE *pFile, char *aText);			// UI�Z�b�g���e�L�X�g�̓ǂݍ���
void LoadTextureInfo(FILE *pFile, char *aText);				// �e�N�X�`�����̓ǂݍ���
void LoadModelInfo(FILE *pFile, char *aText);				// ���f�����̓ǂݍ���
void LoadCameraInfo(FILE *pFile, char *aText);				// �J�������̓ǂݍ���
void LoadLightInfo(FILE *pFile, char *aText);				// ���C�g���̓ǂݍ���
void LoadFieldInfo(FILE *pFile, char *aText);				// �t�B�[���h���̓ǂݍ���
void LoadWallInfo(FILE *pFile, char *aText);				// �Ǐ��̓ǂݍ���
void LoadModelSetInfo(FILE *pFile, char *aText);			// ���f���z�u���̓ǂݍ���
void LoadPlayerSetInfo(FILE *pFile, char *aText);			// �v���C���[�z�u���̓ǂݍ���

#endif