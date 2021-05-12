//-------------------------------------------------------------------
//
// �L�����Z���N�g�t���[���w�b�_�[ (chara_select_frame.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _CHARASELECTFRAME_H_
#define _CHARASELECTFRAME_H_

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
	int nIdxChara;					// ���Ԗڂ̃L�����Ƀt���[�������邩
	int nNumChara;					// ���Ԗڂ̃L������I�񂾂�
	int nCounterLandam;				// �����_���I�����̃J�E���g
	bool bSelect;					// �I�����ꂽ���ǂ���
	int nSaveCommand[MAX_COMMAND];	// �R�}���h�ۑ��p
	bool bSecrec;					// �B���L�����̂��邩�ǂ���
}CharaSelectFrame;

//-------------------------------------------------------------------
// �v���g�^�C�v�錾
//-------------------------------------------------------------------
HRESULT InitCharaSelectFrame(void);					// �L�����Z���N�g�t���[���̏���������
void UninitCharaSelectFrame(void);					// �L�����Z���N�g�t���[���̏I������
void UpdateCharaSelectFrame(void);					// �L�����Z���N�g�t���[���̍X�V����
void DrawCharaSelectFrame(void);					// �L�����Z���N�g�t���[���̕`�揈��

bool SecretChara(int nCntPlayer, int nNumChara);	// �V�[�N���b�g�L�������o��������
void SetVertexCharaSelectFrame(int nIdx);			// �L�����Z���N�g�t���[���̒��_���W�̐ݒ�
CharaSelectFrame *GetCharaSelectFrame(void);		// �L�����Z���N�g�t���[�����̎擾

int GetFrame(void);

#endif