//-----------------------------------------------------------------
//
// ���f���Z�b�g (model_set.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#include "model_set.h"
#include "shadow.h"
#include "player.h"
#include "camera.h"
#include "light.h"
#include "wall.h"
#include "meshfield.h"

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
ModelSet g_ModelSet;												// ���f�����

//-----------------------------------------------------------------
// ���f���Z�b�g�̏���������
//-----------------------------------------------------------------
HRESULT InitModelSet(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n���A������
	pDevice = GetDevice();

	for (int nCntModel = 0; nCntModel < g_ModelSet.nNumModel; nCntModel++)
	{
		// X�t�@�C���̓ǂݍ���
		if (FAILED(D3DXLoadMeshFromX(&g_ModelSet.modelInfo[nCntModel].aFileName[0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_ModelSet.modelInfo[nCntModel].pBuffMatModel,
			NULL,
			&g_ModelSet.modelInfo[nCntModel].nNumMatModel,
			&g_ModelSet.modelInfo[nCntModel].pMeshModel)))
		{
			return E_FAIL;
		}

		// ���f���̃e�N�X�`��
		TexModel(nCntModel);

		// ���f���̒��_
		VecModel(nCntModel);
	}

	return S_OK;
}

//-----------------------------------------------------------------
// ���f���Z�b�g�̏I������
//-----------------------------------------------------------------
void UninitModelSet(void)
{
	for (int nCnt = 0; nCnt < g_ModelSet.nNumModel; nCnt++)
	{
		g_ModelSet.modelInfo[nCnt].aFileName[0] = {};

		// ���b�V�����̊J��
		if (g_ModelSet.modelInfo[nCnt].pBuffMatModel != NULL)
		{
			g_ModelSet.modelInfo[nCnt].pBuffMatModel->Release();
			g_ModelSet.modelInfo[nCnt].pBuffMatModel = NULL;
		}

		// �}�e���A�����̊J��
		if (g_ModelSet.modelInfo[nCnt].pMeshModel != NULL)
		{
			g_ModelSet.modelInfo[nCnt].pMeshModel->Release();
			g_ModelSet.modelInfo[nCnt].pMeshModel = NULL;
		}
	}

	for (int nCntModelSet = 0; nCntModelSet < MAX_MODEL; nCntModelSet++)
	{
		if (g_ModelSet.modelSet[nCntModelSet].bUse == true)
		{
			g_ModelSet.modelSet[nCntModelSet].bUse = false;
		}
	}
	g_ModelSet.nNumModel = 0;
}

//-----------------------------------------------------------------
// ���f���Z�b�g�̍X�V����
//-----------------------------------------------------------------
void UpdateModelSet(void)
{

}

//-----------------------------------------------------------------
// ���f���Z�b�g�̕`�揈��
//-----------------------------------------------------------------
void DrawModelSet(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				// �}�e���A���f�[�^�ւ̃|�C���^

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	for (int nModelSet = 0; nModelSet < MAX_MODEL; nModelSet++)
	{
		if (g_ModelSet.modelSet[nModelSet].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_ModelSet.modelSet[nModelSet].mtxWorld);

			// �����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ModelSet.modelSet[nModelSet].rot.y, g_ModelSet.modelSet[nModelSet].rot.x, g_ModelSet.modelSet[nModelSet].rot.z);
			D3DXMatrixMultiply(&g_ModelSet.modelSet[nModelSet].mtxWorld, &g_ModelSet.modelSet[nModelSet].mtxWorld, &mtxRot);

			// ���_���W�̕␳
			D3DXVec3TransformCoord(&g_ModelSet.modelSet[nModelSet].vtxMaxModel, &g_ModelSet.modelInfo[g_ModelSet.modelSet[nModelSet].nIdx].vtxMaxModel, &g_ModelSet.modelSet[nModelSet].mtxWorld);
			D3DXVec3TransformCoord(&g_ModelSet.modelSet[nModelSet].vtxMinModel, &g_ModelSet.modelInfo[g_ModelSet.modelSet[nModelSet].nIdx].vtxMinModel, &g_ModelSet.modelSet[nModelSet].mtxWorld);

			// �ő�l�ŏ��l�̕␳
			VecModelSet(nModelSet);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_ModelSet.modelSet[nModelSet].pos.x, g_ModelSet.modelSet[nModelSet].pos.y, g_ModelSet.modelSet[nModelSet].pos.z);
			D3DXMatrixMultiply(&g_ModelSet.modelSet[nModelSet].mtxWorld, &g_ModelSet.modelSet[nModelSet].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_ModelSet.modelSet[nModelSet].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_ModelSet.modelInfo[g_ModelSet.modelSet[nModelSet].nIdx].pBuffMatModel->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_ModelSet.modelInfo[g_ModelSet.modelSet[nModelSet].nIdx].nNumMatModel; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_ModelSet.modelInfo[g_ModelSet.modelSet[nModelSet].nIdx].apTextureModelSet[nCntMat]);

				// ���f��(�p�[�c)�̕`��
				g_ModelSet.modelInfo[g_ModelSet.modelSet[nModelSet].nIdx].pMeshModel->DrawSubset(nCntMat);
			}
			// �ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//-----------------------------------------------------------------
// ���f���̃e�N�X�`��
//-----------------------------------------------------------------
void TexModel(int nModelSet)
{
	// �ϐ��錾
	D3DXMATERIAL *pMat;		// �}�e���A���f�[�^�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�ւ̃|�C���^

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_ModelSet.modelInfo[nModelSet].pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_ModelSet.modelInfo[nModelSet].nNumMatModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_ModelSet.modelInfo[nModelSet].apTextureModelSet[nCntMat]);
		}
	}
}

//-----------------------------------------------------------------
// ���f���̒��_���W
//-----------------------------------------------------------------
void VecModel(int nModelSet)
{
	// �ϐ��錾
	int nNumVtx;			// ���_��
	DWORD sizeFVF;			// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^

	// ���_���̎擾
	nNumVtx = g_ModelSet.modelInfo[nModelSet].pMeshModel->GetNumVertices();

	// ���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_ModelSet.modelInfo[nModelSet].pMeshModel->GetFVF());

	// ���_�o�b�t�@�̃��b�N
	g_ModelSet.modelInfo[nModelSet].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		// ���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		// ���_���r���ă��f���̍ŏ��l�ő�l�𔲂��o��
		if (g_ModelSet.modelInfo[nModelSet].vtxMinModel.x > vtx.x)
		{// X���W�̍ŏ��l
			g_ModelSet.modelInfo[nModelSet].vtxMinModel.x = vtx.x;
		}
		else if (g_ModelSet.modelInfo[nModelSet].vtxMaxModel.x < vtx.x)
		{// X���W�̍ő�l
			g_ModelSet.modelInfo[nModelSet].vtxMaxModel.x = vtx.x;
		}

		if (g_ModelSet.modelInfo[nModelSet].vtxMinModel.y > vtx.y)
		{// Y���W�̍ŏ��l
			g_ModelSet.modelInfo[nModelSet].vtxMinModel.y = vtx.y;
		}
		else if (g_ModelSet.modelInfo[nModelSet].vtxMaxModel.y < vtx.y)
		{// Y���W�̍ő�l
			g_ModelSet.modelInfo[nModelSet].vtxMaxModel.y = vtx.y;
		}

		if (g_ModelSet.modelInfo[nModelSet].vtxMinModel.z > vtx.z)
		{// Z���W�̍ŏ��l
			g_ModelSet.modelInfo[nModelSet].vtxMinModel.z = vtx.z;
		}
		else if (g_ModelSet.modelInfo[nModelSet].vtxMaxModel.z < vtx.z)
		{// Z���W�̍ő�l
			g_ModelSet.modelInfo[nModelSet].vtxMaxModel.z = vtx.z;
		}
		// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFVF;
	}
	// ���_�o�b�t�@�̃A�����b�N
	g_ModelSet.modelInfo[nModelSet].pMeshModel->UnlockVertexBuffer();
}

//-----------------------------------------------------------------
// ���f���̒��_���W�̕␳
//-----------------------------------------------------------------
void VecModelSet(int nNumModelSet)
{
	// �ő�l�ƍŏ��l�̓���ւ�
	if (g_ModelSet.modelSet[nNumModelSet].vtxMaxModel.x < g_ModelSet.modelSet[nNumModelSet].vtxMinModel.x)
	{
		// �ϐ��錾
		float fVecX;		// �ۑ��p

		// �ő�l�ƍŏ��l�����ւ���
		fVecX = g_ModelSet.modelSet[nNumModelSet].vtxMaxModel.x;
		g_ModelSet.modelSet[nNumModelSet].vtxMaxModel.x = g_ModelSet.modelSet[nNumModelSet].vtxMinModel.x;
		g_ModelSet.modelSet[nNumModelSet].vtxMinModel.x = fVecX;
	}
	if (g_ModelSet.modelSet[nNumModelSet].vtxMaxModel.y < g_ModelSet.modelSet[nNumModelSet].vtxMinModel.y)
	{
		// �ϐ��錾
		float fVecY;		// �ۑ��p

		// �ő�l�ƍŏ��l�����ւ���
		fVecY = g_ModelSet.modelSet[nNumModelSet].vtxMaxModel.y;
		g_ModelSet.modelSet[nNumModelSet].vtxMaxModel.y = g_ModelSet.modelSet[nNumModelSet].vtxMinModel.y;
		g_ModelSet.modelSet[nNumModelSet].vtxMinModel.y = fVecY;
	}
	if (g_ModelSet.modelSet[nNumModelSet].vtxMaxModel.z < g_ModelSet.modelSet[nNumModelSet].vtxMinModel.z)
	{
		// �ϐ��錾
		float fVecZ;		// �ۑ��p

		// �ő�l�ƍŏ��l�����ւ�
		fVecZ = g_ModelSet.modelSet[nNumModelSet].vtxMaxModel.z;
		g_ModelSet.modelSet[nNumModelSet].vtxMaxModel.z = g_ModelSet.modelSet[nNumModelSet].vtxMinModel.z;
		g_ModelSet.modelSet[nNumModelSet].vtxMinModel.z = fVecZ;
	}
}

//-----------------------------------------------------------------
// ���f���̓����蔻��
//-----------------------------------------------------------------
bool CollisionModelSet(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pvtxMin, D3DXVECTOR3 *pvtxMax, int nIdxShadow, D3DXVECTOR3 *PosShadow)
{
	// �\���̂̃|�C���^�ϐ�
	ModelSet *pModel = &g_ModelSet;

	// �ϐ��錾
	bool bCollisionModel = false;		// �R�C�����l���������ǂ���

	for (int nModelSet = 0; nModelSet < MAX_MODEL; nModelSet++)
	{
		if (pModel->modelSet[nModelSet].bUse == true)
		{
			if (pModel->modelSet[nModelSet].bCollision == true)
			{
				// �G���v���C���[������悤�ɂ���
				// �G�ƃv���C���[�̕����x�N�g��
				D3DXVECTOR3 ObjectVecCurrent = D3DXVECTOR3(pPos->x - pModel->modelSet[nModelSet].pos.x,
					pPos->y - pModel->modelSet[nModelSet].pos.y,
					pPos->z - pModel->modelSet[nModelSet].pos.z);

				D3DXVECTOR3 ObjectVecOld = D3DXVECTOR3(pPosOld->x - pModel->modelSet[nModelSet].pos.x,
					pPosOld->y - pModel->modelSet[nModelSet].pos.y,
					pPosOld->z - pModel->modelSet[nModelSet].pos.z);

				// ���@�ƒ��S�_�̑Ίp���̒���
				float fLengthCurrent = sqrtf((ObjectVecCurrent.x * ObjectVecCurrent.x) + (ObjectVecCurrent.z * ObjectVecCurrent.z));
				float fLengthOld = sqrtf((ObjectVecOld.x * ObjectVecOld.x) + (ObjectVecOld.z * ObjectVecOld.z));

				if (fLengthCurrent <= 300.0f + 10.0f && fLengthOld > 300.0f)
				{
					if ((pPos->y <= pModel->modelSet[nModelSet].pos.y + pModel->modelSet[nModelSet].vtxMaxModel.y) &&
						(pPos->y >= pModel->modelSet[nModelSet].pos.y + pModel->modelSet[nModelSet].vtxMinModel.y))
					{
						float fAngle = atan2f(pPos->x - pModel->modelSet[nModelSet].pos.x, pPos->z - pModel->modelSet[nModelSet].pos.z);

						// ���W�̐ݒ�
						pPos->x = (300.0f + 10.0f) * sinf(fAngle) + pModel->modelSet[nModelSet].pos.x;
						pPos->z = (300.0f + 10.0f) * cosf(fAngle) + pModel->modelSet[nModelSet].pos.z;
					}
				}
				else if (fLengthCurrent < 300.0f)
				{
					if ((pPosOld->y >= pModel->modelSet[nModelSet].pos.y + pModel->modelSet[nModelSet].vtxMaxModel.y) &&
						(pPos->y < pModel->modelSet[nModelSet].pos.y + pModel->modelSet[nModelSet].vtxMaxModel.y))
					{
						pPos->y = pModel->modelSet[nModelSet].pos.y + pModel->modelSet[nModelSet].vtxMaxModel.y;

						// ����Ă邱�Ƃ�`����
						bCollisionModel = true;
					}
					if (pPos->y >= pModel->modelSet[nModelSet].pos.y + pModel->modelSet[nModelSet].vtxMaxModel.y)
					{
						// �e�̈ʒu���Œ�
						PosShadow->y = pModel->modelSet[nModelSet].pos.y + pModel->modelSet[nModelSet].vtxMaxModel.y;
					}
				}
			}
		}
	}
	return bCollisionModel;
}

//-----------------------------------------------------------------
// ���f���̐ݒu
//-----------------------------------------------------------------
void SetModel(int type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nCollition)
{
	// �\���̂̃|�C���^�ϐ�
	ModelSetInfo *pModelSetInfo = &g_ModelSet.modelSet[0];

	for (int nCntSetModel = 0; nCntSetModel < MAX_MODEL; nCntSetModel++, pModelSetInfo++)
	{
		if (pModelSetInfo->bUse == false)
		{
			// �^�C�v�̑��
			pModelSetInfo->nIdx = type;

			// �ʒu���̑��
			pModelSetInfo->pos = pos;

			// �������̑��
			pModelSetInfo->rot = rot;

			// �����蔻�肷�邩�ǂ������
			if (nCollition == 0)
			{
				pModelSetInfo->bCollision = true;
			}
			else
			{
				pModelSetInfo->bCollision = false;
			}
			// �g�p��Ԃ�true�ɂ���
			pModelSetInfo->bUse = true;

			break;
		}
	}
}

//-----------------------------------------------------------------
// ���f�����̎擾
//-----------------------------------------------------------------
ModelSet *GetModelSet(void)
{
	return &g_ModelSet;
}