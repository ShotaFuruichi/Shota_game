//-------------------------------------------------------------------
//
// �L�����Z���N�g��ʔw�i�w�b�_�[ (chara_select_bg.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _CHARASELECTBG_H_
#define _CHARASELECTBG_H_

#include "main.h"

//-------------------------------------------------------------------
// �v���g�^�C�v�錾
//-------------------------------------------------------------------
HRESULT InitCharaSelectBg(void);		// �L�����Z���N��ʔw�i�̏���������
void UninitCharaSelectBg(void);			// �L�����Z���N��ʔw�i�̏I������
void UpdateCharaSelectBg(void);			// �L�����Z���N��ʔw�i�̍X�V����
void DrawCharaSelectBg(void);			// �L�����Z���N��ʔw�i�̕`�揈��
void SetVertexCharaSelectBg(int nCnt);	// �L�����Z���N��ʔw�i�̒��_���W�̐ݒ�

#endif