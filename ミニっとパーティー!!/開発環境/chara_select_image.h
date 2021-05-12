//-------------------------------------------------------------------
//
// �L�����Z���N�g�C���[�W�w�b�_�[ (chara_select_image.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _CHARASELECTIMAGE_H_
#define _CHARASELECTIMAGE_H_

#include "main.h"

//-------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------
#define MAX_CHARAIMAGE		(5)						// �e�N�X�`������

//-----------------------------------------------------------------
// �\���̂̒�`
//-----------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXCOLOR col;			// �F
	float fWidth;			// ��
	float fHeight;			// ����
	bool bSelect;			// �I�����ꂽ���ǂ���
}CharaSelectImage;

//-------------------------------------------------------------------
// �v���g�^�C�v�錾
//-------------------------------------------------------------------
HRESULT InitCharaSelectImage(void);			// �L�����Z���N�g�C���[�W�̏���������
void UninitCharaSelectImage(void);			// �L�����Z���N�g�C���[�W�̏I������
void UpdateCharaSelectImage(void);			// �L�����Z���N�g�C���[�W�̍X�V����
void DrawCharaSelectImage(void);			// �L�����Z���N�g�C���[�W�̕`�揈��

CharaSelectImage *GetCharaSelectImage(void);	// �L�����Z���N�g�C���[�W���̎擾

#endif