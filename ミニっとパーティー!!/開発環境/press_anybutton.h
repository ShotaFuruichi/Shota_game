//-------------------------------------------------------------------
//
// �{�^���w���w�b�_�[ (press_anybutton.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _PRESSANYBUTTON_H_
#define _PRESSANYBUTTON_H_

#include "main.h"

//-------------------------------------------------------------------
// �\���̂̒�`
//-------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXCOLOR col;			// �F
	float fRemoveAlpha;		// ���l������
	float fWidth;			// ��
	float fHeight;			// ����
	int nTexType;			// �e�N�X�`���^�C�v
	bool bUse;				// �g�p���Ă��邩�ǂ���
	bool bPressAnyButton;	// �{�^�������������ǂ���
}PressAnyButton;

//-------------------------------------------------------------------
// �v���g�^�C�v�錾
//-------------------------------------------------------------------
HRESULT InitPressAnyButton(void);			// �{�^���w���̏���������
void UninitPressAnyButton(void);			// �{�^���w���̏I������
void UpdatePressAnyButton(void);			// �{�^���w���̍X�V����
void DrawPressAnyButton(void);				// �{�^���w���̕`�揈��

void SetPressAnyButton(D3DXVECTOR3 pos, D3DXCOLOR col, float fRemoveAlpha,
	float fWidth, float fHeight, int nTextype);
void SetVertexPressAnyButton(void);			// ���_���W�̐ݒ�
PressAnyButton *GetPressAnyButton(void);		// �{�^���w�����̎擾

#endif