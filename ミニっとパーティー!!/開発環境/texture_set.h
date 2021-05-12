//-------------------------------------------------------------------
//
// �e�N�X�`���z�u�w�b�_�[ (texture_set.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _TEXTURESET_H_
#define _TEXTURESET_H_

#include "main.h"
#include "texture.h"

//-----------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------
#define MAX_TEXTURE_SET	(64)							// �w�i�̎��

//-------------------------------------------------------------------
// �\���̂̒�`
//-------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ��]
	D3DXVECTOR3 move;		// �ړ�
	D3DXCOLOR col;			// �F
	float fRemoveAlpha;		// ���l�̌�����
	float fWidthDest;		// �ړI�̕�
	float fHeightDest;		// �ړI�̍���
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
	int nType;				// �ړ��^�C�v
	int nTexType;			// �e�N�X�`���^�C�v
	bool bUse;				// �g�p���Ă��邩�ǂ���
}TextureSetInfo;

typedef struct
{
	TextureSetInfo textureSetInfo[MAX_TEXTURE_SET];		// �e�N�X�`���z�u���
	int nNumTextureSet;									// �u���e�N�X�`���̐�
	char aTextName[128];								// �ǂݍ��ރe�L�X�g
}TextureSet;

//-------------------------------------------------------------------
// �v���g�^�C�v�錾
//-------------------------------------------------------------------
HRESULT InitTextureSet(void);		// �e�N�X�`���ݒu�̏���������
void UninitTextureSet(void);		// �e�N�X�`���ݒu�̏I������
void UpdateTextureSet(void);		// �e�N�X�`���ݒu�̍X�V����
void DrawTextureSet(void);			// �e�N�X�`���ݒu�̕`�揈��

void SetVertexTextureSet(int nCnt); // ���_���W�̐ݒ�
void SetTexture(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXCOLOR col,
	float fRemoveAlpha,float fWidth, float fHeight,float fWidthDest, float fHeightDest,
	int type, int textype);

TextureSet *GetTextureSet(void);	// �e�N�X�`���z�u���̎擾

#endif