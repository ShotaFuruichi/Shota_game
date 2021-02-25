////////////////////////////////////////////////////////////////////////////////
//
//Contents	: ���@�w [circle.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/02/25
//
////////////////////////////////////////////////////////////////////////////////
#include "circle.h"
#include "player.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define MAX_CIRCLE (2)				//�U���̍ő吔
#define CIRCLE_SIZE (300)			//�~�̑傫��

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCircle = NULL;	//���_���
LPDIRECT3DTEXTURE9 g_pTextureCircle = NULL;			//�e�N�X�`�����
MAGICCIRCLE g_aCircle[MAX_CIRCLE];					//�G�̍U��

////////////////////////////////////////////////////////////////////////////////
//����������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitCircle(void)
{
	//�ϐ��錾
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\mahojin2.png", &g_pTextureCircle);

	for (int nCntCircle = 0; nCntCircle < MAX_CIRCLE; nCntCircle++)
	{
		g_aCircle[nCntCircle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCircle[nCntCircle].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCircle[nCntCircle].bUse = false;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_CIRCLE, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffCircle, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCircle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntCircle = 0; nCntCircle < MAX_CIRCLE; nCntCircle++)
	{
		SetVertexCircle(nCntCircle);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCircle->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�I������
////////////////////////////////////////////////////////////////////////////////
void UninitCircle(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffCircle != NULL)
	{
		g_pVtxBuffCircle->Release();	//�J��
		g_pVtxBuffCircle = NULL;		//������
	}

	//�e�N�X�`���̊J��
	if (g_pTextureCircle != NULL)
	{
		g_pTextureCircle->Release();	//�J��
		g_pTextureCircle = NULL;		//������
	}
}

////////////////////////////////////////////////////////////////////////////////
//�X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateCircle(void)
{
	PLAYER *player = GetPlayer();

	for (int nCntCircle = 0; nCntCircle < MAX_CIRCLE; nCntCircle++)
	{
		if (g_aCircle[nCntCircle].bUse == true)
		{
			if (player->bChant == false)
			{
				g_aCircle[nCntCircle].bUse = false;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawCircle(void)
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

	for (int nCntCircle = 0; nCntCircle < MAX_CIRCLE; nCntCircle++)
	{
		if (g_aCircle[nCntCircle].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aCircle[nCntCircle].mtxworld);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aCircle[nCntCircle].pos.x, g_aCircle[nCntCircle].pos.y, g_aCircle[nCntCircle].pos.z);
			D3DXMatrixMultiply(&g_aCircle[nCntCircle].mtxworld, &g_aCircle[nCntCircle].mtxworld, &mtxTrans);

			//���[���h�}�g���b�N�X
			pDevice->SetTransform(D3DTS_WORLD, &g_aCircle[nCntCircle].mtxworld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffCircle, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureCircle);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntCircle * 4, 2);
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
//�G�̍U���̃Z�b�g����
////////////////////////////////////////////////////////////////////////////////
void SetCircle(int nSkill)
{
	PLAYER *player = GetPlayer();
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCircle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntCircle = 0; nCntCircle < MAX_CIRCLE; nCntCircle++)
	{
		if (g_aCircle[nCntCircle].bUse == false)
		{
			switch (nSkill)
			{
			case SKILL_MAGICBALL:

				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 0.6f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.6f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.6f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.6f, 0.0f, 1.0f);
				break; 

			case SKILL_HEAL:

				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.6f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.6f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.6f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.6f, 1.0f);
				break;
			}

			g_aCircle[nCntCircle].pos = D3DXVECTOR3(player->pos.x, 1.0f, player->pos.z);
			g_aCircle[nCntCircle].bUse = true;
			break;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCircle->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//���_���W�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void SetVertexCircle(int nIdx)
{
	//�ϐ��錾
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCircle->Lock(0, 0, (void**)&pVtx, 0);

	//pVtx�̃|�C���^����
	pVtx += nIdx * 4;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aCircle[nIdx].pos.x - CIRCLE_SIZE, 1, g_aCircle[nIdx].pos.z - CIRCLE_SIZE);
	pVtx[1].pos = D3DXVECTOR3(g_aCircle[nIdx].pos.x - CIRCLE_SIZE, 1, g_aCircle[nIdx].pos.z + CIRCLE_SIZE);
	pVtx[2].pos = D3DXVECTOR3(g_aCircle[nIdx].pos.x + CIRCLE_SIZE, 1, g_aCircle[nIdx].pos.z - CIRCLE_SIZE);
	pVtx[3].pos = D3DXVECTOR3(g_aCircle[nIdx].pos.x + CIRCLE_SIZE, 1, g_aCircle[nIdx].pos.z + CIRCLE_SIZE);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCircle->Unlock();
}