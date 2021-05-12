//-----------------------------------------------------------------
//
// ���b�V���t�B�[���h (meshfield.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "meshfield.h"
#include "input.h"
#include "gamepad.h"
#include "shadow.h"
#include "texture.h"

//-----------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------
#define MAX_MESHFIELD		(16)										// ���b�V���t�B�[���h�ő吔
#define MAX_MESHFIELD_VTX	(200)										// ���b�V���t�B�[���h�̒��_�ő吔
#define MAX_INDEX			(200)										// �C���f�b�N�X�ő吔

#define WIDTH_NUM			(g_MeshField[nCntMeshField].nCntMeshFieldX)	// ��
#define DEPTH_NUM			(g_MeshField[nCntMeshField].nCntMeshFieldZ)	// �s
#define WIDTH				(g_MeshField[nCntMeshField].fWidth)			// ��
#define DEPTH				(g_MeshField[nCntMeshField].fDepth)			// ���s
#define WIDTH_VEC			(WIDTH_NUM + 1)								// ��̒��_��
#define DEPTH_VEC			(DEPTH_NUM + 1)								// �s�̒��_��

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
MeshField g_MeshField[MAX_MESHFIELD];							// ���b�V���t�B�[���h���

//-----------------------------------------------------------------
// ���b�V���t�B�[���h�̏���������
//-----------------------------------------------------------------
HRESULT InitMeshField(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n���A������
	pDevice = GetDevice();

	// �ϐ��̏�����
	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		g_MeshField[nCntMeshField].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshField[nCntMeshField].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshField[nCntMeshField].nCntMeshFieldX = 0;
		g_MeshField[nCntMeshField].nCntMeshFieldZ = 0;
		g_MeshField[nCntMeshField].nCntVecX = 0;
		g_MeshField[nCntMeshField].nCntVecZ = 0;
		g_MeshField[nCntMeshField].fWidth = 0.0f;
		g_MeshField[nCntMeshField].fDepth = 0.0f;
		g_MeshField[nCntMeshField].fsizeWidth = 0.0f;
		g_MeshField[nCntMeshField].fsizeDepth = 0.0f;
		g_MeshField[nCntMeshField].nIndex = 0;
		g_MeshField[nCntMeshField].nVetex = 0;
		g_MeshField[nCntMeshField].nPrimitive = 0;
		g_MeshField[nCntMeshField].nIdxtexture = -1;
		g_MeshField[nCntMeshField].bUse = false;

		// ���_�o�b�t�@�̐���
		if (FAILED(pDevice->CreateVertexBuffer(
			sizeof(VERTEX_3D) * MAX_MESHFIELD_VTX,	// �m�ۂ���o�b�t�@�T�C�Y
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,									// ���_�t�H�[�}�b�g
			D3DPOOL_MANAGED,
			&g_MeshField[nCntMeshField].pVtxBuffMeshField,
			NULL)))
		{
			return E_FAIL;
		}

		// �C���f�b�N�X�o�b�t�@�̐���
		if (FAILED(pDevice->CreateIndexBuffer(
			sizeof(WORD) * MAX_INDEX,	// �m�ۂ���o�b�t�@�T�C�Y
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,						// �t�H�[�}�b�g
			D3DPOOL_MANAGED,
			&g_MeshField[nCntMeshField].pIdxBuffMeshField,
			NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//-----------------------------------------------------------------
// ���b�V���t�B�[���h�̏I������
//-----------------------------------------------------------------
void UninitMeshField(void)
{
	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		// �C���f�b�N�X�̊J��
		if (g_MeshField[nCntMeshField].pIdxBuffMeshField != NULL)
		{
			g_MeshField[nCntMeshField].pIdxBuffMeshField->Release();
			g_MeshField[nCntMeshField].pIdxBuffMeshField = NULL;
		}

		// ���_�o�b�t�@�̊J��
		if (g_MeshField[nCntMeshField].pVtxBuffMeshField != NULL)
		{
			g_MeshField[nCntMeshField].pVtxBuffMeshField->Release();
			g_MeshField[nCntMeshField].pVtxBuffMeshField = NULL;
		}
	}
}

//-----------------------------------------------------------------
// ���b�V���t�B�[���h�̍X�V����
//-----------------------------------------------------------------
void UpdateMeshField(void)
{

}

//-----------------------------------------------------------------
// ���b�V���t�B�[���h�̕`�揈��
//-----------------------------------------------------------------
void DrawMeshField(void)
{
	// �ϐ��錾
	Texture *pTexture = GetTexture();
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		if (g_MeshField[nCntMeshField].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_MeshField[nCntMeshField].mtxWorld);

			// �����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshField[nCntMeshField].rot.y, g_MeshField[nCntMeshField].rot.x, g_MeshField[nCntMeshField].rot.z);
			D3DXMatrixMultiply(&g_MeshField[nCntMeshField].mtxWorld, &g_MeshField[nCntMeshField].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_MeshField[nCntMeshField].pos.x, g_MeshField[nCntMeshField].pos.y, g_MeshField[nCntMeshField].pos.z);
			D3DXMatrixMultiply(&g_MeshField[nCntMeshField].mtxWorld, &g_MeshField[nCntMeshField].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_MeshField[nCntMeshField].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_MeshField[nCntMeshField].pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

			// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_MeshField[nCntMeshField].pIdxBuffMeshField);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �|���S���̕`��
			pDevice->SetTexture(0, pTexture->TextureInfo[g_MeshField[nCntMeshField].nIdxtexture].pTexture);
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_MeshField[nCntMeshField].nVetex, 0, g_MeshField[nCntMeshField].nPrimitive);
		}
	}
}

//-----------------------------------------------------------------
// ���b�V���t�B�[���h�Ƃ̓����蔻��
//-----------------------------------------------------------------
bool CollisionMeshField(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld,int nIdxShadow, D3DXVECTOR3 *PosShadow)
{
	// �ϐ��錾
	bool bLand = false;

	for (int nCntMeshFiled = 0; nCntMeshFiled < MAX_MESHFIELD; nCntMeshFiled++)
	{
		if (g_MeshField[nCntMeshFiled].bUse == true)
		{
			// �����蔻��
			if (pPosOld->x > g_MeshField[nCntMeshFiled].pos.x - g_MeshField[nCntMeshFiled].fsizeWidth / 2.0f && pPosOld->x < g_MeshField[nCntMeshFiled].pos.x + g_MeshField[nCntMeshFiled].fsizeWidth / 2.0f &&
				pPosOld->z > g_MeshField[nCntMeshFiled].pos.z - g_MeshField[nCntMeshFiled].fsizeDepth / 2.0f && pPosOld->z < g_MeshField[nCntMeshFiled].pos.z + g_MeshField[nCntMeshFiled].fsizeDepth / 2.0f)
			{// �͈͓��ɂ���Ƃ�����
				if (pPosOld->y >= g_MeshField[nCntMeshFiled].pos.y)
				{
					if (pPos->y < g_MeshField[nCntMeshFiled].pos.y)
					{
						// ���ɂ߂荞�񂾂���W�����킹��
						pPos->y = g_MeshField[nCntMeshFiled].pos.y;

						// ����Ă��邱�Ƃ�`����
						bLand = true;
					}
				}
				// �ǂ̈ʒu��ۑ�
				PosShadow->y = g_MeshField[nCntMeshFiled].pos.y;
			}
		}
	}
	return bLand;
}

//-----------------------------------------------------------------
// ���b�V���t�B�[���h�Z�b�g
//-----------------------------------------------------------------
void SetMeshField(int type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int blockX, int blockZ, float sizeX, float sizeZ)
{
	// �\���̂̃|�C���^�ϐ�
	MeshField *pMeshField = &g_MeshField[0];

	// ���b�V���t�B�[���h�Z�b�g
	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++,pMeshField++)
	{
		if (pMeshField->bUse == false)
		{
			// �e�N�X�`���^�C�v�̐ݒ�
			pMeshField->nIdxtexture = type;

			// �ʒu�̐ݒ�
			pMeshField->pos = pos;

			// �p�x�̐ݒ�
			pMeshField->rot = rot;

			// �u���u���b�N��(X)�̐ݒ�
			pMeshField->nCntMeshFieldX = blockX;

			// �u���u���b�N��(Z)�̐ݒ�
			pMeshField->nCntMeshFieldZ = blockZ;

			// �T�C�Y(X)�̐ݒ�
			pMeshField->fWidth = sizeX;

			// �T�C�Y(Z)�̐ݒ�
			pMeshField->fDepth = sizeZ;

			// �T�C�Y�̊m��
			g_MeshField[nCntMeshField].fsizeWidth = g_MeshField[nCntMeshField].nCntMeshFieldX * g_MeshField[nCntMeshField].fWidth;
			g_MeshField[nCntMeshField].fsizeDepth = g_MeshField[nCntMeshField].nCntMeshFieldZ * g_MeshField[nCntMeshField].fDepth;

			// ���_���ƃC���f�b�N�X���A�v���~�e�B�u���̊m��
			pMeshField->nVetex = ((pMeshField->nCntMeshFieldX + 1) * (pMeshField->nCntMeshFieldZ + 1));
			pMeshField->nPrimitive = (pMeshField->nCntMeshFieldX * pMeshField->nCntMeshFieldZ * 2) + (4 * (pMeshField->nCntMeshFieldZ - 1));

			// �g�p��Ԃ�true�ɂ���
			pMeshField->bUse = true;

			// �\���̂̃|�C���^�ϐ�
			VERTEX_3D *pVtx;

			// �C���f�b�N�X���ւ̃|�C���^
			WORD *pIdx;

			// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_MeshField[nCntMeshField].pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

			// �C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
			g_MeshField[nCntMeshField].pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

			for (int nCntZ = 0; nCntZ < DEPTH_VEC; nCntZ++)
			{
				for (int nCntX = 0; nCntX < WIDTH_VEC; nCntX++)
				{
					// ���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3((-g_MeshField[nCntMeshField].fsizeWidth / 2.0f + (float)nCntX * g_MeshField[nCntMeshField].fWidth) + g_MeshField[nCntMeshField].pos.x,
						0.0f,
						((g_MeshField[nCntMeshField].fsizeDepth / 2.0f) - (float)nCntZ * g_MeshField[nCntMeshField].fDepth) + g_MeshField[nCntMeshField].pos.z);

					// �@���x�N�g���̐ݒ�
					pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

					// ���_�J���[�̐ݒ�
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					// �e�N�X�`�����W
					pVtx[0].tex = D3DXVECTOR2(1.0f * nCntX, 1.0f * nCntZ);

					// ���̏��
					pVtx++;
				}
			}

			for (int nCntZ = 0; nCntZ < DEPTH_NUM; nCntZ++)
			{
				for (int nCntX = 0; nCntX < WIDTH_VEC + 1; nCntX++)
				{
					if (nCntX != 0 && nCntX == WIDTH_VEC && nCntZ != DEPTH_NUM - 1)
					{// �E�[����܂�Ԃ���
						pIdx[0] = pIdx[-1];
						pIdx[1] = pIdx[-2] + 1;
					}
					else if (nCntZ == DEPTH_NUM - 1 && nCntX == WIDTH_VEC)
					{// �I�����ɖ�������
						break;
					}
					else
					{// �ʏ�z�u
						pIdx[0] = WIDTH_VEC + (WIDTH_VEC * nCntZ) + nCntX;
						pIdx[1] = pIdx[0] - WIDTH_VEC;
					}
					// ���̏��Ɉړ�
					pIdx += 2;
				}
			}
			// ���_�o�b�t�@���A�����b�N����
			g_MeshField[nCntMeshField].pVtxBuffMeshField->Unlock();

			// �C���f�b�N�X�o�b�t�@���A�����b�N����
			g_MeshField[nCntMeshField].pIdxBuffMeshField->Unlock();

			break;
		}
	}
}

//-----------------------------------------------------------------
// ���b�V���t�B�[���h���̎擾
//-----------------------------------------------------------------
MeshField *GetMeshField(void)
{
	return &g_MeshField[0];
}