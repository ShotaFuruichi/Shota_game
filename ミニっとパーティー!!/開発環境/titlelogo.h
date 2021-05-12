//-------------------------------------------------------------------
//
// �^�C�g�����S�w�b�_�[ (titlelogo.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

#include "main.h"

//-------------------------------------------------------------------
// �\���̂̒�`
//-------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ��]
	float fRateWidth;		// ���̊���
	float fRateHeight;		// �����̊���
	float fMoveRateWidth;	// �����̑�����
	float fMoveRateHeight;	// �����̑�����
	float fWidth;			// ��
	float fHeight;			// ����
	float fAngle;			// �p�x
	float fLength;			// �Ίp���̒���
	bool bMaxSize;			// �ő�T�C�Y�ɂȂ������ǂ���
	bool bNormalSize;		// ���ʂ̃T�C�Y�ɂȂ������ǂ���
}TITLELOGO;

//-------------------------------------------------------------------
// �v���g�^�C�v�錾
//-------------------------------------------------------------------
HRESULT InitTitlelogo(void);				// �^�C�g�����S�̏���������
void UninitTitlelogo(void);					// �^�C�g�����S�̏I������
void UpdateTitlelogo(void);					// �^�C�g�����S�̍X�V����
void DrawTitlelogo(void);					// �^�C�g�����S�̕`�揈��

void SetVerTexTitleLogo(int nIdx);			// ���_���W�̐ݒ�
bool GetFall(void);							// �^�C�g�����S�̏��̎擾

#endif