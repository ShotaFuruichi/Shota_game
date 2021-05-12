//-------------------------------------------------------------------
//
// ���f���ݒu�w�b�_�[ (model_set.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _MODELSET_H_
#define _MODELSET_H_

#include "main.h"

//-----------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------
#define MAX_MODEL			(256)	// ���f���̐�
#define MAX_MODEL_TYPE		(50)	// ���f���̎�ނ̐�
#define MAX_TEXTURE_NAME	(128)	// �e�N�X�`����
#define MAX_TEXTURE			(128)	// �e�N�X�`���̐�

//-------------------------------------------------------------------
// �\���̂̒�`
//-------------------------------------------------------------------
typedef struct
{
	LPD3DXMESH pMeshModel;									// ���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER pBuffMatModel;								// �}�e���A��(�ގ����)�ւ̃|�C���^
	DWORD nNumMatModel = 0;									// �}�e���A���̐�
	LPDIRECT3DTEXTURE9 apTextureModelSet[MAX_TEXTURE] = {};	// �e�N�X�`���ւ̃|�C���^
	char aFileName[MAX_TEXTURE_NAME];						// �e�N�X�`����
	D3DXVECTOR3 vtxMinModel;								// ���W�̍ŏ��l
	D3DXVECTOR3 vtxMaxModel;								// ���W�̍ő�l
}Model;

typedef struct
{
	D3DXMATRIX mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;				// ���S���W
	D3DXVECTOR3 rot;				// ��]�p
	D3DXVECTOR3 rotDest;			// �ړI�̉�]�p
	D3DXVECTOR3 vtxMinModel;		// ���W�̍ŏ��l
	D3DXVECTOR3 vtxMaxModel;		// ���W�̍ő�l
	D3DXVECTOR3 aPos[4];			// ������4�_
	D3DXVECTOR3 aVecA[4];			// �����̃x�N�g��
	D3DXVECTOR3 aVecB[4];			// �����̃x�N�g��
	float fVec[4];					// �O�ς̒l
	int nIdx;						// ���f�����ʔԍ�
	int nIdxShadow;					// ���Ԗڂ̉e��
	bool bUse;						// �g�p���Ă邩�ǂ���
	bool bCollision;				// �����蔻�肷�邩�ǂ���
}ModelSetInfo;

typedef struct
{
	int nNumModel;							// ���f���̑���
	Model modelInfo[MAX_MODEL_TYPE];		// ���f�����
	ModelSetInfo modelSet[MAX_MODEL];		// ���f���ݒu
}ModelSet;

//-------------------------------------------------------------------
// �v���g�^�C�v�錾
//-------------------------------------------------------------------
HRESULT InitModelSet(void);											// ���f���̏���������
void UninitModelSet(void);											// ���f���̏I������
void UpdateModelSet(void);											// ���f���̍X�V����
void DrawModelSet(void);											// ���f���̕`�揈��

void TexModel(int ModelSet);										// ���f���̃e�N�X�`��
void VecModel(int ModelSet);										// ���f���̒��_���W

void VecModelSet(int nNumModelSet);									// ���f���̒��_���W

void SetModel(int type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nCollition);	// ���f���Z�b�g

bool CollisionModelSet(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld,
	D3DXVECTOR3 *pMove,D3DXVECTOR3 *pvtxMin, D3DXVECTOR3 *pvtxMax, int nIdxShadow, D3DXVECTOR3 *PosShadow);	// �����蔻��

ModelSet *GetModelSet(void);											// ���f�����̎擾

#endif