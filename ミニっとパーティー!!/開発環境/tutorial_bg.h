//-------------------------------------------------------------------
//
// �`���[�g���A����ʔw�i�w�b�_�[ (tutorial_bg.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _TUTORIALBG_H_
#define _TUTORIALBG_H_

#include "main.h"

//-------------------------------------------------------------------
// �v���g�^�C�v�錾
//-------------------------------------------------------------------
HRESULT InitTutorialBg(void);			// �`���[�g���A����ʔw�i�̏���������
void UninitTutorialBg(void);			// �`���[�g���A����ʔw�i�̏I������
void UpdateTutorialBg(void);			// �`���[�g���A����ʔw�i�̍X�V����
void DrawTutorialBg(void);				// �`���[�g���A����ʔw�i�̕`�揈��
void SetVertexTutorialBg(int nCnt);		// �`���[�g���A����ʔw�i�̒��_���W�̐ݒ�

#endif