//-------------------------------------------------------------------
//
// �ǃw�b�_�[ (wall.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

//-----------------------------------------------------------------
// �\���̂̒�`
//-----------------------------------------------------------------
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffWall = NULL;			// �ǂ̒��_�o�b�t�@�̃|�C���^
	LPDIRECT3DINDEXBUFFER9 pIdxBuffWall = NULL;				// �ǂ̃C���f�b�N�X�ւ̃|�C���^
	D3DXMATRIX mtxWorld;		// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;			// �ǂ̒��S���W
	D3DXVECTOR3 rot;			// �ǂ̌���
	D3DXVECTOR3 moveRot;		// ��]��
	int nCntWallX;				// �ǂ̐�(��)
	int nCntWallY;				// �ǂ̐�(�s)
	int nCntVecX;				// ��̒��_��
	int nCntVecY;				// �s�̒��_��
	float fWidth;				// ��
	float fHieght;				// ���s
	float fsizeWidth;			// ���̃T�C�Y
	float fsizeHieght;			// ���s�̃T�C�Y
	int nVetex;					// ���_��
	int nPrimitive;				// �v���~�e�B�u��
	int nIndex;					// �C���f�b�N�X��
	int nIdxtexture;			// ���Ԗڂ̃e�N�X�`����
	bool bUse;					// �g�p���Ă��邩�ǂ���
}Wall;

//-------------------------------------------------------------------
// �v���g�^�C�v�錾
//-------------------------------------------------------------------
HRESULT InitWall(void);								// �ǂ̏���������
void UninitWall(void);								// �ǂ̏I������
void UpdateWall(void);								// �ǂ̍X�V����
void DrawWall(void);								// �ǂ̕`�揈��

void SetWall(int type, D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR3 moveRot,
	int blockX, int blockY, float sizeX, float sizeY);		// �ǂ̔z�u
void CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pvtxMin, D3DXVECTOR3 *pvtxMax);					// �ǂƂ̓����蔻��
Wall *GetWall(void);									// �Ǐ��̎擾

#endif