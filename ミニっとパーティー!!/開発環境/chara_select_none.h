//-------------------------------------------------------------------
//
// �L�����Z���N�g�m�[���w�b�_�[ (chara_select_none.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _CHARASELECTNONE_H_
#define _CHARASELECTNONE_H_

#include "main.h"

//-------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------
#define MAX_CHARANONE		(2)						// �e�N�X�`������

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
}CharaSelectNone;

//-------------------------------------------------------------------
// �v���g�^�C�v�錾
//-------------------------------------------------------------------
HRESULT InitCharaSelectNone(void);			// �L�����Z���N�g�m�[���̏���������
void UninitCharaSelectNone(void);			// �L�����Z���N�g�m�[���̏I������
void UpdateCharaSelectNone(void);			// �L�����Z���N�g�m�[���̍X�V����
void DrawCharaSelectNone(void);			// �L�����Z���N�g�m�[���̕`�揈��

#endif