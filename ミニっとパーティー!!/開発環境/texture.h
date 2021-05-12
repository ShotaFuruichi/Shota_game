//-------------------------------------------------------------------
//
// �e�N�X�`���w�b�_�[ (texture.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "main.h"

//-------------------------------------------------------------------
// �\���̂̒�`
//-------------------------------------------------------------------
typedef struct
{
	LPDIRECT3DTEXTURE9 pTexture;	// �e�N�X�`���ւ̃|�C���^
	char aTexcharName[128];			// �e�N�X�`���̖��O
}Texture_Info;

typedef struct
{
	Texture_Info TextureInfo[20];	// �e�N�X�`�����
	int nNumTexture;				// �e�N�X�`���̐�
}Texture;

//-------------------------------------------------------------------
// �v���g�^�C�v�錾
//-------------------------------------------------------------------
void LoadTexture(void);		// �e�N�X�`���̓ǂݍ���
void ReleaseTexture(void);	// �e�N�X�`���̉��

Texture *GetTexture(void);	// �e�N�X�`�����̎擾
Texture *GetUITexture(void);	// �e�N�X�`�����̎擾

#endif