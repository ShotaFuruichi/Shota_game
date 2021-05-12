//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_TITLE = 0,		// �^�C�g��
	SOUND_LABEL_TUTORIAL,				// �`���[�g���A��
	SOUND_LABEL_CHARASELECT,			// �o�g��
	SOUND_LABEL_GAME,			// ���U���gBGM
	SOUND_LABEL_RESULT,		// �����L���O
	SOUND_LABEL_SE_COUNTDOWN,		// �W�����v��
	SOUND_LABEL_SE_START,		// ���މ�
	SOUND_LABEL_SE_CURSOR,		// �G�ɓ��������Ƃ�
	SOUND_LABEL_SE_DICIDE,		// �_���[�W���󂯂��Ƃ�
	SOUND_LABEL_SE_FINISH,		// �R�C���l��
	SOUND_LABEL_SE_PAUSE,		// �I��(��)
	SOUND_LABEL_SE_RESULT_IN,			// �I��(��)
	SOUND_LABEL_SE_CANSEL,	// �|�[�Y���(��)
	SOUND_LABEL_SE_BOMB,
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
