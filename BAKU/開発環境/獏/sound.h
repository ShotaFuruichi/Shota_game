//=============================================================================
//
// Contents	: �T�E���h���� [sound.h]
// Author	: ShotaFuruichi
// Since	: 2021/02/26
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
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_SE_MAGIC,		// �U�����@
	SOUND_LABEL_SE_HEAL,		// �񕜖��@
	SOUND_LABEL_SE_CHANT,		// �r����
	SOUND_LABEL_SE_HIT,			// �q�b�g��
	SOUND_LABEL_SE_ENEATTACK,	// �G�U����
	SOUND_LABEL_SE_ENEATTACK2,	// �G�U����2
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

