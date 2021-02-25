////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �I�u�W�F�N�g�̏��� [object.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/12/10
//
////////////////////////////////////////////////////////////////////////////////
#include "object.h"
#include "player.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define DELETE_OBJECT (30)

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPD3DXMESH  g_pMeshObject = NULL;				//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatObject = NULL;			//�}�e���A��(�ގ����)�ւ̃|�C���^
DWORD g_nNumMatObject;							//�}�e���A���̐�
D3DXVECTOR3 g_vtxMinObject, g_vtxMaxObject;		//���f���̍ŏ��l�A�ő�l
LPDIRECT3DTEXTURE9 g_pTextureObject[256] = {};	//�e�N�X�`���ւ̃|�C���^
OBJECT g_aObject[MAX_OBJECT];					//�I�u�W�F�N�g�̏��

////////////////////////////////////////////////////////////////////////////////
//�I�u�W�F�N�g�̏���������
////////////////////////////////////////////////////////////////////////////////
void InitObject(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	
	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		g_aObject[nCntObj].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aObject[nCntObj].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aObject[nCntObj].bUse = false;
		g_aObject[nCntObj].nCount = 0;
	}

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/model/Rock.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject, NULL, &g_nNumMatObject, &g_pMeshObject);

	int nNumVtx;		//���_��
	DWORD sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	D3DXMATERIAL *pMat;	//�}�e���A���̃|�C���^

	//�}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatObject->GetBufferPointer();

	//�e�N�X�`���̓ǂݍ���
	for (int nCntMat = 0; nCntMat < (int)g_nNumMatObject; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, g_pTextureObject);
		}
	}

	//���_�����擾
	nNumVtx = g_pMeshObject->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshObject->GetFVF());

	//���_�o�b�t�@�����b�N
	g_pMeshObject->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

		//�S�Ă̒��_���r���ă��f���̍ŏ��l�A�ő�l�𔲂��o��
		if (vtx.x < g_vtxMinObject.x)
		{
			g_vtxMinObject.x = vtx.x;
		}
		if (vtx.x > g_vtxMaxObject.x)
		{
			g_vtxMaxObject.x = vtx.x;
		}
		if (vtx.y < g_vtxMinObject.y)
		{
			g_vtxMinObject.y = vtx.y;
		}
		if (vtx.y > g_vtxMaxObject.y)
		{
			g_vtxMaxObject.y = vtx.y;
		}
		if (vtx.z < g_vtxMinObject.z)
		{
			g_vtxMinObject.z = vtx.z;
		}
		if (vtx.z > g_vtxMaxObject.z)
		{
			g_vtxMaxObject.z = vtx.z;
		}

		pVtxBuff += sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pMeshObject->UnlockVertexBuffer();
}

////////////////////////////////////////////////////////////////////////////////
//�I�u�W�F�N�g�̏I������
////////////////////////////////////////////////////////////////////////////////
void UninitObject(void)
{
	//���b�V���̔j��
	if (g_pMeshObject != NULL)
	{
		g_pMeshObject->Release();	//�j��
		g_pMeshObject = NULL;		//������
	}

	//�}�e���A���̊J��
	if (g_pBuffMatObject != NULL)
	{
		g_pBuffMatObject->Release();	//�J��
		g_pBuffMatObject = NULL;		//������
	}
}

////////////////////////////////////////////////////////////////////////////////
//�I�u�W�F�N�g�̍X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateObject(void)
{
	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		if (g_aObject[nCntObj].bUse == true)
		{
			g_aObject[nCntObj].nCount++;

			if (g_aObject[nCntObj].nCount == DELETE_OBJECT)
			{
				g_aObject[nCntObj].nCount = 0; 
				g_aObject[nCntObj].bUse = false;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�I�u�W�F�N�g�̕`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawObject(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		if (g_aObject[nCntObj].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aObject[nCntObj].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aObject[nCntObj].rot.y, g_aObject[nCntObj].rot.x, g_aObject[nCntObj].rot.z);
			D3DXMatrixMultiply(&g_aObject[nCntObj].mtxWorld, &g_aObject[nCntObj].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aObject[nCntObj].pos.x, g_aObject[nCntObj].pos.y, g_aObject[nCntObj].pos.z);
			D3DXMatrixMultiply(&g_aObject[nCntObj].mtxWorld, &g_aObject[nCntObj].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aObject[nCntObj].mtxWorld);

			//���݂̃}�e���A���̎擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL *)g_pBuffMatObject->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatObject; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureObject[nCntMat]);

				//���f��(�p�[�c)�̕`��
				g_pMeshObject->DrawSubset(nCntMat);
			}

			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�Z�b�g����
////////////////////////////////////////////////////////////////////////////////
void SetObject(D3DXVECTOR3 pos)
{
	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		if (g_aObject[nCntObj].bUse == false)
		{
			g_aObject[nCntObj].pos = pos;
			g_aObject[nCntObj].bUse = true;
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�����蔻��
////////////////////////////////////////////////////////////////////////////////
bool CollisionObject(D3DXVECTOR3 pos, D3DXVECTOR3 oldpos)
{

	//D3DXVECTOR3 max;
	//D3DXVECTOR3 min;
	//D3DXVECTOR3 *pPosPlayer = GetPosPlayer();
	//D3DXVECTOR3 *pPosOldPlayer = GetPosOld();

	//
	//max = g_vtxMaxObject + g_posObject;
	//min = g_vtxMinObject + g_posObject;

	//if (pos.x + PLAYER_SIZEXZ > min.x && pos.x - PLAYER_SIZEXZ < max.x)
	//{
	//	if (pos.z + PLAYER_SIZEXZ > min.z && pos.z - PLAYER_SIZEXZ < max.z)
	//	{
	//		if (oldpos.y > max.y)
	//		{
	//			if (pos.y < max.y)
	//			{
	//				return true;
	//			}
	//		}
	//		else if (oldpos.y + PLAYER_SIZEY < min.y)
	//		{
	//			if (pos.y + PLAYER_SIZEY > min.y)
	//			{
	//				pPosPlayer->y = pPosOldPlayer->y;
	//			}
	//		}
	//	}

	//	for (int nCnt = 0; nCnt < (int)PLAYER_SIZEY; nCnt++)
	//	{
	//		if (pos.y + nCnt > min.y && pos.y + nCnt < max.y)
	//		{
	//			if (oldpos.z + PLAYER_SIZEXZ < min.z || oldpos.z - PLAYER_SIZEXZ > max.z)
	//			{
	//				if (pos.z + PLAYER_SIZEXZ > min.z && pos.z - PLAYER_SIZEXZ < max.z)
	//				{
	//					pPosPlayer->z = pPosOldPlayer->z;
	//				}
	//			}
	//		}
	//	}
	//}
	//if (pos.z + PLAYER_SIZEXZ > min.z && pos.z - PLAYER_SIZEXZ < max.z)
	//{
	//	for (int nCnt = 0; nCnt < (int)PLAYER_SIZEY; nCnt++)
	//	{
	//		if (pos.y + nCnt > min.y && pos.y + nCnt < max.y)
	//		{
	//			if (oldpos.x + PLAYER_SIZEXZ < min.x || oldpos.x - PLAYER_SIZEXZ > max.x)
	//			{
	//				if (pos.x + PLAYER_SIZEXZ > min.x && pos.x - PLAYER_SIZEXZ < max.x)
	//				{
	//					pPosPlayer->x = pPosOldPlayer->x;
	//				}
	//			}
	//		}
	//	}
	//}
	return false;
}