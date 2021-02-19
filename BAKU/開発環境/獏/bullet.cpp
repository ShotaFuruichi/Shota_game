////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �e�̏��� [bullet.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/12/01
//
////////////////////////////////////////////////////////////////////////////////
#include "bullet.h"
#include "wall.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define MAX_BULLET (256)	//�e�̍ő吔
#define BULLET_SIZE (20.0f)	//�e�̑傫��

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//���_���
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;			//�e�N�X�`�����
BULLET g_aBullet[MAX_BULLET];

////////////////////////////////////////////////////////////////////////////////
//����������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitBullet(void)
{
	//�ϐ��錾
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &g_pTextureBullet);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].bUse = false;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffBullet, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W�̐ݒ�
		SetVertexBullet(nCntBullet);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�I������
////////////////////////////////////////////////////////////////////////////////
void UninitBullet(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();	//�J��
		g_pVtxBuffBullet = NULL;		//������
	}

	//�e�N�X�`���̊J��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();	//�J��
		g_pTextureBullet = NULL;		//������
	}
}

////////////////////////////////////////////////////////////////////////////////
//�X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateBullet(void)
{
	WALL *wall = GetWall();
	VERTEX_3D WallVtx = *GetVtx();

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			// �ʒu�X�V
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
			g_aBullet[nCntBullet].pos.z += g_aBullet[nCntBullet].move.z;

			//��������
			g_aBullet[nCntBullet].nLife--;

			if (g_aBullet[nCntBullet].nLife == 0)
			{
				g_aBullet[nCntBullet].bUse = false;
			}

			if (g_aBullet[nCntBullet].pos.z > wall->pos.z)
			{
				//g_aBullet[nCntBullet].move.z = (2 * (((wall->pos.x - g_aBullet[nCntBullet].pos.x) * (WallVtx.nor.x)) + ((wall->pos.z - g_aBullet[nCntBullet].pos.z) * (WallVtx.nor.z))));
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawBullet(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxTrans;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 120);

	//���C�e�B���O�̖���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aBullet[nCntBullet].mtxworld);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

#if 0
			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			//�t�s������߂�
			D3DXMatrixInverse(&g_aBullet[nCntBullet].mtxworld, NULL, &mtxView);

			//���s�ړ��̕����͖�������
			g_aBullet[nCntBullet].mtxworld._41 = 0.0f;
			g_aBullet[nCntBullet].mtxworld._42 = 0.0f;
			g_aBullet[nCntBullet].mtxworld._43 = 0.0f;
#endif

#if 1
			g_aBullet[nCntBullet].mtxworld._11 = mtxView._11;
			g_aBullet[nCntBullet].mtxworld._12 = mtxView._21;
			g_aBullet[nCntBullet].mtxworld._13 = mtxView._31;
			g_aBullet[nCntBullet].mtxworld._21 = mtxView._12;
			g_aBullet[nCntBullet].mtxworld._22 = mtxView._22;
			g_aBullet[nCntBullet].mtxworld._23 = mtxView._32;
			g_aBullet[nCntBullet].mtxworld._31 = mtxView._13;
			g_aBullet[nCntBullet].mtxworld._32 = mtxView._23;
			g_aBullet[nCntBullet].mtxworld._33 = mtxView._33;
#endif

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxworld, &g_aBullet[nCntBullet].mtxworld, &mtxTrans);

			//���[���h�}�g���b�N�X
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].mtxworld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBullet);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}

	//���e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	//���C�e�B���O��L��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

////////////////////////////////////////////////////////////////////////////////
//�Z�b�g����
////////////////////////////////////////////////////////////////////////////////
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife)
{
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = nLife;
			g_aBullet[nCntBullet].bUse = true;
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//���_���W�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void SetVertexBullet(int nIdx)
{
	//�ϐ��錾
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	//pVtx�̃|�C���^����
	pVtx += nIdx * 4;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_SIZE, g_aBullet[nIdx].pos.z - BULLET_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_SIZE, g_aBullet[nIdx].pos.z + BULLET_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_SIZE, g_aBullet[nIdx].pos.z - BULLET_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_SIZE, g_aBullet[nIdx].pos.z + BULLET_SIZE, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}