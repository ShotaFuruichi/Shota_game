//-------------------------------------------------------------------
//
// �|�[�Y�w�b�_�[ (pause.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _SELECTMODE_H_
#define _SELECTMODE_H_

#include "main.h"

//-------------------------------------------------------------------
// �|�[�Y�̏��
//-------------------------------------------------------------------
typedef enum
{
	PAUSE_MENU_CONTINUE = 0,	// �R���e�B�j���[
	PAUSE_MENU_RETRY,			// ���g���C
	PAUSE_MENU_QUIT,			// �I��
	PAUSE_MENU_MAX,
}SELECT_MENU;

//-------------------------------------------------------------------
// �v���g�^�C�v�錾
//-------------------------------------------------------------------
HRESULT InitSelectMode(void);				// �|�[�Y�̏���������
void UninitSelectMode(void);					// �|�[�Y�̏I������
void UpdateSelectMode(void);					// �|�[�Y�̍X�V����
void DrawSelectMode(void);					// �|�[�Y�̕`�揈��

void SetVertexSelectMode(int nCntPause);		// �|�[�Y��ʂ̒��_���W
void SelectMenu(int nCnt);				// �|�[�Y���j���[

#endif