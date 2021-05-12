//-------------------------------------------------------------------
//
// ���b�V���t�B�[���h�w�b�_�[ (meshfield.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"

//-----------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------
#define MAX_MESHFIELD	(16)

//-----------------------------------------------------------------
// �\���̂̒�`
//-----------------------------------------------------------------
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffMeshField = NULL;				// ���b�V���t�B�[���h�̒��_�o�b�t�@�̃|�C���^
	LPDIRECT3DINDEXBUFFER9 pIdxBuffMeshField = NULL;				// ���b�V���t�B�[���h�̃C���f�b�N�X�ւ̃|�C���^
	D3DXMATRIX mtxWorld;		// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;			// �ǂ̒��S���W
	D3DXVECTOR3 rot;			// �ǂ̌���
	int nCntMeshFieldX;			// �ǂ̐�(��)
	int nCntMeshFieldZ;			// �ǂ̐�(�s)
	int nCntVecX;				// ��̒��_��
	int nCntVecZ;				// �s�̒��_��
	float fWidth;				// ��
	float fDepth;				// ���s
	float fsizeWidth;			// ���̃T�C�Y
	float fsizeDepth;			// ���s�̃T�C�Y
	int nVetex;					// ���_��
	int nPrimitive;				// �v���~�e�B�u��
	int nIndex;					// �C���f�b�N�X��
	int nIdxtexture;			// ���Ԗڂ̃e�N�X�`����
	bool bUse;					// �g�p���Ă��邩�ǂ���
}MeshField;

//-------------------------------------------------------------------
// �v���g�^�C�v�錾
//-------------------------------------------------------------------
HRESULT InitMeshField(void);									// ���b�V���t�B�[���h�̏���������
void UninitMeshField(void);										// ���b�V���t�B�[���h�̏I������
void UpdateMeshField(void);										// ���b�V���t�B�[���h�̍X�V����
void DrawMeshField(void);										// ���b�V���t�B�[���h�̕`�揈��

bool CollisionMeshField(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, int nIdxShadow, D3DXVECTOR3 *PosShadow);// �����蔻��

void SetMeshField(int type,D3DXVECTOR3 pos, D3DXVECTOR3 rot, 
	int blockX, int blockZ, float sizeX, float sizeZ);				// ���b�V���t�B�[���h�Z�b�g

MeshField *GetMeshField(void);									// ���b�V���t�B�[���h���̎擾

#endif