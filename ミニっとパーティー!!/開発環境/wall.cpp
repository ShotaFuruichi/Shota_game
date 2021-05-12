//-----------------------------------------------------------------
//
// �� (wall.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "wall.h"
#include "input.h"
#include "gamepad.h"
#include "texture.h"

//-----------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------
#define MAX_WALL		(16)							// ���b�V���t�B�[���h�ő吔
#define MAX_WALL_VTX	(200)							// ���b�V���t�B�[���h�̒��_�ő吔
#define MAX_INDEX		(200)							// �C���f�b�N�X�ő吔

#define WIDTH_NUM		(g_MeshOrbit[nCntWall].nCntWallX)	// ��
#define HEIGHT_NUM		(g_MeshOrbit[nCntWall].nCntWallY)	// �s
#define WIDTH			(g_MeshOrbit[nCntWall].fWidth)		// ��
#define HEIGHT			(g_MeshOrbit[nCntWall].fHieght)		// ���s
#define WIDTH_VEC		(WIDTH_NUM + 1)					// ��̒��_��
#define HEIGHT_VEC		(HEIGHT_NUM + 1)				// �s�̒��_��

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
Wall g_MeshOrbit[MAX_WALL];												// �ǂ̏��

//-----------------------------------------------------------------
// �ǂ̏���������
//-----------------------------------------------------------------
HRESULT InitWall(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n���A������
	pDevice = GetDevice();

	// �ϐ��̏�����
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_MeshOrbit[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshOrbit[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshOrbit[nCntWall].moveRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshOrbit[nCntWall].nCntWallX = 0;
		g_MeshOrbit[nCntWall].nCntWallY = 0;
		g_MeshOrbit[nCntWall].nCntVecX = 0;
		g_MeshOrbit[nCntWall].nCntVecY = 0;
		g_MeshOrbit[nCntWall].fWidth = 0.0f;
		g_MeshOrbit[nCntWall].fHieght = 0.0f;
		g_MeshOrbit[nCntWall].fsizeWidth = 1.0f;
		g_MeshOrbit[nCntWall].fsizeHieght = 0.0f;
		g_MeshOrbit[nCntWall].nVetex = 0;
		g_MeshOrbit[nCntWall].nIndex = 0;
		g_MeshOrbit[nCntWall].nPrimitive = 0;
		g_MeshOrbit[nCntWall].nIdxtexture = 0;
		g_MeshOrbit[nCntWall].bUse = false;

		// ���_�o�b�t�@�̐���
		if (FAILED(pDevice->CreateVertexBuffer(
			sizeof(VERTEX_3D) * MAX_WALL_VTX,	// �m�ۂ���o�b�t�@�T�C�Y
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,									// ���_�t�H�[�}�b�g
			D3DPOOL_MANAGED,
			&g_MeshOrbit[nCntWall].pVtxBuffWall,
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
			&g_MeshOrbit[nCntWall].pIdxBuffWall,
			NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//-----------------------------------------------------------------
// �ǂ̏I������
//-----------------------------------------------------------------
void UninitWall(void)
{
	// �ϐ��̏�����
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		// �C���f�b�N�X�̊J��
		if (g_MeshOrbit[nCntWall].pIdxBuffWall != NULL)
		{
			g_MeshOrbit[nCntWall].pIdxBuffWall->Release();
			g_MeshOrbit[nCntWall].pIdxBuffWall = NULL;
		}

		// ���_�o�b�t�@�̊J��
		if (g_MeshOrbit[nCntWall].pVtxBuffWall != NULL)
		{
			g_MeshOrbit[nCntWall].pVtxBuffWall->Release();
			g_MeshOrbit[nCntWall].pVtxBuffWall = NULL;
		}
	}
}

//-----------------------------------------------------------------
// �ǂ̍X�V����
//-----------------------------------------------------------------
void UpdateWall(void)
{
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_MeshOrbit[nCntWall].bUse == true)
		{
			// ��]�ʂ̍X�V
			g_MeshOrbit[nCntWall].rot += g_MeshOrbit[nCntWall].moveRot;
		}
	}
}

//-----------------------------------------------------------------
// �ǂ̕`�揈��
//-----------------------------------------------------------------
void DrawWall(void)
{
	// �ϐ��錾
	Wall *pWall = &g_MeshOrbit[0];
	Texture *pTexture = GetTexture();
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxScaling,mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// �A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 120);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, pWall++)
	{
		if (pWall->bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&pWall->mtxWorld);

			// �����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pWall->rot.y, pWall->rot.x, pWall->rot.z);
			D3DXMatrixMultiply(&pWall->mtxWorld, &pWall->mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pWall->pos.x, pWall->pos.y, pWall->pos.z);
			D3DXMatrixMultiply(&pWall->mtxWorld, &pWall->mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pWall->mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, pWall->pVtxBuffWall, 0, sizeof(VERTEX_3D));

			// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(pWall->pIdxBuffWall);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �|���S���̕`��
			pDevice->SetTexture(0, pTexture->TextureInfo[pWall->nIdxtexture].pTexture);
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, pWall->nVetex, 0, pWall->nPrimitive);
		}
	}

	// �A���t�@�e�X�g�����̐ݒ�ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
}

//-----------------------------------------------------------------
// �ǂ̔z�u
//-----------------------------------------------------------------
void SetWall(int type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 moveRot,int blockX, int blockY, float sizeX, float sizeY)
{
	// �\���̂̃|�C���^�ϐ�
	Wall *pWall = &g_MeshOrbit[0];

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, pWall++)
	{
		if (pWall->bUse == false)
		{
			// �ʒu�̐ݒ�
			// �e�N�X�`���^�C�v�̐ݒ�
			pWall->nIdxtexture = type;

			// �ʒu�̐ݒ�
			pWall->pos = pos;

			// �p�x�̐ݒ�
			pWall->rot = rot;

			// ��]�ʂ̐ݒ�
			pWall->moveRot = moveRot;

			// �u���u���b�N��(X)�̐ݒ�
			pWall->nCntWallX = blockX;

			// �u���u���b�N��(Z)�̐ݒ�
			pWall->nCntWallY = blockY;

			// �T�C�Y(X)�̐ݒ�
			pWall->fWidth = sizeX;

			// �T�C�Y(Z)�̐ݒ�
			pWall->fHieght = sizeY;

			// �g�p��Ԃ�ture�ɂ���
			pWall->bUse = true;

			// �T�C�Y�̊m��
			pWall->fsizeWidth = pWall->nCntWallX * pWall->fWidth;
			pWall->fsizeHieght = pWall->nCntWallY * pWall->fHieght;

			// ���_���ƃC���f�b�N�X���A�v���~�e�B�u���̊m��
			pWall->nVetex = ((pWall->nCntWallX + 1) * (pWall->nCntWallY + 1));
			pWall->nPrimitive = (pWall->nCntWallX * pWall->nCntWallY * 2) + (4 * (pWall->nCntWallY - 1));

			// �\���̂̃|�C���^�ϐ�
			VERTEX_3D *pVtx;

			// �C���f�b�N�X���ւ̃|�C���^
			WORD *pIdx;

			// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			pWall->pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

			// �C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
			pWall->pIdxBuffWall->Lock(0, 0, (void**)&pIdx, 0);

			for (int nCntZ = 0; nCntZ < HEIGHT_VEC; nCntZ++)
			{
				for (int nCntX = 0; nCntX < WIDTH_VEC; nCntX++)
				{
					// ���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3((-pWall->fsizeWidth / 2.0f + (float)nCntX * pWall->fWidth) + pWall->pos.x,
						(pWall->fsizeHieght /2.0f - (float)nCntZ * pWall->fHieght) + pWall->pos.y,
						0.0f);

					// �@���x�N�g���̐ݒ�
					pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

					// ���_�J���[�̐ݒ�
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					// �e�N�X�`�����W
					pVtx[0].tex = D3DXVECTOR2(1.0f * nCntX, 1.0f * nCntZ);

					// ���̏��
					pVtx++;
				}
			}

			for (int nCntZ = 0; nCntZ < HEIGHT_NUM; nCntZ++)
			{
				for (int nCntX = 0; nCntX < WIDTH_VEC + 1; nCntX++)
				{
					if (nCntX != 0 && nCntX == WIDTH_VEC && nCntZ != HEIGHT_NUM - 1)
					{// �E�[����܂�Ԃ���
						pIdx[0] = pIdx[-1];
						pIdx[1] = pIdx[-2] + 1;
					}
					else if (nCntZ == HEIGHT_NUM - 1 && nCntX == WIDTH_VEC)
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
			pWall->pVtxBuffWall->Unlock();

			// �C���f�b�N�X�o�b�t�@���A�����b�N����
			pWall->pIdxBuffWall->Unlock();

			break;
		}
	}
}

//-----------------------------------------------------------------
// �ǂƂ̓����蔻��
//-----------------------------------------------------------------
void CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pvtxMin, D3DXVECTOR3 *pvtxMax)
{
	
}

//-----------------------------------------------------------------
// �Ǐ��̎擾
//-----------------------------------------------------------------
Wall *GetWall(void)
{
	return &g_MeshOrbit[0];
}