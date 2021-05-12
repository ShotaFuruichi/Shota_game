//-------------------------------------------------------------------
//
// �L��������w�b�_�[ (dicision_chara.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _DICISIONCHARA_H_
#define _DICISIONCHARA_H_

#include "main.h"

//-------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------
#define MAX_COMMAND	(5)						// �R�}���h��

//-----------------------------------------------------------------
// �\���̂̒�`
//-----------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;				// �ʒu
	D3DXCOLOR col;					// �F
	float fWidth;					// ��
	float fHeight;					// ����
	int nTxType;					// �e�N�X�`���^�C�v
	bool bDicision;					// ���肵�����ǂ���
}DicisionChara;

//-------------------------------------------------------------------
// �v���g�^�C�v�錾
//-------------------------------------------------------------------
HRESULT InitDicisionChara(void);				// �L��������̏���������
void UninitDicisionChara(void);					// �L��������̏I������
void UpdateDicisionChara(void);					// �L��������̍X�V����
void DrawDicisionChara(void);					// �L��������̕`�揈��

void SetVertexDicisionChara(int nIdx);			// �L��������̒��_���W�̐ݒ�
DicisionChara *GetDicisionChara(void);			// �L����������̎擾

void SetDicisionChara(bool bDicision, int nCntPlayer);			// ���肵���Ƃ�

#endif