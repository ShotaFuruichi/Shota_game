////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �p�[�e�B�N���̏��� [perticle.cpp]
//Author	: Shota Furuichi
//Since		: 2020/10/26
//
////////////////////////////////////////////////////////////////////////////////
#include "perticle.h"
#include <time.h>

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define MAX_PERTICLE (4096)	//�p�[�e�B�N���ő吔
#define PERT_SIZE (10.0f)	//�p�[�e�B�N���T�C�Y

////////////////////////////////////////////////////////////////////////////////
//�\���̂̒�`
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	D3DXVECTOR3 pos; 
	D3DXVECTOR3 move;
	D3DXCOLOR color;;
	float fRadius;
	int nLife;
	bool bUse;

} PERTICLE;

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
PERTICLE g_Perticle[MAX_PERTICLE];
D3DXVECTOR3 g_posBase;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPerticle = NULL;	//���_���
LPDIRECT3DTEXTURE9 g_pTexturePerticle = NULL;		//�e�N�X�`�����


////////////////////////////////////////////////////////////////////////////////
//����������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitPerticle(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &g_pTexturePerticle);


	for (int nCntPert = 0; nCntPert < MAX_PERTICLE; nCntPert++)
	{
		g_Perticle[MAX_PERTICLE].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_Perticle[MAX_PERTICLE].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Perticle[MAX_PERTICLE].color = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		g_Perticle[MAX_PERTICLE].fRadius = 0.0f;
		g_Perticle[MAX_PERTICLE].nLife = 0;
		g_Perticle[MAX_PERTICLE].bUse = false;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PERTICLE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPerticle, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPerticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPert = 0; nCntPert < MAX_PERTICLE; nCntPert++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_Perticle[MAX_PERTICLE].pos.x - g_Perticle[MAX_PERTICLE].fRadius, g_Perticle[MAX_PERTICLE].pos.y + g_Perticle[MAX_PERTICLE].fRadius, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Perticle[MAX_PERTICLE].pos.x - g_Perticle[MAX_PERTICLE].fRadius, g_Perticle[MAX_PERTICLE].pos.y - g_Perticle[MAX_PERTICLE].fRadius, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Perticle[MAX_PERTICLE].pos.x + g_Perticle[MAX_PERTICLE].fRadius, g_Perticle[MAX_PERTICLE].pos.y + g_Perticle[MAX_PERTICLE].fRadius, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Perticle[MAX_PERTICLE].pos.x + g_Perticle[MAX_PERTICLE].fRadius, g_Perticle[MAX_PERTICLE].pos.y - g_Perticle[MAX_PERTICLE].fRadius, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPerticle->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�I������
////////////////////////////////////////////////////////////////////////////////
void UninitPerticle(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffPerticle != NULL)
	{
		g_pVtxBuffPerticle->Release();	//�J��
		g_pVtxBuffPerticle = NULL;		//������
	}

	//�e�N�X�`���̊J��
	if (g_pTexturePerticle != NULL)
	{
		g_pTexturePerticle->Release();	//�J��
		g_pTexturePerticle = NULL;		//������
	}
}

////////////////////////////////////////////////////////////////////////////////
//�X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdatePerticle(void)
{
	PERTICLE *pPerticle;
	pPerticle = &g_Perticle[0];

	for (int nCntPert = 0; nCntPert < MAX_PERTICLE; nCntPert++, pPerticle++)
	{
		if (pPerticle->bUse == true)
		{

		}
	}
	pPerticle = &g_Perticle[0];

	for (int nCntAppear = 0; nCntAppear < 128; nCntAppear++)
	{
		for (int nCntPert = 0; nCntPert < MAX_PERTICLE; nCntPert++, pPerticle++)
		{
			if (pPerticle->bUse == false)
			{
				pPerticle->pos = g_posBase;
				pPerticle->fRadius = GetRandom(5.0f, 10.0f);
				pPerticle->color = D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f);
				pPerticle->nLife = (int)GetRandom(10.0f, 15.0f);

			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawPerticle(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPerticle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntPert = 0; nCntPert < MAX_PERTICLE; nCntPert++)
	{
		if (g_Perticle[nCntPert].bUse == true)
		{	//�e���g�p����Ă���ꍇ
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturePerticle);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPert * 4, 2);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�����_���Ȑ��l���擾
////////////////////////////////////////////////////////////////////////////////
float GetRandom(float min, float max)
{
	static int nNum;

	if (nNum == 0)
	{
		srand((unsigned int)time(NULL));
		nNum = 1;
	}

	return min + (int)(rand() * (max - min + 1.0f) / (1.0f + RAND_MAX));
}