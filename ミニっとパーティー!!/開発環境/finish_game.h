//-------------------------------------------------------------------
//
// �t�B�j�b�V���Q�[���w�b�_�[ (finish_game.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _FINISHGAME_H_
#define _FINISHGAME_H_

#include "main.h"

//-------------------------------------------------------------------
// �\���̂̒�`
//-------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXCOLOR col;		// �F
	int nTExType;		// �e�N�X�`���̎��
	int nCntAlufa;		// ���l�̈ړ��l
	float fCntSize;		// �T�C�Y�̈ړ��l
	bool bUse;			// �g�p���Ă��邩�ǂ���
	bool bFinish;		// �Q�[�����I��������ǂ���
}FinishGame;

//-------------------------------------------------------------------
// �v���g�^�C�v�錾
//-------------------------------------------------------------------
HRESULT InitFinishGame(void);		// �t�B�j�b�V���Q�[���̏���������
void UninitFinishGame(void);		// �t�B�j�b�V���Q�[���̏I������
void UpdateFinishGame(void);		// �t�B�j�b�V���Q�[���̍X�V����
void DrawFinishGame(void);			// �t�B�j�b�V���Q�[���̕`�揈��
void SetVertexFinishGame(void);		// �t�B�j�b�V���Q�[���̒��_���W�̐ݒ�
void SetFinishGame(bool bFinish);	// �t�B�j�b�V���Q�[���̐ݒ�
bool GetFinishGame(void);

#endif